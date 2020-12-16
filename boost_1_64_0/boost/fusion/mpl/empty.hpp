/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_10022005_1619)
#define FUSION_EMPTY_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct empty_impl;

    template <>
    struct empty_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::empty<Sequence> {};
    };
}}

#endif

/* empty.hpp
DaHzsRn2PZqfYV0v6/JezqZiyLsQfvZgwFrqXbBW+gJr2Xk63gNiLdhmXMG8RTDes2g1KAq0U6OT23ga4aCsc19mzhwilPcgNJfaZGqN5xCnrA+7XMvrUGFYdFLCl2wH4+eldoEJ968xV1Hh8F5Xpie/U7rZR+vK31N+x+iTanJ+VvgK634esIS2LLTYyIQ1OZGG2D5i7qtCb1Q6Y2m58xzya4HuqlGMe8nXWTcjhDzjs8ycn2U0YUc0x9Ca/pZtScVB8buCknb2jVCnhIq2k3yTdT06cX2XNCPbVwd96h8kM7p99VRY8fY1kO2rHW9fAx2ObV/f0ro3Qei5Pyod6YS/Hv5emqi8X/ttzUkTvVXWlr8zkikvLNFyco1KlLwMml/RYhy3i/z3+XfZ8gr8hUv7MuLxhlZnaqv+w44raFue8zt4tLzDbaN/Umn0hQk3pIs592WkruZ357CWkZNMML+7rNT0/C63S2nVxVWR78tJTc/9elpzqUE55y+vNFckd6Ynfu/r7tyfVmWcektjmY1cwfzOVkvqiB3Bb3b/f7+haI7w27fqN/SSvi9w+S2WK0oGH+iCneWupPU2XTglimKm5W5xVmHbcI162gkKO7uyYtyH5H0mmOldRTJqntDBWKoZ6t743ej+VaWWziHQ9xxVGnVMKA/YefGUYoa6e/cbZXpXq/uxAnlIViMMlb5kBtMRhlLkGLSvqyum/f+2r/w19O/+n/a1cc3/7zeufWXp2yyFv8EbHbWqjQt2U5z5/3/XFOPbVt78rtNAY+R67l1Lcm3Z0PjcybU1Q42I16w+4PtBP4ivVMfcChj0pK910gjgMafr9XQ1ZX1ltbPibaHNa82XuY5jJqZoeXHuPD6wgb7S6nINlPpBo1NbF2u+976c06ePTE1PDnthuf5yFa0NHxrB0x1sS4X7MOdvz/Be/LVZo164ShZPwyZtg3XcV9c5jN51JEfbG/KtkusHmgtIvI/bvEFE9+dtZTo3jzKX7ZZm2nxJalTC0qd7ltCoruhIBfuDzw80WsiWfVD/hYE+eYj3O18WaDPj0xP0W357OtQpbKEnT9e6fzCZ52Jx3R+0YDsYxLnhnAVttRQyVMTkS9Xb4l6YYagucDGM4yvJ8pQ+P5Urwnp+lPHly2FtvTDOUTmzv/vyOOPLm++0vnIUR3HK9xZFPuXXyjmrPOeaf45m/TN5nLbnRnVTR4U4p+poW6VL3+/L0l64m2a8HXDSRdo35w3boqSzjy/D4rlUGWd0Al2+adw1GvXNnIo6n58PuNUFSkKyfvMsz2dDnbYdh04xebEIj9focudiPDm+EpffyA7S6adq6xgDFkO9dtalD2swjw/0JkWUTmacz5Lw2uGOnG8P4v3X/8FTg+Q7+0/ckVVvY29vxliH8Rmv7ovjDCeTw+uPZHmMm6+EDL3zT3UAnzasM9pXJ68fz4qKejuMeV9Qb1Qg9DxrZfiPuM9He4gBNxyXfEuWZwbvKjjXVsXbfNtXZi1tT34w98XRlvs75wJWT+Bq8GHuH3JyjYXbwcYDAy4sHIobvowoE7820YY9yjbC7YN6h+FIymc/Zd/dqi2TT0MjCnXc8m2L50cZ6kSZyb0oxlCnLdePXh5jXKfNzPwrowzFJd78iaaZ7gtTutXbDS8YyVF4zG28aBRH6Rfc5stHcH7gQVt95QjODzxoZ08fwfGAXUc/f3gkSy60e9CQ2dJzR7A8yNTHsrp90gjWdiqHcd/9xTv9Bn3QSdTDMyI853EN5RvLI/LHXC+WP+SN92OKT45wJl+8J118SZyXecJ6R1Wxaw2a8KJveTZrNFtR/mXvBVrzTfEUbPpFWpf+ZfIKrflmdwo=
*/