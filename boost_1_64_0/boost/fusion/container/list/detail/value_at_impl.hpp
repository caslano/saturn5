/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_07172005_0952)
#define FUSION_VALUE_AT_IMPL_07172005_0952

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::eval_if<
                        mpl::bool_<N::value == 0>
                      , mpl::identity<typename Sequence::car_type>
                      , apply<typename Sequence::cdr_type, mpl::int_<N::value-1> >
                    >::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
4nhJANSr3kB5T5fwEXgP9Yuqh2bXVmRUlgS/eXBWJAEaVzBYwFe8rTz1xOWmUrd+eIldmY739ag2JpESK28fihbh/igCOu0rnEOu/MAeyIAPJororho7hwJMl8kiF0L0xl5Z/Hfl7Z6RhrWW+61KXq0jZZ62nrzMUbR767UGMjh1vQYV+780axrNUH5Zg+LoogQ6RCrWTTO01rs5vaRXq93EY6dcOMmhp3E8i3VBJSFMkYqbl0loWLRpJRX6yMoeKl2UPBaEa15DyvwUgTmSMBYh52lPyVU7oNZp3NM6vhtEGvX8IbBSyU1USDoA8Tb9DqJiC2xkuz+iaqcvtGzbMvK3fk/5Yhs3kC9JqkNl3UnwgwYoAfEbr6h6IDNUnqNWF5QWvL8g1u7mzP5yRald0TuJ4bx1RMX/p7MS7x5c3LlqrE1cpeVHELFhuqj6piJazPw1S8RalRpXmHI3h7eDzhBE4oYPJ2Z0XMwRgFw/5Ubhfs/GqpantTjp4mq+Ul7ZNHWadv8gOF8WFGcNEixaFgnE/58Qxba6JreyMKoG/JHryV49oD3D6CMo6A==
*/