// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/strategies/cartesian/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

class cartesian_multipoint
{
public:
    template <typename MultiPoint, typename Box>
    static inline void apply(MultiPoint const& multipoint, Box& mbr)
    {
        geometry::detail::envelope::envelope_range::apply(multipoint, mbr, cartesian<>());
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<multi_point_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_multipoint type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP

/* envelope_multipoint.hpp
2clsqgStvRxp/9m6phqpa5x5f9Yt72v1PM12ZEk6WaDHeYivt3kbmc+vaM6XrGaMrDv1hjZc1lPOH4sv5H/yffGuxDlidAfu1VW61nO2LcOWRUlUSmXsrLTMhFR1PYvraf9S4rZupa56L132Z8P5WEZOuud2saFpH1rfUr5530TdLhegn7Jd9nqml22Szf6j1TRqe4l6jgN+3q5tE+xWx4ea8lzqWn2YXa2P9W1F/ks7ufUXks8t1bwds490NmB7pZm3l7TrkrZmrbT+ihkfT+F3pLNkv54HrLMjx+7aYA1ow9jM/45Xzce4QrftF2axrSJlmKn9oeH401bqRntb8zEjogHHDO2aw67nhVrfh8u0nvV9w9q3WLfTqLvdiHX7irrbdVi3J6m73Yh1u4u628NYt0upu32FdTuKuttLWLeTqbv9iXX7n8a3P2lsOxPr9kV1t6uxbgdSd3sb63ZKjW8fZd2+pe52Mhd0VIYXTbnuyfNtrrivpPXU9zfnHX6l8e2gzjnbq8i9ALlHUE5c5OwLSf3h4iHvErwCg3EYDsfhOApH4EQcidPwalyA1+ASHIWrMVye54/FDngtjsMIHI/X4WK8HvNxPO7CSKzECfgdTsS/4iQMJq1ROBin4AScipMwGqfjdIzHGLThjVrfU97a9TDlQdY7SLl2kPqfafP8MQZH4QyMwJk4BW/BmRiHSTgL7ZiICzAJ8zEZV+IcLMY03IgZuBXt+DxmYSU68HWci4cwF4/gAvwYF+IXeBuewTw8j0vxe8xHpf3EHfg7LEA/vBsDcAV2w5XYCwtxAK7GIViEI3AtjsJijMAHcQKuR2c7FB+5rpLrLSX/lvFvnuXzo7bL6Yu3YjAuQudrlZiCi3EZLsESzMdtuAxfwjvwKyxAfyX9OASXYzTeg9m4CpdhIa7Ce3EPrsaX8X58H4vxDD6ALUjrg9gWne0r8CHsj3/Aq/FhHIclmIAbMAc34gO4Cf+AW3AXbsVD+CT+BZ9CpU+Gp7EdlmEQPoOR+Cxm4XNYhM/jc1iOh3EHNiUvd2Ir3IUjsQJH4W68AfdgFr6IC7ES83Ev3oX78CF8CR/G/ViBL+N+fAVfw9fwI3wdz+IbWIsHsAPHoIPYB9/E8ViNUfgepuMRvB3fx1L8ACvxI3wVj+EhPI6n8RNsRz38GQbhCbwMT+IYrMEJ+CXG4ylMxdM4H8/gvfgnfBLP4m78Bt/Fc3gG/4xKH6jn8WL8FnvgX/BS/A5HYy3OwL9iFv4N78bvcSP+gNvwJzyIXkpfTOiNf0EfVPo0bY6X4gUYhS3wdrwQC7ElbsdWuAPb4CvYBY9hVxxCG+GLcTp2w5nYHeMxEOdjT1yHQfgo9sYnsT8mtmCfxAIciPfgZbgKg7EKQ/A0DsZvcBiGKN/WwRtwBE7HCZiCE/FWnIT3YBQ+jJNxM07F1/EGPIrT8Gucjl7UDzHYFm/E9jhD63PCW65v5bpXqUf6K/Wo1MMXyDc3fHEg/g6Hoz9OwLY4HduhAzviWgzADdgJN2Nn3IZd8DhehD9iVxwmfVyOx26Yj92xGC9RpsceWI098TMMQtLi1Qu7Ym8cjH0wDkPwNhyMt+NQ3ICXK/PDYbgfQ/E1HIEn8Uo8jVeh0s7wamyDYfgCXoc7cDx+hJFYgxPwFE7C1krdjJ1xCl6JU3E0Rut9Zsq1KiZI+zhjn5m7lHKIL+I4rMQJuA8zcT/Ox5cxD1/FS5nP6zgI38BxeADH40GUPh/l2tG5j7Fcc5+PM6WvzFuk/rfhOUwS7YRcy7GNPNN9SNL9Nk7FDzAFP8RsPIpr8BMcqLzvgmPxFF6PX0kfPl7k0wXojdIXkVw/UbfIco19Ed0=
*/