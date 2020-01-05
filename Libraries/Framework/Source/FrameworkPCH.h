#ifndef __FrameworkPCH_H__
#define __FrameworkPCH_H__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

#include <map>
#include <vector>
#include <queue>

#include <GL/GL.h>
#include "GL/glext.h"
#include "GL/wglext.h"

#include "GL/GLExtensions.h"
#include "GL/WGLExtensions.h"

#include "../Libraries/LodePNG/lodepng.h"
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/cJSON/cJSON.h"

#include "Utility/MyMemory.h"

#include "ImGuiManager/ImGuiManager.h"

#include "Utility/Helpers.h"
#include "Utility/ShaderProgram.h"

#include "Math/Vector.h"
#include "Math/AABB.h"

#include "Events/EventManager.h"
#include "Events/Event.h"
#include "Events/InputEvent.h"
#include "Events/GameEvent.h"

#include "Framework.h"
#include "GameCore.h"

#endif //__FrameworkPCH_H__
