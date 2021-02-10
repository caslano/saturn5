#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
XWYq9dr5JuCbtCqG5CHM47/l6+OfsHl8+PXFY7/JEH++I4UC4rrK+eh+cbddrUOvW1BJ6XN+7jGPJjkpCfhRHj+9+DdQSwMECgAAAAgALWdKUgfUIXjoAQAAEAMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjQ5VVQFAAG2SCRgZZNNb5tAEIbvK/EfRql8iUrXjtyDEbHqplZsNQHXpqmbS7WBsdkGdhG7EJNf3wH8cegF2J13Zp55l/UtGhsLg1PmS7XT9HrF5k2XiZmyRRStugcUpT40LAj/rNbh9jfz+UXk8z6PfYANljWWrpEJMr/EImsonAgr+lJ89GkEN8MhhN/ZN2HRg6jCjzCcQKBrCoyGMBp744lHkvvHiPXlPGgRXdMt+E68IrvTyqKy7gOqvU09GJ93oqbANuFgeWrzjLGd1kTYM/j8yESod5ls9T1q3C1I0DeZstTaguSnpa9ETgbN4hiNAQFKK7d1RGICqTYW3qRNoTJS7cGmCLHOX6QSVmoFegduJ25AF92OUAmcnARUNdSipGZ9D0KgQerp2evbwSLcRMtVh9OHfKqfU5We0+O8IlDPYFyi/XKUe4PW8VW4jvjoZjw5MxwzkirPG28QhA/LTTQPOh1pcnFwrcwR
*/