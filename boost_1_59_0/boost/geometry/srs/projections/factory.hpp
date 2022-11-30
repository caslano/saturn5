// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/proj/aea.hpp>
#include <boost/geometry/srs/projections/proj/aeqd.hpp>
#include <boost/geometry/srs/projections/proj/airy.hpp>
#include <boost/geometry/srs/projections/proj/aitoff.hpp>
#include <boost/geometry/srs/projections/proj/august.hpp>
#include <boost/geometry/srs/projections/proj/bacon.hpp>
#include <boost/geometry/srs/projections/proj/bipc.hpp>
#include <boost/geometry/srs/projections/proj/boggs.hpp>
#include <boost/geometry/srs/projections/proj/bonne.hpp>
#include <boost/geometry/srs/projections/proj/cass.hpp>
#include <boost/geometry/srs/projections/proj/cc.hpp>
#include <boost/geometry/srs/projections/proj/cea.hpp>
#include <boost/geometry/srs/projections/proj/chamb.hpp>
#include <boost/geometry/srs/projections/proj/collg.hpp>
#include <boost/geometry/srs/projections/proj/crast.hpp>
#include <boost/geometry/srs/projections/proj/denoy.hpp>
#include <boost/geometry/srs/projections/proj/eck1.hpp>
#include <boost/geometry/srs/projections/proj/eck2.hpp>
#include <boost/geometry/srs/projections/proj/eck3.hpp>
#include <boost/geometry/srs/projections/proj/eck4.hpp>
#include <boost/geometry/srs/projections/proj/eck5.hpp>
#include <boost/geometry/srs/projections/proj/eqc.hpp>
#include <boost/geometry/srs/projections/proj/eqdc.hpp>
#include <boost/geometry/srs/projections/proj/etmerc.hpp>
#include <boost/geometry/srs/projections/proj/fahey.hpp>
#include <boost/geometry/srs/projections/proj/fouc_s.hpp>
#include <boost/geometry/srs/projections/proj/gall.hpp>
#include <boost/geometry/srs/projections/proj/geocent.hpp>
#include <boost/geometry/srs/projections/proj/geos.hpp>
#include <boost/geometry/srs/projections/proj/gins8.hpp>
#include <boost/geometry/srs/projections/proj/gn_sinu.hpp>
#include <boost/geometry/srs/projections/proj/gnom.hpp>
#include <boost/geometry/srs/projections/proj/goode.hpp>
#include <boost/geometry/srs/projections/proj/gstmerc.hpp>
#include <boost/geometry/srs/projections/proj/hammer.hpp>
#include <boost/geometry/srs/projections/proj/hatano.hpp>
#include <boost/geometry/srs/projections/proj/healpix.hpp>
#include <boost/geometry/srs/projections/proj/krovak.hpp>
#include <boost/geometry/srs/projections/proj/igh.hpp>
#include <boost/geometry/srs/projections/proj/imw_p.hpp>
#include <boost/geometry/srs/projections/proj/isea.hpp>
#include <boost/geometry/srs/projections/proj/laea.hpp>
#include <boost/geometry/srs/projections/proj/labrd.hpp>
#include <boost/geometry/srs/projections/proj/lagrng.hpp>
#include <boost/geometry/srs/projections/proj/larr.hpp>
#include <boost/geometry/srs/projections/proj/lask.hpp>
#include <boost/geometry/srs/projections/proj/latlong.hpp>
#include <boost/geometry/srs/projections/proj/lcc.hpp>
#include <boost/geometry/srs/projections/proj/lcca.hpp>
#include <boost/geometry/srs/projections/proj/loxim.hpp>
#include <boost/geometry/srs/projections/proj/lsat.hpp>
#include <boost/geometry/srs/projections/proj/mbtfpp.hpp>
#include <boost/geometry/srs/projections/proj/mbtfpq.hpp>
#include <boost/geometry/srs/projections/proj/mbt_fps.hpp>
#include <boost/geometry/srs/projections/proj/merc.hpp>
#include <boost/geometry/srs/projections/proj/mill.hpp>
#include <boost/geometry/srs/projections/proj/mod_ster.hpp>
#include <boost/geometry/srs/projections/proj/moll.hpp>
#include <boost/geometry/srs/projections/proj/natearth.hpp>
#include <boost/geometry/srs/projections/proj/nell.hpp>
#include <boost/geometry/srs/projections/proj/nell_h.hpp>
#include <boost/geometry/srs/projections/proj/nocol.hpp>
#include <boost/geometry/srs/projections/proj/nsper.hpp>
#include <boost/geometry/srs/projections/proj/nzmg.hpp>
#include <boost/geometry/srs/projections/proj/ob_tran.hpp>
#include <boost/geometry/srs/projections/proj/ocea.hpp>
#include <boost/geometry/srs/projections/proj/oea.hpp>
#include <boost/geometry/srs/projections/proj/omerc.hpp>
#include <boost/geometry/srs/projections/proj/ortho.hpp>
#include <boost/geometry/srs/projections/proj/qsc.hpp>
#include <boost/geometry/srs/projections/proj/poly.hpp>
#include <boost/geometry/srs/projections/proj/putp2.hpp>
#include <boost/geometry/srs/projections/proj/putp3.hpp>
#include <boost/geometry/srs/projections/proj/putp4p.hpp>
#include <boost/geometry/srs/projections/proj/putp5.hpp>
#include <boost/geometry/srs/projections/proj/putp6.hpp>
#include <boost/geometry/srs/projections/proj/robin.hpp>
#include <boost/geometry/srs/projections/proj/rouss.hpp>
#include <boost/geometry/srs/projections/proj/rpoly.hpp>
#include <boost/geometry/srs/projections/proj/sconics.hpp>
#include <boost/geometry/srs/projections/proj/somerc.hpp>
#include <boost/geometry/srs/projections/proj/stere.hpp>
#include <boost/geometry/srs/projections/proj/sterea.hpp>
#include <boost/geometry/srs/projections/proj/sts.hpp>
#include <boost/geometry/srs/projections/proj/tcc.hpp>
#include <boost/geometry/srs/projections/proj/tcea.hpp>
#include <boost/geometry/srs/projections/proj/tmerc.hpp>
#include <boost/geometry/srs/projections/proj/tpeqd.hpp>
#include <boost/geometry/srs/projections/proj/urm5.hpp>
#include <boost/geometry/srs/projections/proj/urmfps.hpp>
#include <boost/geometry/srs/projections/proj/vandg.hpp>
#include <boost/geometry/srs/projections/proj/vandg2.hpp>
#include <boost/geometry/srs/projections/proj/vandg4.hpp>
#include <boost/geometry/srs/projections/proj/wag2.hpp>
#include <boost/geometry/srs/projections/proj/wag3.hpp>
#include <boost/geometry/srs/projections/proj/wag7.hpp>
#include <boost/geometry/srs/projections/proj/wink1.hpp>
#include <boost/geometry/srs/projections/proj/wink2.hpp>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

