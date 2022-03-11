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