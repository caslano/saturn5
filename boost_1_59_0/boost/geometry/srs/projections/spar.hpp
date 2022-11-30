// Boost.Geometry

// Copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP


#include <string>
#include <type_traits>
#include <vector>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/impl/pj_datums.hpp>
#include <boost/geometry/srs/projections/impl/pj_ellps.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/par_data.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/tuples.hpp>

#include <boost/variant/variant.hpp>


namespace boost { namespace geometry { namespace srs
{

namespace spar
{

// Static parameters holder

template <typename ...>
class parameters {};

namespace detail
{

// TODO: implement this as a sequence utility
template <std::size_t I, typename ...>
struct parameters_base
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "I out of bounds.",
        std::integral_constant<size_t, I>);
};

template <std::size_t I, typename P, typename ...Ps>
struct parameters_base<I, P, Ps...>
{
    typedef typename parameters_base<I - 1, Ps...>::type type;
};

template <typename P, typename ...Ps>
struct parameters_base<0, P, Ps...>
{
    typedef parameters<P, Ps...> type;
};

} // namespace detail

template <typename P, typename ...Ps>
class parameters<P, Ps...>
    : private parameters<Ps...>
{
public:
    parameters() = default;
    parameters(parameters const&) = default;
    parameters(parameters&&) = default;
    parameters & operator=(parameters const&) = default;
    parameters & operator=(parameters&&) = default;

    template
    <
        typename R, typename ...Rs,
        std::enable_if_t<std::is_constructible<P, R>::value, int> = 0
    >
    explicit parameters(R&& r, Rs&&... rs)
        : parameters<Ps...>(std::forward<Rs>(rs)...)
        , m_p(std::forward<R>(r))
    {}

    template <std::size_t I>
    auto const& get() const
    {
        typedef typename detail::parameters_base<I, P, Ps...>::type base_t;
        return static_cast<base_t const&>(*this).m_p;
    }

private:
    P m_p;

    template <typename ...>
    friend class parameters;
};

} // namespace spar

}}} // namespace boost::geometry::srs


namespace boost { namespace geometry { namespace tuples
{

template <std::size_t I, typename ...Ts>
struct element<I, srs::spar::parameters<Ts...> >
    : util::sequence_element<I, util::type_sequence<Ts...> >
{};

template <typename ...Ts>
struct size<srs::spar::parameters<Ts...> >
    : std::integral_constant<std::size_t, sizeof...(Ts)>
{};

template <int I, typename ...Ts>
inline typename element<I, srs::spar::parameters<Ts...> >::type const&
get(srs::spar::parameters<Ts...> const& tup)
{
    return tup.template get<I>();
}


}}} // namespace boost::geometry::tuples


namespace boost { namespace geometry { namespace srs
{

namespace spar
{

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
struct proj_webmerc {};
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
BOOST_GEOMETRY_PROJECTIONS_DETAIL_REGISTER_PROJ(proj_webmerc)
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
struct is_same_t : std::false_type {};
template <typename T, template <typename> class Param>
struct is_same_t<Param<T>, Param> : std::true_type {};

template <typename T, template <int> class Param>
struct is_same_i : std::false_type {};
template <int I, template <int> class Param>
struct is_same_i<Param<I>, Param> : std::true_type {};

template <typename T, template <typename> class Traits>
struct it_traits_specialized
    : std::integral_constant
        <
            bool,
            Traits<T>::is_specialized
        >
{};

template <typename Param>
struct is_param
{
    template <typename T>
    struct pred : std::is_same<T, Param> {};
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

    BOOST_GEOMETRY_STATIC_ASSERT((is_found), "Projection not named.", Tuple);

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

    BOOST_GEOMETRY_STATIC_ASSERT((is_found), "Expected o_proj parameter.", Tuple);

