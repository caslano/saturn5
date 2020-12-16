//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for any of the elements in
/// the range [\p first, \p last).
///
/// For example, to test if a vector contains any negative values:
///
/// \snippet test/test_any_all_none_of.cpp any_of
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool any_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) != last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
63PfzZr+MpP+T3zDrZvjxyeUzY6osokZj5h3o26W67vsSeSxpbjZ1tXi9itfXd5L+onV0T6X0C/0NbNcxizmPZDuobbm36PpW2bSF/A3sfbEjmXMezpniEyW/xH1N9n4C7bsR2SMc4hKOisQbnMb2P8oEewBHmMc9bMuoGOcuhsyTZ8fI7MtEB7jXDw0dowjctp+94TDSlv/g5iwzPuoiwhnMWZOlL5n/Un650pn/yxu10P6Udy4V/ru1N5WzvHMvBxjN/qfvb7a62c89A8eehgvfYKXvsJbL9F+a9A9475XLn/1qV933Vxw4epLvhd4wEufU3s90gjR8wz6rGOH6Z+u+87dY2Y3PpJ8+UWsv5ezPKreOaf1DfPurHNJ2nN21qe3/9xbb7Zb5H+9b9bhO8qaHfr71dtGvtr2/qPe+rQ7RP9T0fSyTzZM/eHsSzqffVN6n9SDXnqh2uvfPPQ/HvouL71T7fVdHvo3Tz1SheR30+03vvzuU3l5G546a03pFbcd8dIveevlPjXv8kj7l/dUWlm0RfNd2q/5fr6eSzIEo+vJ9Te5/FbnmmM9ueiK6sJesA3sDXPVfhR2NL9z5be3+G8T0n/J50z1Nxh2gENgFzgU9oLD4WQ4Ak6DI+F5cBQshmNgORwLV8HxsBJOgD+BE3Xd9yT4OpwMP4ILYSM9r2QELIAL4VR4IZwGL4fT4U44A74Kz4YpPvpT2AeeAwfC2fBceC6cC8fDFfB8+H24BF4Hl8Kfw1L4PCyHr8EVWl45lv4OAln6XpENG2p5tzJymBrK5ddALg8zL0puR8z7VF31PneHGbCb+tuMWa/+GP+Kv3qYdeovS9+XaQ6zYQvYA7aEUzT+qbATXABbwx/ANnAbbAtn+UPuq2FH+GPYCd4J28HnYHu4J8E6uX4RM3EZBv1iGSasb6xeFtE5JgzGlKNzw7QbHNFBXo+9qjyii3ypPKSPLIvRSR4rj9dLBobAoFmOHgyzENMH9/wh+OP7dswcvj8MvXSXry2P6C/TqVx74XPYP8b0wT4RU4apDF7DHMEMGEr6MR8juw42XxnSd27he0c4cqVT77l7KMRtM/aX4DHMQdx2YE/IJ94K9HyYsF60K24HYH4FsnAejNWRrsdti9GVEnZbf0RfyrVduO3HhHWnxyqww/RVhIE5zvf8IJGZB5sPw+Qhz/dBwwgXs5fv1ZiwnrXxavSHmLC+dfrqiM71Gr5vGYZ/zHbsL8FYHexeZA5hjgTdLwjpYzdh8i7AD9yDOaL62RLcAj25HiR61q3wevLYsSfhBv3C6TF620O474ZdR0T0t/kjkMVE63HXYW8Hu64h/ZhNmEHYr8F9B+Zu7LOwH4QVcA9ux9aQNthxbUTn22fkyfW+H6vud9bakP6346iIDrgcXoPZiWmIfd1ap074iOqFFx5KduiG96yN6IcP8r3xN/GD6Yp9OnTTF6/BvQz3LZgqzHMYNx3yOuKyxpAP5Cux74LNsR+CA2DgW6QRM0/1zGO/hSwsg9E65524VeF2rA/pha9hPwLT1+HG9zwYrZMeiz0flsOGYykXGNZRP8z3QWMJA86BFaqzDlyI3FjiwVRiH4n9tXLeL1meZuVg8jElmC2YquWn9dqnP6c/pz+nP6c/pz+nP/9B/f+y0oVf1/r/wqg9/nM89P8FjZz6f6JXHcqp6/4bq+5/NJ7bwi4wqPuvbBTW/avq31v3r7K9vHT5ej3X7IX0oNgL+Z2arG629aa4fYrLy1Hz12VL0akY3fTmLJnfxg924+c9/OwVP3UlR5SKFdHT3Cd+Esy+WQ+KPVHTGoqDP+YM7p9LmJuthsi0Io1ZGvfz4l6EaxLxJ6t8OA0=
*/