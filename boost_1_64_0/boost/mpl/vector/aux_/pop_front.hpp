
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
5bkOM4i3TvD3Iep3BbcSX21h/Y+gXytYx8TndbHkPY9R37EWvymSefdAv09Dr5pZpx7Uw0zDDhHH1Ziw5/gV3vCKZRVm6ltZp8ibLfmCNPi7DtZDuIG62BuJhwpZp2/Tz3fgAwuIFzaiH05TV/k4ccaz/dU47TSQ96XeAh47nfggxYS9XY4/dBQeaA5ydTW8PjxdsY48Rif9imJ9PkK9USfj+DH1EnvRi6epF+xknseTD9xOXT3+ZWSWDt6UefsdP7rNQrXnduJu5rXyR3ixzfDoDxlU+wbADz+GnAYw/zwvGf84nXxaVwDjgl49lAO/0IJ/YFL3cyN/W8p8xM1Hv5+D/2PcQmlflS3yy//T70JutqO/0aeRX+KvIMfdyHGdHXbEqKfO3VL1x4dxmarlf4lH/uJzjJIn8zb0Yqy6vwP7DoKpg152q5pPP0v8/onoSf7eYov/gX5svJa8JfFcwUp1XaUZ+Z7Afbv4vwm5LDeo9jxPXtsbf88Cv8oMb0M85VNppK4SvnMz/8efDideM8PjNa6gfo+6Kjf4+prfkdtC+tXBvCFfcS3od/pfmYWcXgV/TD6sIQh5bcLvupN18z73eY/xOIscIj9xr9DPHcgDfIoN+tXJjnjZAv+POL0T/86ZOKHoZuLkXawveAGvay3hmWmHK/sjhlCHotXnDyA//AjPt4YHe199usyHz5yr+lvJPIfP4/c71fMC64kbK5Hzf8Fj5sNPcd8O8uTFTsQp7HOJvhYe/UnivnGsc+IY21zi1Lfw/yaxXunHun7wrUeZrzP423ricnfigADG14n8Bfm9Bi/uC7+4dR5xAfH+ob+wmzXMG9fZpBF/eavr69YSPw1Dr2Thn6EH9MiFTQHx5tsm1S7q0xq28vfj5Pfi1binkF9aVmiiDkE9x7mGfOtJ8mtj+T3xWncHeYDx2KOp1KEVsW/rLHUt+Jsp5OdLdzKfOfA65O9K4cMDC4l3bODH4Y1KvjeqdsD3uJGnCD2JXru7vxqfQ+jhUvI2D6EPf8cvaCFf+Sb+qy91rsvI62wg/vubdZWJ3if/191OXUgJ4+sFf8p1Wfjh3Qby2PAmyTNU+449gb60hAc5gb1qxw6vpF2prMMm8gP+8L4R6Ll66r+oK6+biF66Hnv6T/gTe/wDPfZ/KDzldxZq/MbgD5CPqoGfdPkJXi4a+zFkIPsImNe58IRm/s++NZ87GIeF8BwJ+KmryHNSl+C1CD5jOv7EdAP6mTwNPJ9LBnJSRD75GXUf43Osr2D0YxHrrxI+ZDrzPY1653fIZ/jSnmjkFz3eRXvt0vGTB1EvDk8WHImfTX1UQytxWRX7N23QW1upg/yFvM059B15dOdi9ftqM/GnnjrfJEsll88wn/CFKQ+ayN8Rv9Whd5rwM/CTtn6HH0mdTzL7jcILDNQLk0ch3umgvtaL+qxDx+FPx7Fvh/qcQFs9PDv6qIj6vzPEJ3+hL/FrU5bQ7heR83CjGi/0TVmgUd1/LX7VMHgob/yGYcjFPPITLsRnp6nLjoanuQvepBr+5S/iaJMWB8IXoTcqq6mzmTqQ/uOnkk+KpL60erD67DBZoE/gKYzYiZ3q7z7wjG5G+k+9xbIHqKMaTJ4CP3dVKPI1E/8inXVIfiKJ+V/nOoh6IepHPYzwzfB69mY1DnnwOy9jR+BXg4uxizPRD08RV/xNnIOeTr+JcVmF33+bVj9MHu4YvH0A8WE/2usAj/87coT/74Ad22+FvTNS5+Cj+pOj7aP0IQ9lIr7rDy/9i575pp52LPF5P/K+m6jnmG9Q63wI7buVdhdRv0K7trL+I3fiR32GP/sC+bvP4B32on+oZ234AzvwHvoG/7o=
*/