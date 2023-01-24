
#ifndef BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct erase_key_impl
{
    template< typename Sequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, erase_key_impl)

}}

#endif // BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
g+2O4mU7fXGP2+EPgIp78V+/gRnFkq9k/zYl02z7rcj/mt+pQvG/TAnuf2O4Nh7SHh6c1v+uiLI/zjNzXwQDo79JH0jKdRZvstrY6nY5Usm7aIXlsRwDhGeVnW4UbUQvJ7+Nqxu4hnsNypdbsukQCicdjv/80/PYmDGlOBuOzaxekRNFwAfg4trp0YgFMtSTRiVxtCN/w3eF8aiHpCUC/F91ltFkhVueDJ33hDfNdLW1tJHb7ErsIWUjnYzOe4bFHiqZS018THJ33nXCG2pDcKv8ZVCqI/atNSKog0jycNskghMuMpr3g95T3/2zqv+r4tIFQpjw9BCbjJRznq7d1BDUzUvhu+Ka+ASV5f6dp97YcUuBWnxAIh05SjmkUvtRHT5JOyeqrOFvD52hjDQhLoGSgU0MJ2nZo8i/WGFW+PwWHRbq+lgqqQ1MuvxHd03GvHbp5yP6jUfzmVor3MRFc5A7qSu9hWXFas66JjZCK5X3zszPFKnsgQr4r9ySSq6mKD7F4O3brKZ90szhzIQIpZLXTGZjnOHS98h1+5XEM5Rm5zoWaUED87o7f5l4t8bBT/5h7vd9t6Vqr0f7gp9gL1a6SdrZm6H6A5c/R4kZnhKohbHCrnLf821/eMUod5r9YtExiJC6sG/LumqBd9t+kh+C30Z3BVtfWf/D1o2/8CBn5GtG8ylH4m7h+1Mm1JFBDGa3KVTtx1KF3eq5
*/