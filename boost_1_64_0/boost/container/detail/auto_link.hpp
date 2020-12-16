//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED
#define BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

//Define BOOST_CONTAINER_DYNAMIC_LINKING which is independent from BOOST_*_NO_LIB
//and is needed is some tests that need to disable some checks (like operator new replacements)
//that don't work across DLL boundaries
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTAINER_DYN_LINK)
#  define BOOST_CONTAINER_DYNAMIC_LINKING
#endif

//
// Automatically link to the correct build variant where possible.
//
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_CONTAINER_NO_LIB) && !defined(BOOST_CONTAINER_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_container

//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_CONTAINER_DYNAMIC_LINKING)
#  define BOOST_DYN_LINK
#endif

//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif   //#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

/* auto_link.hpp
XcNgTk62M4w6ctXaiw8Znz2p+wk/mJyMzzBcsaE1TCFYvdT9PWBKwSpYJibC1GR8z86X79YIFkfG57urHfcnTEvG5wsrl9McliLkxsxv2AamF2ZPUp7uB5st5PpG7n4HMwi506nOc2BZgp0ckRUPMwpWnf6KGJYn2OrqNdQws2DHUrzuwPLJSjMbebVdDViRYCmbtg+EOZS2nS/ssH0zmJSM19t39dYTmJzMmdniqb8/gynIXPjZnrNfBlMKltJUqoSphTX/nrWqFSyOzIuZ3+mnjrAUMk9mn00158Bmk/Fr90/J1yCYgcyDX7uBK+rBcsgqMzvcKvUtzEImY9Zw3kc1TOJsu+bA+VlLYDKyOswyP5VeC9OQ8dlXfrydDNOS8V4Cd/99GWYgs2fzzb0/IAOWScbPPfRi2gtYjlDPEJO5ApZL5sosZNCzKJiJzJdb+7Z1rL89IMM51KJ7qQ3y1EUwqYu9RP3jO8XadhJJ3dSNnWA6MryufLN2c12bwtLIfmEmr7yyOiyXrAazzR/7X4MVkTVi9rdqwRGY0tVeUp/Zp9dJMlgaWQSzL9f3b4eZyPx4Lxd71YMVCLlmQx+fh0W42UtCmCV8Tt1ZbDPtdWTYlzp29D1U0KT2MBMZZv9mMzaUTyq24bWk7j9zde16/+pc/eIomI4M1+A367ko+lSx1VKks1w9u/Dh1npkBWS4Xr5Z7zczomASD3tJGLOji+y0sAiyusyCan7E769bpZBhzfp2uoTGR3o4waaS4TXum9X2LB8Imy1Y9Ltyl2EGMie25qq9rcJg68kcWO7G3J3vYFmCbWnZ9gssh8yNrenz/kgjWK7QS+y60OWwPMGmJSw+DjMJfY6qWdQXZiFzZVayYcsgWIFgY7/UsM4gkdrup1NU53YwKRmf4UiBaymYXLBh/wYtgCnI/Jg1P5CogqnJnJmtuKqrAIsTeum07jdf2GAyvi9NTm68DxshWOvKK7xgemHN9E+PcmCzhVxTc5OaMAMZ3+sP/fNrw9aT8XM/lpn1BZYlWHDUzQGwHGHNyNU1esNyyVyYqc6XHgczkTmyNSu3ffQ3zCzkRhscR8PyhVxML2c9rECwGtdqeMGKyOyZhe9sch32WbChV9+nwCSetnvdT3qmLkxKxs99VJ+en2EBZPwcUnxvzIaFCCb58EIJUwj1nEzRC2BKwbq73isPU5N5MLuRvSQfpiVzZfb4etEfsBTB7oTHbIWlkfH9zGvxx0FYumADOibthhmEXi6+nuMJyxHq/bv4UStYrmCRPU1OMJNQb11rxxiYWTC3bjdbwyxCL90fWWbBioR6vy6fdx/m5GVrp0cOuQ2TkfF64TdO1obJBZtyyqchLJTMk605yT2nDUwp1Gu1NDcRphbM0iTxJCxOWDNwTLW/YClCrsaqsfNhaYLNanivFswgrLmi24L6sBwht8btwCtYrmAlNwe1w+dZJjI8h0TQ623bxLuHYWYyXNffzBT7bwTsCVlJlptdqcxiWAGZM8u5Ny15BCbxtl1zvKmrCiYlc2F2IPywGSYn42sGr4ysBKtG5sh6OTLXaIHVESyoscznhw1XkuF3Tw3o87r23tVwTUhSyHDP0NBOIrl66Hc5LIesITP717WnwSQ+dC/lXnyP0oisToPXq2DSSvb4/v27dTrQoGaxJccryVLsinNN7fqHv//6ub81V8VeYnYstmb0/+moLcyA6RXWz3e/27PhHwdbf9tEhjWV9M8P/11tUWyxyem17CVaSbE1t5tp3+jc630waW17Sb3iNb/bwwWjPlt/x0IWUaI418KuZv1FE90aFdvAwZJ69N7Codha0v31goe9p8EKGlr387sNnzcHv+U=
*/