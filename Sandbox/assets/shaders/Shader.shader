#type vertex
	#version 330 core
	
	layout(location = 0) in vec3 v_Position;

	uniform mat4 oc_ViewProjection;
	uniform mat4 o_Transform;

	void main()
	{
		gl_Position = oc_ViewProjection * o_Transform * vec4(v_Position, 1.0);	
	}

#type fragment
	#version 330 core
	
	layout(location = 0) out vec4 color;

	
	uniform vec4 u_Color;

	void main()
	{
		color = u_Color;
	}