/**
 * @file    common.h
 * @brief   hftsdk 公共方法和定义
 */

#ifndef HFT_SDK_COMMON_H__
#define HFT_SDK_COMMON_H__

#include <stddef.h>

/* Version macros for compile-time API version detection */
#define HFT_VERSION_MAJOR 0
#define HFT_VERSION_MINOR 3
#define HFT_VERSION_PATCH 2
#define HFT_VERSION_STR "0.3.2"

#ifdef _WIN32
#ifdef HFT_USE_STATIC_LIBRARIE
#define HFT_API extern "C"
#else // HFT_USE_STATIC_LIBRARIE
#ifdef HFTSDK_EXPORTS
#define HFT_API extern "C" __declspec(dllexport)
#else // HFTSDK_EXPORTS
#define HFT_API extern "C" __declspec(dllimport)
#endif // HFTSDK_EXPORTS
#endif // HFT_USE_STATIC_LIBRARIE
#else
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define HFT_API extern "C" __global
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__INTEL_COMPILER)
#define HFT_API extern "C" __attribute__((visibility("default")))
#else
#define HFT_API extern "C"
#endif
#endif

#if defined(__osf__)
#include <inttypes.h>
#elif _MSC_VER && _MSC_VER < 1600
#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef short int16_t;
#endif
#ifndef int32_t
typedef int int32_t;
#endif
#ifndef int64_t
typedef long long int64_t;
#endif
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif
#ifndef uint64_t
typedef unsigned long long uint64_t;
#endif
#else
#include <stdint.h>
#endif  // _MSC_VER

// 字符字段长度定义
const int LEN_ID = 32;
const int LEN_SYMBOL = 32;
const int LEN_CURRENCY = 8;
const int LEN_COM_ID = 32;
const int LEN_HEDGE_FLAG = 8;
const int LEN_PLATE = 4;
const int LEN_ERR_MSG = 128;
const int LEN_ACCOUNT_ID = 64;
const int LEN_EXT_INFO = 128;

// hftsdk错误消息，Windows上输出gbk编码，Linux上输出utf8编码的错误消息
HFT_API const char* hft_strerror(int err);

// hftsdk错误消息，始终输出utf8编码的错误消息
HFT_API const char* hft_strerror_utf8(int err);

#endif  // HFT_SDK_COMMON_H__