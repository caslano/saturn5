//
// this_coro.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THIS_CORO_HPP
#define BOOST_ASIO_THIS_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace this_coro {

/// Awaitable type that returns the executor of the current coroutine.
struct executor_t
{
  BOOST_ASIO_CONSTEXPR executor_t()
  {
  }
};

/// Awaitable object that returns the executor of the current coroutine.
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_t executor;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_t executor;
#endif

} // namespace this_coro
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_THIS_CORO_HPP

/* this_coro.hpp
jTovjdP5oIJe9ixwy+cKcC4PyHs91fpu8HL0H2jNueobOSbzqrzF9nb0xZXo23O1ujHcrR2kPbzj9VHmO06+kUhXxentoN1avThm+TvLzbF0q+QzjT2mha52p6Wr7Vc6oKilLx15B2R4UP/rNRlvPG6ew1v4A6BBESbf0zGx5dfg2yUOcsN4emBaeVy3FtTaTrxlsqOhJGxj++PdpMmg5l0k2GG/F3cnQMHzVP4ME3aHuh8hMc/acG9gB9frS3u5ObCBjNPnQbnzdBtKG1v+QXynKtMNY+mFP6CdzWXpD0j3o1a8Lk4vvT5OE+dpMrj5LgUL03XQHwL2cRBtUWVOx8L2PXuvvEAK88Efr5C/PFyeyzRPO9eZNU/z8kWzGOPf6CC5Mxb24sp2axJ3E3CmNXZ7nP4Gajx/nuYnPwO96VwLP+sO3LOTYSAXjOUhbCCRB6EMQj7EytH5uvIxkuI+RvzZ2Ym1vuo6Zf6u9XGveYbwqv5Y3pykN8NOYwtkwk3QrWWGhB5dvOVlf2s9vjWNb4VPlSH2rSa/hj3zq831aVTqoOVZDd4l+SJslXeBX12g856oeS/Owt8OKskwkBum8pjleYK5dqJelm68hK8S99blvngMc+bfoNwbNL7PcRkf7bfmm3F6LujGSnxicaVs4bCBzjvOSx6A7Al6SOXBMNnv0p+b8A7n0O/Ugbfbb5GO7EZbgRblVX4Km2V7+bVbWurHrsmFF5wbpXOH09Q0ap4BCFlRzt+JBktf1fdDyNWgKe17OGbcFKeboJ+4xrT73afdRJO8HTyqhLO6u36M/c0bK/kwTPgRmGyk5p3mfQfxbpOsT9a8v9ZA5YfjdO0jcbpSy4djnu14eoxOx3ryEnxb4w6zlkLzLcvImW+tm2/HxOmMvXGaVGUwTPhRxXdlHtS8dEm+OGGfc/X/Bm0E6h5S+TCMnRlJeVKuufaZUeFx+Hr4HfTLKh+GCZ3NTrMucmWVZygN1Pn7OL0WVBhyvrliYteBJnR8wsYeAD2hynPDWHqx9iG99TYLK9f1PAR3Kz5kvk05nLTfqRwSsiXbfwyW4/Rp0PUXanyB4Q6ZVOa/Pkjrh+MWVgnfKfOFPfJf4vRW0KSerytOGuZjv1H1LqvUDfnwyz3bX85TPpagj2HMv3+ywZTtiumC8506491pejfeBr8atr2XYw6/FbbaF2IObMadu0bYpDjfua3uu6w7nqB3gpZdpNqOY3IczHSuTskErQENX6T1jStODONnldLfStL2n5tK0BBoz0Xa2SHCyDWMHNiszvQ8+mVGPTj8zFw8vAjjYzHkrgVkt7zMQ+lwfNsrsrHQtTxMy9GGi3K2r/JyV4JWL0jQI2+qzF+7jRFOruEBF9x77FX1/+thG98PHcfFoOE3a+Uewsl4T5DeI3yrOfvbt+/cSt8cNL7jIcv4jv+aGnoNxgTqYP2b9vep8L3Qa31z3u3vqrbW9ncPVu7NHZ2gdaCH3oI2lWcNiE9uYaGwKRdLfyg8XPlDQRy3cK5L9G0Dy2xPnW3qcz+jhfu+6858W5VfkKD0CxMUvFjxQ47JNDxt8dQE7QP1qbQaNps7AtO/i5dVejHkjZck6E5VFsNknrPwyT4jngSe8Hf/J+XHp2o99oJp7AXrqGtU7gWlnAZ7epR1NWjrJZXvY5jgGSxudf/azEee6a9uNrygzoeuW6xZVW1exN/SZnLw7ARdAhp5m/pmhsn5pfy89GvrvfD7lD4rQSeC7n0b9+3Ew9SZuWcd+V0Us1zhZzM/mKDrQCsvVfXlmEwv6yv2N+oce2OCzgFtEfGlvxoTe9tGfLvK2w1j6au3cd9r4EcONKnyYBhfH3ie3uEVOe4=
*/