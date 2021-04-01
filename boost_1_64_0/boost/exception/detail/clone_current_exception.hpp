//Copyright (c) 2006-2013 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085
#define BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

#ifdef BOOST_NO_EXCEPTIONS
#    error This header requires exception handling to be enabled.
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class clone_base;

#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
        int clone_current_exception_non_intrusive( clone_base const * & cloned );
#endif

        namespace
        clone_current_exception_result
            {
            int const success=0;
            int const bad_alloc=1;
            int const bad_exception=2;
            int const not_supported=3;
            }

        inline
        int
        clone_current_exception( clone_base const * & cloned )
            {
#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
            return clone_current_exception_non_intrusive(cloned);
#else
            return clone_current_exception_result::not_supported;
#endif
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* clone_current_exception.hpp
J9LmiZ1cfFvqjEhrO/SkPWJatlM/vA9HxIuxOx4eO5RrfRmWmaM8gI6ncyYmmebG/SaKZl8Oev2XIXx9me5NO/Y6Az40D5jQDPFteTF9aMliewkquv8XjlXBjY/2F3fPxPtHyrRgzjKDOch/06zyF3kvb1DvjBFXQadzDMOcwPisfTwBd89NnGkDR+Y9gZ2g8nH69OSNSZmTEQyBjNXPKGlJ4avFx5AfaXosAfZxr31bxV7Euanl5ek7F/Y/lNMjxg6g4ls7zyBPP808AeYNhSMn24v5t8hY1Gm9Xw4pHUqdg1cQVsUbyTG69aNh8LUPpD7Nn6r4oSU41ikjTXCDQrmcUzf4P8DHVO3+IEKv+bT26ZYGFt315gpL12uKS43qZpBHBwoo0+5DjUgIAkGLHPs6D2RcqGzqWQLFMRkXKPZhr3plh3nBG21568zKAVlOSlfxGdD8lqP/EFXmxR8YSnNfaXmSz3ZICF/yyV9fBHcvPj78wxjADp2w8qdJOaZKf0CSIlNZqPsLsTOy1iOJ820RR9T+KL3Euoh1AoT1bbbMEMqV82mmPDLEgw==
*/