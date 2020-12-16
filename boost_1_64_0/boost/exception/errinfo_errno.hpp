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
EHHKLxRXihRDlouUbb+JRgJXOMM4pOfyB+1kM/ALJFy819bTxqueBq4r8a25utt40d2+/dYy/VAJ6FQyVYC8bgtGQMszpZf1U9B4ttUepEvyh5638dG8DrZX6fuLG+ScBfydTpY2U2DQrlgRzpuevrXGkIHedHXdN9XXFsNQM5HUiHT1a7fXGFuMUWIBqsBF/YxWe15iLWI1XWLV/RmcU3lqa1C3fTS6YgaYEha3glMV/ID54/B09QqttOQVHjG/E0G0OjmjFSvjv87txq8PdZg7S3CrBkCqARA1RhtMqBbX/CedvuZKAFYvchYRsPEAbF1TMUKcA+GQG7y/XAokll0pkvso+atu1Ksx/ZQdmAiIZPbO8BlyWfTDRTjgzMAejL9y8RSwSCMydVtmCIS3zAgk3xADEiVQUrIx/iFwCprRMWVH/EOBdPWRa2qMFTOMzsWGcU1luvqXq2uMUz8K5bcVpaYCCMMYHMRzqxGEWCNsX4GA/F/qxuusACocUbQaxk70j+/s80dP6b+qPLpud1o8/mjnzt1gCjFXHyZbCFRDqIAXMtKcd4YYA4O24i6B4qCkCUQZYJ/Xb6uh5sGWQhr33qY15D1AxtSS+Iy6FTMKR8ljQ4nITE4eM0JEaESwLjptRmhREAORJci2M9//MDYxGCvPC81f4T4ntQ3KTfdT+egfg5H+n7obOvce33ZhVth7207MCvtE29HRi2YQVFQcuqurTgmQjWsWVDZ1pC32zekydpKiDXa+7ZAC6HXB1yQLxsuiK5Zhh0y+oliIK+F/OJIG/PzLf6yiOnuL8xNte8BCtDDUvwMAhs27zvAp6GENOtT05OxgrOw4azBUaDJVyPw4gEodlRU9SkbXU0lhKL7DUu0O4Jtb7NVWKToTQippLHXXrTaWuvRWjaXmutBcQ4kZJBazgqSbF0qSG9EmQFLZbbcbWom9EwHFKLBVUPbeKMAJQmPjvHc0CJJgGjWXSogJErsFU89pHwqQp6nIYAsUqaHcZaFo1X+Cs6EEMB+DRAD8Wm8W+EWg+AhzdYQgR7AQ4OrIondlKhiBpozOhjSnw9GZp3fd5MVSU79IhbT6KDos68PIhkSaLC7p6q+sYRYkPXXBVozbvFxAMfSaYFmx6JRfmmcfCazU/enmTxYg8Q89b+Wj+Qft9mX5B4GkA34NLqvHoKWLRrMzk8VN6Cl486/fPa4Qj7YpvdYUGc+wy6l49KUEMwTpCMfikDRO+GxVjj05AGz3afhYfynakvzCHW4vrtoKv6lB6xd4O+qn6yetWOqtFayfhEE/We5X+kk4KsZf6hTmHBS1vTAUbZnh9uYYlL3QRWPx89yymzfcmBnaZ6erX1kFQ/tfcP583UggHsAxCoPz+ioBh0b2pyEJDjaDDqEbynk0CKOOlBnVawT1ssu5EcoBardDfZvMeW9ifRE7Wr75UBCIhrn6IVMTi7JPUh4Y884LQr6adPUZINygvADoZAGjPZSufvCmGqOzrqitIl39XfFa1n4YyLMmJCvoPzJ5aly6evuXpfKjJ/j3TZQAEA/gmIPiqWe0EE+RA0A8dZ7aPXW0UNfKt3iugVeXdb7WmNP/7l1lrK7HjLYKXA3AQ2avuQJ9iD7ZqJy6moVt0az71a607mgUQn6ZQT3PPBF7XgP2vEXc8574h/CXqLJuaQibe6b7hnJXWKPT/SLzvYx6hHyePkS7p79fBkzRS/4jIaxCTHimYmTIbP/lruwLvULahV5zAbVBL/SiJzd9Gcm+UjuSFzMyEfOOFwiZkPIvaNTo1G9ufcyK63F2XO+dRriGNN/izcaQ0X/M5pTmI6TJgezIhsQ2WhIumRygwds8Y8eudHI=
*/