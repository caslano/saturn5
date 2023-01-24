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
fePLfEtJMdAyuhvs2zjxdia+jRC42dLl927IPdBqoOhklrYawdIxvBqjU4P2nw/gavQP2n88AKtxcG6jXI2DVc3TBQqI49UAS05aihFOs/JHru8yzanr1T9YjUrFTnc42+aGpfjy1WQtImXYUrS2FmtvPtVafPfvNtdiUMu1gJNKdbzxT9aiUK4DLYDo2ehCNt4YDe3jmoj9NrqEU7MotcQtfeQG7f0oySNWKrGrXLPvu2hrdutv7V6zQd/LNRv4/SnXrKiVNXv2QHvWzLGs9TUz+JoVy5WBpIFAjjynLjGfrgzxT0ygq2BQs28KJKSLf4JBdbmd1VMEhE8RED5FzOwUAeFou+Seuxbleh3NQCMF7akHkKPESEdcMeec/J5yVrTI+QFzfHXkca+OjJnrjtEDpf6+unh6pNKD/N7VpdODrHmXZrJyYjoIBX33xvtHZahNrwHaE/8748W/lOJNzlSzaFUw0AvB4FH9/M8kk7N6WqFvWpmvbj+1SCLlhVIUmBy09/jeKjtW0RAs9s07SHv5jy4SLp5guBCvXegV6MWAHV8FvWi5MCCgBdDcOGDcS5H0zZA6+rwcloobtd2TDqujXInhAdCNwNL9VtOH6EbgdhYxOOB4doA8+sayTuxxvOxCOKj4Toe4dyrE5xpIiwWU/PkSHcrcC00XLqS0sln9zIyx0CuaUpsmHwwGt/D7aO09vuk6w/tgw3uF
*/