    typedef proj_traits<typename o_proj_type::type> traits_type;
    typedef typename traits_type::type type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

} // namespace spar

}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP

/* spar.hpp
u0I1A6d9UzIWalIVnUxhufDfVdSM0YxLO3wIi4VdVY92ZUu5a2Xu0L+t5I5vBQzhstxNwiT4tm9sGwjsovRwxDzVzd0IzyU5RJronPEVrsrtvH3Znn4QwKq2GDQ74CygrZ9Ev4sT3qY9CtLBtw2sdWG7VzIdSfJHpTc8x+Fl2lYNBreivTxhHMiV06mMpYd2BqK4McCzcL9zcEMzHEOcsZ7xlDAVpRgvdGguaPSBHnPQyrcNGw4fyp79V9Hq4ZY4h6wdlZ4bQP+p9dOKKz36FDgfh5hj4t6Qaec6Gt0qoJG4x+/mz4vFz1351sUOEhxtC70pHdwtBHU+LogkRxmJdeNH+rmXOqu939tLsVeaPaoF0+O+U/UZBhgUOfaDUk4R/RVEDqc6c4znjS7CHtkm4Ifo4RUAgG0zQPGwaK1QysdEBiNwCOnpD9a2vRujHG9LWTvb5EADX/pY20AHm3lhj8VYdO7kYeniRXos70N0+vA9KhQwSqqacVZjBD6PlEF0DiDw9/0T+jTS/xd4AAIs/dPl5I/hWGYBC6lgQf/NoXr/wkS/kw59K1R9iy728pcrKo0b6+IFyaPK+lu0ZZxrGNtM+Ptunm6zNJeDwMV4g9gXN9se7bXnJMIEAUAcliiBGb1GuH8vc7rtc+MnOdtLqu/YJZTozAm7KZQXIstPkkzgmGpRgICCZuA8e70xaY631rs1kDBit/r2wcT7TMLjY0In9OOkcZZEeD2/lw+Me2kG0vVBlWwT9V+Wlr5WaaZ5X/hj7j/qnq7Ja+c9Yw3jAiI/3s8e/sRgZ9mZDvPLCXT/eMYgyRoN6Tph9niHWuFYyYAxk/r3wLCaLY6Ic+hgg8EJrE6qrcZA9sM7AcPLjxlbu+limEtWIa0N86zlvyC11sqo5DDBP5ROhHXXBJDwehzLoArQdD5kc4XmUgvdFhewHLEVjjGgo72p7c0zr3hEon80HgI5LosfuT0scj7DXwq3wJ2cFSeOWoDMkyEu/MEzuX1lWYq6KRpF6dwXMenoLAhs2O5czSNKL8WjtLgDzQZTwSFJCnKoBfFDosAB7G4uOZz66MXHNYaB9MNkMa5AEXs+kVKcH4yN1xs4CoVLGNTd/Xbp1qF2G8L41H9ODOV5bQz381yPez6Kzajqhe53+QBVJBJBN0+fQX3GqFM7KTSdg2hO4+Qc1hrN8cM4aT0lohr+vD1jyH8V0QjyGX2He06gUA0QMeW9v1G0IfLBPcjhTaZ/jzuX3GimA2adlTIVdZGLx2Aq0F0xFK73GFmE4IeeRpxcqccYAQ02FuoOtY4oUh97Tp28GdIKjBBcEOOPtrsQf2tD3h36lFPJHCIUQdQIlkVQ7HGPsT93K26Uw3nCGCFLCaIaF0qUjlXZlUko58pVos8SrdBf40ujEkdktPVGG5Yt1ylbWcJkPV504IPGpV6pjDyLBd1eDlVYRuivFebgzKSp55OpZklXnspUsmdGXyyenD9k71JlN5leAf11arwGzTxb5CPv1K81hjV+WjbqL8SbNEhu+0uuazVe+PWSHN1c0BVxuibs7P9HkHEbSkgAlqXIWMi/qNdmONszC1NSh5ty0vMaKtOG2Znf+UP/OrRneDo5Y6rBIxmBLngr6LhRa38Lmou/tNqb1fzRGpQoHDX0Y/y5/IBIaw9U4aH/hpoY4VmWGDc6LuQpREi+in6lqBcrYjy2Hy0EioKIzmbf5tbqT0mh/dGej7T90V2Xzx988a3yicXs1j65Yy6L44Evv4RWPR3yRK+pw4DKfbOp/ROTO0BPWQoecy3zVpg6sIRhhPMqT753LjlV1+3K6JsfKbXQl5c8xk1g8oc9EY7yEMGBrqByugnm0slij/rx9sn6bWeNuHS41BVElTC4a0BzOi5EvDD1aYd1/3zaEru7OuLnw9jo6LBizS5gXcBWzKQ0gdYQddie1DL53HL4DLwa+rT8qs+e8XC/+No4NnSFOIUrln8+ReUKMWwi4QdlsEHjGSx1rCX40bACwyhrnoIepd+9xV2gr016T8VeiRmIvGnV7E92CZDVDetD0vgqydNiR+bJuzUYQRjTUUfUMhwR4srC5QOrfAwDz+nMbNV1q2yLZ7RXsHqwm0Qsiz/kQVovhR0GlzUSqh2WSZpdpifpc2lit3YLL8KbFFNhNzpTXPuRP8Zi4vGL5XLfV3kJ7XSmt45p9IrmrQepJ1hRMVRuSkyES33uukWcebL9fLOdZ93DIB3H57o5FnkyNfZ1j3g0rSRGIXBnI4SFmu0/emFfHxrclxMWvdzW7vihw5PDiF8g8wmKO9i8xy2MI9EV3Eog6BQxt2p+R+BqKmYxtTXOiwimDxp0r9ZQWD5a0xd9GohOvIDks2hrzYsALKXZU/b6IiYfk/wqrEMKOzdMQxijj44lQ56JBxpe/KdqQj+GcZZ6hL6ICXN3DRGv/KHJbL6OaQlshezUndnvsRN9nQ3SFScyxzrrXObR1etvEvtvF0NnoPysV1BcEsGxRkj6m3Ku3pclwz32ZW9jsbqCFuyvu0s15EkDPxBE+eIjNdW9t3iJDCw54hei3WNuhUcisrzaHiDa0APQf1b9FzM4UZ70mLFVi2mbQav3KiEI0wc9rgqz1tGto+XN9WcEKx08/rJBsOgsrnF0wnyRpRqI7pZV4HyXtQYNrZHHYl0VRSHDlJ96Pl3UGGrCfHvkH+3wMzWzUgCu+K+8b8RVJL5Sz8DeNMHrvI3FYEVp9PhLMdM70xLimFqpAgPm7SEWe1omnY3I5Bbkjop/nGYVXOEoQdUMb6fOoBfaiVwZ24ubQIonS8QCP7k/DlPRhDKtTxthFW6LcZWfIGvlfTY4OIrAmHu2cVq4okEtunFkIYUpKCJpvtwDpH4ud7HPEoLb7lSGr7fb4+VGnsaBWjdrY034Uz7rAqOLVgjEccKG0mCLSiQnXzm1/PwR/Kv+jP2ZOdRtYlcyQnmlkUAmWzRCuUmGKvByHynico1Wzluc03di32rC2VH/DDvZbSG1GJR6P5ZAGDHj9KHDOgY0m062t9gTNPt16xM0hkKl/SfqNkrN3rtEbqYn0Mw90GAdycoLl4BaaUKV62sXIxVD3J4taGgUGksaJpGIyfGMiRfX0sn4jNttg6eXb/YTDTSmYyVyW40hgUkuTPbFj75LDroz8izbg9b5GjR4sityoxXezI8IbL1BB7wRSke0hm/AVstVhy3l+y+nggDFOtZs6au7X08MUbH31ciWzZPrRMtclZ9vBkujiMHBsLiU/62gFP7I1nd3NtwrMAegokVJIO44swT736WcDM9Te1kwLXztKq8WXYngRxjlsXaLlu+sSse6Rii9wP4qL5+QeS5B4L39xDEFvxnsNGwtQNeKJRbXMZ1VkXvzlSudmHtx5FVTuP30NXlhGuE2EDctRVjKUUuSDRE8fg8DOdo76urkbGkfMNzv56BztqIgs8rLLTWiYLVFCo3sB/XsINEvn1hS/hbWUVVyPM6CKoh263IvBQqs2iecrs30Z1jkMsj26FuBV0uJ9TKmcdmKN2G26kViXDPc8n8OaJp9OeRcOD1Fl9gmeTvlZ+6HJRSFVxlRhKDF93IqCTEviHEEsU5t9uolznKhhJbrGuENRYCoCoY1Bwjh2/UKn6crP+k4xzVJNwql5g4aw+kujSjdrdEt/ZPWQ630Qgy+++QGX07Nl0PXDEfnmlzAYw72oW1YN35la1vDfZ5OdSabV14GI0nAPjOljQZgKTRUWM4tBPCSuN57r7Wltw8XVhOwGs2zu6WOMuy0F8kynUXnfMbA9CPZCbEr+lVfJc1WI8CdNt4cfcE8VOy7pZuoPSJ/PYNEzvUf0kHv0ng2Q04ZjDawJnd4IhE7OJqHV5/TbFpTX/SqT7+iQO0nAL8N/U/uGU03cU03LUSUx2G/4H6EmX3IAiqXuypkRq6p3tLSXYlySmd+bLtj4nRwFOlITHQvxhXycMXAkL9i7irLrXSCxCWndpnkcA93R7I/V8OQpJKCLL/sO52faAvXxcyLTf1ipGCCOCkHMEXPLqc7yhoQTqeSw1+Jjl3xnfN+eEh3z8AWwEfa8h6eg1Yvgx1ZdbiD/64SZfk0zgzNx1YFzT0Mznt0lxgTkcxuNhxAC/HHjdKzi8xQxvJ+LTKnZQo3TdTVuND11yeiTGcJL1ZwDla1NUGjF54syKrgtrkBZ2Ei9hSBR20VrGNcD1gQwjXb3jOcEKM6FxXzuvoS6rq7PyJClPLHJ3g5LoERCKItKdjyPRX5Ccwi59e6OXoncOomtNRJMaCla+GSIDCGpu2AHgUmkDxBiiV74joRInZDhbLiFdtYhkeqKd4h03ME39BrhUHAPlag1pFQkZMcfeRq/mV0IgB0hPSVmIivI273dQxN6J5W39BgCHMo0J8G8E22BuiluUF2AniKOU9kIELgifIPSYx0QE658I/IoXkJoWVwULxMs5kTsQxhaIEirTlHanf6N4HaMYs/gXUXF3Pe8Epb4OkJQ7HxfRphmPW4yvWTFBDkV2hDl23EiDo/WzFTo4nxvdNyTvZ9WB8j+WLkHm9Z3rzgwhK/w8IOcTEzxs1IsjxjeEKhSor1ARKa7zbxWH8H3HBsXaSpNBBAx/foFLTQqFPfF1FwoPGOeO6OSFhOxXd0LPN59SMBae1Rvcxie9RX2duB2ewe0Zobo/se40uFSsEfVDUzn/4UJT4msUUIx9fZ293EKr1lxhNs2e9zK8yJeOfPfD4ElC7KsxKvcINR8/SKkfbojgVj5GEdFETPoZMbnivXCH2qVSq1HsG//OHaAOGhEZf0pCavecE76N7f/Rq6ZUI0XshweMa2lQM3jBrpObR5laMyVaNnetHEQh69wzEe+e6s3G6IaX6UXKmMLLQtOPYhOCdIwuWX0J8eiVwhbU3PGr4KVV45rof7oGaEdM19uVxTG5TuKdLUQ+C8W4J5LtnGuFgipvwxmzgLUEUWhus5McVKwdXJq10AH6qqJ+o3qShSj3wEo4KWvDJaOvgO/2NGZIzIjMaEfxWTvVYiqrk9kGGxR4UtgVeKVYvsucdMGqdRqHYkqcYSSh7yhSwEhVQPQzO5bPfTopUmI9r3ExaSLlgVm+a4vdLhzb1gm6EyqM/xhMdNb14kSMzgAdrzUeWt5deGBsarXHrqDlQSD1HAHb7yeRgVWw0MpsQZtrJObtVFrnOhROzmmTPw1nDrsMouHWP8d1A+prGYbLyoteJHNEXkH5G3N4IBJeC0npGOgN8HHHTWicVDAkK+HE4rM7OKUF5S90HkrLKylcNRGdJZjw6NOBDz00oBUEtESXWSRsv+B/M0Z0CD4vrDfPBSAJa42hbneh5uuiVM5MAS++1NBmoGTQ2G2OpdhsaIKwdN9R7LovRUpHiXzvF2AjpCwjr+NMspE0ULOzWMegioNFAtGLqDnurlsZ1nORiV+Yv7uUCFw0ltVtFYx/lTKnmqcZkNB7YRi9TG0MhJ+I8vHJvUAXuwgiv/lARy+IqDmvOaf4YYcSq5jsfFv541ZLWKmizBoPCPPn6lP5uiwRsuLT9cjPZxrEej7K3XzuNQpuMVZ0lTpuNOZ0k0puOFWYi86GtLw/V2bNg/GEBdtJsoGmhJuE2giueMMMyKfUDHD2NR7cXWeKhe83/IWjAa34EDVbHwdSvg+YbCqB2tkpVjFbmAW32MvGIWF98T8snj/OgtycfF5Uas5Mykr+cJKkuNZ5wKixFBgPvKUWQLMGE5kmwvFL/cdCmm/+EMnLRPMnhXm3GEzjwpj9y2TR+0DrHyml/C4VnfIOKYLSTqjoraJND5gSjItky4t0iPO7XITDDE3brvI1G3SAKHJ2ZTs4ND83H70O0fQKP0kWK/KEzctYeUySl7wZtrIwgvqpAomNeP4Ua+o9aztVGqi/i5QMGDSTP9qZhSfO/mVrgioPGvfUXMDfeikPIAvDNYyjkU9DqVrrcVbC8re6b1v/CXJPjWp/DRw52IOHLk72Rom+cGVKj00+RHTFn6zoMeaenfsht3SidLomZZoxuLPe1tJLemTD4cflSkqnJIg5uT4eBIm820vhhq2o/0vWgDBG4FUVDIRoffOmeGHT75iL0mNBBrS1Xrn+nkDhmQc0mev6ukk+Bj+nG7kEgPHneA4wI7grk9G293tBXaOzjZoqSyuEfeBW7AVN2YHW2U9ABI910mHzX3T262VczOa3S5mFHsYsDySWdQ1/cahvAH7cCW7XkoQrFU6SMNolNhRdP0++YMHH5R4Au30aHWez1OauFHSj38yE9PMc/R95uXZS/yGdGVDVYzmW7+mNuK5FgCO1IWa5fUH20o8ayL27FsDUrP5XxOB2qFX4ccS8otFsQ17H0bJEijjrKbFnlcJ3k6BtD8uYV+Xz7oHMJqCHpBnjfsxIspGPLm1rfYdiILVEDVZJvPuFzzFuI//rbw8wE++VwDn34bBJ9ORx/mOHgR4yQeuYTEI26PBB2vnMK+ZoSjbc+9JITlhH339saG2Bf1Vhq5f3TjUGx7FRxTD3AlcvoOY7+MV6VZCYj7A3wuxgSdyXpd8+Nrz1zhxDMh3BK2FB9CfEIN4OpzrM0v327cD9HhjbWHrMRp16tRqhywWouQC3vlX2eZFn2M6nt8jJpxW1BOHXFmvRWnkzlutzUjNGb9VJHegNfD6nR8wNRg6uNoDFQpcO5eBxCQgN2aPA7hVqXNsp6e1EOoCGTNd83G0fN9Bjx2Ryag7uJ+RbrTDFeaNiMqP3nzaw+h/hltwKLuiiP2W11qg0vq7a8gIMZuCquuBtnOzCmRzmLJDM5BIELDKiTiXOYMobWYamcOEDUH6yg3SK8CLlYPeW1MSp/UjG6+mT7HiiILEREb6kwfQf394qO9miWlNOxA0lRyDxb21BGnIqkXo4mjheig+nO9smkaBdAlS/g7Fqac71Gz6R0ueoyuM/bwm+ZcBR02HdqF3hXjv0sM+cuL4+4dQzaa6DOfn7gzZCuUzHmKZcpq6VL1CvVk2TrVuwnGw4nClrgPaHvnAmcCnpk5axtfrsy0L3b2XSC9ErxIj6wBT4MgPb7siW9puhGJMwTDZ4OgIdgeHRIi+niZnPD9wFlpMcgMhSNTZo79EhLvqDik+RtUaYIM7xwP3mWlZj2X8OM/eBzQlDDaZ6az6YW8D1M6xSUwng/+zkieEes553TxhV9zqzPQ+qiGCily1G29Oa6fyHURYKy2Y0Xhf5Hl/85kgG1pCN+P7fTS5eBG0lEz1m1dkaXFUjZg+DEwfJ/9XGMihA+d9/YDWnALby7kU8v/4N/1JlOFZn6Fg9fwpgoEV4SF21uwIrCmC4e/SNdVeWdzz5bj4Y7IyE6xA6nu5Ok9j+XNMfGoibZafMAHhRFFAtweTOq7gY/ecgHHZBBJJnBzWUpGpnCwFx4hG8ZEsyOQvdqngiVQxoDLGchFPDPoIj3EzaOqNYPdEZt+Z4/OUGxgmow3x1UhG5SAM4X8Ey7P+elTKdCfMcLgKaf3qt+kdpm8jFAyr5iyT9uRvPmrhos5wf5T36zU89RfKvqPYYuvISV7ZP6LiWrtecP5ZxI5QXZuUhFTcqhaa1MeTk9VVUom27OlEK0m/tYCjrql/GW/TEwc1BCVgJLVUUhnwkadtLM6
*/