// Boost.Geometry

// Copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP


#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/impl/pj_datums.hpp>
#include <boost/geometry/srs/projections/impl/pj_ellps.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/par_data.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/tuples.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/variant/variant.hpp>
#include <boost/type_traits/is_same.hpp>

#include <string>
#include <vector>

namespace boost { namespace geometry { namespace srs
{

namespace spar
{

// Static parameters holder

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX \
typename P0, typename P1, typename P2, typename P3, typename P4, \
typename P5, typename P6, typename P7, typename P8, typename P9, \
typename P10, typename P11, typename P12, typename P13, typename P14

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX \
P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
struct map_params_to_cons
{
  typedef boost::tuples::cons
    <
        P0,
        typename map_params_to_cons
            <
                P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,
                boost::tuples::null_type
            >::type
    > type;
};

template <>
struct map_params_to_cons
<
    boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type,
    boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type,
    boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type, boost::tuples::null_type
>
{
  typedef boost::tuples::null_type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template
<
    // null_type -> void?
    typename P0 = boost::tuples::null_type,
    typename P1 = boost::tuples::null_type,
    typename P2 = boost::tuples::null_type,
    typename P3 = boost::tuples::null_type,
    typename P4 = boost::tuples::null_type,
    typename P5 = boost::tuples::null_type,
    typename P6 = boost::tuples::null_type,
    typename P7 = boost::tuples::null_type,
    typename P8 = boost::tuples::null_type,
    typename P9 = boost::tuples::null_type,
    typename P10 = boost::tuples::null_type,
    typename P11 = boost::tuples::null_type,
    typename P12 = boost::tuples::null_type,
    typename P13 = boost::tuples::null_type,
    typename P14 = boost::tuples::null_type
>
struct parameters
    : detail::map_params_to_cons<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>::type
{
private:
    typedef typename detail::map_params_to_cons<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>::type base_type;
    
public:
    typedef typename base_type::tail_type tail_type;

    parameters()
        : base_type()
    {}

    explicit parameters(P0 const& p0)
        : base_type(p0, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1)
        : base_type(p0, p1, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2)
        : base_type(p0, p1, p2, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3)
        : base_type(p0, p1, p2, p3, cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4)
        : base_type(p0, p1, p2, p3, p4, cnull(), cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5)
        : base_type(p0, p1, p2, p3, p4, p5, cnull(), cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6)
        : base_type(p0, p1, p2, p3, p4, p5, p6, cnull(), cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7)
        : base_type(p0, p1, p2, p3, p4, p5, p6, p7, cnull(), cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8)
        : base_type(p0, p1, p2, p3, p4, p5, p6, p7, p8, cnull())
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9)
        : base_type(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9, P10 const& p10)
        : base_type(p0,
            tail_type(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10))
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9, P10 const& p10, P11 const& p11)
        : base_type(p0,
            tail_type(p1,
                typename tail_type::tail_type(p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)))
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9, P10 const& p10, P11 const& p11, P12 const& p12)
        : base_type(p0,
            tail_type(p1,
                typename tail_type::tail_type(p2,
                    typename tail_type::tail_type::tail_type(p3, p4, p5, p6, p7, p8, p9, p10, p11, p12))))
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9, P10 const& p10, P11 const& p11, P12 const& p12, P13 const& p13)
        : base_type(p0,
            tail_type(p1,
                typename tail_type::tail_type(p2,
                    typename tail_type::tail_type::tail_type(p3,
                        typename tail_type::tail_type::tail_type::tail_type(p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)))))
    {}

