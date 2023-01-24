
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
cDUuFrzuGa7fX/6O1C+qYbj2Mo3jO8zWn8wis0SBHC+8vCRB//n0ChU2kDEdRuAl5GjQy4vbadMHuxWap9OkL6iknTt469ggYOLjKvZ34NuH0rXSInhoe+56W5NQZv/BQ2C7Kz7jXcxNGonM+eYJg+t67VVV7Vqgo6aKoYCHHZ0QsTB+nBTjLcr5x2jXOmdrmbdHTCAzQXalMvmb2vN7X7+EdNKAhDYvVYXiO1FKKR2uGbTzd04HhPRrpEIVEjn/4L1RKdVj/s57r0sNs8zXddx5Jb2yLb6t/NvDc4AUfBdauQMFSz0HOMEDZy68JpKOR7XyoQZzKhLqOZ+8SY4eOm79Rl43JsXtHCI8rTUvztyZ5n7Yrukr7lQrFE10To19J3SBvM94DU5TPC5lne8pnmNLOQaoU54T/mRj+hNA7+XtSkQy5G2uaKdxfcTcMBS9pv4GOVnDpL2+y4hSxwgpwRlV5BjLu0sZEsF9FC3+q1F9xEwDaF3MdYTqJwrYTki7RfZbXVFm03N7zhdjjW+lr3pobtmqUJTxFpCDYFvuv4ivRBUr7siJfG4ZDKStINqFvDXRGVZXOpMzmpuzXdCr1XP9NXZ3grQ3fNH1sm8PXFugWgKbJrpzjX2iWrhCl+XKpjDof8e3ak67wls2VtG23k0BEQ6iF/J26WzkFypRYpTiH+V96tTZeLoU19xSLsxP/njAMxhaA9jw1XMd
*/