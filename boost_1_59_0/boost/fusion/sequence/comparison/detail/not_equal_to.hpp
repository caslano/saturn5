/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_1141)
#define FUSION_NOT_EQUAL_TO_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_not_equal_to
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
            return extension::as_const(*a) != extension::as_const(*b)
                || call(fusion::next(a), fusion::next(b));
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

    template <typename Seq1, typename Seq2>
    struct sequence_not_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            return true;
        }
    };
}}}

#endif

/* not_equal_to.hpp
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
*/