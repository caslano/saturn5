/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_1142)
#define FUSION_GREATER_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) > extension::as_const(*b) ||
                (!(extension::as_const(*b) > extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater.hpp
RWG94hLW78JdgU66YfmXO7jx9hJy36Sp8R9dabb0D0Y5lPIiVn36OjTPqHxrwb+Rs3BBTLpwg5YgByLf7Gg1tg5gNhiSdzj5gZib00XKt4COwE41qiNSI0US00zdbJwNszGQq64XQ5bL49KCozAmYxrcBSrNnkmVvn7IhxehBElQ7gRhFrErJfBHKc8xWNCXEzNH8g2On4EvzkJbI2+7Z9J9GE+gxTsJiAMMd3SE3LMfDpnN1Ft5IiWzZKOOO7MnEK3ryxLZF8rKVHx7IzrLXIvDo6eXNmslGDMwUr5UPr5GGykb4EL56hoDzJ3X4LGv5Bu97HNX+bfaAENfmkR0mpmnf7YQP3sr+tlz1xgDbKBGgjmZxecZZRj+jZgqMR6Zqo0Pxwp+Mn4qPxk/aq/uw1FioQAVopZ8/ICHfVaPpyPYG/vhD7NObEkyBZpV/xV8wvr7r2dAvQO59IcQzU0fpgyFAsx6HfzqZyg2otsoOYCD/neRGxQIDx5RR5ep2qtNJi3QEjzifj+Y0VvKqJGaDnr5XYkH7oI87DzPEZejfNxyBp1/lvLsWhQtMs2F642tmoL3MKnAFi/bQYkreWJa4MTyytn+iL8U2pT0lqlC83HMrAFzCvSOPfV+vquQo9qHFPNE6j1U+1+KMfBWzYJaPfAW5bsujCSQDxj0Qu2sy9A7JIsOA3tRg9CgUetZDQtJTC7RDrav701G/6nx
*/