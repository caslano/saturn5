// Boost.Geometry Index
//
// R-tree leaf node checking visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
struct is_leaf
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    is_leaf()
        : result(false)
    {}

    inline void operator()(internal_node const&)
    {
        // result = false;
    }

    inline void operator()(leaf const&)
    {
        result = true;
    }

    bool result;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

/* is_leaf.hpp
fL8C4UkMy7NcLneEx4lZMglvBFMgu+YSnvzpIb2sGcbdo7vFrodIMtYBejGsV1/xrkjoxQXlIuuDQDnPXuuNGKEWdhdCAgZqUuMOnPeYlXvdHMyJkiOIEqy6ZWhP+XvZHowkJBSgXawR3DRy+9Jd6Q+dbrI1s4LrmKKLBbKk5m8xi3AGoMmbRhSHjJwNIz9Ku1s83TDYnkl5VTuMepZotgunfswH2BX8tMDXYbBoW70QRpMXNWkr/ppQMd/zLCWa2sms2abZP9pIevmXirGTZ/1KtsIOY8uBrzVDVgUEN+Vr15PFgugmJCjXcao96yLxjs9xpu340awbMzGuh/XYrx+/hH3A/9EJo4GOwx4ojRjSWTbmpSoL2mSNbbpY+5soIpYnGlPhMa7wN8ZCXJsUxPYXdcbmxUn7dRqnSFF3hSNdh/o8cgfwPS7ZWsBiPpEKUYznFWmGgK0A9JWZBnoapPGUSULZMDkFv9Ysu4Zrz0X6x1OJXWzbPP10T8pR7drdvVkzsf356EExy6CXY3Ebm1XaWyHc2lvjaUHDAoZUNxnOj3Xk6uT34mszkw==
*/