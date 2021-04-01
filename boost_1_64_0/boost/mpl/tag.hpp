
#ifndef BOOST_MPL_TAG_HPP_INCLUDED
#define BOOST_MPL_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename T > struct tag_impl
{
    typedef typename T::tag type;
};
}

template< typename T, typename Default = void_ > struct tag
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : if_< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type
{
#else
{
    typedef typename eval_if< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type type;

#endif
};

}}

#endif // BOOST_MPL_TAG_HPP_INCLUDED

/* tag.hpp
q//M3IjM1zThXn+PkbU3VyeEY4eBHsinrQ+RnWJrBBntuOOWkUNp1wH26INvNnGv90Br3Row8AgsjtubMmpfBeei0DfIKlH7H3PgnZu8nf3SRh3bHOH1xIOUAz0OIF4+6IgpEFvHDGLQ5FZ/CDqyw9tgjOTb0SM5znWRDRtBpj9bHbVOd9UKNwIZ3Id5PeSN52VVq1ZRux0Fv3sdHH98+NRssI4Cri+5MPAud+/H3snJq0M7RvJylwi4MaMAatsjtuTe3jxWnAX6lqLQZ1HGT52x6YfjZ9ap/hTJiodnR3HG72Bz1tv2JoOIcrhxcu5iQpDsFM7LvmTbJMHeatqEvW56nxrwL3k6x8b8RXJIb1yg64XCj8ndjFXMe6VPHhmDFTyUyhLNsC9/mdBVv6/6t/RrbvMITdZfvGkPf3CaXWrviPYMk5jEYtG2FR1u2o9ChJpp7eUUqg2gWShYMW2fQn1Nc71AVUnCltU4ZdbG+B0shXD2Pgx1ZAuEhIt/kQ0wJHBC8zxwK7cYGYDC0mmQkaCfDfzNYl98/yhQgCyEi8Wifru7jL+ee1dJDg==
*/