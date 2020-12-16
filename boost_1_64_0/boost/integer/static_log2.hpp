// -------------- Boost static_log2.hpp header file  ----------------------- //
//
//                 Copyright (C) 2001 Daryle Walker.
//                 Copyright (C) 2003 Vesa Karvonen.
//                 Copyright (C) 2003 Gennaro Prota.
//
//     Distributed under the Boost Software License, Version 1.0.
//        (See accompanying file LICENSE_1_0.txt or copy at
//              http://www.boost.org/LICENSE_1_0.txt)
//
//         ---------------------------------------------------
//       See http://www.boost.org/libs/integer for documentation.
// ------------------------------------------------------------------------- //


#ifndef BOOST_INTEGER_STATIC_LOG2_HPP
#define BOOST_INTEGER_STATIC_LOG2_HPP

#include "boost/integer_fwd.hpp" // for boost::intmax_t

namespace boost {

 namespace detail {

     namespace static_log2_impl {

     // choose_initial_n<>
     //
     // Recursively doubles its integer argument, until it
     // becomes >= of the "width" (C99, 6.2.6.2p4) of
     // static_log2_argument_type.
     //
     // Used to get the maximum power of two less then the width.
     //
     // Example: if on your platform argument_type has 48 value
     //          bits it yields n=32.
     //
     // It's easy to prove that, starting from such a value
     // of n, the core algorithm works correctly for any width
     // of static_log2_argument_type and that recursion always
     // terminates with x = 1 and n = 0 (see the algorithm's
     // invariant).

     typedef boost::static_log2_argument_type argument_type;
     typedef boost::static_log2_result_type result_type;

     template <result_type n>
     struct choose_initial_n {

         BOOST_STATIC_CONSTANT(bool, c = (argument_type(1) << n << n) != 0);
         BOOST_STATIC_CONSTANT(
             result_type,
             value = !c*n + choose_initial_n<2*c*n>::value
         );

     };

     template <>
     struct choose_initial_n<0> {
         BOOST_STATIC_CONSTANT(result_type, value = 0);
     };



     // start computing from n_zero - must be a power of two
     const result_type n_zero = 16;
     const result_type initial_n = choose_initial_n<n_zero>::value;

     // static_log2_impl<>
     //
     // * Invariant:
     //                 2n
     //  1 <= x && x < 2    at the start of each recursion
     //                     (see also choose_initial_n<>)
     //
     // * Type requirements:
     //
     //   argument_type maybe any unsigned type with at least n_zero + 1
     //   value bits. (Note: If larger types will be standardized -e.g.
     //   unsigned long long- then the argument_type typedef can be
     //   changed without affecting the rest of the code.)
     //

     template <argument_type x, result_type n = initial_n>
     struct static_log2_impl {

         BOOST_STATIC_CONSTANT(bool, c = (x >> n) > 0); // x >= 2**n ?
         BOOST_STATIC_CONSTANT(
             result_type,
             value = c*n + (static_log2_impl< (x>>c*n), n/2 >::value)
         );

     };

     template <>
     struct static_log2_impl<1, 0> {
        BOOST_STATIC_CONSTANT(result_type, value = 0);
     };

     }
 } // detail



 // --------------------------------------
 // static_log2<x>
 // ----------------------------------------

 template <static_log2_argument_type x>
 struct static_log2 {

     BOOST_STATIC_CONSTANT(
         static_log2_result_type,
         value = detail::static_log2_impl::static_log2_impl<x>::value
     );

 };


 template <>
 struct static_log2<0> { };

}



#endif // include guard

