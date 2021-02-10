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
TEUHaB3whFag7zLUNvJyijG0L8ejTx13K8M8quwfPNMihwulqioKNVuF3ev355H1MxTGSOXgpztdnIazhjvHdgTosXitfiUJXPHH0XjkrhervFYWjA/1ivHv7eul7s9eMAJRt1yaCxeLAtls9lOi1QNmO2Z4Uoatbs7ppIa8aH0eLtkXJD3FcXEuLmL0WzTX12JaNYxkeIHmNpVJrN2526LLhgrYlclU2/RPFTNSGqimY42J5DLLsIukY3PhOTg0VekpNmMZGXaWYPZSBoPmvhlW2ZeL/igYdYefusORG5OYopcKv/fPa7KLakhuCwzGPdkBil5/3B2+b3e6vwMcIISxPMf6zzvAcTnoYNm06z//jnD85Rlw/OV/A4dlHWQcTUcq9VyZcZRprJLdtDtkzXPSUxgS9V4ZDliFi2iqg5Pt0Rew0z/0OkH/5updd6ht9HvJlQPcUstokxfLDflRaLdyjpT1h9UMTv04T415J4lsFlG1MVC4jbIyrhhGj5lbzkkjb104l3RxtMT06vjeaYmODLXc4sg0Hx21YjY93s43WFx1pc82Dj216LQjmVttZYStaobTOm6ceuUC0yxnNDHqaiIYdOvht5xWHPNBhTWVhLLYnSwktwAsm+C1Zz4Mw2ORBbPsACupSSAp
*/