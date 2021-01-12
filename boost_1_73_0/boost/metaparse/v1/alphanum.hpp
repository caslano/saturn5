#ifndef BOOST_METAPARSE_V1_ALPHANUM_HPP
#define BOOST_METAPARSE_V1_ALPHANUM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef one_of<letter, digit> alphanum;
    }
  }
}

#endif


/* alphanum.hpp
ucT+YNzKRC6xbdWO5cL3PvFWlGsQjhflEucu3/8tyiX2p7FcWLfLY7lwvhfEcuF8W0W5xDZ4YCzXIJzem1GuXrj+Rbl6if3ViigXlu/ZWC6c7/WxXDiP7rFcOI8f3whzDl+C3F+jnNkGn29RzmyD7e31RM4sgu0tylnkwTHIa2GuaWJ6q19N5DRf8Hke5VQj2Le/HOaaJHI1opxqBOvfS2HOah/uY6NcYh5nRLnE9CpEuYaJ
*/