//
// detail/cstddef.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDDEF_HPP
#define BOOST_ASIO_DETAIL_CSTDDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_NULLPTR)
using std::nullptr_t;
#else // defined(BOOST_ASIO_HAS_NULLPTR)
struct nullptr_t {};
#endif // defined(BOOST_ASIO_HAS_NULLPTR)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDDEF_HPP

/* cstddef.hpp
+jy5sr5qCl3jBm13hcb1uAo3702q01Gy1jpdqlWeNJlqwo+m5M86TVbeFefJnXYstijsW52opDB1k9h1V1x/2yhZ2apxZukb3Pofq7NDYl2q3X9yPholH9ZJa30ofngZ/k0Uii9NXZtqk2R41j9OUK6qdVLoJvF1klf27T8ajX76eV3YBthWycY0mV+OvrArVWSW9el5P0/bdAAvlLPJxNa5qXQlqEoeK62Kjna6qhttut8WK+VMvXRmlY+Uqs3e7oelLZ0qkyfra5WqkVqt2LiqambDa1b6ytk3csaRk+KmS+VWhWojwAVVIK9sW+lAXp8nM1vXAUxVtSl0vH5qNlkTyBnKMbbSeYBPZrOxTfxtocpdbWPBz7lagapUlUwyVY1UWlXDaqbO4KdL71ZadehJV0blHVqsMu9dRDaZaeN0gaE0UmtnqmErq8ymuva5Gj5ga5rkOvOlKvB+eWaKZKJTg2flZtAjua2TJ1UfGuvwsnmdqTZ50Q4vqPDoQpkquUYL66qNaGYq4zFaCKvkXlcoqA7gyXR9WSy1a5KrzFRnF2cf0UubI8+yJL1VVYqhcVHsMf4OyUWL8V0NfpifJwud6vffWTLzGlzl8HBMMsy7vVkFtm6TZ1+Yyu6J62RWqFBx0A92z8bk5Atl
*/