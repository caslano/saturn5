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
ITuQjQYtoVPUBaPvwkaWrDIrUoTCpltzpmr3Nix0KMqpbEFRzvdwaMqo6rdAId2z5RpNaDB6ps2ipFDG23UtNweKSOseqOpage6QFtQrJRLvQidK2lp9S8TgZc+ypfwnKbuNvQQpMCoY+SmE6QjWRDHlwpcwu4guM/jiJ4m/yJYQvQd/sdzjfQwX51gbDL22QG+aliqMogW2aTij5YHzX9rpjpddwOwymUdxlsdJ9HWZLeMAnsHo5Az+7IQp7OcjGHG2NpmHM+/ZmXeMAvOWU6J2uaLa5Bh/WE4KEdMLWPifAudH2NUTaFp5szN3LQvJQe8aai3S5SKK0zB1fmOi4F1J4Y1x0ddb/daxaIVE+X3PY/MFjmqsBI4F8YNXF7gUV9bT5LX1dR6ksySMszBaODExTAs65HxLeId1tqZcXpsKQR99YaD5oGP34DmOl6SOF8bWpXWXX2RZ7JibmYSoA+e0Ih3X3gN6qVVMB82xX5Z9l595p0+9Y6gw/1FDRZrOXfggumye2mpfpOnkAbj8JD/uXZ+g8R7U1in+b2m7A8U22M+t2dWhKVZcQTGF2EPYpgqMbIoojgmBiB02wmIRzDLQnRDYkkxceRBq7B5UFlJDgeRfUcuNxUN3Coth4IsUuiO8D66lfyO/Wplh
*/