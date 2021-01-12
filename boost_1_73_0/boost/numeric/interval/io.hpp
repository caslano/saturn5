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
Xx8YGK95+x8zSw2cSPaHS6cZuMmo3D/bZSD9MgP/AtmfbDRQz/bvhc8k5Y81Gfg3iz9vNvj+kPB32P7/cuE+7/3L2EoDLSR/WeHnkPEXXWVgDvPvC7+cpEebgTDxD0baDUwgPN4h9UPaN9lpYDJJn03J+CHp410GdtRJfH6PgStI+Yo9vH5ivQbSpP1ywt8g57sya3j6yFoDfst/6uJRm0fPMrCc2RfCv0Lsg/jZ0r80Z36r
*/