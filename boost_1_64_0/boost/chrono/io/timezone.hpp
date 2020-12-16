//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_TIMEZONE_HPP
#define BOOST_CHRONO_IO_TIMEZONE_HPP
#include <boost/detail/scoped_enum_emulation.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the time_point for system_clock I/O is UTC or local.
     */
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(timezone)
          {
            utc, local
          }
    BOOST_SCOPED_ENUM_DECLARE_END(timezone)

  } // chrono
} // boost

#endif  // header

/* timezone.hpp
kA4up1boOmp+VjNcBbVCD3K/r4epEfqLeZzp36n4vAL3MP3NwOeY/vlM/wKuAVdCjUsp2A9czXQvAmdyjbiLuD9GNteKm8e14hZTC3U598u4hlqhleCvmO6rwbXgNeBt4Apex695Hb/hdfyW17ESrOT+JtuZnmO10LxEHPvlal46Hwur07346V6GIk/mwCyD2QizDWY3zCGY+l+HqfZf1+le6n51v7pf3a/uV/er+9X96n51v7rfL/P384z/52Pg6/TH/9ty/H/rzdbx//y8wmxEnwMPyrPGfyuLDiApiA4gvdynA7BEUSsdAMcLzL3wA67Z5S6v/Zpd8Fvtml3F5ae3ZtdwpvVAEM1CkietvhywCxcCjHMwTFDdAo8H1y3g+M+rWxjAPNjAcdW/IC/akBtxZFmJXx4E12zQ70AVy3G4R8V+2BiN0i9S19HdUCfFfbSjscqGCqGfESSvGF8/vYbkQ2I/alyoQuAHbohrU5nptr6K1iGa4zj3S5gTxizVSMLk6nT25FiPjqOK5oG6BvrvLXHOgP1BsX+NnHbAD9z84rgiQeGXWVpuGXO+R8IYjjkqhuNWOkxAvUQcuEnC/GhMQ/6VG9NVvLj78g+aH2OoMVQtNvqpMN84lb4/kiR+jHkxvgFiH8r4GQ9Cm/EMMEbZ1pyMZhl2LIUflN1EFUI3HU6Z5TcA9TRCebQbaTBzYDLseg75/1bL/7FNPXU6qbo6zfUYX5A0azvyzLc+4/IyvT6jXmPx09KqazY+VFp1fcZ2pVXXU4wvrbqeYlPtNkjs75T41leMhz2VxwvQMhRlmnu5FBUr3pOpfvfkrAD3ZHoAjUqusmhUuFbiDF73VQn2+3YMNQTZ1EOkUQ+xdZHffUvhSiDdyjPid5pVt4Lw1EOgfB2iW/nXtSvetKbUD6xdSfVvYyhgCbhGSkl12hUeD65dwfFT1674ta+npFvxXnsL6iM2cF2Lq1lORxb6XzvEK8HXt6D/WD2O7pJyugJjEUbQtqeF+ElTw5EergmAexWmlmUaRMeir21SGD2zXAd518oo9r82d1mQcqXfUcHXyuDxtlh/tjXy8gTMWviLcEZi9dlQV3hkeBfzn/BA7xPU8Dil7HsFeJ/g2gpyvIusP+utH52a/uv1Q79v+OXXVeFB1uPwzy8KZgI+a4v91uQorsWaHMU1rMlRXMOaHMX/mTU59DtKQyW/OWiQmoOpIDQoGHzzyzcKUQLkG/12kGfpTNjvEXtvx1/UBHXQcKl2DpeshYx2uYouhfnIONqqWL5j3Cn2QY7P8Gzs5jCq6FCYvwzXSsLlw3672Ic4DhkO1cPhCKgLKYC/jeJvqOMLI0T1dIQEvc8rxZ/D8bQRoaJ1XDlFZYVZSAf1nybdpr+NOCvGoNT9aqLRhccMdUTieNnoimM9UQrXGCNEe4Jnkj7me9fI07qmxyXOpcqpFqpYnmeKuLUyCuB6v8pV0XwPGbjAKc+fBKwcGs3zFojbFJTZCL7n6LSgVOYYpUYDdaWBdptlgpqj6/434m+R0dcYQv1YwLCWPCkqzpuXVoS7X7/TjZK0djOijGjEATdLHNNUlMSx0mhM3Y31ncauu0mu4R5I97sHcgPobtxW3Q2f/4fd+vmvdTezfoG6m7AQ0/33sxfPOuS67p7LNjU5sOPe65/779Hj/CpM8rOy7YODjsyc2vLgV2WLY2687v9Pj+O/DnGyIevfUqfDPgL2HaT66XS6U6fTgzqdnpZ1dt0M1wIm+TTW2dVrlDC+jkyHVR/S2fCE7wbGmukC48C+YBuwF2jGU6G/8eS7V+IxOybWgeZvO/UVr1EXsgu8AHwDTAdbIJ4CMBFcDLYBl4IdwPU=
*/