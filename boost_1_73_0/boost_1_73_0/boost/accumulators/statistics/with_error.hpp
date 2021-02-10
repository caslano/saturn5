///////////////////////////////////////////////////////////////////////////////
// with_error.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    template<typename Feature>
    struct error_of_tag
    {
        typedef tag::error_of<Feature> type;
    };
}

///////////////////////////////////////////////////////////////////////////////
// with_error
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct with_error
  : mpl::transform_view<
        mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
      , detail::error_of_tag<mpl::_1>
    >
{
};

}} // namespace boost::accumulators

#endif

/* with_error.hpp
u8y88HbxZObwhXgLjw3vWz894vPNF44DJBf8cZ0fZUZLZjsi5zU+RaL2rFCsjbqKnWterHGueeF0rnlR2bnmRc655kXuUEmy6T5XEqkV3GxeuM+WZEOq+tq8qHC+pGjmj5hEUnWvm3x9RZWZJ01mRdUPm7hUwWkTJTqOm0RKdXedF7+Nu84Lia713rkDwGaJLAZ7OvkNvHderEfSVLMJnjdjZkNnngKWdJRssERAbJvd013Li4aALVbcoJcXjHU4V8tlQFv6vhU0K3pJA7BMe0PMKuRa9ukdTqmooHD/eeFy/3mRc/+hvfy/vGxFyIqIZlT2A3ph+QG9qO4H9OJ+YFUbYv65Jz7l4SuHpFxLuIww3mcwBfb0Pz2TpX8//MoDeAfIauwgW/RuerEV76YXVXBrvu1f3LUJ/chhn30g1yak+rZd2bnJa8TyuU0CrzmrnOn0hHe0NGy9Lxtj+0BJLlyolYsUglZOtjCrqGY9ZOWMGmI1SyrAKhh041VOLIWrgqwTrYoWrAereSIFWFVSzENVTqmCVAsqK6jJxKlGLeYV60LHcC5TBW0Kzr4k2BQy6O3YzdsYZwpBKsZRGvH1KJMzr0OYXKcOMDfjohq8LOMlg5YmL4CQttkh3VImFKa0eXBBSjGnyxGlnkkD
*/