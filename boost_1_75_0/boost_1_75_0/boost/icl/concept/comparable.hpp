/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Equivalences and Orderings<Comparable>
//==============================================================================
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator != (const Type& left, const Type& right)
{ return !(left == right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator > (const Type& left, const Type& right)
{ return right < left; }

/** Partial ordering which is induced by Compare */
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator <= (const Type& left, const Type& right)
{ return !(left > right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator >= (const Type& left, const Type& right)
{ return !(left < right); }

}} // namespace boost icl

#endif



/* comparable.hpp
eeTO1E159yi0u/wCenaZuv3wWkqJW+nntHr9sKWe7daKPWa0AJ/a5mcH0LtV54+dUGR5u+CvRfwOmy+wryA+UMEyn9q22lJ9mFEfzJSxO5F17r/vCvYDYTmEf5WfvK/usDrk1k04KcyhlMiPvWM0ceJei/ibZhWiJFNL/JP/pfOY/Yaj0OW8c59ELdUJMxajeQzdNW2uML8ZS2N+E1E8ZV0Hn+4ZYpENQmyaTxJomaIqjRT4Rq8m4PsYop9A0PIqE+/GiuwM+3eoMxatIdfUxy04Vd8bUYKmzctux8OHEGRX/pp6m9AmfDHiI/6H5VufUfUX14iHDXWxlOhJ/GRltonNoC5H+j4S6++UtzhTsns09p9VvczoQvNP/MzoGizo/n/qZVlinfK85Ul+R+Wy7wo9bD1osN/UZ0nlQ8eDXOGw2+5bNzbyUVNfnAl4myYyBKrqFStAqi2gefzI2qJhn/jlhBv0SctmB0e1tVNF2RFl9RIm4SoDKH+lfXEAOjr9aulMhpHfj4U/Q3XI5iNRerSomsBynZK0WpdptEBnkCbproZJgurvhqXHos1ke2FDcu9/ChteDYpEhgx/eppxqXHGfgg9BwYL0kBMgrHCNNjUfnv7PfOIfp5pVai6FpBj1UXJkSK+45o8ZHWS5NdKxj+mkOkUXHKQL2Q6kvOly7T2/ROe5ouMazfTvsB0lBc7DRubbTeQLeXFEdJa
*/