    parameters(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9, P10 const& p10, P11 const& p11, P12 const& p12, P13 const& p13, P14 const& p14)
        : base_type(p0,
            tail_type(p1,
                typename tail_type::tail_type(p2,
                    typename tail_type::tail_type::tail_type(p3,
                        typename tail_type::tail_type::tail_type::tail_type(p4,
                            typename tail_type::tail_type::tail_type::tail_type::tail_type(p5, p6, p7, p8, p9, p10, p11, p12, p13, p14))))))
    {}

private:
    static inline const boost::tuples::null_type cnull()
    {
        return boost::tuples::null_type();
    }
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Parameters, typename Parameter>
struct add_parameter
{
    BOOST_MPL_ASSERT_MSG((false), INVALID_ARGUMENT, (Parameters));
};

// NOTE: parameters has to be convertible to tuples::cons
template <BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename Parameter>
struct add_parameter<spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>, Parameter>
    : geometry::tuples::push_back
        <
            typename detail::map_params_to_cons<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>::type,
            Parameter
        >
{};

template <typename Head, typename Tail, typename Parameter>
struct add_parameter<boost::tuples::cons<Head, Tail>, Parameter>
    : geometry::tuples::push_back
        <
            boost::tuples::cons<Head, Tail>,
            Parameter
        >
{};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Static parameters values

struct datum_wgs84 {};
struct datum_ggrs87 {};
struct datum_nad83 {};
struct datum_nad27 {};
struct datum_potsdam {};
struct datum_carthage {};
struct datum_hermannskogel {};
struct datum_ire65 {};
struct datum_nzgd49 {};
struct datum_osgb36 {};

struct ellps_merit {};
struct ellps_sgs85 {};
struct ellps_grs80 {};
struct ellps_iau76 {};
struct ellps_airy {};
struct ellps_apl4_9 {};
struct ellps_nwl9d {};
struct ellps_mod_airy {};
struct ellps_andrae {};
struct ellps_aust_sa {};
struct ellps_grs67 {};
struct ellps_bessel {};
struct ellps_bess_nam {};
struct ellps_clrk66 {};
struct ellps_clrk80 {};
struct ellps_clrk80ign {};
struct ellps_cpm {};
struct ellps_delmbr {};
struct ellps_engelis {};
struct ellps_evrst30 {};
struct ellps_evrst48 {};
struct ellps_evrst56 {};
struct ellps_evrst69 {};
struct ellps_evrstss {};
struct ellps_fschr60 {};
struct ellps_fschr60m {};
struct ellps_fschr68 {};
struct ellps_helmert {};
struct ellps_hough {};
struct ellps_intl {};
struct ellps_krass {};
struct ellps_kaula {};
struct ellps_lerch {};
struct ellps_mprts {};
struct ellps_new_intl {};
struct ellps_plessis {};
struct ellps_seasia {};
struct ellps_walbeck {};
struct ellps_wgs60 {};
struct ellps_wgs66 {};
struct ellps_wgs72 {};
struct ellps_wgs84 {};
struct ellps_sphere {};

struct mode_plane {};
struct mode_di {};
struct mode_dd {};
struct mode_hex {};

struct orient_isea {};
struct orient_pole {};

struct pm_greenwich {};
struct pm_lisbon {};
struct pm_paris {};
struct pm_bogota {};
struct pm_madrid {};
struct pm_rome {};
struct pm_bern {};
struct pm_jakarta {};
struct pm_ferro {};
struct pm_brussels {};
struct pm_stockholm {};
struct pm_athens {};
struct pm_oslo {};

struct proj_aea {}; struct proj_leac {}; // Albers Equal Area, Lambert Equal Area Conic
struct proj_aeqd {}; // Azimuthal Equidistant
struct proj_airy {}; // Airy
struct proj_aitoff {}; struct proj_wintri {}; // Aitoff, Winkel Tripel
struct proj_august {};
struct proj_apian {}; struct proj_ortel {}; struct proj_bacon {};
struct proj_bipc {};
struct proj_boggs {};
struct proj_bonne {};
struct proj_cass {};
struct proj_cc {};
struct proj_cea {};
struct proj_chamb {};
struct proj_collg {};
struct proj_crast {};
struct proj_denoy {};
struct proj_eck1 {};
struct proj_eck2 {};
struct proj_eck3 {}; struct proj_putp1 {}; struct proj_wag6 {}; struct proj_kav7 {};
struct proj_eck4 {};
struct proj_eck5 {};
struct proj_eqc {};
struct proj_eqdc {};
struct proj_etmerc {}; struct proj_utm {};
struct proj_fahey {};
struct proj_fouc_s {};
struct proj_gall {};
struct proj_geocent {};
struct proj_geos {};
struct proj_gins8 {};
struct proj_gn_sinu {}; struct proj_sinu {}; struct proj_eck6 {}; struct proj_mbtfps {};
struct proj_gnom {};
struct proj_goode {};
struct proj_gstmerc {};
struct proj_hammer {};
struct proj_hatano {};
struct proj_healpix {};
struct proj_rhealpix {};
struct proj_igh {};
struct proj_imw_p {};
struct proj_isea {};
struct proj_krovak {};
struct proj_labrd {};
struct proj_laea {};
struct proj_lagrng {};
struct proj_larr {};
struct proj_lask {};
struct proj_lonlat {}; struct proj_latlon {}; struct proj_latlong {}; struct proj_longlat {};
struct proj_lcc {};
struct proj_lcca {};
struct proj_loxim {};
struct proj_lsat {};
struct proj_mbt_fps {};
struct proj_mbtfpp {};
struct proj_mbtfpq {};
struct proj_merc {};
struct proj_mill {};
struct proj_mil_os {}; struct proj_lee_os {}; struct proj_gs48 {}; struct proj_alsk {}; struct proj_gs50 {};
struct proj_moll {}; struct proj_wag4 {}; struct proj_wag5 {};
struct proj_natearth {};
struct proj_nell {};
struct proj_nell_h {};
struct proj_nicol {};
struct proj_nsper {}; struct proj_tpers {};
struct proj_nzmg {};
struct proj_ob_tran {};
struct proj_ocea {};
struct proj_oea {};
struct proj_omerc {};
struct proj_ortho {};
struct proj_poly {};
struct proj_putp2 {};
struct proj_putp3 {}; struct proj_putp3p {};
struct proj_putp4p {}; struct proj_weren {};
struct proj_putp5 {}; struct proj_putp5p {};
struct proj_putp6 {}; struct proj_putp6p {};
struct proj_qsc {};
struct proj_robin {};
struct proj_rouss {};
struct proj_rpoly {};
struct proj_euler {}; struct proj_murd1 {}; struct proj_murd2 {}; struct proj_murd3 {}; struct proj_pconic {}; struct proj_tissot {}; struct proj_vitk1 {};
struct proj_somerc {};
struct proj_stere {}; struct proj_ups {};
struct proj_sterea {};
struct proj_kav5 {}; struct proj_qua_aut {}; struct proj_fouc {}; struct proj_mbt_s {};
struct proj_tcc {};
struct proj_tcea {};
struct proj_tmerc {};
struct proj_tpeqd {};
struct proj_urm5 {};
struct proj_urmfps {}; struct proj_wag1 {};
struct proj_vandg {};
struct proj_vandg2 {}; struct proj_vandg3 {};
struct proj_vandg4 {};
struct proj_wag2 {};
struct proj_wag3 {};
struct proj_wag7 {};
struct proj_wink1 {};
struct proj_wink2 {};

struct sweep_x {};
struct sweep_y {};

struct units_km {};
struct units_m {};
struct units_dm {};
struct units_cm {};
struct units_mm {};
struct units_kmi {};
struct units_in {};
struct units_ft {};
struct units_yd {};
struct units_mi {};
struct units_fath {};
struct units_ch {};
struct units_link {};
struct units_us_in {};
struct units_us_ft {};
struct units_us_yd {};
struct units_us_ch {};
struct units_us_mi {};
struct units_ind_yd {};
struct units_ind_ft {};
struct units_ind_ch {};

// Static parameters names

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(NAME) \
template <typename T = double> \
struct NAME \
{ \
    NAME() : value(0) {} \
    explicit NAME(T const& v) : value(v) {} \
    T value; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(a)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(b)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(e)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(es)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(f)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(gamma)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(h)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(k)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(k_0)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(m)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(n)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(q)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(r)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(rf)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(to_meter)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(vto_meter)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(w)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(x_0)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(y_0)

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(NAME) \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_F(NAME)

BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(alpha)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(azi)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lat_0)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lat_1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lat_2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lat_b)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lat_ts)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lon_0)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lon_1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lon_2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lon_wrap)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(lonc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_alpha)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lat_1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lat_2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lat_c)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lat_p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lon_1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lon_2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lon_c)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(o_lon_p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(pm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(r_lat_a)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(r_lat_g)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(theta)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_R(tilt)

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(NAME) \
template <int I> struct NAME { static const int value = I; };
   
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(aperture)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(lsat)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(north_square)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(path)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(resolution)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(south_square)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_I(zone)

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(NAME) \
struct NAME {};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(czech)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(geoc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(guam)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(no_cut)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(no_defs)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(no_rot)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(ns)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(over)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(r_a)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(r_au)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(r_g)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(r_h)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(r_v)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(rescale) 
BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PARAM_BE(south)

template
<
    typename SpheroidOrSphere
>
struct ellps
{
    typedef SpheroidOrSphere model_type;
    
    ellps() : model() {}
    explicit ellps(SpheroidOrSphere const& sph) : model(sph) {}

    SpheroidOrSphere model;
};

struct nadgrids
    : srs::detail::nadgrids
{
    typedef srs::detail::nadgrids base_t;
    nadgrids(std::string const& g0) : base_t(g0) {}
    nadgrids(std::string const& g0, std::string const& g1) : base_t(g0, g1) {}
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2) : base_t(g0, g1, g2) {}
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2, std::string const& g3) : base_t(g0, g1, g2, g3) {}
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2, std::string const& g3, std::string const& g4) : base_t(g0, g1, g2, g3, g4) {}
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    nadgrids(std::initializer_list<std::string> l) : base_t(l) {}
#endif
};

