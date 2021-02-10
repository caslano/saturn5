#ifndef BOOST_METAPARSE_V1_RANGE_HPP
#define BOOST_METAPARSE_V1_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class From, class To>
      struct range :
        accept_when<
          one_char,
          util::in_range_c<char, From::type::value, To::type::value>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range.hpp
AAgALWdKUjFLld38AgAAogcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjg1VVQFAAG2SCRg3VXbattAEH1f8D9MFUKhRJbkS+q4siG0gZhebGq3eV6vRtYSWSt2V3Hcr+/sKonbhpZeKIWCWd1m5sycMzNOLRoruMEpS2WVK7pc436ndGam7HK1WvgDFh9W7c0ruSEH4I0tWBodTNOo9WZHsER9gzo0MkOWaqzLPX3OuOVtwCjpJjCIEx8DKysFt1JVUJdIaYDZmbVqKoEd1gYaw1sptDIqt+FstoxOu3GHXV1dhecHfxzfJ6aRl9tJ4Kryt8EJVIqiTYIkHvZP40EyGAQd9lJVlnzD1b4mX4u3NirstnwBouDaoJ1Io8LRaHgWJgfjN1htbDEGwu9QwW1JvrIkjuMvquvFMZzD/PUPS/ijFPouBXV9l0UL36YiChTX/xXT/4zWOyrp6a6LqblfltI5tM0t/MOUHbHU+IymrLC2Jof7xzRHbhuNNCFPlsvFjAm9r60ii8OHtOJbnD7MGYRh1jK8k7aAxrhZqlHIXGIGX2cMBfIMNYVrYxzBqpAGnCbgrgqwMoQCTx8x+9QZGHoFu0KWCBVulJXUINWmne4jwBus6CsdJD8FIQf+U/l0
*/