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
xtdgQJz90ItDowcJnKxoJw4ocLu1FI8bIA3SwDXLiEGzWPF8Ek7jUez4vHB+YjyrmpzChSmgVWT5wbG5MoH2l3X1zBt4V6JWKpTM3po85/+nQlYSCe9Mxabgg19tSZfDeBCNpskonDhTgsdFOr+u3dATxdR16LYvlxRqwXBv/N7s24iMN1V1aGTHOEH1OHuJsdKUhKuCSt9xFsVo7yZ6JweLYopto5UN2cFa2mc7R5BnLTJRObtUwxoFaAPtQWCiBPujphm267MZN6fUWsjcVmfML8uZBnF8F0aXbTkGBp1IjVLu8uQCW5kL3c4prO0rpbWFMl2E3BApsCeBFEiM2U5LGDad00rM747gKpiNE2dZEf7VWjB9Eg7CcezcCqWtafgluJ2Oh1Y5rQ6siH/7TiWMM93DY2VFzxgP4G8Uw39EZAzP4sHFA3c7FekjwU6lfiZW/UIIf8m4i4Cvoli6OhyEqURGqhIrf392dHb0doRvIgZ3JRXOwvLtsdvDwti/1lTqTRsq8Y/qe45wuKIQVy1Bu9hZRQlv6u2rfxy/YJb64HMwGgcfR+NRMneCPG/Fd+ofn/vH1iEaJrNoAp+D8WzoRFTjaFa2umEa3gBrp3B74mbIqqauhcQm8Tqn2eRmEt5N0tC2oQlAUXk4
*/