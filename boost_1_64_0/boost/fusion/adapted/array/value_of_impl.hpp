/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
/oMryi3406fcZfmUZ8BzlKeRfy+XHzyi3AG3wJKwv0nlCrit3AeecvsDTytXwR1hnr+ivMo18E/OzvLdrNtn+cBiAFeVa8g/R3kQvBc4SXL9E+Wl/QLyBPkUcps8TJ4mn0D+lHww+QfyoeSfyKeT+24Bn0HekHwmeZB8ovpDPos8ST6efCv5bPIU+ULya+RT1T/yEeSFb3XXa+AfeZJcIx+l/pBb6g+5qfVFHic/Tj5a64t8jtYP+Rhy5TZ3PQvtSz6PPId8sdYXeYLcIp+v/pEvIc8lH6v1Qz6N3CWfpPVzO/g48iq3/7X58b+YWhjv8xXj410dvwsKS/2SpSYL/kG5JvZZtePmX2GpX+UGuF+5Bd5LeRI8otzF9ieEOX8ISzZhzvfCslCuIP+UMOd7+C/M+Qb+Ozu296nzB9xVnkH+n4Q5v6J877n5FOVTroLnCHM+RPmUa+CG8iD4bOUGeK5yi/4K8/gJ/5Qri8A/t72F4N/77vgkLMVWnoZ9Q+UaeC+XHzyh3GV9O14Q/gnz+In6VW6w/oR5/IR/YEn07wP1H7y0MI838Fe5Da46O8rbD5YErilXkX9QuMfxAfVP+zC5RR4lX0U+mjxFPoj8Gvlg8g/kEfJP5Dq58qGbn1H/5EPINXKTPEI+hjxBPpJ8NvlQ9Zd8mPpLHiNPk8fJHXKDPEM+irzwR+DDyX0f/X/mx4X9v/R8d6FisdRK7N/gmnINPLLUSr+vvqoLrlH0n+OZv3/Rgn9yDPvCJ+j2YV9FmNdLhEV2duRvKA+CJ5Ub4LnKLfBrYMkI/lSY8yv8UZ4C951IngZvqNwB76XcBY8oz4AnhDkfFHy2cgV8lfIgyvu4MOcH+CfM8Q7/hHl8gH8naX2A5whzfoQ/yhVsv6Xc4P7BYgDPVZ4Ed5Tb4BnlKXDlZK0fcBUsK4Jryl1wQxjrL4r2Up7h/snSE1AfyhVwV5jHN9SHchW8bEvrB1xVroH3Esb6i8If5ZlF4A9YEuxTwjx+of+AJeOi6M9ue4uh/56i21sU+1fugPdSngafrdzl/pQbLK8wj4/Y/qm6f5ZPuc3yCfN4hfYW5vEc9SvM4znaV7nL+lSeAfedpv4sivYU5vEI/Vu5tSj6k3IF9mnlNuvLrb+YsKTTNf9i6E/CPP5h/CtXwXOU+8GDyjVwAywGtqdyA/y4cgvcAUtG8Iwwr5/DnzN0/4ti/CtPcT5SnqY/yh3WDzhJB84zD8rfhP1+8rLkNrmfPEQeJA+TW+SDyHPJB5M/JY+QZ8h36f7HwHVyH/lu8obkQ8h7kQ/V/ZMP0/2TDyd3yEfo/slH6v7HwQ1yhXyU+kMe1fogN8kN8hj5bPI4eYo8pfVBPhosP8DHaP2TJ8hV8rFa/+R7tPzkm8lXkW8hT5NvJXfJt5F/Ih+n+z8GfLzun/yIlp98grYH+QGtD/KJ6h/5JG0f8snkx8n3qn/bu/gY8x3tp6idfKq2J/k+LQ/5NG3PCfDp5FXIt5PnkO8gj5AfVP/JZ5AnyWdqechztTzks7T/kc9W/8l3qn/Hgs/R+iafq/6Rz9P6JZ+v/Y18AblNvlD9IV+k/Y88Sf6BfDF54ePAl2h9kS9Vf8iXaX2RL9f6Il+h/pCv1PFAvkr9IV+t7Ud+SPsjz8+u0f2Tr9X9k68T9p+PuF7bi/aH1R/yDVo/5Bt1/YLLVKbfl6pn/cn+Ul1w1WI+xfryA7yXcg08ojwIngDnjueFfZL2IfJc8jB5+k/6238B19tmCcwfXNbmLIHjG5czA1j278l8XE7vSTvz7Wbbg/4Xt/ebqbXgksX8eZGr7yULWbkBnnS8UMFtsGQEPw6WjODXlKvgT5Vr4B+UB4U=
*/