//
// io_service.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_SERVICE_HPP
#define BOOST_ASIO_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// Typedef for backwards compatibility.
typedef io_context io_service;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IO_SERVICE_HPP

/* io_service.hpp
xnq8PeJ3XaAzFAhKClSGHDJ/h2ZA/YGrzq7cCA/R/7eUP9ZnkuLLKPq7F8Ok+FqgI7B9onWPXWwDh5dL75i3EI+a2yAFxFOgZyZZcdDWIlLShU63rNAbfoj8fleCQbh9ESMjCHlobBzm8MhDw0OGw1h9cmgMvj5PY/Cf58UYJOMYrB0ag/LzV4zBry5Sb3+BYzA1PAasN3QCOOjw+FqM+BX9TvZy22/Mfj911X4nR/R7UajfyRH9zvhv9vt7Q7Rj9xX97vmG+v2rbyL6fe9Qv9d9c0W/9/cM9Tst3O/vXwydOlBtKnXd88+7Pvpts+tP/Jdd91yt67eIrpPF6VITxEPLTcsnLRryOsBdU0i/3LTZ7blp4y180YXwIHyEBj7kBco2SqxTK7Gz7WSN996sg6Y9mbwMTp/FJwyE3QWhZqFjPo+2YCDPUDQjbYmDLZECb5E9oJoTfCCQaVGTofMxF4i+2Eu9/Id/pyqnBpcQJZigNy3FvhCHbivmg2eQXAChGAUl8X/7mAZ6RvANlpPSAc0m7jo3De1dM3QlbTbGVK5NS4HejLWy6PZsn7WhNm2shcWznHxEZEpsRHk9sDZtqaVh83I0Nc8nY8TcNC+enOpYHptJSqGRmW67GuPs8aBZ8E4oDopMtgYGoxIfK7QS5vFMgm5empaCtrYIDnwjsicbZWzn8m5qZ5JYXtDL12hgRe3QomSLMpG6i1FF
*/