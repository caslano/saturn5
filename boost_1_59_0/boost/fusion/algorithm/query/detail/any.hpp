/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1229)
#define FUSION_ANY_05052005_1229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion { 
    struct random_access_traversal_tag;
namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_any(First const&, Last const&, F const&, mpl::true_)
    {
        return false;
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_any(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        return f(x) ||
            detail::linear_any(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }

    template <typename Sequence, typename F, typename Tag>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f, Tag)
    {
        return detail::linear_any(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct unrolled_any
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it))||
                f(*fusion::advance_c<2>(it)) ||
                f(*fusion::advance_c<3>(it)) ||
                detail::unrolled_any<N-4>::call(fusion::advance_c<4>(it), f);
        }
    };

    template<>
    struct unrolled_any<3>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it)) ||
                f(*fusion::advance_c<2>(it));
        }
    };

    template<>
    struct unrolled_any<2>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it));
        }
    };

    template<>
    struct unrolled_any<1>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return f(*it);
        }
    };

    template<>
    struct unrolled_any<0>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const&, F)
        {
            return false;
        }
    };

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_any<result_of::distance<begin, end>::type::value>::call(
            fusion::begin(seq), f);
    }
}}}

#endif


/* any.hpp
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
*/