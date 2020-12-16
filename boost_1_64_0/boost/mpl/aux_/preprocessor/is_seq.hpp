
#ifndef BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED

// Copyright Paul Mensonides 2003
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

// returns 1 if 'seq' is a PP-sequence, 0 otherwise:
//
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_IS_SEQ( int ) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_IS_SEQ( (int) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_IS_SEQ( (1)(2) ) )

#if (BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()) || defined(_MSC_VER) && defined(__INTEL_COMPILER) && __INTEL_COMPILER == 1010

#   define BOOST_MPL_PP_IS_SEQ(seq) BOOST_PP_DEC( BOOST_PP_SEQ_SIZE( BOOST_MPL_PP_IS_SEQ_(seq) ) )
#   define BOOST_MPL_PP_IS_SEQ_(seq) BOOST_MPL_PP_IS_SEQ_SEQ_( BOOST_MPL_PP_IS_SEQ_SPLIT_ seq )
#   define BOOST_MPL_PP_IS_SEQ_SEQ_(x) (x)
#   define BOOST_MPL_PP_IS_SEQ_SPLIT_(unused) unused)((unused)

#else

#   if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#       define BOOST_MPL_PP_IS_SEQ(seq) BOOST_MPL_PP_IS_SEQ_MWCC_((seq))
#       define BOOST_MPL_PP_IS_SEQ_MWCC_(args) BOOST_MPL_PP_IS_SEQ_ ## args
#   else
#       define BOOST_MPL_PP_IS_SEQ(seq) BOOST_MPL_PP_IS_SEQ_(seq)
#   endif

#   define BOOST_MPL_PP_IS_SEQ_(seq) BOOST_PP_CAT(BOOST_MPL_PP_IS_SEQ_, BOOST_MPL_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())
#   define BOOST_MPL_PP_IS_SEQ_0(x) BOOST_MPL_PP_IS_SEQ_1(x
#   define BOOST_MPL_PP_IS_SEQ_ALWAYS_0(unused) 0
#   define BOOST_MPL_PP_IS_SEQ_BOOST_MPL_PP_IS_SEQ_0 BOOST_MPL_PP_IS_SEQ_ALWAYS_0(
#   define BOOST_MPL_PP_IS_SEQ_BOOST_MPL_PP_IS_SEQ_1(unused) 1

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED

/* is_seq.hpp
39JOtbSzeE360KXtb33fMfn3G1b3ELgt74/SFGzHxoQXbLfFTi14fbnOPPZB2uhV8W2l3icK1ptz3iK3WW3X29K+NFjV22Z7XPJHaKQeNq7XXyjt76+kHl/K/nN/y1yP+AL7z+MP1uNB++/2A/bfVau4Qo7V/syz2p/ZVvvzRv7+lDEW8n7iHAW2S6gcnGNku4yQ/ZtysuB28S6h7ZL3gP17w2r/ZlvtX+vtdDF/O9njDf+L8YarxnjDiMSxcy/qtlz+YUHQ54N85g1+OPGGGxr5fpfv/VNWz9tT2teVcDQ64xj0wrHYGsOwK4ZjKEbgOIxEvUbGMGCUxB3G4SocjxswGjNxgsQfJuLHGIM5GItOch/BmqjD9jgZB2C8tAv1GIUGiTMk4DM4FRdjYv79++R7HV2kvur791WSdnF1ad+7SLu+hrSDXaW+NbE/1pL2cG2cgG44GetiEtbDOeiOC7E+bpb4y36Jv5yR+MvX2AjvYGNp9zeR9rCnbIfmWBW9pD7EKOT7ne99qQ/v1XRAZZou9ZmL1XCetO+fkfb9QgzARdKeX4xhuAQTMBnn4rP4LC7DHZiCe3E5nsQV+B4+h59iKl7ElRJHeh5vS9zhJ1wtY3zWYCVcizVwPdbBF9EH03EQbsBgfAm1uBFn4SbZv5txDW7BTLn+fz9uxZNy/f/7uAPP4068jK/il7gr//mT8ruAYwr5PDwh27MN1kFfbI5+sj3bYSdsjz2wA8ZgRzRgJzkOOuMy9Mc12FXicd0wCwPwI+yO2dhDtl9P837HcqUkHoa9sQ32QT/si12wH/bG/rL9gnAEDsSd9njGXzqeMTyZawVJyaRNyfaYhn2yT3/16SH0/9OBqiuR8f+vV9fk9926yflCD1IZeQ7vGV/+97q5jTSoe7egkG7Bw4v2/H/zM9/fYRlKgfmzQF9xsqyvpazvcVlf6G/XFx0bbfjD68uT9Q0jOZEGk/5G3vTfrK94z89X1mf9/PyFEk8YIHXrR3qffFUO/WZdet76b9VN3e6MROuxE+r2b6bEBa5Iv/wX+HeWNfuQ+h6KypKL0v4t+1jQ0cLHdEROsZSLeco6qcC1HJOkLs6F1MXVatxHttW4D7meQ+qquv5D5nNs3qdRYhFW12PckPkwOU7Mz8DYKTv9sBwnB0kfKjGUY+rrYJT7HlL6aF18XIRl3EbFB2y3d44VbSxMIqq3W1IxtltuIdtNWUZEWMHtFmb1+UiUawPmS72fVparHLP5sT9LfYv2nIGyj819o2j1nYTqeFKMNtbGMyVsPaPDHhf5X4yLuDyjvD5j972PW/r5a3uFjkvMTv90wcOJiwzXyG+f/CaesnreegN5vmpDLC/t90el3V5D2u2Npd3ujU2lnd1M2m/+pFBZfktZfln0keVXkuVXlnZ7FayHj0n7vSqay5kuyxlWSDmrq+6L3wRrSnu1Nvqim7RT62CQxC0GYz3L8uV3i+1eyPJbSDkfl3o/gbWxJXqht7SHW2EgtsZ+6CPLP19Kfofk90lZvh9/n0FlGiLlH4rOOALdcSQ+gaNk+aNl+47BvhiCozAUwzAMozECEzESU1CLKyUutQ3H4wGMxndxgsSjJuLnOAlvYSzm4lQsI/GlSpiELjgN3fApbIIzVffPHIhzcCguwsm4GKfgElyJybgan8UsXIqHcZnEM5bjFVyBN/A5ea5GKpbFlVgZX0AXTMNmuAo742ociWtwNK5DA67HKfgiLsR0XIwbMBk34gHchKdxM57Fl/EibscvcEf+cxvktxMPy/Gjfm6Dn+zftqrno7hLnORJiZP4oj92xC7YHbviGImXhGAAhkm85CmJl8ySOMkz2AsXYG+JY/U=
*/