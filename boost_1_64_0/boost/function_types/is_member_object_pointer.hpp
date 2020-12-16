
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T > 
    struct is_member_object_pointer
      : function_types::detail::represents_impl
        < function_types::components<T>
        , detail::member_object_pointer_tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_member_object_pointer,(T))
    };
  }
} 

#endif 


/* is_member_object_pointer.hpp
PTaghqGCnEfgiYP8HrL2A/JYrVvGZ1m546iFMiU/z6F5Xso4skWE2lTL+Y9jDhi2xoR1fHTH79Eq3PWyGA5O3Ebrv8vSpeYx3HPXQvINdeOxN9Qgrb+X6lXFQO5SFJYeRvcM05hvyjjM2rWbXZ0yBhvCD7BtH9rpRUQkjxJwF/Ypkq8cm0hxIzXp5qxltDZTjHKGnSWp4Ek07j8h6vFqpGMzT+HLfBmuOG0yrjxNpdX545Djk4M69V7ExVuwVETQigIJdt1YkJEu7ed/TRxJbcQOrj77E2y6c9mfMGfEC/pPrxXeULOREpulOQ6De1twxVyMerqDeHlcJ3Xu2c8jYjoQLphXoW35JCc5wIas8aHEUcvZpdRc7HU7RF5/ezG2NIa03b2pd1cWrn2+gguvp+Ca5hwKNe9kJ4W2k+WaQhYj0EGZVw7TCGlpnM0xZxo21uhELF3OPAlf+zBsGIyHqfcLBElpoF5Xg7c8baYZKa9w+a8X6Zzez0+xCMSpxvA3/DL9HXYaGdyTtm7WRrL0UuLewogsmwHff0F8+kIjuua7GQUxP8hi7mPynnkb/IAT01hfiUctteybxXOS/qXC8i+9oxkuynQkcBAcdZj9Vw0ace3McFURLr/7xS8N98MwDvxLPwkbEU9SUtSnj9Nq2MwJJohd8ZoL1f2kIcYV/PGtfVh66CWeHraj5t5q8nTJRv6DVBZ9Wx9v7YP59zPr0NZix/YJ3vYV9fKMNQthT1givfzRRHygFBnfj2LlXyv2Wn4kUi3fo0DQG1xRO53RZ3lKVvlIXXmmFFNsRUu8ajHvYB4tS9PFohQZ7pgi4PLPWumghQIkakUw/ysHORnDRbyC7svO5C+yFejH+CCKz3ah3e0L+elSJ5i8sGciRXJ4UilOX0NaEdBxAhdF39Aogyc8OCWfJB1SSLW0AevuvkNi22VMcFJHdrYoifv1I7TRC+9RzWS6C/Cj6AhJ/XbChOapmG6YSUpzP/BO0waaJDSflOs34OmvGEz2FidhdQ/4+8lgWFc1Epp9qKdcDV9HFtLzE8bs8d179GexDEuO/EhCY/KZzRIXCjxtwqeoy+BXyE4aXCAGxbiVXFV+Bz2Sm0ZRAalYmhWGHQrA+jhd6O5+QzKf3rCjryYI2N073vnFiCwmjiDj7E56n32aLMS3oWrmDahnFwPdSdiT3oubDoeh5CfIQRJDUKPLaJtWK2StplPDsTusIiOWbt6Yh8Xxd9DauZsdkxKFuuh4Wij7gyrlW7lH3GWMbt2Dy6LTEWUdyJpOz0Kd+C/iEmMxTOs7sxPwVE3vLJg5CfhTURlUtjyijKNfudwnB7pTa8/X/syhAYUlFOJnQunSh5jQ3Rsk4TQA2SUZdNsqEvPH/MKowL98ZXsazZK4jcRhVhSRsIDLPEyl3Oyt7PjRsxSmdpBqBP6j8Kcwg5I9LfphwfWuWKCsZiNzG7uatkY+o3ftRlBSnS7QGcdxdpMqj+1VgWXkP+yL88Ngky9WRK+H0dpxVFgyAu12oWQx1ZT4rSW8xscW/sGPuYx0OmYtkacs6w3QyfhM9QnTaaq2Jft6sRMb7U7wFVd2YpLNNXz5u5DaPwrTxXd1FPmwlgt/lcGjYwWYxnzJQy+MWzf9E3SlpLmKaTGF1m9mW3zl0fVqHv5zbqd5u4/ymccHyG9uNxftj6WA/afpwt14qN1/QzvqzlOe5U2cf3GXhh/xw4HjUgJOr8NXKelQ4wOO33+U0KlWRLeXD0Cr+CeOKUpCbEoLH3LLGXbjTlJTgRXOljzgj0svkolNOJu6wx8xd5yYjuNrdE2Pg+7i0zTirTH3GcygJKe5/NVf4NVAGP1oLafQ4gJM7HQ=
*/