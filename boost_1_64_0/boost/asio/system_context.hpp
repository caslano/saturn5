//
// system_context.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/scheduler.hpp>
#include <boost/asio/detail/thread_group.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class system_executor;

/// The executor context for the system executor.
class system_context : public execution_context
{
public:
  /// The executor type associated with the context.
  typedef system_executor executor_type;

  /// Destructor shuts down all threads in the system thread pool.
  BOOST_ASIO_DECL ~system_context();

  /// Obtain an executor for the context.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Signal all threads in the system thread pool to stop.
  BOOST_ASIO_DECL void stop();

  /// Determine whether the system thread pool has been stopped.
  BOOST_ASIO_DECL bool stopped() const BOOST_ASIO_NOEXCEPT;

  /// Join all threads in the system thread pool.
  BOOST_ASIO_DECL void join();

#if defined(GENERATING_DOCUMENTATION)
private:
#endif // defined(GENERATING_DOCUMENTATION)
  // Constructor creates all threads in the system thread pool.
  BOOST_ASIO_DECL system_context();

private:
  friend class system_executor;

  struct thread_function;

  // Helper function to create the underlying scheduler.
  BOOST_ASIO_DECL detail::scheduler& add_scheduler(detail::scheduler* s);

  // The underlying scheduler.
  detail::scheduler& scheduler_;

  // The threads in the system thread pool.
  detail::thread_group threads_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/system_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/system_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SYSTEM_CONTEXT_HPP

/* system_context.hpp
5ylCfwWVVb4Mkz4e2nDG08B8PMi1mb9l4WGLBV6Vj0foXtBZi1V5HOP77GpvVI7MidAToF2LtXZgeHU5zXtPMuNZ6YVxunDY7ZxX8hqvcmW7zmXt6lfmkdizNG/dz6+qv78l79/Z/mnY/Tvx9jTGxUOgs5ZWxgDDRB/6jGtsidIW5i/DtZ34OWBW9ZVcZ/KrIzQJ2q/Kc2Cz9jFYpbyxRRHoeiO0ZZkqT8eq2japsVu9b6b7WS9X7H6zadv2eoj5upXv1MF2+ElQenmlngzz4efsQPQZum/rvgjdDLpNqwPHMgtxdmUkAqbPJGsfn9bvqkcDsE8JRLPxQN8JEXoN6BE7ndA9pwMm9jRoSivDDePpZZ299MvbT47QV0FnrVB5MEz0XS36LoW+Qx8OsTunw463rwpSTpE2GWW0w6qTInSPKoNjys8vj694iLeN8sogrRyOWrzQxPW/nxUedCDvS7HzFj5XPe/rcX24LEveXzTPRIftN2DLp0Uo1R+hlSv1/VfYwlaAeiUOcsF4eu+90gLooUf1GS/PItHm5h2EiTm0fSP0V5sw/s28+B0EFu7rnILL4vJdZqxTHfv4ORB/r9eHbtnnfXJeD2+M96UsI2new/K4i+n9TrLUf7A82Pv0/J6C/JW4e11lmHccbxmnLx+ha0EfXq3LOBzn64GP/ni2fi0baak3Vb5EC3jncclbIpR7jm4jjTHrCPNhn2yXI94lith5XIx5BRoX6eU7nyZ2OGiPxEFuGE/P15/CmyP0a9CybpWGYawd5B7e/sbtF0FuAeW69T08yCXMOCdJ58CuZSN4/llog5belK2vFx7yZP6cb2UWYQ+E846mnfysVq7/3O+H4l+dl0boDaCntO/jmLEpSpuyDh+p/tb2F8XpRZPu/kv4t1R9b/Rg4aIc6KCPbB+2eUjjEZj9aDCHr50TY2esPn25cZptQWDeZe5uknbfAaq+dks7rH4piwTRD6ZdYQI28BHaOhqhfI9DV/SMceO0KJ1mvrE2jPsgaGvogA/sXSkXHsX9Bci/vdZlXz64vfWJ1X14mzos880PfKvp9yv/sQh9ALTnCG2eIYxmGVa1beRvYw01XiGsheTbC/h+Sya7NUJ3fyKC8yqtPIQRD5P6SJy3Nw5EyvoeoXhHhP4FurlX45lmnVmY7vvsjDsjdBOoIHEQw+S383ykHCHbxSOcGKbWTu7Tkvsukedzat6k/O5XSswv6qDjDcLPRuguUOFIUUfYB9XDl21M2MLycNl/fBxXPQcS6Wb1Pks77I92mLcmtXsDCxEOWa0NslpqwrZlLewErwUNH6XamWO8PplOyKajthZT3jvX7wINfjlCt4CKKk8N8zHWN3Effz5lGU8ZaBZnOX7jcXsU+ebPAxHaBpo4Wp87GA8uYcZLkvQS3IM8dRg2nFhvTR2f411POU5kW+STlMf46sR+txPxtXvLg9Nl61n6yFuboLWoy/EY/0eirivxrfVrg2V7xHu+eclt/fKOO8Y/jNArH8SedU1lHDBMjKUhNZbEUBXtWUfbfxShc2Fn336MykNhPsaS/N3k047K/T36UtdzYV+DfkpJ33MPRei7oHuP0XSnpm+lXNzCj/wZ5DpVZzeM54G+QZ+std52zYtX31RbIO/tD4PH/xKy37G6fXPSwk4F9Ukc5Iap9P7sgi37Ody/s2+6KJvla2QfHRWmo/BWWZP1NnwbFSYjdPRvoP9UZTowP/exM8tgA2k0SN8n3bJMBCrfNbBhbZ0w7/u1Uve+CN0HWvlcVSbH4N/cPgPHnFk6UHlvrV+/nzNyZJROWAMdrpYPx3zbPvrVoS6O2+8M9rA77h7vAsj5zXxpCj/z7RQ=
*/