/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_joiner
    { 
        typedef is_interval_joiner<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_joiner.hpp
jZ7Yf6eVn4/XVqzJTYrU9WJSVNOOXxyAta02de2GrjweYhVfiyMu1+VxiFft4gGu0PIRSgkEGSzEqR0aA7k9A6JIX/hYmCQguUtAFsBhgoeGjStmA8RgurkFsOVBh20GHkBD9dgDnRxhO6X65imdGbvoMpPGSNu9CsNJvsnfOdrDps7ZLabTbjaQ/8Z+uSCYpAe7DhX5lkhSaa7pPbQ9xR/+vggMkCvqf4VH+FeQmma7PyIWL1bGxBIsiuaHXc4m6oSntIEufa/VeqFeClwNya2TfRWySoJX11Vc7Do+xGJ+BPf3lCWc7ZJq40IVxIeqRHsD1EXuw81IYN8PUV4EBrE3Fau9QRe8HP6dlvLChxclHqKFHo8HshF2rtgGf7dnmYoOYDH5lC3NSmn7Iqf7RUWYlIsU2l+DdJA4U2dmkg4W0OYB8gLxfSO7qGLKFl8mZ8WFN4jWyRcGkl5Qio5Uv4eg/+hIEEDfEPm39wk818rXnEeQkBKDdBZkUCgYjbi+oVdhayVksWbtmzvu/dtNUSaBWEWPBdeUJxQC+2jBZGFTCPgT/cW/bi+f+Q==
*/