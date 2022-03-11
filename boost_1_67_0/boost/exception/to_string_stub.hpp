//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593
#define BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593

#include <boost/exception/to_string.hpp>
#include <boost/exception/detail/object_hex_dump.hpp>
#include <boost/assert.hpp>

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
        template <bool ToStringAvailable>
        struct
        to_string_dispatcher
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub )
                {
                return to_string(x);
                }
            };

        template <>
        struct
        to_string_dispatcher<false>
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub s )
                {
                return s(x);
                }

            template <class T>
            static
            std::string
            convert( T const & x, std::string s )
                {
                return s;
                }

            template <class T>
            static
            std::string
            convert( T const & x, char const * s )
                {
                BOOST_ASSERT(s!=0);
                return s;
                }
            };

        namespace
        to_string_dispatch
            {
            template <class T,class Stub>
            inline
            std::string
            dispatch( T const & x, Stub s )
                {
                return to_string_dispatcher<has_to_string<T>::value>::convert(x,s);
                }
            }

        template <class T>
        inline
        std::string
        string_stub_dump( T const & x )
            {
            return "[ " + exception_detail::object_hex_dump(x) + " ]";
            }
        }

    template <class T>
    inline
    std::string
    to_string_stub( T const & x )
        {
        return exception_detail::to_string_dispatch::dispatch(x,&exception_detail::string_stub_dump<T>);
        }

    template <class T,class Stub>
    inline
    std::string
    to_string_stub( T const & x, Stub s )
        {
        return exception_detail::to_string_dispatch::dispatch(x,s);
        }

    template <class T,class U,class Stub>
    inline
    std::string
    to_string_stub( std::pair<T,U> const & x, Stub s )
        {
        return std::string("(") + to_string_stub(x.first,s) + ',' + to_string_stub(x.second,s) + ')';
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string_stub.hpp
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
*/