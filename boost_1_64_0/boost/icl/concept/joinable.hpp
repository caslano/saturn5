/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920

#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

namespace segmental
{
    template<class Type>
    typename enable_if<is_interval_set<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches(*it_, *next_);
    }

    template<class Type>
    typename enable_if<is_interval_map<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches((*it_).first, (*next_).first)
            && (*it_).second == (*next_).second    ;
    }
}



}} // namespace boost icl

#endif



/* joinable.hpp
4Mj7SKlh6nz9nFqsYWUCCg/FIhxa5fsnM32q2QyUci8bNkpC6zJ7/WuKnWAa5a01GBO60sHvZdJkghjhsF/AszI518mau8ZiCd6aHbGeEJds87+mxvvqSXXZZNsjR7rfNVTdEA3RzrZy3+Mnm4CHWWD0Gv2yjSkEAa3b3NQucv5AANBxG7YW9b6NTSN7ma3YzRzEbLJsjC+u7qNA1Tvg1Hj+3UD3f5sKKDbWhSPCGYA0diaSBVbs/RNxYa+/wm4BYjCD3yuf4YBW0td/DPJo0fCL2VwGUWbe++E+X1vUKe74ahFQ0yT1IOs784MGDuRBRV83q02A9BBOwowkxduFQTGX0EkwGKju8puzl83XIR6ZnPlnESOsB8A5+ygwEa8RK/VI7bkC/8mczTjnDeon0vUU9GwrxRFk9z1LGSleBCN9nETui3NcvRfBLD44udU4AilaTjcYo7tHh6GxFaP3gQehIZ6yUceH8ZnTw64aesEa1Nsdqv9/E7FwP0o9lWGlq8YrHE79Ro4vnDTIfrhpazhhl9H/FCQdngWeHFEpmvM5gV3wr1JNbJqZhw==
*/