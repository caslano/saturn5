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
tw0dkmR2dMisUGRLk+yuB0JjOPQrQu9yKCmZVgsplIvQBqb1SjayQ5KN7MnJppxrko3szQh9yKEnrMRrVuKzZJOWv+zTnBTz9OgUIzshxe7Z2Ke1CD3CodtSjBa6flxMRD+xsr9b2axU+95SjWx9qpG9K9UYd/6VatOSZiSOR+hlDk1OM0/n2qc0spa3+r592myfjsPw/2MO1aWL0V2S+s7SOmWIM4Yk8q+nHmXa1Qg9xiFyAyv66OZ00bcjw6Q=
*/