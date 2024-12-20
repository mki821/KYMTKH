#pragma once

// 각종 include
#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<ctime>
#include<math.h>
#include<functional>
#include<format>
#include<random>

// My Header
#include "Define.h"
#include "Enums.h" 
#include "Vector2.h" 

// 각종 lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent 등 blt에 사용

#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

// 각종 using
using std::vector;
using std::map;
using std::wstring;

// 각종 define
#define PI 3.14159265f
#define Rad2Deg (180.0f / PI)
#define Deg2Rad (PI / 180.0f)

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define GAME_LEFT SCREEN_WIDTH / 4.0f
#define GAME_RIGHT SCREEN_WIDTH / 3.0f * 2.0f
#define GAME_CENTER (GAME_RIGHT - GAME_LEFT) / 2.0f + GAME_LEFT

// 디버깅용 콘솔창
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>
using std::cout;
using std::endl;
