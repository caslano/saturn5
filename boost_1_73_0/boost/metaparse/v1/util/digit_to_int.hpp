#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/digit_to_int_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class D = boost::mpl::na>
        struct digit_to_int : digit_to_int_c<D::type::value> {};

        template <>
        struct digit_to_int<boost::mpl::na>
        {
          typedef digit_to_int type;
          
          template <class D = boost::mpl::na>
          struct apply : digit_to_int<D> {};
        };
      }
    }
  }
}

#endif


/* digit_to_int.hpp
yfw/RS88jN74GdbHI9gEP8fX8AvsgF9iGvoTzDL/tjL/7AT1fdZHpHPBx+iBv2FR/B0rYiY3zicgCzZFF1TPj/bIfI85OD8yMX0RDMVSGI41cSA2xAhsh5HYFaOxFw7G9swjFvujBQfgEByJQ/FNHIZzcDguwJGYgqNwC47GazgGb+JYzEI538LsOB5L4gQsiwnYECdiY5yM3TERA3AqmnEaxuAMtOAsHIJzMB7n4nCcjyNx
*/