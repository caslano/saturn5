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
WC+yuuwxzWzE8ezNuDijMM2JifwdVFwoGUd+PLIXU+5hfvn7KAPNftW+nOpWpEnjjqN8vPNKnpe3Dx6pHXFceApDIQVHNEovbI1PM7nKf/L3RlkLTdx5AvtvYj0b0di0v4fatC/jDHR+pD/qxEgF2X7nT1YTrKCcuQPjNOdO+GxKkgYZtf7VWDNRJBLPoYVuEU6parkqBLPRjXH46SiR/hDXhkgN0MZOtB+g26eNMthS1zYo7BilEMj9u5W/fILfz3+2E79/kO7b93lZAwrmatSlodtvGUu+9uVHcbJC3gkWFTqzn+BdLSZVa339iu3cfX3ZJL2v08diXzfrff1zf97XK81aXzOz1tfOpQPTXOWqv0jr65+PU0T9CWdd6E2sF1Kt9z9kNv0iCvM6QaNbfkfhWZWnqQ3/rfB6wINmnrycVi1yyqcRnTxmTh50w4PGtsJyPPIM6iFy2yZnGk1GHoJGHtIaGcgb6QyNfPQArOqvhHfF2rvU6Lsgvktx5j3Y6E+G2z8/oIHrZl2k7JR3ADx/kpvdbIObNx/EUDFbMJmpcyvqHJgrgVadnxbz3tTyu77spYSTMFjaLIMTDVDxdf3ZV8k4GRuhwUtiQ4PzOfHwySPqCr6e3x+93EmXVGAzXO6ABdNG/Btre4H5Js0TLEmPlVtuDGTHo5ocwuh8fcrq4f9++K8oRSejzE5JgTmzy8XA7BMbeKKFHap9
*/