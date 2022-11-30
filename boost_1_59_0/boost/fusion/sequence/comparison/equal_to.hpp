/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_0431)
#define FUSION_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    equal_to(Seq1 const& a, Seq2 const& b)
    {
        return result_of::size<Seq1>::value == result_of::size<Seq2>::value
            && detail::sequence_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
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
        operator==(Seq1 const& a, Seq2 const& b)
        {
            return fusion::equal_to(a, b);
        }
    }
    using operators::operator==;
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* equal_to.hpp
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
*/