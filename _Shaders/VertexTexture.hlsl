
// VertexShader에서 사용할 데이터
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

// PixelShader에서 사용할 데이터
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

PixelInput VS(VertexInput input) // 점찍는 용도
{
    PixelInput output;
    
    // 정점의 위치에 월드를 곱하고
    output.position = mul(input.position, _world);
    // 월드가 곱해진 데이터에 뷰를 곱하고
    output.position = mul(output.position, _view);
    // 뷰까지 곱해진 데이터에 프로젝션까지 곱함
    output.position = mul(output.position, _proj);
    // 이 순서로 곱해야 DirectX가 공간에 위치한다고 인식할 수 있음.
    
    output.uv = input.uv;
    
    return output;
};

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

// Sampler는 이미지에서 각각의 픽셀데이터를 읽어와 해당 데이터가 가지고 있는
// 색깔을 뽑아내주는 작업을 말한다.

// SV_Target은 이전에 사용한 데이터를 연속해서 가져와 사용한다.
// 정도로 기억하면 된다.
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    
    // discard는 해당 픽셀을 그리지 않겠다 라는 명령어이고
    // discard를 통해 지운부분은 뒤에 있는 그림도 볼 수 있다. // 0~1 // 0.01~0.99f
    // if (color.r <= 0.01f && color.g <= 0.01f && color.b <= 0.01f)
    if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) // 마젠타 색 (255, 0, 255)
        discard;
    
    return color;
};

/*
Semantic : 세멘틱
- HLSL에서 데이터의 의미를 지정하는데 사용하는 문자
- 쉐이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리하는데 사용
- 변수 이름뒤에 : 과 함께 지정할 수 있다.
- SV_ 접두사로 시작하는 세멘틱은 DirectX가 지정한 특수한 의미를 지닌다.
- SV_로 시작하는 세멘틱을 시스템 값(SystemValue) 세멘틱 이라 부른다.
- 일반적인 세멘틱의 이름과 번호는 VertexType에서 명명한다.

slot : 슬롯
- GPU에서 사용하는 상수 버퍼, 텍스처, 샘플러 등의 다양한 데이터를 받아와 식별하는데 사용하는 번호
- 각 slot은 고유한 번호를 지니며, 해당 데이터의 유형과 역할에 따라 다양한 slot이 존재한다.
- register 키워드와 함께 사용하며 뒤에 명시되는 번호는 프로그램에서 명시한 번호이다.

- 상수 버퍼 슬롯
- 상수 데이터를 지정하는데 사용되며, VS에서 사용 할 상수 버퍼와 PS에서 사용 할 상수 버퍼를 각각의 번호와 슬롯으로 넣을 수 있지만 데이터를 공유하는 것도 가능하다.
// VSBuffer 0번에 데이터를 집어넣어도 PSBuffer 0번에 데이터를 집어넣는 것은 가능하며 독자적 공간이 있음
// VSBuffer 0번에 집어넣은 데이터를 PixelShader에서 사용하는 것도 가능하다.
// 데이터를 공유 할 수 있다.
- 주로 정점이 아닌 데이터를 건내줄 때 사용된다.
- register(b#)을 사용하여 지정한다.
// # = 슬롯번호

- 텍스처 슬롯
- 이미지의 데이터를 저장하는데 사용
- register(t#)을 사용하여 지정한다.

- 샘플러 슬롯
- 이미지를 가공하는 법이 저장되는 슬롯
- register(s#)을 사용하여 지정한다.

cbuffer : 상수 버퍼 // constant buffer
- 쉐이더에서 사용할 수 있는 전역 변수를 저장하는데 사용
- CPU에서 정점이 아닌 데이터를 전달하는데 사용
- ShaderBuffer를 이용해 정해진 방식으로 전달해 줘야한다.
*/