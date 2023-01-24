#ifndef BOOST_METAPARSE_V1_CPP11_OR_C_HPP
#define BOOST_METAPARSE_V1_CPP11_OR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <bool... Bs>
        struct or_c;

        template <>
        struct or_c<> : boost::mpl::false_ {};

        template <bool... Bs>
        struct or_c<true, Bs...> : boost::mpl::true_ {};

        template <bool... Bs>
        struct or_c<false, Bs...> : or_c<Bs...> {};
      }
    }
  }
}

#endif


/* or_c.hpp
es5F++FfjDxwKMKxSvAeech7oIOz/eofkE5tBgm3EtvUSzPJ9a4Ra3qbeZVVZFuiM/PkaLhAjlajOvzH61Hd+64c9Tu8Iliyk7LcWNTpA7SOYVQkyImJCQkgC7I9Slps5JpTSf661c2apGI+0FplTDSoVjlRwJrQlGbUfDazqg0gSr8AxHyMF1Ptv56WAjK9Os2mux4/32rBAs+bgqO2x2wgrhdRzB75AQ7FzB6oK7MSafsISyk+m20BCFFkm6wM012fjLeSgvUAQqjIIee/p6WtxMWB2SowWwVmq852IrLPbPwvMPmi9Ldg8s1JvwmTq8b//4NJ22gTJveMPTFMBiNMyDwhAPLwqGSAbCrsAZD2f50IIJ5kX7W9mJsUAANAedLShwxYm2cJmNSt6E2l/nwwL+nKhmB0dibsE/e3qC2bDaTb7/Qp+/IbfNHZOcRu+DG3rq9+dgnWQCkCcalT6u/Pg38e3XVyPikWh+uuYfk9PVil+h1w8jT5S6wIuxGxQUEFq68UOTHqI4Xk2UVOpIvQxDdcetFJWW9z6hrmpymtbfdTdt+JRzB9nnp56TuosAVQ+ZBOf6a7xnHvado9rx3VY9uBWPd5CwMX2rDCaSCyDXZqUWkASJTe4CvItoaP6A1v4jEmPyqr6RYU5Gpk23rZvUFaMgcVKWWdizvRTLjoPCQNb2cSmpwmq1Ml2d18Rx959UE+BiU5sveg
*/