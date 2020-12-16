#ifndef BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp14/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
z9h5VgbPUBpjLeJxOqZP/FkxejDz5ddsdR4tk3of7D4Pz+ndw1li6h1zb45DT8Ir+bwflqSx5S5zafiyXKiNBy7FM8vUhonswN6dk9Sbk+jl4eJuEN11SP8gP6w0v9sGwI9J4gEeNRPHw2iI79htRRM9Qzl65UJ1aS4xtUws30QPdlDL3sdm++hN/t5F8x9fAb9c79PkYP+luveUmooWq1cFBvyJpLuAsqpa4wB+Z4auobulu0S6QUFCursbh6EbCZGuR3coKZ3SrYCAUiLdII1SAu9331tL1owz956z9xf/+PaZmWbqv08IPKd9adm+vM7n6+jn8dahv77LFWKGolfE48hSupIu+QYWTL6otx7Q7jAqvb0OiSbG+CdBPXqlltj8Zg5fTR8UobNw+ADYkVHd7BnJ9/ra4oDzavP+RgPp0/36/ZJaqYs7pvrYmyY5bv2+3yaoO0fClRBYiaPeJIRLM2j2LbCjt96p5v6XzWK8/qgZ35AR//+Zk2ID9dgRvoT3uF+a1p7lnGGjNRdyXrJIfeC0ycVowVzqCRalnWoWiysqNKCNp/BO8/Hdt3JpLYnX49S6eESdnD5Hty4ImPuZj19QU4P5Kpxbp5T7zcdDSeDPYrxUSd/ReBGpYb09jNCPCyLVQDw6wV5SieFy+93U2d59PuKq1+CvT50VzJ8ml2L+w1/B3wODi7LDcV6g4RVf01tjZ+M3+J4f/2wM4YVo0kKb5BP3Tl2rt+1plRyUq+bMpanebU//tcOHIXCMVn1UHz7Aub0x5bqv65uDvccjSZNaI0+VKgcdxh/V0sOLg89iRuLyiup5hRllCbNtvqzETNpeLON/h7/a8uK0cA+1+ZZWHQlXw+ndL/B9OP7Y8ze8rh9q7iSvL/DPTPXQFl+d1I8Bz2KIUcPpzmRGwTx+qRN8Gr5GLYnfIHXp2ZnA1+PUrfiEHDY/9PVI1y2YFmcf5vMHOEecLv9JYV8Nnms3ztipbp+b/9MRWWiOPPfFoD0uPUM36v8T5jizn/Hv8LmP/efRb1H+pXG9phIP2xAm9osCo6Ly3WPM7czHxm51fa/Zeoi+eupMP6c8fVQD+P1WRh55A72hZopd1Nun5eRnXpMmPYsTkxyjnSeaMe7EK5/i6UXuuUqfq/uuD2BUWXrgR7OujTBQjtrA14mPaV/5C/nBs4xX6Vc8/5OzpZof6NwXeGefGB/yLDquq1PFbPSmWKibQ7Hs15riWcuGAu5jjr8zMY/MB27yb7W+zRup79Z4/5fB35WD4KOrPxpi/gfPrsCwUbT2voK0knWtasOflDWLcYa7+7Z8L8dtxeBnCXXSTJwS8S4FvOa5fctL5BQ6Iy0fl8R64NmJunRbY7NYM8QKMKlybr2kZrdGwtSEuKOo2s4cYiYKR/nBEP5t5US8uZXe58HqroXtS/Qsfq0F5yvSNDV+xsPysxwOXt2pL2iDvR/FxV5Ci9PD52jxz+XMNY+M01MDcClMmlaGzjgK7yLkvzF/dJYGp7maOF/pmsYaEvB0C61TzlPi2YpZ1Bau6fyr3uQZnlnX3kHwuFHALJZ3PQ2n4uKj8gF62Xymtd7oRL+9wxPdPfuzTm/fl/Pk/HUpuqgNjMjNM5hxpnCfTwJy/tY9eYXcpeD3cP6sq772vTB7/WwGbDqAP3idL+irIs1w6Ck6Ul0kpNF7wpWoGfG/c4VfaaMD9Fg9Oc3/pWcONlj/dfFXp3lw6Iv06mIGjJCr2/I2qwpfLY4Hi4aIF493I9Rz5/oOZ0Yf6swkv3uoxX/xXSJ6dh4/9Gd986fBdLNeSBjkFzVe4zdclZOHGw6L/gl4zp0vp3emJ+Qp9qlZ9x/3G/5e6Jrw+Mk=
*/