/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FOR_EACH_05052005_1028)
#define FUSION_FOR_EACH_05052005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {
namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_linear(First const&, Last const&, F const&, mpl::true_)
    {
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_linear(First const& first, Last const& last, F& f, mpl::false_)
    {
        f(*first);
        detail::for_each_linear(fusion::next(first), last, f, 
                                result_of::equal_to<typename result_of::next<First>::type, Last>());
    }


    template <typename Sequence, typename F, typename Tag>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_dispatch(Sequence& seq, F& f, Tag)
    {
        detail::for_each_linear(
                                fusion::begin(seq)
                                , fusion::end(seq)
                                , f
                                , result_of::equal_to<
                                typename result_of::begin<Sequence>::type
                                , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct for_each_unrolled
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
            typedef typename result_of::next<I2>::type I3;
            I3 i3(fusion::next(i2));
            f(*i3);
            for_each_unrolled<N-4>::call(fusion::next(i3), f);
        }
    };

    template<>
    struct for_each_unrolled<3>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
        }
    };

    template<>
    struct for_each_unrolled<2>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
        }
    };

    template<>
    struct for_each_unrolled<1>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
        }
    };

    template<>
    struct for_each_unrolled<0>
    {
        template<typename It, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(It const&, F const&)
        {
        }
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_dispatch(Sequence& seq, F& f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        for_each_unrolled<result_of::distance<begin, end>::type::value>::call(fusion::begin(seq), f);
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::false_) // unsegmented implementation
    {
        detail::for_each_dispatch(seq, f, typename traits::category_of<Sequence>::type());
    }
}}}


#endif


/* for_each.hpp
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
*/