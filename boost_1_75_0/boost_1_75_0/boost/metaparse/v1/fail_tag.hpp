#ifndef BOOST_METAPARSE_V1_FAIL_TAG_HPP
#define BOOST_METAPARSE_V1_FAIL_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/metaparse/v1/fwd/get_message.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>

#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct fail_tag { typedef fail_tag type; };

      template <>
      struct get_message_impl<fail_tag>
      {
        template <class A>
        struct apply { typedef typename A::message type; };
      };

      template <>
      struct get_position_impl<fail_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };
    }
  }
}

#endif



/* fail_tag.hpp
4kOO5xWRJN6w7dQ/oFyaY+m3bDvlJOPTHfWh5kBBID03ViB57J3eXKRJCi8MgDSjYlRTKse4vpyrj0s36pCCTrBx6iH4N3HvOJtJOuHD+KZs6VvFcbgaBr08Mg5oc6O/n+LIrAYxnqHk6KQBIxL8iVAGj5EVBpifIg4fNggKJX7A7meqdsjNPmgIGzc4DjD/WRiMccJphNru0N0J+MlMzhiZBg6X9vI5E0E3wV/+jtjdaDd0N8pAaxM7zf6+byKqFhux7oa0nW0lxTFoF5ipd/ikCjRIb1d24Q6bDmwYNz1Utry5nLg6sE/aLygy8To1XF5q/Tm8yQq7Ng9oGtQZ4RI+1Z1pImsdV5/dXq09SzKX9rBeTD2dvBaCMeYqcw6xbdAxeiJgGWE/gymmpoNm6cvEBH9i5K+BV4NhYkCvLu7NJ6ykYplBxfJsUOi/bp5Bm5l4Bwlx4SyzlwLFPUnuXu1JUvvc/fmPHraPmWY2qHLG9YyZYUiSN5y63WSiwvMpHmmbXDLzhAIEHeOWwpfUesK+BOQ1Hqm9J+QTlkTG6RKgWn6aV5rBPuZ8z6BTgeEeSYn0d4fj2nikSs+gMrd9eCW+xDPoU/u8Q7C7S4FzhnQBbkzUqmD/lyd4Bn0d+DYy0ScdcA/a5+/B7vOE2qXqbvQEP8Eb2eXAN/BWqImQxt7r7+6RvnL32ofRXd5uCVGDw8y+hyLXKRA0x+SW
*/