//
// detail/handler_tracking.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP
#define BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {

class execution_context;

} // namespace asio
} // namespace boost

#if defined(BOOST_ASIO_CUSTOM_HANDLER_TRACKING)
# include BOOST_ASIO_CUSTOM_HANDLER_TRACKING
#elif defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# include <boost/system/error_code.hpp>
# include <boost/asio/detail/cstdint.hpp>
# include <boost/asio/detail/static_mutex.hpp>
# include <boost/asio/detail/tss_ptr.hpp>
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_CUSTOM_HANDLER_TRACKING)

// The user-specified header must define the following macros:
// - BOOST_ASIO_INHERIT_TRACKED_HANDLER
// - BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
// - BOOST_ASIO_HANDLER_TRACKING_INIT
// - BOOST_ASIO_HANDLER_CREATION(args)
// - BOOST_ASIO_HANDLER_COMPLETION(args)
// - BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args)
// - BOOST_ASIO_HANDLER_INVOCATION_END
// - BOOST_ASIO_HANDLER_OPERATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_READ_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_EVENTS(args)
// - BOOST_ASIO_HANDLER_REACTOR_OPERATION(args)

# if !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
#  define BOOST_ASIO_ENABLE_HANDLER_TRACKING 1
# endif /// !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

#elif defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

class handler_tracking
{
public:
  class completion;

  // Base class for objects containing tracked handlers.
  class tracked_handler
  {
  private:
    // Only the handler_tracking class will have access to the id.
    friend class handler_tracking;
    friend class completion;
    uint64_t id_;

  protected:
    // Constructor initialises with no id.
    tracked_handler() : id_(0) {}

    // Prevent deletion through this type.
    ~tracked_handler() {}
  };

  // Initialise the tracking system.
  BOOST_ASIO_DECL static void init();

  class location
  {
  public:
    // Constructor adds a location to the stack.
    BOOST_ASIO_DECL explicit location(const char* file,
        int line, const char* func);

    // Destructor removes a location from the stack.
    BOOST_ASIO_DECL ~location();

  private:
    // Disallow copying and assignment.
    location(const location&) BOOST_ASIO_DELETED;
    location& operator=(const location&) BOOST_ASIO_DELETED;

    friend class handler_tracking;
    const char* file_;
    int line_;
    const char* func_;
    location* next_;
  };

  // Record the creation of a tracked handler.
  BOOST_ASIO_DECL static void creation(
      execution_context& context, tracked_handler& h,
      const char* object_type, void* object,
      uintmax_t native_handle, const char* op_name);

  class completion
  {
  public:
    // Constructor records that handler is to be invoked with no arguments.
    BOOST_ASIO_DECL explicit completion(const tracked_handler& h);

    // Destructor records only when an exception is thrown from the handler, or
    // if the memory is being freed without the handler having been invoked.
    BOOST_ASIO_DECL ~completion();

    // Records that handler is to be invoked with no arguments.
    BOOST_ASIO_DECL void invocation_begin();

    // Records that handler is to be invoked with one arguments.
    BOOST_ASIO_DECL void invocation_begin(const boost::system::error_code& ec);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, std::size_t bytes_transferred);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, int signal_number);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, const char* arg);

    // Record that handler invocation has ended.
    BOOST_ASIO_DECL void invocation_end();

  private:
    friend class handler_tracking;
    uint64_t id_;
    bool invoked_;
    completion* next_;
  };

  // Record an operation that is not directly associated with a handler.
  BOOST_ASIO_DECL static void operation(execution_context& context,
      const char* object_type, void* object,
      uintmax_t native_handle, const char* op_name);

  // Record that a descriptor has been registered with the reactor.
  BOOST_ASIO_DECL static void reactor_registration(execution_context& context,
      uintmax_t native_handle, uintmax_t registration);

  // Record that a descriptor has been deregistered from the reactor.
  BOOST_ASIO_DECL static void reactor_deregistration(execution_context& context,
      uintmax_t native_handle, uintmax_t registration);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_events(execution_context& context,
      uintmax_t registration, unsigned events);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_operation(
      const tracked_handler& h, const char* op_name,
      const boost::system::error_code& ec);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_operation(
      const tracked_handler& h, const char* op_name,
      const boost::system::error_code& ec, std::size_t bytes_transferred);

  // Write a line of output.
  BOOST_ASIO_DECL static void write_line(const char* format, ...);

