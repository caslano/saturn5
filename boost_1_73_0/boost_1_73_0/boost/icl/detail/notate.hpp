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
KAABxRTVMsaUICScKcEI1uxV8mZvB5hz9Ulvm3/7f9ZIWMPtCBmk/017ORYdb86ihX7gBn//1mnv0PBeSu83QuWuudUilZ+0z3rX7Krdnml1Li9NbYs97OlLcBQCrdtPNIAxd5eraZCF6+hgWt8CqbeG3u5efguUmufGz98EnV0DAuz2Nu1/W/G1LaW222ld7B6tFaTqN2zw+00Qu8NdQJHSb4fU3rdE6jdE604bFgYAV8atddfRt+irts1SPAl8Yd3qt5pp3egmJhfYXWLxUOOFbljtTtcyOue9XZ5mobJHvu4uiU21bRnahXapt2m8qrXvdpdYavss9LNUi2a02GHpN3GXAehp21LNpq7vLqGUrS21fUUXzZudC22rQ6tNnSqf8KBJgR5t3CjqfHUGD87BazzgOwzYZIk9j4OpPXZxJuQJX8zsSDr5QVt7rZrX1jk02dI+a81dmxcqkqzDyOwOh2dbdHZb1iHs4XCG/lptX7S0XR9D3nZM/bPFxjs7PDTvtXsmZjGyjO7uEisZnV3e9oyrVTs9eymt9otGkVrX0K52OTzLayzQ+xPNWrLL1Lb084sdHEMk26UM8FLZAzzpXqnMw2T/XKEhpf1T2tWF2DvFtt/hT2EXFZ21XArVNDStXdpmlT1lo9Tr
*/