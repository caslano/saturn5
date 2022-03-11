// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

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
    BOOST_MPL_ASSERT_MSG((false), INVALID_PARAMETERS_TYPE, (Params));
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
    static const char* get(const char* name, srs::dpar::value_proj id)
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
    static srs::dpar::value_proj get(const char* name, srs::dpar::value_proj id)
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