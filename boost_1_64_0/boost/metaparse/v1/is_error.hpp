#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
b/1CJUxZJgtx6bvSMfpBzKQps5lY1ZDtVFhUWJcXR4CylnkhJ40KnEHP+9dNmlS+mKBrCtqOppu0M/J9A+s/Fjq4HrDbU0P3nhLCKFo3ZkDXa46bs5+PxWagn9AG5YN7TaIQukptzirNXfdk4aZ3uxJ9UjCWLrgKIi9BJE7QlCNi06EJ64pjVxO0OM+l76e/SaWMoc4EKA8M+8qb4rpWrGRF/p/CHU5H2XCy8G4S1F9RtNoKq4VviC1lDYP4D8APALnxwF6ix1I+UMZ0zr6cJ002eaKFoSV1yLEppXJ97BVVnJcBzrdNcjtyCr965UyhzZPn41OvWPE8cn0SJNtCqOPqlm8ghYAO2bAht65OKXWAfwpBzhaRDynqIFVFwfpQVru/y7m4neID45qbnbKRFCamNAhmQWfhwt988Fdjb+K65V3wMUmhMXokbs2e4G+mBcdY2kJfAkdrLMjVV/ulkeGZaG2q9sVux8tERevbpAAtpRY4cGK8xpNA6Ay5w2X0NKf6qE8tSOJFEmpYUX/G+fgHhBUeGl+lFsB4CdtIVIKL0Eyy5Vr6TOAf9w==
*/