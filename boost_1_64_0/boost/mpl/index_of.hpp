
#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/index_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, index_of)

}}

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED

/* index_of.hpp
bnD9UAYi74SLoRCsDa+lNHrB1fVp8b5pNnKrj5c24ZqwCX+ifAA24cZ9U3jGB7xvWqjn2d83TTrX6b7py3re//1901Ez7O+bHhg3dN80dN/0X/+x3jd9r+Ojvm9646uO90214f/u+6bz/9b7vmnMV9/XfVPgbw73TW/vfZ/3TXeHP5T7puv2/jfdN1Wd0+u+KaXum5Lqvimh7pvitvdND40075t0u/sm3S5dc0gPZqTrlvsm3U43ptulaw7pwYx0vbeGjge0gw5Q12+oeJ7mScUwHjo9d4887LDkx1En9RFjZWj4U+JQKY605/2+UedDpR+HyrntlkOlh+/m4h8xVi1EDVOzy3JiE2H10twx4/igPQIH7RdfNQ6GOGbSkfEjxmoLzv4paHpTUD60EFZv/nVbAysfDodEmPqqRfmAVznJjxir3Rl8tYWweqhw4dsmXz34ymDz1dYMvtpNWJ30xM1fMvkq+Mpg81V7b76CCmXkFydsNPlq6cuDzVc7evMVVGruu754wOSreNtg89XGDL7aQVjtXr34OyZfndc22HzVnMFXG5nb90+tMfmq/qXB5qvNGXzVTFj9+hs9PSZfnfTSYPNVa2++gsru8ednR02+WvXiYPNVXW++ggr32BErrzD56uALg81XbRl8VUdY3XnN6gMmX0VeGGy+qs/gqzbC6rYv3PAzk6927c7gK+hUU3RZQH9ZqQuV8se9W77MSt3DodRds9ui1IXqFNpy3ExAbUsEbyK17beOO+Yd2n1W5OAl9GWohXEBZPqiMEwAQ6mUnvzbyfXmzcSE3Rl0Uxgm6S8Uv5sJw7KvX3Q8K36HQ/H73vMWhT8uEqVGfWx5iv4a94C/bHy4k5XqAWx8d6AW+gWVsqG1Bg0JTkqsRBdqn3qO+S0H/Hbb8zb8lsIdZYL+GpcC5wamZpm3SbNQC/0CJ0fDQuueGkuUxJtccb+25PV15I2b+gXF+7Fmv3DdYNxogPcITlKs4E3/eubvPE8DQv4/lzlPcWuAW1SCkxLK89ef2vNxwr4iB8/gHkYt9AsSQKgUinFJRn+NS5nnhn3mj+YN4GJVi4eJINMXJUmSkCQJsfO5ueBZ4gDqF/jwK89l8iFuFsYyJePG3eYbga+HmA8D4MPAc33zIV9e5HT+7RcmH77ybN98yDvG1PqubpMPNz7bNx+2E4YvZF19ucmH1z7bNx+2Eoa3TD+p1uTDM5914EMMsWTCKWe818NMmA0mzHvWgQnFtZSg3pJ3rrnZvJZ6rtWBA9W9z2ZC7Nhv3vddZj8N7Le+1YH9xBohJIx/0mvYexwB3pvbast7GFwwXhMhNnXf4xuY8bLBeGe1OjCeuBISt6W/ePqVc8wrofxWB64Tok9siuac89g7zHIaWO75ZxxYTsg9MWfnbv3D48xvR4DfNjzjwG8YSslsTyy690Rmtmww2zXPODCbWCnEOe69E9btM6/hPveMA6eJey5xNb18Qlcrs5kGNvM9Y8tmGE3w2FaeBaNXZDOPHQEe273r0DyGrdEZLa0vmDz201198FgrIfbaPS+9bvLYtbsOzWMQcamF93/M5LHP7zo0j2FuXnreph0mj/l32fBYfH+LT6KWEjfSU4/9BONckQsue36nDZcl9u/yATnwWTshd3fPSV9gPssHn92/04bPkvt3+oCescj+fOyqX5m3ut/dacNpKUYvIWSbuLI+Y+2d3cxro8Brk3ba8Fqc0RPTICUExx8v+MalzG254DbPThtuSzB6KSHZhOz9QbP/dua3fPDbX1ts+C3J6ImpkBBToSrZ1WPerN7TYsNxKUYvIeSa2AHsvHDZcua5UeC5S1pseC5O6IHxjGPC1xZtvJo=
*/