template <typename Proj>
struct o_proj
{
    typedef Proj type;
};

template <typename T = double>
struct towgs84
    : srs::detail::towgs84<T>
{
    typedef srs::detail::towgs84<T> base_t;

    towgs84(T const& v0, T const& v1, T const& v2)
        : base_t(v0, v1, v2)
    {}
    towgs84(T const& v0, T const& v1, T const& v2, T const& v3, T const& v4, T const& v5, T const& v6)
        : base_t(v0, v1, v2, v3, v4, v5, v6)
    {}
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    towgs84(std::initializer_list<T> l) : base_t(l) {}
#endif
};

template <typename Units>
struct vunits
{
    typedef Units type;
};

// Static parameters traits

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename D>
struct datum_traits
{
    static const bool is_specialized = false;
    typedef void ellps_type;
    typedef void def_type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(NAME, ELLPS, DEF_T, DEF_V) \
template <> \
struct datum_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::ELLPS ellps_type; \
    typedef spar::DEF_T def_type; \
    static spar::DEF_T def() { return spar::DEF_T DEF_V; } \
    static const dpar::value_datum id = dpar::NAME; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_wgs84, ellps_wgs84, towgs84<double>, (0,0,0))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_ggrs87, ellps_grs80, towgs84<double>, (-199.87,74.79,246.62))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_nad83, ellps_grs80, towgs84<double>, (0,0,0))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_nad27, ellps_clrk66, nadgrids, ("@conus","@alaska","@ntv2_0.gsb","@ntv1_can.dat"))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_potsdam, ellps_bessel, towgs84<double>, (598.1,73.7,418.2,0.202,0.045,-2.455,6.7))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_carthage, ellps_clrk80ign, towgs84<double>, (-263.0,6.0,431.0))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_hermannskogel, ellps_bessel, towgs84<double>, (577.326,90.129,463.919,5.137,1.474,5.297,2.4232))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_ire65, ellps_mod_airy, towgs84<double>, (482.530,-130.596,564.557,-1.042,-0.214,-0.631,8.15))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_nzgd49, ellps_intl, towgs84<double>, (59.47,-5.04,187.44,0.47,-0.1,1.024,-4.5993))
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_DATUM(datum_osgb36, ellps_airy, towgs84<double>, (446.448,-125.157,542.060,0.1502,0.2470,0.8421,-20.4894))


