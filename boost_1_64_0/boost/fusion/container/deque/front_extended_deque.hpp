/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FRONT_EXTENDED_DEQUE_26112006_2209)
#define BOOST_FUSION_FRONT_EXTENDED_DEQUE_26112006_2209

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

namespace boost { namespace fusion
{
    template <typename Deque, typename T>
    struct front_extended_deque
      : detail::keyed_element<typename Deque::next_down, T, Deque>
      , sequence_base<front_extended_deque<Deque, T> >
    {
        typedef detail::keyed_element<typename Deque::next_down, T, Deque> base;
        typedef mpl::int_<(Deque::next_down::value - 1)> next_down;
        typedef typename Deque::next_up next_up;
        typedef mpl::int_<(result_of::size<Deque>::value + 1)> size;

        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg& val)
          : base(val, deque)
        {}
#else
        template <typename Arg>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg&& val)
          : base(BOOST_FUSION_FWD_ELEM(Arg, val), deque)
        {}
#endif
    };
}}

#endif

/* front_extended_deque.hpp
Ho/jRez7e+iNH2Br/Ajb4V8xEj/BGDyJ8fgpJuIpnIN/wyvxC7wJT+MW/Id+XSvtt+hvUq86yPknENthR0N9TJTtRphs10bmDvPFKGwr20UTKmS7ENnOG8Nku77yueiHHbA/dsWw2nSbSPumtHuyPXWSdKV+fCvf/2cxBr/HWfgjXotNmzKXETbDl9AH38GW+BW2wg7EdTFehm0wCdtiNvrhKmyHv0N/PIrt8QMMxC+wI/qTtyAMxs44CbtiAobifOyJq7EXXo998XfYD1/F/vh3DMNu7O8A7IGDMA7DcRkOxhKMwKswGlfjcNTOR9KOKe2bVQTHOY388W3siO/gQHwXJ+BxTMD3UJvrTdolpb2yj8Ncb9MlvhnYBWdiGCZhNM7CMZiMY3Gu4TolJN/1delQiXcY9sRojMXhmIQjsRBjcD2OwntwPB7AOP2+jLQ54gGT+zKb5XpoC/bF23Aw3o7z8A7Mxm14PW7HTXgnPoI7sBor8Azejd/gPTiE9HbhCNyN8Xg/zsY9mIV7sRgfwI34EN6CD+N2fATvw0dxNz6Gj+Dj+Ad8Qvaz3Eva8jBU9lP5/b5G9jNV9jMN+2EGDsFMnI1ZOB+zsQQX4p24CJ/FHNnPXPwaF2MT0lmCrTEPg7AAu2Ihas+4kjY1/FiOs/EZV8skX8ul/EtwLl6J6ViKhXgVrsJVeAOulvyV8d+j+Bs57tfgn3CN5Pc6PIxr8ThejzW4Xr+OlbYoXG1yHXtHEz7XeCcOxB04FCswFu/GpbgTS/AeXIn3IvFz7pM2I+wg39NN1D5T8jKsVyHrdWtgvWpZr38D6/nZ3FsvUdbr62I9rhmVechM5zervhz5m+s5zP6z5y5znrfMvfnKkghZjZivrG6usgszT9kvNUfZaY5n+6neXtGEFEIZoYJwkHCS4DPN2yuEEEvIIqwj7CVUE84QWicytx0hiWAjbCUcIBwneE1nW0IcIY2whrCLcIhwmtB+BukScggbCZWEI4SzhOCZzJdGsBA2E/YSXiScIPgkeXv1IcQR0gglhG2E/YQags8s8kRIIFgI5YR9hCOzPHOseV6el+fleXlenpfn5Xl5Xp6X5/Xf8foV5v+jZ+75z/+nPE8vlpsaVdw4a6oOV+GJekp3UJtVnRtQubFbc6PhbwyDszI8z0vmBnzKMDdgvNz/TZR2zimEDe3J1xT1HsaEGTNS8wp5Vo8WE9mwNjxuwvjcevO+h676AP7yz4kx72vZ+L6Q5n0tXfd53KT2MfzsycdGdUtt9s8fjkd/0untVtwE1O4xS3nLcfBpYn+PeYy0UY3DfjgeozEOJ+IknILxuBVLUrimJ8h9Iv0e0TE3nhNf6eJZ8VlyT+YMgfsvds+MTzPcTwmU+ybG+yVnCftSPPcGPC/Py/PyvDwvz8vz8rw8L8/L8/rPef2iz/+3lTDFR4bGBXgGgHId/6DhOv6YXMdXYgjuwagopVOiel2ZlJyUGjeudo7n3IKs7BL3x15/OUQZX5mV4TzH8sLc7LwsfQ6Bv6rrLS1Oz6sbaz1XHVuck27NqRtvHKUuy8y3GOYU6aKNK+e98RnZBer7EON8LjLn9kdDZMxn3XhpiWOJOg550jD2W/JknI+Gfs7S752AbXAY5VQRbSgndaTuuZWPfX4LHPYnl/fkX8+rRR/Xamku48Ud5ipKaCpzlUg/542E4eQ3dqQhv+pkYBkrtOPq/lwTjsc13mQul0Q9r9pIXX9j/mW8uowFl2OSx5G2n28lTi79MyjrDrgAR0bxjxjDPpB5pgGzebn1zIdm7Z4fpc8DNFgtd5bNH60vkzrpvI85dXkvXC7Hy7A/jvVNrUtrY/S6pL6fNcr+/eA=
*/