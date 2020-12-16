// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP


#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/visit_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template <typename Point, typename SegmentRatio>
struct traversal_turn_operation : public turn_operation<Point, SegmentRatio>
{
    enrichment_info<Point> enriched;
    visit_info visited;
};

template <typename Point, typename SegmentRatio>
struct traversal_turn_info
    : public turn_info
                <
                    Point,
                    SegmentRatio,
                    traversal_turn_operation<Point, SegmentRatio>
                >
{};



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP

/* traversal_info.hpp
GO3/Eknir1yTjpOlSLqC+8ZoagAsy3KEOkkxlbb50Ypoha84C+LMlFEZXEwxgJPKPWpb83QQQzTxvdgQzdQvX95YpFbu4iBchgLQt6QzUiGs1s7TThXXvw8g4LOkawdpRwQwpF1WviHWEYkMJQQG9S2pgSX02YqOalSKjK0uZqwSsz/w/WrN/tdzsfbVHy/7brwvCaSAeOjtTZw0XYa8JBvVPZCzkTZK3UM38nnHoFal138mqHYJ01z+mso/PC3DRq2UZP2mNIRoq0XSukIgUTPzvUCl1iJL1DbCKXc5VtLE8D2ON++z3GSOKOyolZQRNtjEF1qx+590ozyvMb9b90xYQ3X/JeHJLTgWE+ikdyR9cnMyJ/jVfKOdV3pHLjORHSuL13JJRtrqCbVOhJEIedS/bdBWHfQtlbGE6i7teBN+joR/9e3YpD1CX2hNIS/ZJlSjtw74Y+z3q48zxs8lxq9PWWGIpb9uFyXyzdTstyVT5NRKC++WQhb68N5gMkSpoWiwS69Ah4ECozvy6n3iP20ORab7s18l8zN0UvmTqn1rpBHbD96Kte8x/c0KhxSeMAoiim07gTNqiEtzRdpGtO/laXxq9ZB0cfCtEUlWg3yeqvfJtUlWJwveKtAs/LVNHjl1DcOk3nzP3IBKEgo/G5lJuEqyTdpiNmDUcgPZog1F2eARkA0qpNrwRNrxFFY/K02FslgNCj+jXNGzPHz30yL3wRQCOBXH5nmkOD5hVxPgAEmjQ/Lhfek/OB74n4hi0ErYrzLUit9/PbYxfudb8Xtir0TY02j9vuLYuPPOKv35Y5hFLTv8jmMlw0C+JzkEnTzUFUplxxWil4eyC/lAYLQQ/Ru6Oqjd7hXThiaq2Iv5ZRHyKQq0yGZOv8MrxRB76Z5xOAuZAzd5J/zR5gTwH7QGtob31SxcKXfv0W/GZuFAffjrjbaGoFYBVpfYHO4Nih+NP/ryjx2Wx1YP4fIt76/THfL+2jIeR/QWfYn7Z1xio0fFLfTxDsEM2+jiLTQuoe3zd9txF3R3yTj8Bp1v+qKfauH7nDbFXJduf+TBWFAwos2Xq2cMiD3qa1sVoUMFiivRB+FnahGvVRngX8NrcRMiFuQrKzZveKccg6ifCZHz4C5xuws/HNbSje0JIISc8h2lDL9qDMd8vbzfnbIeUTZhqX6PfUZKtWigPb5BwFnDHNDjWvHfzKar+aL5jmRjfUea0N4Ed8CMoqBsPyM3rbQUxYrbpgAtUUfaqBiteJ7DKGKJI1aLMBcWLoSc/c91E8tNL7rndRfubkhPCPdioRSPzpcJIawtHWrtAf/vM3nfjM1GayPR8Zqj90Zj8XqT+CDjiWUKf7F3klSCvORFP9pt1+PrxTeI72P4Povv3/HNRaffgt/z8DsRXw3fGnxTMLtOwPdHxHWDfxjcto6NPnb543AaAbh67pj407qjK1FwmxTT2dYS3K497qzX/Ld8sP7ajPtjuqqaWU+7pRmnGA60ZKcULxF3i0UnYzErXSPJlME0Va3F2ChPM/HvlzYme8NLa2yckUxaoJL6GiV9lklPSZA01cFSh5EYE3q566GXOzA6j7MKk3kA8wo6mcMam8oMpXy52sncuScCNTCzrXlyhzbVuEdjJaaFKuYzCvnUL7bs6MYunLzLIdb4CiHcjRzhrlH89I5MORYpyTysm45Uvwq5nXg8Y/fxTYZUnX97GvwM1l2Qc3fl2prhZxSK8e8Z25PLpi7ktsyL9ztWybFb3ZbU6aVlgeVos1ef8YrZxZT/KWQX+7ChjuOic2Jnsei0o/stsQCF/D+KBV+IJmfop7wmGT99wLTVR5jv/J6Nf0jS6jwbVgNL1ty4R2U=
*/