template <typename E>
struct ellps_traits
{
    static const bool is_specialized = false;
    template <typename T> struct model_type
    {
        typedef void type;
    };
};

template <typename E>
struct ellps_traits<spar::ellps<E> >
{
    static const bool is_specialized = true;
    template <typename T> struct model_type
    {
        // TODO: transform to spheroid<T> or sphere<T>
        typedef typename spar::ellps<E>::model_type type;
    };

    template <typename T>
    static typename spar::ellps<E>::model_type const& model(spar::ellps<E> const& e)
    {
        return e.model;
    }
};

// TODO: Implement as RadiusType-agnostic, member struct template defining model
//       and function template returning it
#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(NAME) \
template <> \
struct ellps_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    template <typename T> struct model_type \
    { \
        typedef srs::spheroid<T> type; \
    }; \
    template <typename T> \
    static srs::spheroid<T> model(spar::NAME const&) { \
        return srs::spheroid<T>(projections::detail::pj_get_ellps<T>().first[dpar::NAME].a, \
                                projections::detail::pj_get_ellps<T>().first[dpar::NAME].b); \
    } \
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_SPHERE(NAME) \
template <> \
struct ellps_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    template <typename T> struct model_type \
    { \
        typedef srs::sphere<T> type; \
    }; \
    template <typename T> \
    static srs::sphere<T> model(spar::NAME const&) { \
        return srs::sphere<T>(projections::detail::pj_get_ellps<T>().first[dpar::NAME].a); \
    } \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_merit)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_sgs85)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_grs80)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_iau76)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_airy)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_apl4_9)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_nwl9d)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_mod_airy)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_andrae)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_aust_sa)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_grs67)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_bessel)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_bess_nam)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_clrk66)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_clrk80)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_clrk80ign)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_cpm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_delmbr)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_engelis)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_evrst30)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_evrst48)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_evrst56)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_evrst69)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_evrstss)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_fschr60)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_fschr60m)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_fschr68)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_helmert)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_hough)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_intl)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_krass)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_kaula)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_lerch)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_mprts)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_new_intl)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_plessis)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_seasia)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_walbeck)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_wgs60)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_wgs66)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_wgs72)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ELLPS(ellps_wgs84)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_SPHERE(ellps_sphere)

