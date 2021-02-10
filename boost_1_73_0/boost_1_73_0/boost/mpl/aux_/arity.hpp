
#ifndef BOOST_MPL_AUX_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/dtp.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)

#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

// agurt, 15/mar/02: it's possible to implement the template so that it will 
// "just work" and do not require any specialization, but not on the compilers
// that require the arity workaround in the first place
template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct arity
{
    BOOST_STATIC_CONSTANT(int, value = N);
};

}}}

#endif // BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif // BOOST_MPL_AUX_ARITY_HPP_INCLUDED

/* arity.hpp
JGDNVF1r2zAUfdevuLjk0VVatj0YJy9ZSwuDZnG2PQbFvo5FZMtIcrrs1+9eO17WUtYNNhgYfd2jc7+OlQb0IVce5yLVTWlp2uPx0brCz8X6dr3sB1itPorb+w83IuOjbLEUdWeCbp0NNrdGpPJ8K5UDkbgQF5ChO6CLvS5QpA5bcyRAoYKCxuYV5vtZdEQfkS+KA3pDqQ2K0joIZWiB4yNKtjD1iaLnXhiNTThx5/2GIL73OBd8W3geUjmeQdqoGuc/coLSGmMfsYDtETg1cBicxoMyT0yc+lPs4mdoqLABtVO6Afocki+PQNVARy7l4DPNbV2rpgDbBm2bWdTYWDe56Qqk9OOYCgh558xmyGTD+zhuu+0Lhks6hriDyafsZpX0hUqknNw9ZOv7ZTLh9JYPq7WU19PpG/DPzFl2x1aeN8sv76WxO8llZvBl+Br6DtAFY3NlKuvDhPN/Gerzf0f9p2G/UoaYyu2RKklqkadmUFs4IuAWzaLnjCzLSnugL4zy7JXpucXU+FH/nhiZhxU6CrGX6Gd0ujwOulZlQMdaGcgq5WGLJJzIVzZEIj30WKIYWefCtrktMIErUfezzQMGEbz+Rpup2Jr9sHx7dS2CrtF2IYF3gkPhjBLoM/9bNKk8R5b6UBDslf/2
*/