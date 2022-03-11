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
#include <Winternl.h>
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
__kernel_entry NTSTATUS NtQuerySystemInformation(
  IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
  OUT PVOID                   SystemInformation,
  IN ULONG                    SystemInformationLength,
  OUT PULONG                  ReturnLength
);
 */
typedef ::boost::winapi::NTSTATUS_ (__kernel_entry *nt_system_query_information_p )(
        SYSTEM_INFORMATION_CLASS_,
        void *,
        ::boost::winapi::ULONG_,
        ::boost::winapi::PULONG_);
/*
__kernel_entry NTSYSCALLAPI NTSTATUS NtQueryObject(
  HANDLE                   Handle,
  OBJECT_INFORMATION_CLASS ObjectInformationClass,
  PVOID                    ObjectInformation,
  ULONG                    ObjectInformationLength,
  PULONG                   ReturnLength
);
 */

typedef ::boost::winapi::NTSTATUS_ (__kernel_entry *nt_query_object_p )(
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
vk91iRiC4Lp7kRMmbPII5wq9o+YixPFsOWhftshgt8GtQWNbIwpxwQPrNmRGIEGt7e9cNIm4ynbaFNZvcIeMKFyvmjH8wuC/uQ1vFcMTqRCGAmLaZoIWFYokc/leRaonG0Jj5pTFojCtWByUH1zMhK1PAk7vIEQ+/0fMAFRZrYHxPtpl1kcR0AgalevP5fpDfDCpucqQX/5api1hYILXi3z8AKZ03SWM5cqjHI7plr/aBUDX9r20xEDFoq2XGFs7rv6cvsSzgDrk1vu7zLMcYfdE+yHLO4guq4/Ooz/34xjtu42VCa4vS6y3r5ewPkE2MEFzG4JiUay5oBxASeN9rBX4YvF5nBFf2kpnLiXvY8x01tta2gi+4V6jVPVNzqN+CR4KkJowoELgIRZYXGRu41bLNyJ8+SNc8vavqCmeAERVWxlkZ57ML4EP9EDjuabgueYiFfogsJ5/e5aXUpf82zqoJE9MqYK1iGg7xkxvEpeEs0aNoBFt4nFcdRRoZxNX7Kul7WxlZactnI+yELEP5rliQ2zbi16sTUn7EfoQQ9qQ03C+TTCdZfmpWdYE3fIR9Yi7HIIzSC5B9dac55T3US8TRbHTlv9S7XUp1T6WrJYqTQSWpRZgRJfTSzzDeBV/Bc+ZEV3J75h0I7roEsxshekXCF5BPBsElVoKCLCiXLhlxWqGgyheRua2rTx8+bQ8TV68gn/9vJw9z4RxrcpbkK2pqTljMI5v+fhvaRcmoBPWtqlvMvV1xfLVrgtUEqBonmlQYxbkEgheDjlp/zvoYOX3VOdizhrhSjHkO9V/6Yk/JDdPutz9P12pcO+7Oy+mwsZP4QyX1ywA8yEbAWZe6PjaZTtvtQmuKHfvZxyibRxwztVvXUgtdGTPQjf2KPTJHoU+0qPQb+1HysS5ELDxAXjPIEXpFNbMxOnXkEWnXzluSozf8Am/SZ6Zrk54OnhunwLxkXwiUudET4ZxZbhJpsP07dSF0dqqrwQran9J0FTbHMoJysmDe9sAt+T2Ab0JMmUxEEOGsXTQ7dq7IMtbKn9EUbNoh1LoCApNeP07Ey9PvlJcUNpxNlKFVrYHu7P9rRT6NfRSNePzm7FzkNWMr13WjF/BmrK+qZTOHmlcushIgc/sNGVhFtvSqBn/s4S4MAieqZPRdcJgwhMScj79lUy0Ir0rCDJ/WSFxkCBjKZZMEChwYpjGl02rLzEjJiHU/GIn0da1oYxZhrqEmLYob/8kYylsHRgsm2AULDQKZhhL13DIOv7dxL+b+ZfNwi9l2lNd4RSE61ltFSi8kjZVKkP1zGIGW7tbtwSXTqU0zQ35zFf55pJpOZTGKZ5FedW1CwOiYcmfcN245LwtC5dd9HcU/b2C/k6iv4PpL+0P/Zq3sU3jbhZBjKe/betts11jdphmn7q+3C0ukPFMJUS80JbcPQlhbK/oXyo6In9NK+XLMUIGXwCaLjTXbHXlX8pHL43ZP7Yxt8DLzBMa0lP8Hb5W8CAp2uubr/WyzaoY9oMs8I5lL3zNUoOoZH7N0jJV3Hm5tkdxR+QKVdwgKdb1Qmlu8y3kk/1QiKytvGj6FgZZqMpMGE0Vz2FKCDHtWyZrj9DW+hm+abPMmd02F/5kmBldlWMLZ0vtKHNZPVAjoFcsnNnm/XNB/97R66IZmlnzlztoD07pbwnTrZFpb+MqgXefJQSFeyOwytYUJThlisOzRn6F0krRP8keTVUfKtlywZTVEPVqErxiYCDUew3m9+rmPk1qIW90hAs32sN9os3hW36LuYv3ijbro0P59+Q15+33ecJfiRy4YnoR/tHIRlq71KI0b6GTB57fesUzk4FzEl49Ehso8jqCu6R5m5JRC3uVq7MrInwdkxbvx9/hXurbbgm4c7vskEzdszGNqIba2ywfaeF/0Gx2Sx1RDdTNbxPMUv27xk5gaqKNfohAYkUMpoRWLuYhZBnDpCwr7gJShFSTpeV8UWn2/31p4nnkh5jSud042cIuMa4ja4jXPoa+odeUKcadwfc8JwU4VQASXD/PNZtCXBwyCEmuD7pZocMnihbZveJ57Gx70Cmex1RdH3SJ55fxi1sYqHPJn9Bo2qVo9cSIrVd8vJXHiwKQUaV3JUr4vIzOSL6zl8VTybkwwCtv7Wexwtjo1MNhm7wS0mUrrF2QUSp/ewjfAE6R1/GLYGvHuwUDNrVPH72USZvq0e9BFDKouyJzg7ZI4V0JlsKLg2g1/7xfivfl0ryzxhhjnvO3AGQ+3R3O9OnesFMcgOyh4UqE6ImQQqcFPdQd08QayOV/XGFrtZBrFlzmt+Ty4NunP0AsIkVm2QsRxI/V9T1LgUy346JP/vq7IORiWgesulZ2Kre75iA3JYP3Jy6slaWhiUo/A2K8wwyGQe7vWRSiHo7Nwa2jaJJXjGEQnMWC7L98kxbdQVl6K1PBTh6NqRPwmgcm98IcpWsQlNJGKNm+8EiOUs6F/O+HB4kGefIqFuXtjbxxZ+RuGtNKAiDDMQCLZiTb1gUcSslJDwpjbHDXP1IU5Pg7w6PK4BDGchUstE6RP0Hdd0E7rA8FoGyeLSq58ioELLzL1Hsnx/Q92iZm4uq3BmPu01z6EK75PWRa1BdMi4xEEqhBdN95uEs97zaGbEV1kmasaLU4ZPQ3JjmVOGAYokxQxLPb4oO4I5Zkgi2dfZZcXZc6ecMul7cszjtLx16ogI59IoEpMw3m2cnZRJSAL4obXcTo7bTCDf2MoXdaDhI1KWgSC725erso78wt7xD5WUZAGtpp/+Hwfef4lOP9GwwW5fbFDqb2c3GDtlL71GUxC1LgMt/UT9N3ae44lbD081OJgBRU/p7wDKt8QINCMQ5Jg7npAApFQWW8yDxxWV5aczJ3OJJQcHHI9tkUSeHPksak8CcdsX//9ALL/PfqU9sGrd2zDAG94UwWy5x7tV3pvFh3avfDSGOnkvO4i6FheEBp7DlGSnax+eEnvvOpqc7bw/Krb1ww56Se38Pf4AN3hLzyFT5wByXP7btfST23ZyebZz9A0OUwZORlPrU07pKDbqCj0zET17ih8TVRYLFpva0TdKe88deE2mmNeSaWHnj0SU+ilS2WH1LwuRDXCgOLlVC4UHNuke4Xf0X7VDstAq1iOKi9FOrvPSa2qJaPNibSJGKpzPdwTrcWUTyf1eD2MzFP6S9sZH5mbSiLx1JJqaUmXpQ82HfK3ZsJFP4ms9uyiu4ui2lucR6tq09n4JFOmyY+NnqW9igVOC5r0BDYODTHOaE7pHtLQfDFJGM7kPpOJ3onnv4aYlPlqHFtDtzSFr5RHZosi89bTr+K3Q91Aw6vgvE4+uyml9WS3rx4wfzc0q76TGl9VW5IYLg47/weeXt4IIbOtO4upd2WcFF6mlEATzWdy7afQ4zRU30lc06LU70Gl8UKnEG1BZkOrDyDnVvZjs1LO2sJI6bHfKXDPC/t3ugMZxKekR45kBHvf047bVuHi8nIgd5xR+SAV9inh8xYSct0cyX8SIlAi//IonRxxAi0CK2V4Hm62GNoraLy9Ll6znmjKM2yF2T7jz6dJo4apVkUnIMC7QWu+F30sZg+poiSztzG6wu8RklH/BYKDFLg10Rptn1alr+RMjYapdkU7OWM05zxgfSRjwtCUXIm9+j109xGSbsoaXccFYEOR0PkVtsco+SMEei8N4w9H1S+iUvl+mbIw1sixo8cskSM1SgHe4hS4zqXRwXyZEbgtKHV/tzmweh+KQ2uiMW/Y5WbN2wQg9y0bugvfTZs2LDB0PYueWgvdcm2wShpCmeYgRozsFMhLYbWsuShFsZ0HPaSQzRISx5qZTjmuL7kuOKoZf9CsVsgUEl4ZqBVaSiLyS4aUJpKyDZpHWKyG3KyzzI1FGj314ULikIZQfntl3vZhC6V+s8Anu4FThB16ymCQhPG3UIZCFf4/LMvISo7Wvvdq+jg1CWMbQ1qb2TuSTsb/zx60eQYUVlLIGHJQ5KRt2wwc9iBrDgMngQ8t8q2Yxf5JqAl3B/Rhyl8visYlEcpnCDKkodO87kwpEdek/Kaeo3cdAzocKsN0tvIa1JeU99Jxb7AMXtt4W9HKqVNTPTSmIcHqxLKVOWoS4Y4XQuRo2VcMwJhepODT0NjM5HF5CyURN6cqHVAGdeIUBooOYK7Mme2T5OEqPIpZu+DnmWKvoyl3un0aafxxSjqnS6f1hp2vcbY6WS35eM140DqEoMEaLr8w+sXzHO8tLA9FB6KY77MHIe1ZI7j3o0QC91injP3bSCmwpZ7KfdCWcjh+KQ0UpsWjA8TC11W1BiR78y9EHLkXipDlOPEdBFwyV1HufUpUkuXL/Di0ryTRBW5CYHVNrMozQRqmG8tFgU7LH8b4KV8ZwpbvCXJLoec+jdi2k4FBNXJ0c4nB/joQP6McgtbsFZR3c9wKnTQkSC0dvrlzMwxFNrmc0sTwxErOaN0EkJps6aDU1dE0NoIbDW382K96UUs1mHAPO8xTRaXHyY8QtuZW2cEavzamUp7Ya525pXc3Uc7HXXxdNHL0GpEmVMw7W9ohxzamdiw3oZ2XEx15y5ltkB5Y+5uUVKTWycOGiUtomSno87QmoyS00aglY1nT8/bP6no8pZsfCHZErDY0JLh4m6n0GqtpnRyUzoTTckQU51oy92uXOZGiJdVixpFr9iwtNwDuQ2EODoOOrRGXD9otD1qAEW1WiNwHCMPCCTZhy+8OWubcYZshVS7ak7d870IXvA+9rxSJ+qSCE11PVagdZQo+fPf9wftKz9VOqGR86buB8FxlolVV3hEQo9RT9VtUjTrufi0JNEwCDh0vF8iW6av8C7mlX6NkD2WgTbmKf/PnJ0pWVcFrvK5dFoS3/43S8z2VBG9q4dMo1ItW32UMSMXJW6DmehiMccJaTfqh8LIcgxtp5615CIb2XAvuQgrGZ4oPDQuuQh4+4RrycVM+rvAE4vA72ykM9PzrI+iZedjUBLYK6ZmGdpWMTWbpiimbe0mWEKjabyhhfn9jzJtIoOVMA8VEbQCDbO1Xjs0hqrHOV7ZQeU0wLVUh3y1g6i5GjTG36QPOKdBZmFxOLNeq6UqbfERkYdqKSY8mGBUgpL6bqagVuTfRWVEKhtsix6JVNba9AdUV/SrUimIHmP4lU9MM/6INQf6yJQSF16BEgMN/sK7woUVo5ERMxc/YOoN3bRG/IbURmSg1vCVPWpLUDE83fAcH9hrTLqLqs5W/nwyLbUy/fZI5U5bOEeU77Q8T0AYg3Csa4iE+5ULwwyJoFYuyzLr4YGw4ooPCf/qZQmaJ0U8D+1NEfEsUgwcI9AVMXM9z+yj6nZApSxifm3BgIjpC/eNmNPCLv9FT5Q9btiF7o0FvEVUGOTCysyV2dwWAuSat41VVANdYlIYlKb/IlBC3V2cNPQf1+Uv+l00Vc5EoKF5qQ79HjHN9S7keWJlvf0HqMoj+lT/AX1ApGquTZ8opsHS21WLfbZ4NsXcYOF8+kgVkfFwxGfTr7BaFZoW76XwwDI5qPGCEivusVE/JGxeSei+S4/36vq8k3nHoL7dB2JOii3lPluXFu5F8NsRyr8n8qcuQ0n0vhf2gkHFGk40xlVfA30tV0BwrD58h1iBdvkPhjPlUyroZordBpdwnf6LCcdYiobRoV3+j4xEFDg7LDfOrF2CMbWWuWg6fifR1tpT0/DLBK9YzRoz3Vp/fMEsq9dcv3t12JK8s/KNi5mwbgv75/ee+3c+jU02UaSet7KefOTki3abPe89R4dR4vJ//ARRfcqskNNWs/JXSaMVBOBcecfqbZspyH/gaUeo9ywj6KzPd/WnjhlBtxH0GsEsy+S6xfZA0z+WcCcjKr1Gr7xj5xa4IGbvFQugm/clMfblOAyY+nvpHlOZXQ/7WBKjH1u2Pq30INywu35WrUv2kKx1gU8rXzaZo9lH5NPp7zbstKK71axTE34rmdDVMyFzR2HG/Sshb8KM+8LDF5UZd8exO2JTGs+kWnH3Jqy4mwVuCmDT7eG+8uQrymr71K+fNyP/Q82tZzM4ymYrrLV+3TfbteD6MthqnbA6PlDZWvcpW+u3/63TFLfRnLVN9s92PXEy7+QcaJmYP7hgzjJmO5Puk+UAapjymywda9miO+aibRWG1yJ56jMQJJeYKfafftAt66tGpqi0DAMT0zrZKPd5OQ13Y9DCneCb6oQ0Nny8H5HZ07qg5XeCb6pcokNoXTRDMHb8NRjsxdHbKdxLjH70aoxdMidW4GY2Ss0hrJqQs+Y3oIbFhcyEPdD2XymBJviX0r5st1nMtu/+lijMCbQ+aciKQrZIXVh+vRcUfOwWwbMYtxJJ8tNrbod/YbA83TgTXErVJML+hm2z9bRzTWws2qq/T6J+ue5DJbpB1au2yMe/RI1YgdLMyOsA2PSVo77ggthWvxRl4k3skz+8kJlsxMdsoCgxxDNevmyIGdlLuM8uW0MU0EwvLbBBm94f6PW81cGeo5b8FXSY1cMGGaemWGZ8aGn0ZsMjawmvwQLD5cC/LvESTip0X8Fzd6TYfIFNBmjuSE4P6zqp/Pc//Ah6Q+5CTzXOxRvQI0/179Rrmi18Q6EnWos+LkWnqZL+QfNJau3Wo0BCeCBU+W2syTp1pBhM+MD4YlaCYS2KYmoLzCfyIYdbAWPqGP9ajKs+ioiTpRja8IhgkJ1MJnkOvqljCdQtzeH0Y80nRzOvktnY8M0EW1rPdrfEsFrnqWYPjJq73jYA4DiTX3NsSiuJNzX7zfu4Z2Wn0ue9SauvPfvUjJFeelynho0Mymtp9A1uQfJm6mP5sLKLeDbfaQ9ffdZm10eojj3I9YczIgtzbJDkT3BKkprwbEImDiFRnHNDkS48qAJ20UKsHIhlTKf6iW7NfzYjhDJoG0w2GTlLCEM/d+8lU+4vJ1IJBhZcuKY5QCkS0XV/V4wyZ5/aeD/K/QbFKdv4hd3sqlv68CHURmunuxmMWaANe0K2mj9gi8iz2CIy9wFKXeiUv/81nLl4QamUu9T9T1lxYgBoqc69ym6reGZ0L29pxRg1xAbPtfL4bWGfzD0aKPsNo70991ymrZu3MuUyokg0E6UvP26DVgFhLL4tKMuzHHdEvi1YOZ7qX9nY5mULsFs4HdVbDf20AdEsEELCkcoxFZwf2BCaCzWY0opeA5TkjmJ1ORKR4s6cUFqspH16EUeuBLtcaze3YD3E9JZY5aENzGA4JIiGISRMOy5zXoMAXYMiCWpBDQxaBwZwYG+9tnf5P2gwHzh93pwDZEfbyeSAvkOhVTUL30ycpZFKt10fCim6fBdvt5C94n+c4Ga5VBNhisvyW02nbnQ/Y/npnrfsjm4LRDCIRHv7PIF3WDpyQfwqaBa5Wb8QSEPIVioLmpRcTk/YVAqDZeHsvGMP+7xhDw6u52n13P5wZLxN/1js7pE275hKfWW8r+et/Y6jSP0ApB3ecj1MDYtHdqel5iAa9ywBPp/ugo9Fl9wGYYd5cCdOMGwjNm5TzJkHdxS34ANM/6v5Qq4v2l8mddXgYoggOm8JyoesDtT3gG3K0Cr1/uLLymiEUvMEvsHbSHTipHWVJcfDg6hSeUViOFIVGNU4/toqKeym0QQUwmBmpaj+Z6elqv4rtclKN+tN6pTXkhU3B3UcB6K9cEppQiN/0KZjtK6UGQRX7CUIe08vi70EcfDpsZeQZjr2pWprIh19ucS+BGp+49spTI0iBpLN8quQFznm363s49wPzaFsGrbp081BjdyG76bLky/hlj+u0SqiQ3+haZR0+S8sGCDOPezoX0RUwitU2TTRoHd43vokVpAGd1U/Rv0BOIhwGfagPH2iewKSTVjSPsF5mSGEhDnLLCPKcrvasFCOwWLAsejeizCuHCQQs/0PXJrxTiMFwV9KfRRvMGeqxI2N6CHEnNRdX3oV2Qi8T6Zy9nKR2ZENDVDJjsQgvUxpj3MwoWYuVUmwPtpEf6be2MtrbGuht7yT5qAWSG9ioU2yZqTMHNTEAAos9dMDFL5OxNBYK1zOzCO0htvMhAvXYrjyTk4G0QRPLpGHXTam88UebO0fvoVpybamRcmh0mB8DB6g/NuGPjgtHGxQtovNbH1OqvrPT5WS4pf/q3LE56ZKquggybdVknRKAgyim0+VLCsI666UPKs+Y953srwWy5z21G2UVZUMm237CMvLSu5EeQP8rybt6ywYZQ7KgXjZYTmJIhT23nfRV4d4IaXAF7HeyDX4tpCpU5qr+Z9/bPuw9ezeKU/l0FdRS9/Fm7O8RafKXfRFx7Qcc3VvW4vumjWrfE+zLLeypS+jRC3lLmRM/17WqfSatoGJb7vuRMLmf1qJm/9JJTUdVUnTmlubpfqYpGec+uMHbeV7TjWdavo/ps069cfm2qa6lmtqxmR5m/Z/sP+Duv+aUzUpkdtLKZubaz/Y33LDSmo55Uwf/xKVc0xF9zt1snn/B39urqNi96ti/1uTmlWuK1Fk036rpv0fHPigrSV9XaL4M921D0A/kZTqH7daJeiuoKio+Z8tJS6VFKNOjafRT0dHk+EjTzUXtVS6ijAjtxPsOVXeac3PWPpqCXTOmrWfCrWW3tn0Tppj+6n0zT/N9ur9I335s7n21KAOeolnnErH38/0jFpIvfujqrHg1B9PpaOxLQeb97b0XT0ti9C4RvqmYfxz8/6mvzTv/eDQBwebf0eduqaBwj/Y23yQxqCu+UBLLY3knz7Y/cH55EhYhd5Ps7inpa9tNBWzxyp+f/OBD/7UvKfp4Af7m3/XdKD5dy19a1FcHRW/B1XXoFL6uxmhbR8caEYlB1v6bkT4gZa++VTBB7sR+sHHVGELNbz5VDNGN0EDusI3sscO54IhgsCVs9OXvSAT92JXfJ+Ih6n+KucTf4M7Dtf3mexzEeUHxx15tYbdmOQ2JnmNSVnGpGxj0jBjUo4xaZQxyWlMcln4xHdzbFXpYhLuwSaNyp3kLfS8OcktirIcmit6LJzp2X7HSM+bB3ogD5SDTrpsUeSNTfECzCJjNuX9L1lf20tTVirGbW1k6Nk7aJ6IXIMw22u12OCJIHzYZrelw8GgQgrKYBV+RsX9NgLetXTMFATxJ+9kcbE5DgXQkUVlRqpcOUSkM4ORDb+9dnrQEG/QHFfLSdYDrBQExcTleGnwvBlwVeTYDtk=
*/