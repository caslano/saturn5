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
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
*/