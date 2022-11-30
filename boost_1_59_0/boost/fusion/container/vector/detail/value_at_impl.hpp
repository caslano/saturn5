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
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
*/