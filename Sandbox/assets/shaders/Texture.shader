#type vertex
	#version 330 core
	
	layout(location = 0) in vec3 v_Position;
	layout(location = 1) in vec2 v_TexCoord;

	uniform mat4 oc_ViewProjection;
	uniform mat4 o_Transform;

	out vec2 a_TexCoord;

	void main()
	{
		a_TexCoord = v_TexCoord;
		gl_Position = oc_ViewProjection * o_Transform * vec4(v_Position, 1.0);	
	}
#type fragment
	#version 330 core
	
	layout(location = 0) out vec4 color;

	in vec2 a_TexCoord;
	
	uniform sampler2D u_Texture;

	void main()
	{
		color = texture(u_Texture, a_TexCoord);
	}