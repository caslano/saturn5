// -------------- Boost static_log2.hpp header file  ----------------------- //
//
//                 Copyright (C) 2001 Daryle Walker.
//                 Copyright (C) 2003 Vesa Karvonen.
//                 Copyright (C) 2003 Gennaro Prota.
//
//     Distributed under the Boost Software License, Version 1.0.
//        (See accompanying file LICENSE_1_0.txt or copy at
//              https://www.boost.org/LICENSE_1_0.txt)
//
//         ---------------------------------------------------
//       See https://www.boost.org/libs/integer for documentation.
// ------------------------------------------------------------------------- //


#ifndef BOOST_INTEGER_STATIC_LOG2_HPP
#define BOOST_INTEGER_STATIC_LOG2_HPP

#include <boost/config.hpp>
#include <boost/integer_fwd.hpp>

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