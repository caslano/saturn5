#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <class S>
        struct pop_back :
          update_c<
            typename S::type,
            size<typename S::type>::type::value - 1,
            BOOST_NO_CHAR
          >
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
+UUbTuZr3/t7UsofEXyiPTjmZYkqJ30ZeEP1HG0QPG7wIFQ0xk5uPsBAyn7t4oHntBzsn8Ec0cjSg7Ys0Nb56lhpy5PJJeJqqbTnkQ0cPVp7rwdj6HL4mnd8GKiNP1jvD0jg6TKyYqx23k5qlujpKihy8cD4UuK/DcJl36VpD10CpOJ7ZoB/cHIMXnB/Td5Nflu2jdLa1si2XUVbb/JC5JGUyxNrnOKVx08DeZp+CG/0aVTvC4hk5XMX7rz/7QsXx1tX+8rAm1XRNMvIyShkOeM4z7VfTM4SbDF487n9fdy+29tzKA1ZP98Ztsj29zeA7+BqMcWH4KEEEUj3Pxt59sWijG+5bwKO4PcTgt8afzZz9mO+E3grBx7W/tY5hiBrNMZZQ+z6ElpF/k+RKea1KUqki2sfsr1wHlRG+KtuA98rt6wz15XlEx+LlmXj7YvzBdd+/swbG49irvmzahprG+rra+Pk5FpsMsaAhfm46ru9AScf175LMQ7Yss5UsKh4q7H3cUa/6akw1Rd73xnYHqdTL4sRS/8Xey/O5OS9lxt7F/PsJuf5dx8xDzZsA+YhsvXYgSudsScw9tdncL9UxN6ybX/ZNlBrmyHbJou2DbRJPSn+i/cUUt445GprLdCbnxrmaakxv+sxO2hDxQhJsz3Od4PmRHB5K0Ui6DHt5ABHfl5exc11xXbzO4ezgraW5praQBuyy4r8nk/7pWfit/rxnGyvaCBhDq9v8NrlzmB+9YEgUQ3Q/EwqghNX9hQ0irzvxeG99IQ9IY6a5wg1j6BrWAVTz9oBF/uXPUHiu0QarzLAO4oxUwf64s5boPKleOXCuQKHRVXrGq7xKp1JtnVmiveQMtgaA2ZA1qr1PAEVhXEjKo14uSjcA1LYFU8bdzp7grVQKJFLiZljYacZijhAa4uDms1g58VLp1kI1ccOrooSAqsc7bjtwVsqKRPvio3fYDnxfS/9fm+8fiJzBJ+m6iJVx5BglEJKhus4djv4g2DbPDjZ1xfN6M6S62h0tsblrwSWUcsHAt8CCe3Hv7Q6qIVjP+d4hm8trRk4mzByj/OdcdzY92ILx46vL7XhwltqfFsYyEM9DOLesZK5VZFN4jk43mWt3+29vAjTI4QIR90N2t6tW3DDvRdy4TuLeMqx5c8wz1Y/FqEUa9pA+1RYzsJb5V/OHM96Ze+l7Y372Q2K2kpXXganq9O+w+3eW3sVvBCpdpZE0O+ReOdyzzjf8M0XnVAqm/amMZ9CiO7H+Maxvtn4rjGGeea3xr9eEbdFNmmt3t+Kgz/29t+gOYqatU56qHppCXq4z5l/5Z9LnWOWeJdZ8DSZ0i0WX6wpoSj5MO7diLaTf8KdfMDzpAxvLtu21dq2lm1LtbYy2XaZ1jY4aCPWp20D47FCnv/CsIG3vbix6Bqvj57EXM1N4QkpRzjWncLJNlzV2l248fid8k97jTPe49IOcB3jp4iHlYzuaeToZnxzQJkxLrAgnp0l6TcsRswraVor247X2hpkW6PW1izb4lrbPNm2r2jrFT9y+azkicuPr702aRFz0VEeBxYoSuWhSEdGtxHfAUdYYPD4WldDyPUCj2QaNcMkeMh88MqbppqZ3MiO6jU63mIXz1u36QSviBS+HAV3FyxOxadHRDiiWqvFYHrfibKzdic7DTwSYPs5C4Mm9MSJF1G0/rlofHFCQk6l9S+EMFXnm1ecR6P7shAHMsYRyGZuvgoa6DZmBTgK5L7r5liXPu3y7V09BY2Ox4Mnajp8aa1IbgxR8XXGekx3krZn+dxKZBMPL65D573amFHnNNdrlEOjuEafJ9UtXDtkVXs+TcIJqthDiKHofoben5cakpU=
*/