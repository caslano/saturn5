/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_element_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_element_set<Type>, const typename Type::key_type>::type&
co_value(Iterator it_)
{
    return *it_;
}


}} // namespace boost icl

#endif



/* element_set_value.hpp
JygdSf7MF2yk+uxarXrlXBSTMdvgYPK5cB9xC/c2lbBwOVX/i0rTUmBSdBZe01lDUJTzevs0HwryvDz/ezCxrXVjo5a5pdiujPIe4OAi8ZdfnTDtz+xu2odFffW1XpGcbI3RQagYkxd/YORobsFTC9m4fDHUBrfwWdBBQd7IHU3HCTzvCpV7uvup9UoKstiXlzfcSFJ2EklVJPAeiuZf0quIKnZlWwq9QyFyW1S0mSr7LCrFYQ0fkKGcbAo6Doo=
*/