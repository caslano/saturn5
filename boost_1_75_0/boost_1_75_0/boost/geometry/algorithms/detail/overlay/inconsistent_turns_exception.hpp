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
CG+WcDiw5X6++Zkjyd8cz1kceU5vCTp3NDwhvRUtd+5GvLUC4slq2z2RRaVLRMdzge6Yqef3bhd88ylWnTj5Deb62l2wZNdYaMroNSYnUFC26MusD2HEOoZjS13GdtrW3eDCxDEhM3QlWYk2e1WbjwRzIpP7/so5LulK74JGVXLH8WGsB1Z/kTuDYA/EBJ/2mxaTP27+Vtu9v9AzkNyVMRvEqY68flzU6q1uyPyEcTLYykHzfRBxrr39ahb954tJa1gmFh3UdSOZ4vcz+5b+w7dIn7UsAjfRb+JZea+1Dj3hxA+TEW66VU57ipgr0gnav9Tr2fX68NRRuNTDKu/FoTB8cM4fmHaZz2t3YiGlQjkzxryfYRNshs1YyZDtjGozaiv4kWxYL6PxdGVE4gIoF/NkPWf9VfzdxhiNonWEM4PLJZHWK/7kGJkOK1v0GClRClJ9ilKPsDyUMiyUKHmpjgZOO6qumdmv/LIPUHl4fLooteRd6n5rM3sG3r73ipKdpVKY6PKpB4cr3RYvlioEvlc4XaxAy1uJKe1LqmJXpnYUpC7ZmKnbmF0uVmBoXZx9fEe/0k2hcsKob/lOur3qJDDj1Jd0sy/Ju1jiS7DXtyOlCgLFCh/fK2QWK9S/V4iTKqx0O1npJlXpJlE5Ieh1bg/77kFW8z+1jHg2Xwkydf91syLJjsCdmxgGXm2494MK18MS7vBVul2odANU
*/