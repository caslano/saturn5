// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_SEQ_ENUM_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_SEQ_ENUM_HPP

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
#include <boost/preprocessor/seq/size.hpp>
// Temporary version of BOOST_PP_SEQ_ENUM
// until Paul M. integrates the workaround.
#define BOOST_PARAMETER_SEQ_ENUM_I(size, seq) \
    BOOST_PP_CAT(BOOST_PP_SEQ_ENUM_, size) seq
#define BOOST_PARAMETER_SEQ_ENUM(seq) \
    BOOST_PARAMETER_SEQ_ENUM_I(BOOST_PP_SEQ_SIZE(seq), seq)
#else
#define BOOST_PARAMETER_SEQ_ENUM(seq) BOOST_PP_SEQ_ENUM(seq)
#endif

#endif  // include guard


/* seq_enum.hpp
MSyL4atUyQ9NyZgg8HxWe14XIrRNmDxDKyYvxehEkfQESQHnsZBHEcUvlINWqlm+ZsrSog+tpexcld2lC7vGOttLLfXuN2BKks5BQXI+nDBszO7xXv5bGzduBva0eipBKgFQtKswmtWPIj2oc6aEl77gh7kNHYegu1wZR3ZFuS763m1//dzW74np78VEjhvPXz7mGKnnzHZCnyOUvH1aQedayd4HljvgQUFid1wI0p4/HZfwk+vEu708JUtCES2q5Vm9RosbTnN4+zIR8LHKGmaj5zfebl37xReptm0Wd2lgrge/gNKdQKyQjsaicGncyMZs+eeSpZpqBRzV5dVj8fsoXrS3jRnEQAersaTOgubqvNHF+0rm7dtTCVVXptaF9IJIG7Uu4V6jUVrT26/yerBEQhkKjwdX4fcskQP++tiatvPJYXu+ed5c3i5CZNlxsa7WvBK3s1cbm8s1BOeI/SNHXnLzFNEkNZun/QO7MtkjAZtaW6z5J9qiW3qtFGErTuIbkEKOnMo6GbbWgi8FXTb8dvuvGTyr42UtvivCu8kNlqkCZ0uY1x/dNmYQwL9D5brTKKoSDsp1BQWm3PjXlDwe/nLnl1oug7EJZRTR0siOv52/5ehQHRaNOmVv6yBpIPzCT9FO3l0mL+kwxbIVTBS25zOsnRMhH/gZM6va78mjtv7Cc1T8QfshwZDs19bc7bitmWQbJbOj4rz4
*/