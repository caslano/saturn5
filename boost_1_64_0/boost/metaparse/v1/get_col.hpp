#ifndef BOOST_METAPARSE_V1_GET_COL_HPP
#define BOOST_METAPARSE_V1_GET_COL_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_col.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_col_impl;

      template <class T>
      struct get_col : get_col_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_col.hpp
dGzRSBV/D591TtM5K9YR3snL+NqLq93hhEqqo0DhMsIM5lnucvDlMpSq/p3RwaQR66LhoONfF3OjrBIKoLTJvg+0KG6NU5Y5kf6H2NVn+yy/oQSRAKsvWvHqFs0okA6c5US0/UK9ZhaR1R6iTx18w2fw/U4i+znOPrKL51LAlteeao8tR6tNrYTBQqt7RvuiNE6jZabZ5Gat44b2KW+yMU6AYWhQW9t/oL2NMhMO2MWhhQtaZSAEDSe2DaW64/Hc7K2Ijc+g3i9+T2V+Kw8Bgof6Q6Qe4z88n6i6wQCqgz0OyNJTVHS3iq1Pn1s+otYvFXalk0iWeQizIXieYYaW3vDgzp2f1Tw7A0etMFm9aLlJhaEuVE7cHOxQsmCSQSztxA0LxLN2XCMTYlEOUoVZtqcmkUe+U4WMDR5/ihMLuKUQIktMIHygJcl5+GcddZ4y9Nuq4dGRT6FXR5rqUDOixvFKhDSRjC2Z/VRnvIZwzkNycPOmyey6UQLaN7T+hyPmF5cJpcBVsKaNk+mozOLHSgKO1lMavey/hAZ1QWqMs3w9DHSY2eAVL3Q1Fg==
*/