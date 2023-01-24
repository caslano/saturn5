/* Boost interval/io.hpp header file
 *
 * This file is only meant to provide a quick
 * implementation of the output operator. It is
 * provided for test programs that aren't even
 * interested in the precision of the results.
 * A real progam should define its own operators
 * and never include this header.
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_IO_HPP
#define BOOST_NUMERIC_INTERVAL_IO_HPP

#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/utility.hpp>
#include <ostream>

namespace boost {
namespace numeric {

template<class CharType, class CharTraits, class T, class Policies>
std::basic_ostream<CharType, CharTraits> &operator<<
  (std::basic_ostream<CharType, CharTraits> &stream,
   interval<T, Policies> const &value)
{
  if (empty(value))
    return stream << "[]";
  else
    return stream << '[' << lower(value) << ',' << upper(value) << ']';
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_IO_HPP

/* io.hpp
50sknvdp5g7MVE3m4ct02RejM2Fi0dqglM9/MQvqNC4C/ibodaPTdL8cZjmQhmLmdpYYGoR185D5lBLaAiiI4nKbXp6RlV7BoH5ox3JCd+b9qzRx2cNcx2BXLzqFMDR54FhfH8cPHTvJBBLT/kTXlc/qBAaQ3wq4t+6AHjwi3xjOHh6J3oXlf/Y52OWo6XtjjYFVNwDG8danGW7ciH+5CvH4I51UiKg/BGi9fhygNZIRw34sAbauAXw+JaJxTX46ypcwgmvPRPrNWjJ/NszgR0k+7uc6u944KhQBWt4TdOdN+i6T1S/CT+87rmkI7fm9dQlMrKwiGmgIuahECK2QLt+ZRbdRkK8v0kXpDHp36NlEMg7p0J/wVKBcAvwxSe7AK1yA2nfFul7C2gVb0BHIglkS5V1yW7gwLslrjyV3Ka91cNdZd6wXnJ6vZEPbTCC95vlVYYa0GZ4Ep6UXAR7NBIYLq+AVeoK8eDYvOoBA2/sP8v7HMnj6Y5f8Mxx8O4+ZSc8cX+LMvRpZDWtojl4rwLEGEMEtk60FTtoT+Bd1MQvz9BavvIUGndnpZRsxuLzElTsmHQCN8R3yb57gq7TNQ3HuwCdGZNHT/b8jP5eOqVAwXucBn16r8s01zOxaEFpI0uOoN3hERYrXhw7K/eB3kOX01yNKVv4jEv9wX2IkgIGynZj74/vshXDUzmDUT801CuoPqTzvSdMbLGqH
*/