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
blbCAwl0A68oMubXk8sO5cswKlHo0C6T1wzNSk/2FcUo2w3v9fV5ojyIwbzAM99YECDz49OqXJhjE/ZAFhiVRLdfX5Qor4lyfwXWM3Turfraj00RO5OPFV0ImpHK64av+x7zLDB6ErGUZvJkazKYirU7rGl3zKCFX3exUV/UWwnlGoG8xgKqnq5KqLwmVRdRF6hJd6jenWE8GSju6R9ULegtMhqKfqKECcEJghZPlBImr8kSA7Htni4EUvURtZ5QjXqYwZ1pPJFfAPId5runr49+rUaYFjKv6IOKdxsnmGbdQAG1qaeO+uSeb5RcQnultipxCnyh4GnGZCiC0DZiK53+Cj6Qk9KMAj/bP0DMzT9raFnPqT9VfcwVK0rt6yS/TaXU/4j8mb6g/izqoOMiV0v7Av/ZGv9aW7/9O2Ucyi21a+anS58qolvKp2TM8peUICU87mp69POSrOqaBjHeeYrfF3BdIUZBV1nVl14LjIL8q9GZTZjFQVwpZ3hzQz14CyL5GhXzvEvsM5s7wiH0Ddc6wpCngnNX6MHZ9HqCX2+FNmbqu9XvR27ghmNphbttykoOvPOU1TFi9l9tIUMl0XC1zaZXt/ixqte4DV30Cm1sOW+W+tVWjZtiDOc6g6CvhANe/qzqC74WITijEAlJR3pWBwrqqYwOeJCT8BRM9wgWplrV/FqyZxSrfMPEUNzkCz1xkibm+4p+zKEENLv5QpmTr2KkyJOxntD8s5HJ6Z/AeuO7m0UZGr9GhbaLF9u5ZoxJ/c+zAGoPSCa4gBYv94J4TOqEOsrsMZSmBe8ASAVG4K69rZdvTk8/kulebuhI/2At6Y+A24LnPUP61Htr4mFv2lfuI3Z5SYkk9gd354j9wRq+MLEQq5MbNlEI3Gt2baSkla359WJtafAObXvuUD67S4s2C72TzV1Yk3wlNVDNWhuvZrSIsgzbiYCF7yIVsEbP0tS/PpBjZA4dNWeHts10iPkVLveApQH4TcAvH7/F+D2GnxTytz06fcjZPAbjjn/sUx0b02L3Av2BMmZWoVK6FLIoNNQUeoRPSZ9V6K6mL2WeeV2KNjEi6EGCxp9RMTs8Hdr7m0IRv9tOVy/8scICBJVyxiZCQRWyArI/JAXMD9v50cfE/MmXMUvCc0ZtrJrzKvUxX/P6Iq1ILudkVOx+yggYzDLqhSvGXV0pPN0L0L1DJ6IxtA8XJjSmPs/qRTqcVzBiIguvJRtODGATYPYIHDCUbpVKavs4JHvJfSulHhdP+OlJbAa+uBllGjtLUWduYXDfQ9U3FxYWfn9QKWW2tcf0yte1B3sZvk7esvAalynpBfJQ/BNPmFJKnycTGx/Y/uu7pe/rnjDPROMd5ixPmLc0NV1mnPsayWUpXWRcORQaHybbarAmFsbtP8WXP71gKtf/fKIAZyKqM3qqTZRnLqqNNUtRGFHI2A2BtimXeSWx5mSU5LsWa16TtGiBMuEUKpVxGpWyqheQvvrI1gDVO0xc1oS3XvR084M93XzR04X7RAj+I+VHon+oeEWkFEkSa/j6WwWglfdGUPUa47LFUCPxlaAhinKnxEmLLKK4izoJ86LlePoMhfVpFSd6ZTGEQaEDHXPhIwZpnaStP/VtUGqb0YPjkeCawzN1wYVvMTjBiaeNgQDnV1bHFK3bXsG2tO7h5gUXVxebWiS0AokwSFGb6v1+T4VogPvhVRo8y8Ti1yL0puG+imBXqggUX0U0YYm+mIAP2V2AVbmeWLLy3D7LpqRauM5kDI6CstWlkJh/jWjUpfA6HIIzq3rFw1yS/1SUOxrMnN3WTMvTXj5KJpRD8OkcbNUkzE2Z9ZuD6z+UxrLogIRR3hhtXSc=
*/