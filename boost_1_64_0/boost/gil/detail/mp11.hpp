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
LcX8rzBOby9Jyu+Pf9NE4x1KVZDBt0pccA3u+VxN4BkMhW+moiwemhi251Z1ACvGxxIG1Y6Ia6ViAN5n4i4ITC8NuMQODY+iBI4s09fq+o2dXxvxwa29bfO1aooMyOAkjYAjrddwgxXgrNxlGB+M1Ttppheyam5CrKacmW2wJf0WzpS/PHK54OLBeA0Zw24uTPL3iSNWtphiv2HLEX/4kNMZfGDDnDCmS2QiLJilDe86VO58w9AxVdzAqfyzkX4pDQ6/mvqXYrvNscv5wE3MOHA6qn+lbhNB/0UTo6dIhXuwr6SlwbF6YKNlq5k6Go00t3pIlajXQNbFEFJOKRwuXjfhcpJ3xsQ+2d2PdDITLoKsEzu3Vuxl3zmIu97qogze1fzlWXFcW6Ck+TdW4skqNXj0tDg7TSSAD8u3S8fGgRnpdHetQKNHO+Uo9KkovHXGg6SnnA4K8IQZOs83D1Ksc6hSpgu0b7tD6fKZSPOACNYmbHMl89x/iPXe0RFTBSJxG7pYlGf7SGEVFxpu5Cfjkt1rw0NUCpk95SKcLPvOWPArNCLLx0xSg/mh9g==
*/