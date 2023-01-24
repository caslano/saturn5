
#ifndef BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_iter_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

/* reverse_iter_fold_impl.hpp
C7Q9baYC7LYO1eLKBODTgFswQVPgINBSILig9NAETnWv7snv7FmJgyT+4f+JPXhWNk8Fu2aiu8nmNNsiue4hYfsEm/VZuhiY2+XVmGSOwXBBC6D94a/FaUgl5WPXuUE/MY0jQhALNEYM5w/YfsCa8bMjCXgjirjRVVPo6anfKATkBBqGDS8nS/31/M4wN0lJuh3zj16O8rIRCl/IRF0lQB01zo2NYaJCNaAa9i/lB84aN8E/7xDj12XTTWP4qNxnUSy/Plxu5dYz/fr0LsQgIzvFKg3uWMkssZJGXxuZwIKmujwMc61b5J1DB/o2HcyjyPw+vdvw5hsBfqnzNfaGR/Tc6KrZLB0oLgxIA7Qp/npzEO4Xz6MqB5sfS0kioOMGhWnW+IXIHTdcxPoG/fKKBXf304ky9AhGPlxNcjzDjx+Wnenrbn+XDlrwu72ugcolzKf0wDwNXkjicRcfD3+Ez6F2Ko2jfzt/r34/zP0ykuQIylf6zEMddqLmmZxa5WSz4ZX/vHR1Gkdv7uzuY6LhoeKeODE1Oy88NTs7v7JiOzKKsVn3+J514q/i/Jy+0NLsRcbuLTyVZKOreAwU3jGoK1fMlexxmLtmKrnUTLU05m2LWak+uKzXQkhr7qlULYcZbm9jDB0cHDw8PIpd1X1AsqnUajJSAm0M70I+vct7KaS57do4Lqd3UxRzOTM1VI8rphKp1E5eqVJLZaAG
*/