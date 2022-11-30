/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_1142)
#define FUSION_GREATER_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater
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
            return extension::as_const(*a) > extension::as_const(*b) ||
                (!(extension::as_const(*b) > extension::as_const(*a)) && 
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

/* greater.hpp
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
*/