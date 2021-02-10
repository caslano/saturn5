// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_upper_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_upper_bound
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_upper_bound.hpp
XyTrrX1u7bD3A8J/vFHya3szfLIodBo6a0lA8v9E1C1ms1NxOvAJttvrEGQbaTOvy+7aeZRYsgIrBGUKhudHx4MBuCN2ae6D3appmZ4VFDneu9eM3zD9SwQ7Pd69u1BrGDF31X9jBXjhoNo3tg5reStl2bi24P7e9K4Hw7INZUFbNhi3amihGzxxO3mmH/t1Zfk28e2FX3s0F36XR/Xfl5pnm6gP/+XWsd04QGmLxgkjt5Y8cvEGroK5y45WzdtxA1DrwXk71NPdZhBUUR8d49IWed0jNNuMRvqCcPACjj3XLDDUm5u4gb2UvdZwcNFqB669VPRPhZ9QSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAABcACQBjdXJsLW1hc3Rlci90ZXN0cy91bml0L1VUBQABtkgkYFBLAwQKAAAACAAtZ0pS9JHunRIAAAAVAAAAIQAJAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvLmdpdGlnbm9yZVVUBQABtkgkYNMvzcssMYw2NouNNtC1hBBcAFBLAwQKAAAACAAtZ0pSfRGcGJ4DAABgCAAAJQAJAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvQ01ha2VMaXN0cy50eHRVVAUAAbZIJGCtVG1v4jgQ/p5fMaL7AU5c
*/