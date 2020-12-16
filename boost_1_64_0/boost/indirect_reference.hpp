#ifndef INDIRECT_REFERENCE_DWA200415_HPP
# define INDIRECT_REFERENCE_DWA200415_HPP

//
// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// typename indirect_reference<P>::type provides the type of *p.
//
// http://www.boost.org/libs/iterator/doc/pointee.html
//

# include <boost/detail/is_incrementable.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/pointee.hpp>

namespace boost {

namespace detail
{
  template <class P>
  struct smart_ptr_reference
  {
      typedef typename boost::pointee<P>::type& type;
  };
}

template <class P>
struct indirect_reference
  : mpl::eval_if<
        detail::is_incrementable<P>
      , iterator_reference<P>
      , detail::smart_ptr_reference<P>
    >
{
};

} // namespace boost

#endif // INDIRECT_REFERENCE_DWA200415_HPP

/* indirect_reference.hpp
uOjCrxyM0n4zmdu2BXTxay7J6lOSGahxhSZnOaYlznY259exDPBb0A71zlW0TcyiOrCoIaKomVf7b3BZvkSDcvb5J6CA29bF9+6ubKxErS+FmegJu+ErrlZf+kVnE9oP3vgAoRLio6n8GDP5ZCeDm+wu/cxpG3kQ5hm2wkxx5N28ipZpEGa8/ls1dwvGNt0tnF+ngX6j9OZAWbBUtlSzmFzVHGpswj7CrHxMTCIfKVqPlSTNeGcKENzpDF9sU7/5w8Eo7Xtn474AzvggyJKLaU9z7OPd/sh9mH6rr/gLXD+rF57DEU6z7Oozze44bFvAac85PMLyLUSmnY7GuVd7lNFWrzIyX531JZnXnFvea0wEDw03Au38twIs0kLT7JEHwToe+Z1S7VNQr0dO1BROGZomp8PoVTN4ZOEucRGldhG22+v0OhJYx7aZNn8XS8TxPVzPWL7J+T6ygfV8qFRFfqusjNyHwYot+zjX8o/5aP7f3pfLnvWvcOUn+Lsa9vXnN8box1UI/TgnTz9CX2g5ZAF+GD/adXsezZW+7LJSwoMzPCkKmhsmPYA33Mq3AB710O8QLSR54VaMruQnQSA8za2867EUWp3Kuwwa6FNgDWudd1+dMf7hVJPXseq27rbXrdEVCzt4qNOX4icn3zHaPnt7JNkprgr6jLa7LHvNo9NyvnIDTBMhcvyga2FvKCpGBgNYDDgZ9bmGTjpyDs8DFw+pgAY6+N8NldhdoeK0+iuw3IG/sGYPC49lzb2d+n8y1S98juFvRazI5981hjg8cxPOCCOKd0O9zkVDDvXBxlkzbgaPIXQHEi2GYL75uRKLCfJC8+fh32dZ5YzugMYLVgO+mZELlJLMyOXwl4QwjI5yGJJ3Pk6JC8csy0b4Z9HuO8JDzfP2i1sPm7tGgUl71RxQIz2QHYZGTiGCFU6bnGZe2W6AWp2a9JmmjKRZ4pCuL6c2t8ShlNgjy12OvDkOLHtwQoY5ydT+GUpR2z2EHmi2XlZLB59WpMgWKboxxeP1BKZpVsZQw7A6NC0N+NmFzqknnwXvo1CVifo7O4Pnw0uRMjkx0s6lOOA0OJKMH7dy2KcUW30wgOOcHzWBXp5zmsvh8J8qG1JZwGryWc3ti4GplO28CnLPPyRSXuOYnOgfL1M+KFKey5TjREoVKQNDfI5iK70GFshLmJuRioZldqnY/m/Rtv+gZFJdXMDt/wVs/xvUj5eTpqqvwYFJdsvrWOuHi0i3LKZvAYVuVaLOYiv6DmB1IF2G17HOtmARMjnLfDKliSnniZSTMzjXocmJ9Tey2OBt8Ej9SLlNI2FvwDhz/uS0OZX31OGfSKK2Ue35LK7rBiKTMcETsC6CJZkm293pCDYK6YVCGDzHBcTZcv9OW6GXuOkZsXff/RkEz7BriwKwdbOMHYtlGXMhMIFmsM3MXP8ckmL14nIFq9UZHhVQLRvEMbwryk90KRvKST1zJUfWy+PmHciR16Acrp+DB+wv98y0mB7B95RZFtOKWyGvj6XwAd7DeH4M/7MQ3h3fHXg2pZhTxCfBkpiU8tN8kpu/trHyt+3a/3/4ibO/9hbmWvojpGG7sIc4IOtcwPbhhw/q/kcHymucGhMXJ+ITEb+Uz2r1/UQRhcz09eA0YUvoZJQzgPehxdgFmhlgw3pnKYWJyKrl/7XMn8GM53BBIvMg2odBYeppn/OE5JAXSIsQwlLbx5fqCY3PbRIah7tEPtcMZedMx2v47aj0mub/c70+VliruptPSaHxxnCnA03kxlzm0/CpOh5ImviDNgsQCzfoLMcrQkcyz1IReiFD8xjKPtDu2dDc0NCM0NDMMvOP6IZ2/7FOa62XqKXJ8Sk=
*/