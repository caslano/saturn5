//
// ip/resolver_query_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/resolver_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_query_base class is used as a base for the
/// basic_resolver_query class templates to provide a common place to define
/// the flag constants.
class resolver_query_base : public resolver_base
{
protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_query_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

/* resolver_query_base.hpp
sy201PbSTWT/ZLXn/82YndKf8Cxi4m2t7cJ/vw3MG2sMZ4pMM7P34jNi7+F87zBhnO8x+OlzjHjK/bkYl8sk/E8kvRvkmYMpxZXF5pnjx77yUHvgfO1oE/UsuX/KffQoZg0J3IDhfon7se+N4dpHirYPvSdp2etacc52E/IebfJdY70ZZ57PbPyApJ/r9ozguSr7moaZG3Q66WgfNFeFiWrZg8eqsr9dZq1PD9E3J8yJ6/oTX9j5QRuahaavHbLl4dKnCvER0keYWvXh8T9xffjWp0f14Y9XHz683nskffLj14c/3v0b3xA9+SU/unjs4cfvfm/EM5/t2jXhyye+PT35/1V9+CQM7nm3Z7/989Leq7vue/GDr67txDONYw9kvofKXivN3cTv+C36xOZ7OW3Lt5cbT5+ih2z0f7vCEXAQ/CGcB0fCJXAUvAyeBx+Eo+EzcAx8Do6FB+B4eBBOgF/DSTDB5ZNPgxfAznAy7Ap/BPvDfDgXFsAqOBVeCafBm+B0eAssgjthMXxa5X8PZ8LDcBZ8C5bCj+FsWJ/8zoENYRnMgOWwL5wLz4Lz4GhYAfNhJVwJ58NfwYXwYbgIUp48veh3S/1eSnny9kx71bp4TfV5D8DTVK98mOqTj1J98snwPXil6gOvUT3fXaoHXK16wK+r/S34GfwCYqqacc6vYTq0SNep0APLYRy8CtaDa2ACXA8bwM2wEXwUJsHdsLHZC1O/e2m7Wltjr6UuqofYVfVdT4PNfXbCI+/W7zn6TYvwohu6CncO0YdsB3upnmY/nYdwDpwJB8Fy1XNdBbN1fkAO3AqHq57uCPgH1Wv+IxwJj8DR8J+qr9xc5mVwPjgRdoKTYFd4PuwDL4D94RSYBQvgcDgVjoDT4GhYCMfCIngBLIaXwpnwCjgLroWl8GFYBvfBuTDG7bO3hotge7gYdoUXwUHwUpgDL4PT4OVwGVwG18MVcAtcCffAq+Ff4CpoeXiWgj+Aq2FfuAaOgzfa6YU3wQXwFngz/CncDu+Aj8I74dNwPTwA74L/gBtgcxrARtgVboaD4RY4At4Li+B9cA78BSyH2+BlcDu8Cu6AP4UPwrvgTlgNH4avwUfhm/AxaNFuqmFz+DT8AXwGDoK/hjnweXg+fAGWw31wAfwtXAlfhj+Gr9jng/sD+tD67k0atX079aHTVC+5DRwC0+FU1RsugqfARbC9nS/YAV4PO6pedCeo1xHvnxGvI6PPm6LXUXOIwR7YM3Wfhv9Gwzv3TG3q8l0/qTADtoRZME3nlbSCC2FruBK2hQ+q3G7YHr4BM+AX8AeBPSr1XYFD+zXnHpVdkWsNu8EesDvspfNWBsNMOBr20nT0hhfCM2AF7AsvhWfC62A/uFHD79D5Mc+q/RW1vwbPgX9Vd9Xb5Vk48h5j3PeMXPkx5A55667fW9c9yJw6vfvfOD693m9j/7F/hz6v9+D3s/9Y5sFvT6c3aP+xOu49dry6vJMPnrg+73ehy3ssPd5VB+u+z9iJ6u9ux2w9eOL6u/+Nurs19Ha/FZ3d3J5eqxSzCrMZ8xTmMMbq5bXaY3Iwpb2iurbRI3pEj+gRPaJH9Ige0SN6HM/x/ej/z5s+V9T/T17/f79D/3+RK0TXQiacpycExrdHZ593TF1J5I2uRVmzIF0L/IJ1LV7l/HXd6yWcriTxh+haHFZ9zytj+M4GZ8PDffgOFJyPY+pLkhcNMx67rqsq9q4xIXkzsrlWiuov3Cb2tjFF7iauo972qtfgsm5Ist37820whlQPEb2riDqVJt7hln9uwC1iT3c/4Zqobv44z5Q4w+kWlZh4siR9ZdhXi/20mAHuiS5vTHurpeo0Pt/Adv8=
*/