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
FSwS82jBUiX9S0f5tQUucN+E0S9RpyKkzEYwkLhpzSu9IHb22bWdU4hSVrrkPmHvqhEq+VFCcHrlmoL9wg4BqfYgDjwLsoy55WgY0TCFwQS/y8ru55l2pmm60L2RkU0D6q4yBZVAmlqatkJ4JVfY2AzcCJBH/jzNJPnYkpKHWfTyRRUQ+oaENuiqvXg5nhlynOzNSWKXnRwXdJIaXzjA2i6T+mtVnjM1dBFrnXknDexQNGbNFUujCgs28JX91thh5pNfYxEb4XcVijtCjFfPTthHOzo9Nq14OViyQ043XsoljD9f9G8jVzP+fbR4ZGZvQxHBfdsgfZH+loyIdPtNmdf2AZSx/KjZOFbgnVK/Sp1JM7mld+9CMeTppm1jukMrajxIN8v72XT4MIhmdm6WaIqGYx05LrbHbW+KoHWafTo92is07k85BLUtG1FgZ66HdmTIFoeT250npXJfkXNh1kyU7Tl++BfOsbx5GI+Xk/5d5Ca6HCpU6DkBbG9tH/kBno+nXQ4dWp4/hoSBPpqtYA5g3HUhTtKztb574C3pGFGxiD5rmapnlYZbvpsg63i3e5ZprZp+jgY60WC6HEcfozG0ExfG3xewc7OL0Ey0afC5iONmVWfH94re6e1J/nzqaKwv7jzRcS9vRuNo
*/