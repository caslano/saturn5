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
69FhcPTmKH6liyCuymNVWBNcXmhOU8WxEDKd6CCRAq3h39nsvjduaySSjORejku+YdWlLCbWCEcY1uKxxCWTFq/1U2/AqnDFwGikKSqEKrHgwZkeO/t78hTclnylBgDLtEwE5+ry33td6dAPaRWmURWVyspkPghuyeQguHK/fS7uj6EtDT2xLOt+Yk2eBf2U3omFOWlWa8nWKBPfHqaE9oiGY9qhms0BS4p0GNA0TRTd1kbX7UGt2eV1AH32bD01VUSY9V1jDhLUdpWWRv1vIYl5kUNAMpOYNb5/yQYtd1t5r5vq2STh2F7ibqJMMNGsdfp1UL4ke2lG5MOPL+fcS5HNJpZAW2yDEmz/qdEC+UPPXohuMjt4V6eSjTMq04GpWt9eiqynUvTb897nz/HrV8gM7Q464SigftuTPh4hHNg3HBt83Lgm9BtTP6+KfP2f4Uq7wh5ej5h+c+FbUXFeDvBCNNsSIeZtEC9dz4mM7mTQ//a4rja5sLr61x0HGd93IaTJXVfXbA6Fq0NrElRvt+T940FbQcvaqp+9+XqyTRwgHC3u8ZTQPHifyTsqzO5yyWzdVBmWHuObfQxDyTcDoEpFVDPMXj8j1aakJqHnnz+PF87K9q89J0wWV0YrBkZiW8+Kt6YL/MC4FwPh
*/