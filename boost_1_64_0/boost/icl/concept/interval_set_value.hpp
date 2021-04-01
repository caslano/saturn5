/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_interval_set<Type>, typename Type::codomain_type>::type
co_value(Iterator value_)
{ 
    typedef typename Type::codomain_type codomain_type;
    return icl::is_empty(*value_)? codomain_type() : (*value_).lower(); 
}

}} // namespace boost icl

#endif



/* interval_set_value.hpp
Fmfd32lcJc8JvJfLwDS3t0waM+c5sig0F+9cymaVDOhb7eJOEPyaRS9DPcpyyqcou8U6RdVEiMkp0tVi8JcRRWWyhymylThxNTsqXYkPsY25cHi/GdN/18ptQQ344qHfHvSIsO0Hs1mPV94oChh9ozMkg1l3RcailxTs//tAS1sobAfzN0XI/7Y2zCchWjds1tsiyEFb/GnQeXUfGh9b2SQeqhFWcRbVBw/3HKurefGvDWLCKAy+7NIKEYsS3Pn4cd55PNHqaFKuWA42cQ2VH5CGGBjWFmsWjxpe0sIhEnLbCiUoLFeGRtVqwUC7xnR5e6bN6XEm/uRXHxk06d0i9GpSmA0TDq49QLDICX5D4IctcW2G/DGwKxbxm/o98vrUr9D2d6VBE8lQAkg5e6ohk+WBUu5mmqk4hKASevQoHCcn/gl6kWx/QGc2ZMWH0fi/qPQaPbljF2WRSj4ZV0moj1Oj+mgan4u6Nvz6T9ar4sA4WLCXUUWaO9b44pwci4J5gIKaCvm9pKBKfNe91024GHnj+OP7/iWGIk8U5jrNhxidPBFNEyqilAWPBw==
*/