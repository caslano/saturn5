
#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename deref<Iterator>::type
        >::type type;
};

}}}

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

/* iter_push_front.hpp
FU4Ymcf2t9CZl9Iz0vgzGDonod6nfUBVQhD8OMu+f9XTRfBJopgpTWnEY7eUB5DCyBsRSarkKiakQl2X0V0LU3JMsfrX/5AWsimWCrB0kKuysZw5q4fyRkuRUxGQAMgpRw2myQy11hcm8tAMms4VB4q5e3tymVGdQhpSASNbX4OwH/hKeBMNVvJFvI02nkUVt2gPp0iHvXvLWrdyUx4jyx6Fsx/dt5Nim9jJMI+ljseNtx5VKIgfrMYokhTxGkuisO4mveB2Jc2+pJIEtOcyhJl/5jb8gK+sRwayb8GRfewrNQMZ+/JcVoDfeJfKOeFOuNlARSC1j8vXaFEW6bLfT96wXdjRuCL3iVeUdqcno+UPgzaqwRgM+u77OyZPxENTXxUIcrh9Tq2ELrrslY2N0AozFYG6t17cym6y+i7epNXrOYh1CD1WMbZvTJ0RETDpUHVO+Tja3vSmbXHyNOHdNs7QSOTqauPgnRoAuO1KMDvpSytMEFhC64zizfFQDDRrDApoDPg8/IuDqCOYVOWcn2Va8ebEx9v9sHUz++HNZhPesUj24nEHxDjKDgIDSiQcTliVjtCfXdyWZqYeOfGdZR5nrlKL1Vl+s5mcEyWZM+lVYweJCY2z2Y/GJ36XyFZF+Xlv9n+H6/C5isD95gTRSPIceJqP+V58oLXD+6cs4Fl3Az0DFjwyd/y+knMjTJGCKnI/gMVr9OVQ6TpM
*/