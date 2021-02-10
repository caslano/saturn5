/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct is_total
    { 
        typedef is_total<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_total.hpp
1BcfGkMHgBtL6oHacdxDFkDZU7cQuoHsKZ1L2r+d6x53jEjYKo9nvCLwzN/UYwwIGJDWkqbdDhqoj/U87QCRx2URIs2bedmXkhqvzWM9MY8dOhpjJZafSv8a9qSXLQYqNH09Ni1B/9ogkLMLlvBDW6H+YhXQsA+fJ5vcA7WNirDi6xYFBYdxYVgO6ZJ5dCeqbtAfcIfncdVcg8tD82uEdhsXrtbn5057zQ8VI6YyCxUDqx/KHB/avZ5kWL6/wtjQ2wsoa4r0XkR3PTB0sbMNn/rO0U8x9KOCzkO61vbtR+Z1GQndNIdjVPDwf1BLAwQKAAAACAAtZ0pS8WGTnEEGAAANGwAAJAAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL3Ztcy9jdXJsbXNnLnNkbFVUBQABtkgkYK1Zy27jNhTd5ysIY7oZJI4kO89BF7R0JRGhSA1J+dGNMEWDdoCiBTrd9O97ScuOG1IgB6iRCSYKeXjvua9D5eqKdLIaOJAP5aAqqD9dXd1+xC9ifvv6jeiKk/rr76+kef3j9a8vf7/+Qn7+h2zp/ibPSff67duXX1/JNlvfZBn58w9CVjca+psiyx5JvnperZ7v1svsaUL8wKpngqfwTjdL/He9JfnygdjVN9ndzSojBW7In7Mn
*/