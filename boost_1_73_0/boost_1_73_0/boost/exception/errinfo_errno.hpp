//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_F0EE17BE6C1211DE87FF459155D89593
#define BOOST_EXCEPTION_F0EE17BE6C1211DE87FF459155D89593

#include <boost/exception/info.hpp>
#include <errno.h>
#include <string.h>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#pragma warning(disable:4996)
#endif
#endif

namespace
boost
    {
    typedef error_info<struct errinfo_errno_,int> errinfo_errno;

    //Usage hint:
    //if( c_function(....)!=0 )
    //    BOOST_THROW_EXCEPTION(
    //        failure() <<
    //        errinfo_errno(errno) <<
    //        errinfo_api_function("c_function") );
    inline
    std::string
    to_string( errinfo_errno const & e )
        {
        std::ostringstream tmp;
        int v=e.value();
        tmp  << '[' << error_info_name(e) << "] = " << v << ", \"" << strerror(v) << "\"\n";
        return tmp.str();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* errinfo_errno.hpp
atKPvQgO4vjQ41iT3NiXDBQPzz/GLwPSzpzcTsrmHP8A3a3JV9BZzi4OvY/8duvp3c7TB7Cn2YPJR1DHXSEuEAJToSg2bqqD035AkMnlqFsThBLIK8LIodiJmNiLWONrpl4dfJ2qwrG/mRoXHBsumA4lxq8CxUpZNvLECu5j6mHuEdCVsrCgM/DyjUhMsVJcXVF/pNdBxvCb1Qqn6HldmQOvAPweU+wK5ZKoLiVMTK7ZArPQfIkWCjmyzlB4ja8JcyVdVW4LYGMtI7M7fHm1Fe4vrdhx3T+nw0njNmaJ1QvU9NKbEPiXwF4+KDXFE5DWlDeohznrDMCFq4pCsYdKU32tU3nrl4hiPrJe431sCbbrlRc/zq5dW3hfHcrpYNDth2wXrMeuUce9dIUbWy06wPXUYuma4cM6CKiS6JM0IsDF17cpABAcO/hINoFrQsBe9FnHaMVKl6ZYIH60kqX2m7lAcW5pB5M6wRAv1sEadrPvi5pahSXOJCZvmHsQxODQe1pBGzl12aKS/oLiYS2cmwZdgvDCfM8XeB6BZcXzbRtufaPUcpe6Es4HpJz72nPnLvQ0tZpGvsa1ut+5F4pyw13QBxF3dsfR3/OE9dUpRQK+5QvNmhrZRizfzncHeIndHakZDfmGjfdyhuPi
*/