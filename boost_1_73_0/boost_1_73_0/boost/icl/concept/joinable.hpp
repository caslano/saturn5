/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920

#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

namespace segmental
{
    template<class Type>
    typename enable_if<is_interval_set<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches(*it_, *next_);
    }

    template<class Type>
    typename enable_if<is_interval_map<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches((*it_).first, (*next_).first)
            && (*it_).second == (*next_).second    ;
    }
}



}} // namespace boost icl

#endif



/* joinable.hpp
efC28a+icjUmDXJ3BFbjzfBsStnYiZPKdnkaOuyuq1z5B2bVyh2YZeuBme9SFWp1KpUZlhkjLBnXTLZDH2cQZkYkYjNUOnFSYAxWSmMwM1ITUgWR2upR2K083CqvmkCLecpzkxGxmeMyoqHJPsreJKU+TlNxKrdPgb2BXwL7E2+auM34Jk2GHt+miU/h79LEL1VTmlj3NKfJ0OMH4KPAH9PkgDVauPg3wJ/SxPX2L8A/gL8CUxE32q74vsD/Amk=
*/