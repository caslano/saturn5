// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP
#define BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP


namespace boost { namespace geometry
{


// free function to test if an iterator range has a single element
template <typename Iterator>
inline bool has_one_element(Iterator first, Iterator beyond)
{
    return first != beyond && ++first == beyond;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP

/* has_one_element.hpp
nbhH4s2VeNvEiHeb6OC4DSbB22EI7oRhuB1mwh3wBHH/EM7AFEq8HSTeRMxEifc9ye/7sBn8ELYQeyY8BNvCjyS/f4U5ll3HXyPxnxIj/hsk/i0Sz1bYUezd4Q9gH/hD2BfeCPtbdl0vByX+4THqZaV8o+ty2BuuhgPgWjgEXgFPk2+hDRO7ru9pVrxZMeJ9XfL9RxiEb8Ak+DZMhm/BVPhn2Mpy1/WRL/GeHKM+rpZ4N0g818Aw/C5MgdfC1nCj1PMmeJLlr79dViPxd1fxO79dVi7xL4EBWCX5WwqzxN5N7Fo3g8TnV/E5z/afLPH1gAmwp/6mnOx3kb5dq78pF81HquQjG1bAdk6dF+w3cdcpcJWku07q/1u6/LIvRNJCzlH+i0XuEuiHl8I0aScnwjXwZGkf+huLZ7uXY6mUY5mUYzlsJ3Z9PUS+DebXjuuBXfLzKvTC38h1/q1cl9fgCfB3tvazV+K7XeXH2X56SPq5MA/2hRfDgXAtPBV+Cw6BN8N+8BbYX5dX3pHDRHW9neXtaNMBIdfDoQsiB7NV5DNFxoPJMPT4qcPtbWS4g40MZ0xvXLicRobLa0S4vZhCCdfLY10Pc/zejYnoVukAvwc7ib2H2GfA6+Fs+H24QMbDchn/auBN8PsyLt4q495P4K1wH/wR/D3cDt+Ad8D3xf4B3AH95OkumAjvgS3gfbAl3C3l2GzIuw94r7SrVLjephvKtH8u488XsD38Eg4XHVCjQXM4DvrgVJgAl8IAvFj8L4eJcC1MglthMtwGw3AnbAbvlPAfwv2GvIeA90k9m/3jacnfcMnXGNgVngHHwHFwPFwIS8VeLvffVfBM6COumbAbnA97wwVwLFwIp8B8WATPgeWwCC6Fs+BF8Ey4EpbAK2EZvBpOh1vguXArPAveBSP39e56XVSt/6pydTTHChjRIaX6Cuws9m5ir4Y/hbvg83A3fBY+LvZn4D64H74A/yLjy7tiPyx2ElfjTTJ8DTaHuNM+rHCt4O9gO/h7mAP3wZPgn+F4+AG8EH4CF8NP4aXwRfgDuB/eAd+FtfAQfAx+BPfCt+Gb4n8YPgEzvVxf2AF+qvubrEnA92P0t3SP1S7bSLvqBG+DXeBPYHf4EjwD/hGeLO2rF/wUcu1VefvC7nAwHABPhXnwNHi6uE+Fo+BSOAZ+B54Bb4RD4a1wOLwLtoX7xb+qEbpv9q+PrevmyIi4Pptvmj6bPceo06bmP6TX5puq0+ZSF702idOPn26bnBj6bXZ9zTpubrTpuTlMP8+42mv0x+RjyjGbMLWY/ZgjmKwN6LbBlGM2YfZgDmCOYLKuQT8NZgVmF+Y1TLiG75RiFmBuxOzFHK6J66+J/+K/+C/+i//iv//E7998/n9h5Vx1/P8rnf83z/Z/lGpEv4si04ahsu+wL/wU//J8/T2QPgXFZZXlRVWzSwuKiMKxv1Pvnduowrf0nE8K8u6aOGK825U9Mb9Ufq+yhu6x+c/TZ2puOkv2+OBn5XT2rMj72bPwL1T+eWL3GFuVPUWF35ZKQK1bYGRaPvyBSq+5J/J+8WOzjPJuMM+qgkbtsU0X+7aIHgHZC3aOSl+9R1D2m8RO3h1nFd+UM/dPY9pi7sZcbFb8FFt9L68oqyopKCovVx8c4AxUVUll3f0BUu/dldx6qfNIPN1t+9arLiov0fvWxb+L3ovdRdk3qfAvRXQyFBBe9mt2Uv5blD1fx99J4nfu38mCOcr/VmUv0+Fz7G1Av2MfZeVV7zMsV/ZpxkmsRMv7XNUWj9je5f79K7zPJX3sqj70daTMuKky631+VXXONOWpfKl8ON75xn5Hdvze2cV+J+v2rtDtHWXT3/0=
*/