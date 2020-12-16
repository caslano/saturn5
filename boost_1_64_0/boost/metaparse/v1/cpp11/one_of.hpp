#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/cpp11/impl/eval_later_result.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct one_of;

      template <class P, class... Ps>
      struct one_of<P, Ps...>
      {
        typedef one_of type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            boost::mpl::eval_if<
              typename is_error<
                typename one_of<Ps...>::template apply<S, Pos>
              >::type,
              impl::eval_later_result<
                typename P::template apply<S, Pos>,
                typename one_of<Ps...>::template apply<S, Pos>
              >,
              typename one_of<Ps...>::template apply<S, Pos>
            >,
            typename P::template apply<S, Pos>
          >
        {};
      };

      template <>
      struct one_of<> : fail<error::none_of_the_expected_cases_found> {};
    }
  }
}

#endif


/* one_of.hpp
T86Nd3NqR39/i/go9ldkD4efZ6sfByV+8svD4+GkEbqTz7EfMWLsqwcdrf84ZWw6sHh5NHsF82t5r+DIWvaR9o5adx9sQa35uXtmR9XijBFgQ9tsH9c47Tkl4N80RrtvtHXsqK8vckSNgg7e6Yvto96ogt4I1p7jjt5wK8vlah6UHCkMhLOvY+C128d0CuvtGvD394Xe8LP1GnAwkMyP2h9q7FjY19HFfYh1VQGbsjykD7G+6hjKboGuQntXGBpCP1aSTmMo2sOBT6U60R6zLb+WEhSRML3D7YKhiWNYj3hD2te0y+LANi9CFzYIq8NSGx2Mz7+B3hcLyME7lRy483Tjq0m2e2E76VhrMw6GlcmXH4wp5XZMgZ1ZYdrfBJ/L2UjHSRvpDVh7PO//0A9KMC4UmpeXhc3LcW5uiahjOeZ/w8negbSSWZ2g96qmWDzh9nsJ7PdgzW6Z1F17oVs6i1gb3tv5sZHb5bXuXmqDKTdsdt5/UvY47JlS2DPB/uUKvf4R3me4lOEAhd8eLWLOY+q3EvUL1fl7IQsG5yrgDH0Htsg5ucG3ZgxlLGYdyfpHry2whr4PutuevRy1vMXZZQZnK3De5+yns7+/RitbmVwLB7phtY1PyqbyrB8SG9/N/AaeZsBbtgn4E2x8h1ttpLX5/R4lZ/r6TUycAQrCFoxsIzN27t8+Rtto7ihrv+tgIwXvGK8foWfyrGflWcOaD77DhnXOu2yEzbrB0hjnbYLNehLgLh11HkDqYXnSvL2oxrB9Xw/w16rTHTgfhLVqE/bvdq/Heskpcr3kDdmf8nlDPHHOUSXAm9NG1Q3FtU+nxcf3U7pq+T5nX5n/037VumvRhoCX54V6EO49hMMES3R4LpNScnA68jTj/uLWWpyzBP7Fk1Em7XOhFnMgC8fnN/vKcKa31vFtbn/6zt82h8903+gI9/4n0+a8RMueo8rWchhnoZzy6Dut2516cZl0vXaqtu9R9cjqslA9zmQYwh1e17MEv5AOHPDPUOvKwUbcgc8nB+93aQLepXluLfgJGOlDU5/5+yBkZY6QlQ8rWfmIkrfzuE6Uxjw/Z45fp48B3th/mpcEE3p3+XwHBmVWMJ9Usqff0LzI5Q3O4SlfAQ6dcJjPKJkhOPDZlZlLuDwEg3TpU1ylb1Tpn1Uy1jVtpIxd4cj7OG/b27XMjSz/VaL8uydzn2Lc8C+u1i8GFK0Tj3BpdQEH2trSulbK2mRTR6ap++71qv2aFT9ucOUW+Fy+bJ/j4/qqwqV5f6PARXmcsulyfR31roUu3DEHuJGXfg7ub7p91uJcNSN/n70VfWyq6GPfUn3sNtXHvh3UD2lZp/70Xmytq3fPZn3ujAmH6D4oyqz7193Is1vhuI3DkCvLE1tnA3ub6hf3qLqcr/ip74H8yGl3l6daX/1Et7uS4Z+B18cIXv9c8foXqnz3M05KY16fCV7/CvDHgpfnivoQzMi7+8xr6A8D5/L6d8DZyO3j8EjjfEikzwiR94c53a4H6vRHRbqRc53+OMpzynTuA9zW+u1jbus/s0xQufLDPaHG/IdUfWtVef6u+m9WvE2sz1b/Q/D7Ewzr8PtpRU/bCf9Ssk39CHjkvbYS71lBi3hlZblGjb/PC1qm/2n98W/um+rONretLv/LsEVvmezK8h4ly/9R9SR490676j+6bK9z/Qh3OC/H1TGOW0Lek96vzu+Dk0UfnFDnlnv/OrfcEwOcSKN4zFNgI9Y5fQp6RPk3Bk6KR59ieo3Kvnuzgj12il/mg0WZJ6syT1FlPliUeYoocxp6Yyqn2/6g+9w0Sjd0/qju2BxK8Rp2Rh3eDmA7V/tJoTFejs0TvQpBf24=
*/