template <typename Params>
struct factory_key
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Invalid parameters type.",
        Params);
};

template <>
struct factory_key<srs::detail::proj4_parameters>
{
    typedef std::string type;
    template <typename ProjParams>
    static type const& get(ProjParams const& par)
    {
        return par.id.name;
    }
    static const char* get(const char* name, srs::dpar::value_proj )
    {
        return name;
    }
};

template <typename T>
struct factory_key<srs::dpar::parameters<T> >
{
    typedef srs::dpar::value_proj type;
    template <typename ProjParams>
    static type const& get(ProjParams const& par)
    {
        return par.id.id;
    }
    static srs::dpar::value_proj get(const char* , srs::dpar::value_proj id)
    {
        return id;
    }
};


template <typename Params, typename CT, typename ProjParams>
class factory
{
private:
    typedef detail::factory_entry
        <
            Params,
            CT,
            ProjParams
        > entry_base;

    typedef factory_key<Params> key;
    typedef typename key::type key_type;
    typedef boost::shared_ptr<entry_base> entry_ptr;

    typedef std::map<key_type, entry_ptr> entries_map;

    entries_map m_entries;

public:

    factory()
    {
        detail::aea_init(*this);
        detail::aeqd_init(*this);
        detail::airy_init(*this);
        detail::aitoff_init(*this);
        detail::august_init(*this);
        detail::bacon_init(*this);
        detail::bipc_init(*this);
        detail::boggs_init(*this);
        detail::bonne_init(*this);
        detail::cass_init(*this);
        detail::cc_init(*this);
        detail::cea_init(*this);
        detail::chamb_init(*this);
        detail::collg_init(*this);
        detail::crast_init(*this);
        detail::denoy_init(*this);
        detail::eck1_init(*this);
        detail::eck2_init(*this);
        detail::eck3_init(*this);
        detail::eck4_init(*this);
        detail::eck5_init(*this);
        detail::eqc_init(*this);
        detail::eqdc_init(*this);
        detail::etmerc_init(*this);
        detail::fahey_init(*this);
        detail::fouc_s_init(*this);
        detail::gall_init(*this);
        detail::geocent_init(*this);
        detail::geos_init(*this);
        detail::gins8_init(*this);
        detail::gn_sinu_init(*this);
        detail::gnom_init(*this);
        detail::goode_init(*this);
        detail::gstmerc_init(*this);
        detail::hammer_init(*this);
        detail::hatano_init(*this);
        detail::healpix_init(*this);
        detail::krovak_init(*this);
        detail::igh_init(*this);
        detail::imw_p_init(*this);
        detail::isea_init(*this);
        detail::labrd_init(*this);
        detail::laea_init(*this);
        detail::lagrng_init(*this);
        detail::larr_init(*this);
        detail::lask_init(*this);
        detail::latlong_init(*this);
        detail::lcc_init(*this);
        detail::lcca_init(*this);
        detail::loxim_init(*this);
        detail::lsat_init(*this);
        detail::mbtfpp_init(*this);
        detail::mbtfpq_init(*this);
        detail::mbt_fps_init(*this);
        detail::merc_init(*this);
        detail::mill_init(*this);
        detail::mod_ster_init(*this);
        detail::moll_init(*this);
        detail::natearth_init(*this);
        detail::nell_init(*this);
        detail::nell_h_init(*this);
        detail::nocol_init(*this);
        detail::nsper_init(*this);
        detail::nzmg_init(*this);
        detail::ob_tran_init(*this);
        detail::ocea_init(*this);
        detail::oea_init(*this);
        detail::omerc_init(*this);
        detail::ortho_init(*this);
        detail::qsc_init(*this);
        detail::poly_init(*this);
        detail::putp2_init(*this);
        detail::putp3_init(*this);
        detail::putp4p_init(*this);
        detail::putp5_init(*this);
        detail::putp6_init(*this);
        detail::robin_init(*this);
        detail::rouss_init(*this);
        detail::rpoly_init(*this);
        detail::sconics_init(*this);
        detail::somerc_init(*this);
        detail::stere_init(*this);
        detail::sterea_init(*this);
        detail::sts_init(*this);
        detail::tcc_init(*this);
        detail::tcea_init(*this);
        detail::tmerc_init(*this);
        detail::tpeqd_init(*this);
        detail::urm5_init(*this);
        detail::urmfps_init(*this);
        detail::vandg_init(*this);
        detail::vandg2_init(*this);
        detail::vandg4_init(*this);
        detail::wag2_init(*this);
        detail::wag3_init(*this);
        detail::wag7_init(*this);
        detail::wink1_init(*this);
        detail::wink2_init(*this);
    }

