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
uFXQPRlvG0CX4UwBXH0Eiz2IJQdw7P5JWbmdOlcJlgPfmnsJ0xg6rIQHdwAic52rXVV4iyh2IJwJQMgqBGi+XfGc3QL25myuiAmSas/cLbNy0bI4X4E5VV44hWFaylDQ5InktipeqawPb+SsCSARJM3/YirHwg5VRITzRylGtWNNfXQiMLZVzNwBHcaSPRR/NfMBiD2bjYi8grIsENUseqcGl54Dh3Kz5Xxdah+VFapvxkM/b4azL91MeuVRqUW/nDIiuWHbTxnhzTtZn2AaZku6i1v4F3ZJk12tsHCLRw7RiyHsghCXIweMZSkHzsGqEmcGTXeQL91/IB+FXgHK0GTHe8iPXwqGgwgrBYPbKBlQKElwsGg9lU48o87JjH4x9fzlHUCbOajdMk1BE1ILUdTns6I415YmYRgQ6MUspZRFw+BTbtANIzaqeIM0Ya7y0rsp7Uj88/04gv416GFBPURSWjEL6Nu0LNCjKiDbhZMF3ss2CCckL4A7kkLcJ0efi+/oJR+P7ZPUfVPc66/ZDbF5mUIJHWjsc+3FGI1QnSzvARBbhHU2KOBkFA==
*/