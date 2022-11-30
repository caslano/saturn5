/*
 boost/numeric/odeint/stepper/detail/pid_step_adjuster.hpp

 [begin_description]
 Implementation of the stepsize controller for the controlled adams bashforth moulton stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>
#include <boost/numeric/odeint/stepper/detail/pid_step_adjuster_coefficients.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <math.h>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template<
class Value = double,
class Time = double
>
struct pid_op
{
public:
    typedef Value value_type;
    typedef Time time_type;

    const double beta1;
    const double beta2;
    const double beta3;
    const double alpha1;
    const double alpha2;

    const time_type dt1;
    const time_type dt2;
    const time_type dt3;

    const size_t m_steps;

    pid_op(const size_t steps, const double _dt1, const double _dt2, const double _dt3,
        const double b1 = 1, const double b2 = 0, const double b3 = 0, const double a1 = 0, const double a2 = 0)
    :beta1(b1), beta2(b2), beta3(b3), alpha1(a1), alpha2(a2),
    dt1(_dt1), dt2(_dt2), dt3(_dt3),
    m_steps(steps)
    {};

    template<class T1, class T2, class T3, class T4>
    void operator()(T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
    {
        using std::abs;

        t1 = adapted_pow(abs(t2), -beta1/(m_steps + 1)) *
            adapted_pow(abs(t3), -beta2/(m_steps + 1)) *
            adapted_pow(abs(t4), -beta3/(m_steps + 1)) *
            adapted_pow(abs(dt1/dt2), -alpha1/(m_steps + 1))*
            adapted_pow(abs(dt2/dt3), -alpha2/(m_steps + 1));

        t1 = 1/t1;
    };

    template<class T1, class T2>
    void operator()(T1 &t1, const T2 &t2)
    {
        using std::abs;

        t1 = adapted_pow(abs(t2), -beta1/(m_steps + 1));

        t1 = 1/t1;
    };

private:
    template<class T>
    inline value_type adapted_pow(T base, double exp)
    {
        if(exp == 0)
        {
            return 1;
        }
        else if (exp > 0)
        {
            return pow(base, exp);
        }
        else
        {
            return 1/pow(base, -exp);
        }
    };
};

template<
class State,
class Value = double,
class Deriv = State,
class Time = double,
class Algebra = typename algebra_dispatcher< State >::algebra_type,
class Operations = typename operations_dispatcher< Deriv >::operations_type,
size_t Type = BASIC
>
struct pid_step_adjuster
{
public:
    static double threshold() { return 0.9; };

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;

    typedef Algebra algebra_type;
    typedef Operations operations_type;

    typedef rotating_buffer<state_type, 3> error_storage_type;
    typedef rotating_buffer<time_type, 3> time_storage_type;
    typedef pid_step_adjuster_coefficients<Type> coeff_type;

    pid_step_adjuster(double abs_tol = 1e-6, double rel_tol = 1e-6, time_type dtmax = 1.0)
    :m_dtmax(dtmax), m_error_storage(), m_dt_storage(), m_init(0),
    m_abs_tol(abs_tol), m_rel_tol(rel_tol)
    {};

    time_type adjust_stepsize(const size_t steps, time_type dt, state_type &err, const state_type &x, const deriv_type &dxdt)
    {
        using std::abs;
        m_algebra.for_each3( err , x , dxdt ,
                typename operations_type::template rel_error< value_type >( m_abs_tol , m_rel_tol , 1.0 , 1.0 * abs(get_unit_value( dt )) ) );

        m_error_storage[0] = err;
        m_dt_storage[0] = dt;

        if(m_init >= 2)
        {
            m_algebra.for_each4(err, m_error_storage[0], m_error_storage[1], m_error_storage[2],
                pid_op<>(steps, m_dt_storage[0], m_dt_storage[1], m_dt_storage[2],
                    m_coeff[0], m_coeff[1], m_coeff[2], m_coeff[3], m_coeff[4]));
        }
        else
        {
            m_algebra.for_each2(err, m_error_storage[0],
                pid_op<>(steps, m_dt_storage[0], m_dt_storage[1], m_dt_storage[2], 0.7));
        }

        value_type ratio = 1 / m_algebra.norm_inf(err);

        value_type kappa = 1.0;
        ratio = 1.0 + kappa*atan((ratio - 1) / kappa);

        if(ratio*dt >= m_dtmax)
        {
            ratio = m_dtmax / dt;
        }

        if(ratio >= threshold())
        {
            m_error_storage.rotate();
            m_dt_storage.rotate();

            ++m_init;
        }
        else
        {
            m_init = 0;
        }

        return dt * static_cast<time_type>(ratio);
    };

private:
    algebra_type m_algebra;

    time_type m_dtmax;
    error_storage_type m_error_storage;
    time_storage_type m_dt_storage;

    size_t m_init;
    double m_abs_tol;
    double m_rel_tol;

    coeff_type m_coeff;
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* pid_step_adjuster.hpp
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
*/