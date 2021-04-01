/*
 [auto_generated]
 boost/numeric/odeint/stepper/stepper_categories.hpp

 [begin_description]
 Definition of all stepper categories.
 [end_description]

 Copyright 2010-2011 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Tags to specify stepper types
 *
 * These tags are used by integrate() to choose which integration method is used
 */

struct stepper_tag {};
// struct explicit_stepper_tag : stepper_tag {};
// struct implicit_stepper_tag : stepper_tag {};


struct error_stepper_tag : stepper_tag {};
struct explicit_error_stepper_tag : error_stepper_tag {};
struct explicit_error_stepper_fsal_tag : error_stepper_tag {};

struct controlled_stepper_tag {};
struct explicit_controlled_stepper_tag : controlled_stepper_tag {};
struct explicit_controlled_stepper_fsal_tag : controlled_stepper_tag {};

struct dense_output_stepper_tag {};


template< class tag > struct base_tag ;
template< > struct base_tag< stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_fsal_tag > { typedef stepper_tag type; };

template< > struct base_tag< controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_fsal_tag > { typedef controlled_stepper_tag type; };

template< > struct base_tag< dense_output_stepper_tag > { typedef dense_output_stepper_tag type; };


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

/* stepper_categories.hpp
3QSh8uPpGgMqMb2BONHZAfA/cOxSHieOKPW9eJQSpQuuKA9a4IXG4pxHwP4Tf4aqJLBSOyOQt55UdqV+YXmhzUQ+TOpSfKl/+oQ49d0HDlKzQ4kWUqlcb1843z4YclnHR3MjL/tXsS+iy+Fli8MwwElGkWLkKx/nhDm7ptfG3w6OI4b2naS6TtkUxWmrSMHXHmfsSwyMcuzLd7NQcKoZ4a5c35m9IU9wx8IjYyc5msz8BI1mq1ZlpvpZnC90Sq4JiCsCsh+HWfuspY1o215bRIHPvk7PSKWx6uiq7jQLyhMxjwBjlRIqbxO69wNgb0PnV8A/1+4Bd3pBDUEhBIBcamvFyrOVyUY5Uc7EUicpzck5vhpnqQG/a5e6QIgSwrw0f/wMxrB7UAogVkfMoDGvGK92WG7ZJzM1iQ653VFNCwZbNl+Zpb9Y1p45Pr659G0seanW+tb1RdJ+zTwEjZk9OlGG3cwV54TIhrKyOxZ82j6SKwo4FmYyZakQJVECbVVdTAi7RRqIZL6BNX1H3cAbB7rCVPEJ0b0Eot4314mLnf6vKpiK6WUCeW+BYA==
*/