/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_splitter
    { 
        typedef is_interval_splitter<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_splitter.hpp
dacuQGhh2hSUGX1lghlxyjW2eAAU0QLQSIM2s1UYUpDpIpvV3j1Ald2JVn1jhi0m1pC8OXmxC0f2cm+xi7XM4biE7N9sADV1aVhWfSXUR926fmnLW8rUFpxwtX1/FoiSt1ryiHbVS3ciMqVQBiymXvsVUy5eHoUxswUhOz9lZS6f9Oi0ClTML++gBn8AYfRFetuL7KoC1O5YdJGNbN8yVGxebewlQ1bOp7sO0XcnryVI4AytXKQTS63I4vD24sh7LR5CS+Q62MkgN0rnzDkexub3jrwAR2dTD0AN0Ir7z/lNO+SvhOou0EsxJQ/NCviNFaIvYHBjnCNyXJMmyP6TZ8bmXG3KEhxwMAn5PCgfWXNpvg9RxpyMjcbbCoc8CyFtZAxdNFkV9xEOKqfEjxEaIIC9ry1DEKhZoiWQoqsZQ2qekJSBNiIlK5ARjalCrNgrNHkCAArzjBlitdTDrJh1kaobDSaTqfliVX/4Uuv5gRERcwcS7gynG+4UxzV0EE/VZxTt63HDCx8pYx5OfUI/LLE+Z1cAzPGI73DFu19xooh3W7opiecI8XOEhA==
*/