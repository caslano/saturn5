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