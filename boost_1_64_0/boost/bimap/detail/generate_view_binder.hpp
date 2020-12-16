// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_view_binder.hpp
/// \brief Define macros to help building the set type of definitions

#ifndef BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(                                 \
                                                                              \
    MAP_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class Tag, class BimapType >                                        \
struct map_view_bind                                                          \
{                                                                             \
    typedef MAP_VIEW_TYPE                                                     \
    <                                                                         \
        Tag,                                                                  \
        BimapType                                                             \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(                                 \
                                                                              \
    SET_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class IndexType >                                                   \
struct set_view_bind                                                          \
{                                                                             \
    typedef SET_VIEW_TYPE<IndexType> type;                                    \
};
/*===========================================================================*/


#endif // BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

/* generate_view_binder.hpp
NqtcQqIFZQvmViwo869b+W93WHVnrx++ogXp7grUDfMT0uM02unRXKz3O4Bf6RzE/VXjjsYfe83A2w8akhSvdK3IT4vz5L4/1hw8cXNPz9f9bpH7emZ0Gbyhxdz+ekg/zM/wnxddBtUL5/qVgfwSQ4dI/pR3L7eFyrOX21zpyXPdDqs8josuD+x2OSw09jzXPjdqjn+5Op7BmE4qlxfxV2iXR5H6VnWseHH7wGqjV2Sy6Yefv4IbaXH9sLuOWGri7JCozxwfey7pxPT4Pvu1YJ8dlb6yei2bWn1Mqeor7DfL6hsrSuuh+ka557p5mtKl+X49ul8ojdGVR/wx+diTHi8T8nPy0RSVj0r6gjrq1Lft4b918iB2O7H77DPUKXVTuR4fPifXTQ9iBFY9L+vRfJnY+d2pn8mbpTttA9xD/Hvt+CPtyfQVr2c7uKk7jORZYXL4L7S2fNDYVxmde3di1G+6cnk5GlsyvoQ/dkEPJl3LMDnO+VkFwXyTtqvJT5uGHWkpGRkZVlsmDxdkDcfeUfIKMzHvnRBZt36I3F2Lv+WYGV1C9z/WinfgdpOmDs2ufwd1jM3dEtExlqP1cMqI+rTKiPHn7C3e48+GDprTldxAgb53DmxRHbDsM3tRTUXdEvPh49fm5D/H1VeUdnfQfqo1Jl/gZEtnXI5xO9GkQ+v+fCeFTHbX5sdbz+8lu//WGv/larslmN/gt5jnKk8aw2LGU0sG4krjdwKawDoqjwrPnWzpsvMY1+SnvyvjsMLYCwkVUDh7rIvor7vK+LvI6SWZi0I3rt6urOXBTEwLvkdUPlFjfI76Hp4fNx4W6L7feDhRa+93Y3phbsT8Np9/trrlqfHQ4/tE5Zln/NaqLMNh82gfbpmoDOUmGdQLsJ9s7PMsvwvddjbYuNWrzMJhB8uvxk+Vcb5xu0LjadhvvmSPVL4yzx5mOR8XXc7YrfLVODtW9thx9o1O8d+Cv6ecd0fK2WOctWXcgvfcd5JwrfsmDMmUmTii+oi9x8WPr2/mcz+SrmbHV/wmGF/lLr2TkqGqmSv3QoW3x99ZR2n8lQyRZKt4Zkxf0nh8zJis317OPXbe9TvK+9tcflP9fnfh3rrxuiW/u1R3nAEXL2fyFunPtNNvf1N450H+25s+LNvkIRJG+cBP6+RMYvunTEjc3HPjjsrLdvMvda+xairmj+Qlz86L+17490WfNv7PUt7C4Xt5vkcTXPdct8853djPC/vnmo9wW0QW7pPGPVv2gDPO2DPCbZffn4fXt6j92u+pGds/Q/wa2429OmKP/g2erfPK9R731VjfGCm/iivKfL8r8Xf05zZST4if2/gzfne7aaorq9ULluCbF/+J5zbk3uK2uTa/+XdsePg7Vnk4S+V6OuY6wu9187CouqimbA63o+Y3lHb56+U5f9H23qh+j/mL5su8mfkIV27mscPQzdhaHYzeOvRaL0/TWnkdP3mgu/sG7295aNPTLz+/8NCV2Y91Pqnd384/ejobveVvjp4ux00heaBOy56cnlv6h473rf3J7rL3l/3/6WY8SPnoRTa/05oCoTkrrZ9rHtZ8s+Cm9XNLnqST5Emy4L2wi+yunI7Cpym8K1ci3Y1BZsC2sBMM64TcqXD7FM7WCVmpdfsq2FX2XFgDh8M66f6qly7FJdKleCWcId1+lZITqpd80DXwWng9XA6/IJ1/d8Dr4MOS13gCroLPSF7jB5LX+DVc4+Zb84iwnUe+c5XvHjAd9oSSy9JcHXWgcLZc1p+U7z/DtvAAzIB/Ufm/DbvBd5SOaZg8xddf8bWDExXfNxXfk4rvW4rvKcW3U/E9DXvBb8N+cJclX1Go+Ad7tI9uah8=
*/