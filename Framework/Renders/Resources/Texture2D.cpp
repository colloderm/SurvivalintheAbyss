#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

// 텍스쳐2D를 생성하거나, 따로 만들때 해당 텍스쳐 데이터가 이미 있는지를
// 확인하고 중복해서 만들지 않도록 해주는 함수
void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// 그림 주소의 확장자 추출
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	// 그림의 너비와 높이 변수화
	UINT width = metaData.width;
	UINT height = metaData.height;

	// 사용할 텍스쳐 desc에 데이터 담기
	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	// 중복 검사용 변수들
	TextureDesc exist;
	bool bExist = false;

	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			// 주소, 너비, 높이가 같은 이미지가 있을경우
			bExist = true;
			// 만들어져있는 TextureDesc를 넘긴다.
			exist = temp;
			break;
		}
	}

	// 텍스쳐 데이터가 이미 있었다면
	if (bExist == true)
	{
		texture->srv = exist.srv;
		texture->metaData = metaData;
	}
	else // 새로운 그림이라면
	{
		// 이미지 추출 하는데 사용
		ScratchImage image;

		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;
		
		descs.push_back(desc);
	}
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	// 원본 텍스쳐 정보
	D3D11_TEXTURE2D_DESC srvDesc;
	texture->GetDesc(&srvDesc);

	// 원본 텍스쳐 복사본
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// 복사본 desc 설정
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srvDesc.Width;
	destDesc.Height = srvDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srvDesc.Format;
	destDesc.SampleDesc = srvDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	// 그림이 가지고 있는 픽셀값을 하나하나 전부 추출
	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subRe);
	{
		memcpy(colors, subRe.pData, sizeof(UINT) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	int pixelNum = destDesc.Width * destDesc.Height;

	{
		UINT* alpha	= new UINT[pixelNum];
		UINT* red	= new UINT[pixelNum];
		UINT* green = new UINT[pixelNum];
		UINT* blue	= new UINT[pixelNum];

		for (int i = 0; i < pixelNum; i++)
		{
			alpha[i] = (colors[i] & 0xFF000000);
			red[i]	 = (colors[i] & 0x00FF0000);
			green[i] = (colors[i] & 0x0000FF00);
			blue[i]	 = (colors[i] & 0x000000FF);

			// OpenGL은 ARGB가 아닌 ABGR의 순서이기 때문에 R와 B의 위치를 바꿔준다.
			red[i] = colors[i] >> 16;
			blue[i] = colors[i] << 16;

			colors[i] = alpha[i] | red[i] | green[i] | blue[i];
		}
		pixels->assign(&colors[0], &colors[pixelNum - 1]);
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_DELETE(destTex);
}
