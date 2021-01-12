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
On6vSYmrgJsiUzRBhn/a37R7mKFx8UB4tLC3EQk6ay3lNEkEAvw2Jeee1xHZYWVyNoPtlctU558VmQvIH04GJFRX8IZccjnb2z3ABT9v/QckpDbPMaMdkzEDZqxjN0AqKGagIxKJQM7MHYHGi0JaXfMssZtpGiARgsjepWg0QvNg/CVEu7li41LjRfiMHZWCNn9M5w/1J3hkrphnQNJ2M4OtUamEVu9a+ZijTkkvmrb76caw
*/