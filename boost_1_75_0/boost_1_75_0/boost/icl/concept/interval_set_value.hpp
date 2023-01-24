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
f5OrLOt8LjMVFgnXVDn0t3WP7Qy1r/hxGln2OwM+6/oHtbvbQsQTiTdUO+bBNuYjUZG1hQCdPbR+XNcwp7DwSaNc4qac9n780NZd943JJJPGR1FGVUmSfyBAAd9f009dReDnexs89KqdeKXUwjjwju9pu63LMlBXFwoC7FNBCZkoX8EI5Y7d8bctx0SfCEUVBvPZm4nJuUSl4Ds/Gvfk1d2o0z7Mz6JMK48zV7K1KK4hAFuAwDXh11whp1ytvvab5fkROserbcbuT77qfYi2fAdCT9Em8BP4vNEkrfYU+qmAE9fYudfFpF+s+jMv4XiMaRGEsJwvdn9kr+VGraGsVdfUEaHSdTVmASPxeTVLz5f5s0gudhWsJURAOgdOM1cycNRZz0gPKWyZiic/qY7aVfwOX1Q8FItJSDhKg1o5b9Guc/mYpNc+7lZGVui+wsV8rq3cYzcGJ4EWYcKO5U7eUN3e/ZXVvRN9sQksWUrzGj6KTQxQWRUrSxaV/i0RdZwKj7Bnhha6T1SHLtCRdutZ5mTjNXdGW864wgjexFhE+WuOJfANMzzE3DuEmvmr0zKo/IBH8sVwBw9LhlpaUXaaNYa2BQlrzvibUldL+kp8Fo9xfRsXGd97PDBvkWyWxvxeSm8b3CcG32IGQmfNncEGGYnM+1K2ooiadfjK6nOLGf1m/JIE1p0kV5MvrjAPOhOqscwMZlHpZLaEpzpL
*/