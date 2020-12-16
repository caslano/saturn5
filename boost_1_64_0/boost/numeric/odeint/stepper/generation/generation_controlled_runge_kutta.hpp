/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_controlled_runge_kutta.hpp

 [begin_description]
 Specialization of the controller factory for the controlled_runge_kutta class.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// controller factory for controlled_runge_kutta
template< class Stepper >
struct controller_factory< Stepper , controlled_runge_kutta< Stepper > >
{
    typedef Stepper stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef typename controller_type::error_checker_type error_checker_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::value_type time_type;

    controller_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type() , stepper );
    }

    controller_type operator()( value_type abs_error , value_type rel_error ,
                                time_type max_dt, const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type(max_dt) , stepper );
    }
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

/* generation_controlled_runge_kutta.hpp
sivSUmN7Qx/Us0rGuesUQmeJKEJ4PLF+FzWjlB+zv19U+1GjtluvMmobKoJRBXbutFYJmsYxOIsc1RgKIGV+vtuxbJ5YEwGsvdPEzQhptehhTsTN37hzmvhwQvk0UrRrMLKrQLsiXvV2bSn1qiNV2SuuiC8vjSSU8Nunn0EghkcQbrFIj+S1l6kPzBPUemhqN2otJbW+lTpk4/T9ub5ibs71dV8jM6wM9hFxX7JzH87ubG4fOqIZ9HnO4chf9FFtV8kO7YWyHWV78prLdiHm1G7d8a+Oj/J7ln1u+XUeONt5iQw0cxG4aR6BGnbuHYHBKK/ZTHRu4TWyXQPxrRRG6p+7OSUQ/wz14hszdxX1+agp/V5LAkxvBaH8kMuD3q4IpzRYKkCqxJ5YC7HbqI8wlYcyxGqkMmOurVGEZF57SK7dzLz4GTAhPu5d0/2jfK7NNu5i3Hw1VLWTrWKVCIfdtWUf/GziPTazSJucFWuU+9cmY/9aYx84EZ6HqE4jDkakCkWsp7wDpDlB2YDOHZYkxa9b8FZ/tGIKRaG0yuDaEf+LHRG9t/fA8oE0wqjh/p5bRaW8La61DdIY350WaPqDsKD+iPwMKPvODUgw4EZzv1YwsgYaoA/JPcMTcBztEnOwBbI+d505gJTGq4tT+14KgP1XVMNe5Y7+mE3Z05DtmNtMpf7FrdWO7nu8AvpzN6Xk1+WnkkiDhNxK9+engX/a1bSBq4zH1cz1UFQaN5BXFIeUPC34SO0eKk7jW0inVHdq68Ra/YvAODDUO1aVLxtuuUe9EIOyGGXU+y3GsiJW5eE3qKvtnM84eAdpZMDFsJubwsDD57dWmdK5dSYK218xdte6SLnbNsn9Nla8JLc8QcBLptgsRn95x5Ly7Q9fv94L/yQBR+R4xfKB6tUpoLrwp79aKUa/8YuwweM1kZS567+sZNKDld03wjvBro2vQszvp2M+LWJu6hFzQE38VlgX7Az49XvFZOS8eJEj0Uu7zYOn7TYHMBCHWXitZZZEQoXd3Jg+kJtaauLcOufXPyah47k7WMYn7JwQ4xELGI7xVQ7Xun2gJqhDo7vxjGx7WiiVZtavdjDC8pFqQ6qqbN3EdHWe6bF1rAWuh+k7IRDUH6o1ybevGjPjxJcOqb0lMZjZVSC7MnVjKrtPIeHWAcxCUeT6d7KY5qBsCurX3CjqiwOQRtB40Jg6g+nW1J+/KX1cDlYnD6RXJ/tv5Opkw3/e6qRJFfsfb8i0D1iCsWUlug4abRWH95XsQnVyLVukLVKx4m/8EXtNy7QnaV8NgVLjE+Ld8aQD77YXqKHz86OM+lWTSGVX4N84rsgVDVqpCUKop6kUqTp/6/puc+Rp9lrRMQtca5uFWkFQ6QCRPndSDyMurg7Eh78u/JAYohqM7+mQ4QYJFgdr/HrLYhvjFGud8Bln26UWgQT8+mPwtoWKyik8x+w5oVYJajh+onwqrHy0qxxwTVs/yR6tLPeLz0zCMWt9c01ymROua+L28f7ksnxkOM+Pv6n+uShhjv51MbZWcOfidOpfQvjTP+MzPzt5A17XV9sJMI7gHri+uld0CjwcAZytoN+FaHJWvJviMJIeBuZlwtdJ3yHSt0DAH9DnpUPsJGIHwopgx5j2flfMoXGUhGH/4rT/y/S3wnSxf9pPoHqFI7kiHxaNFSnvbzKqBVEPp/3ulzhHxBcrUiDXW1IgbzOjrv6oAHeOAPcbKd/5jIcsP5PyqQaMRX54rU95lWvwkp8++rDwJNYK9errpekT3tnj0HZL0OsWiBFKheLyUhkX/iFObrJTTpTB/2E9skf/fJS94KXrM+e3R+T89pgh9mvCcy7lfU8LoxHgbnQ=
*/