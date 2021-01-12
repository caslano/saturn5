/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_interval_set<Type>, typename Type::codomain_type>::type
co_value(Iterator value_)
{ 
    typedef typename Type::codomain_type codomain_type;
    return icl::is_empty(*value_)? codomain_type() : (*value_).lower(); 
}

}} // namespace boost icl

#endif



/* interval_set_value.hpp
O9Ebr1GeopJNuwfGW79xAM6tPkn4PrHhgM8tP8ksBRwAudGTHG+lsUgGZO+YeLP9jqf8E+utiXtzqNQSRC4iFEJ0vJ8y0EJ/en4RwckymfkjBYURbyryI/G09EV/BuZfNjtAOo8End25D1J+hkUAqBXtyxGt2q3+lo+bsbJoao7o00X88y9MO48MhR8ORepeGlFTyCxlRgunaJ/vcuZO3YQcufOHzs5lPWOknl5ePX00k0K+
*/