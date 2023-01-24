// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{

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

}} // namespace strategy::densify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP

/* densify.hpp
F55aCEWtPWA1xxByo3H4u9bQYGuyfF97pcwgXvUN9jpH4lW7CpkDATnwdVih40fh2ZBsHKcoqT5C6ndXse5GO7bHq4mcQ7Ktt12fXxUfqZd06tDXGJwEVlHz1yQoLBInRBIZ+r6bKY74+YkJk/JED/aWoQ2TvqfBom6mSh4vs1WBFVCUMeF6meXuKgdN1S/SPkmMCRINo9X1HMKVjQfM7ksJCTHM4UJP+KJ+xHEtFLvJl8NRzHnVSE0yHeRoVtZWO1im5sj2ceWLQtVVnTOvWtNbUKdkIVR+Vx0DzGuvgYjjQrvgoGPYstjZQhQ/3pA/7tpq0m/Z4j7x2wkK10TEOTg4ECHK9RgzLwSHTseXS1BSAbdq9ScJaMbmkOSwM74H5OJZMijbCVeSTOJh2nrniNJuEiTqvq3jnV69u+LYLagS+dnUwVWV4HKHP514mYxfh35YmGqpQAP6EG6ZXsCoMfU854hJtU6U/IsKjekBrJ2cPPCaA1VfpUe03t9b1rnAvdZRrWBO98h7XgDg6ug+J6I/5+ER3VJBp0/7Xk2Cv0j+Ie0PpB2zsYcqeS0t6iOeGPQv34NFYFhYE3aEdsvwbRNlLjVbJWT/XEVRwG2FPOt89H1ET+e3g8rH1oK4e/l2pTISr7eaAAPWM5xUll6OKji/KRAFjhNl/CvG8vsojfdJZ6PxL0vNysQbg2aNshLBEZhO68WVVaB4HtUL
*/