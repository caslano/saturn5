/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_TRAITS_HPP
#define BOOST_POLYGON_RECTANGLE_TRAITS_HPP

#include "isotropy.hpp"

namespace boost { namespace polygon{

  template <typename T, typename enable = gtl_yes>
  struct rectangle_traits {};
  template <typename T>
  struct rectangle_traits<T, gtl_no> {};

  template <typename T>
  struct rectangle_traits<T, typename gtl_same_type<typename T::interval_type, typename T::interval_type>::type> {
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::interval_type interval_type;
    static inline interval_type get(const T& rectangle, orientation_2d orient) {
      return rectangle.get(orient); }
  };

  template <typename T>
  struct rectangle_mutable_traits {
    template <typename T2>
    static inline void set(T& rectangle, orientation_2d orient, const T2& interval) {
      rectangle.set(orient, interval); }
    template <typename T2, typename T3>
    static inline T construct(const T2& interval_horizontal,
                              const T3& interval_vertical) {
      return T(interval_horizontal, interval_vertical); }
  };
}
}
#endif

/* rectangle_traits.hpp
8+itQsFtFAobBKHxjaDQ4QwfTXhbfoR3b/U7WNCL1M4ENg3OInpV0Pom77hO+9+CaPDY6F3YSd5fUWNT6lZ8IdMcKjVkQmfMYKeOOi2o3t+vlk/2zlPNX93D5IziBFE7ihXnlBC7fLKniI4DTJYlQMudMTTb7OTC+R9QSwMECgAAAAgALWdKUjcBxYycBAAA1gwAACEACQBjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxMzk2LmNVVAUAAbZIJGCtVW1v2kgQ/s6vmLiigtTF4Fyr5ijV0bxdVARRIKqio7IWe8HbGq+1u86LEu633+zaBpukybWKEXh3Z+Z5ZufZWZzdl3tqsAvPPp75evjg20ScCf6d+upxb8+7h+yDUVN8P0fiwCbk3mvC8yH30DAhXs7yUY897zmiqc5N/zg6curpIa5gmI484MmtYItQQeOgCZ39/Q/wFty227bhkMSMRjBWNJ5RsbDhY2BW/grJzU1L0k82UAUkauVQk5BJkHyuromggOOI+TSWNAAiIaDSF2yGExaDCinMWUThYHR2eTo8seE6ZH6oQW55CjLkaRRASK4oCOpTdpVhJEQo4HMMR/CASYWAqWI8biE3BUXFUmoMTU8iyYFcERaRGRIRBaFSifzTcfxURJi9
*/