/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009 Christopher Schmidt
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1107)
#define FUSION_FIND_IF_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Iterator, typename Pred>
    struct apply_filter
    {
        typedef typename mpl::apply1<
            Pred, Iterator>::type type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if;

    template <typename First, typename Last, typename Pred>
    struct recursive_find_if
    {
        typedef typename
            main_find_if<
                typename result_of::next<First>::type, Last, Pred
            >::type
        type;
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if
    {
        typedef mpl::or_<
            result_of::equal_to<First, Last>
          , apply_filter<First, Pred> >
        filter;

        typedef typename
            mpl::eval_if<
                filter
              , mpl::identity<First>
              , recursive_find_if<First, Last, Pred>
            >::type
        type;
    };

    template<
        typename First, typename Last, 
        typename Pred, bool>
    struct choose_find_if;

    template<typename First, typename Last, typename Pred>
    struct choose_find_if<First, Last, Pred, false>
        : main_find_if<First, Last, Pred>
    {};

    template<typename Iter, typename Pred, int n, int unrolling>
    struct unroll_again;

    template <typename Iter, typename Pred, int offset>
    struct apply_offset_filter
    {
        typedef typename result_of::advance_c<Iter, offset>::type Shifted;
        typedef typename
            mpl::apply1<
                Pred
              , Shifted
            >::type
        type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };

    template<typename Iter, typename Pred, int n>
    struct unrolled_find_if
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              mpl::eval_if<
                apply_offset_filter<Iter, Pred, 2>,
                result_of::advance_c<Iter, 2>,
                mpl::eval_if<
                  apply_offset_filter<Iter, Pred, 3>,
                  result_of::advance_c<Iter, 3>,
                  unroll_again<
                    Iter,
                    Pred,
                    n,
                    4> > > > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 3>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              mpl::eval_if<
                apply_offset_filter<Iter, Pred, 2>,
                result_of::advance_c<Iter, 2>,
                result_of::advance_c<Iter, 3> > > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 2>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              result_of::advance_c<Iter, 2> > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 1>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            result_of::advance_c<Iter, 1> >::type type;
    };

    template<typename Iter, typename Pred, int n, int unrolling>
    struct unroll_again
    {
        typedef typename unrolled_find_if<
            typename result_of::advance_c<Iter, unrolling>::type,
            Pred,
            n-unrolling>::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 0>
    {
        typedef Iter type;
    };

    template<typename First, typename Last, typename Pred>
    struct choose_find_if<First, Last, Pred, true>
    {
        typedef typename result_of::distance<First, Last>::type N;
        typedef typename unrolled_find_if<First, Pred, N::value>::type type;
    };

    template <typename First, typename Last, typename Pred>
    struct static_find_if
    {
        typedef typename
            choose_find_if<
                First
              , Last
              , Pred
              , traits::is_random_access<First>::value
            >::type
        type;

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter, mpl::true_)
        {
            return iter;
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter, mpl::false_)
        {
            return recursive_call(fusion::next(iter));
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter)
        {
            typedef result_of::equal_to<Iterator, type> found;
            return recursive_call(iter, found());
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename boost::disable_if<traits::is_random_access<Iterator>, type>::type
        iter_call(Iterator const& iter)
        {
            return recursive_call(iter);
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename boost::enable_if<traits::is_random_access<Iterator>, type>::type
        iter_call(Iterator const& iter)
        {
            typedef typename result_of::distance<Iterator, type>::type N;
            return fusion::advance<N>(iter);
        }

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(Sequence& seq)
        {
            return iter_call(fusion::begin(seq));
        }
    };

    template <typename Sequence, typename Pred>
    struct result_of_find_if
    {
        typedef
            static_find_if<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
              , Pred
            >
        filter;

        typedef typename filter::type type;
    };
}}}

#endif

