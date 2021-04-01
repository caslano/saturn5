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
WvfwPTnA6Dy46t2er3PX6NraryaKxyw/NvS1aAf0xsnx2GIKVtsKQIjcAhp64epdZgSo6gPWXySHn7OrnHKfJ1NHzW/IcLj6ItsiSjNcjAnUenOh3pPt22lqp5QOBR/xK8L6JKvO68rQw5uPITmYYF6FEQaD1qQ8irCvgN/L5wBHDwOUj0gr/GMFKhDkEiPuH7znY8ZvVuEJM0R0FvB+ZhJF6XKiRaMjFI8F89TNRyA5ubIT84N9eqpgqXJxVjJEcQf6XYVyROxvXjref5P/85IKcA2Z1neH4JC/vleaCLtehwjRRh1iTj5Hn41OjOfqFvJd2gHTH0lJLMkuVJ8It4mzHvfKDxIDDJgrmc3KB6EZORhTlfCqTctMqFWFsqrvEclW6KDC+JDEFUIqz2kZpDfbwq+KBSl3XwXGC6tkFtpsQ9G9R8dKIBz+lr8f/dP0uQQ/USJ9xkGULamI/eQu7duAr/iPCqSH1LXhB7Mai97ZKLMlqmQ/mKV2drWCQIF2xqnZe5lqkJitvs7NgmENy9Bh/Rc5HTUBB1q7TEdss3hiqCIFJWW/not5ew==
*/