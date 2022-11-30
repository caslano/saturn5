// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_JOB_WORKAROUND_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_JOB_WORKAROUND_HPP_

#include <boost/winapi/config.hpp>
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/dll.hpp>
#include <boost/winapi/overlapped.hpp>

#if defined( BOOST_USE_WINDOWS_H )
#include <windows.h>
#else
extern "C"
{
BOOST_SYMBOL_IMPORT ::boost::winapi::HANDLE_ BOOST_WINAPI_WINAPI_CC CreateIoCompletionPort(
        ::boost::winapi::HANDLE_    FileHandle,
        ::boost::winapi::HANDLE_    ExistingCompletionPort,
        ::boost::winapi::ULONG_PTR_ CompletionKey,
        ::boost::winapi::DWORD_     NumberOfConcurrentThreads
);

BOOST_SYMBOL_IMPORT ::boost::winapi::BOOL_ BOOST_WINAPI_WINAPI_CC GetQueuedCompletionStatus(
        ::boost::winapi::HANDLE_       CompletionPort,
        ::boost::winapi::LPDWORD_      lpNumberOfBytes,
        ::boost::winapi::ULONG_PTR_    *lpCompletionKey,
        _OVERLAPPED **lpOverlapped,
        ::boost::winapi::DWORD_        dwMilliseconds
);

}
#endif
namespace boost { namespace process { namespace detail { namespace windows { namespace workaround {

extern "C"
{

struct JOBOBJECT_ASSOCIATE_COMPLETION_PORT_
{
    ::boost::winapi::PVOID_  CompletionKey;
    ::boost::winapi::HANDLE_ CompletionPort;
};

constexpr static int JOB_OBJECT_MSG_END_OF_JOB_TIME_          = 1;
constexpr static int JOB_OBJECT_MSG_END_OF_PROCESS_TIME_      = 2;
constexpr static int JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT_     = 3;
constexpr static int JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO_      = 4;
constexpr static int JOB_OBJECT_MSG_NEW_PROCESS_              = 6;
constexpr static int JOB_OBJECT_MSG_EXIT_PROCESS_             = 7;
constexpr static int JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS_    = 8;
constexpr static int JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT_     = 9;
constexpr static int JOB_OBJECT_MSG_JOB_MEMORY_LIMIT_         = 10;
constexpr static int JOB_OBJECT_MSG_NOTIFICATION_LIMIT_       = 11;
constexpr static int JOB_OBJECT_MSG_JOB_CYCLE_TIME_LIMIT_     = 12;
constexpr static int JOB_OBJECT_MSG_SILO_TERMINATED_          = 13;

}

BOOST_FORCEINLINE ::boost::winapi::BOOL_  get_queued_completion_status(
        ::boost::winapi::HANDLE_       CompletionPort,
        ::boost::winapi::LPDWORD_      lpNumberOfBytes,
        ::boost::winapi::ULONG_PTR_    *lpCompletionKey,
        ::boost::winapi::LPOVERLAPPED_ *lpOverlapped,
        ::boost::winapi::DWORD_        dwMilliseconds)
{
    return ::GetQueuedCompletionStatus(
                CompletionPort,
                lpNumberOfBytes,
                lpCompletionKey,
                reinterpret_cast<::_OVERLAPPED**>(lpOverlapped),
                dwMilliseconds);
}

#if defined( BOOST_USE_WINDOWS_H )

constexpr auto static JobObjectExtendedLimitInformation_ = ::JobObjectExtendedLimitInformation;
constexpr auto static JobObjectAssociateCompletionPortInformation_ = ::JobObjectAssociateCompletionPortInformation;
constexpr auto static JobObjectBasicAccountingInformation_ = ::JobObjectBasicAccountingInformation;

using JOBOBJECT_BASIC_LIMIT_INFORMATION_ = ::JOBOBJECT_BASIC_LIMIT_INFORMATION;
using JOBOBJECTINFOCLASS_ = ::JOBOBJECTINFOCLASS;
using IO_COUNTERS_ = ::IO_COUNTERS;
using JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ = ::JOBOBJECT_EXTENDED_LIMIT_INFORMATION;
using JOBOBJECT_BASIC_ACCOUNTING_INFORMATION_ = ::JOBOBJECT_BASIC_ACCOUNTING_INFORMATION;

inline ::boost::winapi::BOOL_ query_information_job_object(
        ::boost::winapi::HANDLE_ hJob,
        JOBOBJECTINFOCLASS_ JobObjectInfoClass,
        void * lpJobObjectInfo,
        ::boost::winapi::DWORD_ cbJobObjectInfoLength,
        ::boost::winapi::DWORD_ *lpReturnLength)
{
    return ::QueryInformationJobObject(hJob, JobObjectInfoClass, lpJobObjectInfo, cbJobObjectInfoLength, lpReturnLength);
}

inline ::boost::winapi::BOOL_ set_information_job_object(
        ::boost::winapi::HANDLE_ hJob,
        JOBOBJECTINFOCLASS_ JobObjectInfoClass,
        void * lpJobObjectInfo,
        ::boost::winapi::DWORD_ cbJobObjectInfoLength)
{
    return ::SetInformationJobObject(hJob, JobObjectInfoClass, lpJobObjectInfo, cbJobObjectInfoLength);
}


#else

//this import workaround is to keep it a header-only library. and enums cannot be imported from the winapi.

extern "C"
{

typedef enum _JOBOBJECTINFOCLASS_
{
    JobObjectBasicAccountingInformation_ = 1,
    JobObjectBasicLimitInformation_,
    JobObjectBasicProcessIdList_,
    JobObjectBasicUIRestrictions_,
    JobObjectSecurityLimitInformation_,
    JobObjectEndOfJobTimeInformation_,
    JobObjectAssociateCompletionPortInformation_,
    JobObjectBasicAndIoAccountingInformation_,
    JobObjectExtendedLimitInformation_,
    JobObjectJobSetInformation_,
    JobObjectGroupInformation_,
    JobObjectNotificationLimitInformation_,
    JobObjectLimitViolationInformation_,
    JobObjectGroupInformationEx_,
    JobObjectCpuRateControlInformation_,
    JobObjectCompletionFilter_,
    JobObjectCompletionCounter_,
    JobObjectReserved1Information_ = 18,
    JobObjectReserved2Information_,
    JobObjectReserved3Information_,
    JobObjectReserved4Information_,
    JobObjectReserved5Information_,
    JobObjectReserved6Information_,
    JobObjectReserved7Information_,
    JobObjectReserved8Information_,
    MaxJobObjectInfoClass_
} JOBOBJECTINFOCLASS_;

typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION_
{
    ::boost::winapi::LARGE_INTEGER_ PerProcessUserTimeLimit;
    ::boost::winapi::LARGE_INTEGER_ PerJobUserTimeLimit;
    ::boost::winapi::DWORD_ LimitFlags;
    ::boost::winapi::SIZE_T_ MinimumWorkingSetSize;
    ::boost::winapi::SIZE_T_ MaximumWorkingSetSize;
    ::boost::winapi::DWORD_ ActiveProcessLimit;
    ::boost::winapi::ULONG_PTR_ Affinity;
    ::boost::winapi::DWORD_ PriorityClass;
    ::boost::winapi::DWORD_ SchedulingClass;
} JOBOBJECT_BASIC_LIMIT_INFORMATION_;


typedef struct _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION_ {
    ::boost::winapi::LARGE_INTEGER_ TotalUserTime;
    ::boost::winapi::LARGE_INTEGER_ TotalKernelTime;
    ::boost::winapi::LARGE_INTEGER_ ThisPeriodTotalUserTime;
    ::boost::winapi::LARGE_INTEGER_ ThisPeriodTotalKernelTime;
    ::boost::winapi::DWORD_         TotalPageFaultCount;
    ::boost::winapi::DWORD_         TotalProcesses;
    ::boost::winapi::DWORD_         ActiveProcesses;
    ::boost::winapi::DWORD_         TotalTerminatedProcesses;
} JOBOBJECT_BASIC_ACCOUNTING_INFORMATION_;

typedef struct _IO_COUNTERS_
{
    ::boost::winapi::ULONGLONG_ ReadOperationCount;
    ::boost::winapi::ULONGLONG_ WriteOperationCount;
    ::boost::winapi::ULONGLONG_ OtherOperationCount;
    ::boost::winapi::ULONGLONG_ ReadTransferCount;
    ::boost::winapi::ULONGLONG_ WriteTransferCount;
    ::boost::winapi::ULONGLONG_ OtherTransferCount;
} IO_COUNTERS_;


typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION_
{
    JOBOBJECT_BASIC_LIMIT_INFORMATION_ BasicLimitInformation;
    IO_COUNTERS_ IoInfo;
    ::boost::winapi::SIZE_T_ ProcessMemoryLimit;
    ::boost::winapi::SIZE_T_ JobMemoryLimit;
    ::boost::winapi::SIZE_T_ PeakProcessMemoryUsed;
    ::boost::winapi::SIZE_T_ PeakJobMemoryUsed;
} JOBOBJECT_EXTENDED_LIMIT_INFORMATION_;


/*BOOL WINAPI QueryInformationJobObject(
  _In_opt_  HANDLE             hJob,
  _In_      JOBOBJECTINFOCLASS JobObjectInfoClass,
  _Out_     LPVOID             lpJobObjectInfo,
  _In_      DWORD              cbJobObjectInfoLength,
  _Out_opt_ LPDWORD            lpReturnLength
);
 */
typedef ::boost::winapi::BOOL_ (BOOST_WINAPI_WINAPI_CC *query_information_job_object_p)(
        ::boost::winapi::HANDLE_,
        JOBOBJECTINFOCLASS_,
        void *,
        ::boost::winapi::DWORD_,
        ::boost::winapi::DWORD_ *);


inline ::boost::winapi::BOOL_ query_information_job_object(
        ::boost::winapi::HANDLE_ hJob,
        JOBOBJECTINFOCLASS_ JobObjectInfoClass,
        void *lpJobObjectInfo,
        ::boost::winapi::DWORD_ cbJobObjectInfoLength,
        ::boost::winapi::DWORD_ *lpReturnLength)
{
    static ::boost::winapi::HMODULE_ h = ::boost::winapi::get_module_handle(
            L"Kernel32.dll");
    static query_information_job_object_p f = reinterpret_cast<query_information_job_object_p>(::boost::winapi::get_proc_address(
            h, "QueryInformationJobObject"));

    return (*f)(hJob, JobObjectInfoClass, lpJobObjectInfo,
                cbJobObjectInfoLength, lpReturnLength);
}

/*BOOL WINAPI SetInformationJobObject(
  _In_ HANDLE             hJob,
  _In_ JOBOBJECTINFOCLASS JobObjectInfoClass,
  _In_ LPVOID             lpJobObjectInfo,
  _In_ DWORD              cbJobObjectInfoLength
);*/

typedef ::boost::winapi::BOOL_ (BOOST_WINAPI_WINAPI_CC *set_information_job_object_p)(
        ::boost::winapi::HANDLE_,
        JOBOBJECTINFOCLASS_,
        void *,
        ::boost::winapi::DWORD_);

}

inline ::boost::winapi::BOOL_ set_information_job_object(
        ::boost::winapi::HANDLE_ hJob,
        JOBOBJECTINFOCLASS_ JobObjectInfoClass,
        void *lpJobObjectInfo,
        ::boost::winapi::DWORD_ cbJobObjectInfoLength)
{
    static ::boost::winapi::HMODULE_ h = ::boost::winapi::get_module_handle(
            L"Kernel32.dll");
    static set_information_job_object_p f = reinterpret_cast<set_information_job_object_p>(::boost::winapi::get_proc_address(
            h, "SetInformationJobObject"));

    return (*f)(hJob, JobObjectInfoClass, lpJobObjectInfo,
                cbJobObjectInfoLength);
}

#endif

constexpr static ::boost::winapi::DWORD_ JOB_OBJECT_LIMIT_BREAKAWAY_OK_ = 0x00000800;

}}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_JOB_WORKAROUND_HPP_ */

/* job_workaround.hpp
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
*/