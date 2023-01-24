//
// Copyright 2017 Peter Dimov.
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_MP11_HPP
#define BOOST_GIL_DETAIL_MP11_HPP

#include <boost/mp11.hpp>
#include <boost/mp11/mpl.hpp> // required by dynamic_image and boost::variant (?)

namespace boost { namespace gil { namespace detail {

template<typename L>
using mp_back = ::boost::mp11::mp_at_c<L, ::boost::mp11::mp_size<L>::value - 1>;

template<typename L>
using mp_pop_back = ::boost::mp11::mp_take_c<L, ::boost::mp11::mp_size<L>::value - 1>;


}}}  // namespace boost::gil::detail

#endif

/* mp11.hpp
6zuDYLbnOzNVpojfXRtZpaAaqemToTOyqpeVqRR8E60uQF3XO4WNo2nvJwX6Bypm8j/unfhfpncDtXrEF24J8B9vdVP/yn9Ig43ou4ArVRTHKa88zgx4xuaNWbccHG3ps9aOaXpeskd18LNCC5FLzKl6NrEGva7xngwezyHs9JVpUnUZpZIALq6ou2NUJi17nwrOW/FSOl0YwcEswoXEQRrol9+gsheHyZR7IjpeWRUIq+8asv7P9X38bY8ggWt3g7JHjGLLLkVJesbinC1CVidRnFFJIITR6l3yovyBa/fp+H50NWwAYQVq8XQ0satpdr+18ZTHtc51NnUBiD1Ob153eAygXJiTejtyhDL6TnTEMdY9fAvIfQsS9meyHIgFesOOnaUXmgHTs2rDqypZgxd4QZzuBpfmC+ek1wE/W+agrYnQgJdgo3yx4uObO6cOUuD1qZVMxEZRK5uIcoWfeYJRkM+je3s7dAt9zyQ21xPZYUa1s0OZcyjuaVmbF1QBXru+p0Vmxv1q76bY2d67RxD6BjHTxa03IafpQM9IBVOSykcQshIB+h8YjLIhSkHLH+3lpd2Rcarq1/PYiOSgzeMc9PCSFNZMxu/yNPbExuOoOzYjh/uuQXICC5lQasJNb1nxK0lpfHHmxd6IGk1Hf4TaBvVsBsLM1oM+NmM3En1OW+COfh+yE8avD/UonXCnQ0iX+K59B9x4sNXm
*/