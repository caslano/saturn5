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
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
*/