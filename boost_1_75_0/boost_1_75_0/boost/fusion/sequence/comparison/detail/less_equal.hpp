/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_1141)
#define FUSION_LESS_EQUAL_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) <= extension::as_const(*b)
                && (!(extension::as_const(*b) <= extension::as_const(*a)) || 
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

/* less_equal.hpp
2QTom8AO0nPwpDjIpA9KSCYt9ZJMalTq/mPIpAblkZ+4TGrEPhDZ51wmWT4vr2wtlRQqXfgzDY36tkMDAIA5SpdI13n40OBRu2Fyty8qIbrUK9eQWPLWw/xv91L48NnwSknTHkdu6WDgyfYhUEa1fz2GMn0M41Vey6vcr2CqcaiuH69ugP54CwkE734epDwbW/kLnXK9yeS72B240eTvJMGvr5O+FvIqGhPNvI0Dq90Wj2nFU+4xlId4HHTWDuis0dBZO8priaM0W5yIQTfuyiyJeok+keNlk/SkwBN1+0/zEcP+E5tnRPdH4FmgT3iC/gZn0K/A30b4XwPX9fAXpim/BMTdczcR950xRNwC5diPQE8lqznKLGvaMgv0aJFEziYTi9CUh3EYkF2OU7PwCusp/Yk2MdcBPda1m3wKDFKPGc1J/VfehVDUy6GlXr/qyU4mZaiZBFn5KtIA7C8v7aSdY3XmDjZEf4FyJbGWfTTg09HrxJ8JngqAp+Ic8HziJh7pD7BAMS/vLYKl1mIxUW4d6n0AyNkSsW7CayirJ5meM94gbrU2EqphJLQWFwV8qJy1gLdGq+1yN4kfb4PGSV3gHm2CWuDgBZ8jofXzJ5wpnj1BTNGIXjqymFp1dn0bTZsShhA8CpIClvHK4BNRmnPfpSjNefzgWXj+TpTHmrlGQLMWqQUCX87cGqdrWLIWNV87DKyFG/6Swk/O
*/