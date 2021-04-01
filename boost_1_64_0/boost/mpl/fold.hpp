
#ifndef BOOST_MPL_FOLD_HPP_INCLUDED
#define BOOST_MPL_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/aux_/fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct fold
{
    typedef typename aux::fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, fold)

}}

#endif // BOOST_MPL_FOLD_HPP_INCLUDED

/* fold.hpp
rA+BDwDDvww5rHSNxdyU/wSFlxXKVn2Te/QG6PXIOhvSFzGrZU44+ynfCDNG3EOWaRunh8Uu/zEl4ykxl0bauM1Ys9/61CrnOQfEj4ZjzoI5bornwJb5ZYwQfZqoYXrA/B1aHwocmrq3dDnRWx6CCe2AWW/wcO/TQ6A+IAbWcUmvR6v/7lvivc8qyfwhaOoccWuNGcEXNWWK5urtY7pyo4KSoMz9rF7PD3C+w9IlzJaceL5insWpkX4lxp/nhgAazAf+Vuc7m2j6fV3JwswZAH6N15zW39739/ieVOVBYEEi8IxvbG8nQ57Y74Y+golwL7kw7Za1HBSmCA7CukenSJ7SYUNPRda0+VstnoU+/Gp/r+sTF9eUzxKxMM9hSZfIlFe3oaH2x3q9J8ZfqZg+5PvJjmZJUaA07kNOGRXkpjURWxlkLwNc/TbslxSf8GPlVyVOfNY0eoFQnANyg1C3tXZKd+iVjdzCD+TMnGdBZ4/rSKybU77UGIKkJpCcQtHD0xHe9JoxOTonM661GF9S3WJj1TpFY/rEf5WfLC9ZnARoZnOF4lQ0bq1esA==
*/