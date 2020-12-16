/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/functors.hpp

 [begin_description]
 some functors for the iterator based integrate routines
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

#include <utility>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


template< class Observer >
struct obs_caller {

    size_t &m_n;
    Observer m_obs;

    obs_caller( size_t &m , Observer &obs ) : m_n(m) , m_obs( obs ) {}

    template< class State , class Time >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_n++;
    }
};

template< class Observer , class Time >
struct obs_caller_time {

    Time &m_t;
    Observer m_obs;

    obs_caller_time( Time &t , Observer &obs ) : m_t(t) , m_obs( obs ) {}

    template< class State >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_t = x.second;
    }
};

} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

/* functors.hpp
IkyzXrMom7SSzUyXn9Uf/s7e6+E34ENs91AiHufknilot0szZhN5FuWJSVdsYtKVSEw6NdZGGmdqjHHtaJqrP+0AYeXuHR0s7Oey5B5PBe/xZGWxUcvCxIAdeY157DoVynKTsdthXTYnxA6G+raFdvAEZQchc36Xix2fXZ4/rvaJMu8wXqf4Vkg7e3tSIm5jt+/PMoq2jan9KZSZSj2IykV3sZ50uKuxbxG9BfrpxFjW247v7qtJiPXlO6CL3wINbSUdmZflnhVsiMgX7TyF8v0s5ev35+x4kH3UU5Ufc5pnHj49EZ83z2A6rMckNZedKX63o2nn2yf3iPLO8c63Mn+enYj65gvu2y67LtDUnGxevqiR3/sFYXpR48qmhsYg+v5HejFetzBxMs9L2FiDpMNQg/68+FrARDW3r+PdoQsSonv0Y6jH0h7ouClXGFyckLRdwxrSeaB5qYwj+ivxs+in4Hvojdje2wCcAb33IHs0ErNpQMVs2sDfLkZF7nepJ5ZnmcTyVHaado9x7soD3hN34e7Ah3gV1m76Y3eiHzFOTTzSKh2PlGO0Vtm6t0MwX1G27oDwPTaxde16LfI7pXG/8dul+eOwfZVj6msJf9yyW0uj8rrM11nmquw4RJldyEetkdj4R5CdprNLcA3pfIN0uOZCOqOVnxRcx/LXq/H4QKmlpe5X89txOv42Glo3ktZNpLVzgd7fkPlpG/3Udrz9EcYhy+rclYAXOfjwGGdXO3+VZRjWzO3v0F9td9EUU5sGSOubbh7t6CM4R+cGN4fSJ2V6mvik8vY79VXmzPaBAfWe7c3OPwXfaC8Rl6OF3mwHlzgNCcaWvUXpXpXDUY8sSpL7hL4YsiaSn4njR33ivRXq8FbRTRs/4Cy5Dyp7Igl999+Pcwdw4mdb+lxwGPEDN0Rp3uuGHenN2povzwj7EYLJ9EZ9QpxS3iWfxxhwdylZlbl2xy5ga0D+2LljKBfK5m7qK98ro62VcaXiA2AsjB4f4B4ZU/ruZ+7Ns3OmRDb7voTkARb7Dv+R+CfElTlEp6HnsfQNJp0x9K41+Teb9DaTvtKkr5Y028L31/agH8C2TDR7UY8l4vk2RvqvTD7aFct/3OTfYPJ/Y/IBj+U/ZfKvNeWfNvk3m/xnTP42k/8Hk3+lyX/W5F9t8p9TunCWiWX4vJR1+mfvE75AWr+eqvC1LpUqu75VxYpnHsc7+Pr3Vl8Rf0XhWLzC4FXRWdZLxhR5uTTawDGm0sivUHUBzLtn+6bUhTgGj3X5t8iA+qpp+++TF9TE5WzfKJwo+WIXVf5ONZz/OO4rgfs20hoKJBYI70RiPSDPXAoqRaCVQPldRyifGZHGrsHbauI+4K3wATmnS1k1n7dViEzA083pu9VQL+nHaJm+I8oreWepfBNMBkz761Nq/Dq1e02UBk27Xw8+/r7fs2bkeC+oc8wOl3nx5V+LPxX4bLseN6hjvE17A497sKoNuO9n9MPuZZZLvpOLzZ/O/mrai2/jTGDMdjNf2/cn3otyLQV+3z4zJt8+8uenuHWrHjjRGecL/T98fBd/W31LzAzW5WJ3z3bnq4RelUujPopvLc58DfVlUnoN6IA83wzz9TcD31teYL4ZFnm+GZbwmyHcTwDKhP1qxKNYGnTJSuPa+LmVX5s42u+jPZhlxkS5iwNt8XHWhvhziJ8dq6fuNzZffi7LV7G80x3Wi3pDGyG6k2CZGpa5I/D77PvXqJjuKen3SsCLPLGLqwEvtv436ZSI/+3SpR7/u4y6JGtccf+7FuXKpT7OCU+DdyVj/tSpPqvI/545501lg9Q44pk1dw6bMBvXnmt9Q+lUEg587M3V9FCHFJc=
*/