//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP
#define BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

#include <boost/chrono/config.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/ratio/detail/overflow_helpers.hpp>

namespace boost {
namespace chrono {
namespace chrono_detail {

//  template <class R1, class R2>
//  struct is_evenly_divisible_by : public boost::mpl::bool_ < ratio_divide<R1, R2>::type::den == 1 >
//  {};
  template <class R1, class R2>
  struct is_evenly_divisible_by : public boost::ratio_detail::is_evenly_divisible_by<R1, R2>
  {};

} // namespace chrono_detail
} // namespace detail
} // namespace chrono

#endif // BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

/* is_evenly_divisible_by.hpp
J6vCtjAchMitIbEWKhdLuBOOMudK+/rkJK6rHJmcJCa2J3FXiihzxYOsrhFNIbZkSkfOUG1lSHw+pMIkKuUnSoTFsl7mymbhLiw41MmJqcjKPG/hYKqkbVKQNGurFfJJKhG9cvywRlv2tslMcXAQZW2B0rrScIey4FxiUPiQap3Iyp/3hei8tFX2Jf9Cy3axJ2Q0oqJef0bDWY+Wwiob0qfh/OPkak6f+peX/fH8miYfqD++bvF+HY7PwQ0FrxXJu7KSFlFUpIoyVzI5cP5NJz2I5h+Je7qQwm4XcS6Frkt6Qb3TU+rXKxD7+cse9XK15FP0MvrhZfR8b+EC50UOnNlHGvcvBsFjsGc0QJMEdSa8CYbqJJfebHY9nkxnw1kQvafvlY7zOpH0lo82bMveBdgaUm9tVPI42KOzq8sRPe21kNQ7ftOEcz6YnV0Op/PhZBz4hqW1jpnzVNTW0VL6JucC7/c74EQs8pxSFB9N9KFaNMNPytBxq2EUmLI0VoGoLVNu0uEuLqWVO3pxfJNOd7hM084rOwBNNui2B7Oi8AhN/GyGgVW6rDE4GUZP/Ce8D7WSDpRmkjRZFl6b4txYnuMck6O19FHYZvzbOmXwUnuV4REyyHGZb/3qrSwdUpQag+FUTtps0MRa58xK
*/