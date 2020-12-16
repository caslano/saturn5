// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, typename Strategy>
struct distance
    <
        Box1, Box2, Strategy, box_tag, box_tag,
        strategy_tag_distance_box_box, false
    >
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Box1>::type,
            typename point_type<Box2>::type
        >::type
    apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

/* box_to_box.hpp
9ZaJtYr6BzbI3yRxT6c1riLmGcctxOU34qqt9YnOJeTIIbqP7394nfm1x8Hy0Iw6Ren3QH10hnPiDjW665HkQgk85wV+flr9+KGWGmh+S/vE7LWFtWx5eIpa3VpPDlv76xXzzKOhwcfR8nhHXvqdeT1FN70RDifemdpITnaHrfnh54jO7kcRq7exxxHffxr/LJMPZjbWA9SnyYjRZHXoJzw3+9P60IOJZ33i7xfy3QPmGIPzznntMPObYO+pWP9ZH1+okHvA9tOMc9BC1fRKasWoJNdN3EP6On70GYyrSkPdKH+GGNeN7GdcpfW5ib1Q2Taw7RZ4qp4t+s1caY8FXL+9Xjb3HeJTTB9jiyvY95cs6p7+o5n9g8lqddvLxGlqQv+Jh6n3ib2JsC0zuxfVj2aDezSfVJrEGzmtlcvLNe5F3k6fKV/IfsZ54m6s/Z5N5KmYbLldn1SI/iFu3rZPtG/VxPunxGF39Qv/H9ZHH53EX4lnTtWhf2zk21/UIjYvK8e3bk3cbwl7B7AXG3S5ExdQW8MSkEbr2cPu68VA07vtGxWPb8Glxi+pf8PUOHH7ywa9XU64nh230W9WLqi2fKFvXgH72WHuG4k9Xziw863qQ68RQy+UUoveMraH5HUazt0bz06sqYurs8bgUTOc97A85LPiXdWuNsYC4/Oqz8Vct2drOen4A/31Kan6YnrxTj3TurPUr4ryYiKso73XOVMvK/Yfqx/c2423y5OHT8CvDmyVZN3PMV/1oDUO1l/OoHknntUm94o8RYNsz9+N9Zi94EdtvOo7/qKFNfsKjxQ/NxRI7IGVp3XU7G4w/xj+35M20tA+95r4Oz9k8m/OAXrr8jB7tTyS7zvGsVNRmNmTXljaeao5pz5v6J3057X8gEMOrK5nycY3auOZNdQoGHQNrIzxfbm34a46lDvBG6fLe9/d90eS7jo+y3IPA/i7DSQE6UZg1AGR7u4eIIyOwejubkVCJRSUGEhISigljcQBBCQGSHd3IyF1vjv+sQ9se9/nue9fXNf1u+5n20LrfUgHbqMPY36+Ro2dvSBmZtUcGenHOs7h6IAN0eb3e3B8m+ddRvOTU+B1setX3fXCxeIQ7jDjzKkujqf5Avru09J6uCNcqKGn9XLDVK4hX7f0iLk+kFUPV9LT28TrOX07bLCcN/T8uOtlOq/WrHe2zxfr7ZzmxQ+Pqf0s/ISnau2Ze+vfa6msd5+6TUU/2lvnnUE8PR7Qe5j/JsbrCYJTfBn5Kvgx/C+G/9IE/v+zsIXNFkPE9i18W0FvrDnD28sI+6+7znU4J2+htEt9PlxwkJm4KBzaaO1icGI6TscdLcU8rn4PXw7n8fk+dX2VzhntWvtx8cJhfKfFOJiHVu6Kc81r4mLuPBZtz3r/cT/x5Ad8wHeY5b7j6coSH4rjp7T2Opiz22tp70JbzRF4YVw/nGWmyj/YteiDuXX8jhjr+TmXZ5vC+RFm4iG81rHOqVM2V+Mx556+3o9+7oxjN/Wgryvz88Qwb246mV/3bVf9rq8mwMQ/L8Af+JdcjnoMoGsSBdHrMIxuD88CP3bJ5yp6Frbeood38o13tKf3eFqPW+qdoficnkoVwfMx15cpByvp04V91QktPV7fto+iObqruUvB/HwaF681hmlh/p8xs33RdDm+toa2NEY0fqdF++r1JA/0kjpqoMe+nsEzSQsTFupHGqzXMLNkV/H5Qs914Oeox8FLcUopmpTOibbmFM1p9V/MjS1po700As2QQn6mTFH7cDB0tDlgtr3xd458Zwa4ZQ4Xt3eT+YZV5VIc8zfmVdvf8Zx0AkzcF8yXCZLbx/S6nhkjz59s1lNm5kXl4EA=
*/