
// VertexShader���� ����� ������
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
    float2 uv2 : TEXCOORD1;
    float4 color : COLOR0;
    uint index : INDEX0;
};

// PixelShader���� ����� ������
struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float2 uv2 : TEXCOORD1;
    float4 color : COLOR0;
    uint index : INDEX0;
};

cbuffer WorldBuffer : register(b0)
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _proj;
};

PixelInput VS(VertexInput input) // ����� �뵵
{
    PixelInput output;
    
    // ������ ��ġ�� ���带 ���ϰ�
    output.position = mul(input.position, _world);
    // ���尡 ������ �����Ϳ� �並 ���ϰ�
    output.position = mul(output.position, _view);
    // ����� ������ �����Ϳ� �������Ǳ��� ����
    output.position = mul(output.position, _proj);
    // �� ������ ���ؾ� DirectX�� ������ ��ġ�Ѵٰ� �ν��� �� ����.
    
    output.uv = input.uv;
    output.uv2 = input.uv2;
    output.color = input.color;
    output.index = input.index;
    
    return output;
};

cbuffer IndexNumBuffer : register(b0)
{
    uint _index;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

// Sampler�� �̹������� ������ �ȼ������͸� �о�� �ش� �����Ͱ� ������ �ִ�
// ������ �̾Ƴ��ִ� �۾��� ���Ѵ�.

// SV_Target�� ������ ����� �����͸� �����ؼ� ������ ����Ѵ�.
// ������ ����ϸ� �ȴ�.
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    
    if (input.uv.x > 0.0f || input.uv.y > 0.0f)
    {
        // color = color; // �׸��� �׸��ڴ�.
        
        // discard�� �ش� �ȼ��� �׸��� �ʰڴ� ��� ��ɾ��̰�
        // discard�� ���� ����κ��� �ڿ� �ִ� �׸��� �� �� �ִ�. // 0~1 // 0.01~0.99f
        // if (color.r <= 0.01f && color.g <= 0.01f && color.b <= 0.01f)
        if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) // ����Ÿ �� (255, 0, 255)
            discard;
    }
    else
    {
        color = input.color; // �ܻ����� ĥ�ϰڴ�.
        if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) // ����Ÿ �� (255, 0, 255)
            discard;
    }
    
    if (input.index == _index)
    {
        if (input.uv2.x < 0.05f || input.uv2.x > 0.95f || 
            input.uv2.y < 0.05f || input.uv2.y > 0.95f)
            color = float4(1, 0, 0, 1);
    }
    
    return color;
};

/*
Semantic : ����ƽ
- HLSL���� �������� �ǹ̸� �����ϴµ� ����ϴ� ����
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���ϴµ� ���
- ���� �̸��ڿ� : �� �Բ� ������ �� �ִ�.
- SV_ ���λ�� �����ϴ� ����ƽ�� DirectX�� ������ Ư���� �ǹ̸� ���Ѵ�.
- SV_�� �����ϴ� ����ƽ�� �ý��� ��(SystemValue) ����ƽ �̶� �θ���.
- �Ϲ����� ����ƽ�� �̸��� ��ȣ�� VertexType���� ����Ѵ�.

slot : ����
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �پ��� �����͸� �޾ƿ� �ĺ��ϴµ� ����ϴ� ��ȣ
- �� slot�� ������ ��ȣ�� ���ϸ�, �ش� �������� ������ ���ҿ� ���� �پ��� slot�� �����Ѵ�.
- register Ű����� �Բ� ����ϸ� �ڿ� ��õǴ� ��ȣ�� ���α׷����� ����� ��ȣ�̴�.

- ��� ���� ����
- ��� �����͸� �����ϴµ� ���Ǹ�, VS���� ��� �� ��� ���ۿ� PS���� ��� �� ��� ���۸� ������ ��ȣ�� �������� ���� �� ������ �����͸� �����ϴ� �͵� �����ϴ�.
// VSBuffer 0���� �����͸� ����־ PSBuffer 0���� �����͸� ����ִ� ���� �����ϸ� ������ ������ ����
// VSBuffer 0���� ������� �����͸� PixelShader���� ����ϴ� �͵� �����ϴ�.
// �����͸� ���� �� �� �ִ�.
- �ַ� ������ �ƴ� �����͸� �ǳ��� �� ���ȴ�.
- register(b#)�� ����Ͽ� �����Ѵ�.
// # = ���Թ�ȣ

- �ؽ�ó ����
- �̹����� �����͸� �����ϴµ� ���
- register(t#)�� ����Ͽ� �����Ѵ�.

- ���÷� ����
- �̹����� �����ϴ� ���� ����Ǵ� ����
- register(s#)�� ����Ͽ� �����Ѵ�.

cbuffer : ��� ���� // constant buffer
- ���̴����� ����� �� �ִ� ���� ������ �����ϴµ� ���
- CPU���� ������ �ƴ� �����͸� �����ϴµ� ���
- ShaderBuffer�� �̿��� ������ ������� ������ ����Ѵ�.
*/