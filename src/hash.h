/*
    Overview about hash-functions:
    - sdbm
    - djb2
    - xor8 (8 bits)
    - adler_32 (32 bits)
*/
#include <bits/stdc++.h>
#include "stdio.h"

Napi::String sdbm(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "An argument is needed")
          .ThrowAsJavaScriptException();
      //return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Argument must be a string").ThrowAsJavaScriptException();
    //  return env.Null();
    }
    string st = info[0].As<Napi::String>();

    int n = st.length();

    // declaring character array
    char s[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(s, st.c_str());

    long long hash = 0;
    int i = 0;
    while (s[i] != '\0')
    {
        hash = s[i] + (hash << 6) + (hash << 16) - hash;
        i++;
    }

    string hashWord = to_string(hash);

    Napi::String word = Napi::String::New(env, hashWord);
    return word;
}

// uint32_t arg2 = info[2].As<Napi::Number>().Uint32Value;


Napi::Value djb2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "An argument is needed")
          .ThrowAsJavaScriptException();
      //return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Argument must be a string").ThrowAsJavaScriptException();
    //  return env.Null();
    }
    string st = info[0].As<Napi::String>();

    int n = st.length();

    // declaring character array
    char s[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(s, st.c_str());

    long long hash = 5381;

    int i = 0;

    while (s[i] != '\0')
    {
        hash = ((hash << 5) + hash) + s[i];
        i++;
    }

    string hashWord = to_string(hash);

    Napi::String word = Napi::String::New(env, hashWord);
    return word;
}

Napi::Value xor8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "An argument is needed")
          .ThrowAsJavaScriptException();
      //return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Argument must be a string").ThrowAsJavaScriptException();
    //  return env.Null();
    }
    string st = info[0].As<Napi::String>();

    int n = st.length();

    // declaring character array
    char s[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(s, st.c_str());

    int hash = 0;

    int i = 0;

    while (s[i] != '\0')
    {
        hash = (hash + s[i]) & 0xff;
        i++;
    }
    string hashWord = to_string((((hash ^ 0xff) + 1) & 0xff));

    Napi::String word = Napi::String::New(env, hashWord);
    return word;

}

Napi::Value adler_32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "An argument is needed")
          .ThrowAsJavaScriptException();
      //return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Argument must be a string").ThrowAsJavaScriptException();
    //  return env.Null();
    }
    string st = info[0].As<Napi::String>();

    int n = st.length();

    // declaring character array
    char s[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(s, st.c_str());

    int a = 1;

    int b = 0;

    const int MODADLER = 65521;

    int i = 0;
    while (s[i] != '\0')
    {
        a = (a + s[i]) % MODADLER;
        b = (b + a) % MODADLER;
        i++;
    }

    string hashWord = to_string((b << 16) | a);

    Napi::String word = Napi::String::New(env, hashWord);

    return word;
}

#include <inttypes.h>

Napi::Value crc32(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "An argument is needed")
          .ThrowAsJavaScriptException();
      //return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Argument must be a string").ThrowAsJavaScriptException();
    //  return env.Null();
    }
    string st = info[0].As<Napi::String>();

    int n = st.length();

    // declaring character array
    char data[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(data, st.c_str());

    int i = 0;

    uint32_t crc = 0xffffffff;

    while(data[i] != '\0'){
        uint8_t byte = data[i];
        crc = crc ^ byte;
        for(int j = 8; j > 0; --j)
            crc = (crc >> 1) ^ (0xEDB88320 & ( -(crc & 1)));

        i++;
    }

    string hashWord = to_string(crc ^ 0xffffffff);

    Napi::String word = Napi::String::New(env, hashWord);

    return word;
}
