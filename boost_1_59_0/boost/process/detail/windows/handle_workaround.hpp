// Copyright (c) 2018 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_HANDLE_WORKAROUND_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_HANDLE_WORKAROUND_HPP_

#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/dll.hpp>
#include <boost/winapi/access_rights.hpp>
//#define BOOST_USE_WINDOWS_H 1

#if defined( BOOST_USE_WINDOWS_H )
#include <winternl.h>
#endif


namespace boost { namespace process { namespace detail { namespace windows { namespace workaround
{


typedef struct _SYSTEM_HANDLE_ENTRY_
{
    ::boost::winapi::ULONG_ OwnerPid;
    ::boost::winapi::BYTE_ ObjectType;
    ::boost::winapi::BYTE_ HandleFlags;
    ::boost::winapi::USHORT_ HandleValue;
    ::boost::winapi::PVOID_ ObjectPointer;
    ::boost::winapi::ULONG_ AccessMask;
} SYSTEM_HANDLE_ENTRY_, *PSYSTEM_HANDLE_ENTRY_;

typedef struct _SYSTEM_HANDLE_INFORMATION_
{
    ::boost::winapi::ULONG_ Count;
    SYSTEM_HANDLE_ENTRY_ Handle[1];
} SYSTEM_HANDLE_INFORMATION_, *PSYSTEM_HANDLE_INFORMATION_;

#if defined( BOOST_USE_WINDOWS_H )

using UNICODE_STRING_  = ::UNICODE_STRING;
using GENERIC_MAPPING_ = ::GENERIC_MAPPING;
using OBJECT_INFORMATION_CLASS_ = ::OBJECT_INFORMATION_CLASS;

constexpr static OBJECT_INFORMATION_CLASS_  ObjectTypeInformation = ::OBJECT_INFORMATION_CLASS::ObjectTypeInformation;

typedef struct _OBJECT_TYPE_INFORMATION_ {
    UNICODE_STRING TypeName;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    UCHAR   TypeIndex;
    CHAR    ReservedByte;
    ULONG PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION_, *POBJECT_TYPE_INFORMATION_;

#else

typedef enum _OBJECT_INFORMATION_CLASS_
{
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation
} OBJECT_INFORMATION_CLASS_, *POBJECT_INFORMATION_CLASS_;

typedef struct _UNICODE_STRING_ {
    ::boost::winapi::USHORT_ Length;
    ::boost::winapi::USHORT_ MaximumLength;
    ::boost::winapi::LPWSTR_ Buffer;
} UNICODE_STRING_, *PUNICODE_STRING_;

typedef struct _GENERIC_MAPPING_ {
    ::boost::winapi::ACCESS_MASK_ GenericRead;
    ::boost::winapi::ACCESS_MASK_ GenericWrite;
    ::boost::winapi::ACCESS_MASK_ GenericExecute;
    ::boost::winapi::ACCESS_MASK_ GenericAll;
} GENERIC_MAPPING_;

#endif

typedef struct _OBJECT_BASIC_INFORMATION {
    ::boost::winapi::ULONG_  Attributes;
    ::boost::winapi::ACCESS_MASK_  GrantedAccess;
    ::boost::winapi::ULONG_  HandleCount;
    ::boost::winapi::ULONG_  PointerCount;
    ::boost::winapi::ULONG_  PagedPoolUsage;
    ::boost::winapi::ULONG_  NonPagedPoolUsage;
    ::boost::winapi::ULONG_  Reserved[3];
    ::boost::winapi::ULONG_  NameInformationLength;
    ::boost::winapi::ULONG_  TypeInformationLength;
    ::boost::winapi::ULONG_  SecurityDescriptorLength;
    ::boost::winapi::LARGE_INTEGER_  CreateTime;
} OBJECT_BASIC_INFORMATION_, *POBJECT_BASIC_INFORMATION_;

typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING_ Name;
} OBJECT_NAME_INFORMATION_, *POBJECT_NAME_INFORMATION_;


#if defined( BOOST_USE_WINDOWS_H )

extern "C"
{

using SYSTEM_INFORMATION_CLASS_  = ::SYSTEM_INFORMATION_CLASS;
constexpr static SYSTEM_INFORMATION_CLASS_  SystemHandleInformation_ = static_cast<SYSTEM_INFORMATION_CLASS_>(16);

inline ::boost::winapi::NTSTATUS_ nt_system_query_information(
        SYSTEM_INFORMATION_CLASS SystemInformationClass,
        void * SystemInformation,
        ::boost::winapi::ULONG_ SystemInformationLength,
        ::boost::winapi::PULONG_ ReturnLength)
{
    return ::NtQuerySystemInformation(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}

inline ::boost::winapi::NTSTATUS_ nt_query_object(
        ::boost::winapi::HANDLE_ Handle,
        OBJECT_INFORMATION_CLASS_ ObjectInformationClass,
        ::boost::winapi::PVOID_  ObjectInformation,
        ::boost::winapi::ULONG_  ObjectInformationLength,
        ::boost::winapi::PULONG_ ReturnLength
)
{
    return ::NtQueryObject(Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength);
}

}

#else

//this import workaround is to keep it a header-only library. and enums cannot be imported from the winapi.

extern "C"
{

typedef enum _SYSTEM_INFORMATION_CLASS_
{
    SystemBasicInformation_ = 0,
    SystemProcessorInformation_ = 1,
    SystemPerformanceInformation_ = 2,
    SystemTimeOfDayInformation_ = 3,
    SystemProcessInformation_ = 5,
    SystemProcessorPerformanceInformation_ = 8,
    SystemHandleInformation_ = 16,
    SystemPagefileInformation_ = 18,
    SystemInterruptInformation_ = 23,
    SystemExceptionInformation_ = 33,
    SystemRegistryQuotaInformation_ = 37,
    SystemLookasideInformation_ = 45
} SYSTEM_INFORMATION_CLASS_;


typedef struct _OBJECT_TYPE_INFORMATION_ {
    UNICODE_STRING_ TypeName;
    ::boost::winapi::ULONG_ TotalNumberOfObjects;
    ::boost::winapi::ULONG_ TotalNumberOfHandles;
    ::boost::winapi::ULONG_ TotalPagedPoolUsage;
    ::boost::winapi::ULONG_ TotalNonPagedPoolUsage;
    ::boost::winapi::ULONG_ TotalNamePoolUsage;
    ::boost::winapi::ULONG_ TotalHandleTableUsage;
    ::boost::winapi::ULONG_ HighWaterNumberOfObjects;
    ::boost::winapi::ULONG_ HighWaterNumberOfHandles;
    ::boost::winapi::ULONG_ HighWaterPagedPoolUsage;
    ::boost::winapi::ULONG_ HighWaterNonPagedPoolUsage;
    ::boost::winapi::ULONG_ HighWaterNamePoolUsage;
    ::boost::winapi::ULONG_ HighWaterHandleTableUsage;
    ::boost::winapi::ULONG_ InvalidAttributes;
    GENERIC_MAPPING_ GenericMapping;
    ::boost::winapi::ULONG_ ValidAccessMask;
    ::boost::winapi::BOOLEAN_ SecurityRequired;
    ::boost::winapi::BOOLEAN_ MaintainHandleCount;
    ::boost::winapi::UCHAR_   TypeIndex;
    ::boost::winapi::CHAR_    ReservedByte;
    ::boost::winapi::ULONG_ PoolType;
    ::boost::winapi::ULONG_ DefaultPagedPoolCharge;
    ::boost::winapi::ULONG_ DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION_, *POBJECT_TYPE_INFORMATION_;



/*
NTSTATUS NtQuerySystemInformation(
  IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
  OUT PVOID                   SystemInformation,
  IN ULONG                    SystemInformationLength,
  OUT PULONG                  ReturnLength
);
 */
typedef ::boost::winapi::NTSTATUS_ (*nt_system_query_information_p )(
        SYSTEM_INFORMATION_CLASS_,
        void *,
        ::boost::winapi::ULONG_,
        ::boost::winapi::PULONG_);
/*
NTSYSCALLAPI NTSTATUS NtQueryObject(
  HANDLE                   Handle,
  OBJECT_INFORMATION_CLASS ObjectInformationClass,
  PVOID                    ObjectInformation,
  ULONG                    ObjectInformationLength,
  PULONG                   ReturnLength
);
 */

typedef ::boost::winapi::NTSTATUS_ (*nt_query_object_p )(
        ::boost::winapi::HANDLE_,
        OBJECT_INFORMATION_CLASS_,
        void *,
        ::boost::winapi::ULONG_,
        ::boost::winapi::PULONG_);

}

inline ::boost::winapi::NTSTATUS_ nt_system_query_information(
        SYSTEM_INFORMATION_CLASS_ SystemInformationClass,
        void *SystemInformation,
        ::boost::winapi::ULONG_ SystemInformationLength,
        ::boost::winapi::PULONG_ ReturnLength)
{
    static ::boost::winapi::HMODULE_ h = ::boost::winapi::get_module_handle(L"Ntdll.dll");
    static nt_system_query_information_p f = reinterpret_cast<nt_system_query_information_p>(::boost::winapi::get_proc_address(h, "NtQuerySystemInformation"));

    return (*f)(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}


inline ::boost::winapi::BOOL_ nt_query_object(
        ::boost::winapi::HANDLE_ Handle,
        OBJECT_INFORMATION_CLASS_ ObjectInformationClass,
        void *ObjectInformation,
        ::boost::winapi::ULONG_ ObjectInformationLength,
        ::boost::winapi::PULONG_ ReturnLength)
{
    static ::boost::winapi::HMODULE_ h = ::boost::winapi::get_module_handle(L"Ntdll.dll");
    static nt_query_object_p f = reinterpret_cast<nt_query_object_p>(::boost::winapi::get_proc_address(h, "NtQueryObject"));

    return (*f)(Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength);
}

#endif

}}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_JOB_WORKAROUND_HPP_ */

/* handle_workaround.hpp
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
*/