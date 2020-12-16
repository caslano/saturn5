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
FZRWqQ+V4dMaqT7gPnJ6sdPp3eKi3Lnm7f70ukmvsuuG+QIkXF5kYj4Xkbw44WXvm6NW7rZ8+gKsi4w2z6ULlx9TyrJmF5RONyLkCX503d1J3DPcEn8q+y+Jd2AdzYgOX0erwsWzuDxs/Koilpm2U3GvIN7fI5L3vyjuP1sHJS2xEkKM5Hni3jBpmVqWGyG/xb3ruGuvwuSrjssmWYeTID7ikYvq4zNcXMrou/I4i03HhUlZRXr+jviJColrsrZLCMn7Qoe2O246PLZ0qGtLPtvzPSVCXd8iGU6TrNO8nLR2ipzWLN/cvlR7erkPxZ+sv8Bep9el7WqLnT+9Yx3aTtW1J8j/QuK1OkntL1+tumblA1qYfEi154PoufazyxpaoS2N492psJB8yNgbsNYhN0+m0criAcmHaNw59Ly0s5MWwQ3KX9M4vfZK6ZmGR+bKLVV6b2epI1avMzp0wDRrHXAu5dT8LHOalYS7FD6s/LVQ4Q7V4d5iKJ0w9ik9Ua3haRkQRlbZlNkFEs4K+IByd4oO55EPTb2eCidThztY1snQXiv9E4fSdVxbGR49l1rO2pZrZMM/Kj9t43xnhnV/31pT0cIYosIZrq+zBj+4Idy/7kdnRGLZ6/QEzNlWywPUNcaa32qUff8433y6CqU313OhNqrw3HqO4hIVh6Y6XXWUnhp6fSmTB5S9S82xHYb7NoYvzg41B3CfuZe4dRaixC2rpHhGmTn7zJfl2m+nIL8H8dsuvF/rR0lOfj6jWQlIn3N5tQpjrNMXbnpQuFWE69X5ZVvDpedYrVHuO+l8W670ITquGUFhHiPMRqqdsoeZxRS/yeWF+gzTQe9ZawxT8eWbg3nju6oN1GEPDgobK1WPSlTYdKjcbTO7Wuktwn2x8r8LN6bOijV1jQnM3Oytw8wMCjM2SsdXrYuReOoy8Uo7+50Kq6+jO21PJbMOWmN+CebnvWOaf+Z0U+JdmONazEyGg0ZD5mmsNO539hb/nCqo6sck14XMk17jXKnyt5XZrlr1Ns6r48A8O2vOXhmKbuc/UmkbTDrQddrGcif2i3hm+P0fWvPMvYHpU0Gr5Om5fKtUHLrFzYi1znK+vb7lVpaNqnxSZ8Vjt1rsZCFNac4s6rXUjX4qL4ocidw3fZBZxnS+d7XX5y/OVWnIjPHoObqEYzWHev7kcNVeXOlYYZyGP8x0G9I2sJyoV+axuNMnTSqT+iprUde+K+MU7TZP58enph2aV/pV535rHUBro52jwLFNzv6ltivzZs6bjGscvjnJnyu/70cHzpf3SN/9iCrbVc53+Yru67OvVeUzULmph/71PlP/CzV+hF6Tk6jcuPS6gUGqvK61wuXXUhWPeuZaV5n/7qtHUbLulRipvClgZnCSXnf6iorrTwFxvUSPJX7/gWlXgW7V3wx1jdMl3rR4B2R9rPabO6W8zNBrfdNUnPOcqx2Xko+Y6bqdFvWw8bFjgstaA1xszbekoMzWyapDO/Hv1XaTppTSQcqyDWWf6bTs1/jqWDlnOZdNml461X9mbJy61qlGmsxTH6zqXF6UuTqiB61kiTHT+IxWZYOre0jbrNb4an2w6zaqwB3ONXpd2+9Uvo2O0feL9FW+tquRtFOlyt3EmOZGFKWeasyKturqtMD+jjDbE8LVyu3QmBtdHZ3NrLaLP2lkaMJyp0w2a/KUnGlWHkdh+wd1P77qGuY6i3sLM7RyVX/uiOpC/ajjaM/38njnO64Vso7Wd0/QgUteLnUQXuB9Lw1amtTZ3irfVjsakCsDkCuQZbSO3xrJKp+m4n++qivnO5+mX5zkOI3wTHPf/fGss55xj9PMO7Ovm6nSeVGM/x6dmVM=
*/