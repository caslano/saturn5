/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED)
#define BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate;
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f);

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f);
}}

#endif


/* accumulate_fwd.hpp
n4XPwo9hDdwCn4Mt0f15uA9cA4+FL8IT4EswG74Cz4N/hjfCtXATfA1+BF+HRrjEWtgavgGPgn+Fs+A6OBe+DW+D6+EDcAN8DL4Dn4Tvwhfhe3Ad3Ai/hJtgPXwffgM/gB1o9w/h2fAjmA03wzz4CfTDT+FC+Bm8CX4BF8O/wT/Bevgq/Bq+Bv+heY320d47ddJ9sr3x7l/j7XrdJ2+AfeCNcDC8CRbARbAG3gq3yt9EEvncDlvBO+CBsAoeAu/UPHI3PAUugafBe+DpcCnMhsvgLHgvnAvvg9fA++Et8AH4KnzIct1oj5y9c+d1c77qcQEcJrvbibK7vVj2tg/AS3Rd/E7z8O9Vr3nw7/AKmCz72R6yn+0ve9nB8FrpU7OH9ru1D27oM9BoV103mbpuJsmeOxseBXNkzz0FngWnwikwT9fRNDgXTodVMB/eA8+RX4QZ8k9RCLfAc2HgBZ38UvhhITwPngdLdR2VwYVwJqyE58OlcJb8UFwA18E5cCO8EPrkLyIdXgxPld+IAvmNuFB+I34vvxHz4Tx4DbwMroCXw3VwPuyaRLvCg+HVsA9cAPvDa+BEeC3MhdfBafB6eD68AV4JF8Ib4I3wcXgTfAIugs/AW+Dr8Fb4NqyEn8HFcDu8Hf4A7wivD7R3Dg/W9WJdH7BuNNcRStcnSroqpesdJR17xTH5mWB/NyY/E+y7xuRngn1RTz8TP5vp2NuUflHS1Zn6NZAO+SK2dNlK1ztKuqovvOvxrXW9q3QHR0lX79DPNR17TtLPI92qFlyH2LPXdMYGE2nDgqQvkoGUIQsR7OOj2sW72b6v5LceMcOxe//fjxu+kfp72bxv65K02+3e47V5j9XWPVY7952JI971wKS4bdsby6490qZ9GLo0ZNeeeWBS1Pjiidq0e9mzlx2Y1BRj3NWGHdI2q5A6pCU3+l7IMCQbKUcqkdVIHdL8IOzKkXQkH5mHLEHWIpuRNt34PZKOFCILkJVILVKPtOtOPyAZiB+Zj1Qja5DNiC+F/JF0pBBZgKxENiA+Fh8pSDpSiFQgq5E6pGWPJlv2pk/Tp+nT9Gn6NH2aPk2fxv7sqvj/xUXTGiX+/wVsltYsNo59FBl5ZoVOpHbT/9UF/i/wX4X5OaX5ShCwoZ9h2tDzvlH+oLUPMRLJN86vPNIjZHt4Rv+s4ZkTAqFLc3JzA1WI3fbwouAZVX6j878u58+zTbs/nXc3z8Zu2l+xSCw2gpfo94p9GK7LPNnHn626TELOoS5VnnUJtF1U+5S2IfuUiLqku9Qlw6MumR51yTgy8oyT4rEnOfulkLqkPBpZl3HDT98N/fJ8u+B59PNi6Jdhso1forrcgRRRlwqPuqhfYq7Lx41cl162fjFj/37SMRi/uKywoNQlFqDNRqxNC2f/+alz9sqIOu+GvnsyOA45Cu/Zd6a9egvnNVVCPWoj67EbriezHtGvpw2yu0/aI1iPn5GyIaR/zLMeWaUzYu+TnR2Dpt46+xcZQ0jj8oi2GoPesShlF8DPIm1a93KOyfON+fGPEW3QyOORv6nu9phF+XYbiahjMbulU//Z6J/8uJv+WUUFuY1XB9NORe0fyD6+eoT6oZPs5mfKj4AfuYB6lDvqgRlnDHb+uk5cdTPtP6aWFJSZ9SCOstJiUjJzquY4R4wrm97NZdP+vdp/G3IheqesitC7kefveMbPAHt9dU3oupF9pOpqaa+yC/x59rG2WXVdpLregFxkzN9POOuqwdZo9Y13rNnrHFv9ylsrRrTeU92IXGL05ZPW+k3PKwvbIEa349W87qhLunPeC8T+fTBYlu+89nbdUmV7f6fOlFcil6JbnUM3xi4rY1+Cuuk=
*/