/* find_if.hpp
C58f9tZJD9z4raQP5+0o/mFy2/qaWXFqJ3Tv5triTvRXX2cA7KO+Zn/1Nc+Bg+EsOAQqPe559/R6Kr1eSu8spddb6fVReqlmerpv4SyH9E5XX/gM2BueCftZ5l0kw0yYAusi7EPtuDtk//DQvcPvtq8zat9+1bt3/2/0rbR2x7GPNXNnZP0s787w8xu27zy2fa0DOyPrb0WyhibSflfnhtb7Xp/FPuHZDc79r/yGyPtgh+hzJTTEx2U0xPpesSN2xI7YETs+2+P49P/pq7bT/P95aXHmXve71ffehqQiNyI/Mb7/j+e92brH96yFSxcvzyus9BirAFZtzFs4d2Yk6wAC+/o+neHrb3usexxXI/xWWtTyPZ3fgvf6LTHnAKzaWO2pMvex5ryQvX5P8vXpKSLLN/afdvPbLa+u3Mg/g/b5r1df/3WkL/Iy8gxKjRmt5H3R9HlxEexn0DXuxG7FE3xpDfBUVmp/g9CyyDJo+q4ycyiLXIeyyHcoi1Qz36ypsOV5e7xiIinP9yE/w5+mCa3kuXpD9dFeb/+39uJST1nRcb3egXkMZ3RUPxI5EemBHDCu90THvBuzJ4yNqH15jmslz53gmETl2bbXR53s9pDd7siz2G12t0umPIXkuc22J8p2R+3h31W2uyDPGQU1ydE2w1pttxko5/2yeRYGUmEKbMJmqotNlXPEdYtr7NCW2PYID65HoXOPNC43pmWtUdA1y9Ue/Vs1Jnk98gJ5qJvskgdds2j2Og/Jh7UdsF3HDdobf8kJ/vt2ITyIPzlTbP4UFBXl+Wp/JPuWn9jt6+cGt09e29io9jLnWgf7WttSlhWF+m2L+RvFYdnPZfmZvt/WxlnGQtX2azzWvAblhQ7XJUltZKC8LtHob9Ces9oX/wo9xzYhL5JwZqZb+eghFsX1aimXY/MM2+BQprUOZZoeuveN2j7n9qdR+/VfqTb/cuQl4xnvWjZ6yB1l2Zh1+T+4bA6cGlo2r6BQPy1c2VRviOY+bymbY/MsbO+yCbTjTdqb/xzNDT0bvmq0OdNtZVPkKfPwlqBmJ+K5k/ZyKXHIR7q1/QjyOXjN6BBLm5LEvwdY85/nrfSs95+XamtX0oLOK/dwYYPKIKuzYiXqe80w5DUcaJoRXAaqG4UVNeXVkXyXCuTtfZfvUE2yu1TfoRYhb2A3YabNLm8LPtsRfJcLtanytJa77f64tkvLnMueSDbyJgq1Tn6Ulhd5NqhdjeD9WM+HkHqQZWtXk3QfyceCqmpvRZX5rmt5D7T5XqZ98h9CeiH3I78x2j1X39u/3TN8z3fxfYjDszHV9mxMD9N2ZWjv+wv0zDsfeceom7Mc8ldN1daliaTvEum1UTkE5izXFIe8k9FORXCtztAb56/UDr+A/M5oa2a75CWKfphrXqzXKoq82NoR81pO9KVlvMoGz1vemuA8bzl/zrGdtzxd9lO1H/9QtSUDkN8b9cRvv2ptnu11Vg262Y614k+6vR4Hv9MF+bJPvozVPZmOvMfJCVkuvnBjVhF/oK2+BD8vvGZ5Zbb4V7Qh8NyTj5ONi6R6mCg/S8ZzvVx9LK9ZF4V//xwr/2x29yeGXqc12K1ztbu+oKzG0ya7KpeWMojNP4jNPzgO8w9+45t/kJZ7374vbPSWd/jnO0UFP3qipm3zD/LjNE4Jt+n7/ilwaSD+LvFaU+FpcATsDMfBLnAF7AovgglwM+wGvwYT4Y2WONr1cRoThK/LTje4VXa6a3+NXnAMPAvOhr3hAtgHLoKpcCXsBytgf3gxHACvgwPh9XAwvAsOgQ/AofAROAw+C9Pgr+Bw+DIcIT9L4jSOBx+Un6fClfLzL3F+P/8GR8GP4EQ=
*/