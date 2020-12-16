// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_POINT_TRAITS_HPP
#define BOOST_GRAPH_POINT_TRAITS_HPP

namespace boost
{
namespace graph
{

    template < typename Point > struct point_traits
    {
        // The type of each component of the point
        typedef typename Point::component_type component_type;

        // The number of dimensions in the point
        static std::size_t dimensions(const Point& point);
    };

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_POINT_TRAITS_HPP

/* point_traits.hpp
dsfvMQEfYG8n837cBz1Msn+5/w7AEHwZO+JCjMHFmIPLcRa+gUW4AW/iZnyM76CLA9c39MDt6Ik70B93YgAWYlWVH6zyG+IubV5wN0bjB9gfP8RkB/Ny5eESnImv4au4FF/HAbgVD+CHyPzJ7dNKqO9YxOZquzthA7Xdm5jMr5uaYS0MxcbYQp2HdgVYvqNQfneibM/b02JLgLn9x4zTFT/BBDyCyXgUM/BTHIPH1e8XX6jfL07gPDyDy7C3s8gfqG0XzMa+OBtTcCGm4hJMx404FLfgMCzC4XgUR2MxZuFpHIPnMQcv4gT8ESfiTZyCzszXVPTF2fgMckzJ7TEAu+FAjMJFmIKLMQOX4ExcgQtwJS7E1bgEWR+5XTKwCH/GL/CKh8j/Bn/Aayp9C6+iK/N7DQPxJ2yJN7Ej3sI4vIvJeA8z8T7m4Z9xDv6Mb+Iv+Bk+xlP4BEtQlOHXEnTEh+iEJnYMF/RDV6yOblgT3bEPTnNmXJyJ6TgYx2AyjsNN+CJu1uYFt2ARvoOOzhyPjO+D20nXwR3YHHdia9yK4bgNu+PvMRV34XjcjS/gXlyM+3At7sd38CM8hAfxHh7GX/AodnZh/8NULNb6wy+1/vAYzsZPte2Ip/ASfo1OrryPgJXxPFbD09gQz2BT/A7DsQT74x8wCa/gVLyKn+I1LMYfsZYbv/djZ7yFc/E2LsTruAZ/wrV4F+/gz+jgznZFV7yHwbhFmy98jAn4BFNRuIj8YWjCieiAL6ILTkFXXINuWIQeeEyVF2MZPI2e+C2WxR+wPD7ACljeQwg/9MfK2BYDcDTWxokYhHOwLr6m0suwHq7G+rhB5W/DhngKm+BFDEXtvdyWOAjbYD4+h46e5nQtbI8tsQN2xy6YjeFafYzAqRiJK7A7Fqjybar+EYzH05iA32JvvIJ98KEqd+XE6YUBWA6rYw8MxZ7YHfvjIByA2ThQGx8H4wpMwh2YjJ9iCl7CVPwV07T59eI8h3VwBLbAURiN2TgSx2n94gRtXrGPK68jsC8WYSJWLMf7mlgbtXQjlZ6M/XEhDsDXVXqFSh/FgXgXU9DkzfKhN6ZhOqZjnkpPVunPcSiW4DC8ptI/qnRlH87b2BVHYzxmYTJm43s4Bg+p9OcqXc2X8zmGYC62VunnVDoD8/A1HI9v4kT8BCdp/aj0GXwBv8XJ+ANOxcr8Yj4dQ3AGTsOZ+KpKr1Lpn3AWPsHZ6FbBnPZALd0K52A6zsOxOF/rB1/BAlyEhfgqOlfkuoIVUEtXU+nRuATz8TWcrdJzVXo3LsUruBzv4AoU2v1c2BtXYZpKj1bpfbgai3ENfq3S36i0eyUhCrAFvomdcR3G4npcjxtwp0rvU2kvf35Pwxq4CeupdLBK98PNOAO3avOB27AAC/EevotOlc1pL9TSg3E7ZuMOnKDSv1PpzbgTz+AHeAk/xJu4B8MDuG5gAmrpwSq9FfdhEe7Hoyr9qUr/jEVY5xle72Az/AQ74mFcgkdwnUpvVenHeBS9q3B9wcqopZ9R6Uj8FMdhMU7FE7gQv8Tv8STeVenHKh1dlesTJuNpzFDpkSr9Op7BT/AcnsRvsATPY2g1PsaNXVBLR6v0avwWC/E73K3SH6r0NSxBv+rc04a18AqG4A84Ha/hYpVerdJ/wj+iqMF1D91RS5dR6dZ4HYfiDczFm5iPt/A03sHLKv0nlW7/LNdFjMV72E+lB6j0bLyP7+PPeBB/wWL8FQNr8nslNkct3V6lF+BjLMAnuFml31bpr1G48XqfF8xOWB6dsQa64Fh0w2kqvUClv0V3vIke+LNK/6rS9WoLUQb7oBemYjnMRm/8GH3xlEp/q9KNArkeY0c=
*/