template <typename M>
struct mode_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_MODE(NAME) \
template <> \
struct mode_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::NAME type; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_MODE(mode_plane)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_MODE(mode_di)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_MODE(mode_dd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_MODE(mode_hex)

template <typename O>
struct orient_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ORIENT(NAME) \
template <> \
struct orient_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::NAME type; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ORIENT(orient_isea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_ORIENT(orient_pole)

template <typename M>
struct pm_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

template <typename T>
struct pm_traits<spar::pm<T> >
{
    static const bool is_specialized = true;
    typedef T type;
    static T const& value(spar::pm<T> const& p) { return p.value; }
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(NAME, INDEX) \
template <> \
struct pm_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef double type; \
    static double value(spar::NAME const& ) { return projections::detail::pj_prime_meridians[INDEX].deg; } \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_greenwich, 0)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_lisbon,    1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_paris,     2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_bogota,    3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_madrid,    4)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_rome,      5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_bern,      6)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_jakarta,   7)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_ferro,     8)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_brussels,  9)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_stockholm, 10)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_athens,    11)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PM(pm_oslo,      12)

template <typename P>
struct proj_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(NAME) \
template <> \
struct proj_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::NAME type; \
    static const srs::dpar::value_proj id = dpar::NAME; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_aea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_leac)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_aeqd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_airy)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_aitoff)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wintri)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_august)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_apian)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_ortel)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_bacon)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_bipc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_boggs)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_bonne)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_cass)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_cc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_cea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_chamb)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_collg)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_crast)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_denoy)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag6)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_kav7)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck4)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eqc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eqdc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_etmerc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_utm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_fahey)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_fouc_s)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gall)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_geocent)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_geos)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gins8)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gn_sinu)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_sinu)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_eck6)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mbtfps)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gnom)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_goode)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gstmerc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_hammer)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_hatano)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_healpix)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_rhealpix)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_igh)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_imw_p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_isea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_krovak)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_labrd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_laea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lagrng)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_larr)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lask)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lonlat)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_latlon)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_latlong)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_longlat)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lcc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lcca)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_loxim)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lsat)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mbt_fps)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mbtfpp)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mbtfpq)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_merc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mill)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mil_os)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_lee_os)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gs48)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_alsk)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_gs50)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_moll)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag4)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_natearth)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_nell)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_nell_h)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_nicol)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_nsper)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tpers)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_nzmg)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_ob_tran)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_ocea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_oea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_omerc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_ortho)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_poly)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp3p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp4p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_weren)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp5p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp6)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_putp6p)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_qsc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_robin)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_rouss)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_rpoly)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_euler)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_murd1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_murd2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_murd3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_pconic)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tissot)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_vitk1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_somerc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_stere)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_ups)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_sterea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_kav5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_qua_aut)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_fouc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_mbt_s)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tcc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tcea)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tmerc)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_tpeqd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_urm5)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_urmfps)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_vandg)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_vandg2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_vandg3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_vandg4)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag2)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag3)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wag7)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wink1)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_wink2)

