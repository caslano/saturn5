/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912
#define BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912

#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct identity_element
    { 
        static Type value(); 
        Type operator()()const { return value(); }
    };

    template <class Type>
    inline Type identity_element<Type>::value()
    {
        static Type _value;
        return _value;
    }

    template<>
    inline std::string unary_template_to_string<identity_element>::apply() { return "0"; }

}} // namespace boost icl

#endif



/* identity_element.hpp
Ueq8umwEQwuUyKjkCnC7y3gbXG5LNME0UO7hl0WamHbmDxLbemZqZRQZCDTljhsiBQaA1dv0Y9hE1fgmolsYftXHexjq21caQgu8BmvK7+SJpDeD1zxUe2a6NBNHxbLU9wHzD4vIypQJV6wbl6XOiupyvLtvxgVpnqqdD5/29CUZV8Rf21fnHnL6MZk4b9n4D6q1ftD7HXrr4rb1UY1aTpTDx6gWaBA5NdvQyIo2sMJz9U9uUkk4/EsqZNX34YKAnHdAIxm6/HdRtZaOG6en2HyCo1ZSKtXRI206Vv8giLZpSoa1vRVWT2Ky+jjaxKvm9x9QSwMECgAAAAgALWdKUjoE0YHkEQAAkSwAADEACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy92bXMvY3VybF9nbnZfYnVpbGRfc3RlcHMudHh0VVQFAAG2SCRgtVptb+NGkv7OX9EwckB2INP2TLK59eFwq5Foj3ZlyZHkmeQGhtAiW1LHFJvLF2uUX39PVXeTlOzZyWJxgyC2ye6q6np56qV5U5iduNGpuhZxXaTLTfa8XNU6TZZlpfIyrL5UQSAGJj8UerOtxNvLy7+Ic/x4e9kTfzPbTNzJdLdSxQbL7lWx02WpTSYqI+pS9USMnT2xM4le46fMkgtTiESX
*/