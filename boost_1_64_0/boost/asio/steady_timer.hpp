//
// steady_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STEADY_TIMER_HPP
#define BOOST_ASIO_STEADY_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the steady clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::steady_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::steady_clock> steady_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_STEADY_TIMER_HPP

/* steady_timer.hpp
Vdr7xoEAgZX9Lq+aTKj9YxGcOeDYt8s4XcX06cLzPXYqiCoViiPZ2xmuET0FcX8CSGxalwo/8JzmHzASq/Wg7G8GCr2AGFeL5RKMU4XMP+nM+a1lIgWZVJjWY0f6Pya6fx+HSctSSqkTM2o8uFCmi3f3QSc9Of5k9J6wbDAtZ3g62YXdlTM5EWX7CJzwUv+DFnH5bvedxCnO7Au3F062BlqOE0N7+Lpp9M4d3DGFaTjv54ZHObJavGw9Tw+BUxL6M/TICXldXrSi2qOuJKvk1GsNAkfiUPwoNuhL2CFJSjMzy2gVd0zxPch09ZvZid0PQZCQjF7/uu19M0IqXct4GWpUQe2AvCTQRW8XiH7cLBM36aVgSwW/f+rNVTnT0CUFu8L+wEG8G7yRXJek37dCAw75O5JiFUZz0JgVBwPP1fhYThiXDV5txfew+aUudiiOQj0GJTKMmE0PtqdbwGqLR/SpkboU0cluraCyuI3+OXQsGUBH41SaSIHCGeig4XzLjAzIzNyO5jcAXOiDKbrOmrc2x/EvctwotIcGzIbGbwRbLSD9L1AjeYf1QQ==
*/