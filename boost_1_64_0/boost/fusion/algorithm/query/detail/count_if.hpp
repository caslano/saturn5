/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0141)
#define BOOST_FUSION_COUNT_IF_09162005_0141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion { 
    struct random_access_traversal_tag;
namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline int
    linear_count_if(First const&, Last const&, F const&, mpl::true_)
    {
        return 0;
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline int
    linear_count_if(First const& first, Last const& last, F& f, mpl::false_)
    {
        int n =
            detail::linear_count_if(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
        if (f(*first))
            ++n;
        return n;
    }

    template <typename Sequence, typename F, typename Tag>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline int
    count_if(Sequence const& seq, F f, Tag)
    {
        return detail::linear_count_if(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

    template<int n>
    struct unrolled_count_if
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static int call(I0 const& i0, F f)
        {
            int ct = unrolled_count_if<n-4>::
                call(fusion::advance_c<4>(i0), f);
            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            if(f(*i2))
                ++ct;

            typedef typename result_of::next<I2>::type I3;
            I3 i3(fusion::next(i2));
            if(f(*i3))
                ++ct;

            return ct;
        }
    };

    template<>
    struct unrolled_count_if<3>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static int call(I0 const& i0, F f)
        {
            int ct = 0;
            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            if(f(*i2))
                ++ct;

            return ct;
        }
    };

    template<>
    struct unrolled_count_if<2>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static int call(I0 const& i0, F f)
        {
            int ct = 0;

            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            return ct;
        }
    };

    template<>
    struct unrolled_count_if<1>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static int call(I0 const& i0, F f)
        {
            int ct = 0;
            if(f(*i0))
                ++ct;
            return ct;
        }
    };


    template<>
    struct unrolled_count_if<0>
    {
        template<typename I0, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static int call(I0 const&, F)
        {
            return 0;
        }
    };

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline int
    count_if(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_count_if<result_of::distance<begin, end>::type::value>::
            call(fusion::begin(seq), f);
    }
}}}

#endif


/* count_if.hpp
9NZL7xK4yb/PRqvxfPZUBMXycdw747G77ftnhN87Y/Mt8WH3z9hxS9j9MyLaO2P/LfHHff+MQ9i0xQz6zPfP6HxrvC+2UM5Hke+jEekeGopDFNG+GXthGr7Y983IvjW+XffOiHbfjCLsB8cyct43Y7NRjtC+b0bRR/AN1/0zgvbOSIObRwXFN2qXvTKOdp+MHeTNvlfGPn5z2S/Dda+Ml9Cxx0P6iN+c9sxI2R7f6r4Zk7fHR7V3RnaDuX+Gfe+MVvfNiHbPjKX4tgHZjhxADiEJtxHLCslGypBrkQZkP/Iu0vF29r1AspB8ZBOyDXkMaUY63sHfkSykDLkW2Y3sR95GEuq5V5BcpBrZijQiB5EjSMqd/B3JRzYjDch+5F2k013E9UKykCKkFtmB7EcOIZ2/xb4ayFKkGtmKNCIHkI+QATvYjwPZhGxDHkYOIoeRM77NfY3kIpuQemQf8i7S6W7sIllICbIF2XF3LB5V7IgdsSN2xI7Y8f9+HIf4//zHiH9z9PH/jRiAZZbY/nyj9h2Xw2S4ET7PB9nmBfTHFffFCABUWlxayIzSPMOLaGI/PdYtOPZT39PNObah8/ill2b+Vqq5Vi16cZYY4/X/RfOqop0/5TwPKzavqr3nVbnNn5rjmw/V5aXzjqzKn3T96GenF07r+OaKts2H6tRB95Pus1zKprfv+5y+32h863TYB54JB8MkOAKmwHGwO5wDe8Lz4FlwOewN82EqfBT2g0/CAfAAHAifg4Phi3AIfAmeDZvhMPgWHA7/AEfAQ3AUPAIz4An4PQGeBSfBBXAqXA7PhRfA6XA1nAFL4SxYA7PhRrgAZsZHNm5nGbMLib2dOSWymNsuY3DHJdb28YyzbY+xrXGtdo2r3ZaY2rZxKNdY2p1mOo4ttTludrQxsz+LeNmW8Z2o4mTvjY09xI7YETtiR+yIHf8Rx/Hp/1d515a2T/+/2NL/r1P/vw9Mgj3g4QxkLv0Ve6z9VePG5BV5CiuKPK3GgA3E6R3gW6NVVV1pidNbbdk7LYnfMsx4vkYescDJXQMx8n36XjMOQHZK4Dy/brrSky6J2tbuKpY/c6dJA4EfZPD7fJf8ecqjyp/FH3zGRzMvXpt/ZCsvJM/6XflRnr2+3w1njHILzs9B5WcqkohMQP5MYnuzHfKz2lOtQMytrmnrKl+1b0OQzZV65czS2rkZ2o8hYYGDzaq223Rbhz1K+9q9Kj/OU96zkWcSKS+/H0ZpUcCjRwbGp1KgDsf97FId6ieIqwnUz6McazrWY0rttZ9dbKzpsx1rusw31vT+mFVP3Xrzg8sWXPnJi3P2f3xC28aatsWp7Vabnmvbn64P7iXBAfAsOBAOg4PgMjgYboRDYC08G26Dw+AdMA3+CA6Hr8AR8HWYDt+FI+GncBQ8E/ujYQ84RnO96uLU9sJk+WeE8N0s/yZwXiKcAvvBqXAaPBcWwkxYBadprc90eD+cAZ+GM+EzcDb8BZwD34JZ8EM4F3bB7jyYCOdb1hypDcUmftnWHCXJr2Q4EKbAobA7nAB7WNJRu4jN0HQ+p7G+BHg27AZHwEQ4A55urulSu6b2LrVD8Jqul+TPy7A7fEXp/BrOgq/CbPgazI2Nuf3Hjbkxbyw27naMxt2Yd3VMxt7G7IyPW4lsRnYjB3fGxuJiR+z4fz+OT/+/kp5V+/T/Cyx7AI7poLXy6tvN0p5LTVn6/q+4MC3dutbjo6hfRywYt35dcCzEvQ4+vI9C+txQH6pqVq3xFFbnlRes80QSu8jNl20+X4xUguMn0dRz+H1I0vvcn1Coc/CF/XCqSivKo/ZB/X/tIe9P5Wj7mp/VvIZYvJj/rr7mA76+5tg=
*/