/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
GIlvrMQXpYuvqI74Lpf4Jkh8V0h8EyW+eIkvQYsP97Pn+G6W+G6R+OZLfAskvoUS3626+BLqiC9V4psm8U2X+NIkvnSJL0MXX3kd8c2R+PIkvqslvmskvmslvnxdfL4HPd9nd0l8SyW+ZfBUeDccBu+BY+FyiS8OyZf4EiW+NjDa+Xsq9t2XwCHwTng6vAuOhMtgFLwbXgLvgRPgcv359L94/t19UH53H4LecD10hvOtI9xqCfeAhFsDne/dUAk31OS920/Kpz/0hQPgEOgPneHz6wjfUcKfKOE7SfjOuvDldYT3kfA9JXwvCX+SKzyNfc/hj5bwXhK+jYQ/Bkq5Mb/nudzulXJbIeV2H5R0ZS6OtEzSfVraZc/AnvBZeCp8The+qI7wGyT84xK+VMJv1IWvqiP8KxJ+s4TfIuFfdYVnLslz+G8l/HcSfp+E/16f/zrCvy3h35Hw2yX8Dn3+6wj/qYTfI+GrJfxn+vz/5rnef5Xwv0Ff+DscAv/QnheZd4BjTep9pLTvQmCYfNbaGRJuvNruNb5Pdko75X3YDX4AB8FdMBLuhtHwQ4kvlPD7JL6/pN9Mu4TxALFfL3pcDPvAS+AIGAdHwUvhODgBJsIrYCaMh7NgArwBJsJ1cBIsgUlwA0yG5TANboHp8ENoh1/DLPgjzIZKfz8H9oKz4BkwF4bB2TAa5kE7vBrOgtfCG2A+f4vgXLgCXgfXw+thKZwHn4M3wtfgTXAXLIBfwJvh9/AWeADeCn+Ft2nvTZljgL1N6jNY2u2nQ194hi5ckYQ7y8N90BWGwDN094Evsk/CnYoEtzDaIz9bu07G0mHvQ1zHuHe94iuqZ3yVct0AD9e14cY9uNjL5r3EyxaExCBpSAFSPd/Ltv/TVrbyHC9bzSzsYuO3dUn97KmXZWKTgYZxAbIacdpvmGB32XDwpcFstxMOCR3psukQ8DH2Ga7E5jnitO8Qyv8pXFOA7A9w2XpIwr8GdhjosPngC/vDEGQB3xUjlUgQ/hPws2VxLZLL/37QzJ570Sj8s8gLLOdzXhZxwBo+dziL7/lchuxEfkeC8AvJRn8klv9zxMbEUliA324GUfchrQahD379YYlyLcwVGxRx5LkKeucQBr9QmITYQgnDZ1+Yl0OciNOGfBR+VXA9fgfhVthpsNGOxV78imEsnyvgvI9dduZ9ZqAbfvuR6j2tbJ2uPUqzO580g/zBPLgY+X0w6cD+XOM9mrT4Pxj6BCIz0Z//7UgI/09AAvBfzOd5/L8ccdqtL5+p2a7nBYJuSlzIaj7vg+WwUxhlimxXwsAQrotFSj4mP/jN4/9o9MjnuyJkOZ/LYTXSJhxduSaJ77fj324I8cL++LfJhXwOgGb28GPxr4BR4S67+BPC0RXR28dfymc/hVy/E9mHhPC5BP8KxPsqyoPPMTAHVn1MXPgn8blNBOUCA+BydJynXGdiH0Rvb/8gnztEEgapuArd8IsQ2yG2YegPS5BKxFaFjvjVcJ0fdNoWaTOmto3+oNkuWyMx/O9bTNnCYiQKv3KYBN1t+FfjX4B/MbIVqdFslBht+/vwud0c8hWE7rCU/AbjFzsHgbmwEMkTmyal/P8M3An19k0q8fPJc9g5CVLI5ziYh3SKIizUnxlQyudQuBsG8j0dBO38AD/+j8MvCubCQiQf/1w+l0SRH8WPzyV83su7rt2dXrZAJAaxI0uRcqQGaXeXly0YmYDkIUXIVmQ/4r3UyxaCJCDzkGJkK7If8VnGuRRIGrIYeQapRtrdzTsYSUAKkBJkJ9LmHvyRWCQPWY1sRfYjPsuJC0lDFiPlSA3S4V50Q1KQxUgpshWpQWwrOPMAiUFykSJkywo=
*/