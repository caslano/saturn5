/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_set<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return *it_;
}

template<class Type>
inline typename enable_if<is_set<Type>, typename Type::value_type>::type
make_value(const typename Type::key_type& key_val, 
           const typename codomain_type_of<Type>::type& )
{
    return typename Type::value_type(key_val);
}


}} // namespace boost icl

#endif



/* set_value.hpp
acQgrZgwIB0sLBm89Zh7AZ3F04qmQ2miMyoRZg4Hj4lBM6EI9spzeVwWLQGoMKIUpAQzoupI3DWjTQ56WAaei0IrMQF/sJKjXPVvrsMsPXgwu7VxkVFnp7gIFz7M7ne4LK//SVflx+w2xEWW/pOOtwwcwvmnqPHKMsEu/9xF2WB0K+MiG//ZqbQKxMQBQbbMFFRkgkvhjAg8kX8K6ip3c92dWq0Z1uvzAxOgTgdLGRtmoO2OsZwXDEHb1fWfIKAjXUW03f8lK+RfoMvAesNtdM60UHNL3yxzbHwyj+E3vbYCKjixRoaOaIfXvBnHg3o6Vpwn4yPBd+SlChqJB+Z65STBSO24dvqLj72udsy2pqU+WPnqCkBEPyh+YkKb+x8cXXk4VFEb/0qloiTZQwiVkH0dkpAtSSjbVLJkZzC2saSQLFkie8i+jH0bM5MsY1+zmxn7YIyxDrMYn+/77z7nec69557fct/3nnOeN9zv7mYPLetDLNPtjgy7zrPZGl00q/gQe2tIHCcoBB0T2d9s+xBrjYl/08ZXVHnYpFU1Hs+UJG3oEk2Y7pl7VxnxroSPU8ROrlSwUTiyqWPmsaqcQFkMl1eStBNtNPssN0o9x2zKF2vwf+CvanX5h51jBvHF+v8P+bNA+7Ji2Nk9vN6cAZ8WxYZ6JhP2rjzC64zXNzxQPvGJbv+bSuEzidz6X/LWIKfuPG457Pvopojd
*/