
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
ViHu6d/RH6B3P4WdBYguUxw+e5DbzSqe7Tgvn1rC9pdZvUld4qM5KAVZhjrXrpViUQt5lVXp15/e6gm58Zyy3T9WJWixs/qK1zT3g71+2cP1AFapyfT7ieTfgJPpZFY20TMuFrRLSC+YbmO/kXbIb8Gt/j2lnnqe+8Kj6V4rslil4KxogCC4CincMzcwH3XwTAbF34lym9Ad0HjKs4vJdcLEaEsV3OCbuDmp+Lzy+0zfEgNte8K+owmGnd3J49w+OdRJSPG740Gh5KekdBofSKPvnZvv4v00BQxcbaypRv5tJfpmUL5ljBsS5rQeXX7oA9rQqTB51mxZcUsYk7mCLd4ned1lkx1E1/kZV/nbysInmxhP3GSBEVNbIlwpn5ln6ZlQMfviu8y6RLKQTmge2Wlx50k1tLit7g5D6dyeOWGLWWW+ihPcuBPHCu3UjDcvrIaEIadUj4Htx0+O5/134raPpjWP8Wd+hTaelxMbUOs/28a+Qnd/QLW6XZpxxsLY34A2H4K+mp3oAUza4s+JBXvSFNtKopQmz4W9pDXcxhicoq9h4YrY041s/w==
*/