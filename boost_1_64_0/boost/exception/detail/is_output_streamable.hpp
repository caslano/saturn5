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
ZMYNwfb7kdDsehPRXGNGM5XQlDnDSNAvKMGlN0aQQAxEUDYhWLZHpLLxWx3LpP9s/l41ntz2BI1mflJeioPlkeVhsFzmwbd/gw138IZQ7DRsU3O1cAlhD72Bws4wCzv3NSHsAX7LaBjsWDlG8YILtDbJtLZJZt+C3oi/NeGfLvAvMuPvIPAHbggMEwgLzwx2uL5kMm5L0AME9GIz9LuvCuhUYu3+r2mAK8Ln7IQt4hANZ9HtHQ4tptovFSv3v+HPskic9qEYLlFZYgpbwII8+c+0IE8KDMLEziKxCyd2xcQ2IrEDJ+JCvpP64jUk5tPK8cQWfb2ZRIlVkMhlW7ys1psHIbkx67DI5xeLPiB7/tqXyJ7vgwWL5iRIyriSlPGhw2zPn8bKOPploYxZIf6VaUYymr741MLiaUlFVn9OexT6uu8rMQGnNujMok55K5y4/n9frSdv+ji4nsQcp/SCygGJr3LAnwouq9ZlymCvn3Q8SDVz6yG2VF/PNXPmATGIXNEMyR6SSzHjFvnLb8yXv3y0PCvwSm/e4LOAP3nUYu2acnQDojFsEc7XTmmE6/2srGOwwG0it5WfpT0cPmmF58QRp6zS+tLA08T7wYPI+zQz73PAtle9wCPNAvM6i21s/C6iUXwsaWGcCKdegSgD72hPfWM5yUqMJRm5L0Lui5j7aVuJ+6Ig97E0Qx2FGuVld8I9U9sJ97a3NMNkrL+UgFBtS+J5S55aXO72r1OZ/PDz5kNyzs4WuArc1YfBC5HKN4PyauH5Huz42TnrBaqix18L07wX74cqmgi9QeAwmvrXbSPO9scC43FIPItGYzqo9nuMifGxwdKCHD78hZusADyFD+woVdvuYPeDUTo/LxM/p4TjZ28F8HOgabCCCAFR8ETSC9dWXS/cEEb6JLe52d7OLT9ji25vR1iNcSYKy0+3mIXRnILnmqWZHmosqpzUz7XKeY8qx/FqmMrZuA8q5wm3tgTa+JquYEOntFOP/uYKd8QJxP6VMCxJc8BYj78JtOWfoFFVLRormlOD4uiFJnRkjevcacrCMbV6NrXxQIc6N6Lh/ZqAJkaAxEh/JYwYH+0FMaqiLG3sU20sThjil17jijgMtN5ibu5hrpPe3HxWoDd38VP6WQHCEt2MAg8Ot06H1jLxr+otc/+V7chVdbVTgoBlZSn8lpU7kFVCmmYOaXXpbCLq8osDYeryzj1Ql+uhALc0WVbDt/SG2FimqFqaa95pypLrxKvgwPFt60HKKlk5q/TKuXozVg5l1jGMX/SU3n6uwMKT3HjrJH/rdP72biL+1mn8wYB1N7g8B/qK2yZ8aQHtAnKRTiligpPG0IHBkfCdZjRec6N3eFlv9McuF41+qeBLDavNIgyrNQnzqXgfHs1DRv+nD8jRf6woSk8WdSHteG0/asfVZu0oehG0Y75TOSXcA5sPtGvy+81ZQJis8fiFwT+pYOZ+rYHmCzIpRCZPkLnKTKYlkmnrJCUcyCoVtIjk8aOPw6tDMJ9GmFuEw/zsC4B5Jw2deRbVHIiLiw0O6S8N1HkukicHH6jpR0szZJpPSzviVCcMGWVptMVeVOEldEby57iWTafkayv4QoFIHkLJF8lkn/EdjIEk6CromBQ0tTchSgTrBcG2wF90eFKpil++B5dZwmbjJJvN7I/JZuP8j7LZ/P/vv/cv8v7L+TrtvxKepf1X+b4w+69zaEnQYw/vv6ZzP/8He0cCHVWRnJkkMIQjgxBuMUAIgYCEQ4gKmmjEAaKMwmIUcaNyRAEJkEBQ7kswRlERQVHxgEXUXUSFEGRNhOXQVQFdPNcFJdkfxwsPRECzVV3dNf3//EkmAVz3yHvK/O4=
*/