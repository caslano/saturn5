#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
ucb4M5btBixRbKzxRpk2Z/QlwmjlcMIRu6da0lPxIvaDOo7na7KQgtrall+8LJ5XD8VTxOZK4YZeX/LLiEUTecjwl8CJ0P8ikPEpScaP8fj0F/4BUEsDBAoAAAAIAC1nSlJzWpPtIQIAAOUDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxOVVUBQABtkgkYK1TTW+bQBC9j8R/GCXyrYS4PhWtUCzLka22NjUkbY8EBrMy3kW7SxL+fQbwR6X22AvL7sy+N2/erHBkXZ5ZikBIVWpeDtS9aVPYCOJtPIPdMt3BKk3j4YOL7WazXKTjpjH6vQMRXK+IYES5hVtMyLyS8a0sCIShpu4iAJFrpSh30YAQTO+m+Pn+Hr/LfeU6LKUilKogKjxodDML0baGsJIOj+SBxwQXAKb4WZHCQku1x2/rJP2Eb4R7cugqwoLKrK0d1tI61K1rWodVZgo/1wUVzDJk9foZ6JHV2KFeEEXmsggejT6GTPpg9ZHeKjIEqQ6xzA70oPR4AC+66AB8HxA73RqLVqqcI3XXVzoCjYB5Rfnhv6Ge0ERwbmvf70UtSblTv/NhwymjqmjoJlTONf7ZtXNElJQ57jLb18fhHL8eo1DZkcaBwJJcXqFr2YWa++gq
*/