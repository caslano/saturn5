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
wWGYQs4ygKnqYXuID1jZwyE5EIckmg5ufIWZc06EBMgTrXc3+aqtw7jP3aAxx0IkOBey6asyorVNrUJKb++A8tNAqeMEm5U92fLRSXpdzNqezwkDU4xEpZVS4koH/qnYjynjIpThJsYNnduxzPRTaBf1OXhBVV6xEaNy2g1d0rhXMOfKSSONTnyzAtXSimGwCBx4BO3WbWbo+8r4gUD4DxASfbEa4CTArc1lHi9aW8T0YwmeBVGlg/Ml38qwiddzzkLAZoKHc3aMBPE9NCU1oeJY+U+YoyfGBwVDF81AfAtkPPEXpqcaCX+xhxMKU9kft5i+vQ5E0aN4HoVzY43/9JDj8X71VU8QF1DlN8FqucEN63bSg3hquP9ov0eK8Q8a1aU3V269pB7iBx2eLWJc8uBr7Ghx/aOg2Fa/Fjha/CYZaORT+JEb9sKaaHnwsr+Pcvn54np2vigxG/62R4xk7STARtTFuQvq+IpjxIaXI4QF1+qIcq98qUW1xFqdA/VaXkMr72P4fps9wn8WOA9A+SEKHpeY1KjpGFURiauGNfy2pT24kUu7IhkTqJ14ZPD9iFxqJnSQIDeMxOa3aM3HTWDERwcZoRu+fvVq51nobnyJtg8NSEzBewLyfdoVjNJB8rZXqbkZewxGj2R+GNfqC/h4QapZPYnvSIXxEd6kz7TQ5EOQXA+RPKdInTHj6Ch6ekKlOk9LiAEtWPke
*/