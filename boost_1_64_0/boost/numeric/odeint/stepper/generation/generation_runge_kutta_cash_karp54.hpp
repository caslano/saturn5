/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Cash-Karp 54 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// Specializations for runge_kutta_cash_karp54
template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_cash_karp54< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_cash_karp54< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

/* generation_runge_kutta_cash_karp54.hpp
WnLGQkYWm0ZW7VvhQ7MQNEtpfCm+OpZc6qnRdxUbqpQD+tpiUuUdIkU+qBJK6F5CMPLA9kSOISHB1Pi49qBAJzrGh6QEvzhzRMkOF6BCU7XWSNUJB203qvY6IlXbu0A44XcSpSJF/24pcsLnI8WAM6fQpqjim2AcmuQ6LjzO6Mu7R5q9e5jhs2Uka/At/JtnkxeLxIkcPNjiVEFAUha6BsAHUOjVbFKDvmf7A3P1+2ZIy1POe0gdOaxwZBMzFKanZh0zVOerEMXtG4GlUV4b8yNkGPq2G2hBstGQ081CCdNRwgeJ8sh2x40bL3bHK4QlS0eiHCLGsQgcyeK1wZSswYInufz3yeV2tMtLWjbRQEHbj5nglwJ6rRnTymtW2iwt5r6Q8VfJqeX/fO1/5iX3b79U3XP/dnmNOKB2QhDvbnGi/VS4sE2SIk9sMZgW8mgPCSXtm1aKN5uEoraf9tATwk8RfpxAauKjs/VHitglHigyZ9pCTHoXqD9JDRZ+Tno3FZmfERNn4aKQ/PAI/Xv07eK0xsV0TVD/kcyFA2g+B5M3IH0AuU8zJ6cp8lRgnJSwdj8mp2ZOSixxP+ckn5iT6DFMm0LAh9+oTcm+EY6LNEQyKl+UyMWswhdOehyMAdZ6n51srvhKAByXrs/G/1jN52jW+V623sdHOYfy+y3dJD7r0vKVr48gIj6P/0z5ys01+jOTDT0zWV2VZdZacAwY+qw/+TEnSrEBLDgpp6vwi8E3ieap0TdcxYTFVA1/UYg4NiBzqcakNY2xw+tTVXL7Vm1vIaOp0ZcxltCIPs/NGMmljuTS/Br92pT3ZkT0sIzCGj2Y8n04gqbH4JeqXfgS/Y3hNgstAmU+TiMro8KK1xTCNkDHmAzq7yI2WgwQmvbcA7vP78Xm/C4U6ADCWEG/OOU/cQfan7Xvm/a/bf+3HuHrm4cjvGPvcITn9gifq70TeftwUzmGChjTZK6KSuFVf2chOQSh+sIIMMVZg+etT0FIBz8sdsPsuaVQaQXZg7c5hH9RDCYneJ8DFmsqFk3+Yml6UrCrssilLBuofgPv6msYklTHNRiXXhwqqB9dYZ5+CG6/Pr9QDEETH7byXPYmscQg9eKUemxi76pwrX0Sb3GxcwbRJzG6PK1hY45YpxVf97bF/aTHIl7ch7ts7vbpSkaKinSKRUjxw1KLTLb95xY3UxQetbmfdBNsnGlBsC3t/TLT/2xoKv0Qo8TCX6DEQqNEK9K3H8LLJV+yEnjuHOaZX0v5N0H9lUSA+Z2YF4YIBHDhtDcbGWSbn+jhjh42A3rnpZPApv5iYUsKhPlpED6fnQFCQQYIiWvTOEpHvxXRtWcTg1NhhekwP8KeJDa2uY18PMjnqTqjBY0WLa74pcX9QzZr3Z2jLU294aC6JMZN51BwFke259l28A282OFxc0e77t1R8ltteuEH4577rBKrpdhbYmsp229rLkt2HtGmF8BJs6OKsu0UocA1jrpQZDsBsaeV7YfPgrj9UsRF4rLd46aPhs91GlK47mu27aFpk7d5uQudqIuJXd89Ti+ET2h+00YwOee51n6VhGM/QDrOBwK49ZmWzAuhXwXgaIWJrOvy89WZitlGc0ikowabEfwkVCTdrhB3Q5DQVdz/YcQRtmcudwO/ywu/PTe63mtz9d0gXundhif8drj6Sndke6G3ZdkLyIox/Hjey+ZIQoYC4q9bBaoLVcerTjDkVgPOH1wulM+FXLw2RzeUUznVrOdHG8qXwEWDJzfcNxhuB9w3wp2YFMjI42M98rgulceHM/L4UEYe1xvHVl+BJ1HpavgaezoaGAawjQV2oeEqF8Yq+ZnVgG8BW8jWwjpMtRI=
*/