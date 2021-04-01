/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_07172005_0726)
#define FUSION_AT_IMPL_07172005_0726

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Cons>
        struct cons_deref
        {
            typedef typename Cons::car_type type;
        };

        template <typename Cons, int I>
        struct cons_advance
        {
            typedef typename
                cons_advance<Cons, I-1>::type::cdr_type
            type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 0>
        {
            typedef Cons type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 1>
        {
            typedef typename Cons::cdr_type type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 2>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type type;
#endif
        };

        template <typename Cons>
        struct cons_advance<Cons, 3>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type _b;
            typedef typename _b::cdr_type type;
#endif
        };

        template <typename Cons>
        struct cons_advance<Cons, 4>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type _b;
            typedef typename _b::cdr_type _c;
            typedef typename _c::cdr_type type;
#endif
        };
    }

    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename detail::cons_deref<
                    typename detail::cons_advance<Sequence, N::value>::type>::type
                element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename detail::cref_result<element>::type
                      , typename detail::ref_result<element>::type
                    >::type
                type;

                template <typename Cons, int N2>
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Cons& s, mpl::int_<N2>)
                {
                    return call(s.cdr, mpl::int_<N2-1>());
                }

                template <typename Cons>
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Cons& s, mpl::int_<0>)
                {
                    return s.car;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, mpl::int_<N::value>());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
ZHLuIVL3h6+AXETZ4weLE6h1ACNwK2bc4tpnfDyXNOHsPiDfxBDBCSG86N8cp0XB6E+/sqhkGLNyyaiKD6AsAeoGnWvhqayljBch5GpB1JUYeVYoHNYs6irGy4eRp+0vlwX1T8wcqlz1NNWHrqZhNRm/Fh2qNYAV7OQlCNRxn7PLb+MNd8SCtDidYL4kT6zQWUL7PdXdTn6Jfa/kInNtskknJUxpw7z25+gLX+6dcpKZ4WJRdaqpkyE5qxyXVD5jZcGBE2e4Z40vJPE1LkLjSURilHpTO+n3AEbM9Qc5gEHJA0GwDul1uTtraiJSfrqDjEVKuh6uQ7gfImFJge70F44wJzsgEAU+L15MJtVpxqcGh6tUyqg8av/2sC+JdUt6SfBMH8Zweb9ND2Mxo4hi+5egLZ70r6sUo2mgwo0yE1HUH4YtS0GM5z8O6G/28esMfX/HDbFexjd6Op/k4TsjDghLBDMOCl7ZTsWmqBzc6i+h7g3fW9R9TwkwFTZ1d+oo7lm33JwygkqbsA8h7Ki4/9QPts7REzuV1rXRUuL2k7NKmBi5H/gXm93QjA==
*/