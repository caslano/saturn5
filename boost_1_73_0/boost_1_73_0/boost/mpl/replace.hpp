
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
vQEpcisWU9pc37ebaRNMd8vu1tJ/7+TDVvFR8CXZyc6cc+bMRAbyQStPGcjarC2/Xul4sK70GUyLYt498N9DARNrApkQL5TZECzI77cEa9s09tBYrUJtDUhxrpaiB4RLXJJ7Ixf7uiSQjnbNka9LFVTPIZLrBG/GCeZP6A9+ZfdGE8wG0BRFcnd3op+R2YQqxRuA/IlJepgOLfkE92c8buHaMkO6x9GN9fQNKLn92lqKqyO7grfjGOBeh71qUPcJAx3z9IS6Iv36sx5+RfCgk6PBfJ7JpKlbhH4mugvYRt9NKoMqhB2nf4QojdpSdloGPNShQtftACpT8rGsHcvmTNGnotR2u+W7HiwVYjTNl8XjPB21KPN8UbSeYDxh4RjPmO1UwMdBEAt9IVevj9j2gWodyGGoCNu9xUp5XBEZvPCVDRcg37pcBtg5G6y2TQat2o7ow+kIptaHFL/JieCznX/Zzgj+swPx/Ya18DT2rhGjl4fF8jF/jthpTTv+fCWuIoh+jUeKc29SnBoW5x/5HVBLAwQKAAAACAAtZ0pSf79x5soBAADFAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE4OVVUBQABtkgkYL1TwWrjMBC9C/wPQ0vY3YJX8ZrArtEa
*/