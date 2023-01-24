
#ifndef BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct O1_size_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : Vector::size
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct O1_size_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : mpl::long_<N>
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
kcQw9T0VxkIxc/w9ixCbaeLF0NWf2KI1ExuXBqW2mvV6jqUZoIiNy8DXmfrrQ8mvM/G1RX+9A16DmYmcFVGsttsEkxHmPRTKzov+gfQoyN9SdP+jYHdTrK30AToR3/6IsVtdmrECLIMLP1tNepPXUwmU44DcMin3+E3ZQuSEEi7AyguYOzofmBdkDAZ2NbLArtx3oZiUuxP+BeabYigbOkBxXT2ZkxoX5MGMAJ0zzhqojYdmLfQWu0IzSqVJdm/6DhWyrVYdni8AtsRMIrncA9lC4i0AqxFkUOjVZEQY+4DSJvGYcXBjZus+i2Cs97dkPbAVy9AZalnPlgw+q8HnntgUCy9+I3m/2LTEC10cirFErtAp+uChc2g/Lx2k0pOcXlqg0IhwXN7WHjoERaxQYWqhgq1ZeqF+HMyWTsBsYWD258UxUu0Ym0ghrYTOgtmb22SgdPVLeAyf9eWfxbUSTPGv0iOpufR8WMlkUjPJWN5TxyTmQGRwuPbh12x+TefXH+9k1yP8mriTfXd3HUnaj/nP9/nrd/j1TX59lV838evz/LqeXx/j1/vvNOi6GTMvZzGBKGp+WMFFjbfNh5IblN2HAQzweRKQ48FYi8gWtCAEW82VNNd1bGD+cPnUP6PQC1kjw4TWSyngbIEM+PPKUGY9bTnZrdxXxVUfbnlFHXrVXlEKyGSMnsu+OcQcs95D8Nn1e7Tl9X5Q7hAi
*/