/*=============================================================================
    Copyright (c) 2014,2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VALUE_AT_IMPL_16122014_1641
#define FUSION_VALUE_AT_IMPL_16122014_1641

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/value_at_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace vector_detail
    {
        template <std::size_t I, typename T>
        struct store;

        template <std::size_t N, typename U>
        static inline BOOST_FUSION_GPU_ENABLED
        mpl::identity<U> value_at_impl(store<N, U> const volatile*);
    }

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    vector_detail::value_at_impl<N::value>(boost::declval<Sequence*>())
                ))
            {};
        };
    }
}}

#endif
#endif


/* value_at_impl.hpp
eeX0yvuz6sjVU3aBtSs+kXGK4+VwESDqyhRJ1uVSKuxuh/FlRwyXk4n0xHRvJZ7J/ZxOg46Z0jPiC8B6n6Ern8jZh9CzqOQbwx9iRRp/w4m36UoUOzxetaPfHKFDHe8VGLxfPFKR/hV5OycLTDaZaXAhBvsIbfsA/gRA9I0m7hByDuJwmOKi+WSl3qh7Ck3U7J7c5GRTV5ACruoOw1qkazhHK7We5mQZ01MTLQKAQYYM5xkIh7HDKel8QaMuKkEwhMMJI5AlZTguHzRG6SNBM1rAQYduImJK0SJQQS9GEgO5OR0da8YGWxFO8PgAIsPIrrrF8EIHaB8CwgB1FlSj3jl6VF+uUHXxRwuWXu+vntT9q+MCF05H2kjFkFUITngJugeJ6g2xPbVi56SG73DX3G9w0e6egiJoZ0LOrLrTrUyD2zDK/UGcXiumTlB3gTotnMZKACE0UaOMNTLpw0DRlnjzWlCQHWqhoLWet7sucZ+YWCJkYIHqozbde4N/NlYdMJYwPd7QRXxHRm5p384PcNH/qoItEPDxMNTjqonAv1HALzpjO1AOljGIqV/URKbuBAlrNl9XdeWddWj/CcdI4XonRsl8mODaH3ck+Gv5keeDPdmKnPGbSyAujrgSjdJSxqRaMQ90Dt5akrrC
*/