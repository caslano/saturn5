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
RnjeHyJuuaVCH2LXJkv+VLMhtoOriVx7OLTRUmU5YqncvgLXa+Tyu1Xpu7lV6fu7lbyhblWq8W4l72a3kvIEuD4iF54wfECu3eD6mFxvcYpj4HqDXK2cW5pH5TYNXNlUy2UeFVrDoY8z9xK7vmRXule5hrCrkl0rvUrKRua2MfcSc68x18Jcb59y5flUKK7lz8L3QCYeK7S97AV/Qry/jWn5io3av8mA/+VUWiES73eJ3+cyjO5JmaLJ35gUwu0=
*/