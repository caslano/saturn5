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
JGMoKYnxhlAvtThez585ZkJNJgXtSvfJ7dpF8B+VY3U82t4n9987Mu+/G+XYJCNX7J9t1zE9i3YqOgTY+Lbsf2t+RIodh4QIwni3M/8OX1d7CTef7sKbV2dzrYkjCMf1jSgnnJPq6vuDTuNb8bhm8VuzbcGPBkq05tKPj+yCtEY0sbOuY0QsbeEDF9jyln5hQSMVNPJyuKzAnPiCAr5Fo+9s+zomwjwRrB57cySSr+4jiIc7
*/