    void add_to_factory(const char* name, srs::dpar::value_proj id, entry_base* entry)
    {
        // The pointer has to be owned before std::map::operator[] in case it thrown an exception.
        entry_ptr ptr(entry);
        m_entries[key::get(name, id)] = ptr;
    }

    detail::dynamic_wrapper_b<CT, ProjParams>* create_new(Params const& params, ProjParams const& proj_par) const
    {
        typedef typename entries_map::const_iterator const_iterator;
        const_iterator it = m_entries.find(key::get(proj_par));
        if (it != m_entries.end())
        {
            return it->second->create_new(params, proj_par);
        }

        return 0;
    }
};

template <typename T>
inline detail::dynamic_wrapper_b<T, projections::parameters<T> >*
    create_new(srs::detail::proj4_parameters const& params,
               projections::parameters<T> const& parameters)
{
    static factory<srs::detail::proj4_parameters, T, projections::parameters<T> > const fac;
    return fac.create_new(params, parameters);
}

template <typename T>
inline detail::dynamic_wrapper_b<T, projections::parameters<T> >*
    create_new(srs::dpar::parameters<T> const& params,
               projections::parameters<T> const& parameters)
{
    static factory<srs::dpar::parameters<T>, T, projections::parameters<T> > const fac;
    return fac.create_new(params, parameters);
}


} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP

/* factory.hpp
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
*/