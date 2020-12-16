//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP
#define BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP


/* min_max.hpp
sWz0dIMwewU30YQfYDZ/c8zsNaBPJx00bCOgz5C6WAM/U+oQQXd4KsShT/Nakb4XHBqywggsETFxbdg8naU85udbJV1o82224nxW/BzF+NzD/pAF59INKE4RIz7oczpuM3uyIz8szpMa8SHN2yNwOfJ8lJvLKd3DivM607mK0c8HKst5kovvYod7eqrKcn7IJ3FZLvBZtCyP8D2qLI9UnMvyKMW4LI/2mSrLY3yuyrLgc1WWx0Y5l2XR56osR6Kcy7KkOJdlWTEqS3quJcTl/IZRocnnwRjpsGCIgNuX2bJGsQyPYvMPvpfg7QXzeioTewrjY6OTbHjHdfaatxL2mxdN6IHgwFft6MNPEuam4Bv/H74uKo9azGfevIu7JgOvRzi87+j6Royb1egJxeP4gNO7inOK5mw2o74wRzHMNO6VuQC+1v/0deF4bdRHuUDpXBz1QE4APyHKISdwj2jHmxW799RSTyuM2ja4zOnYeXN9ZOInBjzsD3/ScejE2cuBfcpneCmxk4j5R9ThPU92LP4+P8Vx/c4+1TH/nX2a0+Pv7E87rt/ZnyHGj0bUT2fdC+sMobcbrpeFY7TE4FFDbfZMqeEU0YGe4dxwwfxqN7+f4bqz2LMsoXh9zmqtJJV7hH+edDqiDrSzSaPHGJ6J62uRO9P4bODjxwmdixvn9CjBuJ6TefI9w4XZfTTWifq5UofKSeuJpY67dhRbtH7oPGLyu9tXSKM+3pJWUkvptxWEd77Hq/UxsX/IVyXjT40Q7tcEg8vMj/XmUmjRwC8QnC+FKUWQvgs9Xm83SzQeK3QYyTE/g8cbdM6tZJR0kxb7Sxmuv0R6aN2f21OamBxzvFRo8Fkfzgffx+11fRlyKgK85nKrpfE8vcJxnadXOqbz9CrBJkXC/YbkQbhXSxaEe41j8bK61vF4WV3nuF9W17MuywrYDY7JcqC1xMRsGdr31E2k67K1+z3TWCr4crle+cHDjqVaRueBhN8vbrbcPZFpXbHT9d78t1gW3Os7Tq9H7/Vdx6kPSN89vmd0mBlCdexW+7fYh/w2p/E+5LdbjT9RgP59p9OnCbrPHaSb80nAdyf/TXfCcH/AOt6N9B+yTiFjuHdZfco+4PsR/+2FezfrGC7l9Y9Z55TQNfcw8+75E9InT8W0/JT/9u55r9P9tNzHuhfu/aTbc1ge4L+9cB9k3UvLQ6yrtDzMjO5Ja31Bn9OXrYluVkdpKwFkjzgGK5Hg3WPT8KjHYDUoXPNzT7crIWk8kVnL7jP6mNPwYyLdBNjjAYObEPtlwPBGeJ8ngA2Z9a7FaqnQDdqvPG0atJlfe1qpWklqtmkA/43H06Rpnh3IaczQ423QnvK0JZBXT1tt3rRu2psPxwg9nfbvWVpomzsBf1Zxh3G/Z4/zmbnPSV2sUX/e6dSXgN96/cBeCNg0ZPCue5GY/a5Uy/Y4GevHHh/l1UvkoYmj2M2omJgSf7kDL0zD+79C3PteM4bsd8Qg6eZApLLom7wKbH5/jvf/xb2ipU758nuhyffu606HXyuVcna4SG5Gbojq2huKF9MSsTcVa1fr1I/8g2Nc5n9kzaRU3+stxflef1KM7/W2Yzym/Y7TuA78OdOGZ+cL03Ni40Nk7wZMfo/9C7B8obunZ+5Qd88CuQ/zewGTfb73A4afiyqlZj0F/kGcV6uVFNfoxniamDHxcurOQg09ck/nkKX+/f8R5Xz/f2ou749jgeiBR5ctTvoN59aZ/Zs87tSIVlrkUyVoLa70mGEinJaD7MMoS4Ett2bI+DfV8oLhTISS+S1XLBkO164QcAwWf4OvqFi1ns13zSb1ZH2obPZBpYX5tFLgpe1yTFOGfXE=
*/