// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace geometry { namespace detail
{

// Temporary meta-function to access segment-ratio for a policy
template <typename Point, typename Policy>
struct segment_ratio_type
{
    // Type in segment ratio is either the coordinate type, or for
    // deprecated robust point types it is a long_long type
    typedef typename boost::mpl::if_c
    <
        boost::is_same
        <
            typename rescale_policy_type<Policy>::type,
            no_rescale_policy_tag
        >::value,
        typename geometry::coordinate_type<Point>::type,
        boost::long_long_type
    >::type coordinate_type;

    // Define segment ratio based on the coordinate type
    typedef geometry::segment_ratio<coordinate_type> type;
};


}}} // namespace boost::geometry::deatil


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

/* segment_ratio_type.hpp
NksHc6HhHsWgZTCWCRaolfZkdanRGG4XXHsl1qJah7OY9y/huqdOWsC9NSPQDgrxo0aa5n6T7jZLghYXR9IyTYRcxrI+DHMIYi7TtW8wHNhcYjOuHt2JxzsC1/bJ8fza//YV2lFIi7O0xeV+XG0zI7QcPxLng9iszTZLBRtM4nT1v/cH1h+UQvu8JJ0bo5pj/V2Ee/SkzBqOe30Yx+ufZVtSzp+yLUHfZCwZrCQx2Zag3zKWAeZKTLYzGHvswsl2BmGuQjsjJtsZ/BuYCzHZlqC/gxUkFlC18xubGcGS80n7JsXtU7Q7QnQi4er36TkO8wc2gljZxLfVsTyhRmYTW/35HTz/CZg9/Ersq+ehPTAP94ToRmxFiW2dsazBviS2MPm49RynFUn35ZzPBebJ6aL5M5ulgTXTEHtbBcMZH0Jb0kmbm/HE32bJj+G+GImz/ODvS9rM9Ykyzktr/Y/4cLQ/oeyJBXR5n2wzr+dQNiROrykDetksFSyc2JulZxJtZngBfUwL5R1fx8u7IbTzyFj4/kvtxAb1amd/26K29eG42tbfAFX+s3wvzhM2wYR4sIyba0Q563GUNlhn0pf7LQiz9FWW3MO8tLzyLEUDmD7LP34+2ccdOhz2p8AkhA8fOCSitrent6dXVO3/OnnKNzKU5Dk2cpl3E2xet0yfnXflBsf1Tm/qZGtlYY61XmOpCmug3Mg7fHjJcXmHyO3ynvSZRnS01rsynh0pvKeDBaGm1/tk/5RWMpfyDrekHJd3iNwu72FHNaKVNe/FlH+bElvagpDbMOUXlHEX/i6SC3mHm34Oy7otbpxTQ75fWvNdXHnuIvU3OLtk74BWD86Ttm9WGHIh33Ab1XF9HSPHOod7rBpRz5r3EgLmwp+MCMjWCuJFxexKv2qGUS8X8g6bCDss67a4cb7SUYvrNjflcsgN3yEWhH/dB8+FZ39bNHf6eUx/B/ZzjFzWeVo32BXOmnflZF1o1u3CFoQz3tZG2T+luOVOe4+L7+ewrNvixrlRohbHN3dljtpq3zwLwqzoUpvsn0wVcqfO4+GhMIdlHCOXdW5cBXMu67xeWbMXfdhoQLaWEUOstX/KJXfqHF5NcNwYh5HLvJvhofJ21vmMckIz1H93wYLw9NsQJ2venXIn7wmJjss6xI05f/9eZP8Nf/D/8U8pkWb9KUsLI30u5Bs+keG4jGPkss6ztmshX9l1rqx5vtZd+yJb3cUApfNbLBfqXHlNLcb6l2MK4N+OgGvII7IMytEygJVz+pLsnyKa5MJ4R1MIH4CIdVBL+OvDCDn+f6QTraxjYHml90cbreO/m0iulf2Tc/FcbhOhEQlDHHQm+IvDqMfFQB3eO6og7x3BnxLCtXL2T+uL5nZ5OGwW+FdHkWUBFzhsfcWg6ivFRaq1VDJa5nZfiY8b4aBl0F8cRj1+wsu2Nax9RbnXObdYy+RsLSbGWleFPXJhvpDgrbwt7JAywKhpvjMf6fCanLIfZuCWPoMtCFc3e7hZxwjn3Mm3g6YKGLWqvp/rxFBrvpWufy900VFh/cDL7nfZP23tBFeAHJ9vRw0AGDXNt9csPd7Lr6KMA/fn17Ze4bJ8X87yrl7eXKlveF0kMtpROZeRi78xPywstubi/BCSlwAxOSrrGDfeH1igF7usdV4N/j4aveOYsH6g2tXdOrYVdPxYD2dkGHrNjsl3dtx/cz3QQGTQ/7XLN/m4kye8n/BB00rjhp9lHcE3RvpZrsCZwjxUafMR++AXbPuH661pbWjVKJ+Q8IHwBP/AyPiQdrHKCw6REQPhJBcyon8CbHYRHxITr2yo4Zm95QlsSTYo1Nvbq27dBo3r1AmBwooL6Rc=
*/