/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_times.hpp

 [begin_description]
 Default integrate times implementation.
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED

#include <stdexcept>

#include <boost/config.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/iterator/times_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {



/*
 * integrate_times for all steppers
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepperTag >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , StepperTag
)
{
    size_t obs_calls = 0;

    boost::for_each( make_times_time_range( stepper , system , start_state ,
                                            start_time , end_time , dt ) ,
                         // should we use traits<Stepper>::state_type here instead of State? NO!
                     obs_caller< Observer >( obs_calls , observer ) );

        // step integration steps gives step+1 observer calls
    return obs_calls-1;
}


} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_times.hpp
/cN34IT7LaS7atMvJxvRHbAh821+rBzf/hnueY0uV0MTi3utJv1UGD59T9sVwEP/pRGs+aISsAC/7cUhC54F+oIGTQ/Xhvt/Tvh8UfzaGqtcOEozl89MD+zjScDqt6uay0HXpFtzwMHq4j3jRz5wEvn0BLYtkO/fwOiLxtELBl3HX2JYuiEcT+v6JWjwAuoVXv9wS75n5nvCrUupQp7TwHG0Q/QcufOd+XxHDw+kh3uKiXwKzt5tz6rfNL9MfNTd+d1Lzl8KNMFBtdICd2fUa13mW6xQI4v06YMiYs+dl4OLb3Y3PpjcUL2/29JelHjls88wbTR8OoRLS9G91qYP7dWcl5OqIhyVd0m+sYYnaGwe2GIYaHsydl+sWQQt/RuMT2rv7DPexhLz5Q3NgG1D5ePYN3Gjn1WuwZvtwuMwvnRJ9dqTzH8grR7Nb7GObc8boz61ZDSP5jfaCr798qH7t3YtvXeKluaDq3rjgwv4qnCusBgEZ4Jxwgw6HpdNMY6x/r1KbHP1dn95fMT480/F1zR0rwfWnD7ux59+tYH+Cv+2tnYLva/zo8DTp0P5aoP0AFX4Qt2bw2H1fuslGr+meUXhuOvwyt5ctZO4f7S82RwZex4rczlr+oNc/kmfN8Yet3m0oKXDYfjUxTqXt5bDjMe1cvZSw7TEN21oJzFbpp4nDsW3tFu9/bD6NfGsKF683C82qMWjtFg8+WVvqKrc3SAXOz811krW8Q4vFF4fX6O32Efb62HG11V71mBmQ/qvfkg90HleT8bjTWNN1sL8OVfgWSlcWpg+1gNN0hM9bha21njgesBb9Gd216Mj1phvQ9x7fq1crIi/v+B9ytU+9MjP9iUm86cSzcEd4pu/jDhHmsuvvC+cVmg8/C0sR3eGrBUuLxqO+90yfULOROv7o3hZ+vfBq+UgvfhFIXWQlRZM4XztONhpjapUh1t6+hWnzLM+7OArDaN3ogvLPb36fNd7/xc5QSumOuK8109ywjNzL4f0ydbmSSv+S38azDPYfSfRsrjsQ/hR5yxOxcMXVsu/hXTmNR7GBJgnR7tdxZOwNr/rbv+XFpupTv/RG57Wd7tO8b241FrnwM33DsOgp3JELiXJ6A/MLJ6QH/pIjemtTmezrn/Rz5F8Tfw8e7C1Cv7Yh66pgbsl9wqbc2U516qD+JSlNeHHcz1z7kt8mIn8i0Y0aSb7CQ9pLP3tttyoES81k5/p6YqocnLaHIch3LuwvOQ4PbEazlLAPYs4+wn33lL393FNkz5xz7m+PIBeredz9M61+MZYhabcHqaJ6Ibl4oDbxuXTJ12EawVpkfmwQR90Rp3WTm5s7dSnfmp9V3rqsrjQ1D1ehxPjAu+fT1ovrr/fep+H9R0sqOYZIrpoy2aeB9w8JPeTdNHjyMt14pe8Hz7ZD8tziEMnfCMHOzaOiO1j8l/BAfK4lpxOShdFTqWj1+th4U/1ryI8fylGC/HjIjEaYyzmttS+3BS64Rd74R+N5Ylshp+fB8+U0IS0W7p+7strnkujPYFHHfY7k7rNc4Vi2aeFfYoq9E6MnmiOnyeBXYu89xzOH2AOYbE7FKF3Vxt8/jX6q+5X6Iu2vKT3aZsjodjvnGj0gkYzjjr59EbB/GFRjk7yKRN/BRZtc8906jjnDFvQ5rsIj98dYx8gQj+HLxKXtuf4daT3euEsfuwD52dZ/wM8HBiQ/py5FxTfnNbCn+cNxa9e3LMO1fXenYzl65fwykiSiK5oqOd9vRIevU/HjNcPTjI3e43paJdX5WdxtbwRz47OFWGfRMz0VU/V3Eyx+B4HJPZnj/UZhCOnrTQemJVUTh+5pY6m2eOT0yXk+ilc0TYP/0E=
*/