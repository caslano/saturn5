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