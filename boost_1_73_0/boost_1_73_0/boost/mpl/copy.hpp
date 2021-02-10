
#ifndef BOOST_MPL_COPY_HPP_INCLUDED
#define BOOST_MPL_COPY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Inserter
    >
struct copy_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

template<
      typename Sequence
    , typename Inserter
    >
struct reverse_copy_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(2, copy)

}}

#endif // BOOST_MPL_COPY_HPP_INCLUDED

/* copy.hpp
aP/EJgPOyE4n19k6ypOrvDUda3Cle0CE0HudsSbGLdH/wQlE51owAfaNigRgFxCMDRFVBa6Gc73z7TkTHW3GWvOa3lzfUIIBC6s2VEFJtYT8ebV8eLorXlbzdVk8recvefFjfjouV4Us8mJJl4dbQrvNRtlqMJUlydmiWMuHMjvr6lUWK5kcxT6ItD0+qG/Ab/SmPkBfclVH9BAbhK6z0KgAr4gWxqFxcczEe8+lFFvvotOde2ou9BJwbFA6YgsXYgb/ORmx71rjlkIXycWIjcjJKY9A753XrqJHcYp8giL50E1OP+4vUEsDBAoAAAAIAC1nSlJERh6ykwEAAHsCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUzNlVUBQABtkgkYGVSYWvbMBD9Lsh/OBJKoSyTvLKNGS0wPK/pltQh9va1qPJ5FnWkICkN+fc721kzGBjZT/d07+mdZcQQtQq4YNLYxtHrGU9H5+uwYMuq2gwL3OUVk/xSkXwksxmbQYn+Bf08mBqZ9LjvTkSoVVRgnW5RP3+enjBMx348eSvgnRBQ/IBwDLpzAdlKhThfu9o0BusUqvbwBkQC35WF5NNHAUKk9NwKuFtXLHM2oo3zFdrfsU1BMLLTy/W2zvLkKutM
*/