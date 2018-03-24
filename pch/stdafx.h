// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here

// ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

// Direct2D
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <wincodec.h>
using namespace D2D1;

// Bitmap
#include "D2DLoadBitmap.h"
#include "D2D_Operator.h"
using namespace D2DBitmap;

// Direct3D 11
#include <D3D11.h>
#include <d3dx11.h>
#include <mmsystem.h>
#include <math.h>
#include <d3dcompiler.h>
#include <D3DX10math.h>
#include <initguid.h>

//#include <xnamath.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::PackedVector;


// ------------------------ STL ----------------------------- //
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <functional>
#include <fstream>
#include <string>

using namespace std;

#include <filesystem>
using namespace experimental::filesystem;

#include "inlineFunctions.h"

// ------------------------ Screen ----------------------------- //
// 화면크기
#define FRAME_BUFFER_WIDTH		640
#define FRAME_BUFFER_HEIGHT		480

// ------------------------ Camera ----------------------------- //
//카메라 종류
#define FIRST_PERSON_CAMERA		0x01
#define SPACESHIP_CAMERA		0x02
#define THIRD_PERSON_CAMERA		0x03

// 종횡비
#define ASPECT_RATIO	(float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

// ----------------------- Shader Slot Number ------------------ //
//VS_SLOT 번호 지정(Constant Buffer)
#define VS_SLOT_CAMERA			0x00
#define VS_SLOT_WORLD_MATRIX	0x01
#define VS_SLOT_AABB			0x02
#define VS_SLOT_SKINNEDBONE		0x03

//PS_SLOT 번호 지정
#define PS_SLOT_LIGHT			0x00
#define PS_SLOT_MATERIAL		0x01

#define PS_SLOT_TEXTURE			0x00
#define PS_SLOT_SAMPLER_STATE	0x00

// ------------------------ 기타등등.. ------------------ //
#define PI								3.14159
#define RADAIN(X)						(PI / 180) * X
#define RANDOM_COLOR	XMFLOAT4( ((rand() * 0xFFFFFF) / RAND_MAX),((rand() * 0xFFFFFF) / RAND_MAX),((rand() * 0xFFFFFF) / RAND_MAX), 1.0f)


DEFINE_GUID(WKPDID_D3DDebugObjectName,
	0xa67e850a, 0xaa61, 0x4e0a, 0xbb, 0xf5, 0xac, 0xad, 0x32, 0xae, 0xf, 0xc);

#define ANIFRAMETIME	0.0333333f