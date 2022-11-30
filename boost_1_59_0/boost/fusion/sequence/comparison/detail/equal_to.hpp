/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1142)
#define FUSION_EQUAL_TO_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_equal_to
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
            return extension::as_const(*a) == extension::as_const(*b)
                && call(fusion::next(a), fusion::next(b));
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

    template <typename Seq1, typename Seq2>
    struct sequence_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& /*a*/, I2 const& /*b*/)
        {
            return false;
        }
    };
}}}

#endif

/* equal_to.hpp
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
*/