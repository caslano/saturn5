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
a4nzmmIeZo2sr5+J/bxa1rcGHXEtOuE6bInrsQduRC/cJOvl/7mfYtiP5bGTrFcj650q642X9SZK/yXpcyzl/gfaUTRGOZatZT1tsDK2VeYASz1nZW6mifadMF6Zyyv1qpmot1TqLUN7XC71AinBUu9JqVcJfaXeLKk3W+Kcg7XxKWyMc6X/5uFIXIj+uEiZa1rE9iTJ+qfJ9kyXehGUXKk3RepVwSCp10bmoW6PjuiODbADDsGOOAo74WjsiirshiHYHScV5Arzd/ncjW4UjdG84I0VubQO2BRdFDm1rpR0qV+b0pL6ZdBR6t9SPC9bnlfjMc/LledVKfp57MDirc81uHjxeRXjeVk28vlIPjdlGM0jnyL7Zx064gasj5uxFW5BT9yG3nJ+Gow7cDLuwqmYik/hbtyBe3EfPoef4358gAewOnE8j8PwBRyBh3EiHsUp+CJG4zH971rK5x38VV5n1XCOiTE2VfFXrIUP0UPG0vSAcjgQbVGNFTAOK+FmrIxXsQrmoj3+jNXwPlbHW5hjI59nMEj6tR7/f17i6SNxeEscA9ANB2JPHIwDcBgG4ghMQT9Mw5H4OvrjKRyNF3EM/ohj8Q6Ox58wCGsSx0R0xBB0xlBsgmHYFtXYAyejN0biQIxCf4zGQIyRfncoo/v8wrlettMlv//0Y3GqYhb2xb+jCt/ACDyF8XgG5+NZXINv4y48h0fxXTyN7+EXmI038AO8i5+gNpZPZXsuYTu8jN3xM/TCK9gPr6IPfo6D8WucgNdwNl7HRfgtrsTv8Qjm4rt4Cy/gj3gZ7+IVpK9l/8vnE9xmYv+zL/L6pQGqsCE+hS64BF0xBZvI664ZHsMW+Cq2xDPYGi9gO7yE7fEX9MBytNsBq6InumN39MaeOBx74TjsjWHYBydjX4xEb1yK/TEFB+AmHIiBxRhLkLNeO3ag9H7D1To+oPTHB/yRv936W8YJ/NXGCPw//nar7QZy+ik+lGBKMiWNkkXJoVTayFgCSgAlmZJGOUfJpThsYiwARUNJo5yn2G5mDAAlnLKRkkG5sdk6FsC6WBfrYl2si3WxLtbFulgX62JdrEvpLb9r/n9MwuTS+v3/m4r5/5fJfdUsrIqZeMOBx4H6+UA9VOGRCZqQxLAIVQirSCxG3kzh3Idcfd6C5CjI4ymK3BBXRW7MbR6XJ8Kw0IK8hzX68QGeNb4Zm38v9Cf+pn2cMC7/MXUM8oID5aP/K5IL+hJlDTfIc8cptm96PD/BrQrRaPIm+CMnNFGdYMnvict21tTnklFmavS5oQ54Kj92leRoSD6TIjdU2T9sTwv5rvo7B+tvgP+HvbOBr6qs4/gENJQJ40WGgLwMVATEvcB4EXndYONlm2yMMV4ud7t324W77bJ7h4BoU6lQSadhYqGCYZFR4TsaFSkpGdlKKisqKkpUSjQqM8S+957/c+65956LG9yH+vTZ+fj45Z6dc37/5/W8/f/Paf8GuP5vgH/10lA5LxrzzB0nR1zeNHjCD35yz992tt0HJpHfAH89ScYhGZ/oyyG/8gNR32QeBnvB4XAIHAmz4Cg4HV4Dq2A6vB2Oh1+DE+Dj8Fr4PXgdfAlOgr+H0+E/YC78CM6Qd0D5cAKcBfPgbFgO50AvLIANsBB+GRbB52Ax3ANLzHeMMg7J+FQW9Y6xq+SvO7wa9oCTYU+YC3vBWfASWAR7wxWwD/TB/nANvAxuggPgA3AwfAqmwWfhEHiild9ebn/v0v7eRdd3m9vfu5y79y6++3k/cn/7e5H2pX1pX9qXRCxa7/+9nopE3P8H59iv7sc5tHPwvrI6GA9T4awgmLE20Jgksf/vhWL/5TtBHcVPmAvRVLg=
*/