
#ifndef BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct has_push_back_impl;

template<>
struct has_push_back_impl< aux::list_tag >
{
    template< typename Seq > struct apply
        : false_
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
i/PU7+rKtaVcc6Y6fFe3h+zHvbE69sGa2BeDsB+2x/7YDwfgOByI6RiLkzEO83EQzsPBtrYPpWzXmEperPE3MNj7j1slx6k16IvrsS5uwMa4EcNwE0bjZozFB3E4PoQzcAsux624CR/GR/AR3IHb8Bl8DHfh4/gSbsfX8Qk8jk/iWXwKC3EH/oRP4y+4E3/FZzGAPDyH9fF5bIm7MQxfwEh8EQfjHhyJe3Es7sPx+DJOwgM4GV+R9bbbINeuck2rlJsvbte0MauMLTAYW2ETDMWW2Bo7YBuMw7Y4CsMwA9vhJOyA0zEc78MIvB8jcRd2xIPYCd/Crngco/BjjMYLeDt+jd1Q7Usp1XWbl39Im5fXMQgPIvNx3pJrWLm2VeZT8jMDlWGY5Hs4+uIo9MfRUg5jsBmOxQiMxyhMwJ6YiEMxGcdiCibjeEzHVMzCNFyKE6Q8JuITmI7PYQbuw0x8HU14BM14EqfiOZyOSmZmYDmcidVwFtbC2RiG+fwXiXfi7TgH++JcHIzzcDTejcl4D2bgfMzCxbgMl+BqXIoPYQE+isvwFVyOh3AFvo334QlchWdwLX6O62Q9st/JNbhybW5dH60t39uW9uGyPu5HX9yMQfggNsGHMBS3YFfcij3wERyCj+JEfByzcTuuwSfwEXwSn8Fn8GXcif/AXfglPos/4HN4FZ/Hssp+iL64V8p1H0bhy9gPD+AgfAUz8VXMwddwBr6OC/EgrsNDUp5v4FZ8Ex/Do7gL38eX8Rh+iMfxE/wAv8IT+B2exIqU44fogx9hDTyFgXgam+DHGIqfYBs8gx3wU+yE5zAaz2veCyxT7+/1XuB/0zuBDet5/yXvBUYR7xhCPmEDYTfhGKGQUCmI9jFBnnYxnsEzeAbP4Bk8g2fwDH+n4eY//4/PNiVNbHMjnv8rz/d7at7tPyX3eD8SahLOExpTMRA1Wn2+n5iUZDTnxBvzDPJcLQz1g/Pv//nJ85gcgixEyYehmjyXORjB9OTkLO7f9c+aSLcpM9vgL8917fMbk61L4PfyjHc8y+BJs7IYy7TDTLMt1/ZM6Ojv+m/ZLR4t7yGRT2X8ORlvEGEdrz3GOv4e4zzzUctqjJc1owGE0gR/QkXKMn+MWlZJ6aZso5JEoxv9IVbTlI9kyxL/PQ7x0xZD1w//RnkeuBabk4cdmvhNmZnGpJzi+yR0Ere6Xnaq5ed0veiei5kyrWkOv8Oa5nwpw9536Mt0pcPftzr8/UcZbynrpMZY+btDGVyWh7ofyzPEj1Apg/1j1TJIT8vOYU0X35/c9ZbBVU0Z+EuZ2JaVM9VsjJfvL/rJM23t32zrOiDems8ZUg7t4/Xl8mK8vtzecfh7QIL+76EJ+r8vdfj7Qw5//zlBX+6VE/V/HyDjT8t4UqLz9XJKns3PkGfzeYRWLDNhnLperLuFG8/mtesl2ZSRmJZJGcp6cSxDP826MWeZckxJpnTbOvN1WGfVZJ057m9LLWmkzkvKYOs4Wx7de+br/BluyZ/VOn/me/Of4Tp/9lryZ7s36pmsi2esrp8dW54RL22xdn/NPov29A1/Yc3sNzdOLPmz+JI+C77WM9/5BjmHyrl1jfIcEmfIhv6VPIP5FlvjdxiO3+MwvIRj8EdMx59wAf4bt+DP+ChexeP4K36Cv+FZVN5jPo9eaH3/Vs5TGCDp0b5/W0Hq6itiVfTGGlgJ/bGyLOekQc43ch5aQ1DaER2W5QzQvD/si3Ho7/DecCcchqk4HE04EqfgKFyOo3E7jsGDeAe+g4n4AY7DbzAJy5OGZGyARmyCEzAWJ+JYTMc8zMACNOFKnIRrMQst5VRKziVyjlHy10gpJ1SGdZK/9ZI=
*/