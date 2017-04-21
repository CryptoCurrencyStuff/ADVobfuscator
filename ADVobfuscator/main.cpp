//
//  main.cpp
//  ADVobfuscator
//
// Copyright (c) 2010-2016, Sebastien Andrivet
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

// To remove Boost assert messages
#if !defined(DEBUG) || DEBUG == 0
#define BOOST_DISABLE_ASSERTS
#endif

#if defined(__GNUC__)
// GCC O3 is doing very strange things that are sometimes wrong or that remove the obfuscation. So use O2.
#pragma GCC push_options
#pragma GCC optimize("O2")
#endif

#pragma warning(disable: 4503)

#define ADVLOG 0

#include <iostream>

#include "MetaRandom.h"
//#include "MetaString1.h"
//#include "MetaString2.h"
//#include "MetaString3.h"
#include "MetaString4.h"
#include "ObfuscatedCall.h"
#include "DetectDebugger.h"
#include "ObfuscatedCallWithPredicate.h"

using namespace std;
using namespace obfuscator;

#if 0
extern "C" char* __cxa_demangle(const char* mangled_name, char* buf, size_t* n, int* status) {
    if (status)
        *status = -1;

    return nullptr;
}
#endif

namespace boost {
void throw_exception(std::exception const&) {
}
}

#if 0

// Generate a sequence of random numbers [0..10) at runtime
void SampleMetaRandom()
{
    // Do not use a loop, it will not work (it will print 10 times the same number):
    // loops are executed at run-time,
    // we want to generate 10 different numbers are compile-time.
    cout << "Generate random numbers in range [0..10) at compile-time" << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
}

// First implementation of obfuscated string
void SampleEncrypted1()
{
    cout << "Encryption of string literals - version 1 - Fix algorithm, fix key, truncated" << endl;
    cout << OBFUSCATED1("Britney Spears") << endl;
    cout << OBFUSCATED1("Miley Cyrus") << endl;
    cout << OBFUSCATED1("Katy Perry") << endl;
}

// Second implementation of obfuscated string
void SampleEncrypted2()
{
    cout << "Encryption of string literals - version 2 - Fix algorithm, fix key, not truncated" << endl;
    cout << OBFUSCATED2("Britney Spears") << endl;
    cout << OBFUSCATED2("Miley Cyrus") << endl;
    cout << OBFUSCATED2("Katy Perry") << endl;

    cout << OB22("Test") << endl;
}

// Third implementation of obfuscated string
void SampleEncrypted3()
{
    cout << "Encryption of string literals - version 3 - Fix algorithm, random key" << endl;
    cout << OBFUSCATED3("Britney Spears")<< endl;
    cout << OBFUSCATED3("Miley Cyrus") << endl;
    cout << OBFUSCATED3("Katy Perry") << endl;
}

// Fourth and final implementation of obfuscated string
void SampleEncrypted4()
{
    cout << "Encryption of string literals - version 4 - Random algorithm, random key" << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
}
#endif

#define CAT(x, y) CAT_(x, y)
#define CAT_(x, y) x ## y

#define MK_NM(p) CAT(p,__COUNTER__)

#define OB_NM MK_NM(p)
namespace OB_NM {
    static const char abcd[5] = "abcd";
}

// Fourth implementation of obfuscated string
// Declaration and usage are separated
void SampleEncrypted4_differed()
{
    cout << "Encryption of string literals - version 4 - Separated declaration and usage" << '\n';

    auto mo = DEF_OBFUSCATED4("UnraveledVisage");
    auto bo = DEF_OBFUSCATED4("AbstractReflection");

    cout << mo.decrypt() << '\n' << 
        bo.decrypt() << ' ' << '\n';
}

void SampleFSM_obfun()
{
    //constexpr char w[] = "BadPerson";
    cout << OBFUSCATED4("DeterminedGaze") << '\n';
}

int SampleFSM_obfun_with_params(const char* text1, const char* text2)
{
    constexpr char o[] = "Oops I ";
    constexpr char i[] = " it ";

    cout << OBFUSCATED4(o) << text1 << OBFUSCATED4(i) << text2 << '\n';
    return 12345;
}

// Obfuscate function calls
void SampleFSM1()
{
    using namespace obfuscator::Machine1;

    cout << "Call a function with no parameters and no return value" << '\n';
    OB_CALL0(SampleFSM_obfun);

    constexpr char a[] = "again";
    constexpr char d[] = "did";

    cout << "Call a function with a parameter and return a value" << '\n';
    auto result = OB_CALL_RET(int, SampleFSM_obfun_with_params, OBFUSCATED4(d), OBFUSCATED4(a));
    cout << "Result: " << result << '\n';
}

void Sample_guarded_function()
{
    cout << OBFUSCATED4("PRISM") << '\n';
}

// Predicate
struct DetectDebugger { bool operator()() { return AmIBeingDebugged(); } };

// Obfuscate functions calls. Behaviour is dependent of a runtime value (debugger detected or not)
void SampleFSM2()
{
    cout << "Call a function without parameters and without returning a value" << '\n' <<
        "It will only be called if a debugger is NOT detected" << '\n';
    OB_CALL_P0(DetectDebugger, Sample_guarded_function);
}

// Entry point
int main(int, const char *[])
{
    //SampleMetaRandom();
    //SampleEncrypted1();
    //SampleEncrypted2();
    //SampleEncrypted3();
    //SampleEncrypted4();
    SampleEncrypted4_differed();
    SampleFSM1();
    SampleFSM2();

    return 0;
}

#if defined(__GNUC__)
#pragma GCC pop_options
#endif

