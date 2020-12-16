// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_INDEX_HPP


#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

namespace services
{

template
<
    typename Geometry,
    typename CSTag = typename geometry::cs_tag<Geometry>::type
>
struct default_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Geometry>)
    );*/

    typedef geometry::default_strategy type;
};


// TEMP
// Utility to get index strategy from other strategy
// In the final version this utility will probably replaced with some other mechanism
// The issue is cross-dependencies between strategies
template <typename Strategy>
struct from_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Strategy>)
    );*/

    typedef geometry::default_strategy type;

    static inline type get(Strategy const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_INDEX_HPP

/* index.hpp
lOP8klPXH72/nLr91Gge4bZhCh+vHSaz+bBIEGUbfWNB0akeNLJ+sRNjJ2DVTkUYwZQ6JUYplCiFOkphB/rPdvmplN/WNkrlABXO7qjjtV2FaXBPF2rw/WNH6xFbhGt5KvUQx/pKlw72OCY9IRvJptSUWuWglsikZJXK3mSS1BivogSNI5Pb5p9JTmxcYY3/eeGl7+yh715YhR93wlfchZU1kiZ05hau97HHdwLMQ9DK1vaN2rh+RwZ9Zg+Rlj240Tz9VOEk5XsVCymBT3TcqW4+kZsFVmX4RHWoQEmrfT7RH6dIavsg9KdSvUXszMJktxZL3Oo9Os8rPZznbeJEovQhemTWPQV0UVsB3tjdlAYp7aSOmV6rsIFCHm78IWIIlGjKkFF2ZreS8/cTisudUkW850R6JOdSVsbqqe3OBEpYt6pUbEkWVMfxK5h9yAZyhE2IX/4qrSFdqqgSVaSWV7dPxvJqoez5dMl9nF4UvxBpiKxUjZ2ClP9Vng7kf9RGdwhu6lxZBZSMY/5Ty4PIUv2pu6Z8i+Ckp8LBxH0fx1SvFA408823Z3dFcGto4Vfe9Up2GaC50fwlk9cTViO3SDXxOeSCJPX6qtBP6mJ6/rg0eX3lnto3O9aUS4vnVH+ltVZGtoa6/IzaCeJeFwz6b+9Tc7y2HcO2fto2iG1dtc0TupMX80cTh6pDc/Ew7VvmnUsZomVy/x8M5GH0pDVB+hn/Gt3e27SE28T48I3xGrrd5ZfRws5UrF+HGzYHyH/xn8PN8J9VUEwpBWmAPQT9S44B/cpB7dHf3unw6ZsNUDTXu+53V3nobPKkPsP/j92WPk4QEgaRCLaq32L8+t+lUF48vU5PFmQHRz2Te38Z8xBKmjwlTeUZJU3hQElTJNtcj9hM9z7zokM7WOxw0qnzFtWuF5dnfM1l2cGl7y9YNO+0Lpu0o1ccF9XMW9hlk9K0HDA6jLhRoqcJNGYUuCmX1NZUJlCet6hmQRLlOSVTSw3lbEM5W1POpj5MlId1tIgZpJG44MaNStnuNv9TUcuDscjv+ZvloUV+k/+jvRb3FxmD93wxnjthYyYxgSK2vSKTL9i17VVsL7LtkUy6djfoCM/2PEd4stfmNvu/sZeTs5r8jfTAZeHOaSDCeXL35E7w5FZ4llC4BXtVtiroQZfGp+tJFSu7SPt4tY+lfag3ystaMqslqwO1ZJn6T6QLcoO5ZVE2KVs73+dseZv8z9CDM1ARTffycFX5I2iF5/9F2mOz/7y/qJJM+0tyFE+A6F6f5JpHrgso19aO8KY3guEuO5hHYla9dClLJmmezqydss3//luWx4d0/voWpxNo8r9FD6ZemGJDa5Do9dnm30I+fgR+CoGDtHdID6PAoQvxAZGXsrHSiVxwGD3nf6fB5+Pmn+U3THj6z+Rc04mOpuCry1JnVJhXIWdO3P1XQnzqrX51t9fDG8IH9sVJ4ViHKIkhOZuJLLly1wTGe4CrgPcDHwCuBq4BSviP8fwesBW4E7gFOMUR/jvAm4HXAauAFwMXgtoYYDFwHPAU4ERgCHg68PfTIJ8EbAW+AXwT+BYwCnwb+M405BO4B7gX+AHwQ+A+4P5pKBfwANBzJqMXmEHI9bXWsuuwI3ZeC4lbavuojf/zTT5t0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt0iZt/meNrQ8p3vp82qRN2qRN2qRN2qRN2qRN2qRN2qRN2vyfmdA5OAve/HbuuqnBaNnWffEVfLb7ws2J/tFdL5AfQg2xQ6WmV0Thw01T6Uz9ZPrzNHuaJo/m5+apo6EYADqEbslp/SE=
*/