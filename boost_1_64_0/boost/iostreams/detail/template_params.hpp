// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TEMPLATE_PARAMS_HPP_INCLUDED

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BOOST_IOSTREAMS_TEMPLATE_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, template<) \
    BOOST_PP_ENUM_PARAMS(arity, typename param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#define BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, param) \
    BOOST_PP_EXPR_IF(arity, <) \
    BOOST_PP_ENUM_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

/* template_params.hpp
dtAMmWefCdW+EeiDl8EOsBx2gnNhZ1gJ+8HZ8GQ4Bw6R84HrVcv1hhuut1Cut0iuVyXXWyzXuQJ2hVfDbnApHAivlOtcBYfJ+cB8aJ1c73jDfOgE9BwWwFw40eWv/Sfh/RWLv8nib6r4q9bv0LzLir8WyFLxd72kbxXMgDdLvNfC4fAWeKnMWxfCX8OJ8FZ4BVwP18A74O3wTniX6G0QvT/IvPVjjrtOj7y3wUxDerIlPW1gS5gj/kYF3ofk2b7OY4+io6TnBJgFO8E2sAvMgZ2hemdzhVfdQHjdJbweEt6JEt53JLyeEh6/dXibGwivt4TXR8LrK+H1l/D6SXj93fVFwmtiyKdBkk+DYRL8rvjLDzwny3Nqnfg/Xfx9T+JxjsTjXInHeRKP0bAXzIcjxD0QbkED4V4g4V4o4V4k4Y6XcMdKuOMk3PGucDdLuIMM4Q6XcEfAFvAMaX8jpd2Ngt3hmXCg/Jb8k2cq6r0h/06V/BsCm8PTtD/kYPj6mS7+MqR+ItpfvvjLMfg7Xvy1lXxpBytj6x1i6x1kvcO6pYmxNQ8RrnmoIa92IWlX8j0vZBKyGtmM7EHSrsLOEFKALEPuRrYjCVcnWp2ujq2HiB2xI3ZY35D5/7JBxUdp//8z7v3/8fINXETWJ1sdeGC6+2M9FuKauTTOXep9UPcrP9PMe70+Dpqn4y9njo4ImfdfoG+c5zTv40LXPM9pnLtE3zTPaZy3RDfcPKdx7hJ94zynae4S3fDznO1duu09ugMC85yWpfcuv6jO5zPm8x3eEVrrcdR2+x334VzP9s5/6vnR0UonVX7bVoH6Hcc70DhVLs8St+eQ55EkPPxF5itfgJ+1Ovx4aZj5Sj1uRX3AXeqD3rcYOo+ZFmYeM9Mwj5kdZh4z1zCP2T50HlO3j83yGHAVEodciZzhzHftd7WPCjXNpcrDU1+NbQG/5vpqbgvoG+uJsS2Irq4ntqueZMNfqfNTrRNJTRFiah/u+A1UuUAHML14vnvP871Kp0iNz18SWrf0OPwupdfHykUjMO/9IhHZKnXoTgRSUQ4/763GPg31IjlMvfAFl6ue8yZf/PXw/3wf1otqjDRp5f1fvv6LoY//8tR/te/W48R9sTHSb+oYqew7kXsBbdCw76SljIO0hs08+68GwBx4PsyFY+HxcBZsBytge7gMdoErYA94LTwB3go7wTtgZ/g70btH9GQ8UfoP+kzDeGIv9OJgH9hZxrG6wwEyDjoQngHPgCNlvOoieAq8RMZjyuAQOF/GYxaJ/o/gMLgYDodXivvSCMdPCmrgg+g8dPixlJrF9eMpTz54dMdUtj34vzGuklzDtRHT+Eq/miMfY7m25uiPs5TVEb7jVhPZ/pKtNfXjLXtq6sdcVl2dGNW4yxc1DY+9pD1EOuDm38R/Y8Zg8h+KbBxmI3mxJTaeEjv+B4+v8/1/0lF6/3/Z9f5/uqyPH4o0k3mos5y1Su73/0nFKjqBtW/duzW4FgK/ka9RLvg4ujXK7rD7ZlgckwpLpyhdZSPJcT+YrtxnFck7/SHcA+ueXsn2v3+8Kmst5B2jwbUWpNe/1qIRa2ydODnxbCXxxE3Fhzji5sTx//sdJOEtxz35jS0z4l/5wUMPTb/36ZEP3PSX2DvIN/kdZFCgHUq/USftvmfAZpW8e7SE7WAmPEXeSfpF+Cw+KDaX2ahn7m/TXOam2DxmRM/Pe2LPzrEjdsSO2BE7Ysc36vj63v9n8mJ5dPb//831/p8t7//XIjayArnI2af5gXvvx8ziuf5XXa/tRG0r+Aylf5Xa5z4a+bF53w7hyvu+HhuYVTpJwjaMDxj0JS7m8QGtn8P7fqLln1t8I9s=
*/