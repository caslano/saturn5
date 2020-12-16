// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_RING_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{
/*!
\brief A ring (aka linear ring) is a closed line which should not be selfintersecting
\ingroup geometries
\tparam Point point type
\tparam ClockWise true for clockwise direction,
            false for CounterClockWise direction
\tparam Closed true for closed polygons (last point == first point),
            false open points
\tparam Container container type, for example std::vector, std::deque
\tparam Allocator container-allocator-type

\qbk{[include reference/geometries/ring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_ring Ring Concept]
}
*/
template
<
    typename Point,
    bool ClockWise = true, bool Closed = true,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class ring : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{ring}
    inline ring()
        : base_type()
    {}

    /// \constructor_begin_end{ring}
    template <typename Iterator>
    inline ring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{ring}
    inline ring(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{ring}
//    inline ring & operator=(std::initializer_list<Point> l)
//    {
//        base_type::assign(l.begin(), l.end());
//        return *this;
//    }
//#endif

#endif
};

} // namespace model


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag<model::ring<Point, ClockWise, Closed, Container, Allocator> >
{
    typedef ring_tag type;
};


template
<
    typename Point,
    bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct point_order<model::ring<Point, false, Closed, Container, Allocator> >
{
    static const order_selector value = counterclockwise;
};


template
<
    typename Point,
    bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct point_order<model::ring<Point, true, Closed, Container, Allocator> >
{
    static const order_selector value = clockwise;
};

template
<
    typename Point,
    bool PointOrder,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct closure<model::ring<Point, PointOrder, true, Container, Allocator> >
{
    static const closure_selector value = closed;
};

template
<
    typename Point,
    bool PointOrder,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct closure<model::ring<Point, PointOrder, false, Container, Allocator> >
{
    static const closure_selector value = open;
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_RING_HPP

/* ring.hpp
W+F+uAu+ZvIFfB3uhW/Ax+G78Gn4lgknPEO5fAm+p+vBD1nOXcPkRa03K1q4a+k5Oj67Xq8Kq8Equk8pEzaBWbA7rAX7wNrwUlhH940089n1S11dl5ut+8Mawu9hI3hc9Z1U9dOwsc+ef8v9D3tnAh9FdQbw3VwEEiAJECByhEtArhBOERUEJSpHFISI1CQkgQQSEnNAUMSIiKioKaLGioqKioqaKlZUVKpUab2wpS1aj1htRcUWlba0pcd/vv3m7czuLAS1/fVg9eOf713z7nkz8w7YHVr6ADgMZkLL/Sg4FJ6p+hTRdd6iObMW6nNjD+v+Aq3fWp2PeCPsB9fBofAmOBreCrPhevgI3AC/r/pzav9jeA/8GbwP7of3wz/ATTq/8AGYBh+BGbAR3qH6Xao/ovqTcCt8Fj4FfwSfhi/Dx+EncAv8DD4LrX7vOZgEn4edVe8BX4B94Q44Fv4Ijocb4RnwJajvE/SsQ9Li8T5hv590wINwEPwLHA7/Ck+Ch+AZqk+F/4DTdT3feaArvMBSYR6MhgVqvgjG6ji5HayHcTDFuj/o/S4FUqfE/hTVz4KpcBrsDGfCWFgAu8AFMA6ugS3g7ZDr6XdSPecO1nh8J12CO0tfBrvCy2AfWAcHwsvhcLgCngivgmfDNTpeuAGeD1fCC1TPU/sK1c1zYmkgHtd7PCc+2YbyhE/D7vAZ2Bu+CIfAbXAUfA5OUvPz4fPwQrgd1qh+OXwBXqHuzHdSvf4wj++kFT6djwI7wko4CC52riMsi/yd9HzcWbwQxsJcaD+fpqu/QR7Pp0+pv22wFXwOdoHPwx5wOzwe/hD2hy/AE+CzcKDq9ng9z76Ox3j9R3qdl2ES3AlTVe8DX4F94auwH/yxho9unns2aPgjPZ57Fmj+LdR4lqr/MjjU0jWcJvvcK/iFhtMZ7rbn3+g6yvehZd6k6f0Ajoa/hmPgR3CujHd1XR6sgn+CtfAgvAz+Ga6CH8Nr4V54HdwP18Ev4K3wS3gb3Ac3wM/gg/Dv8FH4D/gm9Pu5T8JY2ASj4YcwBn6m5qbcywPpHO9R7j30ebwPTITHw7awL0yFA2BnmAHTYH/YW83Hqbm9zqVOr/O6xzqXrq0D5dIdDoc94EmwJ7wQ9oIFsDecB4+HFbAv3AD7wXthf7gJDoAPw0HwBTgY7oQZ0F4nVF/hrCfudUJztZ4UwOPgfK3nRXAAnAcz1Ny+rzVpeKv84fe197luB/gh7A5/o+n8GJ4Mj2sT6Kc/RZ8DP4NFqlfBffAy+Dm8Bv4OroW/hzfD/fAO+AW8B34JH4JfwUc0vJ3wEPwtjOJ6n8No+EcYB/8GW8A4q03CNjARdoCtYTeYBPvAZHgSTIGnwXYwB3aAuTAV1sA0eDEkffp+Xs9fge94vJ9/lfh1gm/AUfCn+p7pZ3CC5QdOhz/XfPkFlPc08H74lqb3bfiyutd6ruej0Cd51PNftaVeW+5hX/guPBW+B2fB92E5bIJXwQ/gnfDX8En4ITTr4qoD1yHfwtbFLdd1qqvgOfAqOBteDSvgGngjvA5+D14P74Zr4UZ4I9wGb4JvwpvhbtgA34W3wkPwBpjsJz5mXaieCwFv9/i+tF3Xcb2g44gXdXz4IzgXvgTnw5fhMrgT6noxPeeAuuqxXuw13PWEuzTdb8L+8DM4Bv4MngZ3w0nwl3AG3AOXwiZ4qep18G24Er4DV8N34Rr4HvwufB/eof7uhh/AR+Gv4WPwQ7gFfgR/YsUZvqXx0fTonv6yNjssPY/pfNAnYSbcCk+DT8Fsyx28ED4LW+P3h/A4+AIcBF+EU+AOOB3+DObC3TAf/hzOhzthLfwx/B58BW5Q95vV/SM=
*/