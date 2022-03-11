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