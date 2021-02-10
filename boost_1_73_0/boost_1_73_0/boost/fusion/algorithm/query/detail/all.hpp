/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ALL_05052005_1237)
#define FUSION_ALL_05052005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_all(First const&, Last const&, F const&, mpl::true_)
    {
        return true;
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_all(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        return f(x) &&
            detail::linear_all(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }

    template <typename Sequence, typename F, typename Tag>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f, Tag)
    {
        return detail::linear_all(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct unrolled_all
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it))&&
                f(*fusion::advance_c<2>(it)) &&
                f(*fusion::advance_c<3>(it)) &&
                detail::unrolled_all<N-4>::call(fusion::advance_c<4>(it), f);
        }
    };

    template<>
    struct unrolled_all<3>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it)) &&
                f(*fusion::advance_c<2>(it));
        }
    };

    template<>
    struct unrolled_all<2>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it));
        }
    };

    template<>
    struct unrolled_all<1>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return f(*it);
        }
    };

    template<>
    struct unrolled_all<0>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& /*it*/, F /*f*/)
        {
            return true;
        }
    };

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_all<result_of::distance<begin, end>::type::value>::call(
            fusion::begin(seq), f);
    }
}}}

#endif


/* all.hpp
93P4gk4/Ou7cMHowXsyja2ykt1zFtL/3NOJgPvewp7yys3BNW58wKtzEtFIeDTZ8J2cljwkK1qFaLPy+T89WweqR0CCaR4tb6i9Ze8nmGli8BM5xN5tF5tFDeE3oTbtxE0wLncXx/ECdnENAvQ8Wh4AaLW7iQ7tPjIPm/IfoRpPHSa8/6XfbHX+UIY+T0XjYaY394Ys/hAvCS3yzmM43s9B7CYA/wtXB3cuU4uyZVaM3CQYswBJ6ST2mHyePyTq8t7/Fx7SmwFfqnA7g4jbxVpvF/jq6D710i9rW6L50escNwuhw4V1vIjrQ64AOzRro9yVa0KvmoGOm6u3IWGY78h0RxL955pE8m0wyT6Xdrve//pchdS8877f0o9G3y/NOUz7MLhx/Wly1PybrWRQf3P2D9Wge0RFN8IyHmUK/WIXh+aiNQdEI7AfeP/zJa+zSini9MJzRCbuh05G+14ufPN5fx3OBGDH+2JvwxzhZhfNZsA55PGqoh3tM6nSjZL25uWHU9q7DefyAtSXcWswfuU9szmT9WxYube7h+nEZJtl5om1hluli8SR/y+7R5EvLzz2ftL59oHe84ATnt8yujvqtT7Tn2V3ULyYf+TG2ED8pxO6XzmDSH4wnH3P7zy8+tofycndXL870Lpx+
*/