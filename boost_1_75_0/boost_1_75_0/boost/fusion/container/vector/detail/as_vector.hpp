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
EFP8OYeVqB9QMLSiYFjLBcOcw5x2DthgxeKM/RwOYz8wboYBtPGA8yiC89grpphpNfC0dTdAmTWK9Vh9kxQr24dTyHBEwdEdgAzD0IKRqrEexBtyjeNy28uiwcEUsQHj4J4CrnphiMoxhHeKoYZyuYW9NW/Ft/6tNDh7CLHoK2oDqnJIhA0sWcCKExlpvjhFWS/pw3vYBno4kuLAUWSa+fOJtKw1kBZhVGDkJe8IMdTsQ/TM4L9Tj0Rpfvl0zXSU8BtEilPMKE5GspHiZMunBQesZK9qGDpUqg73+2znpOyG4Do58hIYER7PlSDtBsGJoU4No6VwZA7LCRyL4X9WpTFnxz+025k2lrNWGdDChNYIVrn1fbi2P/UwIMdaIluHUfhm2CV3fOdNEGYZGWLLPEparJpMZtPsNpn2DWBT36fM+S0K92IwDQ2SX61lFGoyRIXr4YST2Zx9yppH6DAY8gDlyLtyIqvQY2k8nhiaK8ARMa6b1PMT+4bIwvSoWE88eOAXMs58LGV30HLpbu9us3+ImaFU1i6mb0GNvzyK9hXaD7Gqo9c64wBE/g72Zq3JkL8DMty1Zux1UTzGiwSHluvQQWjqPhOWZXO2NuVApn8Qm4H414bGmJS7iqMpNlJbPjXZQJ78jjddMRDJ6jBvT+AVRMIeZCbaxLfyWiXtW5igBIH2BQYotq7vWU0AdRGHYhO9NizsOw7Mxfkj
*/