/* static_log2.hpp
qwaqoWqkGqsmqqlqppqrFqqlaqVaqzaqrWqn2qsOqqPqpDqrLqqr6qa6qx6qp+qleqs+qq/qp/qrAWqgGqQGqyFqqBqmhqsRaqQapUarMWqsGqfGqwlqopqkJqspaqqapqarGWqmmqVmqzlqrpqn5qu/1AK1UC1Si9UStVQtU8vVCrVSrVKr1Rq1Vq1Tf6v1aoPaqDapzWqL2qq2qe1qh9qpdqndao/aq/ap/eqA+kcdVIfUYXVEHVXH1HF1Qp1Up9RpdUadVefUeXVBXVSX1GV1RV1V19R1dUPdVLfUbXVH3VX31H31QD1Uj9Rj9UQ9Vc/Uc/VCvVSv1Gv1Rr1V79S/6r36oD6qT+qz+qK+qm/qu/qhfjLtsx3hSEc5jqMd47iO5/hO4IROxIniRHWiOdGdGM4vzn+cmE4s51fnN4dfaTn/deI6vzvxnPjOH04CJ6GTyEnsJHGSOn86yZzkTgonpZPKSe2kcdI66Zz0TgYno5PJyexkcbI62ZzsTg4np5PLye3kcfI6+Zz8TgGnoFPIKewUcYo6xZziTgmnpFPKKe2Ucco65ZzyTgWnolPJqexUcao61ZzqTg2nplPLqe3Uceo69Zz6TgOnodPIaew0cZo6zZzmTgunpdPKae20cdo67Zz2Tgeno9PJ6ex0cbo63ZzuTg+np9PL6e30cfo6/Zz+zgBnoDPIGewMcYY6w5zhzghnpDPKGe2MccY645zxzgRnojPJmexMcaY605zpzgxnpjPLme3MceY685z5zl/OAmehs8hZ7CxxljrLnOXOCmels8pZ7axx1jrrnL+d9c4GZ6OzydnsbHG2Otuc7c4OZ6ezy9nt7HH2Ovuc/c4B5x/noHPIOewccY46x5zjzgnnpHPKOe2ccc4655zzzgXnonPJuexcca4615zrzg3npnPLue3cce4695z7zgPnofPIeew8cZ46z5znzgvnpfPKee28cd4675x/nffOB+ej88n57HxxvjrfnO/OD+cnk35bCy210o7W2mhXe9rXgQ51REfRUXU0HV3H0L/o/+iYOpb+Vf+mY+s4+r86rv5dx9Px9R86gU6oE+nEOolOqv/UyXRynUKn1Kl0ap1Gp9XpdHqdQWfUmXRmnUVn1dl0dp1D59S5dG6dR+fV+XR+XUAX1IV0YV1EF9XFdHFdQpfUpXRpXUaX1eV0eV1BV9SVdGVdRVfV1XR1XUPX1LV0bV1H19X1dH3dQDfUjXRj3UQ31c10c91Ct9StdGvdRrfV7XR73UF31J10Z91Fd9XddHfdQ/fUvXRv3Uf31f10fz1AD9SD9GA9RA/Vw/RwPUKP1KP0aD1Gj9Xj9Hg9QU/Uk/RkPUVP1dP0dD1Dz9Sz9Gw9R8/V8/R8/ZdeoBfqRXqxXqKX6mV6uV6hV+pVerVeo9fqdfpvvV5v0Bv1Jr1Zb9Fb9Ta9Xe/QO/UuvVvv0Xv1Pr1fH9D/6IP6kD6sj+ij+pg+rk/ok/qUPq3P6LP6nD6vL+iL+pK+rK/oq/qavq5v6Jv6lr6t7+i7+p6+rx/oh/qRfqyf6Kf6mX6uX+iX+pV+rd/ot/qd/le/1x/0R/1Jf9Zf9Ff9TX/XP/RPbvlsI4w0yjhGG2Nc4xnfBCY0ERPFRDXRTHQTw/xi/mNimljmV/ObiW3imP+auOZ3E8/EN3+YBCahSWQSmyQmqfnTJDPJTQqT0qQyqU0ak9akM+lNBpPRZDKZTRaT1WQz2U0Ok9PkMrlNHpPX5DP5TQFT0BQyhU0RU9QUM8VNCVPSlDKlTRlT1pQz5U0FU9FUMpVNFVPVVDPVTQ1T09QytU0dU9fUM/VNA9PQNDKNTRPT1DQzzU0L09K0Mq1NG9PWtDM=
*/