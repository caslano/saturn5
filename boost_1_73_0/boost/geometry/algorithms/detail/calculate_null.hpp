// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct calculate_null
{
    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

/* calculate_null.hpp
4ce6YvmfJ+oyX1BjEs2dY2j63/58S8OcNLLVi+heMJ7OsqM6v9DSMYeVDnsR/x6U6li+F1usnWuwsDLsJRajrYba+aViLnSMCZ8VeMeceB9186w2FHwsHrOYdC6ZKk5znNNYP47gBzTldZwTNObiE5cyh7/M4tK7Aq3BfocH2oep6dJDm25d1rt05dbsOuF7hO7SYc1duCd05ceufH+hvXN7TapY/UvRpyFc68El6gLhNe0x
*/