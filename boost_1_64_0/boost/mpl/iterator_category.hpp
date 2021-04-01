
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {  namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

/* iterator_category.hpp
bpnRNnowDxm03gcF4XIA7VhWSFpsEq6v4CdeQr/L2m2HzQ37QV4lwNpkEWroum9oobvObLet8xBkqCZUeONO2tT3kk2kXGtu0UXVlaV5EYtEmpbTA201sxDgWkiussu995a+twInev+fEP4Ro64BWxErfMdMwNOoGg3OLKDZhyZgsLZidcSca2Fk2XTxDuP1wZuCxUD1znwse2yI27o+BVdzlYfd+ceMZsE6T326Ly473GC1xcgfCk6E43s1kFbDr8tT1AO3c1ABNXPFiQOTWmfYpvcSL6v5wudG9CBMvqyGnX8JblrjyOhu0wCdNz8BWC3LLNeQO/cshiGE9fP/v7ekDXJN3+z0qbLhrYRHv6wqTZ+a+1PSRcjFfM/pid6M1jCJ9/0fwpoLYL9vgtb75knUqpzHOwj5jsFppEc3+Y4HL5pf7xZ+FrmoJ8I8xqtpcimA01z036Fff5ws6ovH4/zVSXhNx6mof3MrEBB+mUXQBZ6t6RiH91IrWzEb04GYyFApREDsPXRByMYGBo6eFQa71Py85hWscQdSqDj5CHw86nxY0gQ26AvBrQ==
*/