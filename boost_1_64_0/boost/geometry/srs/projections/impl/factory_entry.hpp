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
6+l2+/DpgCKz1og6X2YZlfnny1z24/MG8083uH24Sd/j0otc8Z2d3pD5sRk3tA14jHk5QePz3pjGjzN+Ii/NeyOwrtB37Zdz2hW4tpC0Yflleqs4zYlp0uTC3fhcTnMypzlFpSnKSZ/mm5xmtdLbCu4n1nP/9C3G+7ZqCwSnciufOIx7uqK5Rr2NtJbxzmS8LMLzUA7mrJNx1ilaSS/I33rGOxt0I1fROCdvyDd9h5wzm/Z6Xl6qvZ6Puqjy+36atdqFeVgH5FuA8S9GfKg3jX8p41/G+A9kpPe5msQ7DPK+n31CDtd7ZJ9GvgI4TV+e2LD1GM9Lfly5iXM+VSVthYnzXbJ8iO9HULy4gHHx/URjio23/bjEzbRxsWiUeUpS3BwTx4scn2aDjZMb15LXYhMf9PsisCUa1mLvb1iaKymfLuGnxTxELXuaJxEsluLBAYHuSgMTj3BB/2+nUtrVrvyJfp4Tr6G4tRy3EuJPo/gNxt8Cz+EoI+KwVeZyZxD8Ii+WTAc/i+AbWX7oQ+17FH+DR2Mhp/N530DxP4b8fDrnUvxPbXzQpv0Cin9I2oYntDeZODU3uITinzTxcr7kCmpglxPseb/8Cm7montSx3EFjEWvDustNvJ9AvZZG1XfdFUefWqcvprbzjUwNzs7V/ZIQu/jubRtfX3GSlfu6Cl/bCZe1tJuP5BkC7hmJbOUBI5xUaogu5nSEcSlbXkmG4zva09EBQLxMYqwbt8YhGkSkw/gWOCl9WAdx/s6PQPi25bFBsQle7tN1Qs25pdMtBsVkjigTb5ROgbAlnfHu1OcI53OKWEyoIViIL1s2Nu4a/OkXtz2DPsLK6CB+Lq84d1jHItzYJjrXm/TW7KyH3IDzp+G4be8NGDz1dLQQxbdXX09Zn9HfJLdCDRpftfdR3v6lpr7SXRgTxzfs2Zd38Z76j9iXb9F9j6yUuPeDu7F5DL/P7Y8uhRzme/bkG/ZW1eUbEHSwMAG6bdq3nw7l+UOaLcdsIa8S7X9u/PoU23/p0zjHjWXGKHyupfx7oO8rlGyfoBpH8KyfpDTPKRon6loP8J4P2e82Vgn/8V+hF8vv4B6qfPPkUPrRRNzFZMGGDhnjvOaNJbL58xcpl9xmY4OtJ9e8aNi0DON/27wRZzL85GVHCd3TN0cRcIRnsPMZhvOzVCm/B3wixlq170DtqCPwzqOfsu88AmlB0+yvvyW9yW3sMyeAh07T+nY7zjNCJbzM5zmWUWbaAZ07HnGewFof1WleZHTjOL580uc5uW84b/pV9lMCjJrYbO7UZQGxnJ6hen+7L+y+WVLvdYeGRNetXNV433eXvoS3HLGZRNhGEN8OykHRzoTaVwTSr6Nlt1XcP7BZ/NdmddwT2EH3sCfjm1+B/au/Lb+BrT12dzW38S2vkP+JZ1+1Kt9ordYP/4kayi1/yZPc0IJMBr4D/R5/4UNsy+Ht0P6vHcGH4uq0g9GAqQ8pC3LOPOuGmfey6NPjTN/Y1m9L/scYTaOLb5d4+SDLBsQ5jazFPYnP1T5fpRHn8p3K+e7TeoI5LyddeTL9mOQ7SyW7T/DZStkQKoYLecQLXCu/6nqlz7jMi3hcfVfXKbPBY/SQH14+UG5jMh3H8olI9/R2Ck/RaNL7VWN5DSLuK/N4jSj8oN4i9R4vjPj7cJ404e2ezJbZ+Ebalzvu+UPbUNlnTnQolSR0wDR4d0dTTnzG51vaFHeYEO6B8XRWNzmx81mvY3kg97ukA2Xk12nkl0uyy4vfzBbrbbuPrUOhBjxz1OQn9KpQqZn8irKlz0Z4aMoJzj2leQDLD8IG0NhX7cojj6EZ3h7Clz2awLwLzK98ZKX6Kakn5Q=
*/