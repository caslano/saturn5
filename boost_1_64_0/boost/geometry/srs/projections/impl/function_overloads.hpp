// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

#include <cmath>

namespace boost { namespace geometry { namespace projections
{

// Functions to resolve ambiguity when compiling with coordinates of different types
/*
template <typename T>
inline T atan2(T const& a, T const& b)
{
    using std::atan2;
    return atan2(a, b);
}
*/

template <typename T>
inline int int_floor(T const& f)
{
    using std::floor;
    return int(floor(f));
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

/* function_overloads.hpp
x+ynIJc+6I56L6VDzaKB3p2LAqMkmcl38+ClVuhefhkvxJ8UITYolDpIGJ18EffsziajwCPdpp6zJb0THE+XuY5gSMHhFCOmmxg37k/oWR4o/qYuov8fjxEwOUNVy2wn750diL5zdHxZ6608pmzgwJpVo+3tMcrOugYDLapnGVaEsY67tOrrvuogJga/LVmFFAtNaPgeV2V8PI7x2ZXHfzmgDF2qXif3kF51cimFSBVKnAS4m7bwKS3QlmfMr2pmhMv8eBeK8el4tT8SKg4tj/McHqt12y9UT/0XvypUj6LKo3vbpIkfKSsj4OoFdyKQgYm6bVm6rB+kYyot6mo1PXHlsIdT+GUJlOJAGGYr7KVy2VZnwqUjm34qyJ+ufK2m3K9JAgtjCkE3mnVqcOasnkd9xLSAuGje9wwacV+DVyVl/RCaRW6ioLV20mdSbHFozqnxkhC/8NYTJ64QQAAm5EhwmOuNJkBEtmuSy714zDawTgo73Ma3RTbshMuqoh0sgMSb5/rKlxZc77dYoxUJHbdSvPCig9STuRz/YVqHJCYWCyB9StduiuL7jg==
*/