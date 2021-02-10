// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP
#define BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using convert_integer =
    std::conditional_t<std::is_integral<std::decay_t<T>>::value, U, T>;

}
} // namespace histogram
} // namespace boost

#endif

/* convert_integer.hpp
ZDTJ1RTwgyGXGBkoNtdwxC9lMgIHopcCsSwNbW88+QE9gWbR2eRqOn/Z+YJcoG14YkW8gXlXfoH4Tm7C4Ai4/Sb3g5BTIQDXizCANgc69soh2iUsL8ZFYN/rMEzUsgLxLoJ90ofz9DuhLXb2xVZiQZwhntfXUdvYW+hrbBdZ7RxEzXj0Xot6zhRzXIAFgqvnY4woMn8R1rwA2hfKTKfdZjBqtv+cyhZpXCjhfrcCBFg1P3HHn5WcJih90oJwtHv06Gcl4tRSldpOD+hoHahqg9pHOt1llRalsz1V1BoXhUaps49ZX+saR9d/39rXalDrDFJQODtRRXOmKGidA6uaHYpitQs4s4keQIXV0UdnMkzFKe3nZpicCdmrUxb3VA6WmTstswA5XtznbCUxo/HZxDsdzAd9wYE7ikpskZvdw23f21t/5CpA9fYquQNofvtN3FtkHy3Wjzl7jANVuB2rnZ81ZKGwLmMd2r6NKvd+D+0pBVZWQRUFDsElH4xoUsVq/NOhFk6rnFBuGkr8ASBQHkMJ5iIzoTNGUL4SIjowh4zSJLg1R3JK9OZFpIDs2X+KfoaSR4+UhqmcKE6Lrluz6XqihpBHIrorDzzABT1IlMna093uSmlsq5TaNqAfIIx6L3FO+xHMdZfJUCd+
*/