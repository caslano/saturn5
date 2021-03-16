/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_09162005_0150)
#define BOOST_FUSION_COUNT_09162005_0150

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/detail/count.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count(Sequence const& seq, T const& x)
    {
        detail::count_compare<T> f(x);
        return fusion::count_if(seq, f);
    }
}}

#endif


/* count.hpp
VVadXgPxGogPLeVUbABsF4hdIA5aiJuVNA6COAjiCwuhzlg+AfEJiKPmq73YU02ean34FNSnoE4KSs7Vk5lKeOHnQywAgrzCDtosVWq75ZwmRt+sKmPZ0CftdqXk4ul7UmPzKGgA7BCIQyB8BqFdL0sV4jMQn4HIlATVq0pt3lmcVk3eUxXyc5CfgwzKs091s9T9yTx3PUylfPANIJYNirzed9DvK/XJSkvQ56RP2p866A/Q9JlJ1+zzOeqH1CU=
*/