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
D+rpB+tZShb4ukXT5c4UR8bK6dwNtMUrpqcKELFvwnROWovEQfCHp/tjvRU8cFpwtvdtCp4DKLYRbUdM/IbpqSG2ugjI5M/IUgCAfRNNGED7xjOMCynPV3MbtghjK6fP/7BExrSkGfCygC0FJNCgI4kyo85VosxIPU3At2Ob+byYRMRekld/h1L5sk8sP0R1r9Vv8TysfqLwVFIlWPWxeLkr/doyClskbVxezTicANenc1d6
*/