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
vjO+pRxinyZrarTPQ9BNtRs/9yzpp6jY7NTDdYpbkgr+7gJbLpKqFJt7i34zufi+ZxO05kIlvKaVlGWiKynj1aCURZ1oqn7rwqqcW8ps6/34Iv4FP/q297L/Larpfgbqf1c8nJu/mv347+To++zkaP2s09z20/8DUEsDBAoAAAAIAC1nSlI+JRvQWQwAACorAAAwAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvdm1zL2NvbXBhcmVfY3VybF9zb3VyY2UuY29tVVQFAAG2SCRg5Vptb9tIDv6+v2IiBEjauEqcbYFDellAseVEW8fKWkraosgZijy2dZElrSTb8f36I+dFGr04Ta5d4HBndG1HIh9ySM5Djrz7e6QXLxMvpRN/lYaTLF6lPtX9ePnL/h78I/vWdF98dRdBRpI09ul0lVLic72M5AtKZkEI34KI5JuYTIOU+nmcBnDJi6YkpUmc5kwQcabBbEZTGvk00wmxcgKw/irL42XwLzolszhlkOtlxtVQPQsAb0tCbxuvcl04BKoRpVMAjskDVTHgAkKEse+FBHSp6pOurgf+rTLQeNiSJZW2M0qSVQpWaXaGkvjq6jJSDBqQ5kGE6CxiJJ4RD4PzT7BCNkG+gJUT+hRkeRDNJQa87q4dgsvS5bXT
*/