// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace expand { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::expand::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP


/* expand.hpp
XcUXvjX+DYk67PVRLD0KiwOBwpD18dNKdAf2qdDFLEib14HfZBx/TpAs9Gm/7VLuxvCR8MbQdwNA0uUExh4av9l8UoQbR++bQAWmYXDT1IDxoP6UDr7xvae49eTnl77OjSiwiEvf4JrVTU9393b7Fiyz+vnpB0GL0F+J497wkjJnpoW9+DkbAiS59A3OfKZbb1hb31oQbhup6XmGdrxqiToa3VS+Xg21hG7a6Z+0fwpziX984FvzxnaPB7JfukrAFVlVvhEMQ9xv/nrBp7aTVY8DP9FP7WDfgOc9dFBCXneL1s/1+9TM2VnEPy9IjZqcwoafmh/UYzcp9MzuX5/WJO21CKh33SLYA859hE9WdiluRLKSKInN4M9kH7qolHWCoxMhLsGIvYCV1S3ny/1jZGzrTwiVpGfvQ/tww32TM1fa63/Ez/U2Tv1t/6f+/F/YlesT/39n1yBHchkioMf9wOaPpHSaF9kOt9lCOdIhyFKdBr1boElbo/cOjLyFVi5uYn1w4z4wYH09arc4PGo+HwWn8JV8QoQhzRYVaZ4EvkRjuGj8G+AvqtwvXz9rqHflNe530B7wcXU8HBkG0anGp5dsno+vZvi5bIxnLS8vXwBdoGM5QfcrUZoE9+o4RmCHXNpXgAOxr9oSuBldAD4+SD0ETgUv6RVFwoM5Fc3FGa/55Swi34mhTv/BjTwhhl37VpfuOxIrhjZSRQjv
*/