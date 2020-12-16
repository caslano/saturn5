/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HPP

#include <boost/phoenix/config.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

    namespace expression
    {
#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        template <typename F, BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)>
        struct function
            : detail::expression::function_eval<F, BOOST_PHOENIX_A(BOOST_PHOENIX_ACTOR_LIMIT)>
        {};
#else
      // TODO:
#endif
    }

    // functor which returns our lazy function call extension
    template<typename F>
    struct function
    {
        BOOST_CONSTEXPR function()
          : f()
        {}

        BOOST_CONSTEXPR function(F f_)
          : f(f_)
        {}

        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        typename detail::expression::function_eval<F>::type const
        operator()() const
        {
            return detail::expression::function_eval<F>::make(f);
        }

        // Bring in the rest
        #include <boost/phoenix/function/detail/cpp03/function_operator.hpp>

      // Solves the result problem for F(X)
        template <typename This, typename A0>
        struct result<This(A0)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type>
        {};
      // Solves the result problem for F(X,Y)
        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type>
        {};
      // Solves the result problem for F(X,Y,Z)
        template <typename This, typename A0, typename A1, typename A2>
        struct result<This(A0,A1,A2)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type>
        {};

      // Solves the result problem for F(W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                               typename A2, typename A3>
      struct result<This(A0,A1,A2,A3)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type>
         {};

      // Solves the result problem for F(V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4>
      struct result<This(A0,A1,A2,A3,A4)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type>
       {};

      // Solves the result problem for F(U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5>
      struct result<This(A0,A1,A2,A3,A4,A5)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type>
       {};

      // Solves the result problem for F(T,U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5, typename A6>
      struct result<This(A0,A1,A2,A3,A4,A5,A6)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type,
            typename boost::remove_reference<A6>::type>
       {};
#else
      // TODO:
#endif

        F f;
    };
}

    template<typename F>
    struct result_of<phoenix::function<F>()>
      : phoenix::detail::expression::function_eval<F>
    {};

}

#endif


/* function.hpp
RYG8h/IqecvB16sbirx8DOs7tKxSl6Nr3fKx1y7zPO9TyuXDCfISKTRS34NL5zvTK9YlQqLt+Z/6zYNKbYS+V5J2Wdt4fNlvjkyqnZeDUuRjXeElJ3dfi9yNdrKo7isK8qe8S6l5eNCOrg10UBwqumAEdb9tN2aBxXQi42Ok7ClbtsUyDhP1kfHtx2ST8XE7SjygW7LJ9TdFZK7Ck17Cjl7Prjtm3KGz2fp0vMS7B4567yxNYkeefRutv2eYihZofOf0aUtvtDMZ7dZmQecETd2xXzzpPWcPPQcYWs+hJDB/HXue8d/2zgO+iyKL4293xQIKCghIBxU9BEyB0AQJ//yBSAgxCU2jMSQBIiFBEhDs3tkr2MHee29n7w29s2PlzoZdPOtZ7rj77v4n/32Z/yYE7z5X8//4c8NvZ2dn3rx582b27ax1rq42mEc0tRdkcLqhnwxtuOchBDn47arqhR1psmq6fUaSh9pfryY9kD6dRz0rGW2nCWYJQVuGcSQ97TV3f/IYDGnJvjCWNH7070I0jqWZsirWh6PP+c8DUv1QXmsNFhx0+fNM2cJ3uMx3W1S/L2isg9Qt2H7FyFp9C6FxOspSzRImbojeW89qL7UHVjP7Z3InNVaN62mf1+IK06WRTn9ARBt2Xb+9GpcbCxjsTGa8rDC/SdHpmMzhLql0+Y3TmVXVQBLILvS7Ck06ZB++w4jPp21y+E2/suqGT7YYmWvfLJCQql/L/SwGptR5Y3qkndqX8jKehT6E8q/251yEfxH9HUEzDpp+npTb7J72cyndrE2/L2vHr1WqvpSTm1im1jZhrnWeHpO0J4v9fjRP5W3Fth1snQ/fpFDf27DS2HvFH2qdN6tX4VyU81bcRqN49SNSz+O5h9cfZZ2395A8mvP2e0iN9m5KvT4wWPbecf0jv3cVpEre65ie1n5X9cEba0kbfFzPcK9Y7cO0b7xPXjK/kxqVLZltGKtjlV1HDG68jumm9GG6o6PSmeBRnd9pPdUzTkplpJWUbe/IOAoV797Mswt1vfUN0rqUZ5vLTXn9fqOvO0OXry5szQHW90FMBcM2rUa3q8V+Ph2VJimL86L1J/mtpSEbjddgh9t5Jlcl41Wp+er3MZLpLohMlxasu+r8LkpJpx9JSegPRKYzvceK/7mip/0+Cl3XrODqtTPaIniYGcxWggi7xvsyXdlTPWMOnj0l/N6b4WlZecUR0ppvlcNdBrebhNzdJl2OC9dSn9X3TVLGgtLOUXPuR3qmfO8meEdO29nHSeNzQQRn8CAkPPekPpfQ4vA7HJzT793jeJbTC5LnVzc+n/zoY/JbG9b5Wl+yqo89b1/vn1d1e9HYpObq9nKj8pO6RTLO5GsScyP2Mzowcrx9tWfgh4ZbDXKuyWexQYKGh7EteT8ms4nvstfosqjnpTqetnKReQpE7w9tQ3HKN+vqGbzxWXQ++jtoZsUs4So0ZatCq9yUrTXn1TslyfdNdD44a8nInWRfPMe6VzKByueNnqbMdU3vi36CycefL+idHXU+Z6Xciz/McoUVd9ZkzOq+Voy1nhtqH8jOx96z9S1Tp8A54iybU6j4XvUeuv6MZ9Cu6Faz+/5b8XJNf39EZR3W/w897T2UcyY1uS8yqpXciUF/y3GHlDQteIaS2cR3po7pHPUM5fqU7+00fu/gnZ7qOZz5lpMep98zc/6g2+r1C3Wd5btEvBuOZVTXmm8AZTb1fZ5PyfvteubMpO1txok/Ga5UcV8brr/ivoXrsJiYGZ9roa0rnx0lz+VKns19V6caeTVznko2rNn86MuSsp0clE2tVUZcUzoiXC/0etFHJmWnB9+90/Ey8FNyhgW0lns=
*/