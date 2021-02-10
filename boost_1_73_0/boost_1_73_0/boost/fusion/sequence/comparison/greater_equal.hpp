/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_0432)
#define FUSION_GREATER_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a < b);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater_equal(a, b);
        }
    }
    using operators::operator>=;
}}

#endif

/* greater_equal.hpp
h8HgIiDL42O7f3HZZaKm4p06zpQkNssuC//xoAuC8v0SeA9I35gMux0T+jBip/gatAUF9xSo8OL2+C3mhcIWH4rGj93uNd+JoQ39VdCDUbd/wQ+MuOWjvBz2AW+uzedikhZLxWJEA3RQq8UZ8onzjqDX2MEzOgeGf+0ARBO/VAydswbvnaqowzSIHZs/lMZ48/LRPji26mOngT565xoG2F1w1KRgvcKwE/3sY5FiNImQb/BKNKOEmpmafmpnVSU8vkanciGp+RuRpDwK9OHUS+65rV6zXxH1Rsk+PD4iRqXLgOrQqQBT4MQ4nu6uiH85GCivFyQ8W/M6s1Ltq855G43b425wDR7TYHgF1L7nepf1jceDwfv2aGyHdrXSHENIVDICu5my9TObnOgcleELcy3bPFUqoOEOGyVNF1N4KIQ38FA+qqCzwgYhyCLnvMrojTK2LLk0PWDoW3ewXLAMV4EFyaZcaW/KBbSQqzWZBqUqH3iEgpJTn/rM6fvaQF9SylFY6ETrmcRUtsx+YYz6NjobDFCKg7/tbl44VdSE/6040VndU23Z1AKteyhRi88BYNZI8MdP3/18ZpeDEFNe7QTVIVbXNXDopADWslQl/Ag/mHnxQ2kyN3kFNOwsoG6m4JHB5VQnrHK/3J5Y
*/