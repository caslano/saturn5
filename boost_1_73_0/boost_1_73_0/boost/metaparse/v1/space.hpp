#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
BnJ4tUUt8K5oTRWd/rh5Xt+tHkevb5uEPkYf8fCu5XctH7Q8CkaQ8JsAF9FRldHb37L/AFBLAwQKAAAACAAtZ0pS7iEOux8DAAClCgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyOTVVVAUAAbZIJGDtVm1v2zYQ/k7A/+GgIihQRJHkOOksqAbSNJ27OS+z1X4qUNDSySJMkapIWdWG/fcdZTsB1v2ADAhgyHw5Prw78nmOiUVjM25wxhKhCk1/W+w73eRmxuZp+jB84OF+lbIkeJpKgr01e8VewQqbHTa+ETmypMFa9mSQc8tB6azEbPvO69F4e8AgOotgHIZw/zv7wC3GkLZ4CuEU7vSOJqIQokk8mcZk8uttyvbgMThHfTN0goJvkS04DdzqXBQC8wNKdA6/tcrBE8o4jsIjyk3KNzF44ygcX/h59tY/n04ux5PpLx67yjKsrb/kaoMmhnVPO7FrrSwq6y9QbWwZw6UbUZhZoVUMmdQGH23Svkbn3w8blLaS7GOrVO+XyMkript+jPmF1j5lzWXFZe+QpSF911I4mH36sqFDJgVy2zZIuc5x3W5ozdNIss/DjJXW1jRz7CaKVzh7OjLohC3B1FJYEEpYwSU0+L2lVIJBldPS/QoC
*/