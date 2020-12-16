//  Boost cerrno.hpp header  -------------------------------------------------//

//  Copyright Beman Dawes 2005.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

#ifndef BOOST_SYSTEM_CERRNO_HPP
#define BOOST_SYSTEM_CERRNO_HPP

#include <cerrno>

//  supply errno values likely to be missing, particularly on Windows

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 9901
#endif

#ifndef EADDRINUSE
#define EADDRINUSE 9902
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL 9903
#endif

#ifndef EISCONN
#define EISCONN 9904
#endif

#ifndef EBADMSG
#define EBADMSG 9905
#endif

#ifndef ECONNABORTED
#define ECONNABORTED 9906
#endif

#ifndef EALREADY
#define EALREADY 9907
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED 9908
#endif

#ifndef ECONNRESET
#define ECONNRESET 9909
#endif

#ifndef EDESTADDRREQ
#define EDESTADDRREQ 9910
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH 9911
#endif

#ifndef EIDRM
#define EIDRM 9912
#endif

#ifndef EMSGSIZE
#define EMSGSIZE 9913
#endif

#ifndef ENETDOWN
#define ENETDOWN 9914
#endif

#ifndef ENETRESET
#define ENETRESET 9915
#endif

#ifndef ENETUNREACH
#define ENETUNREACH 9916
#endif

#ifndef ENOBUFS
#define ENOBUFS 9917
#endif

#ifndef ENOLINK
#define ENOLINK 9918
#endif

#ifndef ENODATA
#define ENODATA 9919
#endif

#ifndef ENOMSG
#define ENOMSG 9920
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT 9921
#endif

#ifndef ENOSR
#define ENOSR 9922
#endif

#ifndef ENOTSOCK
#define ENOTSOCK 9923
#endif

#ifndef ENOSTR
#define ENOSTR 9924
#endif

#ifndef ENOTCONN
#define ENOTCONN 9925
#endif

#ifndef ENOTSUP
#define ENOTSUP 9926
#endif

#ifndef ECANCELED
#define ECANCELED 9927
#endif

#ifndef EINPROGRESS
#define EINPROGRESS 9928
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP 9929
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK 9930
#endif

#ifndef EOWNERDEAD
#define EOWNERDEAD  9931
#endif

#ifndef EPROTO
#define EPROTO 9932
#endif

#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT 9933
#endif

#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE 9934
#endif

#ifndef ETIME
#define ETIME 9935
#endif

#ifndef ETXTBSY
#define ETXTBSY 9936
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT 9938
#endif

#ifndef ELOOP
#define ELOOP 9939
#endif

#ifndef EOVERFLOW
#define EOVERFLOW 9940
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE 9941
#endif

#ifndef ENOSYS
#define ENOSYS 9942
#endif

#ifndef EINVAL
#define EINVAL 9943
#endif

#ifndef ERANGE
#define ERANGE 9944
#endif

#ifndef EILSEQ
#define EILSEQ 9945
#endif

//  Windows Mobile doesn't appear to define these:

#ifndef E2BIG
#define E2BIG 9946
#endif

#ifndef EDOM
#define EDOM 9947
#endif

#ifndef EFAULT
#define EFAULT 9948
#endif

#ifndef EBADF
#define EBADF 9949
#endif

#ifndef EPIPE
#define EPIPE 9950
#endif

#ifndef EXDEV
#define EXDEV 9951
#endif

#ifndef EBUSY
#define EBUSY 9952
#endif

#ifndef ENOTEMPTY
#define ENOTEMPTY 9953
#endif

#ifndef ENOEXEC
#define ENOEXEC 9954
#endif

#ifndef EEXIST
#define EEXIST 9955
#endif

#ifndef EFBIG
#define EFBIG 9956
#endif

#ifndef ENAMETOOLONG
#define ENAMETOOLONG 9957
#endif

#ifndef ENOTTY
#define ENOTTY 9958
#endif

#ifndef EINTR
#define EINTR 9959
#endif

#ifndef ESPIPE
#define ESPIPE 9960
#endif

#ifndef EIO
#define EIO 9961
#endif

#ifndef EISDIR
#define EISDIR 9962
#endif

#ifndef ECHILD
#define ECHILD 9963
#endif

#ifndef ENOLCK
#define ENOLCK 9964
#endif

#ifndef ENOSPC
#define ENOSPC 9965
#endif

#ifndef ENXIO
#define ENXIO 9966
#endif

#ifndef ENODEV
#define ENODEV 9967
#endif

#ifndef ENOENT
#define ENOENT 9968
#endif

#ifndef ESRCH
#define ESRCH 9969
#endif

#ifndef ENOTDIR
#define ENOTDIR 9970
#endif

#ifndef ENOMEM
#define ENOMEM 9971
#endif

#ifndef EPERM
#define EPERM 9972
#endif

#ifndef EACCES
#define EACCES 9973
#endif

