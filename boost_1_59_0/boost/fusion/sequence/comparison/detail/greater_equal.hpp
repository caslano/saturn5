/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_1142)
#define FUSION_GREATER_EQUAL_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater_equal
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
            return extension::as_const(*a) >= extension::as_const(*b)
                && (!(extension::as_const(*b) >= extension::as_const(*a)) || 
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

/* greater_equal.hpp
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
*/