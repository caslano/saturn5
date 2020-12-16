// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP


#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/closing_iterator.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{

// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4512)
#endif

#ifndef DOXYGEN_NO_DETAIL

namespace detail
{

template <typename Range>
struct closing_view
{
    // Keep this explicit, important for nested views/ranges
    explicit inline closing_view(Range& r)
        : m_range(r)
    {}

    typedef closing_iterator<Range> iterator;
    typedef closing_iterator<Range const> const_iterator;

    inline const_iterator begin() const { return const_iterator(m_range); }
    inline const_iterator end() const { return const_iterator(m_range, true); }

    inline iterator begin() { return iterator(m_range); }
    inline iterator end() { return iterator(m_range, true); }
private :
    Range& m_range;
};

}

#endif // DOXYGEN_NO_DETAIL


/*!
\brief View on a range, either closing it or leaving it as it is
\details The closeable_view is used internally by the library to handle all rings,
    either closed or open, the same way. The default method is closed, all
    algorithms process rings as if they are closed. Therefore, if they are opened,
    a view is created which closes them.
    The closeable_view might be used by library users, but its main purpose is
    internally.
\tparam Range Original range
\tparam Close Specifies if it the range is closed, if so, nothing will happen.
    If it is open, it will iterate the first point after the last point.
\ingroup views
*/
template <typename Range, closure_selector Close>
struct closeable_view {};


#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct closeable_view<Range, closed>
{
    typedef identity_view<Range> type;
};


template <typename Range>
struct closeable_view<Range, open>
{
    typedef detail::closing_view<Range> type;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP

/* closeable_view.hpp
c6Eg//22r884zPjnmm8F+Zas1C9dHnze+Abt+3rH2fGc9rTlNPob4WTnWf3HJMdp0ndt15+Ua5J+w/l2Y7r2X6w+K9fD19mut+qnZuqnf6R+x2o3yu2pb+hvjyhv/fNB/fvcNwXp8b/r923H1Y8E+ZYdU04fU+9K1PsM/eraID0So7w7le9tQTpnjuP2Lv1ygv+m2CLnpQmOc5HttD8HttueV1nPauvR7y6bpN6pX7O6jUscx6uH1bt1+j/bsX+l8jU9MMV+7Z6gPjuv9apPju/SKUG9K54NPu903tn4vHp4nXqpXh84qJ6UKoeN+sfttjPW9r3BdcBH9YPz7b/x1NqHbfdC49Ebfe8O/Wexcc8G7W+b6cOmhfq1OO3qQeflDOOLnc5rU4LnR54wfrEft+hvNpdZnnHV8dXe73Z8/qY/jQnSXbXmb/I371e5nrjH+KrTcbndeDBTOX8yxnldvXuH8WCx/u836p96dOFm9Sgm+Lxfu9zwK/3wa/wNvnq22/G+8JHg887z9WdPGv/oT1Zd6rphl/7lMvX0lfpP+3VfunHvEu1PfxmTYDse1f/e7PvK90Odxn3T9SPJQXrccf6Q47k2zXn9J46zclzyhHb+Recl63n+Ltv9A9tzQPlOcf59QL1Mcx7t046ejcQB+sPI+jPbeNNxel79XXiG8cJc49avOA9+QP/rPD3bOOPW1Ej8ODG4/x7XDSnaQ4/t/LPt+Vko6N93leNrtTfjgWnGq9vq1dP9wed9Z7t+e7vlT7Ac7ezqH9mfz/rer+3HvcbzL7oe/rHzUqHymKsfi/jfu5X/2foF9XFzkvr4R9OIf/D+Cgj+7R3jJtMDO52vldekYsf9uHH6k9rXRdrXOdYb7/sROzzD93L0Y9rBtd93/bhbe5ipnFx3zzauu2Cm/av0ebP6Xarcv2Jcoh9c+37nxUn6j1H9VI/y0T6udV695rDz0JvM7/yzYJJ2qZ/dUxU837/A+U17W/BH4yb9xa4G43zjmhUT1OsrtUP90O5m1yHOvzudp59fqR3+Xbn9znbq34+cp10UKjft9+AE/W+77XzM9lxse9XLRx/W/33M+z3qlXH9HPXs2jONEyY7znc6bqYHn7b/rpMOGeeuWug4VNnuB92vKLSdfl5W7/z0uHJyXTTJeH/NfO324iA9+lnjlO/YPvdtVv1de3Vf4Zpf2P9E/cPZ9jdVeVyvv/iYftT18nb3WU6sdd4b0x609+MXug6yX3PeqF9L015t561Xqo+z7N9M5/U3B+l255ND+u1FRfZ7luu4G+3XBe436Ge2rbHcOOV1g363TT/8Zu1Ef7Rzqu+9yf61uR+1Wj1JUn/S1PfPKqcJxhmfMU54lX7y3fpP2xvj/tAe58UlI84bzse3zNHenf+2lqg/EyYG7TpgfBqj/1f/lqYZ599k+TvUH+3oQeUwa7fl+nzTZj8/oh29zn2S6x3HM60v1fE8x3ZfoJ2/Wr190na/Xv/+VfVkneueNu3C8d/2E8dtq35EvZx7wvn9UdenR4xzlusPMtTHecb3+u+ncl039usvHlevdvr+p40T1I/j+p815frNneZ/zrhXf3r1M9rNcp+/4PqmT/940PngXvXlT9r1DepFk3qvXO41nltT7Xz4Hes5U7/9Su3CeH9XvHIv0z5d5xxSjw7utv+Xas/fND4zfth0jnbRrpx/ZntvdB6Zapyy1363a1+X6wcet/6njBeNKz70Q9frn1K+33e84hz3c9130w53Ol9vjejxn9Xfd9n+Rtsf2T8pU25J+vWQ8Yfz99Xq4zU/sN0/dJ5SrvNy9LdfU8/eavuOKb9i41bj4knD2oH6Nyeyv6Y/XbRXu1A=
*/