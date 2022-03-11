// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_DPAR_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_DPAR_HPP


#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/par_data.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/srs/spheroid.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/variant/variant.hpp>

#include <string>
#include <vector>

namespace boost { namespace geometry { namespace srs
{

namespace detail
{

template
<
    typename Types,
    typename T,
    typename Iter = typename boost::mpl::begin<Types>::type,
    typename End = typename boost::mpl::end<Types>::type,
    int I = 0
>
struct find_type_index
{
    typedef typename boost::mpl::deref<Iter>::type type;
    static const int value = boost::is_same<type, T>::value
                           ? I
                           : find_type_index
                                <
                                    Types,
                                    T,
                                    typename boost::mpl::next<Iter>::type,
                                    End,
                                    I + 1
                                >::value;
                            
};

template
<
    typename Types,
    typename T,
    typename End,
    int I
>
struct find_type_index<Types, T, End, End, I>
{
    static const int value = I;
};


template
<
    typename Range,
    typename ToValue,
    bool IsRange = boost::has_range_iterator<Range>::value
>
struct is_convertible_range
    : boost::is_convertible
        <
            typename boost::range_value<Range>::type,
            ToValue
        >
{};

template
<
    typename Range,
    typename ToValue
>
struct is_convertible_range<Range, ToValue, false>
    : boost::false_type
{};

} // namespace detail


namespace dpar
{

enum value_datum
{
    datum_wgs84 = 0,
    datum_ggrs87,
    datum_nad83,
    datum_nad27,
    datum_potsdam,
    datum_carthage,
    datum_hermannskogel,
    datum_ire65,
    datum_nzgd49,
    datum_osgb36,
};

enum value_ellps
{
    ellps_merit = 0,
    ellps_sgs85,
    ellps_grs80,
    ellps_iau76,
    ellps_airy,
    ellps_apl4_9,
    ellps_nwl9d,
    ellps_mod_airy,
    ellps_andrae,
    ellps_aust_sa,
    ellps_grs67,
    ellps_bessel,
    ellps_bess_nam,
    ellps_clrk66,
    ellps_clrk80,
    ellps_clrk80ign,
    ellps_cpm,
    ellps_delmbr,
    ellps_engelis,
    ellps_evrst30,
    ellps_evrst48,
    ellps_evrst56,
    ellps_evrst69,
    ellps_evrstss,
    ellps_fschr60,
    ellps_fschr60m,
    ellps_fschr68,
    ellps_helmert,
    ellps_hough,
    ellps_intl,
    ellps_krass,
    ellps_kaula,
    ellps_lerch,
    ellps_mprts,
    ellps_new_intl,
    ellps_plessis,
    ellps_seasia,
    ellps_walbeck,
    ellps_wgs60,
    ellps_wgs66,
    ellps_wgs72,
    ellps_wgs84,
    ellps_sphere
};

enum value_mode
{
    mode_plane = 0,
    mode_di,
    mode_dd,
    mode_hex
};

enum value_orient
{
    orient_isea = 0,
    orient_pole,
};

enum value_pm
{
    pm_greenwich = 0,
    pm_lisbon,
    pm_paris,
    pm_bogota,
    pm_madrid,
    pm_rome,
    pm_bern,
    pm_jakarta,
    pm_ferro,
    pm_brussels,
    pm_stockholm,
    pm_athens,
    pm_oslo
};

enum value_proj
{
    proj_unknown = 0,
    proj_aea, proj_leac,
    proj_aeqd,
    proj_airy,
    proj_aitoff, proj_wintri,
    proj_august,
    proj_apian, proj_ortel, proj_bacon,
    proj_bipc,
    proj_boggs,
    proj_bonne,
    proj_cass,
    proj_cc,
    proj_cea,
    proj_chamb,
    proj_collg,
    proj_crast,
    proj_denoy,
    proj_eck1,
    proj_eck2,
    proj_eck3, proj_putp1, proj_wag6, proj_kav7,
    proj_eck4,
    proj_eck5,
    proj_eqc,
    proj_eqdc,
    proj_etmerc, proj_utm,
    proj_fahey,
    proj_fouc_s,
    proj_gall,
    proj_geocent,
    proj_geos,
    proj_gins8,
    proj_gn_sinu, proj_sinu, proj_eck6, proj_mbtfps,
    proj_gnom,
    proj_goode,
    proj_gstmerc,
    proj_hammer,
    proj_hatano,
    proj_healpix,
    proj_rhealpix,
    proj_igh,
    proj_imw_p,
    proj_isea,
    proj_krovak,
    proj_labrd,
    proj_laea,
    proj_lagrng,
    proj_larr,
    proj_lask,
    proj_lonlat, proj_latlon, proj_latlong, proj_longlat,
    proj_lcc,
    proj_lcca,
    proj_loxim,
    proj_lsat,
    proj_mbt_fps,
    proj_mbtfpp,
    proj_mbtfpq,
    proj_merc,
    proj_mill,
    proj_mil_os, proj_lee_os, proj_gs48, proj_alsk, proj_gs50,
    proj_moll, proj_wag4, proj_wag5,
    proj_natearth,
    proj_nell,
    proj_nell_h,
    proj_nicol,
    proj_nsper, proj_tpers,
    proj_nzmg,
    proj_ob_tran,
    proj_ocea,
    proj_oea,
    proj_omerc,
    proj_ortho,
    proj_poly,
    proj_putp2,
    proj_putp3, proj_putp3p,
    proj_putp4p, proj_weren,
    proj_putp5, proj_putp5p,
    proj_putp6, proj_putp6p,
    proj_qsc,
    proj_robin,
    proj_rouss,
    proj_rpoly,
    proj_euler, proj_murd1, proj_murd2, proj_murd3, proj_pconic, proj_tissot, proj_vitk1,
    proj_somerc,
    proj_stere, proj_ups,
    proj_sterea,
    proj_kav5, proj_qua_aut, proj_fouc, proj_mbt_s,
    proj_tcc,
    proj_tcea,
    proj_tmerc,
    proj_tpeqd,
    proj_urm5,
    proj_urmfps, proj_wag1,
    proj_vandg,
    proj_vandg2, proj_vandg3,
    proj_vandg4,
    proj_wag2,
    proj_wag3,
    proj_wag7,
    proj_wink1,
    proj_wink2
};

enum value_sweep
{
    sweep_x = 0, sweep_y
};

enum value_units
{
    units_km = 0,
    units_m,
    units_dm,
    units_cm,
    units_mm,
    units_kmi,
    units_in,
    units_ft,
    units_yd,
    units_mi,
    units_fath,
    units_ch,
    units_link,
    units_us_in,
    units_us_ft,
    units_us_yd,
    units_us_ch,
    units_us_mi,
    units_ind_yd,
    units_ind_ft,
    units_ind_ch
};

enum name_f
{
    a = 0,
    b,
    e,
    es,
    f,
    h,
    //h_0, // currently not used
    k = 7,
    k_0,
    m, // also used for M
    n,
    //phdg_0, // currently not used
    //plat_0, // currently not used
    //plon_0, // currently not used
    q = 14,
    r, // originally R
    rf,
    to_meter,
    vto_meter,
    w, // originally W
    x_0,
    y_0
};

enum name_r
{
    alpha = 22,
    azi,
    gamma,
    lat_0,
    lat_1,
    lat_2,
    lat_3,
    lat_b,
    lat_ts, // 30
    lon_0,
    lon_1,
    lon_2,
    lon_3,
    lon_wrap,
    lonc,
    o_alpha,
    o_lat_1,
    o_lat_2,
    o_lat_c, // 40
    o_lat_p,
    o_lon_1,
    o_lon_2,
    o_lon_c,
    o_lon_p,
    r_lat_a, // originally R_lat_a
    r_lat_g, // originally R_lat_g
    theta,
    tilt
};

enum name_i
{
    aperture = 50,
    lsat,
    north_square,
    path,
    resolution,
    south_square,
    zone
};

enum name_be
{
    czech = 57,
    geoc,
    guam,
    no_cut, // 60
    no_defs,
    no_rot,
    ns,
    over,
    r_au, // originally R_A
    r_a, // originally R_a
    r_g, // originally R_g
    r_h, // originally R_h
    r_v, // originally R_V
    rescale, // 70
    south
};

/*enum name_catalog
{
    catalog = 72 // currently not used
};

enum name_date
{
    date = 73 // currently not used
};*/

enum name_datum
{
    datum = 74
};

enum name_ellps
{
    ellps = 75 // id, sphere or spheroid
};

/*enum name_geoidgrids
{
    geoidgrids = 76 // currently not used
};*/

enum name_mode
{
    mode = 77
};

enum name_nadgrids
{
    nadgrids = 78 // arbitrary-length list of strings
};

enum name_orient
{
    orient = 79
};

enum name_pm
{
    pm = 80 // id or angle
};

enum name_proj
{
    o_proj = 81,
    proj
};

enum name_sweep
{
    sweep = 83
};

enum name_towgs84
{
    towgs84 = 84 // 3 or 7 element list of numbers
};

enum name_units
{
    units = 85,
    vunits
};

template <typename T>
struct parameter
{
    parameter()
        : m_id(-1), m_value(false)
    {}

