//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E48761AD92811DC9011477D56D89593
#define BOOST_EXCEPTION_7E48761AD92811DC9011477D56D89593

#include <boost/utility/enable_if.hpp>
#include <boost/exception/detail/is_output_streamable.hpp>
#include <sstream>

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
    template <class T,class U>
    std::string to_string( std::pair<T,U> const & );
    std::string to_string( std::exception const & );

    namespace
    to_string_detail
        {
        template <class T>
        typename disable_if<is_output_streamable<T>,char>::type to_string( T const & );
        using boost::to_string;

        template <class,bool IsOutputStreamable>
        struct has_to_string_impl;

        template <class T>
        struct
        has_to_string_impl<T,true>
            {
            enum e { value=1 };
            };

        template <class T>
        struct
        has_to_string_impl<T,false>
            {
            static T const & f();
            enum e { value=1!=sizeof(to_string(f())) };
            };
        }

    template <class T>
    inline
    typename enable_if<is_output_streamable<T>,std::string>::type
    to_string( T const & x )
        {
        std::ostringstream out;
        out << x;
        return out.str();
        }

    template <class T>
    struct
    has_to_string
        {
        enum e { value=to_string_detail::has_to_string_impl<T,is_output_streamable<T>::value>::value };
        };

    template <class T,class U>
    inline
    std::string
    to_string( std::pair<T,U> const & x )
        {
        return std::string("(") + to_string(x.first) + ',' + to_string(x.second) + ')';
        }

    inline
    std::string
    to_string( std::exception const & x )
        {
        return x.what();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string.hpp
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
*/