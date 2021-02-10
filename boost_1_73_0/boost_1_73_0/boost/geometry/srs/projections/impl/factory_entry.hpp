// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FACTORY_ENTRY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FACTORY_ENTRY_HPP

#include <string>

#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

// forward declaration needed by some projections
template <typename Params, typename CT, typename Parameters>
class factory;

template <typename Params, typename CT, typename Parameters>
struct factory_entry
{
    virtual ~factory_entry() {}
    virtual dynamic_wrapper_b<CT, Parameters>* create_new(Params const& , Parameters const& ) const = 0;
};

// Macros for entries definition

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(ENTRY) \
template <typename Params, typename T, typename Parameters> \
struct ENTRY : projections::detail::factory_entry<Params, T, Parameters> \
{ \
    projections::detail::dynamic_wrapper_b<T, Parameters>* create_new(Params const& params, \
                                                                      Parameters const& parameters) const

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END };

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(ENTRY, PROJ) \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(ENTRY) \
{ \
    return new projections::detail::dynamic_wrapper_f<PROJ<T, Parameters>, T, Parameters>(params, parameters); \
} \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(ENTRY, PROJ) \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(ENTRY) \
{ \
    return new projections::detail::dynamic_wrapper_fi<PROJ<T, Parameters>, T, Parameters>(params, parameters); \
} \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(ENTRY, PROJ_S, PROJ_E) \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(ENTRY) \
{ \
    if (parameters.es != 0.0) \
        return new projections::detail::dynamic_wrapper_fi<PROJ_E<T, Parameters>, T, Parameters>(params, parameters); \
    else \
        return new projections::detail::dynamic_wrapper_fi<PROJ_S<T, Parameters>, T, Parameters>(params, parameters); \
} \
BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END

// Macros for factory initialization
#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(FUN_NAME) \
template <typename Params, typename T, typename Parameters> \
inline void FUN_NAME(projections::detail::factory<Params, T, Parameters>& factory)

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(PROJ_NAME, ENTRY) \
    factory.add_to_factory(#PROJ_NAME, \
                           srs::dpar::proj_##PROJ_NAME, \
                           new ENTRY<Params, T, Parameters>);

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FACTORY_ENTRY_HPP

/* factory_entry.hpp
M5Tei5NRE37TcQ63YDDwN1JPVe/0pZXAXBsHgVdnnoZMOmcAwMnUbwwaI7PO1PmT1M1VspffHR83Ou3G0NQGTycpMGzPtSOeaYCYEjri8SV9/1PGQ51gCR3EIFtt5gIfl2av96ltDjVuLvh5FqlmENy6jvBxYZFN00xQE49q4GezNlRpUycQBGX/ZzEbV+cmjWs3YaiyaJaAqUWUzBU9yw+NJosEIjGXUl0uedRL3o7CDLAiB1vJG6605Sq5F/NLO/GEcAAij4iyRR9lEUl8g4kaYmMBrcnpCKG2x3jSSt2WpXjE1ywx4Zo8fZskagSw7OXS4cqlSkeRWYJSqPGdIb+IWLLcqQPoJD7Y+A+aL7j/h8Rg4gFNE7JYbMa0MMWmxq9ztmUURieemuBLGQvFMhSyikZTLNQFLVJPTTnqFeTvWjciLDwlNpEnN32OJwqjjbLCpSIv4/v/29De1rrlmq4WS3pCYV/yDMaU3u5VSK8iKV9vRlOR34q6tP1ZYLz2nXs+wvutjwEAe8uTIINsA3bLHTonKUxKezsU7u+YGTqkH8xXDo8AGRKbON5hvoL0nk/wFLixPy3Xd+MaS/PF7nq+2KxxFXUroQzv5FAQj5qcUk6ed7kr4r4UGJi/MbVQyEylrAS337AguiAj
*/