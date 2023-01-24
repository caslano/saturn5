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
7WBV7r7YocJJVHMugn8lmSci8eV/COM4kttHZSC3XVJ+HhiS+ChbvFxtzJ8VqrDooGZuLx9kJHzi0/xVPTyyH5B9ekNK753dRvaJxkl1tkb26YaTgZq5QT7QSHyofhsQGi9jTIQazU1vNdMgrUV9fhpltelaDvZXwSE5p5CpqRosyf3URnNiOOSXD5Hzf+LD4/NuZIXqY/ZJciKcjprtY0sKr/KCkytroehnULSl/fNIeB4LxwTJQXl7stegKjR501HGOLM+FiRlXgL6bdOtHgTtZ6vNOU2tz6HnBtMBm2Q2F2Pbs9sgn5ZsxWlxPXrqs2/ovXYSA7VMMj+mojZrNzJXmvmh3nCk5905d1UoMftROFSq6MXLtrnFWQ9K5v4aKaZ0qr9UWG3D/zSS6Uy1ZWRvhM6IM5IZTph5GI6fqqmQTLVazettoTLzQK1N1z4J0HMUm9ofEcSN+dGSOUeLD+lai69nhkUbzXlAbdRBuIpECEfcOxC3oDc28OanvWy6YgPm8dxsVET/I4QKRrPPcq0GGZZfJXNirE034BnIkRVmqkWiK0DZTLWtSBOm2o6auStwIkmTJ0OjiFRUyCD/atOdShLKJSvlMpRy45Vyg71wmxotnDBE2/xELNtOKfuYUjZCKRuMEobSXcBuBEkoH5c/S63f3FrliRgwS2s0x8fGwZFj5kSV5ZVbNhvqat4+bKyyAYIhwJdkpAzw
*/