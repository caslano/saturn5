
#ifndef BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : not_< typename Set::size >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
yOF03Qc1mjcDSZGeA5rK1V+tcCkja2IWBM1X8SZpc6WP3x3LHJuZxUMGOnH+0LWkBqgGgDLEheTToXeshcQX4mbUf/haD7hPkUgyr/DkZHCbMVmsu4MjlSS4tp6e9a0t3K1nZcvs1QX+FjPtW5/47QBdybyBR5YBmwHSAT09x352cJo5/pHHgKyMxqXq75ytghAFOmDiLmmXQaR9xhhaSf9hsqcypYptRMyFvUb0ge1MurBg0kKfHK9YSpR1Bo+mmsH3RDKSIrslhdgjaMIU8KdtBY/DCP9Mps14trjHe+o2xu1MSR4bLN3UinhLDg435U6zQf750cyVETw3Q77n/wEKahV7yt4a5J1veGsxq36y22YpkrNwWMRiphMss/hvjqlebLZfkUyrOIzxjmUkvlwZS7BVMUtjn1WIqo0f+TVi+oli8ZtNhteDwyLYD8obtZPmLGhOqmmW/JrOLq7AaOz1OL7rtunn393UnrlxEG2Npt1Bdz7z5YxIT6lxxhx7XVlphhLS7JDP4QJ8oaPYlRVfq0ULKOf4iFboii35p6NDMMrlx5QqEkdw5HYCaC3ST19TKFuwC2SIS1pPxjOrHhCw1EoUWs188AhXE9NnNh2nb0kXLVWXeg9SnHVM7+IvNsiYPfRLUz7aBh8uBTA40J8h9hm0lgXrA0IqDwgdMK18CyQp7lECaO0q+bGXw46th2Zq2FMoBErNw0VK
*/