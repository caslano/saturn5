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
VDWnKd7XXSWb8mpff+9iTDcsajNxJyXKo4udo3kq8T6YDILRKoxlLfzK+T4V8dYNnhroW4tweYfqcDWEQPnZR3jsQkY3XGgSYSDNnVr7Z+lO/s9EFQit3W6hDsCD2F7wXeRxQkmDFpI+4M5gklIt6vCOpYor/kPNNDqRfgOGFju5sOd7XpZf0zzGmPBN2OwXmbOP4cfkW+EHqdyAiDrUp2qG5wSATYoUWb05eWO806DcaGCu3s6ufjAFV3HQQYUsLdveGTgd924I7WtcpR4r8V0D+b1APi1TcJ7CoBsD+B+LL25UytfcF5ojKWfvzMnL9HARFKxGuIBg08f5Z7K07qwr4izXc8olWXuUd4SuLfj9AiuLTzo1hj1L04BiUOl7tY86DA8dgcXE0sVPrMi8C/9biKczAMhT/SzrkVGoFukFL/6vLyhoLrrSiB6x34t7aONPpPoyWjjBhILgTiKfwlNDcRgOegtTt3cHmR1O4xiuMfAg3h8mgQxwnkGhFFMAFQkaCJRpxBli5NsrmYqJ1N7ycApYWVpU0UjmErW1zV0JUbpaJmV+Oz6vHw==
*/