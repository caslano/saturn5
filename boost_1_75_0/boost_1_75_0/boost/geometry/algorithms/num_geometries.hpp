// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag_cast
                            <
                                typename tag<Geometry>::type,
                                single_tag,
                                multi_tag
                            >::type
>
struct num_geometries: not_implemented<Tag>
{};


template <typename Geometry>
struct num_geometries<Geometry, single_tag>
    : detail::counting::other_count<1>
{};


template <typename MultiGeometry>
struct num_geometries<MultiGeometry, multi_tag>
{
    static inline std::size_t apply(MultiGeometry const& multi_geometry)
    {
        return boost::size(multi_geometry);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct num_geometries
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_geometries<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_geometries<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_geometries<Geometry>::apply(geometry);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{number of geometries}
\ingroup num_geometries
\details \details_calc{num_geometries, number of geometries}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of geometries}

\qbk{[include reference/algorithms/num_geometries.qbk]}
*/
template <typename Geometry>
inline std::size_t num_geometries(Geometry const& geometry)
{
    return resolve_variant::num_geometries<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP

/* num_geometries.hpp
rrDpzknMZXN2gROT+/+gshVcTyc3iXfKaR817+e/4STAumn0Xvpz8yN0+AU127f14AI2mlr9W829nC3O/lwcdonDXeKwjw7Gu3ZfybVgnOT69rl00XSSkn9OKv72N617+ajbD9Nms3c5+/HSk9Q+s5JONlK75KQCjQddHJM0fszpVrqu3eyxH+ND5lrJvMZ4r6TvZXxy956k+GgRT/AjuvgXCathPul0OvHP9LUvzbRnc5L7Q2a9YWwR8l/ajBzV70Hdr7VE9TufThqp9SyRsMMuLP2bJOytS4pfk5kRuo23G3eSeNxiXsGNH0jvX1u8Ssl280m2C7Lwg8Wy3fYlLt/iK+ji20sgQ13rvED6Fj9X7a8XvsXf4vxq6jtrREryZU8vceM/Xfx6icL/JVPomYf4u9+DvytBW+0vuvo5li46v4h+Fn6xuJ8jgi+7ryRfNvJFF1+2hi6+/kXM0VlOH5IRu3lG2GHERLtOMWM90s9+LslRc0mOmntotuQh7vui0vk9QifPU3v7iwUdR59bepIb7h6pT3nFBXb7+8ROVodeNvNEX4ZJaBBkZYkkK/A7k+M6j81+0PmWuqUKL8R4tNFF/1KMR3Jp8Xicb1hrPDRFG4W1tJg/GqWfjq4Xv0+UHPPLl7rlX7r4rnrHzVPe8Xvjaj5Wej972t3HC3Txa9XHq1P6mC18gkfgE9zidWIB3ivGz/DJ9UwEPacX
*/