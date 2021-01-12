// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP

#include <boost/geometry/core/assert.hpp>

#undef BOOST_GEOMETRY_INDEX_ASSERT

#define BOOST_GEOMETRY_INDEX_ASSERT(CONDITION, TEXT_MSG) \
    BOOST_GEOMETRY_ASSERT_MSG(CONDITION, TEXT_MSG)

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP

/* assert.hpp
9dwZW7inYRbCbgVlRudbX5ilMK+XS2vnWzLMWtjfp/RcSoNZCbs6eC339Ezl8xr+PMo+eaEy7sHB/frvHSrj6qxsxOfpTbBywuptrHsg37JhTsK6/5E4KN9+wGyFrayXGJJvlh31eq1t9NhZwW7cKzBnYXXe3hvP3IUVFva0ZcgArlFHvX5qNii8Es/NHcrnTbfJ/pVvF2G1xLgPqQcb55tnJ/3nMnFa7n5oz373bCe99mhW
*/