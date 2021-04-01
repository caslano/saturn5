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
Y/lZiokZhNPwrIyup9460oEX9E6gDNc7kfXElCBKiw8tWEqoIszTebMWHuF41SaARArw2htbQkXhifudKqKEXAkrg8/hEzStxLm8XV0bIU0pFXCK3BQAOeXCwD1O1bZxLb1fZOTH6LZH4qdS9JjX9ex2E45QmwPlXtVpX08EqFGMpgNLExj+45naN319iXgCB2bYXHEz23mqgJUL3FN7IeJ/+jDjHaLCt9zg4MEpntopIqEy1bB7foLFNyuptJZ8fvLxmLyggBI4X957b86oX0zDukOL3BxV9wsYQWzKlspjQbDOzJEmX3wVs4VXyMuyV3SiaQmXEwoC7o0i1TloDs/rYRC63ntZlk7u8KVSHY0Bo3EQKq5aSuF1SBPKZrnw99TlMpbFVEjfhL25JjbSIofBAuP9NGHkBqSQV3YV5vqf4qjdNVdfNKQrbyb5yAQJ6VSREiLbXem8uKASd0h/ESPIftAXyeHiHcxQyliiv5kutqtlIl3XtHp63PnDE/wdHMUlQCDosLjb21uFqRQyKL79IVNtPBqz1dEARSZ/N47IDxEchD6aS0ANaA==
*/