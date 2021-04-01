
#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

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

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_range_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos)
    , typename BOOST_MPL_AUX_NA_PARAM(Range)
    >
struct insert_range
    : insert_range_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos,Range >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert_range,(Sequence,Pos,Range))
};

BOOST_MPL_AUX_NA_SPEC(3, insert_range)

}}

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

/* insert_range.hpp
mI7Zk2OCNWag8iT/McvCkcK+L/vWscB1t46b5nuWBJj9+YhdT5a2vhgLuB3cb5fi/9G5vQX62WwlNBqZBUCLzOsNbRi4G7pRyAu5g0eV0IEoOFqw+6yvPhQMP1H6VZ7rTZQ1SEEn4RSzPJ52GIYdUCixa48zWveNzhNlJ25DIcea7InARZixzP0wjBj9xN9Sa1YdfOCqoChZe2KN8CWs0/Uxjxh6SVgmYDPhuT4LzpycER5vOZmbB+U6wYnp+WXkqaGhvz1RLtpE0bzxkYbRJ9+SYddjL4ib+Oz70ZQmjotGV3RK7NohEmztxwKZCerT72iwf8Y4bwuD+Lh9toILfGBIYk05SoFc6nJ2CKmms4GwQw12xCeCmWDCSLlO8V3wxMLW3g3GFWsM6P7WzuEjlBUUPcRF8qUaYfFqSNmIARIaph9VLH5gWYW0FVv6RmPxJy2IXBHLPGEJnAiP4uKKVksJXMa6kz7YnjGskxLzaUk0dWRKe5IQfUneoSKQyjysKA378whg9KtjGzBNTPTXbqtrglmhDp6/f64zlqvtlzwsO3NpRiM0nVxt1Q==
*/