    parameter(name_f id, T const& v)
        : m_id(id), m_value(v)
    {}

    // TODO various angle units
    parameter(name_r id, T const& v)
        : m_id(id), m_value(v)
    {}

    parameter(name_i id, int v)
        : m_id(id), m_value(v)
    {}

    parameter(name_be id)
        : m_id(id), m_value(true)
    {}

    parameter(name_be id, bool v)
        : m_id(id), m_value(v)
    {}

    parameter(name_datum id, value_datum v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_datum v)
        : m_id(datum), m_value(int(v))
    {}

    // TODO: store model at this point?
    parameter(name_ellps id, value_ellps v)
        : m_id(id), m_value(int(v))
    {}
    // TODO: store model at this point?
    parameter(value_ellps v)
        : m_id(ellps), m_value(int(v))
    {}

    template <typename Sphere>
    parameter(name_ellps id, Sphere const& v,
              typename boost::enable_if_c
                <
                    boost::is_same<typename geometry::tag<Sphere>::type, srs_sphere_tag>::value
                >::type * = 0)
        : m_id(id)
        , m_value(T(get_radius<0>(v)))
    {}

    template <typename Spheroid>
    parameter(name_ellps id, Spheroid const& v,
              typename boost::enable_if_c
                <
                    boost::is_same<typename geometry::tag<Spheroid>::type, srs_spheroid_tag>::value
                >::type * = 0)
        : m_id(id)
        , m_value(srs::spheroid<T>(get_radius<0>(v), get_radius<2>(v)))
    {}