private:
  struct tracking_state;
  BOOST_ASIO_DECL static tracking_state* get_state();
};

# define BOOST_ASIO_INHERIT_TRACKED_HANDLER \
  : public boost::asio::detail::handler_tracking::tracked_handler

# define BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER \
  , public boost::asio::detail::handler_tracking::tracked_handler

# define BOOST_ASIO_HANDLER_TRACKING_INIT \
  boost::asio::detail::handler_tracking::init()

# define BOOST_ASIO_HANDLER_LOCATION(args) \
  boost::asio::detail::handler_tracking::location tracked_location args

# define BOOST_ASIO_HANDLER_CREATION(args) \
  boost::asio::detail::handler_tracking::creation args

# define BOOST_ASIO_HANDLER_COMPLETION(args) \
  boost::asio::detail::handler_tracking::completion tracked_completion args

# define BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args) \
  tracked_completion.invocation_begin args

# define BOOST_ASIO_HANDLER_INVOCATION_END \
  tracked_completion.invocation_end()

# define BOOST_ASIO_HANDLER_OPERATION(args) \
  boost::asio::detail::handler_tracking::operation args

# define BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args) \
  boost::asio::detail::handler_tracking::reactor_registration args

# define BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args) \
  boost::asio::detail::handler_tracking::reactor_deregistration args

# define BOOST_ASIO_HANDLER_REACTOR_READ_EVENT 1
# define BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT 2
# define BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT 4

# define BOOST_ASIO_HANDLER_REACTOR_EVENTS(args) \
  boost::asio::detail::handler_tracking::reactor_events args

# define BOOST_ASIO_HANDLER_REACTOR_OPERATION(args) \
  boost::asio::detail::handler_tracking::reactor_operation args

#else // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

# define BOOST_ASIO_INHERIT_TRACKED_HANDLER
# define BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
# define BOOST_ASIO_HANDLER_TRACKING_INIT (void)0
# define BOOST_ASIO_HANDLER_LOCATION(loc) (void)0
# define BOOST_ASIO_HANDLER_CREATION(args) (void)0
# define BOOST_ASIO_HANDLER_COMPLETION(args) (void)0
# define BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args) (void)0
# define BOOST_ASIO_HANDLER_INVOCATION_END (void)0
# define BOOST_ASIO_HANDLER_OPERATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_READ_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_EVENTS(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_OPERATION(args) (void)0

#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/handler_tracking.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP

