/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09242011_1744)
#define BOOST_FUSION_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                typedef typename std::tuple_element<N::value, seq_type>::type element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
Q4a7S8YDXa/lqzE7JgiRWD1mrg/PIiZjyAnLZLiD7pD5ZMilYVLYq4iHlJ9tJJn8BjiZOJ2bg/X3/m+w1ZbznntAZlPCzDvOMg532rEgWPi+CT66dNkIvirRGLAV6ZV6I6+1G9ONZhV91Iy2kZUbFO4pHpt247C20vX+yFzpetzWUboet3W1joXsE9WameVgvibkGM0aA57birhZ358xWxuxPMvgz3UBoyOMqSdkflrIzaxQI6fVocTfEHJJNvHTI95tr8moXhA/oxef4effmOQ0cKK8nRnyejZp72w4K2RZTX+eI5uzEzarxYrnvgIbrrEyrntzwNn1mO8KmXm5mS0lrelGdYp9ifmuyK5l2hNeb3mjODSw1Z5mn7wtsKXiLD4bbMBxvj3knXbDjxFzXtpuVZWOesrsu2C6O2X7mHdqOxzI2rLncSqmz7B9d6CbeVRVdNhvGtiEdeO9vTj2+b1PcTdtqQsZvn1/yi4saOT1A8qWy5FGg5SnDyoWuwpzXNomj9vThwMe5vmcJJf28JEkl7nfjwZcugn2xcdCnq5nPA8W2HK3wewTzMzFFRi2UWfG5fLJkEVfXTkvn0raNZp27/unYy4/UhDGubENflBwGJ9J8eBdfl5oQxWZ8/LZiOXJvJyftJO8fC7mUV4uSNpIXj4fc5cXN68mNvg0xPpFoteqTQqU8n6x093UpfPLJY7pTzw4j9QxOVvsUtHq9rfHZU6T8czlounPOcS+6Bjecu2WW990RcDMkGONnou50vFo4QPxqzTnOo/ajr2Xmsc/33juzbfJmjV4xc69KS4/8Zhd4zH/uWs1C74lXyfM5KVvvIvfZdc7Xe4H+opoca+LuL7q2fhxfU1Yq9Yp5gZZ/7qvF67nfZZOD3tEzMsJx+iR9Rud7p9Nc5OnrykyS/o3A90kguL/ltOD3hbl9W3FU2X+HcV7lfl3lU2qzG9WPCzzWzzmP/c9j6Gqg92qWZCe2zymmwHz2wMuzYDXpny/F69UJ8xnpcx4ybz5Gk0TqPvW+wP3DH5awn8/JF33rRONbMpd/cBzfmTDX7J5+TruwNO6OT2RXkVgdygWjsXvVEyPxX+idD0W/6nW6+NT1v5nStdj9J8rnWKF3+5SOmX16Jl2q7gNrbHG8xm9rXFuwC/CZ2IX88sfa/ru/r/sZ/jePG1rTrJjB+KcVM0acsbyvZ6eV6odewsj96G/CniryR2IOy9V8+LiHyTQnZeqeDhWvM9jXVcOv1W6/k18v9ZNg+f8MfudZqTTOWHEHkiw7gSz38fMeI7ZgzEzsXLZP6RZ/v+V/cPeM/+77P/wf9nPUHr+GNi6PYBZPQ4f6Xnk/35mhvd1hvadllQW1Ic/K5vcrxA8L+nz7hTK6C+s4+XUqPcVv/TBHtOs0A20fd/jxPiXaLcx1WmgfuZ49omCDw6ZzyFjK92kHtLyZMjwXeapQNdnEj1dsOGFQ8Ml6rkoDc94Gm1Y9O5OfdZxrB5FX/lX0WvT9UqjmH3Kal26fNXG9zdnI+ve/+5rxcN8l1+s262O9Nw/HXfT9HwGrOgyPyma8S1NxZH+n0Av97P+nK+XBmC/wQs8fbR/eJD0DQPdhEO+f57S5ZoB3NOXYm6FDD+/UcoGezlfELBpWq3bNBR7NT1OPnSLk2393kRsZExI/mG+aYqTn5hvluLkL+abpzj7jfgWKU7+4zy80HF9o43LBvloS98Gl8by81ulWODjF6VscmYv9pi/x2Jrj6EOuqTx89uENm1KGrGXKBaul9jWY3LuznaBbvoqiRHPvtS3marmHep/t/d0+lxPg6vVmXIofhfukLLtjmtTiutlnp3cb7Oj0nHNBaV/J1+fMQE=
*/