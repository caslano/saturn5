
#ifndef BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>

#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct is_class_helper
{
    typedef int (T::* type)();
};

// MSVC 6.x-specific lightweight 'is_class' implementation; 
// Distinguishing feature: does not instantiate the type being tested.
template< typename T >
struct msvc_is_class_impl
{
    template< typename U>
    static yes_tag  test(type_wrapper<U>*, /*typename*/ is_class_helper<U>::type = 0);
    static no_tag   test(void const volatile*, ...);

    enum { value = sizeof(test((type_wrapper<T>*)0)) == sizeof(yes_tag) };
    typedef bool_<value> type;
};

// agurt, 17/sep/04: have to check for 'is_reference' upfront to avoid ICEs in
// complex metaprograms
template< typename T >
struct msvc_is_class
    : if_<
          is_reference<T>
        , false_
        , msvc_is_class_impl<T>
        >::type
{
};

}}}

#endif // BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

/* msvc_is_class.hpp
e317tj3H3sleYO9tH2QfZZ9on2yfZr/HPts+1z7fvsi+1L7Svtq+3r7R/q59j/1r+0H7YftJexEHuoOiA8OB5WDsYOHg5eDrEOQQ5hDhEO2Q6JDhUOJQ5lDrcNeh06HP4bXDoMOow5SDCE+Op87T4TF5pjx7njvPjxfIC+HF8pJ4qbxdvHxeIa+EV8qr4NXy6nhNvFZeO6+L18fr543xpnkzHKmOco7KjgxHtiPXUejo4+jnGOQY7hjlGOuY7rjLMc+x1LHGsdHxpmO7Y49jr+OI47ijiBPVSdVJ3YnhpONk6mTlZOvEdxI6xTjFOcU7JTolOaU7ZTvlORU4lTtVOtU41Ttdc2pxanMadRJ1pjjTnOWcNZ2ZzmxnjrOVs8A5wDnMOdw5wTnVOcO5yLnOucG50bnJudm5xbnLudu5z3nAedh52lmKT+Xb8nl8J76AH8gP4YfzI/iJ/GT+Hn42v4LfyL/L7+D38N/xB/kj/Cm+uouOi76LsYuFC99F6OLuEuwS6hLhEu2S4ZLtUuxS5lLlUuvS4NLt0usy6DLuMuFCEUgJ5ASKAh2BlYAr4An4gkBBuCBKkCBIEuQIygW1ggZBo6BVMCAYFowKJgSiruKuqq4MV6Yr25XjKnT1c/V3DXINdY1zTXZNc0133eWa7ZrnWuBa49rs2ura4drj2u864ioupAkZQn0hS2gltBXaC32EAcJI4R5hpjBHWCIsE1YKa4QNwpvCNmGfcEA4KBwSjggnhBQ3KTdlN6Yb243nxndzd/Ny83Xzcwt0C3eLcUtzy3IrcitxK3ercGtwa3Rrcety63abcJt0E3WXc6e7G7tbuAvcPd393P3dQ90T3JPdU9yz3IvdK9wr3evdb7pT//AeCx0oA03AAPqADYwBB3ABDzgBIfAAnsAH+IFAEArCQQSIAtEgFqSANLAL7AG5IA8UgGJQCspABagGNaARXAPN4CboAD2gF/SD1+AdGAYjYBxMghkz8H4ToAIaUASqQB3oAH1gDKyALbAHTkAIvIAvCALBIBREgEgQA+JBIkgCKSAdZIBMkA1ywBFQDEpAJagCNaAW1INroAXcBW2gA/SCPjAABsEQGAXjYGrG7+8bKAVoQA4oAk3ABCxgCjjACtgDHhAAL+ANfEEACAQhIAyEg0gQBeJBAkgFaSADZIIckAvyQREoAeWgClSDOtAAGkEzaAFtoAt0gx7QDwbAMBgDE2AazBDBe9JACtCBKtAEDMAGxsACcIEt4AEn4AE8gR/wB4EgCISACBANYkEcSADJIA2kgz0gC+SBfFAEykAFqATVoAbUgWvgJmgF7aAL9IBe8BoMgmEwAsbAJJgCIrMwf4ACqIAGVIE60AcsYAosgC2wB3wgBO7AE/gAfxAMQkEYiARxIAmkgFSQDjLAHpADCkAxKAFloArUggZwDTSBm+AuaAOd4AnoBX1gEAyBcTABpsA0EBHF7wOkgBxQBMpAHegAFmADDuACHuADd+ANfIEfCACBIBiEgygQAxJAEkgFaWAXyAI5IBccAYWgFJSDClAFqkEDaAQtoBW0gXbQCbpBDxgA78AQGAWTYIYY5g+IAyqQA8qAAZiADYwBB9gCJyAAHsATeAM/4A+CQCgIB1EgFsSBRJAC0kA6yALZIB8UgCJQDEpBBagENaAO1INm0Arugg7QBZ6AXtAP3oERMAbGwSSYAhRxzB2gA1WgDhhAH7CAFbAF9sAJuAMv4AN8gT8IAKEgDESDOBAPEkEKSAUZYA/IBNkgDxSAQlACykA5qAH1oAm0gLugDXSAbtAHXoNBMARGwDiYANNAVAKzB2hAESgDTaADmIAF2MAK8IEAuAMP4Av8QCAIBiE=
*/