    parameter(name_mode id, value_mode v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_mode v)
        : m_id(mode), m_value(int(v))
    {}

    template <typename Range>
    parameter(name_nadgrids id, Range const& v,
              typename boost::enable_if_c
                <
                    detail::is_convertible_range<Range const, std::string>::value
                >::type * = 0)
        : m_id(id)
        , m_value(srs::detail::nadgrids(boost::begin(v), boost::end(v)))
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    parameter(name_nadgrids id, std::initializer_list<std::string> v)
        : m_id(id)
        , m_value(srs::detail::nadgrids(v))
    {}
#endif

    parameter(name_orient id, value_orient v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_orient v)
        : m_id(orient), m_value(int(v))
    {}

    // TODO: store to_meters at this point?
    parameter(name_pm id, value_pm v)
        : m_id(id), m_value(int(v))
    {}
    // TODO: store to_meters at this point?
    parameter(value_pm v)
        : m_id(pm), m_value(int(v))
    {}

    // TODO angle units
    parameter(name_pm id, T const& v)
        : m_id(id), m_value(v)
    {}

    parameter(name_proj id, value_proj v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_proj v)
        : m_id(proj), m_value(int(v))
    {}

    parameter(name_sweep id, value_sweep v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_sweep v)
        : m_id(sweep), m_value(int(v))
    {}

