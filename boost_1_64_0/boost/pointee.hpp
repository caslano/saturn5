#ifndef POINTEE_DWA200415_HPP
# define POINTEE_DWA200415_HPP

//
// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// typename pointee<P>::type provides the pointee type of P.
//
// For example, it is T for T* and X for shared_ptr<X>.
//
// http://www.boost.org/libs/iterator/doc/pointee.html
//

# include <boost/detail/is_incrementable.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/eval_if.hpp>

#include <iterator>

namespace boost {

namespace detail
{
  template <class P>
  struct smart_ptr_pointee
  {
      typedef typename P::element_type type;
  };

  template <class Iterator>
  struct iterator_pointee
  {
      typedef typename std::iterator_traits<Iterator>::value_type value_type;

      struct impl
      {
          template <class T>
          static char test(T const&);

          static char (& test(value_type&) )[2];

          static Iterator& x;
      };

      BOOST_STATIC_CONSTANT(bool, is_constant = sizeof(impl::test(*impl::x)) == 1);

      typedef typename mpl::if_c<
#  if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
          ::boost::detail::iterator_pointee<Iterator>::is_constant
#  else
          is_constant
#  endif
        , typename add_const<value_type>::type
        , value_type
      >::type type;
  };
}

template <class P>
struct pointee
  : mpl::eval_if<
        detail::is_incrementable<P>
      , detail::iterator_pointee<P>
      , detail::smart_ptr_pointee<P>
    >
{
};

} // namespace boost

#endif // POINTEE_DWA200415_HPP

/* pointee.hpp
OO9QWaGW+GahKlIidk6tIiqBATWpREVQy9CoZSjUkhvra4hdRk2Jm3Xa26bThu/VhpL9DEiyFhTmogAXkqD+D7A8Ggr3/89EI2zdr6fJ+eejCVIU+jS5X19GWsR7v6kb9rxfKVp0lKJFE/yKFh37oKJFXVyJDftxEzTIw2TSIFH2vPZMggaNnXuMCRrUVUwlYWd8BsoQ4gKog8D/oaa7qpH8zWD0JSUIggJNEApEqL6oBzC0xlHZIn+R+kx5SqjPNL03gOsLJmjPSI0gIzWCjEzSngMgPJ+j1eSmDvYwF1x666Zef8DriHyWpDPczH3VsrNXJ+mMH7zeYO7YhSCLQ7mhDyIfyA0elzQohNKrjJUJ9tWwYIPOr3HugG9FwFcJERGbv4FuYpM3fTXIVBlUdHP/3mBEUaSyBZmbA77XAr712Li9qCcLWzl+HglDPyM6zs0tHXu2wTpYQVXAtQIVgLkvQA3CAoCKDuf1EBQcE0vvGfDVBuCYx7USxb2qeLaB/Gz0rh/b9tUDLIBKZwZ8G2EZhHqEVwCfgvZzUpsB0Dxk5+hsGIHgZdW74A1BZwrAFqJd8D5XjejtQIv9BAHYLGz54dMujiUP8uGPjXFp+hEC/fj8Cbmf1FgCGrM+QWMqAZoCczKrLmsCSubxl7W2YxqTZn2iKuDEmqFUGrNWcy7mlyEypiIyCRoz6xp6H2i4mCRGmJiHSrg+BLezwLc0nPU/Q2IS9EVO7w78OEFfPmhS9EUbzysSsxUkhjfx1NFZC6iN/bWfKzqzS9GZLsWKzrx8r6IzG5N05mxQIPvnTNZ0ZpV91W/a0JkdbekMIfbc1p7OqFDiAA5fsayLvpj51FNJTkdnWyrWOknNp0AzKGj4eqnUxodIVA5FbUo0tSnR1KYkB9+5+M7Fdx6+80h9PgT1aSHvRmmZN82U/VcbapSfQo3y7OEtpEZdQI26aGqUdzA1IsWBCHq2n9EQ/bhAZpISDSKByiepCho0mudNsVA6qAyJV8D1qsFw/L794kXKVUMiNtTA+5AsyWp+FWRKJBCcLOGyWUikENIP31rKIqgsi3TAtcmIoiKQAVIq32bkkd7Qgj7gWm2y9FqUztL0Zhb66Ec55GeboG6uDQHX5oCrni9RHHD9AaYsqM/L+kbHsq5DJ2lybPpWgWwFXCBeVLwJBQxlawr4vQDIjqtSVdqP1bFbr6EaoU4qHb3DV2gg+gvChlYURD8NAVqLxgNM3igIhLxc9VJ/wBv1RT/ylDim2h7IttVIeFDtIFYhDaNcniq3OWip6QUMdItq0lEHFa+x44cM600tNAhlNwi6qHGQpozHCGXcJELZmIwg6DGZGwYldC23tz+mqGNgVgmpo+AEqeMmwAC0OAHnfTxBIbs8figKqRBLTvuXo6Z2FHJKgkIub0shifiGRnxDI76hEd/QiG/kcbPmQ16N4WY7tv9KIZr3fA6iyS5nLOBiVwt181O8AvP5/wrR/Bs+Kl7pBLGjoogpmv8f3pOgu+WNCRETYYiuc5uUhE7n1Wf+eN1+QsmSix5VepjfnK6cHYy7g8nQMTLZ2ghyu/8MkNtCJif1MPFfJPQwMwE2N98s+qS8pyEpcAjYUKbKEnLeTRQwK5SAWcHMkcgEfPiiZV21LmbIL7QuxiflMqmLEUcQWmswSnQx+M6hFhDfuTx8wXceD2Dwnc9DGHwX8iAG38X4LqaB9A4jNqoZzcOqGE2HsK5Og6DxSAlVk/ug5Cxuaw8cy6qhtPkIpc1HIG0GYE68y4js6wrC21WJm490JG6eQ+nsEdPiXx2kqq7GC12VdHcaF0rlrq6Q6ZAX+q2KUdkVgiByqlByqRmleFilUioJC7g=
*/