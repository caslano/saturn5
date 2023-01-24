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
b3h69BYG1fCs6C1w1vCc6G0D3OZGbxWX4wQzs0Zch6It0bu6tLRU6I2HdEymm+V4DJFtYttDtUmiutXJtrMvxFBt96Y9TketmLEPX3SCS1aTsd2xm+1yWraFalNGWZLT2N6RFo91nZN97YJn27o5drssYWfGV2xXqDbOyfY5tjkde0VLrYttdmV87mI7sVqXo8ppCYnsS6g/6JqfUa8DIMJ7dSsAgc2ynVqj28WMnQ5Q41NWPmMzQdMuS7JNa9U132Wpc1kOiaxeZDXQPoDlYicBioxmEafsUwCGC6atbUYTCMsOp6UFARHZDt4YkOt6qBwap0edRPYPeNq0J+MLBCljh2O3yOqg6YxdiLTI9lH7ep1OCzYtQp2sOlSTArU46ukyjv46tooZmx0hUU6+yMnqAHFomdWxfdC01sFfsjqOK7SeUQc9XBPTw/Vt2tpO3SxajrIakX0N+Dn2w23GPwHCjBrHAd7MLssBamYX26s3gyShNjL+ARBC4V3Q0PaYhr5o1ZDLslOjJ5YKFs0ngiqO3U5HxJXxM7ICsoojjA262DanJcy7dJvI9uhtZuyDex21bdgi9Ge0SWCBNm3u0NpswXLsMFLP8R20mdFAbOB0HOLNATEO8ebqxGhPZuwVoz25TcSuhMawJWoG4bVA+X+IlhASjO0Q2WkARW8eoHP8lnGKWCAOqbhbo34L79QazjWshtVHabcH+E5r
*/