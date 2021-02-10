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
R25csZTQHdJz6XLha5xodwWLcuwge1gSvywHy49POvPl+hQ4APbj9joOLwOcLeXOw6XjLNz5bPKRdTZBypfAaV0ardM6BoPlf1n7u4xhQdalzY0Y9EkSbERJImQ0tqlpz6VWOBbewNZLPrte6nqbe1w33uQVml6YRHAOteSUwLc6PEWoanST0UDHh18PQogFqzE61gQmDhpOxw9hSnoQVg5bjXc0HupY8etBOLFgDSth4Oi8hK+HMRMK1rTd7B3n0O5xavuHpCrHiF8PwogFC+s6etfBkMP9C46Wet0+uNvtGrxLx14YaPHBQVixYHXzQc99+GgghXH35fEgrARbg3a+eG1gxQeHIYWC1TjH04HZfHxwEE4sWI3TnjomTnxwEE4sWI3zYr64RNdAw3oR78AfOQgvh67GPP274xh48cFBWLEgtwCa9tMWcgwdwBckSu9oNNe9AzbWvBLsqHlLnVrzjlRnwzu77iXxqeYdSWbNOxpgNe/s6Vn9q/rWC2Vd91byTdnLqm4fTBz7/dDoeC/Meun9urB02iwDHE21ZA3n83djy1Ra6zj+HJSWZ5vrEHhqKll+XDhzd7DCLTO9ouRxl8W3ibe7A0/d24M3jpMCmjQeVmuOuLrm99bybG7LjQazmeBKXMepL3z8
*/