
#ifndef BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : Set::size
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
eB98iE+3+fN8B7YNke9/jcVGy/6/tDdB5v8Rt5ky/89Ynuw1U4gMWRPrAPGIy/gfTNb1+8tYmqzNnHqx+eUl+f7XWN5a2f/XWKawk43lyjdO1YxFZY3GWsYK5dp9OjJkDtBZxuKy9sn56CdjoA2NZVf2cWsM6+5tu9RYluxdmIF+9/lyVxuLdfNyrzWW0UbW/8OO773O7Y2lp3p7O2ObXLe6G9N99Xuj86P+/OhLuTG+bn9j+ad4GXcbS5Pv6e6lnKz3OhI7JK9G41P5puFhfP9HWccep66848vBV7J3w1RyQ/q6p8mN2Z7Nhsm3r3PR+duIYwvQ5bXSji0+Vtf75VXK9fOxXIltd3g/v0E5yY238L28y99ILOV97XvEQ+4FtmJvjahjH9OePKd8hm1rfdwKYKNl/49jPpX9f/G93Dv+g5g3THLsV+zNl/E/2pNvLo6S99Pl+9+mJuMWf36UNBaTd+DljEVkTvRJxnIkN6oay5PvEk4xlpnsfVDbWL6spXymsdx2vh8/z1j2af7cT0eGPCc3Mpb1iO8PLkG/phUduxLbGsv6f9T92LPWxgp0/A/9unm/3ERd2VOlE3Xl+a0bciWWvWALZP9f7JXvse8yVijjB4OIR3cvYyjt7fHn732Uk+eZGL6X/n4sMnT8z1hc9nmcRHtveL88STw+9XVnGEuTfHkWJmthPodcGSuYT3uDZfwP34sdr6DLHq/LCvwnubsaO2T/srXoUsvn5Abqyh5pm9FPnrvjyO3h2XbYI/78/ZTckLpfkRtHZP9f6sp3n3uNZchc2J+NZcqaIftpL8OXO0Tey337n9RtL+N/l1i+SK6VMJYj9xtljZ0jcwcrGsuStdaq0N5sf67WhMm1O81YuuyvcYax6E6v37nGCn/1MhoYy5Z70YuMxSXmTWlvivfzFcbyy0Yda4698szUCv3Ez23QRebHtjOWIXvBdjSW2cTrd4uxPBmD70m5X7zvb6M9Wcv2TnTpKeN/xtLe9+webPvL+3kEcmWu3wOUk/W9H6KcrAc6Dib3KhOp21nG//DzGl9uOjHa5+M2y1hEcvJv+H6kj9sLyJD+9CVjBfJd/svEQ77bWU5dWSfwdfz8XUnH8skXWTtmPXkq45jvEg/Zf+YDdJZnpm3UfdfL2GksV+f/EbdelR37hva6Rh37nphPkPE/fLrLs1/QL93H4yA+qF3OsSP4StbVTbrUdJH3M8WNZXbw/W4ZYxmyHl7UWOH5nlU2lt7dsxrGcrt4204zVpDlda5rLEvWGzkHGatk/w90vtLnwYXod7Os/4eMqMz/oz1ZY/oq2pN5ANfA2nl2vbGI+KCtsRzxwc3IeNHnQVd0kXHqLGP5sk5WH+rKXPE7qNvc5/hA9JN+fAj+kzGe4cRD5qrdbyw23LMHaU9se9RYntg2AXaG7P9Bvkjf+RR+kTGymciVd0Vz8Oly30c8jy7bvK8W4oPRvm4e7VVJdWwZPpV1Ol7DBx29r9bQnuy/tQ7b6ns73kGXTFn/j7qnyvgfdcV/n5D398n3v+TpTF/ua2NxOVe/wy9feDt+pJyMh+2jPVnj9zd830a+/6U92ecicpn5T+JbzFjWZb5caWORBl6/CsYK5f65krF06Teq056sI3wqTHxVx1hcdDnbWI7kWj1kyD7LFxhLkzk7TYwVyF4LlxnLFLnNjOXJe8SWxqKypvZ1sJe93ExkyDW+A0zs6AITGT3w6Wsy/odP5X68Hz4Q/w0gbik+7wcbyxXbhsFkn4ZR+L6YlzEGn0rdR9B5nffBeHwlz+KTqXubjP9hx42ePWMsv5VnucRjnGfzsK221+9F2pN185Zg23LPllJuYQnHViH3HM8=
*/