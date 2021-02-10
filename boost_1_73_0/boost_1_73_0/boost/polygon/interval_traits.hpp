// Boost.Polygon library interval_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_TRAITS_HPP
#define BOOST_POLYGON_INTERVAL_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename Interval>
struct interval_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }
};

template <typename Interval>
struct interval_mutable_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }

  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLICY_INTERVAL_TRAITS_HPP

/* interval_traits.hpp
oyFXPHBEChKjSNsiPYYyDxuhW5TH1mKQUMRM6ZsUXGpXV6GIpwSpjtrKIEs5OaI6kFAgqMw2ZDzA1AibzEsXRU1NgRe2ZhxvAIJTMGC1unDUtaDvSSZt+HTUe98568Gn1ulpq907h847aLXPtbEPR+231HpGzlLA6yRFSc5TYHESMQwKnw93OZWfGPejLECwdPP8EP2vjdCaGOaoUn96KMY4wH42pFFwtuC41e1BOWmwR3YrUnmK+eCHXgpbkRgyvjc9lnhSXok0mB7W+tyL8fOr3S97IysHZ6fHviDzGWfKlaiypHYpWFCv/FMBKC3BPlDpA5qzrPoeTRi3d0bZoFYdqdzeQtWI1UGbAjigMrjSG+AgRayVckZxdjLXy2dSiinlJtBDl7rrdt65Hw8/dk7P9fy3yqzEh73Kt1F6OpUiNSUmM1sSzPxQyOZZ+6jXO+z23G6vddrT+XJFzmUWKa3XFyLKC+NSwfkQg9FoaX88QTNlc4hFquhc8VK2apsqbJFFx0Bl+5fmrqVNEkr85KZWStljeVs3hJ5Hc9v1uvHlbOlaEqeQzHvAiT54TXRCyiAUNEbdFFkKxlHJQtBwgyJDCsUUhtYziUasZimy1sBrjziEDV/Elg0vTAHoXqZsV6YW9hdTBZqQGw+V
*/