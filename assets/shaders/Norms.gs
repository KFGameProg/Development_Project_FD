#version 330 core
layout(triangles) in ;
layout(triangle_strip, max_vertices = 3) out ;

in vec3 posES[];
in vec2 uvES[];

out vec3 posGS;
out vec2 uvGS;

void main()
{
   for(int i = 0 ; i < 3; i++)
   {
	  gl_Position = gl_in[i].gl_Position;
      posGS = posES[i];
      uvGS = uvES[i];
      EmitVertex();	
   }

   EndPrimitive(); 
}