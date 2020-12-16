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
IkEgHf7AAxY4HURg/AHAI8gAI4I/APJJmFRlABAnnkQeTkcekHgcmAdOU/JJJCm/pz4pIsvwYlTt87aH1+Oh8ajg236OPO0G5nReR5A8PFyDMFyeIQ/iND7NwNxWgsa1CTjKM8XgeYZY1jTEg0AhWVUQ58FTFmg8T5CsDjwuqwyvx9sepR2eyQ2SVUKu08tBWd428TincrqnXqVPnjyKWiMqjaBBJwQZSAhCPAhxAp3zDIgBQEdcR7IMAAGYEEDjPPLmlfMAQOc0LkM8L8myiAM4nwqqD+CtFzwEYJJoiPM6eRxB3X5gTpM0UOkTIQ6Q+4Z4UBRWRRSoPBgMUhx/UQbKRwQYcdDBIwRgyHOrAFnQuAynQQaB5/WWBQAmzoOMwiPQgTlNKZfTDEp7QJN5BBpvD7CnPYgrbeM8n7Yp7QEdPMjJPNkQIc4jARyk1dgJABp1ApC8+gI4IIO8eiGDOKcBEAd2A+hESlnUidNRJs8jWQCZJm0aMi8KWC7P2x7y0Lz5EThPsjY8Lq9iYB7vxONESlsEb72cxuOCt/18sPIxGhMN+cqXN4jzYQcG3TuKEwkyAI6lyeB5ZRo+iMt5PBM4EYA45/JyeZx3wls2T0uT5mmHkp+3DzSD0i6eT1Mfedqrbid4Mk3OM9HrLuar2v3/8O8bPAfWuHYOC3XW57TD3xw5euz4X749cfLU6TNnz53/7vsLFy9dvnL12vUbP9y8dfvO3R/v3f/pwcNHj39+8ovISAgooitaLDCoeImSMipVukxZfXC58iEVKlaqXKVqteo1atYyPFe7Tt1Q6X+958PqN3ihYaPGTcKbRjSLfLF5i5atWrdp2659h6iOnaI7q8nudEyXrrHduveI69mrd3yfvgmJ/foPSBo4yJiSii9y0jMsLw/PzLLa7Nl4CjEnd8TIvFH0G4NQEBSGJwQE6HSBgUFBJUuWLl2mjF5fvnyFChUrVqlStWr16rVqGQx16oSG1qtXv36DBg0bNmnStGlERGRkixYtW7Zp065d+/ZRUdHRMTFdunTr1r17XFzv3n369O2bmDhgQFLS4MFDhgwdajSmpJhM6ekZGcOHZ2VZrXY7HsPLyc3Nyxs1asyY8ePz8ydNmjJl6tTp02fMeOWV2bPnzn311fnzFy5ctGjx4jfeWLr0j39csWLVqrffXr363Xfff3/t2nXrPv54w4ZPPvn0082bt2z54ovt27/8cufO3bu//nrPnn379u8/ePCbb44ePXbs229PnDh16uzZc+e+//7ixUuXrl69du3GjVu37ty5e/fevQcPHj78+edffhFFQQ6iHGohlEE4h3AHQRClD/74p9a5WufK3Clz5xwidxARzuFzR7jDET61xFpiGXxEOSLUwqeMUIYjfM6J58Q7+IhyhDsZsr3RAwgzowcAG/QA7uzw3R18AAWBDwA2APPdKxxgwF84AHs4hQOAkQY/CHwAsAEYafABwAZg7j7oAcAGPYCoOOkBwAY9gILABwAbgJEGH0BB4ANAoHAAsCEcYEDecAAw0uAHgQ8ANgAjDT4A2BAO8O5WfGsGliJI8z0+gO9J4OuQBCBtIADSwOBLHi3y1SUCIM0FkTYQIIB7uuDrwAcgbSAA0sDgy8NfDsXqAeXkaUDaoAeU04EPKKcDH1BOBz4AaWDwUbceUA516wFIG/QApIHrQg58QDkd+IByOvABSAODT6Ty6QEIivsNCAChCCAAvCKAAPCKAALAKwLgBO6XID+AApAfgDQw8oNXBIBVDqwDRn4A0sDcwePahPqAdcBUXAAgXVwABIBXBBAAXhFAAHhFAAHgFQFQAPIDKAD5ARSA/ACkgZEfvCIA1AeM/OAhDTo=
*/