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