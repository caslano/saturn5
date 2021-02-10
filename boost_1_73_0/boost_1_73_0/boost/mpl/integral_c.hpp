
#ifndef BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/integral_c_fwd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
#   define AUX_WRAPPER_PARAMS(N) typename T, long N
#else
#   define AUX_WRAPPER_PARAMS(N) typename T, T N
#endif

#define AUX_WRAPPER_NAME integral_c
#define AUX_WRAPPER_VALUE_TYPE T
#define AUX_WRAPPER_INST(value) AUX_WRAPPER_NAME< T, value >
#include <boost/mpl/aux_/integral_wrapper.hpp>


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !BOOST_WORKAROUND(__BORLANDC__, <= 0x551)
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
// 'bool' constant doesn't have 'next'/'prior' members
template< bool C >
struct integral_c<bool, C>
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef integral_c_tag tag;
    typedef integral_c type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
#endif

#endif // BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

/* integral_c.hpp
DZsAAAD9AAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MDJVVAUAAbZIJGBNT8sOwkAIvPMVJF41/ADpxZOfsdmldmNlE9j6+HupRusJmBmGgbt4z8llAK46tigXed6bFR9g0dpXHqbkEzBtDNNHDDvY4XGuov3gtQhwfg+hcLGb2ADaNGD6jjxK6ovJvz3TBiJrukaak3YxTTOutzFbCIRSKVRiw9oT182q5z3KQyxXjx7zLElxXDT32tTDjD5uTL9ctH38AlBLAwQKAAAACAAtZ0pSkyv++I4AAADnAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MDNVVAUAAbZIJGBNTzsOwzAI3TmFpaypuADK0qnHQDFJrLpYwiRVb1+nUZtO6P3gQS7VR64yACWdSht3eT2LxTrAqsl3HRauCxCeCuFhhg66cM1J1C81RQEaP6A5qtgmNoAWbTR+IU3Cvpr8ryc8yUDKj9bmpi6mnMN+O3CMfTBxS7Jx7kOULJ6Khj2fdG4xPHKEvwZ4/vYGUEsDBAoAAAAIAC1nSlLmLAxqjQAAANoAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTYwNFVUBQABtkgkYFWP
*/