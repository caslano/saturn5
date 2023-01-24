// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP
#define BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP

#include <streambuf>

namespace boost {
namespace histogram {
namespace detail {

// detect how many characters will be printed by formatted output
template <class CharT, class Traits = std::char_traits<CharT>>
struct counting_streambuf : std::basic_streambuf<CharT, Traits> {
  using base_t = std::basic_streambuf<CharT, Traits>;
  using typename base_t::char_type;
  using typename base_t::int_type;

  std::streamsize count = 0;

  std::streamsize xsputn(const char_type* /* s */, std::streamsize n) override {
    count += n;
    return n;
  }

  int_type overflow(int_type ch) override {
    ++count;
    return ch;
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* counting_streambuf.hpp
uqREffH67met2FA0imnBzWz5RusjHWPcZbZ+z3IPohUyWiYWqTMvPmpmcRL5IbJR46L/FX8vtEa08wdtQPG20MZltD7p/ZM1xHrV+sTaFlwUzxYNzDkl7uRf5rnS8TNgtayqD6bl9wWAeefWOa9GllcpHjaHZqnZvgOEjoZv+q+nTt1bsnRjC4dnClZXmM6OPMq5j2qFFlRmFNoSPiLENr5UMfEf07VrvTQMuZHD9ZFmSLzHTSdo61jCbo6yk0xfendqSgQsrxnQMvMq+X2ugnjC29dB1aL26PG1chohBWExHLe1is5INAvam9b5WTGgIqeSAei04odb623eE72C7NmnX7gtzQ54/EIUhfIwxpI6Lh3U1eSw84RPt7FLl5f2LWZyuHRVyYjrPgK6X/8o566etcK1w9fK57J3dXSvzHZgzn+LvVy+Z12O276MdKrC0xM6k1MSOliD45TMBmD9PdyEBNyQO31d7nJVgdJmQ6aUKQE3p1bKVrSuJTpxweQfKj3yVKH+exhH5pllXVH8E8ZHHmnttq6XxLYy6iFu1Lpup7OyfMrH6GSFRoWOF+hiRTtLET/eZcnSOV+9lJkKmaUrefQTnMiiJc5l342aeudbUiSY9zYlElpKyK6Efqfykb5UUvS3awMkF0zmHnkuGciTqxPlBKt7p5lHS5DfvdbiBnp0aSIEI3RmAD8y+IYPHJoIBNd2EFiNYzeU
*/