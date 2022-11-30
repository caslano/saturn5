/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_1141)
#define FUSION_LESS_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) < extension::as_const(*b) ||
                (!(extension::as_const(*b) < extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less.hpp
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
*/