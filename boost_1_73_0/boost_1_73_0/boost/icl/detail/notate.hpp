/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
    Macro definitions for some useful notations e.g. iteration headers
-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119
#define  BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119


// Iterations over stl or stl-compatible containers:
#define ICL_FORALL(type,iter,obj) for(type::iterator iter=(obj).begin(); (iter)!=(obj).end(); (iter)++)
#define ICL_const_FORALL(type,iter,obj) for(type::const_iterator iter=(obj).begin(); !((iter)==(obj).end()); (iter)++)

#define ICL_FORALL_THIS(iter) for(iterator iter=begin(); (iter)!=end(); (iter)++)
#define ICL_const_FORALL_THIS(iter) for(const_iterator iter=this->begin(); (iter)!=this->end(); (iter)++)

// Plain old array iteration (assuming member function VecT::size()!)
#define ICL_FORALL_VEC(idx, vec) for(int idx=0; idx<vec.size(); idx++)

namespace boost{namespace icl
{
    const int UNDEFINED_INDEX = -1;
}} // namespace icl boost


#endif // BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119



/* notate.hpp
lX9ERvXDPyLbqgIjMup9K5VZkumoF2n0iGz8xImTp5/H6ysdfUsbE8tKZ84urxxr3JkUWpnzeQA3AOHu/Pesspl8Sdd5M2ZMtDvqG3j1hfLbQ68BFRzIlPHTJ44NLQTtoZdfZERYNr3UY+HI8m1kJlkcWUflulVBZGP1Y9/OD52g+l+Mg7QINNDqunDGzCnjZ86oQopYndn0UbImsyWi7I/eLw05D0H4E00/mIZswMPTxJDwiDQxJCxME0PC4cA=
*/