/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_07162005_0235)
#define FUSION_PUSH_BACK_07162005_0235

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_back
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<Sequence, single_view const> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_back<Sequence const, T>
        >::type
    push_back(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_back<Sequence const, T> push_back;
        typedef typename push_back::single_view single_view; 
        typedef typename push_back::type result; 
        single_view x_(x);
        return result(seq, x_);
    }
}}

#endif


/* push_back.hpp
nyzFyk/nfbWoeUysM30LcN/7ItgabfhsuOor/knyxItiowHCNPIoiOX8semnfW3XPjF9CalHRnO0Oagbt2+/8QNk7qzBrCuUZS4PvjhnAPH3rXyYD8RRl1K1uG764eOzA82omnOHOX3h7j2P/F9qcUV9rBIXb+WwyMszA8/MiTs037EJ+Wq4FXmdbL74PNxjhhUS5Typvavs2rwq1Av5/NQMe/ZK3Do3NwmOfmZrzAR8F9WvVTF76UH17cyX+K+fsh0JeDlCf+t5yXpikUn6258t+1QJgDU3qzye0rcHyoGtbg4T5bg6779ew+1iaDxCsndVPUXVtxrbwXp6YW2yc6GaXhHwKXPUsLbX58KO0wZ+vOL2DRU4cvs9mvGgrJjb6xpi00XKa86cn4AOOqkUm0dFiWaHIKD97RoBJ1jZwxaZYc7ga5Io4KJB3fdCr6EkPHeV9rIDoI+WmqeLec6SPXBFQmNQeTJLjtCyZl3MJKrniosBqMwfcrcKykaQGIOll1o2SeQeo6uL5LnDA5JNQ4LAnxTOZ3RyzvmqxZ04zG4M+2NkTl7BZOEGug==
*/