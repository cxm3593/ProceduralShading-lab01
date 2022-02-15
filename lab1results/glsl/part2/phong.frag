#version 150

// Phong shading fragment shader
//
// Uses shading information provided by the vertex shader
// to do Phong shading calculations.

// INCOMING DATA

// Light color
uniform vec4 lightColor;
//uniform vec4 ambientLight;

// Material properties
uniform vec4 objectColor;
uniform float smoothness;
uniform float metalness;
uniform float transparency;
//uniform float refraction;

// Vectors "attached" to vertex by vertex shader and interpolated

// Light position
in vec3 lPos;

// Vertex position (in clip space)
in vec3 vPos;

// Vertex normal
in vec3 vNorm;

// OUTGOING DATA
out vec4 fragColor;

// Fresnel Attenuation
float F(float x){
	float kf = 1.12;
	float numerator = (1 / pow((x - kf), 2) ) - ( 1 / pow(kf, 2));
	float denominator = (1 / pow((1 - kf), 2) ) - ( 1 / pow(kf, 2));
	float result = numerator / denominator;
	return result;
}

// Geometric attenuation
float G(float x){
	float kg = 1.01;
	float numerator = (1 / pow( (1-kg), 2)) - ( 1 / pow( (x-kg), 2 ) );
	float denominator = (1 / pow( (1-kg), 2)) - (1 / pow(kg, 2));
	float result = numerator / denominator;
	return result;
}

void main()
{
    // calculate lighting vectors
    vec3 L = normalize( lPos - vPos );
    vec3 N = normalize( vNorm );
    vec3 R = normalize( reflect(L, N) );
    vec3 V = normalize( -(vPos) );
	vec3 P = normalize( vPos ); // To uniform presentation in the formula
	vec3 H = R;

	// Collect material properties
	vec4 C = objectColor;
	float s = smoothness;
	float m = metalness;
	float t = transparency;
	//float n = refraction;

    // calculate components
	//// Component Qd:
	float d = (1 - m*s);
	float rd = (1 - pow(s, 3)) * (1 - t);
	vec4 Qd = dot(N, L) * d * rd * C;
	Qd = max(Qd, vec4(0.0, 0.0, 0.0, 0.0));

    //// Component Qs:
	// Qs = rs * Cs
	// rs:
	float alpha = dot(N, L);
	float gamma = dot(N, V);
	float h = 3 / (1 - s);
	float rn = (1 - t) - rd;
	float kj = 0.1;
	float j = F(alpha) * G(alpha) * G(gamma);
	float rj = min(1, rn + (rn + kj) * j); // kj = 0.1
	float rs = pow(-dot(R, V), h) * rj; // H = R

	// Cs
	vec4 C1 = lightColor;
	vec4 Cs = C1 + m * (1 - F(alpha)) * (C - C1);

	// Qs
	vec4 Qs = rs * Cs;
	Qs = max(Qs, vec4(0.0, 0.0, 0.0, 0.0));

	// Ir = I (Qd + Qs)
	//vec4 Ir = (Qd + Qs);
	vec4 Ir = Qd + Qs;

	// ambient

    fragColor = Ir + 0.2*rd*C;
}
