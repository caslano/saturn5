/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_20061213_2207)
#define FUSION_CONVERT_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/convert_impl.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
///////////////////////////////////////////////////////////////////////////////
// C++03 (non-variadic) implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/cpp03/build_deque.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/build_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque :
            detail::build_deque<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef result_of::as_deque<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef result_of::as_deque<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }
}}

#endif
#endif

/* convert.hpp
5XmFhoYxDCpN3lOwjfVWF7vu7ZNYMV0aAuzH4BoDvkTu+62E1oQswjjWm66tN9OW7+CN7PnscFudxrvX6yhkPHRnsYwR3V77fIt8nnCB9nm119+36H/X32fgMQ7CJEnveElvyBx1+ezM3HxJbuDj1XundbC6LvrSRmifr5bP5dGeebfGT1rs2vJ5+cbU1CPvtnilZ5eeHs+8KQ6TZ0slPYckPclF6vJKyat33pSq62K9kdrnDUWe++2pIs+0viSfn4jWPr/ptfxPXutrrZcDz7HEI+U5iYMypvc+Qjj9eaq0vGAgYQ6dAPJYiaPxXC2OpyRNl3h9jvf6nOn1ebHX5wf1z55prpI0/yhp/taVZm15ZbBhEh1Ymn/yivOieZ6fh3t9nuH1eZXX56f1z55l6FN5X/8e/tgWn8UJLFPmVJdX6g6l4jDwcdv1MmSowywM1+Y5ZF4X7zH1SeNftThDHpGy8rtCz89tCj3PIdd5/T3L6+/PeH2+crb+2WNs4jgZ212pyumHkbiDPIiY750H/Cjk8aMj5e7uxjXXoZY0dr8r4fWF2rgr2QUF+QWSB2sb++bV5sa+eVXe2JVXyglGq0/doc9TUma35Nm0+WkhxmUt2fkyP0GfPzOjWKmilnXHm7zbIBntMm5Ia/mdS1d/s+wOvQ5br6MtyHYU2pyu57iO8b01TamnVcrTDe7xVuL0dzYwNL6So7L8QJa9m3ABC/YxLK/8Tu1Un3Mr0iMwvoOgsyx7bx9t38bw2XgemiSfd0v577xA+zxazjsTFnguP3eB5/IXLdQ+57nKzkLPspTi9XmmfD73XM/j67iUrRnSJjGRMJ7vlCxyly3aQmzsQDm+ai5T3ZAypR9r81tpzxcan+l7NlrqzuW4Kicu47YckM+SVv38lSzj+59DCFO/yzr5TsvFktZMTl8BXG/IO2n092wY86Na4siRMRMzCMr5plI7NosKrM5sOdhO2/lG2ebzizzPFZcW6ftPb18obeB/vGnz8aP9j+NsPl6z//GdzdsF6t7uYD6Ouf9xsc3bR/y1X/hvf/lznDK/ReeNPe85+/PQm6MjGuT2f4p8c/ZR5rfst+mKmLzGmYdf2Pnlxi1Pb/Xf3mHejuN/nHTzccb9j5NuPm573cc9r+s45v7alS4bqsw/sT5twADb1UtCi7Z/eFtRm5/1/rpc7/sf1/t16a9biU3wDXSNwZMu37PK94xj8DBUZUlr7IGdMRKjsCfGYy8cg4PQgrGYhVegjIss199cC5uMixwi64/AC7ATdsWLMQY7YzJeiuOxq2G99hrW+06ott4f8QI8gV3xJMbgT5iMp3A8/oysl0ySa2J8T9bbHJ2y3htkvQswAhfiZXgjJuEyzMBSLMGbcSXegqvwVrwPl2MFrsDX8U08hG+h7Be5fuV4NNkvfC5pjgUYiQ68Bp04HQvxZpyNm7EI9ynpQH39ct34o8n6r5L1j8Z+mIQTMRkX4hh8CMfiKzgOv8WZsv4dBLku5HpRW3+4Og47k4xV0xa/wItkjJpr8CvMxuO4UMaoWY7fyHjc3+Gr+Dc8gt9jmIxJ0wV/wj54CjPwZ5yG/8Q7ZVzpTUjCGNsGcAc2wWexqeT/4VD9mo5rPS39A5V9IffaHViuH0bgYLwY47Ez5uIlWICX4lzsikuxO96Ml+EdGImPYk98Ansp6cAo/Av2xRMYja2IeyAm4GCci1dgGV6J92Ic7sOrsDlpHobtcThG4kjsg6MwFxOV7+G1uAVH45OYjB/gGCUdOA6P4yQ8ixPL9dga07AtTsZuOAV7ogWvxHSMwwxMx6k4HTOxALNwKWbjMszBTTgNH8PpuAtn4B604QGciUcxD0M=
*/