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
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
*/