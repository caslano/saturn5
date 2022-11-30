/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_0431)
#define FUSION_NOT_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/not_equal_to.hpp>
#else
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    not_equal_to(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return result_of::size<Seq1>::value != result_of::size<Seq2>::value
            || detail::sequence_not_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a == b);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator!=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::not_equal_to(a, b);
        }
    }
    using operators::operator!=;
}}

#endif

/* not_equal_to.hpp
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
*/