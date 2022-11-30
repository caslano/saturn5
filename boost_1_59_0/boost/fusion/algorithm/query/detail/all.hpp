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
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
*/