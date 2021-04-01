// Copyright (C) 2003, Fernando Luis Cacciola Carballal.
// Copyright (C) 2014, 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_NONE_T_17SEP2003_HPP
#define BOOST_NONE_T_17SEP2003_HPP

namespace boost {

#ifdef BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE

namespace detail { struct none_helper{}; }
typedef int detail::none_helper::*none_t ;

#elif defined BOOST_OPTIONAL_USE_SINGLETON_DEFINITION_OF_NONE

class none_t {};

#else

struct none_t
{
  struct init_tag{};
  explicit none_t(init_tag){} // to disable default constructor
};

#endif // old implementation workarounds

} // namespace boost

#endif // header guard

/* none_t.hpp
USTgiishLFwgHJvKpQjSnS4UL/zzY8/gv84Pl9dl2g96qNSX6V5L1hujaEomLVOjYbCTTOd0+ION0xbcqTMs318KrlFM1D42QOdcgXfM8PbggyeiTvYZAZ+Fh/po6p4bwFxv5vtA/ww01c2Tfoy9wSQkYoef7uZq778MXbMXnja9DTyNw/6KHD4OKEAk7SRlydCb2A63kM6OAjU7eGieu9lQx/SASCMUHqFDcryeWj5sT0ksjQfLQrHBUyZ3ryOKuSVYMXb6rreGkDD2e1WzI5wJTDR7V7O3vfxVOuvb1ioiWdklzoUnQTeKNKRquCjc8gjCPxMcwANqkUIy5PTtlNpukfYLXy1GTYtrD2PCmgrbE/ENkFKeWInW0Asc90o8nmvHkniN4hKq6nHfYf4+V+1zEhdNkbY57YS7Mpoqs/XBtJo77Fek2toQAFaG2/uKtw218xmgeTQhhwBt3s4WQbqhz48hp/p1RhARbuhEj//fKS9R/w5i2EP9TKx68gU1zbDj9uHGGLocFcMEl2TlOL7skVbvKzK9cxt0jwPTxjqBiD0RK5bDo8Bjog==
*/