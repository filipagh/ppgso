#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

// Direction of light
uniform vec3 ViewPosition;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

in vec3 normal_V3;

in vec3 fragPos;


// The final color
out vec4 FragmentColor;

void main() {
  // Compute diffuse lighting
  float diffuse = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.15f);

  vec3 lightDir = normalize(LightDirection - fragPos);
  vec3 viewDir = normalize(ViewPosition - fragPos);
  vec3 reflectDir = reflect(-lightDir, normalize(normal_V3));

//  vec4 lightDir = vec4(normalize(LightDirection - fragPos),1.0f);
//  vec4 viewDir = vec4(normalize(ViewPosition - fragPos),1.0f);
//  vec4 reflectDir = reflect(-lightDir, normal);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);

  float finalLightIntensity = max(diffuse,spec);
  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * finalLightIntensity;
  FragmentColor.a = Transparency;
}
