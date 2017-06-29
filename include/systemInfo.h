// Copyright(c) 2016 - 2017 Costantino Grana, Federico Bolelli, Lorenzo Baraldi and Roberto Vezzani
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// *Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
//
// * Neither the name of YACCLAB nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once
//#include <iostream>
//#include <string>
//#include <algorithm>
#include "utilities.h"

#if _WIN32 || _WIN64 || WIN32 || __WIN32__ || __WINDOWS__ || __TOS_WIN__
#include <intrin.h>
#define NOMINMAX // Prevent <Windows.h> header file defines its own macros named max and min
#include <WINDOWS.h>
#include <lm.h>
#pragma comment(lib, "netapi32.lib")
#define WINDOWS
#elif  __gnu_linux__ || __linux__
#define LINUX
#include <sys/utsname.h>
#elif  __unix || __unix__
#define UNIX
#include <sys/utsname.h>
#elif __APPLE__ || __MACH__ || macintosh || Macintosh || (__APPLE__ && __MACH__)
#define APPLE
#endif

/*@brief Retrieve system information

Class that retrieves machine information like he cpu
brand name, the OS used, and the architecture employed.

*/
class systemInfo {
    std::string cpuBrand;
    std::string build;
    std::string os;
    std::pair<std::string, std::string> compiler; //first for compiler name, second for compiler version

public:
    systemInfo();

    // Return the brand and model of the CPU used
    static std::string getCpuBrand();

    // Return the architecture (x86 or x64) used
    static std::string getBuild();

    // Return the Operating System used
    static std::string getOs();

    // Return the compiler used (name and version)
    static std::pair<std::string, std::string> getCompiler();

    friend std::ostream& operator<< (std::ostream &out, const systemInfo &sInfo);

private:

#if  defined(WINDOWS)
    static std::string getWindowsCpuBrand();

    static bool GetWinMajorMinorVersion(DWORD& major, DWORD& minor);

    static std::string GetWindowsVersion();

#elif defined(LINUX) || defined(UNIX)
    static  std::string getLinuxCpuBrand();

#elif defined(APPLE)

    static std::string getAppleCpuBrand();

#endif
};