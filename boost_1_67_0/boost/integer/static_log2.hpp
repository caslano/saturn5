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
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
*/