//
// detail/work_dispatcher.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP
#define BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler>
class work_dispatcher
{
public:
  template <typename CompletionHandler>
  explicit work_dispatcher(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    : work_((get_associated_executor)(handler)),
      handler_(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  work_dispatcher(const work_dispatcher& other)
    : work_(other.work_),
      handler_(other.handler_)
  {
  }

  work_dispatcher(work_dispatcher&& other)
    : work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<
        typename associated_executor<Handler>::type>)(other.work_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    typename associated_allocator<Handler>::type alloc(
        (get_associated_allocator)(handler_));
    work_.get_executor().dispatch(
        BOOST_ASIO_MOVE_CAST(Handler)(handler_), alloc);
    work_.reset();
  }

private:
  executor_work_guard<typename associated_executor<Handler>::type> work_;
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

/* work_dispatcher.hpp
loPjwBvBCar/rgLvB/PAveBE1XeTwMfAyeARcBrYAF4DvgTOAF8FrwX/AM4Cz4D5YFfaPBccBE4Ac8HF4GRwCTgTvB5cCy4HK8ASsBJcCW7U+JPgavCH4DrwBFgG/hUsB/8OVoAp9NcUsBs4Vef9yZDuo+pe7Brdjz2h/f6q+r95DbwYfAO8BPwDmA2eBkeDb4JXgX8C88G3wOvUr9AK8C/gWvUrVKX+hLaDYdrxfjAJvFfz7wPbEX8a7KD92BF8BUzR+0EnsD+YCg4D/06+yzSeC6aB7wTTwVKwO0ifGL9pqWb/CBqVo/783Ra05qH4AdJ27gV3qT/Ej4P7wAfBz4DPgPvBV8HPg7FCvwimgl8C+4BfBvtrfIDGc8CD4FjwcXA8+BiYp/GZ4CFwsdKv1nJvBL8ObgHrwW3gE+BdoPgvA78N7gO/C34OfBqsB4+Az4LPgH8Avw92hP8G419R12vBmljc5V+xEroYbgAzNd5b4wPBm1QubgavBDeBc8DN4CrwXWAleIu5/+laIVjmc/97XsfhBbAn+COwP3hU5fHH4DDwJ+Bl4DHwCvAl8GrwODgNfBlcBP4cXAKeAIvAXxi/WrpGputza1x+tZZCJzYEyt/14EhwOTgBXAHOBIvBeeAqcClYoXyXqhytBW8H16m/uTLwEbBc5R56vR/r2g440ud+3DvMfRXsC2aDWeDhttyL35MUOkw4SeizNalZP1HLuZ4L3UzCGsJWQsw/VB0Y2ev0E3WQa36+ohq2JrXIX9QJ8gX5jGq7DR9G25LOq+8oP59R46jD7jeqYFvS2+I7yu03yu4zKrotKS6/UXXQHdqWlJD/qLYPGR9STfmPMr6jjm87f76jzmxList/VJ/bkkKvgTNB/EgF+pBaflvSOfuR2npb0tviS2rIlUmJ+ZMCcwmRTfH7kzpA2+0+pQ4T9/qVatqn1Kvkibw3KZRDmE+oIdxNqCccI5whZG1n3AgFhBrCbsIBQgPhNCH1fcxLwnxCLWE/oYFwmjBkB/kIOwmHCK8R0t9POwlrCLsJhwgnCJGdSaFswkxCGWEnYR/hyM7z76eq9df6a/21/lp/5/f3r/H/V1JTXVIecwB4Tv7/Yt/2XyEf8DD++qYUzJ8ya9702bPU/Z/x/bfLh+as579Gn31XDQ8ZvwfVAT77GmbLHrOroMR8we1/I9gXXMTHZ19GLu89fvXGHKWpvc2CNIefNOgT8pPm8KdAWR6ffQ/4+Ox7ELrUfJ92qQWStstu4w19Qr7SXO3y+krrE+Czr96vvxL0Zbe8iXHa7uOzL5VxyvPtD6w/WuDPy9TV1lvX+2LnealLfak461OZaO/ypQJ9sC8Vkx7oS4X0lvtSad8CXyqGfx8ffe+H/7og/uc18v/0CJcPkmb4r2uG/7pz4P/pES3nf347L/+3w38D7VG/Jd7x98496Jv0wUJ6y32wLEiLz59Mlo8PvA/AS2hOAC86lsdc30iFPpgXSW85L9TVJC+nZb8iyKYhyGbi/Nms+NsoBNmCBNtY3DA2dv2OU6v+2nvsh3vPTh998wOPXfvrxG1W/G0sgmxigmxQgmw7gm1ZzH7JbLO/zfqpc58h077vr3RZPnR9DJ3eo8C+PnS9bHT1gfWC9n3IOMuLxklX1wRdb/s+UpzlheY0Xd5uxmXn7awLEFjfiHsd0b6GWO1YN/SuGb5GsK8VmjVCsx4Y31rgfHAfaK39nQDb5slaH+t83jW+vXn2NT3QrOU51vF07c6s2TW5VpdH8FmbM+txxbLu5llvC1pnY40taF0teE3tEMG2fqZrZ551M9bKbOtkwetjgWthM0HWwBL2pc7al6x3pU9zrG/p2hb5kLU=
*/