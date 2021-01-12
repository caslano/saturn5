/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 

namespace boost{ namespace icl
{

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct is_concept_equivalent
    {
        typedef is_concept_equivalent<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, IsConcept<RightT> >::value)
            );
    };

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct has_same_concept
    {
        typedef has_same_concept<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, is_concept_equivalent<IsConcept, LeftT, RightT> >::value)
            );
    };

}} // namespace boost icl

#endif



/* is_concept_equivalent.hpp
eR/RWcaRa08XG8ntazlDNC/rmcUOzUIDQr2P/WgELYgzAOm24n9kOdna1Q8UXCy8RoMFNs6tigU1NX5vWL9eYsEOICoaD8bNgqEPtSCsnOEtUjeXH6qffRxvap/kWzZbQQNXvmjVbKVsHyyadvVYX5/ifPckLRqjFaAh/rXPsnyMNNEF+B39O/uAk/DLvI8RvP4fAaMkcCfy0/gkZ4lfN5if7WU69XAhXyrM1i8VSq5c9o3I
*/