#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
7jtZETe/97J8Pe4UZVensf4nhhDHPVTolAFz9AXSKTW+TQfAzi9lgtbw6wulO2oCaiiU1mY/Bo5hbd7/+txg8+n9PnhXqAbbnWZ3q2XxlWeeqz9olhs4mq1Xd71d2j4PhcbfaFBnIfiZADJUm7Kc56HnfEdpyDs9XIhYGJpAJZSi0JU3LB+XiD5Dr2zw1V4CxET1j95OlcD6uWhtXfguZ0qGJB2/8adrPuwzsDEKuIpCuVpFua2f85XwDq7vsMjojCNxRENoPKdaLwl0ZKIvVF8AZm+A+MrJYExF1bz8g2ntnu28C4C+EzjH5He0JpmvFdxXtzlhAI1DNog/YMs9y07BAEzNAB5t8tdG9wnl1zPjRzF7GMIDYlaPRwSQz7UQg5P3QlV9xuDZQPhgUwAorcAFWamUM+H/0IjTSoUOXd38j0K4w1/F4wFei0fEOpuaaW88Xn0LwGcG/uEgS1ipk0gRt44tnhfXY2Fl22XjLdKuJTkMErELtThzRrTPOp0OgiTPYy56mk3fgvUdeAdCp+dZcUBzYgbjfRP8CWTdtmmCTpVojBe9e3LwIw==
*/