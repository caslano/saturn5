//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP
#define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP

#include <boost/compute/config.hpp>

#ifdef BOOST_COMPUTE_THREAD_SAFE
#  ifdef BOOST_COMPUTE_HAVE_THREAD_LOCAL
     // use c++11 thread local storage
#    define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
       thread_local type name ctor;
#  else
      // use thread_specific_ptr from boost.thread
#     include <boost/thread/tss.hpp>
#     define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
        static ::boost::thread_specific_ptr< type > BOOST_PP_CAT(name, _tls_ptr_); \
        if(!BOOST_PP_CAT(name, _tls_ptr_).get()){ \
            BOOST_PP_CAT(name, _tls_ptr_).reset(new type ctor); \
        } \
        static type &name = *BOOST_PP_CAT(name, _tls_ptr_);
#  endif
#else
   // no thread-safety, just use static
#  define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
     static type name ctor;
#endif

#endif // BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP

/* global_static.hpp
PTKHJMgxv7zvg6/gd82sruLn5P/k/jD9I0WJDjNC2shRY8BqtybC9YiT43LZs//3c6bTp/zvh6+W3Htp8+DKZw7U7W9po3MDc47ip88RqB56n7fNeR5+inF8vDnsnO6T9HF3n/71iJGlTJsxm/84m59ZLn3mwPWsRXrM0fvU0O9eJiQ9vp6YcQp0WBDJmp8kqTAi8zh10fb6CX7e9rhMmyErwmk/QxMnR40eC/beeI5A6PFeI0eNPgtC4l2NKNndZ1c6hN9i/tlW36TvdJiw5Uo1c5LlG87hs67OIeE9Nkf16eYyNY97HHicJXzq6xtHdLmRfTEOnmHO2ibsO+M15wgsPJ56vOVGz3AMWQ6sBTz7Txv216jY12bClqifoS71TPOCBMXnyYMGi4059FfvJy923Xo/yXHg8dhxS/aeZb6w/c/XHtu8fTWOPU7RoOv51WxL7OfkRpQRayLPlmPeXOBupCnS2N3zvyT0PPOPM4iR4VrP1g5JijQZs+VSz3EsScq0GbEm8lxzhAQFGozYMhc3nZMrLSYvcA7hgj5wuZfZz5CGuoT/Zj7R4nIXMO8JR/z8zN4L5fFJ/Xrhf95Lvd8/zLiLccQJHcaceD1HlQ4zAi8yli/RNke7e/3z1Biw2N3vHydDmUvt1iCIkaPOkBWRF8uDGKfU6LFgb7cWwd3IUKXHnOBLvMYxaUp06L7gf2sRXI2FtkMlbRa073HV9vCT4u3WHCjRoM+UNZGXy4djEpxSpcvVStrw3jGmaGHEOne7kWuHIEsLJfYpcnrdcwTqjAhczzHEKNBhxf71fZ0lQ5URezfwtYgUJdrM2LvhOQLXIk6RNtP/KKsxgTeriW3tlebyK8xlYmQ4si9HjxmXK6vta/SXg906BAevNW9fZ8zpX1buXIsg08vImaG5FPd8Ybv3d+8xLDw/irj+bBO2BRqELudriffGmvfE1Kv+t6bBpRrmPifMPA9pK2k81m9Q9zcqEzEylGgyYsX+m5xLkTGRmuO5GxU6TLjZm809Tqmx5HpvcV1TpsuM/bc67k1+IcfVmPj/JC2OrVu7ebn3+NerSVXtSFOhx4LQG8QkTp4mYxLyWpOtqeGb9UM7xVfJjSkbIrt1JI7JUKXHnOsZjxg5Gow42q0X0WfDkbplqFBSvzZTgvK9GlFOqTOh9aaA932x/9NfKnSZsCZcdx5H5Giz9zb7iJKlSo8pjd2aCJF36Bczgg118PNiXv0K3ZB7310b7H08FBjYztk492bOy3PknBxZ7S/q6mzfCZOXe91YVD/o+PeHAmP2/T/xmxGnbC63WLFnHl+JkccJ26Oya5oOB2rfbDifgP+rdCVi5KgzYMX+u7z+KtfOOxxDlCyXe5Vc3xYKRJjWHf9ax3PwOvODDDWGbLne6+VHgQ4zIlXvDRQZEHyDuBySpEyXKcE3ikGco1f9d40FeatxyfG2KQo0GPn+puia6X7gf2smpD/0v7UMRu+0bZlXD9AXlv95/m5zjf2mujHmUru1IeIE3yvO+/63fsPlxDnierv1EBqMWRPuOIZBTL3ETieNjzwqtoOU8W0E1FjOYua5nLhJcY/b3uc/pv3DYCDn+OvZ1t8jLgWvR3drSNS5kfhJKjQcO/f6GR+V7x2NiXbHd1ALjzf/2YqfosqAZUut1GJF88O2YqS1W3Ve7V3mLgtKapZ1TEA/ox8W2zEh+2NqFHm/WCTlXP6Q7Ud9rVCvBEUWzh04N+e8EzU5cu7lnHvq3Bvt1rjIO7fzIcf/51yv1b0Wt3/fuXWvzbzW+qiaynl/t8bGkZiX+s9rH/7fuhI1cdt3cQ05f+D83PvVwfm99v/WtBh/1D6vrbxW/0++Xps=
*/