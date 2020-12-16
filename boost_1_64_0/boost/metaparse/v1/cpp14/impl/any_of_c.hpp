#ifndef BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          static constexpr bool run(char c_)
          {
            const bool values[] = {(c_ == Cs)...};
            for (const bool* i = values; i != values + sizeof...(Cs); ++i)
            {
              if (*i)
              {
                return true;
              }
            }
            return false;
          }

          template <class Chr>
          struct apply : boost::mpl::bool_<any_of_c::run(Chr::type::value)> {};
        };

        template <>
        struct any_of_c<>
        {
          typedef any_of_c type;

          template <class>
          struct apply : boost::mpl::false_ {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
K/XzAt9Hcd5SEk6+U6fqanM4fUbDFsejkxrKxWx1rzaOw646vP75M3KVjkZP4Hs/mSd/pJsPuBf8eWemM6JEiN/vC28LqRe9ULUVXx/0A4Xop6/wAuxZ3ICG+dbr+uG3qz6eFbvdNOw/apI+LieOPw6Tm2ywao852TO4ZAb7OV2z42s1oS/i8YMJ06ujSWbbZhnl08jBP3xyJC/Ls+2Li+ca4vJb3i+vf8nJUlx7HYYG8NXVcfjRGVyHW84gwjznLM/vonm+51ceeHQIwHYdGFr1JcxV85fN8It2tTZ8t7MxLWI94/rzat+4dhhMbKWe38DE1Hr1kbPAT/UYrr+I13Ltpv3oy8MwOyGdmnwvrwwjxqfCD7DzvX5tUxFvVlBX0ZyVq/dPJ9HjNOPIgrDkFOzP4iPuXWveN4MXbd8fFttfe73w/UX7SC0u9+0F993BEVmj4bfVeNWaFk/RdwnkqIfn/GqorW68cHteyNe2JaJVdtH59rMqHO+mc9ZMJ80Tg1HtcUMs9amW1wR/Lq8s3oSDr9TDQnWZwjMg89RUDlp1GL3VZSFdZJ914MFR+S4e/HnRJTDL15vm8LUzeEAOQvnQUbAgSia9QitNr+bsnobZR+sU/BwXd+PlRtLEt9QGHo7G33bU51HHq4My3r+RVuP3SqvZpp49rToGD9FThad67ru896mJ6XRZr+Uwb7hYwrJF4vlS/VV1jX/o1xqd8VM1/qGt+Uds5+h0XSn1ei8zfFH/t2jqKMWdEzTRy1Fgi54J9d4S6834butBmjXWDZ6OZvRf4Pop8/VpfJz7tZih97vhsf/gXfOTBTT7jvQwFS7lzIDL6d6j8DJNNOueJd9FnFvjxrz2Hv4nvKGZmuOuirgl63YzIP0/w/yttplKJvF6+B382KxmbvKBx7w+TH/zCftprt3N+Y3gLCgTnXYFvvaF43h5Hg9bMwx3ykn3n62NZ6mgjkrPVvewJVQvd/sev/HgUVdYn7PxtTHh0mPxd81Eo2BnV/zhjGnwZNcQg+q4JLSMWj6ups2bG/D/2Wjcx/g/DR/ZESYVhb1TmsOZ4jTOKPPxI+pYzjrRbhG0ypr5uGcJTIyBu/R8djW/jpZYDqfe0g7NEuHhCnLzN3yCf23MR9+8hZH0Q1dz+lh0Q1y5m6PuXqn5qeddB64WwrnH9dpDz64VaqSmZsO96vwqfh+dE37E1+e9zQL5vYi+sN7cpbo6fcrf3aQ1Tx90XizGxxfzHvDo6Cl82hef91JvO/TSQPWUhRa9Seuol/Fq78YdOcorL7dgZGN6pROt4znvlLA+Q311flNttrMn/TpqpK/3ofcGWUditVAVRi7UA67TtjB9JHY1XaNsZbr6qN55gIenuCZPfxKGbuDTiuLzZY3M7HfwEs6YeuHUA03cfxr9UlufVuYpy8JxWPQU104aHjC/1qPVzRZ45kwZrecb/rUVbv3gGTi9foe2+fqQfjnDg7pv+840qHOSxw+dW+uD0IJwP68aF78MUUJoAjiNW3sl1lvVXRN/roAdX2UMhfHu5XVZn8Dt1jRjKpjt3Cw9TMgmx7/qg7rwZg2OjukMrzSPGOeoc1e1WJw2/pR2jVPBXK+RvDdUk//awzqckN5zDPCyN+02NkNQE9I+1p52s3Xt8v6cejMOzYhPI9XP3ItyU56memymGPSA4nOkrL6AGdu7O0u6S990F98jsPt7M9lh+svaN+ZQc/xijEG81zRcwwc8WCk3qemMB/R7G7qhoHyNV4f4tK44hlU0Uwvl8UfwsmvhHywYTLdE0J9JOzgjLQ4z9MpHe8sK+2OcUkN4cBmM3WousaCyuV9O97LWc2PU01m5gn8Tspo5vHQ=
*/