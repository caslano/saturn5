/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_0432)
#define FUSION_LESS_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/less_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_less_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(b < a);
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
        operator<=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less_equal(a, b);
        }
    }
    using operators::operator<=;
}}

#endif

/* less_equal.hpp
uVOebgYkVmBz3bDlFJSpSBHEnbXAOG3OKJvPx7XILrUA128Lli3nSJQBG+zyWnBknZs47TGC8cOJoyPUCxCauMIFwosQguGElAIJTHMt4aHPrd6lIs2umvwArF5nRJ4X2T42cRGgxkUyIDafijEFRbLjZ5ovMiIZdaI816wJZAa0DANSSE7ECijJ6gih/55ErTEiEs1vQ6KMoqUdkWgbskxU5ANKu5dxQsFwhMG0nJDaoU1oIA13BieCdImT7zEDZVGqfQPC7XuYAoAiKP4zGrQZAIgGMwDgsArEm5MkAaKJ45iVLeKo6Gi1ptBYDR+YNmAa0QRC0QpNItQRzTgiI4ModvQJhXnn04Qi4rDTsLEsIwJthMGmDyDvUkQlpM0h7DTNKWLGGT72kDEdLSjeOZGI8RBwLhJA3oOs0yX2OcTAmKgYcKKywEmzah2AvArp3R1pxOqbaHJKgkmKyIGzD05WMPu0n68AncHBKL8t50NpBSk2Bxy7YRKimYs6IDpnwfREc9PCKbjdxYpWM+9Kyy7z4/FO8+9sTvMDyeY7Us3DuzrNj6c5zbf2DCbqcZOysrlBlJvS78x1s+kFbvaEFJMtOxpHL7pX7jjhNlKekkkg3lEZuc7DNuMuPcb5uCsznfaza1V7r0lm8lO6tLxybmp+9bxkWVKlSbtLg4PHRSylQYeWjdRH+SJzovGgPUbQppO8Jd8ENwMga9TC
*/