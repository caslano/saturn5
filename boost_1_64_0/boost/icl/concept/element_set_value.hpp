/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_element_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_element_set<Type>, const typename Type::key_type>::type&
co_value(Iterator it_)
{
    return *it_;
}


}} // namespace boost icl

#endif



/* element_set_value.hpp
0cBfJGgHinvnNOdDLpoLz1UEWDGjc/HW4NDIy0h2hsX0O/Lu5tVwtUJTcUDTKH7TlUxwA+ubXGtfjhVd/Kx4aJ4elBJLWPs+WEJ5vFVOJ5lkgT1+MbtYPR/WB7ulfs/0wdyWhWDxHENGeLa2TRFYcjpL0j4NfcdIfeCmADWOqSSFGEhE9C4t8yz+uVp23qP7pCnmWr0HfwYnfOffAp3W66j3p9q9c9Yh9iERVY5I9VDV3WeV77kKgu1yfO6h7DCn2vmkYy6D0QzDlZlnGMcfhaTlHpaXykezwqmxKDp4/JI/zVmMEY1yGJADmsiCFgQiq0WrsdKW6dcD4Ez67ciQebB1jflTgVXopiB/QYGYEoI1DH/fQWAzzvefdxVVwdAquDEX8ezKSXISjhvCVcbOcq3TtqiypiNW3VzTFQu1Qp53a35G13j7j9i1TP5RklSjQMISF/L+O9b6UaCClOa++f4iZBtKusOuIPmeenEsNLdnnB0w0/rjiPwAsW6b+GHwYqRSFMvHotbvFyv7dCg4jecYCkn2MRMqUczreRZwseNmDn5CF0sS+Bl/zw==
*/