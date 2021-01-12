#ifndef BOOST_METAPARSE_V1_GET_RESULT_HPP
#define BOOST_METAPARSE_V1_GET_RESULT_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_result_impl;

      template <class T>
      struct get_result :
        get_result_impl<typename T::type::tag>::template apply<typename T::type>
      {};
    }
  }
}

#endif


/* get_result.hpp
RcO79rjuB/umPbTZxqDNOibtP3qVjvp7PiLPoM3mJ7VZsAPJ23/sRb8BKQsKtlPppOGiC/732y2+bvkNNu+1n0Ifyu3ic+1UdUHUTmnpFw3r9zuOz/bUB8m9ZX/5+Kxc0rYK46hTUMehffL3fWkm1F55l8qdFbRzRe2+WXnTKuXWKyvvXCOYT2K/dkMw7ryywTOVg+H6wTOe9nkoHC7Y/4T7YL3oj5U4m8UcS9UzvrbRh0Xu
*/