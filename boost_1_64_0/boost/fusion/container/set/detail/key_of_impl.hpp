/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* key_of_impl.hpp
sAsOwa6Yin5oxUBcjt1wN3aX9tMDT2IvvIi9pR31wWvYFy2s/37ogyHYAQdgPxyI8RiKyTgI03EwzsahuBpvw3wMx204HPfiCPwH3o6f4Gi8ipFYmfU6Bj1xLNbHcdgax2NXvBNH4QSMxGgci3E4C+NxDibhQkzBB3EyPoKpKPsruc9MHZVyvpCvG8/19cALMt4Bk+uBC6vQXnARtsD70B8XYxDm4gRcgjG4FGfhMlyHD+AWfBC3Yh6+iA/jXnwE5Xo392NdX+/uKtfX/bAF+uNADMAh2A3HY3dZ/pxK6v1V8rbPrzP/TpPj8meyXJ9je7yEPfGfOAy/xEj8Ch/Cb3AHXsHd+B2ewGv4NX6P3+F1rEYeP6M33kAf/BXD8DccjpUoZyJWxilYFedjDdyFbvgBuuM/8Ga8hrWxMstSB2ujBwZiXeyB9XECNsQEbIS52BgfwKa4Bb3xMDbDD7E5FmErrKRcF8S22AbbY1v0w/Y4DH0xDjtgGnbEJdhJbX9y3xa7lXBcPWORe6tYKOd9jR39QfikyHqfjC0xFX0xHf1xCkZiBt6JmbgCp+FGnIHbcCbuwVn4Cc7GGuQ3B2vjXGyI83Es3oOz8F5cgAtxNS7CzbgYn8UluB3vx2O4FE/iMkc7tMh9WCySetC+T3mMnNeOxbYYhUNwAqbiXZiB0TgHY3AtxuIhjMOjmIBnMRHPYxIur+KM0bShnbvLOE1H+NtlUq327pZgUhppGamAdJp0neTtSyxiUi7zyJlN/B/+rY3rNMFaWRfbyWf7fz6+0zmvKn96jKc5LKerOE+h2/+aWE955GmM95SwXR/zaQvjHCQZYz+FciGoM+Yw/srt5Y8DdcbX/d+OBZUm8aBu+Lr/JTGhGndwtwSRokjZpDxSAekU6TKpVkfifZMiSFbSctI+UhHJoxPtmJRGWkM6RbpC8uhMzGzSBFIuaSfpAsnShbjjpBBSMmkZqYB0inSFVL8rcbhJkaRs0krSPtIZ0g1SSz+mJcWQ5pPy/SriWVV8Kj4Vn4pPxafiU/Gp+FR8Kj4Vn4rPf+vzH4j/H6u8QfHPiv//elOLM7ZRJbk/SmpECiQd8OE6ZZLEWHD2a4m2ZirRPkrvM+F4jn+VPT4Xj+ep8cWkH0OOLp7YOSnDHJI3aQbpEOOFTJIyRNNZw557qX1rpN9ZsbzDnHlL3xK1f0pSEjbUxR2z2jvTWPT96n0dceawFVbBw8zzgr2cCRnR2qKWrW/dgsmGvnUmZc81lD1PW3ZZ5pW43zZOqtL1Tfp9GPvmuO7/RP3IO2ET47OyM6VvbLH+OlJ3xfv/RVmK99WJsRTvq9NV6jJP6rILyZPkSwrihn3BXdJf0RZxpuxtrVU9fZ/cXpJPiDxXOEva9zRSOyWfaEc+8fTZdAZxKcs7dKX/luQZK+3L8T1O2pKujqJjpY21NAynXnTlPSflfVzK+wipP/O9MlEtb4Z1prPA5YnDVMAX+rdlyHrUlFmJZqO+n9jYJ13tYxpZTZ5RlXXWS9ZZvlq29JSsLHY3zuKV6V3ArtZhoOSbJnHflOcjW4q3MW5MvCNfZRpeBJKZVoZtrhZwDT1J+nayDX6YaN8Gw0cEdrPIsA3OYYGOYQ85hwU4hs1yDvN3DLtVHRZwq2NYVoI6jPHs2/7ueMew7rLtyzqSOpB+eI5t3Vq8r3ts5qQA5/ZfpboMC7T3e41ifd1gmPIcyGu2vIx987LohGuME5bMMGf7CKM8zDPNkU+Udhj5sJ7UvJJZT8/y9wUJzrxCTPIKMskrwiSvGJO8tPvja9Iu7pX6mCvt8Yq6D8lKpEd4SvZMZWdSer9MKa+uHco2K+VNjJc4WLpyHJQAJPU=
*/