/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07172005_0824)
#define FUSION_BEGIN_IMPL_07172005_0824

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<Sequence> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& t)
                {
                    return type(t);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
OdLnizRmVbse+uvXwwahV2tX09s40V8zcXhTOIhpkveWnc1WY7zl1m2c5Eb2qunz1q/eiVeQNHZH9mQQRzvX9qXT1/at6Vuz9ty+9ees6dvZJu/b6TWobSEv3B3F1aDxclJkghQu4VgwfrjiRe4YdZ+uN3m4E/Fg5DCnePHhzpimRDHfHPNJjfenKzWxzmHxycn8cCdBOGdqbOZw51UOnz/Ur8Odo14n9nL4KWrRy0EnjSBNEM/V8ChxgTXY+0s=
*/