#pragma once

#ifdef DLL_EXPORT
#define SPP_DLL __declspec(dllexport)
#else
#define SPP_DLL __declspec(dllimport)
#endif