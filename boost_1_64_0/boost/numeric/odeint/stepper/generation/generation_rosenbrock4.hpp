/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_rosenbrock4.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Rosenbrock4 method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class Value , class Coefficients , class Resize >
struct get_controller< rosenbrock4< Value , Coefficients , Resize > >
{
    typedef rosenbrock4< Value , Coefficients , Resize > stepper_type;
    typedef rosenbrock4_controller< stepper_type > type;
};



template< class Value , class Coefficients , class Resize >
struct get_dense_output< rosenbrock4< Value , Coefficients , Resize > >
{
    typedef rosenbrock4< Value , Coefficients , Resize > stepper_type;
    typedef rosenbrock4_controller< stepper_type > controller_type;
    typedef rosenbrock4_dense_output< controller_type > type;
};



// controller factory for controlled_runge_kutta
template< class Stepper >
struct dense_output_factory< Stepper , rosenbrock4_dense_output< rosenbrock4_controller< Stepper > > >
{
    typedef Stepper stepper_type;
    typedef rosenbrock4_controller< stepper_type > controller_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::time_type time_type;
    typedef rosenbrock4_dense_output< controller_type > dense_output_type;

    dense_output_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return dense_output_type( controller_type( abs_error , rel_error , stepper ) );
    }

    dense_output_type operator()( value_type abs_error , value_type rel_error ,
                                  time_type max_dt, const stepper_type &stepper )
    {
        return dense_output_type( controller_type( abs_error , rel_error , max_dt , stepper ) );
    }
};



} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED

/* generation_rosenbrock4.hpp
fxQP25gzUthp63aS15Plp63b87k11Fi7K01JXK5qneNABQmKHQ9uoY+6qwiBiUGyUb7JRrkG1ohMnnDwn+QJXXSR+vJZW/YLZWgoPxeISYpN7rawnaR8YFj9eMIg5WpxXxdGkC9eYwrFVor8lYmWCsbgMNnqczAZ+ISxycbf5zIf/hcuv0Q9mSp+lJJB+7n6UJa+H36tTCGuauyb5FLVe1zaCsYemmA1tALtP2Tqn6dI7haT5IYIln0s8hK97PVUcRt69qPvMNL1DP91KtKnekaKMdIEhk9ORbq/Z6QljDSQ4b2Us3bbKxmJts+ckATtC2vczUIQNpFfcKm1q3u5bEv+xNja1sDkWeqBDM/Q7fB4M9PjQ0imZ3rMQozDGR7hQrUjNVB8PmPC+valgk9LfFQ9ccaBJG6Ez1R/lwp/MCP9R4zwMZjizpR+OsI5pKTs68JzROeQ6uVH04x837lk5B/81zHy/7/+Iy55nm2l2Fcqvzn1yTl4iRzLWvU7Wz1HrrpxA8O/cm2eCmO0CmmMBga6Ocu7z/WF7WfYn+Nkxzwyy7CX4/KnIEhjCliJVZu8ykju49MCjrjd5d2xvJfxiRBnizLDU7JPmZF/8QxnLOBIZHlXO1b8TJvhwep/bvJxThjrK5Wka7MOqVMpRusivfV9nD+ewr9kdLDmoDagZKdSJcWa+J6EyJqlOcdoB2nyVvKqtqPsVawVDzRZyMwcbE4MvRoM3qQdZUkuvdHhF4DnB+iF2iuU9GIpOZ0rbZu+UXsh/pFkyYtaK5bQ1VjWj20buyMXihdMN2P3nNrt2gzty3SlrG3Evs79Iw5yOe/FBLmsTWz9uBUZovzOl1ybW+JTKReQSrC2+BQF6/Hmkr1a88LFqDrWq537FuU1E/R/bP9t2kv9+2R/5nrjOasQbRywSvMrPikxfVtu5ne2Yk1hwYVnIZ8wAhyE1dlCDEBMicHnXj8HH+bcAkGojqelJuBqWECe4wdic7DtEnORNsbw+e1otuQv8C+/HTRQfSi1XC6lEKdJBDm1L2yXq598KKHzyjpiaKX2CEvQf4gY4ggLbYqd3ia5qQH9s6NTHIadHAZkdJsZuw3vlJ9EjiqrfVDIJ0OXCbPOXfnm+d3Z46tO4KgvOGf59T0meKs/xiUvjFFKvW8sOyQoBRBFnjksWbABWVJN0gdPLp6zswjf+aKK42QeXJlFkooLXDfDTpUw7Hf4Nzl219rPcWIg9tsH2eDabOCD5lv96PF4hodiI26Zl/71kjRupc99IvMY/k3cbuuO2wUMIm43nY7bkUn0ZX1RiYFb4Xce/Mp2A3HiQMZ9xleB4g8WTYFTyAB2OWiPQfyR2Y9VbijXLxBQuFJVLASikkTxvUWHaRgbd+SJNel+HN0QdzajEU3zmuvX7tfuE+efTLKGrdoOEBVTWNZXKFG58zOU7doyCSsr1xYrfC7lorimU/NZQc1jFXHAZfaNcH+AkMoUMSsc5XRMsieKNAXxja9p9LBfVEz7RdfmqhPRyUltioV7njEcTrFEJyta9mxI1Wt7RydbXZuzawdQeh2dbNM/O0pIKCi9FCtClGSCzQ2xoVqlckOpkp2YRxZeEV7TzQih6dq0DaVaM2iqCPKTkoNx+6B4TdLbdmeBtopLInfUo/i0yqdLbS3etlXvoXO+Y5X5KguQ6xDKUczMwudrKIm8zyq8wgQPAALHa2/Dmy/S0hs0zIZkq3lfdN11NbejkZZJmzsssmXLdqNn9I8HPBs1a3x2aaxhAwnF531x2XvYXk63P1g7vEZ/5GJWmiaMQ9RhthRzp8D1SeP8r2LGkBl64oH8P5HfiBp9jpnf6v5xDPnwLKrRr0wVcpE=
*/