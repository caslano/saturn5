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
+cQd9RAJnuSOIOfP3y9k/Cqcr2R9jaW6KAK8fUPYHtYEDdtHvuhcv0STYHzXhBG+dW50fgau7Jw2CToverc7R+NejYZLmNoSd1fTZJgsc2AmUxlbK6Ixkh6nCS0Dn2A6z4V76MpcgLFD89PFIkZkD0AoVW8OXxGi/Bc70WVdH+qHED/fdoxuI2FN36Epv6BBLCnDnlBRGS7lMIOKkdgg7C9jQdJqmh2SN/2ZGE8b5BOWtkOaRmli43mdMOjbfYhEQ0wKGzrD1ZEa2p2ufWoQvrWxGQxxz/6D6zwmyJI2ozMqZWMS74QTqNEjbZj5kR7HHDxU5WGiwELjAIz5kuwT8FyYd4A06X7LNLMoKNk8cvBUQbJdz4ljmtaU274ErzhIOHgQFHMFXt0OD0oRSG4Xq531v3nve5BVXq1Nwyz99u5DrnzSYbQu1NvMPlpxqiLZ9E9PHhG6DTwaBOHKm3nTLiU9WER7UCvZHM8OF+FHPNJU6BoYkbhn3VLId6zbelXcu17cpZ5sqeXeW1J7ZeW5niWtXVQ+yL5KjhfQJxIiZB3CXqGXtSbJiYDrnGwWyK7Qv5almLKQSrKG+UTQqzBnmVmOX30jMTYHC+L5O1op52whvKBnFwQc+/tdkX/paYYVSw1FO0otxt0hLb2t
*/