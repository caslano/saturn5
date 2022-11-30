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
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
*/