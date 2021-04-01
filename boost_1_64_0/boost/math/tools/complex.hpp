//  Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Tools for operator on complex as well as scalar types.
//

#ifndef BOOST_MATH_TOOLS_COMPLEX_HPP
#define BOOST_MATH_TOOLS_COMPLEX_HPP

#include <boost/type_traits/is_complex.hpp>

namespace boost {
   namespace math {
      namespace tools {

         //
         // Specialize this trait for user-defined complex types (ie Boost.Multiprecision):
         //
         template <class T>
         struct is_complex_type : public boost::is_complex<T> {};
         //
         // Use this trait to typecast integer literals to something
         // that will interoperate with T:
         //
         template <class T, bool = is_complex_type<T>::value>
         struct integer_scalar_type
         {
            typedef int type;
         };
         template <class T>
         struct integer_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct unsigned_scalar_type
         {
            typedef unsigned type;
         };
         template <class T>
         struct unsigned_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct scalar_type
         {
            typedef T type;
         };
         template <class T>
         struct scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };


} } }

#endif // BOOST_MATH_TOOLS_COMPLEX_HPP

/* complex.hpp
K45ZxzYLC227sO2aTsVlMcvkn1ikwUKzV49VKC/aaHs6M8/ApTYQIpRi77AeE9FW2VEQ+rZVfe/F4W7A04yEC3JIziDD0bbR45Nxzq5E/1z/sqs4LxOvVILfVAlcndbbABNWN6DOuQszgDOdJ8ds313PFByEFz1lLQUNYE/zVtTltOJ2EpcrXpkDvK2idBqg7JFsv0VhoVYCeTjtepmAiVbbTg8c50jr5ciTkaYXjSwt7crjaVeygqftWCW3sZq20II1lI+1CwPN6AmD1daA/PbkNNGZlMXZ6kiHx8Rd9iSiH5jjkQN9K0h33GESgl75nJlrd1oW3Rq8NlvRh+8EtwxpLT07qHFEbZYMmEU8Iyw+WctWXV5dR7pUZ2EFHc3wZam5dkgiGOpiu2Vl8S/Y4dTE5FdabAGxT/8U6tHYvkjGmPc3QYDcWB0aUiJkA9qhcAQq0bFwpNpMIUtQiHlHtmdjDEMna1Ws+OoD2joyw/dK2UbMQIQr7sKYqKlQINSpQIjyjigjk00V1ipwRJW8/9my8buJvNfx5MUxqQ6v94nWqnJozFkGykjOBw==
*/