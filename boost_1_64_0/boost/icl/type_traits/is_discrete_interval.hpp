/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_discrete_interval
{ 
    typedef is_discrete_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_discrete_interval.hpp
cS9zUoKtP8BvnKRlKrOViaJDHAEM6tySWbbGif3pvTVp837s5Zeing9oyEyccRA8lBjChvNR+zgytGMCExpJbij44W9/snqP1I172idk4g+E28bNupa3HuNBRZebiJ2ojKAlZhvEgAv6XBUT/La/ON1FfrrDULtGF9x56vjAARuZHEQOBd9ekJDksswXHZayjHrDAwEPXmbLi+aI/66ijZ2gHsQmZyXO/B2lE7B/nYJLRk6kCiopLUCm+Bo8IqfZREKBZVIDTWGLMgHPTNAFYOz35pQmsEMIELaSfF637BA2s+eoxPFf/WA3frziT5PaQU6SMlcywefSsctGf9dpH4/jf11vzouKiA+uy3+sJXRui1hTCak7KtM+3TJrmSRfPA9zjeAXMKrE9Act5jJRb56CgVA2Zs7+4SP+F2MstgYC8cVutxnwuw7dHyqf0p7vIERWcjAW2BXTMSIwSGX/Ps2U8L54Hom2F0icJt+7dp3OmuXAuFeWzzL73wsKCrqUxveS6mrfoavUMbnF6co43l1H1vf0x/Y4odKXHrWhHFEKV4thqTG6yZjQ5A==
*/