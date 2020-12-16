/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/prior.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::prior<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* prior_impl.hpp
jVp81UOYr70dljPbOenZfGHuDnivzUz+3wvWZ2DQUW0uA/MbWMTAnJ3U5jOwMBrv9dhUf1da20/U5kZT9sXAoLPaXAbmN7CIgTm7qM1nYGE0ZV/canMbmN/Awm51Lo6uavOiqcYMGhh0U5vTwLwGFjQw6G6Hsszkf+vgfAbmNbCggUEPg/kMzGtgQQODngb9NDAvWjtmL/6+842wiIG5P1Xn4jewsIFpvdTmNjC/gYUNTOttMB+acj8ysLCBaX3U5kZT1mdgYYMxtb4G8xmY38DCBqb1M5gP7Yc0K4WW9VST3MJc/fGajxn9Bx6aT2f0H3hoIbSM0th3ejFPNBsz+g88NMsAO1RjJv97DfNES2bGz/1+tCRp7PkEzocmcimtyyViYDAQr+uYpVsxsB/VjjbQJG3FqxrjKE8PXhOxuL3XrlYVBoPtsDdGWovfBjqFBYZTP9Gi+xlBszHjPdNG4PNIPl9k52xhXrRFzO6O77RCmHOkHVYzG/to1Qxah1E8l+h1d6Gp8vShjWfm0z7/VphjtB3aMxt3sfApWj+0nMxmzapRV1gQTbVGITRVX+AzOxRn1tmb/zrVjhbH7IMmawYJ86A1ZtZ6a7V8NB9aOWa3T/Z20Dp8ru6ZG03VMz+aqoYQWirvy3c7JguDsXgfZ5ZmDU1KR3HjaT9Ci96PNK/aPAYWREtmxvc/mKA2p4F50W6YpCVsqRQjLPyFfN6KJp+3osEk3N+Z8f3daWBeNDszur9FC6DxNaL7W7SIQZw2WR3nRlPl4kdTjRkyMJiiNgeaaj6PgQUMxgyjqerTpsp906HbNx0G5kRLZMb3FS833b4SRLMx4/tKBK0aM77tOqepzYeWzIxvnyEDs0zHZ1ZpVgbt+b9XF1INaBmZ8dp9BuZH+9Ys7asMScupvll2OMzi0qecvUY22w7PmF3f1LQsrcOXdljJDNbvziYMfNhrZnwdnNx06+BFszHj6xDwqesLGswHc9XzOdGGMvttUfmRtEZoqvnCaKo8LfPeHz+FzS5qHU9xC+wwl+dydEJrWqOFdljK4lZfS3BT3BLaztCitzPHV2rzoiUz49tZ0MBgqR2+Z5bj5uYulAuanRnfpy3L7FCMmbf8grXCXGiqOC8aXyN+LAii5WXGj9dhgzEty/G4xIwfl1wG5kNT5RJCU80HK9R5amiqOBeaMhcDC6Gx9WPvjmDtK9U1uNBamaUNXpYkj5+r7BAysTw7vVxGuayW74eURXv1n7Y9acw1OB+Z7toNrRqz+ks31Kb1Q1vEbMCIc1eF+dfaYQyzanBhJ+W5DvdNZnzfdKHZmPF904tWwyQt1/mOPurZd1g7i7v3y82XtH7ro8cs6QkepvnQ1jPLt+LAc2GODWqzbFRbxMBCm1g/9ddgm+0wj9nehWOrUq915tgS+Yp6vQWfqTIrcPjYfapha3Rc5Uq7h1CeaMlkumfGAczTJK3FzTK1hAW/l+uXrL/2RuvEbNXagaup19twOyPTbWdoNmZ83YM8Tn9+2K4e04mmytOFpprPi1aNGV+jkIFpO7CfzHg/3QbmR8vLjB97gmjH09ahHNrWJ5nKCoNdVB9adH0WtERmvC8uNBuZrnYep+t10GBM2I33m8xG9B+dh2pHK8us5vGPZ1HtaMWYlar9bTVhYTRVfRE0VQ3aj3aoyqzI13baHzxo1ch09zJoJpO0PB8NyEL9/I86zo2WTKZbW7TrzBbPX55E8+1Vx8E+/CyZWQ9rzAJaP7TXzMosOFJMmG8/nnPIdOccNLF+Kbr1sxzAXjPjvdbQbMx4r11oXzOrvGXdC4oL2mE/s4Rr7VbQfAfxXQBm5+IryXMVWoRZvdK/9qeeHYo=
*/