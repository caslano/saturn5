
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
4FFtcYqxP+pYd6pkyoavq1dF6QTwYQfBwdXThMcGJ8AJd67Ew8YULdKyqw1rnSaMCQz8jgheGyXaLSMVq4jEu0Z81lEUXAqzx2ZL1pBbSqtHLolmtiJXnKJG8Qkq76jNeN+hh7gqvNum52NuRWnCFuD9h82B32i3FvQB24neR9aPfw0sXgNFiyY2CNWA8MaAp3zRQR/jxuXevsd5vf6vDn7mYw7Gfcfcg9vOTi1bDq3mtRg8UHlMUTUCesMnU6NfG4GHJ75QBsr6UPJJ4DP6ZgZYe7CHbfO4l3QwD/wiubEbTDxofKUnuYEKQttT6wiN7trhpwcHy6hswB94zmTGZbbXRh+nVInxbx/HnYj1fD5IxAx2FRBs4NW/EXaz/S1t7+ny+gf+44RtZodpcBz6M9BqTxzCRA8uAdrsmfjXUoOdzyW6K2AsIP+Ew+Xl8U4yAeriWUy3ew3aBNNs800kt0uVxzEZedHKiMVQWTzQug6IAlOB4RRDk8DU4qxvtEO8ED3wR336pOe1l27sOTOo1KMBiWLT75GExoaXQixDI+gTDyEBkX0T8Mh2uLWBYnnvw70Is/ILjPzGqttxu7R1xtgQc/PvhzLMeG1AGmfp6Sl9mENsOgo7KLE2cuPy7pwOaLYQR3z91lhVfoGLhyRW7tTQlbdSpD30eTmcazNOgcZwpcNTUcQhHMteI75BmJpdfECQGCSSg1VoFI+z
*/