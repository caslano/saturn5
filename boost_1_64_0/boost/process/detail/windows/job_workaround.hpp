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
34ae+7bOim/T7KpFt4co51gx5JvLv1eZ/r3E9O93TP/OM/37kmxf6t6Lumd0FCcSIXbdvry8T94Sw7ErzsLuuAR74Arsh5uxtNX5u8kA/BID8QgG4XcYjBcxBK9iKPow8TCshGWwOoZjCyyLbbAcdsXy+ChGYF/sxXQHY2/MwkGYi3H4Mg7G13EIvoGJuAqH4juYhB9gMm7G4bgDU3A3puE+TMdD+CSex0z8GbPRSnmOQBuOQj8cjSVxLEbiOKyME7AhPoWNMYf/t8SJ2BqfwS44GbvhFOyDU3EA9sJknIFpOBMzsR+OxhicgE/gc9gfX8ABOBtfxLmYi2twFr6Hs/EjnIM7cC6ewflos7FvQh98HR/APGyJi7ELLsGeuAwH4wocjW9hLr6H83Ejvo8f4sf4Me7BbXgRd6C3nX0w+uNOrIXbsR6uxodxDbbGt7EnvoN9cA/2x32YiF9jsupOwf04Gg9gLh7GN/AILsejuA2P4w48iV/gt/g1FmABnsIL+B1ewb/gbfwJS7L9X8Qy+CuWxQNYG3/DB/AyPojXsDlex654A/vjOczE8zgBL+B0PI2v4hlcit/jWryN2/AO7kCLlXYO0Ip/Rg+8gDa8jnYMYHsvgY3QF1uhH8ZgSUzCCGQ/QbmocxvcrbrDCXan8leJfFashgFYHSthTayBtbAZ3o+PYG3shR0xBjthPHbGJOyCyVgHUzEKs7E+Po0NcCI2xGfxIZyFTfFlbIHLsSW+ja1xE7bFbdgOd6np8Jt9eUc2ikiKtf+j92L1u7PTyJdHbCD2EmeI60RAHO/cEq2IGCJyuo13N/8z79P+s+/S7iPOuHmXNpuY9j9+l7YVEfNfepf2v/Ue7X/qHdrC92cz4uz/lvdnNxA7/g/en/1/eHf2P/Xe7N28M1v4vmwO9Sov7t77r/f+/n1/dmLwf+z5f0bGv+PZfxj3Qdcy7MYPHJegI5JjUxOzk9IT5Fn7J2EW49uCatPoYLUwbpYHvy/HtuUhp139Ovd4sAGfsJAbbcY3HIZmpqca92eekbxBbu9nMR7Xb2ulk2x8n0H6N3P/XS4Pt9+D0N9GKmWT51Tk9eF3e6V5LuUheSvTT27fqLyBeEjGFSNfDG/MM9SOhCPvk7L82cyUcd9quOT9int8niqNr8/LtCJI8TAPJwVR+I2Ux2S4m3QXPnscyo0sY1mjpH8y46Rbj7OijNP0PQr9fHCc5G/HMoSrNJ46S1pDusNN08lmOsb9wXaSZ6KlJSmyjvS0bPrbGV0lj5/VcT/MbvnH98OaybB8qE51y7hUAQeZvwsn9cL1uztStHJvtYdMk/N+udc6SHV7WWyqf7rq/22ks3uxS/dO1f2d6j6guh8Nd3Z/p7q/V/1/dsl/2SW/p83ZXUXdGw5z6a7h0t1ede8LKPodGK5N5G894UG8S0yQdhOd76skJMTyYDNWf8BN7oXqb9gZ9W6o5L9fapmbbUmNz+r2u2QbpN8g1jn9jfc89LdNRjj601feP1Db1FNB8g7FcG7O6+etnFNK3anIkgxkz2P6jn+Re9C7JV9H3pvwUWl8J17S6pDCewI8v+Lal3cn1DferY/Ko7NaPDlz+9xM5c/2LPy2e1xx37nkXi/TJ8LVt9APFvONPX/C3Tf2Rutv7BX9ttgGL2dm0EZT+JF2WY/smWPjhwxJzMoi3difya7R/b18u8u3i9kf8LE+d/s6ndd1GSzulkFvWzJtSfPWz2RkGlJfZZyk/RBZ9FlGhI/x3aL7MAQnRbB/MpbT8c3OjHiW1FhO57fZKqr6FC15f7BGMcXHLW0tO1nnXa0vuysHxuv6/ZDhiYkZg5PTLe7Lgvy63DaHyf5N5kU=
*/