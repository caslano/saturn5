#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct later_result :
          boost::mpl::if_<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* later_result.hpp
y3TKzkENAjud6Fa2sR0cUZfOdyYm6b6lQ7ZXpRZzHBzYzCVSX0ZiM7eS9jEj27bX2o6UbR0x2nqtV6I846PjmV6buZS5RJzYmqdG0NYZ1+X5DX7L/Tc21DcV3TaOHQ4rOh4VyKSBJgInXS6/O8QdZ2JMyxfcMRz7erwHR+jnutYhFFu3mye4OF67ecVAd70ccfaktXzzFHcs3Wegi764FYXU9n3GEP28i5puoiu4AKrF+2cNCWNDbuI2ci9TniwRgS/R13wUdiWQAQIgIjk95xpXcixOPRlHl9uzwQkCwTajRnf6EKMGmFiCEISwgiVD5BtRXHcBMCuxZLekJSKh0/Y5GnttlBfjyLggCrXu4jqc9QG31ngRsKh3d8o4N7x4iJl/yQA12sMlJtzwy5f699AGI1LkQdH57eXgsXfB5cif/II2XCaXD9uNWvovaa+q4SZl8Y6+8KogWGedVwcyptCkVoTwa224VVv5rfL/4ZMNICjdvdGFiwkMXbjewYlUJuLx+ZI+5OnZbCZXSLYr6dNl67YQrx2jqMW5t+u0h9956y7JHcCL9+lFCQRNqmCrYR6ye5jDgNPQWL+AR36qG5uLCaxiV4Dr5pTTa8yMUq0VfZJ8g81dsC5c69mmnIR2oZf1s2wu7dTPbvHWVe/1y55IiyK9/qPln4V5De+qRnmihdNFIblAXhOdHQyJ4lNmYgjN1j0ArCe9JJ1ZlhZbdvz/Q2ZfZEhsUPW/x4AH3XVaPwGcmjyaX8jrfH9miK8uhQhr9PmbF0eIscqvnwMnVZ7QhTjSzxfk3MKq6nHYS5JeMi/jNEqdX70s+4jGYrrLdnrpo7sT2bwn9n3QKwP/Lu4RFa+tqTwkPofnOuCgRYe3fDgWHd4p0qGg0yHS4Xe9/d0a6T/Bc5FUPWCNdxxMhqWDa/14eGwVW30g/QqF3nIcRqSDB0Al3SCJkcOc5EMZOy0ReV2v69rZJT2OXj5p8GRnKyYOKys8H1PVXCOvpMh4r9/QYC2Die369z6O41KVT0ae9crIZkNDvhhGEt4omm/qxxHki2xJ2qjLqjy19/F8ti2V8MWhL6j1954/bSmHPy9584O5ms6rPEzp96ihUSyUSxYvjSm5GwMM/RaAdr3P9rK9gPOSt0ojWKa/ukMXT5jnxEcqmqoqj7bWHYcaNM8TGeEBlc4NB85NI6r2eUEBJzbeOeof9g14GvrGzYeuyzciIjLvSIJ3zlTuqNFnQJiLyLZ5WluetqN3QIe1th6JVyvaei3r6RKy/p5X1lcM1WqFQR1RumHlU74LDieRxeqdzsNjVDv3E6h0dinZP36oUSttapnOQ5tBWK9yCC+OcxaPvyV/zKcnAaHAyJMccDyE/ZAximaCfQcHEYrXpwMzD1gEotLhHwBvz5CgB9fa4hCO3Ja7l7jOKEYGhwxeHVZrtckzg/23p7W2c8K2PDpgtolqNbLs4PbkUjG7LaXnNifTJqa2rZHu398hxrII6eRiJ/nGEUjaXCv9PBHOJPJvP/biKAcX0n8peB4kdZdnKDjUDXQeERT17lwdA9Dq2LHNynx+5vJg3Vr4JJ9kZVF6jvKLUnhQQb/LcdVQO84jXdPOQC414cimirF/XWIO5d7Ven5TAldqyvrXTRFBP5+7ZKiZYxKHRry9YagnBqT83ZUsGPWxm4bq5zMhgpKjm73jCAKq9d7iw1FiFI11mxePjELb0x/M9QBU/e8M+IC82Bmr6n+3yStUXtmRQ8vsvME8c7ra7EsxUOnzpuTiTCjy2F7KNWbIketRSq577RfE1VpfDDGmzOfznyjavaWGbuo2+Smd3jy40JZdESsJSxQi//nHoaXOXBXfdw7zkVI=
*/