/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BUILD_CONS_09232005_1222)
#define FUSION_BUILD_CONS_09232005_1222

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_cons;

    template <typename First, typename Last>
    struct build_cons<First, Last, true>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_
        call(First const&, Last const&)
        {
            return nil_();
        }
    };

    template <typename First, typename Last>
    struct build_cons<First, Last, false>
    {
        typedef
            build_cons<typename result_of::next<First>::type, Last>
        next_build_cons;

        typedef cons<
            typename result_of::value_of<First>::type
          , typename next_build_cons::type> 
        type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_cons::call(fusion::next(f), l));
        }
    };

}}}

#endif

/* build_cons.hpp
d7m0pU3HMJyBczAJ52Ey5uJMzMNZWIhzcAPOxQqcp7V9yjFJjlXhHm2f86V8aZLeQhyHi3AqXomrMB2LcDE6cAlW4VLchBm4BZfjA5iJP8YV+Dxm48uYg9U+9oM7cVMnr33hok//9/vDZZxue5+4mtMXt19c4+lvp29c0+lv1j/O0vTt9pG70P5x59iGOu/oZAknpBJshJod/vYH/+Sf/NN3f/pW3/+XV5GlPLXtvPL/Ztf+yrvvPonkVEN9x50smGUOIl653rXq47MKS3LXOf/Wh3nC9X+TB2bD+BtYotW/2Uqy9H/OKqFwvDLNkaXec3gnxD3mYJ1cwx7H0diI/47EQeo5UNKiZWnpC7Js5fYsLY9tfufVZUO060zKwDuvtOux3MKcsjKyaMvTv/vqklHOd85bJK4JA9S41aUlRXKNrnuHlbxXUD4XyDP12vPUjlJZTpw2T1EFaNeLX0Wq37Pr3+v/tRpX5sih4pW4ZPmuki8q0tJf7k1YnM+cE5mzJs9C3riq7OEsr+XvkcZ3y51tL+fcUtc9sR3fjxmqq2v17o6rstte18OsbatrZx2xQbvrWupffe2XT3XrWh93B6jr6BvVdUv1+ukwZ71+6VGvR+Xews8J/QhPE64N5BTLalavag349C7NHSHGukxroS4z3HVkc8XFmJTX6rEdyfvYpO5yDOVK6SjXHIT+hDmEDlGUK0RfrjXs1rK5tOF5/gBtHct9NmP+1XxMk3xUy3PzL5LoMPwFXko+0oab5IOXQDorpvU+E0oddww11nF2C3Wcr78/WCh9KfT3B/nQX/pSsI0Qp2RmdXlxrvudpH9X4zme6eJrtfmVbUT9g9xfar7+YkzWX7yX9XdYTptny/4+FjtRb3Wh+nojjxd4bP229u8UH4+did9wf745zHx/tnV2vwt3sLwLtwvft4/S11uZfrtvdX+W45au7N7322yt/PRjMakj/T3gk5LXMbJtRhDqAwjhal6lBxZD97Rh35TjKJthmZrWLKmXqi7Oma8h9CBsIAQqxzlJSz1JyXIlmVNYqDsJ8KVPjce7Ill37Xu/SvkqSHcCcZ0jSEe7f2pc9+TTcL/3lOR1tuR1BmEbea1Wl+F5gtJ63tTjkSw7oavzD0Nk2UGuepBlm538+PLeR/16DeimxrOPsWzCQEKfUcRHKmnIy4o5jLTl3r7neU2Ax3lNfxl/hm1P4rK07dRqsp2GmxwPYwzHQ2OZzkiZ+hECJbQn/Rh9mZRDoA9l6i9lkuMEp8zFDq1cJsePIPe+d1HLdLi7eZnS9GXiEOvLevqulCmxhzNT7xCUiFOErsrxz1km5Yc2p9imXhS0etxr7bwl3rAfG/ezA5KPAYQeUoZuyu9XlJqPsnVZMzOykqanps6YnjRP/R0rLi8sbGk/s5InYxteUE/nX0Jk+cGEXqTRaJ4GY4q3vnxX/fZw/uas8yxXg6QZJWULI/TmQ5NpmvYSu7pT+J7uZ5Fautrv3z0BrvML5bju0Se6V/P89OWDNdo0P+Vl+ReWlz66cxXZjg35OCH5GE8YLL9p/chHtmk++P1tw7owy4fnfpLYQt7SZc9Vx7uSdoMB5K3eNG9q/1Of88Z20kLejPvm0YDm2+vGEWw7Wj42lBTYlA3G9/Q/GKClb+xf3bv5/reJtAJG69PSdrxW09OXo7Z383LsYtkxxmWzw/m+jneOkHJ4pNW5T/Pt+3bmzTakpW7YPqdFnRnXmeH4bEx/T5/m2/VAZdsxps8G7XtZPxjg2/as5clj3Vr7Nt+e71C2I0OeZENuw362c0Tr2/KnmNjOW7vp/67d2rx92ns7tHm7tff2Y/P2e+/t2ebtzd7buc3blds=
*/