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