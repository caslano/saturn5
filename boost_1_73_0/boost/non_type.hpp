// -------------------------------------
//
//           (C) Copyright Gennaro Prota 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ------------------------------------------------------

#ifndef BOOST_NON_TYPE_HPP_GP_20030417
#define BOOST_NON_TYPE_HPP_GP_20030417


namespace boost {

  // Just a simple "envelope" for non-type template parameters. Useful
  // to work around some MSVC deficiencies.

 template <typename T, T n>
 struct non_type { };


}


#endif // include guard

/* non_type.hpp
bP/Y5B3Py/6b78YGpm8bJO391J2hC5uvVNRbJMgEv6SbZm9pvWSvVTwwBMzBgFAvJtvm3cFOOAgV/oesD6jlDyiTQnLxe4uOqOUFX4uaTkMBbuHSQGt5R99dcHHY0990pcpuaFX2++Qu6IYcwCZ7MOhcAo9HoetFHlza4d2xWy9bfX+Db2841JJDoubvAgi7gku7cq9o3lW0KVI//ULitfh44+OKIly6/gSZN7lqUJ9t35Kh
*/