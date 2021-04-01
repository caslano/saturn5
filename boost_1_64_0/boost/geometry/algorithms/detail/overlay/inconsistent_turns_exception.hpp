// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INCONSISTENT_TURNS_EXCEPTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INCONSISTENT_TURNS_EXCEPTION_HPP

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
#include <boost/geometry/core/exception.hpp>

namespace boost { namespace geometry
{

class inconsistent_turns_exception : public geometry::exception
{
public:

    inline inconsistent_turns_exception() {}

    virtual ~inconsistent_turns_exception() throw()
    {}

    virtual char const* what() const throw()
    {
        return "Boost.Geometry Inconsistent Turns exception";
    }
};

}} // boost::geometry

#endif // BOOST_GEOMETRY_OVERLAY_NO_THROW

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INCONSISTENT_TURNS_EXCEPTION_HPP

/* inconsistent_turns_exception.hpp
9K7jrGYz+ThN24nwRYKX3DnMepAQOYMrJA6T217KwVIlQtgn3iPT3KsHjpaC6U1cwRWvt442olOFoKa2/JqMeZJV42g0Z1dIwnZsmKrDTLqH8M/f91KhQw+ubMdBXNRAGNsPgm9kzH7ls1r+5mWCQNJG4Ti2kjS+Dg7zPu39yel6xC9ecvlfuUrK6snQBSNAkUkrPFE/eB1A6eH6QxtRgonkwjwDIlIT3r4jo3AvCNQqPmsunfIcWLeM/9yPMG3QYkokPqTaJMANrNNHPa2WboHTIrvnGt3SUWykPYAN3Peo4cLx0KBA0BPwDyqf0YfuKH5xB1kdFteoYkDSxg+QfQIhS5xyeHaG/7nwGRd3BRmYy2P2cqo/+psROe2U2lCvua834K8pOD8J4gBuHO+PY7f72KiM0Nb5nqKaB7DUd5rAAU7vOk9fMGgu/A16LEqN0i2nQdtVLNPMhw1YQtUMyou9VFhMQjaCPHOW+NfIRj3LXITkTkUA/EtZ1C0gbW/q1+PGO+0AlE8eit4y7n0fM3Z1fo5iMX/dqsfvdvQeSnFGPZhboGGboJQ2iw==
*/