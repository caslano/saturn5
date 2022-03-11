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