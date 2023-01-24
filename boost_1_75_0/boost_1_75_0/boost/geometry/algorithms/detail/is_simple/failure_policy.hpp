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
MVusdCeJKixi+cK7jG4VoZstw/zogfnRjUZcttJt3qLb/0FkA4SHtiTOcbaYFZP0rMc242PU4vCC5J1OPnYS47iQLz1BzZPLgMGsFXQ/HP1g7/VsMc3zFyBh28rm+StbrPP8Tiwdw8tRI87lvEgx8CL/h7hvj4+quhbes+fkcHI4GU6GyTAzDEMeQzqmQxrikIbcGCchYEgDxhjSyEVIQhITGpJxEhAocgMX/dAPvUiRAkUaECmg0JiiolUaEBSs2ohoxVeDxbdYpKjUq/Zb+3HmnJlM7OOfb36/PWvvc/bZ78daa6+19tWAi+QPvf/hXm5vqBg8S8CtuzdyD5NmCT+WLDBOrwv0NoViPIleorPyXn1mvXGFE3040jsZi8ulDXKRss7iVddaP1VPAZpfCWMiBzVL5EIAD13Ehzv7OX0vp2FInc9C4Ete5w/1rChPK1GUdgi4F7XjXBThZ7mRCmka+VneTRynnASeVnD/tSlyZ9AFo2qbZvqf3LcYpY9g0tjE9bTKN2/SV77dy53ovJx9WCiBxaRU3qp4sUuusBxUC6wbqHxjvnSKKMwTS8DsjkVWd3LGCGW1EvsgdKZz/Fcr61vgSfx5Bsr8OS1r/HsJi7kWb712L+EOLPB7BqGYjp/riC65VfAzNacVR870NddmvEywjapaeYUS7b5A2q7DnGev+DmX9bgDPH3gTvw8QoeZhupFXDDoRQyy
*/