#ifndef BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct first_of
      {
        typedef first_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<0, S, Pos, Ps...> {};
      };

      template <>
      struct first_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* first_of.hpp
D9t0sSMpZdhm09+6HLNT/dKAzWdeOAaG+ELDtoHWSPQRAYH+6zeLliOUGRvT68yQCoRrt2N9xmyJG4ul0Anam+ADbkuKznr9gycLwlwrb1OrJyv9StC+x6kDSK5aEM1mqnT7UN96yVVZvKt+gx2mq0qOg9PLKsAakVJUe1kn5uvr9bEzoGrGIH6Q+w2+Yb6A4ftncFkQ/tKR6KXMTjaoHVUGm9/C8HDAMLBWRoYSmvEKWCF3S2bAdoZMtaUCN+O9iVhDh0FQtss03MQxmzQns2snsKi8/QBgNXitfwmlxzIbi06SEdxBdWjwljdfhDw0/wN7yF3Rvj9n96gS38ProWHj1Qv9bNk4gmWp+HFVA1EtAa3dN6MlS0IGxfs4dgPmfQckRMC/1BysqpwlEB4l0AVA8wB7dauvqpgfMIg9ts9s90XrlgqeFcu1aAg5hqgJHpTUOMLW0eJRxZEUHRfj828nKLCHhU713gKbD6YH5euwfeTx8qyRKbjMDt0rzuHvW25hTX5F5DFAbhAGmu/yf8CwNpsvgcSvspntnPqsM/tTEutk2Ht4QJhyTA==
*/