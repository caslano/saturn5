// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    //
    // No more limits set by BOOST_PARAMETER_MAX_ARITY. -- Cromwell D. Enage
    template <typename Parameters, typename ...Args>
    struct match : Parameters::BOOST_NESTED_TEMPLATE match<Args...>
    {
    };
}}} // namespace boost::parameter::aux

#else

#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    template <
        typename Parameters
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename A
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct match
      : Parameters::BOOST_NESTED_TEMPLATE match<
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, A)
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* match.hpp
+z0WwW8xEu9gGfwLVsKfsBb+jD1Qt3F9Q1e6Seigfyw6MQ0/Z/hG/BO+g9fwOjZHV4Vhf6yL1yjv5vgNtsF0XIk/4Bb8Ed/G23gEf8Iv8We8gjfR6cf1C/3wVyyNOulXkP7K6G9j/8C82AAD5HhPy6wnhE3kfJ2PLlXO1y3lfr8d+mAHzIMdMT92wiAcgsHYGQthVyyGPeR80RfL4wCsjYOwscx3EwvrmfVXmFfO25F0AXLefswn43qRiEGYgnUxFR/C5/FhHItNcTy2wAnYASfK9XKKXC8fR/X7HefjDFwm6azC2fgiLsbd0v8qLsH9uAyP4Aq8iMvxzzL8C+m/hWvwJ+n/VfrL6NxvYl3chE1wMzaX/pbS3wmfl+v3Qbu8u5Y6BVvkXcMuOS8vtrG9cRW2wtXYDmPt7Ke4hv4kXIvTcR2uwGfwj7ge9+IGPIAb5fqzGT/ELXgHt6IvmdiGAbgdI/FFrIy78SEZ3gK72Cl/PEL/Y/g+TsFTOBtP43o8i5vxHP4eX8aX8RXciy/hO7gLj+Pr+CfcjzfxAObjvPgGFsI3sSi+heXwMDbACzgAP8VBeBFn4Of4NH6Jz+M1PIffoMPOeQF98TsMxXSMxBtYBm9iORleGW9jTbyDDfAv2Az/is3xLsbhL5iAOuWUijacinZMQx+cjk6cg764UPpXSv/zmA93YX48joF4BoPwPBbAyxiKnM9VORTx4bijvxQWwygsjs0wEntjSRyHZTANy+ISrIj7sTJewCp4GaPwr1gLK3J+rYu1sR62xfoYgw9hT2yAj2JDjMOHcTI2xunYBOdhU1yIzXAFtsJ92BovYxu8ge1Qcz0jxQDsgkHoGh6K3bCQ9BeV/trSX1/6W2Ev7Iq9cQD2wcckvQTsikl4lHKchsdwPr6La/AErsf+TLcRY1G1A6XLOyJ5D7cFy9NFy3nuLaYri0ewOh7DhngSO+Ap7IQf4ED8CMfhx7gCz+Iz+Amuxz/h7/AzfAMv4Vt4Gd/Gr+T35VXM4/pdhGF4HQvjN1gKv8MamI4N8AY2xZvYFr/HzngLl6Kd89ZJzIvn8CLDL2ID+r/DPBhlY3/FdhiIo7AQjsFKOBMr42KsgsuwKq6Q4ZzTVHq9fLLXXlQqN9eL6aIY1p5uGN1kulV03tqSWnCf9qRSTW1K7fo725X6rW1KVfkHtys14B/YttS2v6N9qfrSxtRcaWfqpEVbU57tTN2lC+j8j2lv6re2NdX3H9je1EyPNqfuSrtTkXTRHu1O7bJoeyrqH9j+VGvLNqiY7l/cDtUFU1tU2ziWj9Ol0xXmpFGfri/dZLr1dIfoLtP58CO6Al0MXRLdMroddCfp7tAVHmfTGtF1o0ulW093hO7iuNz2qnL//vV//6r4/9QuGhKf/Nvj/7vi+L9miuPfV783xmiL4hzDPBTSJVb7I91btmzRJWsc/+YZMQCN+irPqekDLesakVaO4qyTtjuGreQzyOaO46veA0o+D96bTylJz3xKHDU1fWGrfJLWg+Pj++Qgz33txndCRjyFVkyXfm+eCRGkvhe6J8+u7VFijSpbYx1+VvMXt1yH9Mx1MGLixxn1e35Q46prhazj4TOvZ2zXROP7EZvKQyHLelgyX7bbEpCyot8cRz/OI55rYpZvjXyk4KvJ9q8q3141XeP+9ko2PA6MkwPmgd9dNV3z929z8zdRj0g+L8rE3aVuQDfJZ5pFPsclD0+Nl4wymTmvRn3iWWq+TlZ5lzR103c6ScOT4t3xPBeo8fVN6/bgOKUW62bsz3OlTYMKMkN5Wbd007qxI49JknWiUuUDyz9jXt2IRbGXld4XqmX7XGH1XdpzTqMeAsN5zi35jFo=
*/