//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593
#define BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593

#include <boost/exception/detail/type_info.hpp>
#include <iomanip>
#include <ios>
#include <string>
#include <sstream>
#include <cstdlib>

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

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        inline
        std::string
        object_hex_dump( T const & x, std::size_t max_size=16 )
            {
            std::ostringstream s;
            s << "type: " << type_name<T>() << ", size: " << sizeof(T) << ", dump: ";
            std::size_t n=sizeof(T)>max_size?max_size:sizeof(T);
            s.fill('0');
            s.width(2);
            unsigned char const * b=reinterpret_cast<unsigned char const *>(&x);
            s << std::setw(2) << std::hex << (unsigned int)*b;
            for( unsigned char const * e=b+n; ++b!=e; )
                s << " " << std::setw(2) << std::hex << (unsigned int)*b;
            return s.str();
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* object_hex_dump.hpp
TlyF9fjqKcam2fnjn1FL4Jrw98CJjaYHdzr8E5Crl5pBx8m4WoxWOD92UxJdcuUQPI6qCzICTYJcXFq1cqEh/AC7qfIUb2BKZRCi/CpXJ1wEAZF7/p6ptQU4nMp7L2IGQ4nhQxdAGErH6bF8C2yus/2B9zgRKOAxioslh+3xgE2ahUggU5aGFo165KLSAz4WWxs1Wkp1MCbYW7Cra3Xyi3VIXzliSVGCAdRTPQNLIlew3u9geuyOvBS6tnXdD1V//XR0CseK+cZhNCfvBlZaphaS/5cOHw6LG0ATa8RvwfHEHEWZehu/+r/D3IYpEUFQaCJQi4HBdCtLByjY6uEszFIBxp2QW22nSAgDARPX1Rs/tveqEF4TfJ+hGFxVIlUoutiqAWGQMY4u/OkyRZMMecHFTFWA26velqukyihHFjaZI0bxT6+tHJMtE2jRmN4ivA1dpukjpuu4LQNH1daxBlUgzz8nfNJSQuEQ1oAoNJKW6XRlYbL0T7KGTC/ywmGkVnx2BG5A0nNy2T7Kaa35sSy0T+hjOLnFm0C74zl1Ki1K2dMFjzbpMzNqYg==
*/