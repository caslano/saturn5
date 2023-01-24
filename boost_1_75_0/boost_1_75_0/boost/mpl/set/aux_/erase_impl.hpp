
#ifndef BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/set/aux_/erase_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::set_tag>
            ::apply<Set,typename Pos::type>
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
XDFMhWgrSxSzXLxIJmIwmqw8wzqljdYkenITTdhJyF97nlzEQ2XojOh6dJ/vWH6KA0w5uh6jHJm+Mf4Lqym24SZzotjD7HTdU8eXp/uJf7ZcXhfDj5PvR3svr4pKPYLnTROBCKHoKfPvoQGKhvZsV/BszQ7dXofvhnJljkYtFA2l0AiNZARgXO0rvGN6fdDMhmwRgxTBMxUaE0LV2Wc8dMDF40lg3mb0m838zb2b9/ywllKSIFXMR/CLFsylbfJX2BbySQ/pszaryLUuS7IYe2WLFYwFgfiHXn9GzS7gICIuZ+d8tzWyiZRHN3FGYtIgHGTxB329h+MuuuUfl0EUfaVFJH+Ke0DrYlR78WjUEXpYntrleXPsbOa889GMnqeCgWeUnsk/xCiHTqHuOybYx0b0if8MTpVXd5ueMX9z72tuy1t0csTe8S13mse1PUcp2dlqSZpyZZuscSOlqlAarhFhHQOv/badcvRMWp8xPPkZ8R147VZOUTNDmBA3YnBK3WLA5gI1/ZPUIsW9UQcr9FHxwUYh0Aq3R/YhgPNJshHkpDZCklegEHsY4GeIPv8JVTq6wtjZptmH2FfvA/IQ5jfS523zyZYrGqFKimvRGgHvK/uNGBcZUEoKd1SpUV3UYzqHkzNTdXS+cqjupOKTZCoGnaxcPlvXHijiIYTndzq9226+gsnjyuGNqRbF4crPm9g/82GYSRBuYSjv
*/