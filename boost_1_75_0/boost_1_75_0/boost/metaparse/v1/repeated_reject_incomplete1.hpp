#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete1 :
        foldl_reject_incomplete1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete1.hpp
trI+6IBJ8AXOajTCdqXLWdWts9oLiSZ0Gk3cOJ7P1cHvbKLPvj58rr75DudqAMzV25k2M9QKzdWfk2nsD/Djz/z43WQjHkPmKIwTCCx8Su7vZDJ38Dpu9byOGyBVPXI7t1asl9aK+pA6bg7W4j0KQmkFh6MOCaaICDJUbOcex2L2eGHBoAj/HJxwut7HMN7n0JzuMS1sGgJyNA7fy60ZjVkGWUBj4pn8ULVNGDQcJZfTUo/n9pA+Ypn2UYR2hCaHCDI5bDfMKHEigaIPNyQ4it5Vwj6VV21NYIgXxhO4SQYXxONr4KRLhXSF/MfIyDFYBBbkj1H9gy1LeoBY0gMUmVMgdOytwibxzlhLCCEg7eM+eRflETTdy+PPu33LR4uR/T8nSr38sQlEGJvvpeNH96IFnFOf6CkoyTu0WRPpnqX3huYumhzs5MaKGhApHewtuO5+BAd7Fq99zvS4eQQOlxqDKrRZZ67WnUdZY0uNEr0hNpC934IZ7Tlu3sgV5o18Rpp14yCb7ghO1U+dpO01N9SdDjuVKU29cahCdWKFG53cJcI1vrITlfMFZ0rhBrwY4Sh+20aefHIPWMrLSgp6GD3Q+ziYvvQr+M+GKZlVZ1NcGFnjUlubcuBda4W9mOPoBJ0Xb5WWOayELQAj+ptuBwOdE8w/hB0xAURuuhhiqItgtEdfBHvd91For8u7iLvOyoTvRfjHt7AbdELx
*/