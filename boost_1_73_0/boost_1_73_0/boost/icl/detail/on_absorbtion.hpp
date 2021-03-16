/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915
#define BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915

namespace boost{ namespace icl
{

template<class Type, class Combiner, bool absorbs_identities>
struct on_absorbtion;

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, false>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;

    static bool is_absorbable(const codomain_type&){ return false; }
};

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, true>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;
    typedef typename Type::codomain_combine codomain_combine;

    static bool is_absorbable(const codomain_type& co_value)
    {
        return co_value == Combiner::identity_element();
    }
};

}} // namespace boost icl

#endif



/* on_absorbtion.hpp
C4BHAslisghIp7QxjuHd+6OAa4DHpomh4HHAJuBIGtIBj0+TIecJwL2AGGXE6UzmicCRwDOBZwLPAk4GYvTAPjrOSZN9HwwM4nRSakKa3A5VmiaGgej+uZMoA/4FLAfm0leYJj46LgSOBl5E+oEXA8cBFwDPAy4EVgHRQ/Nu/WVAOvl5OZBWSeuAfwCXAmkwcAWlF3glkHzF1ANnA28E3gu8JU3WVO4H0ntalSYXaT8EnAB8BFiZxA5W2VCvEXg=
*/