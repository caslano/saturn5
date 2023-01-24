//  abi_prefix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# define BOOST_CONFIG_ABI_PREFIX_HPP
#else
# error double inclusion of header boost/config/abi_prefix.hpp is an error
#endif

#include <boost/config.hpp>

// this must occur after all other includes and before any code appears:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif


/* abi_prefix.hpp
OpBjtSdJ+6hhPVjTm4Xap7DNfr+dGsTiBKXfOzL0O39h0oSOFmMSwmgIqubuVInM7Za5ywbRqFgi9ciHlYRarpU4unSfo1ELq2VSscMjlTkHpTPitdjd4TngTRjlviJ/fiDhL/KFjTL3ObER1rAXJd3Ex4Mm50rA7wY0Q/OYdNTlM/s//f9U9DfEx8oSyFwxoKJdkDZyXS335sZ+bMzb2gCmJjXnt2TW7GZGO05I9J8pgdotTQm0/wayaG8MZGVR3f4YN21ili9CjArebCI3qmFLfgvbhejpWCDpKBU3x/REPXtiqf00NRqaEi4yFl1glCGrYkpIV8EspBK8YuZhroNvcZdVb2PAp2avfoL5oNuMVzgYyEc19ptgH8rwHT/AO5X60mn1WqeW6dz5lP2hhZd9xYQQuyGHjoj0XZ3dT/D7T7pprdJFF6vd/JkpJTsblRYzwKzYzV46dNKEVzWi+TfDqBfVLK+Gn4aOzm/CT29vXwf8rFq1egB+1q8fHYYfNLrh3wYIx0Inbr2w9ocympfLiwOCfa+MLv01Ly4V+qA4dScvTtgfg+IX9bw4Zf+bJ2WU3cyLNuESFF/8TsrljfDIPhl9797X8EvEjVEZcEN50nPKoHpEG3MM4aijSKtQG7yVvjpHTNukjzurXTdi94jTq+X5tgZK/L5g0u/LbfGXhu4Q/Kt99+NwSZ4vkszzRWvzkjgZasnv9Lf5
*/