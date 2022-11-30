/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_14122014_0102
#define FUSION_TUPLE_14122014_0102

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/core/enable_if.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <boost/fusion/support/detail/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <utility>

namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple
        : vector_detail::vector_data<
              typename detail::make_index_sequence<sizeof...(T)>::type
            , T...
          >
    {
        typedef vector_detail::vector_data<
            typename detail::make_index_sequence<sizeof...(T)>::type
          , T...
        > base;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(tuple(), {})

        template <
            typename ...U
          , typename = typename boost::enable_if_c<
                sizeof...(U) >= sizeof...(T)
            >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(tuple<U...> const& other)
            : base(vector_detail::each_elem(), other) {}

        template <
            typename ...U
          , typename = typename boost::enable_if_c<
                sizeof...(U) >= sizeof...(T)
            >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(tuple<U...>&& other)
            : base(vector_detail::each_elem(), std::move(other)) {}

        template <
            typename ...U
          , typename = typename boost::enable_if_c<(
                fusion::detail::and_<is_convertible<U, T>...>::value &&
                sizeof...(U) >= 1
            )>::type
        >
        /*BOOST_CONSTEXPR*/ BOOST_FUSION_GPU_ENABLED
        explicit
        tuple(U&&... args)
            : base(vector_detail::each_elem(), std::forward<U>(args)...) {}

        template<typename U1, typename U2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& other)
            : base(vector_detail::each_elem(), other.first, other.second) {}

        template<typename U1, typename U2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2>&& other)
            : base(vector_detail::each_elem(), std::move(other.first), std::move(other.second)) {}

        template<typename U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple& operator=(U&& rhs)
        {
            base::assign_sequence(std::forward<U>(rhs));
            return *this;
        }
    };

    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};

    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};

    template <int N, typename Tuple>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple, N>::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }

    template <int N, typename Tuple>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

#endif
#endif


/* tuple.hpp
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
*/