#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/or_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          template <class Chr>
          struct apply : or_c<(Chr::type::value == Cs)...> {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
Tx+MBuPlVoGaUvEvbS9i2ncF5kg+qRtGbNvGvemVIEZCeR1F7LEll6iL1lHHZFqwvC3uQl6hz2ksAkPnWJ+jjZlLbkEPV44SZ9mTwb6VImM1up1Am48ukXVDc6r9zFzP0y4EnWgWr+luU/E1t77Q3cLwN0oXNF3xAL/lUUrRDVAQPMC3ar7HAxVyfd7fFoiOzBLuQqjZcmfG/b9pK33aDc03FuShc/1JXtUi6ItBfGmJ+LTTFe7MeHw5ZvOr0jPfAUKb8wu/DAYFKZo3bnDLW2zEzi342DuTSpaUdq9IV79ObcbUhaJi3nYBFJWM+nPB18mK+zweRFZtUK4HjqCrDtaHpifYuXMVcy4w/rbxvMrFN5RpceHWFbJgQ6XALWJscGeroIUij3cUSTNMmP5rTeCEvFk5Oq5K8ADQEoer8ohnUgt6YvLUQhlrp0rpo1fLlClS8fcmXoNu3PECJYT24N1B1gq6SrL7aclPGoPFiAcDo12s6vhIa2W2rL6MJLzECNhyEQEvNLAKONKCsigMsr/4H6AR3SR72W2sGxUqhGBpeKZKFl+zHc2OUg==
*/