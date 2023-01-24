/*
 [auto_generated]
 boost/numeric/odeint/algebra/norm_result_type.hpp

 [begin_description]
 Calculates the type of the norm_inf operation for container types
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename S , typename Enabler = void >
struct norm_result_type {
    typedef typename detail::extract_value_type< S >::type type;
};

} } }

#endif

/* norm_result_type.hpp
7xDkzm9nnU94qCv48/MRfLBJL9K2Rc7DJ1nqgnVRvXNIGuqd38UQ+FPvkUBezv1zNI0l7wmabxZU89IsohaTJZ7mfaDAhg5PBCJ58XCisTfnY3yn2KsMz8M0QPBXhb97JTY8lzwr4bEAiC9V3wVF/98s8q9P7GCfAE+m7AhvZ3FlPeka6ggTemdY0LXlz3WHPYNk9hVrw5qHrGwVxdt5CtG9ELN5/YyVxyBU4MIb8C5ZLS+vRF/gOxXkYZgsw0truJ+4WO2Gb4QfKCYj5a6JXtCebBt/7DbLQ7X3yPzwcu0JDIrhnG5xC5y3/+y70TW63WY2NR20kmeD9JuwB/SuSzEgJOwZHOjmU4ITfeGgK5LHyjA/lpNY7Ox01pDDS6sgOIvWxZtDwdXQGo1I2OOS2El3+C5ekPUN6M03tQKDjJTbrWUVCwdJrG5aaPDIS4P9gNJs63qPxLTZfZVhO6ZJzi1zeijDGpytttE1rBWz3CPTrJ2/I6SZbUv3Yepu82Uy6+JjrlaMriyrxFk1EoZ7GZYiB7wqMbBi6T86vF+aTcpCDV/eKa5gCyj1i4/zMsoY54iJp0XWa0W2yc7aORb0tYUOgKpbqd77LNzPOSCLLWPKVdCIy7K8u5J4jo92d3HrWT/kl+FhO0Tm/z49eHrbRl/mLl+4CMutYg6yphdNpwcoU2TCjgIURbU9aDtWdATtJ6y8+79Bm58iqg/K
*/