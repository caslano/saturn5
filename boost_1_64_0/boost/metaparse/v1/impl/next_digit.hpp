#ifndef BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP
#define BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct next_digit
        {
          typedef next_digit type;

          template <class PartialResult, class NextDigit>
          struct apply :
            boost::mpl::int_<
              PartialResult::type::value * 10 + NextDigit::type::value
            >
          {};
        };
      }
    }
  }
}

#endif


/* next_digit.hpp
5EUM8iE/CqAgCqEwiuD7TPTKazEURwmURCxKoTTKoCzKoTwqoCIqoTKqoCqqIQ7XIB7VUQM1UQu1UQd1UQ/10QAN0QiNcS2aoCmaoTlaIAEt0Qqt0QZt0Q7t0QEdkYhOSEJndEFXJKMbuqMHeqIXeqMPUtAX1yEV/dAfAzAQgzAYQzAUwzAc12ME0jASozAaYzAW4zAeEzARkzAZUzAVN+BG3ISbcQumYTpuxW24HTNwB+7EXZiJu3EPZmE25uBe3Ie5mIf5uB8L8AAexENYiEVYjIexBI/gUSzFMjyG5XgcT2AFVmIVVuNJPIWnsQZr8TuswzNYj9/jWWzAc3geL2AjNuFFvISX8QpexWvYjNexBW/gTbyFt/EOtuJdvIdteB8fYDs+xA7sxEf4GJ/gU3yGz7ELX2A39mAv9mE/DgTT6YUX0xsdQ3bkQE7kQu5wWDEvYpAP+VEABa+4hXQMRVAUV6MYiqMESiI25E5yy+kYQiEaOoZTbnwa3+BbfIfv8QPO4Ef8hLM4h59xHr/gAi7iEi4j6GRFIBJRiEYmZMZVyIKsyIbsyIGcyIXcyIO8iEE+TFPmdNyK23A7ZuAO3Im7MBN34x7MwmzMwb24D3MxD/Nxf3gt+QAexENYiEVYjIexBI/gUSzFMjyG5XgcT2AFVmIVVuNJPIWnsQZr8TuswzNYj9/jWWzAc3geL2AjNuFFvISX8QpexWvYjNexBW/gTbyFt/EOtuJdvIdteB8fYDs+xA7sxEf4GJ/gU3yGz7ELX2A39mAv9mE/DuAgDuFLfIXDOIKjOIbj+ANO4GucRIVAKFZcCZVRBVVRDXG4BvGojhqoiVqojTqoi3qojwZoiEZojGvRBE3RDM3RAgloiVZojTZoi3Zojw7oiER0QhI6owu6Ihnd0B090BO90Bt9kIK+uA6p6If+GICBGITBGIKhGIbhuB4jkIaRGIXRGIOxGIfxmICJ4fj6ZEzBVNyAG3ETbsYtmIbpuBW34XbMwB24E3eF10B34x7MCq+p5uBe3Ie5mIf5uB8L8AAexENYiEVYjIexBI/gUSzFMjyG5XgcT2AFVmIVVuNJPIWnsQZr8TusCz8zWI/f41lswHN4Hi9gIzbhRbyEl/EKXsVr4XXg69iCN/Am3sLbeCe8fnwX72Eb3scH2I4PsQM78RE+DsfdPsVn+By78AV2Yw/2Yh/24wAO4hC+xFc4jCM4imM4jj/gBL7GSZzCaXyDb/EdvscPOIMf8RPO4hx+xnn8ggu4iEu4jECE/xCJKEQjEzLjKmRBVmRDduRATuRCbuRBXsQgH/KjAAqiEAqjCIriahRDcZRAScSiFEqjDMqiHMqjAiqiEiqjCqqiGuJwDeJRHTVQE7VQG3VQF/VQHw3QEI3QGNeiCZqiGZqjBRLQEq3QGm3QFu3QHh3QEYnohCR0Rhd0DT+v6obu6IGe6IXe6IMU9MV1SEU/9McADMQgDMYQDMUwDMf1GBGOiYzEKIzGGIzFOIzHBEzEJEzGFEzFDbgRN+Fm3IJpmI5bcRtuxwzcgTtxF2bibtyDWZiNObgX92Eu5mE+7scCPIAH8RAWYhEW42EswSN4FEuxDI9hOR7HE1iBlViF1XgST+FprMFa/A7r8AzW4/d4FhvwHJ7HC9iITXgRL+FlvIJX8Ro243VswRvh51tv4W28g614F+9hG97HB9iOD7EDO/ERPsYn+BSf4XPswhfYjT3Yi33YjwM4iEP4El/hMI7gKI7hOP6AE/gaJ3EKp/ENvsV3+B4/4Ax+xE84i3P4GefxCy7gIi7hMgKR9B+RiEI0MiEzrkIWZEU2ZEcO5EQu5EYe5EUM8iE/CqAgCqEwiqAorkY=
*/