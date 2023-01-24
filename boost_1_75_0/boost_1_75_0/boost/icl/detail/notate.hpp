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
pxl6NPb8H3d3XmT/S1qoJzhPNTn1jkA4aRyTXGpNm5YZU3ps97097e/0ECjHVBOf6IRx0oWqK9U0CT77NRLQHeXjvuOXvC0ml9fnXz2lrJfuabfc5/4qPQbOwl/BqtxEXVFwvCmX07FbHa4+rUNBTj68hVRm9Uug3MZPxf4mFHMVDWgk/BMvjeGvvO/E/fr0ZL/9NfFvzreO32oFWcRrnbT4gPDqXPGHO/xGn10oIewjcegPa0wPgYVwJmI73zZ3Hw5bkOD5yRy128ci5QN7xY5/XAHPDS5Ob3Pi5oYdEzpCLq9G8ed/KgjfttXoi/ct+1Ao86PvGxfhx29DLMfflTIe7M9fwTyih9qhaeNeu31aFTmxuJe3HFVOdfqa7l850vx3WtIl0PCKZf21o5HZ0Bvd9forDeBCcZHxnarH9WxaiX2zuWGNCKlS0Wk2TewnJDyt3q5qH4Z60bRP+6c+cghrNLb/WUcz02e54CsUbDYCyvrCnTLJdkDuiI1p/s9a/3vczyhNEDktKCjCRI/WftcIifb1e6jSLbB2c+famLTvlvCdBbvl5w3BuAK+eiwVicETRZP5pH42HokMt2w3mzsYki1bTMm2aa6OJLF6DTLknJTYXwFtwzNsrHgKEsnWcmXPsv8UW+m+bd6PMt5RZoWU1CjyjDEK0NquvpwSzp4KjkiVHmG/SrHzKitrdCz6o7yqewlqMr7zleX3
*/