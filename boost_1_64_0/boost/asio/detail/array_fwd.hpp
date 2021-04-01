//
// detail/array_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_FWD_HPP
#define BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {

template<class T, std::size_t N>
class array;

} // namespace boost

// Standard library components can't be forward declared, so we'll have to
// include the array header. Fortunately, it's fairly lightweight and doesn't
// add significantly to the compile time.
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

#endif // BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

/* array_fwd.hpp
BcYKXYGgzH0fueaQSuygCk3V0bF5uOvkf9drAJ0I39QyRFrkEI0Iu7WvNa2Jo2cm1Zj5p2eyMk4kid/nLg+M6/QgzJFCXc1LqIRRwvJWBZlTegS812mYmRvk7Dlb1Y6eXHZE8BGlPzKjviB2uJSZ5QfErr+E9s9MNhBQNKdN16TEuEHzT4x0Mk0NPrrNIw+bqYDSzP0a3EhThOVQQu/zIZV42sjgWxTzuNX6QsKJ26LC6c2WGvKsFHOMFp5NfpHDjNbTIdGaFA/89B1TaGXZecSK9QjUndsdOQpK1KrsXVAAMIWd2tSrBxsggsV3mgXYEvzPXkzEI3fjv8ToJy0GOdzVgYne0Q5wZMDiNQpwekOB9dwSJHbGqZnlNTSLpLaCORSpvGA4NPcyJ5zHYKn43B1N8y88LWObTAgW11y/Licg2tceGG7TiLQZFz5mGUPmpwK3rfgbWt1tFleaVSeuuysr/7Ao22Z0M3i6oxAyPEzYDvk7b6evStlZfSS6FBqZQrRvqQob2Z7awqvWbRksg4BKkIoAgZCQTFrnl93fwJK1f4Nt6GUIHXpT8w==
*/