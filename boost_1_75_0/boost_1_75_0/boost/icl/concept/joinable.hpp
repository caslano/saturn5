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
92qwF3dlHNDCNgmdKD/m/QUFPgQ6IJhHP3a/sjPYsNsTRaRVuWPRURKTEHeMuSOGZTPJ2etZ91E22iJlW/CiCa48yn0UJ60dv0iwOJfIqSkRxw2gRwe4v13ASRMM3wJE+1mhXzl1GW0aaM/WZlXCOEzia13RyR1oi/ViqDxgMZ4E7X6Gq23w2zI//45T2Wppo+3u1IVt7pptHaKXpS2hvYFAA4d92+mYD1ExsSztVeh786ZZIBY6KOyyiF/OYZHGGqENM+TfEBooXHqKBTzbLd1sbopoIcngfu+st74w0wuCtl0PdHXJRw1xL4g5eLzoBsL9ql40ZHDjHb7+eXnMgSMfLBFECUknY2kGAt7+Ap6GEx6+RnB3DoGg0iYG+j4EOovpxEg5TnDbjwx+0V/pDUs6p0Ut5oBkxTeFJV83znHSTABhN1We+JsJHNI4CwAzYBBOzcuaAUp07kR45EG/rk7JB/z9kU8IOdk8/nj3t5W2gc0SJjomtv7dQBE/8ANJSTBH7m+s2M6RJe9fEaVaFjm8OPIflvZ3WNbSyZAmYKCNX1W20RVBA+N+YCrXh5dPuoE3l9Gx4dqJDera6/WeHLxwi7W3YlPVWvU3VQevSweyTV4DCAllmPL27D5ZBNR8eExkJjTh/qu2l4yp4F2TVr/kdyDgvtWQi5UJYr+2Mt/iASTiScfHGkwnl6ylee5QsXkDu3zuRvrqYjyh
*/