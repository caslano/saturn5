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
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
*/