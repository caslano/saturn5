/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09242011_1744)
#define BOOST_FUSION_END_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template <>
        struct end_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std::tuple_size<seq_type>::value;
                typedef std_tuple_iterator<Sequence, size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
6bYRzkDarjCjcAZjHnbdZFfqbYfum8eKC2K7VBdOYS5M20oXjjJbFNu5OjIUM3f2ydGWVWu1bIb2oc60mnmWqz1Qxzgb8wuN7gfpdloTE64tLwan2/hqVB34gG88vyTBm61mLQMfjjmdhNbF76+lPnd7kkY83f1wJ3YsGCXEVAjd3kY1Q0yVXPb3lD3eaZnHKcwx6Py9zmWB2DKfmYmVRt2soqXwloPRfAc/RvpxTm9PcdfIYa1QOg6Xo+RtY9hKyxr14rcx2b9ONNnxgHQdr1gjz7tZmx4jdoJlrWZm3lS27VDaTgQrlgvnWaVr97u93urmgW6Wd4rSoofg20rMURuYn5Ti7BPi1ZA3cirwDOfFjAccaUdbYJtaZCP5s+msBzZyfzn7Jou4rA+eCJi+S31SWD7DqSJ9ldbVnshGpLuqT8+drLna87g60snJbn/cVMTlzOXpmM20zfrcWlavVDts04xsyAMmZW3X/7Zg4zoN+3UG8cyEnHpfbq02jFMiG2QfYbRjLu0Vec2tTZ4166ZMaJgI1glZU8aQ3YBxC+S+fA0YDllc6+IPzuc61dmZD9FTGXkKSaQ41lreLbaLr6lNtWrut+66go2UhsvlxZXBodGKSQU9c1qgG6e68esbFBsaHhrTY5DTA6bzc0bIcHvcRGOy2P7sxlVvVHaLF+GVjPDPDFirKutuzkow876YdPORPscxmpiP9Jh853mzp+NIsVOb+LqPfYi+TcOUUNv+Zn2rx2R+7G2B3qpzrcpR597ei1PFYpt3JGy6eXUSluTzd/aykdB43jKw607TBuHczVv6vJ112o1sDfvoPT7LUz56r2+DrOJs3ATT7ef9IW+vquar2L8fUKya1/q6zQbpH9R6J1trxyEfEr04NLO4qMyEx2F9WBh/Bs8z0s8JdZwP8RHRUY35O+ZHlV5vcBgfU9rkdKdh+/iPR7p5G53M7BMxqzcmJoh9UjGTB7Mesd3XwF7yTynG+eszWeU8flqYt0/y3ECv0Mx6i9hnNMtN5V7TqNn2eF7AOl363s73vArzLnjhjRhyD+L5Ylf8wjZjA5xtq/R8tekHshm7XIPPtvU5+gnsF0yxyozbd3NhwLszrF/k6fQy5HNtY92dz3SJx+T3zRc8Hf0C0ndpwPLgnKHLPC7jsssjndbb8Zyox+T8rSt8faaFsdeVkS7fOq8KWDdfRfrVvm4KHHe4RnoxxqPj5PkO14Cvaky4OaFrPEaO4Ptbfb3b5KeIXecxLCJCeNf77LSs3SL9K1o3OyRr1Q7pXw31GR5Hfc3Xm+aty3OgosuhyS3uE76hmOmL+qo55/+GQO92JubZenyjZkanTgx5ualgY+ZIQbt4DPo3ta7mBL+ldTUn+G2tqznB7xgdlxpX+LZqzuN3Y72oUPTMzYaZc276RvpH+5eouG/Ruor7e1pXcd/KugqG+8/btN7gMrpdafob4PdJNwe6q9S4uUufue/FP/R1Nxb6UaGXlvB1AUWxIo4fhzq/nOiZOzQ7td2w84J3RrrM+/+EWbSP7adK9/a9KX2ZOn/p56zzsev0QYcSTe3xrpgh4cx/EXJJJM9rgo8X51PLs8TuAatnZkOKGWONV2urbVp/6dhq/gkI/V6rt9xHWL4blXW+8HC5PT+TUkTP/Rrc/Dio8Z5GzHFCRzGR7X1O43sVbB35rdYHF3l7W+/3WLl/hDe2mvO4cSdqwCsjy+abZabEHggYB8zh/l6z0sDIMSNuyyvxBwMu0XK8D/kc0fJ79WHN0os5eG+c2OFOAfbTH0N9Hof7SKRXRkaHlldMxFwg8POflJ32x5+1Ljmi/D6q2ajnZ+J/CTltIBZ/PBZwxMv75hQ=
*/