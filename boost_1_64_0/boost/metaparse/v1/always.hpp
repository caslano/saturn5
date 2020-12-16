#ifndef BOOST_METAPARSE_V1_ALWAYS_HPP
#define BOOST_METAPARSE_V1_ALWAYS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result>
      struct always
      {
      private:
        template <class Res>
        struct apply_unchecked :
          accept<
            Result,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef always type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* always.hpp
vsYZtK+q5F/7cvo+xVfjgyNn/UyUvs/w943fgIfpW4u/5bhdP/Pw8Ykg7rhdP1P3h0TQgNv8G1tO30L8cpzP41H6+pTT9yB+kfFjt40FPcvpex+fYPwxPEzfRSclgvtjG/p22znlL8/4r9rfdyb9Y3G+9kH4VMft+pSD8SmO2+enhEfrr6vMv+G9RP2YnpWoxGe2rHL+X2+8v3HSV2kf7YnvJuK/B+A9Rf+ngKvzWRvwm2PR+jP7fL+Mn4JPipz5saj+WYH/wXjzbaL6MXYK48vGD8LD9DXD+xlfglfab6eSvqD2+Yav4oy/8DfuPN9blNP3Hj7Vcft8l/AjHbfP9xf4gY7b5zt/WiI4p8r6vW3C9ys+A086fkTXqH6cgx9nfEb/qH48Hz/W+BI8rB/n4kca77Cn83zPTgRv47XmP/+CP4iPCt3Exz6M32983S9R/j2B32l82H+i/HsTn2P8brzy/js7EaSc8mfjK3fDN8Vt/oXth93xFrjNv3j4fOAxvFb+7Y3/Eoj842G8oEr6ti+n7w48j7eMnPjKaP+uevwk42PxMH1349ON34aH6VuIH+24ja8snEf8ktpfE++s4m89n1/s+XzJ8/k1ns8nC4ng31XWd+1a/n/0wV8JeP4i5/mOymd//B+O2+d7ML7Mcft8T8Ovd9w+39k5ieADp/1o1w+fgS/CM45v82o0f3c+Pt/4wXhlf2j8FuP34mH67sdnG4+/5owvXsD4SpX827OcvpX4TQFtYsfn9WDeLWx/43ONN+Jh+j7H5xg/a0CUvk0upHwaX41X0odf6abPli/8crE/z7P4bMft/NJz+OmO2/jN5fhJjtv4zdxFiWCrWO38Ox//rEr5C/NvLr7G+A1csE05fTfirxn/HK+cj4w3GB/T1jlf9mLi05rVTt+HeBd8UuS8n6P0fY+3MU78SuX+/oQnjBfbRunbfm4i+Dy2oe+0tfN+vjQRvCGe35X4vVXKX/j8rsLni/L3Pn6LKH/xyxLBiaL8FfFLRPlbhl8syt+q/xJ27/FSj3kAx39zOpHODNNFpU5MISKZyiKpRkSc1p4QUTiRUC5Tcm3TsJFL7BQJ3abLstIyYUW5nAoVLVO6uGZyvzuxLovYz2t3nnmevq+Z7/PHvjj79vv9nt9vfpfn8n2+D365cv+9gY9Q7r/38GHK/Ze8nftDaX+Pwf8VlI8vuwn/p9L+W4RPUdp/j+I3K+2/1JSqYF2J9kszk98MX4q3NC7azzvwoxyX7ed2d9C/5LhsP3fEWzgu289Bmva3036R+TGq8DPwsOOdJtv6V3N8oPCblznxz/iW0M5+fnNbvrvxZcJfwovlu6sqeFO5fs3wF5TrdwfeV7l+0/HDlev3AF6tXL/0Pbw/les3E79QuX7z8WHK9dtzRlXwvnL9uuArleuXva8qeCBUvv97Cb7QdTl/Ap/rupw/gd/nupw/gc/Ay/V/18+kf1cp3wr8WKV8L+G9S5TPzF9ajfdSyrcG76mUr2424wta/ge8m5b/Aa/W5h/iR1SU799dj//BcTm+twHv4bhcv3YLfpDjsn07ag73pzj/bsc6/UMZ0f8v4zNwrf2ex3l/lc3f+z3eAa92/Pz2dn7MD/g+wufjZn7Mj3h74d/hZn5M43mMfzou8+9kFxB/54yPyu/v8/j7eEvrzJ+z6xvV428J79yH4xX+WoFvEn4d3s7Eb+BPOC7nz8Uf4PlpZMsn15/si0/CY453bWGfj+Pw64Vfipvnoz/+Z+HP4eb5OB6/TniHls71W1QVtClx/3Yy9zf+VYh2puM16+z9ux7/QniPqM1ftAH/TPgkvLLw12b8Q+Gf4MX2xz/E+LQcH8LjWv4=
*/