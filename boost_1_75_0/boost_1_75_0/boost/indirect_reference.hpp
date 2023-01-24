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
Ydf/uiBV7LoFc0s8J/L6xbrnEbZaJiy6+mAwL/98dpxptw1KKne1VWgIjeBLjx9+FIOVton6CngM36AfmczyQ/z4LCXDlycmaRHXemfI1m6sZOrkHSczk56KdN2QGcNd8785nj35UrKv/+mPsM+T3GnBjrc0Jz6a23Blgvic6L/uwcF8fK0RSunJ4EdfGA1rekyjnGLG6xb1G5GTQiV1k5IMacoFbBBHtPpU8YvgembadP7dEoZaueRm+/nMlNGhdlMH5IQAR+GtKYWt8rDEPdi7dfORBFtkx4nu1rThRpfhqkrs0YzKeZPLxMiuo+tLi0cGHd91w+TTcxi1P1FyGkqHzuOHZu4cY+8c58ZPSs/dmfZ3D/1aEFfvEqGxKIIWbrB7ptCZBkfWp1kzkA61zUdYB5ddaQyZYKd5nIy6PWYDv+L2vqY+OE/JmKFhFzayXNl4t0T0RT7Nn58980aPKX2O34o6iOw5CuEtCK9hC8RNJWPnvfoa7Lz7pMSTlnaae98eey4FUUKdXAUcskwU3RjNlI0zWeJ4YpRleqxWR0tlnHUCb7yjRBQta5yg/qR0WT8SOADcQKeko+RJnhdBxNCioN8EI2UqwXSVaqR8ICTQsSqnBqOL2so6JDJx5DGt780tXOnxDN1lqNnDGc0q0q+mq6a8XRmbrEez9bebx1XaISw/mp8dzjwKMdk0KwiSD8v9AT/wi9k+p4fO
*/