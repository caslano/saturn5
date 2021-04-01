#ifndef BOOST_METAPARSE_V1_OPTIONAL_HPP
#define BOOST_METAPARSE_V1_OPTIONAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Default = void>
      struct optional
      {
        typedef optional type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Default, S, Pos>,
            // is_error evaluates it anyway
            typename P::template apply<S, Pos>::type
          >
        {};
      };
    }
  }
}

#endif


/* optional.hpp
fxL7t1v8hr9GlcM7/Ebr368x9DKETvrsL65lvx+yxv3OehTbxgOIJvXz8adnxNIeZmkNzz0bUmW6Lv7fNijLK8Sg2nqdqel3la5BxpRNN+XKw1posXEca3Xiz/mPSamaF3BnfKbS6DqcLw3u/ZwzGlUoZAtoSdAnG5sxwyzLs4r2eOQKwV1EWyGHlZ6JMEysxmZ9/W5Q644kuI4Mi39Z3KjtJmD3uTcRmtghvKhgnpXOAFpYtt0EmymNCNWzsaPOPYXv1hjOzykmUCY0mN+dNcCzLteWw69d5V6AlXXqxJ5LeQ/66Aw4UdUMEnOp3lBscgDjCb+SiDMzNuBq3dC1ArJIJzsxmcUi3SEoOTOryp/qp8TuyEtAFCO6ctosD+PPqhrLJ96NqEItjGC3c71wRunnENItwuljGmXOc40kPIuFPRWdjWw+vNXkNF2sjJ7rJyx5FhH32KnHGamgZG0rT0BucIFffDCQbVqTuoi03eTj81cw9OOq79GhEAXdfM4T8DVuAHGIanoe8qrCIvKw1k1GmxZbvxhs3PkzlmNlIjcVrijDFTztjkIaAA==
*/