#ifndef EROFS
#define EROFS 9974
#endif

#ifndef EDEADLK
#define EDEADLK 9975
#endif

#ifndef EAGAIN
#define EAGAIN 9976
#endif

#ifndef ENFILE
#define ENFILE 9977
#endif

#ifndef EMFILE
#define EMFILE 9978
#endif

#ifndef EMLINK
#define EMLINK 9979
#endif

#endif // include guard

/* cerrno.hpp
Mho2oCDatwdxE1LCfrmmQgSLC3bGYtGeWA8up0xSP+M8tuPW+HlsVTz2ghGvekimrVsoSmb0vr20THurTVFPYN9TkeEOt3AzrK+1Qs/Dq/MBYkT7vmOYuvwObAPTvQgt/bxqA+6BsMwqgSdFybWKeouDsaR38CsDpKAmPHAdPiHuROppAFn8/ZaE25gCBY5AAfW5hm5jW4rbmHwc9aoPVDi4emuB5jgj4jwh4lAonqJ9cK44RaP0mPAcXOokbvLeHEj9NrLH9otQJXSLQ+3l19KPIF+9xlkLXvBm9DUDYhH+B6/yosidGdhCTbCLH6ZNcPD8SZ2QzbU87JjLrWauMG6hrbwfbV95d6YSq4+FK4ssFQel2rZhjRPtOdxSZiBit1yHyPf6v4ni979S3PIb3c3iUOZuuKruxgvO8afWzGSzd/vGD2f6u7f71RIo+1P1sEfd7lFfk4PHsqWlm7mSwYYRwQAejHvGNJ+6QTn69hKsoHin86i0ynpZwdje0oMruVyJYebYM5Vge/b892XpZQv+Zqd78WFbtPbgCVz5Llr73MhYTMuuREmxVctW+J2mDQhp2aVM2pH0andOtaCKdmfAEjyRJT0YADQLe/EagUMAiDOz/BijK2j4RWvaTnAb/6JrJR7j2BkebbQAd8QzemuhdixdPNpYkZ2JbK/m8kPOvvNvw6G2kq3JG8b2vverSJf20UqYDkgvR7TRldLLddoqNtZGz0F9af4VcuV9fUdUjAho0/vqh3vMXnCerF3b16cpklAK2veRY5FYHbQiF22av6/yRaGzG3A9sews3lKkP4gvf9laRfJCbwMX4Ymbl1JU8D6Xa/GEsLC/RrVHMAf8Iaz0PRiMhV7tYYoLl1ngCd3qyvOIaBKO8hSFGsD6F1sIqobRCfrikvWpeuFeZso33XIzZonM9+Q4Ma9El5xhB49zdBs1/mHn+jmQPr6vyI5vSZq9YJMD/JMdHbHu92fQjjMetI9liabu7fAzLs5R7tC4HagrHFJ+1qOLPjOmczhWX1loqfhQqj08jAB5YkPJfb+7OXqhUzg5N0+Izsb6GMdN1NsFuMdB9tD49E8sRxCnyrkhZozmM8Mfc848asPnWFN8TgQ+Z0zc55wSpzge3W262MHv2nMgbbmDauPu0K/eAPVw28jR5T4ggrz6jh9DabqfUvvLvsBVGN757+gjLa2CRHiX36+N++NL2O9s4Q9HXky3kB39/QacFfaqOJueYchl+WNH3ttXkV4O+6Sn10iLN6OWKBhbIC0tAtDYMdIjbnzjcll6uclX9Kb0iMuaUmdwvI6Eb6Bo2aFgfZpHn7doMwHuQjQ6COCJRUu/VHzdYLz+uiv+NJtPj7BTGmkCGbu32FcWlvGy/IseqwXbk9guWZMP3NF0a2jSgFaXx4rP85ATC010tg70hCZlt0r4dLT2xqe91eYJSTJO4fE6NcAypKVO+PXWDKKnhUYqZfUllWNzRlQUxerloncX3oQMdbM4zq/8tGD+Nbwvp5o+HbNwIN5CWehEkT/HKsYZKjzwftHm8uFoE29xQ0UfgVMsLVurrm3tp8lbVp4oH1GFV2PfBwyPBWgcFWaKL4S46+f+n1fgubpxg+u4Imanl8NQOD6P1Wvj7TJ6f8VfVl+bgaKArR4OzqH7ul974fesHunlt6AFZiyX4fHGa9lPxLVOlXuLlj6ua/peyM8nXdO344m6GIo3BDIqentv3+jsy+NAPDoqMuQ7ImM9tg0woC8YToP1kN17fpW3ehPmj/S7N92bMH+8al3UhiNo7kaHAC4hf0tfPD0qjbdazsHf+fi7FH8F+LsSf2PHW/9n/lP15H6Mr2Uld2PjM4wTSI8=
*/