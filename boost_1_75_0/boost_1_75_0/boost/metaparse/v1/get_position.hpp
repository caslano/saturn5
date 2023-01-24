#ifndef BOOST_METAPARSE_V1_GET_POSITION_HPP
#define BOOST_METAPARSE_V1_GET_POSITION_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_position.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_position_impl;

      template <class T>
      struct get_position : get_position_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_position.hpp
V3hVC9OVXDZq+Z3ZsE1NY8+Xosp8bf47ZPTK8BKO8NhkNnJTYORGQsxI/7SUK/MSSX9+qAwCCrFe31juAB03AoZ1alU06Tezydeaof2+yqYMrmxESQR20Avxq0OvdBQloLpTrXv0SnZiyPX+I0jP8NCmN2y46XVDbdnynd+uO+2MJZtmzEsowca0Sf/xJ9x4kE0u3et72Qj/18NdY0l6Rhbc9zJZfyxB89JZqjtPzbdj85IkC+nKvxmyb5jG48fXbYT9uwjnF4hj6XEb7BxAAHzn2Bw2jG+9DsPYVA21naJow9jAt5N1XUKxh00l5X0cOxguZhH5rJ1nVwIXpAVv6DzVPXRkQt70qa7COQmx/jkh7ida/OcWihiSvDH8Bq9ajTewV0TSTYfnEy8dxO/wqTvQUsHuiKA7vmJ3NMUZIRS6szM7g9D0TBSFxsGqQdAMowK7ga0bx2tUKChMRPnfkoukRREAyYhUtzWtX4qR7vHafJ7usWU+9QJkMEuor9wpr5wPKNY4QIvnEqx4jZbTxmQL4gQe9XlYX/PmxD0AS8KJxIy+eCSh24Yz6ehsPPmdPHn9cDIcJWE2yRYujPOiMkbEWSJrDcfztDuKX8JlMblfvsJJN98SFnGcX85VgOjyPQTHnsuFrV9sppCHDL7uGf3ozh+f4BjXuTzeoUiheIcMc7wDnBS2Y1pvH65HIQ/f8foT5C3JVozYUbaI
*/