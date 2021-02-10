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
HMFvpO9A/l+j+flsMYrg7eRAJg4RkINetnfvFCiFeQx+QzJtNtuV+b0n6IjNPsMvpx4Q+gYHyEr0z2XYSrggbN/2kT05Sl8pFkKGH1CRYkpr/yelfYeHv9aAuODIhjdFO3qRwtjFGMlZhE+T8dQ/BcgaEira46LeNUabwCv00qHZ9uVosWSj+Zx9if+czdl5PKxn1xo/gtRXLFGCF1VJ4SeypVlY+wu/P4EjlZIsCKinQ9qM7rb10cN9/Im39FlSE9156aea9tpOhvudj3qp4f8FUEsDBAoAAAAIAC1nSlLznGv7BQMAAE8HAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTU3LmNVVAUAAbZIJGCtVG1v2jAQ/s6vOHXSBCglhU/ry6YxunVoFKpC1VWqZJn4IJ4cO7Kdvmjdf985CYV2rZCmGhE7z909z/l8cdx+u9GANmwdrPwzGjSXEWfW/MLEv+zN2ANUP4q6pnmbSAzrkAfWgu0hD9AsQ1itchTWjG0Tug65hUccIq9ZWBJCYSFyYPJ7K5eph+agBd39/Q+wC7293l4Ex1xLVDD1qOdolxEciRL5nPK7u47DTxGgB646NdUslQ6cWfhbbhForWSC2qEA7kCgS6yc04vU4FOE
*/