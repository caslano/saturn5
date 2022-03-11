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