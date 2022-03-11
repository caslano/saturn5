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