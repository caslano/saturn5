//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP
#define BOOST_INTERPROCESS_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/variadic_templates_tools.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

using boost::container::dtl::tuple;
using boost::container::dtl::build_number_seq;
using boost::container::dtl::index_tuple;
using boost::container::dtl::get;

}}}   //namespace boost { namespace interprocess { namespace ipcdetail {

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP

/* variadic_templates_tools.hpp
LgOeIj4uh73W2X5Iu5RDPGiHlMOvTZ7v32myvo93kv3oLpP1/c0my9X7gblqXAXmq/Am6+tPmayn7wbOAqJvUz9+GfgF8BWT+/OXapzB+/+q3gP8GtgY+Cqwg+q/JvfjT4HTgZ8DZxIf5+OYdT4b2pLkqzHosOSjzM9699WqPah2J3rJtX7W7yv8PO4sBQ5U+fazPeM6IMlPNe4Dr/fzvO12P+fzDrK/MH+pskP4Wc++CbhS+G4VvvXEx3J2FfB3wFuA9wNX+1nergU+C7wV+IGE/1zCf03hOb+zTTnji84t4/y2A02VecFGH4+rd/l4HLvHx/m518f6533Auaq+gOVKD/Kx3rnVx/ajh4GqDfwB+CHwER/rS18BVR/Z7mM7yw4f2+N2+lhvetLH48BuH49je3w8H3gaeD/wGeBW1fd8bA95TtrpC8CPgPt8PD94UcXvwTgBbAB8GRgHfAXYFPi6j+0b7wMzgId9bM84ot4L/AC4DPimyg/wLeBtwHeAT6pxwsf2hqM+tjN84WM7wzGgx4t26CM7A+VX5v9yng54TOf8/0Yf6/+3+Fj/Xy32vzXAQapege+p+vRxPd7hI70N7mwH+o28Z2XwLAw6D8QpJ2O9rE/Fe3n+38jL/TIRmEZtgdtvay/XdxLwcmVPBE4ld563NvOy/bAFsADY0sv2uVbARcQndgCVxkmit4p86AbaQ+0MfgGeB20AXqjkg9g57gmwXNgMzFB9MsDpuB84UbU74EzV7gIsPx8CXqXaH/Bm1f6Aa1T7C7B+9UiA+8l24MvAxwJsH9wRYHvm42I/eAJ4TKUPqOTAM0BT1VeA7Z3PqfSq9gZsqNob6cv83Fiek1T7A7Y1OZ29TEon6TkHgKOVfhJg++CbAZZr7wLnyHOhPKuKOgRcBXwvwPbC94HrlT4XYLn9QYD1ug+Bf6NwbO/7BOhR7RMY8PBzJD1zf/gsQPKSyvV84JfAVkp+AjsDvwIOVvJRlT/xidywvhFG2Uj7qguaKu0ry8/1mONn+ZErcnKmzGtny7g8R+zQ+TKfLfDz+Ffo53F4nl/PN4qnVT0vf0na88tenme8AhxJd+7zvPyAl+flr0p7TFTMV3J8l0t7TAZFS3v8FfhaAjd42W7+Oy/Pp+708nzzLi+P33d7ef59D/AW1U6Bv1J6vZfb2/1ezscDXp6HPQh8Xp5flOcvVLv1sv15q8qHyeFjgNu83H4e9bI9eTtwkvjPVnITuAD4OPAGJTe9bD9+ysv24N0qXiU/gWq++7SX5B/Cs333WeAlwOdUvxd3Wd+Q75uwRuKyvtEBfIby8/J86xIv259SKDyN7/LdCOnYFL4TaJ2Ubxev2DmAQ4H9vDy/7u/l8T9N5MoAKc904AbgGuADwMFSftOAr6iq9LKeNAH4lqpTL8vJSV4edyZ7ed401Mv9epiyF1E8bOeYocoHacv2Un+m5wR57gHM8bIeksv1gHSwPjLGy/12rJft+yO93G/nAK8HzvWyPpUP/AuwAPiJhP9W6WfAOso+DewELAV2A5ap9wIXAAcCF3pZX1mk5Cvwai/PLxYDrwFWANcCr/Xy+HQdcBNwuXq/sosDHweuAj7r4ffLeCR7y/FOF3t0c1mHbCXrkK2BbYBtfNwv2vrYjtlR9Or2Pq63DsBScuf3LLD2O6Ms5D3R8pvWA2V+v1Tm9cvELnxjgNcbrwuw3FgeYPvk9cCR5M724ZXALOLn9rMCOFeeg+utJ+T9Xpf11pNiD/8+wHaAUwFdPsZMDtfOpXwGezjdQ4ARqn15eBwbLvPjEcDmwJHAVnQuEsvB0WwHwbOWb6nynh4u8m2cvGeCh+XpFA/Lp4kSzyQP2yk=
*/