/*
 boost/numeric/odeint/stepper/detail/adaptive_adams_coefficients.hpp

 [begin_description]
 Calculation of the coefficients for the adaptive adams stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAPTIVE_ADAMS_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAPTIVE_ADAMS_COEFFICIENTS_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template<
size_t Steps,
class Deriv,
class Value = double,
class Time = double,
class Algebra = typename algebra_dispatcher< Deriv >::algebra_type,
class Operations = typename operations_dispatcher< Deriv >::operations_type,
class Resizer = initially_resizer
>
class adaptive_adams_coefficients
{
public:
    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps;

    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;

    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef rotating_buffer< time_type , steps+1 > time_storage_type;

    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;

    typedef adaptive_adams_coefficients< Steps , Deriv , Value , Time , Algebra , Operations , Resizer > aac_type;

    adaptive_adams_coefficients( const algebra_type &algebra = algebra_type())
    :m_eo(1), m_steps_init(1), beta(), phi(), m_ns(0), m_time_storage(),
    m_algebra(algebra),
    m_phi_resizer()
    {
        for (size_t i=0; i<order_value+2; ++i)
        {
            c[i] = 1.0/(i+1);
            c[c_size+i] = 1.0/((i+1)*(i+2));
        }

        g[0] = c[0];
        g[1] = c[c_size];

        beta[0][0] = 1;
        beta[1][0] = 1;

        gs[0] = 1.0;
        gs[1] = -1.0/2;
        gs[2] = -1.0/12;
        gs[3] = -1.0/24;
        gs[4] = -19.0/720;
        gs[5] = -3.0/160;
        gs[6] = -863.0/60480;
        gs[7] = -275.0/24192;
        gs[8] = -33953.0/3628800;
        gs[9] = 35.0/4436;
        gs[10] =  40.0/5891;
        gs[11] = 37.0/6250;
        gs[12] = 25.0/4771;
        gs[13] = 40.0/8547;
    };

    void predict(time_type t, time_type dt)
    {
        using std::abs;

        m_time_storage[0] = t;

        if (abs(m_time_storage[0] - m_time_storage[1] - dt) > 1e-16 || m_eo >= m_ns)
        {
            m_ns = 0;
        }
        else if (m_ns < order_value + 2)
        {
            m_ns++;
        }

        for(size_t i=1+m_ns; i<m_eo+1 && i<m_steps_init; ++i)
        {
            time_type diff = m_time_storage[0] - m_time_storage[i];
            beta[0][i] = beta[0][i-1]*(m_time_storage[0] + dt - m_time_storage[i-1])/diff;
        }

        for(size_t i=2+m_ns; i<m_eo+2 && i<m_steps_init+1; ++i)
        {
            time_type diff = m_time_storage[0] + dt - m_time_storage[i-1];
            for(size_t j=0; j<m_eo+1-i+1; ++j)
            {
                c[c_size*i+j] = c[c_size*(i-1)+j] - c[c_size*(i-1)+j+1]*dt/diff;
            }

            g[i] = c[c_size*i];
        }
    };

    void do_step(const deriv_type &dxdt, const int o = 0)
    {
        m_phi_resizer.adjust_size( dxdt , detail::bind( &aac_type::template resize_phi_impl< deriv_type > , detail::ref( *this ) , detail::_1 ) );

        phi[o][0].m_v = dxdt;

        for(size_t i=1; i<m_eo+3 && i<m_steps_init+2 && i<order_value+2; ++i)
        {
            if (o == 0)
            {
                this->m_algebra.for_each3(phi[o][i].m_v, phi[o][i-1].m_v, phi[o+1][i-1].m_v,
                    typename Operations::template scale_sum2<value_type, value_type>(1.0, -beta[o][i-1]));
            }
            else
            {
                this->m_algebra.for_each2(phi[o][i].m_v, phi[o][i-1].m_v,
                    typename Operations::template scale_sum1<value_type>(1.0));
            }
        }
    };

    void confirm()
    {
        beta.rotate();
        phi.rotate();
        m_time_storage.rotate();

        if(m_steps_init < order_value+1)
        {
            ++m_steps_init;
        }
    };

    void reset() { m_eo = 1; m_steps_init = 1; };

    size_t m_eo;
    size_t m_steps_init;

    rotating_buffer<boost::array<value_type, order_value+1>, 2> beta; // beta[0] = beta(n)
    rotating_buffer<boost::array<wrapped_deriv_type, order_value+2>, 3> phi; // phi[0] = phi(n+1)
    boost::array<value_type, order_value + 2> g;
    boost::array<value_type, 14> gs;

private:
    template< class StateType >
    bool resize_phi_impl( const StateType &x )
    {
        bool resized( false );

        for(size_t i=0; i<(order_value + 2); ++i)
        {
            resized |= adjust_size_by_resizeability( phi[0][i], x, typename is_resizeable<deriv_type>::type() );
            resized |= adjust_size_by_resizeability( phi[1][i], x, typename is_resizeable<deriv_type>::type() );
            resized |= adjust_size_by_resizeability( phi[2][i], x, typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    };

    size_t m_ns;

    time_storage_type m_time_storage;
    static const size_t c_size = order_value + 2;
    boost::array<value_type, c_size*c_size> c;

    algebra_type m_algebra;

    resizer_type m_phi_resizer;
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* adaptive_adams_coefficients.hpp
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
*/