/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_UP_HPP
#define BOOST_ALIGN_ALIGN_UP_HPP

#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_up(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T((value + (T(alignment) - 1)) & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
+/Bps2Z/xTPhELbtrQUSqJX8bIecO6rFL38KqA1h1jWnqM92vXghjqfQAkQbSUXDJKsEu+/nFC9RrBiU10HZ6sgzgHHcIG3TE3bQGrCJytkVuIQsJ4/TwAFf4l0YITXhpQE/dG+jo6BH8GOksggTY+h7+IC60IxRw5NyqQvBgncu2no0eb7JAPGsHgo8kjm/9ax/IhacoB0+SCb5C3+KB84btYoIW29equxpiGSN8jEZbledoGuJyer+CaVZg8z3xF9ELW+szhsNMNqFTA3PKSGpokNdQqqfQauQoEEeNWWynz5WI67/yEF49f3xJ4v9R16k+xPlC+bHtLpnEXvDGanq/U1+5c0PSBRr7IxAp2/4tuWyrLz0mlC/ZjYqGcVYkhSbbvTg6oZC0B6Fxjjam4qjaI+GQ/XHKPgudCAApezQF5sTS4pr3YtAKtEmm3HTBwZziqsmiPGuZmawRrOMsNKrX4xN5c0YWFZp38AsaUPKGTVXFnEkOlzyaBAuIJrE7tMSJAqnKjiuBER2bW8izJ5sw3MBTgVRBOeeFDyeqz/Ytk1Uo1ID0oXOyw==
*/