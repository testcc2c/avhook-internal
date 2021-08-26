#include <d3d9.h>
#include "../imgui/imgui.h"

class MyDirect3D9Device : public IDirect3DDevice9
{
public:
	ImVec2 GetWindowSize()
	{
		D3DVIEWPORT9 view_port;
		this->GetViewport(&view_port);

		return ImVec2(view_port.Width, view_port.Height);
	}
};