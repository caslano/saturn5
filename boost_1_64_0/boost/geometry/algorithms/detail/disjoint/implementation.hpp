// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP


#include <boost/geometry/algorithms/detail/disjoint/areal_areal.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_areal.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/multipoint_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_segment_or_box.hpp>


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_IMPLEMENTATION_HPP

/* implementation.hpp
DHRUqell37r7huUtnON9hOGk5yeSRX6G/paGpfbn732fdXFd+uLnz01jY3R5V8zfyhRLJfMJ3gk+f9Hcss8R3SWSmfmVe18iGB9/4BFmg8f85hAd80vxcYnYnjF/v84I4empykyOBlS/3AVlX94oO+QSIx2JVAfRMK6SteVtZdsk6ZaX3w66O+j/mhnYZtPUNs39KTmKnEEyyHtW6bwxmhmnY9l8PhnLuIHVsTgEWuxb3DZ3kcx3WVuBPdyl+s9dpv98Xdk/474G+79b9Z+7VP/5huk/3yyR/1suv8HZ/gI7uwd29m30iXstT2PjqIfY+Hc2ajqRPRL3LWPjD6Ds74qNg97Y+NWw8Tsd3Lfnr87Annmv4X2OzjYq8SBbv59t/VCks/nvWZsnW/5+tC07ezqSbPgH2oYP057aprbrsK8PQYSHs5UHld09aOzux6qNGfcj2M1Dyu4eVHb3U2N3PyuR/+fIb3Dii7Xd/QRt/wv44F9ansbuUA+xu99s1HQieyTu58bufouyfyd2B3pjd2+0vpXs6Vf0d0jtsKVfw28qhLOj30f4zl/P0Hc+XMLe2mBvB7W9HYaN3KHiL1RHib98RLX9H03b/0m1E9M9irb/M2SxODtG23y3ReLs+I098rCVv+L/v+H/v9P/qIPYxz83Kl5eCfmMjaG+claM9tv6bd8SpusqtV8nr1QdG6U9A26SF4XAN1m2PchibO8jZHtHLvS8PxCcx/R/0P9hm5vjPXaoj/L+hTpdUiR28DKqwzyC7x0P4oFlXrmDxdzmBrbLf83QLue0RNtlE8byihZllzOco04znrv3RVxeSYVtubIF9ou/tb+b11Jsd8bNbfFt70jISXSUR72f1hK2+WNK5D8W+Q3O2LXF2XkplU9w/v8JTgZqb07zWsKWa+wQdRWbX9Ci6aR+kTjILj5xIWRYFJRZqeiVXb4qYr45n2ikWeAPqwl2iQB9X3gcwYwvJLqZ2dzxU9jcUWRzNdrmZmg3vdPYHIfGY/TySyzl3uwQNhah10uLlR0uNna4RLUn406ArTxZ2eFiZYcnGTtcWiL/ychvcJHj7olo51NgY8ssT2NjqIfY2PIWTSeyR+JONjb2FJS9QmwM9MbG3gMbI/uTcfdU+juyUf7g29tpYm+GAGuYp0bY3mkztL3TS9heL8bhp2nb+w/t5041b7vTzNtWqrZi3Blo/2co+7lTjd2rjP3Ulci/GvkNzozdBhfhx2rRvmvgx9bCxupRLufln10nWd7W/u5U43pTi6aTukfiVhv7Wwf51ov9BfTTr6nPJBq1sHRrkIaW6dcgbJuNsM0gM9vjhgh7bJyhPTZPM/5u1PY4wzVxqXc/tmBHHP3h5izu3XvEwL3oGDhi5rRvkTfbx5O4ONffL9DK/pFmIQkVc6+x3zcRR18SEUffhnfv21qi4uZcjsmCqPkUBKXf8ngc+HKf7FA+vbOlGJfvail+Pwq+K25y9XIeom8sgivto5AzIZuVDioOldV92lVSWpSTT8tRo+Q4awZy7IYcZ4sc3GanRpcW9SlwZqROzjrIlXelTIwm6YY49R1cp8n29rj0csTetyj5jomw6Ur2kF6//2YH2mdl5NxAPqC6XiQpfE87R8b+Mv5b2nzQ+OEh5YeZbgB+eCvkBC/xedtbFJ1XpANvWa8sA79zjQ9lXK3CKR5Y50TlMzLOYg0kerFrIEHYNRDKMH74Z1gD9ROc1zvbWlQLYA20Q/tRwHYSbDyeG4/xRljAnqnpNniHwE5WsOEEXWyNO4+eRWkK0bPvlXQ2vjdWhC3wng3dXFIUzq2vztPrK/LbsRJ+m23tGPLb/2bvzsN1KtcwgL/f+sypzIQ=
*/