// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP
#define BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP

// Daniel Wallin discovered that bind/apply.hpp badly interacts with the apply<>
// member template of a factory as used in the optional<> implementation.
// He proposed this simple fix which is to move the call to apply<> outside
// namespace boost.
namespace boost_optional_detail
{
  template <class T, class Factory>
  inline void construct(Factory const& factory, void* address)
  {
    factory.BOOST_NESTED_TEMPLATE apply<T>(address);
  }
}

namespace boost
{
  class in_place_factory_base ;
  class typed_in_place_factory_base ;
}

#endif // header guard

/* optional_factory_support.hpp
TVQU1czU/wBQSwMECgAAAAgALWdKUrSLr5eaCAAA8R4AACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjY0My5jVVQFAAG2SCRg5Vn/c9rKEf+dv2LDm/YBkb+AnaQJcabYJnk0NngAN5PWHc0hHUYvQqfqTgb6kv+9u3cnCYwxZPo8TafKWEKn3b398tm9u81B7fe7SlCDrZer/1y88Kk5rhLxK/fUw9Su+xXMP+S6wee2SQ6gYPnqVmE7y1eoaBbXzvKWfrvutoluSDe6HRDnjUs/cQTZiPNMxIskuJ0oqJxVof769Z9gDxqHjUMHzlkU8BAGikcjntw68NbXI3+esPl8X/J3DnAFLNy3ooaTQIIUYzVjCQf8HQYejyT3gUnwufSSYIQvQQRqwmEchBzOelefO90PDswmgTchIQuRgpyINPRhwu44JNzjwZ2REbNEgRgjOwr3A6lQYKoCEe3j3BwUT6aSZND0LJQC2B0LQjbCiZiCiVKxfHNw4KVJiNof+MKTB15m/v5ETXNLPqMSU7YAEStQAlLJHSBKB6bCD8b0RIfgYJyOwkBOnEIbnCryD0QCkochyUK+gEujNoeBdY9DZBCjxoGihxSRpKlmEzFdIUQ/kpRxmkQ4EfoBiXyBbnYg
*/