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
8umfjGpCN+ncghy5lHFbQUWVtixGwvlczDrgQVa6EKFiRAaFgliShqBUfVkq5lJffi2B7S5BlFvzECGQuSPathG50ZFz0H/P/Er0Xw/9TaWK7AbZo88Mq5qF5h7Ehw+aK/HzR8RUsEOtsjbs9vVrXiQ3mSZx9J8Qvbv4NV/60Laa4EHT3KmzOvhs5hsgzi8982eeOb+/TZ2hIFc/5OqRQ0GOQcih09Mz4yr16sKCtuIZhTXw
*/