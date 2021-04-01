#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
BNIwWmbmVHhDUaiS9rn/I2JhFuW0ddQqbiApGHRkwXzfK7++JVgpcOl6MwxRC6Xp9Ad2FY2nUnGQa52xYG+OCOTfFVXqlRXRjDqu6vG/Ll2GqrV8efelYrmyjmQeOwlpsElMbfbZER53hH+X7gZX3TxAZ/T/ccc96OXJw3jXA3zN1pb4Z6A360nHifp9KjYtaXHsBENDOh+IrOxbyz3eHdOrahtDcgF8slNylNq6JGrrOIODSrfwGxV43T/NYZHh0MO++jTmXCcYi9Z8f7rlfcIQlJEL2GRyp7SEdVw+iSb5VEUgSE7P6DNmzphDxxf4vyknDv2hHFrYQKlmH4O0mn6iMaQu+S5zSufsU81vCG2b93EgEGilcbE71UGmGZbXySQgXw0/hr8HyurHkRVISWoGpGakpyzNzN4W6/du6mMF+Le1XYkIzKPw/RJO2H0aAuGsb4Rf7bioaCwGD6DWLZo6VjqPZeGw+FuCtAtmLclKnIrLDvHsLP/hVVr6kyAOlGahl8tL87mrFePd7YNal4mkRd59ZOIbdfQdtgewOdjF1FqYavIjGGTY4Q==
*/