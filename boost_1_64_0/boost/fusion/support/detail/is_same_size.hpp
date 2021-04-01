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
W8SCnw7dnNCJh99/gfzsw6j2LPczSWluwuo+/IRYee5PbY7/F6zBH17p6VSx8luzQhW/MzbTxztCp4jGm+es2udITo0P+7BKFScs1q3cBjfmkEbMPUtn8p4CyVyuvFApIf2rcN74yaX7zcHCioTOT8OH52UyzUxoF5RMA/LmI416Bd+MD4JjFhx6axeQA6IBPLjjrdC5gd27wkGNLOo2GW5uBe4oQfeqhhF5kE+AeeeGi589zar4/IUYeUJcpmiYHuWWFuqbQkBs5dRAN5y1ZPWyXRetjZiC028qpATG+97jPcrcmET8LhRg8M3ubKOsTtFpjqMUbCerVGGeyd4NsT1DnFS0/WOjR01mdnhrHfiM2P8HXn61UlSqa98hhymAlsXdD615/+TwxhUUo7Ko5rsYNqsoTwJfvGe1BIRJX4JfCFF6zB1I6CqnCbxjozoAO0iKuICsYh+sm6neIAt39Re2cVBNHxQGpqkaF/xuVhyke4DZ5LozVtCS7dr87727ef6mjQXOhxpaxRl44ONAi2Vtflfk/ktvMGir2ObMhkLcOzpAJ1v5oQuzkw==
*/