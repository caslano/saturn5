/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_set<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return *it_;
}

template<class Type>
inline typename enable_if<is_set<Type>, typename Type::value_type>::type
make_value(const typename Type::key_type& key_val, 
           const typename codomain_type_of<Type>::type& )
{
    return typename Type::value_type(key_val);
}


}} // namespace boost icl

#endif



/* set_value.hpp
Kq6/oP4j+APLVBfehBfBFK9ytZs4fQSTkJ5ki3FYeo+UZCsOvyVoB9KUbSO/cOFXnXyiNAELTEmGaktWCSJMvZxCotwFQgTpFGOGcWdRU3yA+D1Q34NwslVeeP4jAPgQBz+lgAH4mbeG4Oa4HF4xszReEk8BGQ0csoxXUQ7o6zhcLalM1yBIs7xWbC2JKL3fLAJ/gc56WQY4U14mCLWKpjSVCn48xbcoT+OQhUcU9rSIcy0sZf3QSPEHVfG/OAq30rlaPPF2CCVBpwoGpDlbhZjVMASoNS7Bm0cxVI4PqA9YCTJeshqhGAfMaL7wcgYbxTmZ04imXh7EEQgIyVMpuQyyDOui1TMp/auUbvcfjYg79WhLhPcSQe7ynOf4OZ0PldVg7fStwYBVDlpklJNVt62679NVBEHH/Wb3nXcfamVjzcjtTd9wTayEOYQXJDMsRQo5nxLItLekOU07Io0yTsAE5RL4ohGuFhGWNPBhleAuKdJ6ATJ05kFaZcYw0aValvqTNI7zs29iT08i8OK+gMtTL8pCRMQ1ZjF4uECnwuBR7vq+5Xw6+waQOv6XUkGpehUQ6TfHgBWOAtkJBEAGwvBXaKcGB9wrW0EVT5IzJilLqB/MAl/AtWVXWXwtcOASGmkJgqIjElfkCLUC
*/