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
fNb1j98XZEuMaJlDhdUcQBj4qHByEi4MiZjHw78AzmBYsqPtPDBfLn2Rr2wg9ecEM68cBVIoJT7Jq+k72u5OAGveNUc3q3bK61OApoAJ2Eo0p3vvZXLs7tkWFEHHh/f/4mdLEzLHtuaqnJeDzn/mI3kdTHsCpB0yj8U2zn8nyjnN8rphgWfHg5IwMgiNyrq8VxwJ1DrVrkB+B7T9iqrDguXlbrCKSI6DklRg57qlnQRdzEYhdpuQXzAWH2GJW6tUF+fAlGBJTs58dGfeWXu8aZuYYkFg7qyl2/r7FiMmnje6N/ud+X6xIFTV0xW4x25bXmsyMF16vdiknlaDBbDdUkkCINpaEKQrcu9WGwpOBCCKJL6CS/6zFa+DRWt3Mm8tSydAQ7YnI9nA28TVrFBoVZuYchE7fzcN0VCzu2j06lbCu5dK6iM+bHQ34wGmsZnq9oSDgr/burdY6UvvFTY7eRbQmW8xmcuGkXdLHluINXITXGT9/PqSIL/nb0hUk35g31R4njf7H6FOY5nIufK6lG3+qBLNrvfFdvEYYsuziDeF1RydKAB+BfH/MA==
*/