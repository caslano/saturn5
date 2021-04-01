#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
ISizc+ATa92khk/bViSj2fvv4tSXoHECqBhqo14a4+zMmTJnMLJWnGyu25VFrtn6a4MEnGAAiWSMS0CvujqZ1A4MKqpKU12hU04naIzrRTHKltnoJzPe/HcEf74e8NseDFuSBmDPyHcuB6xZ6PEseXRAcMorF2qWV016UJIsbyygmnie0IuDT5Uss9BUMlhR+VSvDZ5JwcmyWPryjZvyGAj9+f3gDBlEJZUIGklTldBXo4eCzsKW/SQUkOPmQsmr+wtd4jA0DWOafpHacQws2N9yAjt+P0ab+AuFjhWJOcaIdtPhTWOy8yYOi90Mm11urtQICxIirDhufRZ87AMr7WC9r0dGml3DqeItn9D8krdjeBIYn3+NAh1j+PArr8ekf/avWdZxrcoGg5I5L5OGndFLb3sQKQx++bRLSPPqg9jWh/zKJAL0o+HHGw0QlxziaRc7fhvNzYhAdk/uW4MPxmKtWbwPVNokXKKxi7Dyk9q8c64rFrYdjVEq329XxCGy63e+VkW0BI1TXd3O+ouP4kmhAKattQ1PnGfS20yxgxTtlt1O//xFuY7pYQ==
*/