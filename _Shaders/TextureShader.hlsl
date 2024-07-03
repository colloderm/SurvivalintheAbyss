
// VertexShader���� ����� ������
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

// PixelShader���� ����� ������
struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
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
    
    return output;
};

cbuffer ShadedBuffer : register(b0)
{
    int _selection;
    
    int _blurCount;
    float2 _textureSize;
}

cbuffer AlphaBuffer : register(b1)
{
    float4 _alphaColor;
    float _alphaCount;
    bool _alpha;
};

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

// Sampler�� �̹������� ������ �ȼ������͸� �о�� �ش� �����Ͱ� ������ �ִ�
// ������ �̾Ƴ��ִ� �۾��� ���Ѵ�.

// SV_Target�� ������ ����� �����͸� �����ؼ� ������ ����Ѵ�.
// ������ ����ϸ� �ȴ�.
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    
    // discard�� �ش� �ȼ��� �׸��� �ʰڴ� ��� ��ɾ��̰�
    // discard�� ���� ����κ��� �ڿ� �ִ� �׸��� �� �� �ִ�. // 0~1 // 0.01~0.99f
    // if (color.r <= 0.01f && color.g <= 0.01f && color.b <= 0.01f)
    if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) // ����Ÿ �� (255, 0, 255)
        discard;
    
    if(_selection == 1)
    {
    }
    else if (_selection == 2)
    {
        // ��� ó��
        float3 gray = dot(color.rbg, float3(0.299f, 0.587f, 0.114f)); // ���Ӿ��迡�� ���� ���� ����ڵ� float3(0.299f, 0.587f, 0.114f)
        color = float4(gray, color.a);
    }
    else if (_selection == 3)
    {
        // �� ���� (��ġ���)
        float3 negative = 1 - abs(color.rgb);
        color = float4(negative, color.a);
    }
    else if (_selection == 4)
    {
        // �� ó��

        // �ֺ� �ȼ� ��ġ
        float2 arr[8] =
        {
            float2(-1, +1), float2(+0, +1), float2(+1, +1),
            float2(-1, +0), /*���� ���� */   float2(+1, +0),
            float2(-1, -1), float2(+0, -1), float2(+1, -1)
        };

        // ���α׷��Ӱ� ������ ���� ���⸸ŭ �ݺ��ϸ� (1 == �� ����)
        for (int blur = 1; blur < _blurCount; blur++)
        {
            // �ֺ� �ȼ� ���� ��ŭ �ݺ�
            for (int i = 0; i < 8; i++)
            {
                // �ֺ� �ȼ� ��ǥ�� ���� uv�� ���
                float x = arr[i].x * (float)blur / _textureSize.x;
                float y = arr[i].y * (float)blur / _textureSize.y;
                
                // �Ի��� uv�� ��ŭ uv�� ����
                float2 uv = input.uv + float2(x, y);
                
                // ã�� uv�� ���� ������ color�� ��� ����
                color += _sourceTex.Sample(_samp, uv);
            };
        };
        
        int blurLoop = _blurCount - 1;
        int offsetCount = 8; // �ֺ�pixel��
        
        int totalSamples = blurLoop * offsetCount + 1;
        
        color = color / totalSamples;
    }
    else if (_selection == 5)
    {
        // �¿� ����
        input.uv.x = 1 - input.uv.x;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);
    }
    else if (_selection == 6)
    {
        // ���� ����
        input.uv.y = 1 - input.uv.y;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);
    }
    else if (_selection == 7)
    {
        // �ܰ���
        if (input.uv.x <= 0.01f || input.uv.x >= 0.99f || 
            input.uv.y <= 0.01f || input.uv.y >= 0.99f)
        {
            color = float4(1, 0, 0, 1);
        };
    }
    
    if(_alpha == true)
    {
        color = color - (color * _alphaCount) + (_alphaColor * _alphaCount); // _alpha == ���� ������ ����
    };
    
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