template <typename S>
struct sweep_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_SWEEP(NAME) \
template <> \
struct sweep_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::NAME type; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_SWEEP(sweep_x)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_SWEEP(sweep_y)

template <typename S>
struct units_traits
{
    static const bool is_specialized = false;
    typedef void type;
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(NAME) \
template <> \
struct units_traits<spar::NAME> \
{ \
    static const bool is_specialized = true; \
    typedef spar::NAME type; \
    static const srs::dpar::value_units id = dpar::NAME; \
};

BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_km)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_m)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_dm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_cm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_mm)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_kmi)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_in)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_ft)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_yd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_mi)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_fath)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_ch)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_link)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_us_in)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_us_ft)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_us_yd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_us_ch)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_us_mi)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_ind_yd)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_ind_ft)
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_UNITS(units_ind_ch)


template <typename T, template <typename> class Param>
struct is_same_t : boost::false_type {};
template <typename T, template <typename> class Param>
struct is_same_t<Param<T>, Param> : boost::true_type {};

template <typename T, template <int> class Param>
struct is_same_i : boost::false_type {};
template <int I, template <int> class Param>
struct is_same_i<Param<I>, Param> : boost::true_type {};

template <typename T, template <typename> class Traits>
struct it_traits_specialized
    : boost::mpl::if_c
        <
            Traits<T>::is_specialized,
            boost::true_type,
            boost::false_type
        >::type
{};

template <typename Param>
struct is_param
{
    template <typename T>
    struct pred : boost::is_same<T, Param> {};
};

template <template <typename> class Param>
struct is_param_t
{
    template <typename T>
    struct pred : is_same_t<T, Param> {};
};

template <template <int> class Param>
struct is_param_i
{
    template <typename T>
    struct pred : is_same_i<T, Param> {};
};

template <template <typename> class Traits>
struct is_param_tr
{
    template <typename T>
    struct pred : it_traits_specialized<T, Traits> {};
};

//template <typename IsParam1, typename IsParam2>
//struct is_param_or
//{
//    template <typename T>
//    struct pred : boost::mpl::or_<IsParam1::pred<T>, IsParam2::pred<T> > {};
//};

// pick proj static name

template <typename Tuple>
struct pick_proj_tag
{
    typedef typename geometry::tuples::find_if
        <
            Tuple,
            is_param_tr<proj_traits>::pred
        >::type proj_type;

    static const bool is_found = geometry::tuples::is_found<proj_type>::value;

    BOOST_MPL_ASSERT_MSG((is_found), PROJECTION_NOT_NAMED, (Tuple));

    typedef proj_traits<proj_type> traits_type;
    typedef typename traits_type::type type;
};

template <typename Tuple>
struct pick_o_proj_tag
{
    typedef typename geometry::tuples::find_if
        <
            Tuple,
            is_param_t<o_proj>::pred
        >::type o_proj_type;

    static const bool is_found = geometry::tuples::is_found<o_proj_type>::value;

    BOOST_MPL_ASSERT_MSG((is_found), NO_O_PROJ_PARAMETER, (Tuple));

    typedef proj_traits<typename o_proj_type::type> traits_type;
    typedef typename traits_type::type type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

} // namespace spar

}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP

/* spar.hpp
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
*/