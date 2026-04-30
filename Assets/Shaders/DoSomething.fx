struct VS_Input
{
	float3 Position : POSITION;
};

struct VS_Output
{
	float4 Position : SV_POSITION;
};

VS_Output VS(VS_Input input)
{
	VS_Output output;
	output.Position = float4(input.Position, 1.0f);
	return output;
}

float4 PS(VS_Output input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f); 
}