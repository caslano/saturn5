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
Y1e9KZZI7DJpJrXmAyWzYSy5JOIYGIClKf+SWYgfKjJm5hP+JcvsEDlKEOttDMt5Fl2+rOer29SX2GK7qUkGx3kRIu8PH+xZHSTSalnwAGtgtHBLFU1+Ymviii+EPX4NSc5Thd15SGQRL9YaTdSmiRa0GXPpTXm/QZTGUY734JKRRchd0LCIlQlktt1Bv403I78eITX4o1LiGHNuxJgJ29RrrJGnjctQQsIFvC0Hyj2OSMA9X80EOQITEXmT2CujzzvXYXsxHDNxQ9Bho/b9gAepY1sS78O4tiimV/S8tS0Q0CydURjujZYoBUmYogJVFxIMRfsI+WVy3p12gVV3kZY9e7y7EOf85jUs9Fd1QU+6GOEsylxpOmeMp+JHlMEs7tUqv1BLr66JaegmlU59c5LZRa/W1OtV0QmjteUg9Dfb3AOyvb3TPgHhwsh/BHaLerRLyfYHbyKNli3WCunQSTmpQe2eMot6UhYBP3NL/MwNCfE7nHS4ePdLzY6eeBtxmiyeKQ3o3KaawcLeNFvLhsI3QZG0FuXd0Gb4EtRaoJ3qza565ZKyDEiunA==
*/