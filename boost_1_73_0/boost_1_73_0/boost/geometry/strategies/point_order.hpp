// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

struct area_tag {};
struct azimuth_tag {};

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP

/* point_order.hpp
9fW/RIBKEUs7lD2b7MACu3q01h6Ph7xvY7Q7nmPeC8OFvLMuN9btcrNPJ5/W7faxhXUWy6dTZ5g+DNKlULLKLIptt7ZLhV4RNllXm0+nCD9DSjv1MolJxj4E+ueM3NkQAGTiXv/ZVWJoEd+7zVPYbtcj1DWDBz/tJTugQpetzrViUIVCPpUDINlvxndAONr1eN8R8QMvpGbKFzyyPFytM1saCBYtlVH2DJjzfYiiIMKkfybb8XZcdrwiHFzKS0v23vEuGAsLpiGdBzmKnAgfsY5SfzDuvR0W0GiKg9lyq5DTSXv/wCZyssmahZYgx6LrnyuuV3mtqTebcDOZSuV1JSfOSpVU5cRnXmBStPpVfdSIgcesil4bFk1UjP1prncnhKMql+NFVl+QkTwixQxdsQ5uFbZLTIdi9xulS1gDgefO66Qfpl3MAofkB3TNlwlSYtRwtGoDP2JjhVatAyVKhmed5h9/3ySwHAIIsYDB8e4EEuyZhiUKyxdWCXBCeU87XYJEuH0z7JXnX1UQ/arwb2rgFxywSR8R8NPgGW5zjBD8BkRyfl88JNlNb/xWL369jIFwUeG+dwnygDdIAvheWETynEP+fBilk/sT2FDjWyt9y+23PRAy2OABlCQk+YDCeq3eekUqMNlK3CmM
*/