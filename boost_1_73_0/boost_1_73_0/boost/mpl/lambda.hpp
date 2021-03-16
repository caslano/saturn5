
#ifndef BOOST_MPL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   include <boost/mpl/aux_/full_lambda.hpp>
#else
#   include <boost/mpl/aux_/lambda_no_ctps.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#endif // BOOST_MPL_LAMBDA_HPP_INCLUDED

/* lambda.hpp
vKmSGlksPZYWshfIhCqTzK2GVuue2nVdTS2dTWn4nN6Omlb6rR16NzRS2djaPqO2U6ssqayk9yrTQ8mgUVXTkOqob29qo3c307QKrYJUVtboWs1oPaYZvkAw6QtrlcW6v7KitKyjcgz91fxfpLuy2Be39PHmtqdLbpeb20a6XgoVGnxodSd96hDfgDq/jZp85jAUlP2raU3Xp9Sy9C5r6q3ZVF9zt6qxhy3Zt5Bra06xZ0pxh/0IJT42ZfGQPxk=
*/