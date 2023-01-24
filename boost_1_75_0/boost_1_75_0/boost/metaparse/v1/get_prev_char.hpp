#ifndef BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP
#define BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_prev_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_prev_char_impl;

      template <class T>
      struct get_prev_char : get_prev_char_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_prev_char.hpp
+LcfshHGaiKtLDZ8c3rzBYPg/F115xchLwD5GYvhmIA3G2+DagJttrwYUZJX7MPBWOcI2j+Txf45GzcOvFxV1O9F1nroTBXZ7HAJBbnpnz0lA1hHzuUhBaxPX86R4yKAgHMNwQ9GWIDA5EuBj2PstptF09QFCqWm8h1gcXsCT9UTGH+zQ3dePpcg2RchGQMvUFtho5DVXKAPApj980603rfw4wZ+XMePqzuF49ZnQP3TMrltpvrUQ7BYACaQaP3VAjvQdA7QtOfIyIRUR1EALQoCEJqz3ceGsq4GEHfYiKZPwT7nsr1w9lB2CbbCwJy0puvhPXnusHcMPv07Uk3vkOPpquqEu3sleaLYCE07YmylGWJs1nKeWBYVGjsHW2styYwjVkmuUYlnvqGivjgQL8y2K1YJVobhx89BOdlVMRw3WCxHw3hK5epIRSQbwDnqY5yNOxRdFWXcdZSk/dDbxhkBFrxiFDME+dwez8CvHOUxaY7yyDjXwGoBMFLp/7V4ABYs6dObvzv4E6+MQJXOeR77mMl8WzTbYub1z7aLTaWSE9L1h0kqrVXM3nmQSi34pPMOxKHzI+rC1+XgQI4BJxTLED02Sw4RR0cvrNG9apWhIhycjRlx7sE/ewMruedoJTYhrWQlBbgwKaQBpRBy88Hv3+30e23I9UpaymBM47LKSrzmDV7+OUQ2BlZzg/W45MI5cc87it9Bc/OX
*/