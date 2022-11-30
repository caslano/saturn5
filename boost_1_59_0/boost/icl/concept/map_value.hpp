/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_MAP_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_MAP_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_map.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Map>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return (*it_).first;
}

template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::codomain_type>::type&
co_value(Iterator it_)
{
    return (*it_).second;
}

template<class Type>
inline typename enable_if<is_map<Type>, typename Type::value_type>::type
make_value(const typename Type::     key_type& key_val, 
           const typename Type::codomain_type&  co_val)
{
    return typename Type::value_type(key_val, co_val);
}


template <class Type>
class content_is_identity_element: public property<Type>
{
public:
    bool operator() (const Type& value_pair)const 
    { 
        return value_pair.second 
            == identity_element<typename Type::second_type>::value(); 
    }
} ;



}} // namespace boost icl

#endif



/* map_value.hpp
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
*/