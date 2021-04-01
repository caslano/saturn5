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
YCgopWmmadBC0xsAyxU3mYjFITvZW3YCvLoc7OEpL5TNYOKxFl3tZTGBhz7TW7LHXMf/5Y9LYq1CAbpZzY4+gUnMeVs2eD9ZuY8z4VN+1UrgnMyLgLHOjIqS2W4Xjnpg5wO9Wf81keASyGQi40DDINH2kIkbXzIyPO1fFrDRr7EOK25gnD1LoHHggND7HZ03AL3P0Op1zhlpdFufywrhM2iJZFs/Kiwld2docLDW+/m0axWu/7tLgcT27nBD0eCEdoNWDzQWNjsW5WEV9IIYTd94Z/TPos+iqsdOv/9dLpSJhCRAFVPwS2+9tXPy/sZpnbxlGkdsFfWMW6/oFHPCL6iABkQf1o0cNyZjl97IPfnWwybne3OauLe3RZhvruPwm/qmYtKfMLzoq03cV7ZHlqzWqCkTOrYgKLd2snKkRSCSZ4BY8TAJ36E5zXCLw98c0o2xJIzIqOd/6xb7VJGbraqPNlN4AbCzRR40AH5r/I41vMWp6Rre0t0E9TYF2JQJzAGZRiAh0udKcaQbkd1Dk4Ek5GJFDITtUS2/8ORh5S+nOZG56QfRz0xCZw==
*/