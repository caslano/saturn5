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
0A9S0mJ7RHnCnaZGX6UGnTOvQmv3VQjJqea2z7oBAPogOOTWOVSaU3wZZh/wZPM2DFg99o5m6aiujUJOaj58zH10jWwIR4iCHIKHqBnrBHmI6HOK6nGxby+EUyH6NoH06IggT7Cii8lYbcxfzTGedI0HXucJOpOJdLRqMswwacoRN5n3O9B41UMv/hImEWz8VF4vnhlO3Q9kEYWyIzKcMeTfXur16HNTWT5DzPSB04AdoOlOvFQYaQcYHWHWYAIc6WCeyWA5UYgbPrBBHLj73LLHBSCGiAKHrBSH1coKoDfapSeWx0AWD5DIa3iiOwxKy/IXA5pNDGfrB8J1XgFw45McMbrf4lrWWQHc48FZlhkNIwmkBWG1rwQg/vErg+AKIjPsbTNsZbjLKrATvXoxII3EcN1+YBUtS4wlQCiEtCis9o0AmlulDeA4kRnrjplTOoy0D/xdDE6GBeQUB3Ymo18u0L/qFgHVmIAmYjhxP5BSFMqLUBIKKbw2e90zw0nFEmEJWAN+wwGpeoK8lOHoiL9OFLrBWlUftGUWrgRnpOH3sDXDB06JAwuTwVkusD4ykBN6pAq8Zh0dqaD3BQB2OphUMhjHDeYRj94ZWYYTw036gc603T4FQG+hkJWSsFp1ASg/wq4PDKHpOJronOGnYomynHEDPMECYooDzZPR+oTjxZPaYbAo4aJ3FhBmxNEaMAkH1IXO2aoEV0IC
*/