/* handler_tracking.hpp
54r1wAQkS8be1PM/wnL+gxihrut/hSncmy0Gn/7y+9xH9OA11nJtLn8sO+Xfp+X79BATbCO/i4KjWuhIjH9yslRnwX4im1vAjxMdH1/vBzZ9UBxplj+bXavOg+E0peX3gy46w2484+3bmNsfvFU3aTleJJ3hMnFi/DvqEL++semESoEFf4Yi89E1U97y9aiJ42wyZ75hbOyYokNn+BNZ5CgthKsWHl3RSq+j7uxsGcbqVv70XMzHaLK/X7hsPhn81844eVwNmtpLmukb3fyE8wpcigfwBbhOZn2FA0I71PaDg02GL3xbrnSwYnXTkKyqlN3PwyH2zIcJj8NxiyvmCpd+5UBBtmbC96e+v7yR0kts3dzEVMHCpqeoGYxtmMlzNwzSrU8tNLHvJR9N9zrVx+yBTIsxAnQPxpr8i2K3BH2w/iVuZqcEs0s8pdQ0puzjnqoubU9Hc+j94tZ9WGPEqdkXfQHxFuTOnUeNcC8OBkkMI4PG4yxIRrOIvjQwR3TSYpT4YEn9xluRdAr2J2U5UfFFe1L9wiJpCs5xuOGKDI1bJXHEWVR3UpnYx2f/wMeLREaTFX+q0BotxWefm34I/HV8tFMIKpkdguREQphFzVU+sEF7wJXXEAmFzc51PfmO50JBxWYvl2u6XjRp+0RH1u+0l7Wtcuwm2W43Wfy2WZzsu2lL+1a8Z6q/CgfO0gbZ6E7CZftMcUS/UHBlYCq21bUrbYrLIMkL20tBVgPpO6/A1Q1L7hEyg3QD3YBbLjbqYosnUycKOg1WcETkE3N+/dzKvsfQa4hSHE13QJMlud/GtSoay/FKLJ1BtS2o1qai8lXkkS34I9eSr28eew1S/ATbQWcfqT4W1lZ2tV3M9BJFXPYmGXLci631m4D6MCmlFsmu6saosA4jeAWx8wqsI2wzPIcHFkZQPr1sdzaHvXAiaNrLCb9sqxc4vb8E3jvF8sReyG59hF+6SlxdwsGFPrpv+AK3Nx40/0/1Fz2tUrB3KaITWboPo9VfazLK4ZSrpWgjs+lrxUmOI8vspcqlv3RoWhZBQDa2uifjD14Lxzk8C4feYWcTvmyupTcNlgKD4HgwJsYrx2ZpA3MZ6DJ4b7d4nsNg3l+Ujo7th86ttp3jx8VqoA2lYmtqj7zP9yLJUjVMhYY2fNUvtL6sLAJnfluyvXhTGvSMvdnSMXYVFnxpUPTl3kQpI11RafjRPQ7mLtd+Rz0slydcCiP9b87s5tuDq6mPxf6R+hSI+Zw2C8Tg4ZcRURJ4ib16Sy5eS3wwlZcVsOQSxF4shd9/QB2G7IzYOabMh6+QCLHVfFifKu30Yh5cS1sae0OieC1IKKIfw7a5QmqmBtTNbt63mCKe7IE/kquRZLAKibzNeoc4TKG0CSb2/K1PkJU0zirQjQdBzBQ7kqUiloqMZeSvgyDDl3e15MAIJ0PGOUGMy42wuwt2g4N9Hjyhx49NZ6B5W1K17b4Pzeu/zp0hO/6EUXHyd9JA0JdDBAUhgG/1TSPu293db7/dhkTog8uAhSGP54G4OugjtAS22gHtEPfdxLey/c2oDOBYnQV0bGpFJWb8cEPfghL/TGywBXWowPQzFBjstbv+1Hnjawn9Wnn2dhvpQR/JOzXftSf3qwgR6J3s04WzJjc3etocfp8eMw79U5TC5hox8wTbByOoT84sVBtY2jvTXRiXN+82c2c2kpCGMQhiLM/KHHhrTQNjqM+MrAQO8VJh9uZyfmEGUB4U1goxWNfj9ErYt6LhTwAAh/YMeOnTCg6P1zswQEhgwC0sKCzc7xMUEyjgLyYs7h8aK/cZlBOYlpQCg5+bEB2Rgjg6OSkt3Nc3MD0oA29o2k4NAoWHhweJCHmyJ4RDhuSNVOz3/roOxP8XWByIJD9fHPBlNi9vLq+7GZChh/XJbQQ4DAv4KVazNxvtPFSzkc/KDEB8Vj5OM28OwNv/ONW/xz7PO/s78Z/Dp5vxTzIx9EsN3lpSSg9TPbwvQz3/sN/KbD3Dj5+teR2BzNfAaO/XhNlV/2xXjb/ZDhJCDWCpn45/IAMDQAiwMr/TROwI3usNlpdp8U/M18/Sagt/SNIeAoC5bQe2cG/LJQy5X+qPL/+XeWf6N14cQCeXOqEfjvSlH6S4/tsGP9ChPhBT/V/1dP4elKcZYEj+WXx/EIKH3ACQYj1/ELg8hAoIrkiAxDgC6AaAQgQuhEEgQ2RjUxMjRCDI+rsHJCdoBkiISAjg9NXVoDWQ1T/8/ZNR/GgI1A0AQagou7s/HfxA0Bd6AEgA0AAUxqSjbUD+gjZA/DwRwPwGwoB5tZ2A8quTfvA0+nv6pp/w/VBp/JeD0tJ+QNDCV9Y4uTs2CD1XdJgkPWIRMJKu78vPMzfywEIrN03eE5Br3t9wuq9tiz8c3b1wh6/gt/22MGowYAgS6i6jPOxw8hhQxfkEHoYAyVGe8wU/qN2XnPU5REPmAKJ3yEvPdxJ78/3X/QPc2bZyi5ljmVsNW7JT7cU1yVMapMrjTIgwN04FYXxZWNQGKSK92rwlaJE9LdRez4aaLZt5W1U0Stz8J9rMzDWM1Z3ZmUwHGkFD7Wt//BQ2jOss2ryqT0pziVwuqD76HcjSK3VFOfO/wt6nHE2H9evHnvc63E4aPhpIYZa852WLTfTaumyujVKqLHzCPQs2AAUs+tO/L+vyN8uUTFGqdDSGw193Idg4rIOmTfREO3mSdbx6F96DH/+Kk2cwBMQfgT3sp13RPZYxBUxqBIGv43ltZuR78uI/P7fQLY6nGGFNlR2UrOTHexdNo4HO5yJ2lUMPjWm5R3ecBog1K1WIf9Tn5jJIYlh6doVL1rhTmlYjWKkbHAI7EUlOc7lrU5xKQiHY1WL6uFadnb+b7+K57VdjWxk+Lpk2joWt5zmEjwjSvLjYMNT0HSwJVCA3atS149qkfq/kXvUfUtGKQirOEoEqclleylZFXaq8HxvIlHYcjOgdEa6bn/j2oQr+y/Gk6Q1SJ/wnaibIgNTdHMi2ZBYWrPYb/dxmCrTMc5C2BxeH/+yPKWQuWvjnq+vzI87rBuBT5DYhQ/NQ2Bi4v4+PKgETXuK4bTsuBYcaj/E7y6URI7bkZwGkecVf68Zy3S4XRmcF3f2RVd7nLUMVOBskV89cVoMA8aE6XODdoFGFoE17uicTBF6jWuLi4T5PxNfoasMui8rXDUiJCjg5s+BJ4w89QDyRw9DHDqLuSGVFN+yY0MlieEFKxldVthxpCg/JdBwxirobdoNh3BL6/pNInT4XfGYYLg/J2mUJFiRY5GueD2SJYnIZBJfNKiexpXB27clFK50xOhI8jYP1JOqtOju7LArssqKzREtNN6VASYs9NtD42dlRXVVel//dq+7ndl8WtyyrRvzP8sx8Ic1S61xzd/vUq2SeLuSWI5J6Lgkc1CnmFpU/uGqsviw8OjjSN9iwC7sklul4oz9bZt08HFq0BQaM+gaqJT/HF1OGxEYF7xGepNQkU4nuWU4qymZ8tkWfmib923IG8/AL/0xfUP1YT9WDGs2Q4JQ8BfX+z2u4CTFY/edgPTKwxk/Lp6Kp6nJuM0ecyfWJDxwy8t+Cxu4uUMa4K68O34azNWACPy80oKhuvo8fUq0cuw5Uml48FgBYgGCwNYnNK5ZbAjky89EdO7hSL4bZlxtXmqA43Ikur5e8fN9MsGgwYO+gafofGz7Hl8oOcP9LsemZTOwav0PNtMdnP5jWofLVAywnjCiZx4HOYuaPw6yO9P7eEOkHEaNGUz1fFsJmc+wK+1iiGd29xjl97rarpG3tknb5ws5jHbQ/x+DB/eZRZphyJNAeEOgWperp0eExX5X2xuAWLDZgBi4H83f1Mcc+4hh8qfMVSBdsXJWSKQIZFGXMnXpkRJTY2nWz67ZjNrwOTrrzDpEihT2Vil07p2Ou8uXhgWprl3U+aSkp738jGDuELKfUsSopUywDEp3lKv5uVKvkOlabyuIsF3XSMpU+0rOQG1AqUw7BoHlqYjIIaGZcZA/d9pyyMQP7mbv/SDWHeLUwf38dY0BhgT1vuyn9bWdu3lldZ1fyCpLth//sKsteN886+9K3zoOka9Uhi8zowgqAjs/us204UUucQMhO2bB44jVOsxoh661rwrqIOGfkrEAbmx9Gs24al+SjgNAh7u45T1oUjC+05FVa3wxy+e8C1BLUiov/dBh7Pwh5tUi8kByvbpoQc3nRdpELdzXzdXN0dzq7z7b4tPm4n94Prd4N302QtxwNvY4tACXjaygKbnSGEq9sCJ49SQxlRHrIDxylMH8mGt/VkSPGoNyLugXUX/8Ua32zL1f+0Cn98GkWf9v0APN3Vv0QGA0AfjqkA3H70yjHoXgrl+bG6snAwmaAvIr/vIQsa9d/HckNOMLv0F8x6zetRW4QHQ/b5r/hStWcqPGHHb85iFVN9e+FtbUlypa46243cvUtXOLcxqjSmG7kQgUIouFw9jZdVmSgz4HMqYSOPD5pVrVq52ZmwTseoeKwuren6lWRx0brteLoXsJe9zipKuvo4OnAwPwzXP3WaWxSEfs52fHZu4T40n3G3rCPvcJIbehidgMqI4ert+/jk5C8i4mLt0EtyVNfTvsE7yH85GtCVUV7/rkMhsQ65l3s6ggOR6pnEOjjXy4Dl+/RScPr2yQXGNllJwCmOu2R1KL5opZCQUnhxpDK9M3yIOM1Nl6gpPeqnKFUrVfMYN2oJfohYhBxUWqSu6jXKBjT9/lM2OHVm+uc60w5aLwSSVtWXZQOF62LCqWdQ7aeplkODA8cRaGds/3gr4mxftBY2GrRlIIO9YBUYdYGK79cWjkeFlEhVJo7OBDysxz0qXjKLgjJPD1PYjK+dRbNa/YeXVTzz+Lx4eseVo1TOjnKdCdf+CdBOkDVDWlRNXX5+kkEnCCuIttg/QDE6ld4FwDSEPQJqbhJteJULqQllGqILP0lnIjSgWJN0+zPqpW8Q6oMZ4PekBtz7m+fIKz20zzLYPdw8hQbERFhLXJgL7Y2PF72EDz2B/HMuFQgoEMEdYXJ7hpU9S9X8XGl6xnQddnYof07lbhmE47PSbO3l9EqHW+H/vtVeur7WbhF1WLpvewGql6dQTEoVgYX1t6u6yaZbmacbKb52xFWiTgllivl+rRNPO0Hl0pNi4oSOa46q0Q9y5RNQ4ptSJgmE8octJSqCjd/D74M2qwf+cT/j14mzeRPNs3/j59Nfe1nJtnEFsrbTDrNz6AW0o977rccPp8nM9Do+02//Np3Io6LdS++DjnAJrC6ONDalnxvL/frVixf2v2Lfi3RtREFRQh87KevMZppTee3d0n+6uRLWPGHK1/OI+c4hCmXTNuGan9Dsx/ez6AaHt9FC+N0AA5fRU8ite4QgFaneyLLbbgcSc2EgT4aKA2Bznn/flR9w3Gj+9j9l+a5mGpA1d4xkw7f7dbUuycp7lLjX2U1vqqAwqVGSU+rD8+ynZXz4fWREYqLDdYFuwXKWt6fh2Rz9875uH/vYmR9z6nSgpo7fYDSlZAkYNsGUX5D/MJXjzp+/h5flsT8bDE9dsR0zB0KGaN2YQrBNy1G4K9pWrtn78QjLpurSbW2CftveBvsE9ekPTJ+olHvwdCy67suXNCorf7rLaxsCzhoDGZRB/62aIb/mNnhg8os3eISUuxkNTuikzczEu0fPJ5enQVAd/XylCd3fCfkJxYhx+PeGQQqh4uoG+osTylaV6S1enp4K2wFA1yH5BFY3uusG85OKzycNERTi2TZcPJx7aGi+WJrKlsTL+8YhkNXZv+g+68zC5/x7eg++71y4CAjEzMzQzzyidQRBjPWAQa4Qdz97Dq17vh2v3w5/RnmK1y97ClYvZycpPkkIADnCkVgJoYYnR4koxmdpBscpZikGe2jd3/hyAoDQBidnoFDMUUEC1wN0gDRSF/lIDijAZLmzwM42PnBibmr8YYLhVtz6wTl30oF5uc5BeMn5AfOi8v5lUggBSA8/AeYfy8OMM8eGlA+NhNQHiQozmn3Jn/DujLvh8Q5E1McZv9V7e8GH+o730gzIdot/G+aLoUHzMWI91bSfObDVoUvixyZ1V280m+z6MtOUhGjHBwcudRFVFBa1YwZHuDzCOj4elJ24ngEgA29hNZ6tF3yvnB8Omh26dYC8WQkZH1erix1JoHBxjwLRaSdkTRGQGQWzNhAHJFf7FO8vZKLBtYlpzkIB8HwaDlfNUOyi1biIGXutMtZoTazdeDe/bCOOZMRWxLLwc9/qQ5cKFj11hZ96DvcoMr2bOtDzbaOpE+T0R2dQiO3xNR1quLg4q6huQE/yMGvLeqCK4eozYP661nb9GzcJE8MKsAfiOtcU3JWwCQjulldHmUTRUUoq+fVF4/tIijhxAUil7jP7U4ESBZ1ZARKGKqP+lA8ANK9VHkxuk57Yv6mf3d6h94tkCeF6zrA+1H4BX9q0p7lqAuVy8cLGkf3Em6tRILOebJAHMWXW4TENHOeyV+GNerOaxxMeDRF0YUbBVCNwj6nVSzt2PsQj3lYlYrJMnjnoXTovXlbzQJ+YfmIyNy1MmKyJMhHSDszkVNKk95IkWol8uWkqxtxlAdRVp5tdUhdTn5uSUATsrTmkrhGXI9uO0LDVgZeWncCbiIJj9UK16xRna/HuaP4vVNYSYRgFVwq7L8Tv/BjtZl8gL75hN6YfKbWiPpIvT7+ibz+zt6rDOjjdauTiZGEsqR8yGr+ejX5SPsvmUCO2ktI3NbHKrRD2UtmV25BaRXLcNh0mQxmXzQO0vB4V5J8mKDQDjTk8TTV7GDrU99Yvl6hma2j4S13dvNm4bi6UQ/7/gZoRd2fr6d1FObzLR1q/xVz0eSbPbAdBaCcD9AG4HTnql//WmBg+yosXJ4Q+s/jzbM5wgziMS/WLSLNGP5cwkGwAP19Qi3Rg6+fYg13xnt3y5CyM703jTLN25zdYNNJdJHNEK2qOcs47K5iM8lzjAQtEIUaTdTiWPOQmxQ2bPbKXSLjpfq4+YAc80zxsdRFrJAx0J/b4rpBOrFNWpvFYzpOShIgIF1BqkvGPNSkrcYb6n+EKkeUdWVZGEtoUZZKDzKYGrHs8ohUrisatRTj1Q+F9/Q+o6mso4uqr6oXlXUWikrrdwZQ6weDeZbnj/SMRvlgeoAReJX0QZVV6bxH4HQWVLcg2+K50vgFS8uP60fMnU1IXEZ/TLCn9hpn2jooZUMlYQwRzz0wSJlwtlIL2NKAyO3GkPtJZVMSFZn8ckvD6I8m1t8waEc3YW5sivk3ExBrI3yoRuUVrKUzUAqRs0laGwunEOgFSLZgmmpqbmJ3D3+okkb674CFvvTqZTpvmt+wD4IC1Hd9TjvUcnPzgK4F3DFOdwg9GMxjGdIeJfw/70+LmntaZiMvOvj8Rveq5DGbXmWxP1BFEdO2SFRfG1iiXwHqt0T/Zq8Rij/b9EOXEV/PihUVkaggj3Hc5wiqJnOYGrXvCaORMWuMo5ubKOF2hYA4C9if3sTZi0u8uJuJns05XXSfvk5Z+mvh1rkghoZST3j5kAC5oW/ZY0xta2Imqg0PSff2wveLrPcmnfPVv+MIvYh2UglWjQdUi6dnBrZ8OhsJKRHviAwPGHu5F9ULWpBY
*/