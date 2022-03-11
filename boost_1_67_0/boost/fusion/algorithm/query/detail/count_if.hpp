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