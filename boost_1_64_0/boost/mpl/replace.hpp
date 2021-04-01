
#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct replace_impl
    : replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct reverse_replace_impl
    : reverse_replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED

/* replace.hpp
50XpJAGCf5RQuZTtXM2eWewPTKuXHv3aIMkaOpw6len5FrLunq1dKBvtFS/nI72DVnzdtKrwxlggvrGpWh8In38HieKHsFoyjBvToz3X5Ptq20gcW4s82gHtl4BNJjErmTnsM/2oFxrLS0Vcf2TFuQ98tVTf/wh7FC9dZwj636vgCSx46mpap61gL0rUyXrcgDEX/XveNZ/N5yMlMd6zM6l06VaBfT5LFga25Qp+JScCU2MSpaH639FXdKw2bkusQITU0Bf14xntuQXKdzztG9oSiq03+uAtG8BoXvnRgVkwsWW5P2wJf0Z9dVnP9Yf1VjOfMnpwpVaM0kqpwrIZchLCkKqNALc+ppdoERT5xGJ2wBoQhPXPJgOSTquO0uvirAK50ankH+VTFtr1XN1QDj5wtLJ9R4rT6R85URrvKMRzvY8qkI5vMn0ooCvg1WnlJ7b7bFTtbXTolSdQHXHbcoY4tfq7pbEWV8GviB8kQXy/qFqDLAyAX0nx1C7rFMXFqbuXhFSWR5v/cB2coqwVii4io5tSihAj6hY606P3aUZc2erKihP14zN98Q==
*/