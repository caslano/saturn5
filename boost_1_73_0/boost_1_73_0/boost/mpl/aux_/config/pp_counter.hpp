
#ifndef BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_AUX_PP_COUNTER)
#   include <boost/mpl/aux_/config/msvc.hpp>
#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define BOOST_MPL_AUX_PP_COUNTER() __COUNTER__
#   else
#       define BOOST_MPL_AUX_PP_COUNTER() __LINE__
#   endif
#endif

#endif // BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

/* pp_counter.hpp
K/mtKbQUYNaGl8rIgdMDjWFaM55L9AsPgwRenzK9Lqo3MDufedEhOQwGzs3NjdvCycoWnFk5vqepJStXk2H7xm45fAuVqricDIlPw9iPSETxjJVLZGJzNJ2fT11KAjegMV40RuqcmXxidYOMTlRlMYa72NQYw8rv1svtqnwHPGfaSDspjHJHI3rkkp3xJ1ktbT6GIB44A2eRFwbwUykLSLhjCDVbolZeLxJKeG9kmrpGKQRYBbetrW10hds1vrTzNp1EsJTWAEPHJ5o+qFAWlcQYBpHcooJMq1XnzcsCCfbJIb7vP0pQ4Ptw+fGPkvF3IoUPIl3Mnwq0t1WoZ9qzRir86/+6Qsn+hcxts4W77VjAij3panA7LfqCxHHR1/Wxk1tbo/n9Ns0kwxaQOG/25vPZhcP1prYKLXYXkFZsJfuagDWKD1fvT5KYxPAoBY/H2K5WWCWeZgbBvB4NUq5WKzToOY09b//8cr64mI3320Czy6uFF/hxCG4DbVW0MON20bYduK7o4iHRBxhcbl+LKlxLXWQbaEUCllls6VbA1h+QDPY+9vvQ5MoOnfSus0WAWiuruCqPHZzO0Ie/LwMsCGXsGJ6xHDhfkJo7XWLoMfBGl97+9dnV/OLy88CZci5rPD7wDtpk/hbsr0dP
*/