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
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
*/