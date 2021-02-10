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
22SgComIJMF5wXHbVWVfRukMBNf33EmTHPP4sLzEoYYCPgrZlpvEcLR6C7/e+MZcqzdhJErOjzrt779rE1BOPjiwgMHxbiQSPJoPihKUB2w7mAkVP3mguCwhuwx/SiF+ySKP58P/IwN//4K/4UAEomY6xlyBwUF7g58s2uVLkk4Shbdm8fUiBMINg3miGdADbnjAUmSjpAuZvu4eNtLu7W4bcMNtL75l8lMeEBlE7QEjKUjyCxLrdbJph9RgsTWkK8oC8tQzPSdSGW4wG6GyRkCYiggk8NcpQuymNESskjQhVPjLHNwzrXCLhLgzwyORo/GTqkcNupceNCni0eg7Dr2mDknqPIUpMxiwMhpLmV0115pgbg0WQh3xgypJ9Qy86qQwRAfcXNOYQ4gmFH5iB4pZJTCIX1QJGQIE0M8KTJltihHgpjTU4OKEgGG7aqNKHFiQAd84Pw5YDuxYuA3lDhUnLgFeImJUKA5xdqFJ0nMDPtpACCuBM3AVVgktm9Qmj5eoFHri4B1am8RhWjP0akorbe16+iBW5Zpa7thTsZv1JjwQVOR/xD5aO5M6yfZMl4SfNC2RoEaxz7SltHxDeJDR4goCDMGwJcEl2V0eV0gD+u/+mX7YPTq4OBnmvKTlOEKaRKeARcNN5GSF
*/