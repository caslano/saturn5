// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


struct simplicity_failure_policy
{
    template <validity_failure_type Failure>
    static inline bool apply()
    {
        return Failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data>
    static inline bool apply(Data const&)
    {
        return apply<Failure>();
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    static inline bool apply(Data1 const&, Data2 const&)
    {
        return apply<Failure>();
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

/* failure_policy.hpp
U8V0UAlUU1kWqoSSR5mPsGapC5RVZbaQh8p2kIOWPuicgsKqkhXgH62UmD9gQSwS0RiyBfSsVgbtl/UK507PkUigYCLUMGWzp4UWB/QTlM/iURz+IrhhBBfTJF7cTWmwaqyKWdWq0ot8vZhUyHBiD5vzUsBsJ9YqjabI79M4zSJ/pt4gzyRgBDLpzeNEkbuwnCc7eqhvLq5OPyCeUQOBRx8lkBUaAQvpz8AqpQ1AajIhQqZVc+D5YQu6iZzFT68uL3unQxRrgD4KDol5DKNEdAUg0pk7AEnAPbzcewADZwCN1UIQPWklTsRSDdEmsj0uRH9QBiGubgs5AGT/ThKKUy1ncgY08pMgfGR1o/RQdIflsSA2p5tQ5rA7waGXp6g6xJqAoGC6o3unr9ieWgywOIj8UJNCPdevCVFOFhHrxBl5EIAKlA1NQRMmUJdMqEb8ZFgFNTbxR1g2Nb0FjF1puK9SoUcMzDCHNSXIGsUZVAZLHGUdVY05wjCe0TCJ/EdnzitBJWCCMOHmy5xx2+IQ1ELwTxlPmvnTltIPxVag4ZdFpseVuJdyrlW3xW5q9Ki4bYHDCaYSio/95FHbxOZbQJttdDHovcZsuBgoNQ1NIIDqIriL4qRcDoWoIZq6ibwLfNEypNJazdIa+NXL
*/