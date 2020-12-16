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
czDMybA8hrkYVsIwN8NKGVYGJsaVTcqYikmktPsW3lJmZZjdlGFOBCb0Fok5mGibxG47YqGsmmE1DKtlWB3DdjGsnmENDGtkWBPDmilTyqiF5Ge1Mqd1hfvstiqshGFuhpUyrIxh5QyrYFglw6oYVs2wGobVMqyOYbsYVs+wBoY1MqyJYc0Ma2FYK8PaGNbOsBMM62BYJ8O0CHNmFcyz9qu0lVpidyPsKKtj2C6G1TOsgWGNDGtiWDPDWhjWyrA2hrUz7ATDOhjWyTAt0pxZGWZnmINhToblMczFsBKGuRlWyrAyhpUzrIJhlQyrYlg1w2oYVsuwOobtYlg9wxoY1siwJoY1M6yFYa0Ma2NYO8NOMKyDYZ0MAzBlVobZGeZgmJNheQxzMayEYW6GlTKsjGHlDKtgWCXDqhhWzbAahtUyrI5huxhWz7AGhjUyrIlhzQxrYVirKcPcBkDMGa5V1hzro8Q9Si51PqE9SZi65thCWIVyDnSEMPUcqIMw9XwsLNrH1Lm+gzA1DQWELVSYO5pZF2ZYGcPKGVbBsEqGVTGsmmE1DKtlWB3DdjGsnmENDGtkWJPKaHsAM1v3dsWYryeXMMzNsFKGlTGsnGEVDKsEM1v3bolh1qUY1sawdoadYFgHwzoZptmYdSmG2RnmYJiTYXkMczGshGFuhpUyrIxh5QyrYFglw6oYVs2wGobVMqyOYbsYVs+wBoY1MqyJYc0Ma2FYK8PaGNbOsBMM62BYJ8O0WKb9MczOMAfDnAzLY5iLYSUMczOslGFlDCtnWAXDKhlWxbBqhtUwrJZhdYJ1s+7tjjNf2y5lWJkpw5xIMLLuLdumYN2tCzOsmWEtDGtlWBvD2hl2gmEdDOtkmBZvxnAuKlg3695VxG6rwqoZVsOwWobVMWwXw+oZ1sCwRoY1MayZYS0Ma2VYG8PaGXaCYR0M62SYZjdnVobZGeZgmJNheQxzMayEYW6GldrN171b7Mx5McPaGNbOsBMM62BYJ8O0BHNmZZidYQ6GORmWxzAXw0oY5mZYKcPKGFbOsAqGVTKsimHVDKthWC3D6hi2i2H1DGtgWCPDmhjWzLAWhrUyrI1h7Qw7wbAOhnUyTEtk2h/D7AxzMMzJsDyGuRhWwjA3w0oZVsawcoZVMKySYVUMq2ZYDcNqGVbHsF0Mq2dYA8MaGdbEsGaGtTCslWFtDGtn2AmGdTCsk2FaEtP+GGanTJ3bCKaue4O1g8V57ZzqXEP7BMxuwr5g7GzJWO7y6jnlHEXGAuYw7G5QmIthpWB2E1bO2FWBpZqwm8ASTdguhu0GSzZhzzPsEOPzOMP+waQ9IsXczgFmFksBYzcRjOYZrWdzweKMslXXoReDiThrFLaW6KnsRrAsE/YAw5rBckzYnxg7T+JyTVhuqqy7ch1ajjlgaYbdtxQ2AyzDhC0HiyOM5vV6oqeuF9Skynr91bVDhjWC2U1YM4lFZQcZdgQs0YR9wuh9wcSZOsDcbijDihk2DcwsDXPBbCasAizVhG0ESzZh3wMzy5d7GJ9PMHE2M+wgk/ajDPuEiSXMYZ4vdjCz9OWAmemNATPTKwVLM2GLGbaF8XkbE8sDjF0To3cIzKzufsiwkIH4rp4Jywczs5sMZhZnOZjNhC0FM6svaxlWAxZtVq8HMvUazG7C9jDsOcbnQSbOI2DJJqwDzKz8ogHM7LLAMkzYBLAss3JgfK5kWA2jdw9j1whmlmcvgpnVlzYwMU5vUtZbPwAT5b5dYR0M+xfDwtLNWRzDHAzLYVgBw4oZ5gZzmLByMCdl9JwLLNHIz2pl7v09MNE2b1TYHSQWldUzbDfDnmTY8wxrYdghhh1h2AdM2v/G2J0=
*/