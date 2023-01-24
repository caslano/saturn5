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
XU+0WdXXWBAv4M6+ql24uzuCw1038u6UnHK8OZwoKevlKHklNOpG7eHrIzoCYVs/013n5eohrPkKXR9RVsZwVYIKZ8BLPL1SE0xmwknshK+4bEc3PSeRKp/NlHdCB63ppxDKdkoQOvd9YhI1iFmhh5gM4QVHBzE7QxBiah20nDYOMa3iwgQgJsN1Q6Z7p75qn3o4RLSpgkHEVIKBy1GhCAbxa1fBYmSoHIoPi4GSyHn1ZtVUiYu1FgtzJctUWPqR1+LSD7+2ja6OtvbO0nbX/t6uF1j7F9W1T+/akbX/oC7Y2v962QXXflNJ+2tf1cV/7V/0X/sX//Lah3Z07V/879f+d2NH1t5Ve6G1H301rn3G1fq196E3E4rbXfv5xkD05hY2POBpvebbjSQWFuRlmLEjALDj02Dk5Zf+0NN2eJm/PdQ+L7O7cwBeJsVO/e0oO/MnsjMvL0eUfUD5W4ofR3Pt4L/K0YT9NY7mssH/BUfzeid/jmZTJx+Oxt2pIxxNzIELcDTfX4kA9vWVun3rA18nlrcLXz06BYMvCqwT0skXvr4I7wh8Td0fDL7W9LsAfFmWtw9fM8ODwFfZX4evMg5flkF+8FU78K/CV7e/Bl8fD/wv4MsR5g9fGWE+8HVlWEfg6919F4CvlVcgfD14RTC+5ZFl7cLXO6EXoF0VKu16MLQjoGXYF4x2pVxyQdr13dL2aVdYqD/tqkDa
*/