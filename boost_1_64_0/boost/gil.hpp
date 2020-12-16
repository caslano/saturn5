//
// Copyright 2018 Stefan Seefeld
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_HPP
#define BOOST_GIL_HPP

#include <boost/gil/algorithm.hpp>
#include <boost/gil/bit_aligned_pixel_iterator.hpp>
#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/channel.hpp>
#include <boost/gil/channel_algorithm.hpp>
#include <boost/gil/cmyk.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/deprecated.hpp>
#include <boost/gil/device_n.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/iterator_from_2d.hpp>
#include <boost/gil/locator.hpp>
#include <boost/gil/metafunctions.hpp>
#include <boost/gil/packed_pixel.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/pixel_iterator_adaptor.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/planar_pixel_reference.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/position_iterator.hpp>
#include <boost/gil/premultiply.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/step_iterator.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/virtual_locator.hpp>
#include <boost/gil/image_processing/scaling.hpp>
#include <boost/gil/image_processing/threshold.hpp>

#endif

/* gil.hpp
Ak7JMHnZmRKCmDQzmn7VVcB4KpXMy3+tze4WqU6RNY+z+7DAeOvNwG7r1Es6xGC8Uf3FqjjMpu4syIexu0CBbUmy2JOSbUsuSIh04KakPSfAldiSWsgnX9nD5MITwGzf3DRTuWgNNya1NgGFY4s+xVlWLyWsHkcCMQbqqu0HpXvubYyOyOggomXWZ0S0hbkhCHemP4UJiz0DcwJXMSwDUqmUD0Z6Z9kBtn2nsPJ3JpIxsh31qUUkO6NuFJE5xniYzWI80uZq4zHkDXW5iX03NEruEjPJQ9qE0+Qh7Sm+z3+bU/8fdj4D/qf4iUT4X3aWUEnnbEI5ardyQNlDabaTnWX50kNp1znCr90I/KkFXSngP0hGWBCyVBTT+JGBqBes4GY7FZYLLfRaUxSaCTt0INLxDsuVpNEjtmA0IZAiA0i6O0k5s8BXbsMcwFK/+hTKc+dR3Fg3kvTgbXFEJghMoeExIHowGuk10RXK9ynrSEZNHaFUK+9PJHRT/n07RJlRFSQM8WqRik/tfANnZQY6CQOA0fRrLu8BZSWHMZ0+Bc3miIwT3uukQt34E78na/LPncQMCM2AMwFV6icHDwqrI0lpT3c3GZZHjDNSC/nnmPxfYyzUx/X87z6l5w+17zqp+w9KLINeLBD6Px0lTGjOhuj1age05FxKJbEHT5hLo51M0hWTcynegami6f3Hci8lGVlwedUxzhOBjrrndE6ndGa0Qlp3fCMZ8fV/AyjxoHCU/GfL/HpmdekPpE86en0lrG/WD+RfaZfnH8ptoRAjcwdmHnzUzBzPi0frzDdPGJ5lsU2XFSUg1y12fSu4+hptKyilxynQXN7iPaTLiqClCE9Y9P1d76KdPKdymP8DIOo2J9sb9kTLBeKxrPfmbGwwfwx54ugqkAzrPeHEFMz53AiW3gCl9CXBDf4IQOCtA6rrWjZPzGeYLCRHnW1kna+4Klz0mDrjRlp0rfKcO5/HxuA9aKVr4atJTLY0mWm3+kJvZnkQrEC5y85EIytz6sKFFpjhs9AMX4Irp0KpfshFMtu5r3FEcaMCBu+LFeFRZke1bcSm0s22u582I/8Kt7JLbGCLnGU9zGzNA6xGClXe+inWvbIOe0ObW7E3pGkR49TnANRaenqSlqm7IzV651UOjyiNzrnGuZzWMIaEE3Mc1bPbUuZ4Fnxz5rohVzkYJa7EW/D7NqI8Hoxk8U6bq1p4SB6GGkTZejWsYdknB2EIFMSY1xGd/WfMjx6ZPhelyTQPIY1X+YhNuMipHHIcvm24E1V2Bct0Vdi5ffBV05OdS2mcA20YMatZr97//gi98rLOGhg/9Do+nv2yUWHDSXqF2Ugwb3bWVPnqVKr9XYR+cgvKxEeJapFI2Wgr39s9OiZLHHRHWL50WSBDbanzBLFrm8mXspX+CvCpAGooiuOJWDCwPkXOOXp2ZTjxvHK2xCeBh0OG/syfqTeq3fdGo4CC/SeR/zr/sGhRO0+0whmtnpdvCvy9qUlO5X22yRl9z1JHY6BhrgDuoN1wFMTOyZWi8zcvv7JK/cvnB1tldfC/9yPxzcWpR8Y3682IXLvlGPgm5lQ9pkkuPEmWRy+cOJUp+93KdhctW+4nnXnXKzwY1QqGACkDD2Tfi1U6oCtBBKmjU8HLPpnSkh3pDZoONpOGS0PJ4yA/eQEksh0Ie2C6DHMhLHyB+SHnvoPKXuhGkOo6N13GZSOOJj0dH87+S+lOo+D7jYKfGyYTRr8AEkDBZyLMlC/DIgjT7FCyqTRGaSjzjjMkoa84oXv08dL7Gv8vRdN/qHDJqdOMNzx4QMBvy/1fph+h1IKc2cqknmiv+vO6m47s79EXcmlCxDJ7b5k=
*/