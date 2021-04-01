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
rOrgzbcL9WxokEICKCD51znw1Nqc1hQGNEMOz667xnNcMxDnCLLbGfzs/GuATVqs6MyHipYIOpu41p5y8ESKynkwPNa6FLOIh3/A1cgzbgSIS6R3NdPCc2DXV84e9Efm94cvUAOci/Ex8wVo8T0ziokfb5OsIPGYjgd4anaWRLcQ+x0m5oK7Y241ug4Oq5kdrewpDDoPyMVfmXwfjLIxRtxiiZeh5riv8WZVhxY3x/EwPvzkovcNPOy2zea8FnA/gq+b8hOUrGJoH79809WihJd+gMSrevEooBw2LSXiM2aStZCbTYdxta5QF5VtYsKtmvscvDirru56daCyIRWOnTj406swTbHFJtZZSkPa8KKP0WRg7Pojb0neD/pbKwBusZLTpNe+Po6Ooeb1GcQzMTacHyEocwcAm2vXgMWY+hkrQDyIof+7HO8Hihr1XtVLBUpdgnLNKcWy7vo6YtmPM9iJ1GaP7kvWa75DzkckYf/djTbQZJjJEFG/T5JTJU4+PTYk4bhgfAp3NfapVNP9022BnWkeWljgLYtRhwUK8oTuHUOd+9nygqdDAg==
*/