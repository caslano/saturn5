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