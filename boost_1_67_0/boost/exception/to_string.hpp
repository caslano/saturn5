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