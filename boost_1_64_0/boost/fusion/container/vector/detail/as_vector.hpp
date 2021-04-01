/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_VECTOR_11052014_1801
#define FUSION_AS_VECTOR_11052014_1801

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/as_vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <typename Indices>
    struct as_vector_impl;

    template <std::size_t ...Indices>
    struct as_vector_impl<index_sequence<Indices...> >
    {
        template <typename Iterator>
        struct apply
        {
            typedef vector<
                typename result_of::value_of<
                    typename result_of::advance_c<Iterator, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator i)
        {
            typedef typename apply<Iterator>::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

    template <int size>
    struct as_vector
        : as_vector_impl<typename make_index_sequence<size>::type> {};

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif



/* as_vector.hpp
UXK8wn6wx/YlarxqIopMtNfrVJb6dum2k/Z6ROpGkENOA4HnSPcz396HN9Im+f9GihnBw2re5Zbb5b09wBLveA8UAcVaHvlahXPA9tL+XRQo9F/1GtMldunpQ/1ss920YCnXZRALgCSVzShZqogb0BTXFsQaw9QN2KArzGhnxc/heA3GD6zSlZGqxopu+qFQKaAGQA8JQ5rkgzL6dk6gQKw62IHWv74Hk1S1t9ZtEYQmFY6vTXT9vt0Sz4MQvbvtDKpemy0WwAsQ7Xnfy9GJSujv2BRB/X9s/XyUmz4nASirYeOQITm2TRILvhgW3XCkI8M7M8yaKq6cDozd2PQ25GBAFMMVWBFM4HSI/z0B/05QYbgvmMrhJkehnga0QQg0nTsaHsIl1DKZXPlH71M9Uy4khS/3FDjnzrlhBVHwlv+oiTb5iQYLtT6n5Rcx6qMCO+79x992768/w65HduPbi1ovM0+eG7Sbn+eb+R59GAAdjuqEaUHVFh2JpQ2O5yHGWFbIzve26WMgeKWyIEhGcXbkOTColl53rxAqwGXesDvMT2HcOog4UGqD0Q==
*/