    template <typename Range>
    parameter(name_towgs84 id, Range const& v,
              typename boost::enable_if_c
                <
                    detail::is_convertible_range<Range const, T>::value
                >::type * = 0)
        : m_id(id)
        , m_value(srs::detail::towgs84<T>(boost::begin(v), boost::end(v)))
    {
        std::size_t n = boost::size(v);
        if (n != 3 && n != 7)
        {
            BOOST_THROW_EXCEPTION( projection_exception("Invalid number of towgs84 elements. Should be 3 or 7.") );
        }
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    parameter(name_towgs84 id, std::initializer_list<T> v)
        : m_id(id)
        , m_value(srs::detail::towgs84<T>(v))
    {
        std::size_t n = v.size();
        if (n != 3 && n != 7)
        {
            BOOST_THROW_EXCEPTION( projection_exception("Invalid number of towgs84 elements. Should be 3 or 7.") );
        }
    }
#endif

    parameter(name_units id, value_units v)
        : m_id(id), m_value(int(v))
    {}

    parameter(value_units v)
        : m_id(units), m_value(int(v))
    {}
    
private:
    typedef boost::variant
        <
            bool,
            int,
            T,
            srs::spheroid<T>,
            srs::detail::nadgrids,
            srs::detail::towgs84<T>
        > variant_type;

public:
    bool is_id_equal(name_f const& id) const { return m_id == int(id); }
    bool is_id_equal(name_r const& id) const { return m_id == int(id); }
    bool is_id_equal(name_i const& id) const { return m_id == int(id); }
    bool is_id_equal(name_be const& id) const { return m_id == int(id); }
    bool is_id_equal(name_datum const& id) const { return m_id == int(id); }
    bool is_id_equal(name_ellps const& id) const { return m_id == int(id); }
    bool is_id_equal(name_mode const& id) const { return m_id == int(id); }
    bool is_id_equal(name_nadgrids const& id) const { return m_id == int(id); }
    bool is_id_equal(name_orient const& id) const { return m_id == int(id); }
    bool is_id_equal(name_pm const& id) const { return m_id == int(id); }
    bool is_id_equal(name_proj const& id) const { return m_id == int(id); }
    bool is_id_equal(name_sweep const& id) const { return m_id == int(id); }
    bool is_id_equal(name_towgs84 const& id) const { return m_id == int(id); }
    bool is_id_equal(name_units const& id) const { return m_id == int(id); }

    template <typename V>
    V const& get_value() const
    {
        return boost::get<V>(m_value);
    }

    template <typename V>
    bool is_value_set() const
    {
        return m_value.which() == srs::detail::find_type_index
            <
                typename variant_type::types,
                V
            >::value;
    }
    
private:
    int m_id;
    variant_type m_value;
};

template <typename T = double>
class parameters
{
    typedef std::vector<parameter<T> > container_type;

public:
    typedef typename container_type::value_type value_type;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type size_type;

    BOOST_DEFAULTED_FUNCTION(parameters(), {})

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <typename Id>
    explicit parameters(Id id)
    {
        add(id);
    }

    template <typename Id>
    parameters & add(Id id)
    {
        m_params.push_back(parameter<T>(id));
        return *this;
    }

    template <typename Id>
    parameters & operator()(Id id)
    {
        return add(id);
    }

    template <typename Id, typename V>
    parameters(Id id, V const& value)
    {
        add(id, value);
    }

    template <typename Id, typename V>
    parameters & add(Id id, V const& value)
    {
        m_params.push_back(parameter<T>(id, value));
        return *this;
    }

    template <typename Id, typename V>
    parameters & operator()(Id id, V const& value)
    {
        return add(id, value);
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <typename Id, typename V>
    parameters(Id id, std::initializer_list<V> value)
    {
        add(id, value);
    }

    template <typename Id, typename V>
    parameters & add(Id id, std::initializer_list<V> value)
    {
        m_params.push_back(parameter<T>(id, value));
        return *this;
    }

    template <typename Id, typename V>
    parameters & operator()(Id id, std::initializer_list<V> value)
    {
        return add(id, value);
    }
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#else // BOOST_NO_CXX11_RVALUE_REFERENCES || BOOST_NO_CXX11_RVALUE_REFERENCES
    template <typename Id>
    explicit parameters(Id id)
    {
        add(id);
    }

    template <typename Id>
    parameters & add(Id id)
    {
        m_params.emplace_back(id);
        return *this;
    }

    template <typename Id>
    parameters & operator()(Id id)
    {
        return add(id);
    }

    template <typename Id, typename V>
    parameters(Id id, V && value)
    {
        add(id, std::forward<V>(value));
    }

    template <typename Id, typename V>
    parameters & add(Id id, V && value)
    {
        m_params.emplace_back(id, std::forward<V>(value));
        return *this;
    }

    template <typename Id, typename V>
    parameters & operator()(Id id, V && value)
    {
        return add(id, std::forward<V>(value));
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <typename Id, typename V>
    parameters(Id id, std::initializer_list<V> value)
    {
        add(id, value);
    }

    template <typename Id, typename V>
    parameters & add(Id id, std::initializer_list<V> value)
    {
        m_params.emplace_back(id, value);
        return *this;
    }

    template <typename Id, typename V>
    parameters & operator()(Id id, std::initializer_list<V> value)
    {
        return add(id, value);
    }
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES || BOOST_NO_CXX11_RVALUE_REFERENCES

    const_iterator begin() const { return m_params.begin(); }
    const_iterator end() const { return m_params.end(); }
    const_reference operator[](size_type i) const { return m_params[i]; }
    size_type size() { return m_params.size(); }
    bool empty() { return m_params.empty(); }

private:
    container_type m_params;
};


} // namespace dpar


}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_DPAR_HPP

/* dpar.hpp
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
*/