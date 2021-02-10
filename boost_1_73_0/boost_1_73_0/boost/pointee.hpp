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
HW0+TGUKFP42Xy4vGwPsCtDj6hRdXay6EYephVe2SEO9JKCcPB2zZ3q3puwhjr7N0GnByEvOde4d5w3WJbq6xcrV+rY0Pr79f54XXc0sVpsd0zAq5SuNtSnIBwydOreucbAUa6HQH4qmIUnWqKF4wksMK0PFYzsaXVLF0p7gZU6PPph1UNYR1gFGUG1j+Qz3o+06HxfWgWjTx/SUzpPXIq6HFfpAjF3RXns5VMmBFEZ1EJnD4+lZDVPhlKziuUQDpc1HT8+ktvyLwvT010+R3oL8lGw1darKPDq9XI8mJxllsuviBy+5XZ8wOj79/Dl+u88b8Kv6xNiZn7z3wr3Pnl/f79iPbLaaTP5svre41wklfCwhLVMXAI71ovjiJvH9LpQ7YS+Nd4mfYSKKF/mzJ9mmhrH7VVvNNBRG1mJpDQeONfrxZecA66O7AAVlVRRaZYOrBLYdrbTs1QIsj3OnFMoqT3WnGJqoycOTHhmoPB/82UdN/o2SL67KqxBU6AjNkdc1n56nx7Id3g2WrXZD9IfYLxrOutPiNclMjtAjJZ/qBKP58UPaV1EMFZOqygmXbfrQhqniQZSYCEQl+6D8DGKph5+v1JymqqNidfao6uhDPYEtLo2rryOSiDbs1hmQcrNPQQrAytDZYBPp
*/