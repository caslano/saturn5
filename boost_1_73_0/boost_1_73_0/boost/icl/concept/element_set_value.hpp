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
u0aXqkdViwq1rhp0lGt4yNhLdXBa712WJkm+/0lNwJXFhD9ztyrSChwUFFzySYfHr//G5v0fG9AtD/7+kIYYoEHZUSYBHfHT8ElyRYFJrvmsHIG6nXn10t6XkpQZyyfkFUAqbeAeuUXxAllW2pQ6msGM6eMiJ8ArKr4sSlOSTYu5cOTcChcYfKoMrdJ6VV3t5vWCyfiY9SaRL4GWlrZx7gUCyhL7gmsENKNTDlaLzgaUlq3gx6N1ozC8d6kbYzsFJ+G9Mh9T+yoPl1mhjomEHTJCZICgNOfnyqefLM+iRjy8OzrD3mXZAJeJNW3BIEzhYCwJW+471VhIzXhvTj/UjYflPh4+nirgO5Gethq7RpEdJenSLnol1ZrxgIsqN3kgtlsteb3VLj0Uob/SmVH9IwgNzTfXXuf8fY0rmCtY9Bk+po7GlCOKKdmXKFBUc22vpZ4IOI6xSAnx2XU4y8MlxtyxuO4q8vSjSqiRORphxXlqNQnVdq4oEaPOp/0gDLkM0qgyY2w2UVqtkHB3Cwuw7BfLWcGKzYlhScPJaPi6PDdlFG5bTuddu0pkZTN4wzhg7jSOYwquulGMp/ruYROqrl0e53RUxnUD0ffiGPzlmf3wL/rO2N0onOfapAfQRq/fHR6fl+naaADLVw1k
*/