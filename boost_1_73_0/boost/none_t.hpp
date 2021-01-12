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
5lBDXsFAmXGgPzHQPQYQ8/RnM5A1DvQeA80xgJhT+IfooTjQHgYqMoDsBLSLgZQ40F4GGmgAKQT0NANZ4kD7GOizfToQD4iVDER79dkCaD8D7TCAKOVGtSI3DvBnBlhvAFBKuVqRpX7Gxl7OrMlqRTbcmjZVOBqdjqaK/EZnflPFJY3OS5oqxjY6x6oVhSFnIS8kqTTTQsjVdSn6zK0pVrEYs6epl7AtIyDubkgaSWvpXcbA
*/