/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_IS_SAME_SIZE_10082015_1156
#define FUSION_IS_SAME_SIZE_10082015_1156

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence1, typename Sequence2, bool
            = traits::is_sequence<Sequence1>::value &&
              traits::is_sequence<Sequence2>::value>
    struct is_same_size : mpl::false_ {};

    template <typename Sequence1, typename Sequence2>
    struct is_same_size<Sequence1, Sequence2, true>
        : mpl::bool_<result_of::size<Sequence1>::value == 
                     result_of::size<Sequence2>::value>
    {};
}}}

#endif

/* is_same_size.hpp
tvXV5lyVlv3SI1vUIzcbbbwh3/SflEMJG2d/5/Lk/IDOx53sMTYPTWnLmc43dooct7QspTtaGPU7U1o0bsgUfjkrI53ZKmHqGXntDpGRCb25vUubG23nh3dZzkTEKMpkjOnaGCAeI/Ud1/c+u5Id3KH72jbOC0p+Zt3ndyleLzcrPPajGLtObFWzvc8hQUv22CDTXFPVRnzUVB2jf1nOHax63GEl4AyE3E6vXc+xBjo4ajLt
*/