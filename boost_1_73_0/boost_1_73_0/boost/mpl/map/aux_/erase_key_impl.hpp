
#ifndef BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/map/aux_/has_key_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Key
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::map_tag>::apply<Map,Key>
            , eval_if< 
                  is_same< Key,typename Map::key_ > 
                , base<Map>
                , identity< m_mask<Key,Map> >
                >
            , identity<Map>
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
WylopWx9BvdatvjcwNGG9YzYLZY611nO7YP/AFBLAwQKAAAACAAtZ0pSiseSqzcBAADtAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgxNFVUBQABtkgkYFWR0WvCMBDG3wP+D4cibg8S3RwMCYWulFmma2fj2B5je2JZ20gSnf73pqlT9pS747vv+3FhBrXJhEaPsKLeSPv84OlXqlx7JFr4CQlKFAo4Hg0JZmHwRoJVyuPFMvxYhSknjN70jLYWpEd6kKI6oBrqIkfCFO7KUyO4FE4RlAXW5qLIXGMl2u15pKjEzi78tcBqUWHLBA4EKlGUa3mEu39E91ZKWy2wTFaVqPPWbUppfxanPEqm/cYmiZecPo8nMNzD3uZMNWYKDQy/YOASBjb/6mDLC6KD/0RVbE6QCyNAbAwqMFuE5pqwFRrWiDV09VaaLmEHp7UWOyWNzGTpEX80GkPgJ/5LNI/4d6cZPMA8fo3eHQu0LG7+CGk4DwMOltUNJu0BXP3ULMUr3rGAN3tGr5n09sNnUEsDBAoAAAAIAC1nSlKnzQFUgQEAAJ8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODE1VVQFAAG2SCRghVJrS8MwFP0e8D9cHLJN
*/