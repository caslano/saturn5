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
gkSuqgL+OQBvMJnF15NeixcnVHelsfnVEqxjDpvIOl1aX3VPwKZNcwJQ1LlWEk4/hdPLaRjGPa/knglHGha67h2hcM0kLA3nfkMUBc8EapMrYAtsrYOnkIVhcytFkNjaGwaT4JdoFMW3vTaOYBrHo9mGcDO5nCLAE6kOjNmVSnOjla4sWq3KpWFYVnKvsYBDTp0/m40GKPaUR0dFJZ2gIeXY1XJ1vOVYcBNfheM4GgZxuPFkdH0ZjdtVNItbr8NROGyX78N4eLW7St5H42C0oQWTSYiDsbvc45mFwXRLDZrHGWuXwSzeOiBOQPE7HLGKIBQD+YalYaUv9Bk1eT3VvjdxmCssAy49cwOxQ5oKjsntQyBlzZkxx3CTOQ8ssJXf19oIrggQiso6mFNreIsJ8VD2S6MRqrBAGceGuUcAqJGcoWlSSfqQIWdNT27sk2NpztQSlc+5u+e8dtCJgtv9Mtd+URx9iroJzTtPo+FHvSwTZ5iyCwLA5uOMNnNm4KRA1J/rh7OdXH6siRQHQvOmaWuJSmR3TIpMuNXZRuImuvgUjKIL7GWSSnOe/kU56RTfMrY2iLDIlpzUkPiCuzTfFioE4ve2kyQUEY2MUAxA/iKq++8uFbZO2Vmn3Rm2b3Q97hSkkxSHvltwguMa
*/