//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_898984B4076411DD973EDFA055D89593
#define BOOST_EXCEPTION_898984B4076411DD973EDFA055D89593

#include <ostream>

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
    to_string_detail
        {
        struct
        partial_ordering_helper1
            {
            template <class CharT,class Traits>
            partial_ordering_helper1( std::basic_ostream<CharT,Traits> & );
            };

        struct
        partial_ordering_helper2
            {
            template <class T>
            partial_ordering_helper2( T const & );
            };

        char operator<<( partial_ordering_helper1, partial_ordering_helper2 );

        template <class T,class CharT,class Traits>
        struct
        is_output_streamable_impl
            {
            static std::basic_ostream<CharT,Traits> & f();
            static T const & g();
            enum e { value=1!=(sizeof(f()<<g())) };
            };
        }

    template <class T, class CharT=char, class Traits=std::char_traits<CharT> >
    struct
    is_output_streamable
        {
        enum e { value=to_string_detail::is_output_streamable_impl<T,CharT,Traits>::value };
        };
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* is_output_streamable.hpp
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
*/