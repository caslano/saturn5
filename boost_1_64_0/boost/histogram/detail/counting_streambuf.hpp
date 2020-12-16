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
xhxprLIPRGiv68Z3MSL0jQMcipKyEOTipVLr2Ugg7UsJDKPhegi7fOEgzq2Mx3OVj/Ku9on+jJAcNKk3icmVYj7ykzLAyzKvN4+gn64zUXwz17Fgh5zaFiOSaKn1aYI6aHKBbzFUsoSaMFmyoX933vyf8GH9e0GIBkHRYVM7Wojx0LH+neEPNRL8w00m/GHH8eDp1nPWyPRMpiUELQmnK2cjcypJbIK8332fsfE36ONaD7meGQMQKVt2Z0c6egX+iKc+VgKuB4J8AWCkIP+i1mLOb+QhmGUn0v+zQOw2xHXKd5RaZtS+yuZP1eIHH/HAOm2BvvVx1D32fdTf499/diD+fdb++PfrE9IHlse/T0lIX5wAP/ed+PfVn8a9RwbM6gd/meUvtZn+MikABxyghNfuL2B/mT/Es3KL05F9i37PNsQAa8NWzi9ah0drWaDddcfZ/udcNJP8hYIKWmzt+npPI65mx8Xsq/lS9inglK6Geygaa4N57M4X7430Lh13vZiC7trDrHRqiHvrxCI/249wna5xLh7Vzbl46BnsIBUPXdWDix+C91IxAOqBoO4qLlM9uA2glyVQbwT1UnE91UOWAdQigfog6CwVd6Z6yOYHX/Be2v0Vi6So2UwYO6WL94yPvBU3S9rPPsVo31V7w1IXYXgFGdYP2jP9Ypooqhq+Q3i1rfBWiasuS6ZVlUsGQbfS3YoYXEcOJlmAwRfO99FCRqWoEtlIAKqHn+Pgd6gMJn/KVd8d+Kuz4O+Bo67pTqzSvPAbY+Fes72HenStllmgyM0DOYcgV/G0Rw/k1z3xNMf2QcvJQog8/g6xwvlv15BwhXZm1Q9Jqh9razqWHuzoBBu6Jym0zZEWwoPVeOjMv03x5ZVQL/UJ84ZjKc5w6WOz9CFu/dps/eYcEq9Q+MCQSLItD47DPDuWxL8SvYlCmhBSpI9lH8b6CgpZgZBC1KAqSFeCXOtCDDKzw0lyKYlQCE0PHHQ5v70hiU9IjuZb2lakhHYSSA4SV/mciyuOPKJv0tvwcNj5+HuOR0IfONLa0jbh/VDC+8GEd6tt6yNB6rSDgY0WnUIszse3SoiDDBFJeD+a8J5se+8R9mciAm8RweQgu2x9M16ci4fbnY+HAfxXR9rmNIF3W8J7UsJ7J9vHgQ0W29S8YmodHslT9SO6QNse3+2As2LHI2ltBC7wnIqw2PeU2HfSANrCaBQyKwoiQ3qE7xsreMb+7YQt2i3Yf31evm2TvqJbG55K8QTs87ObnrktRaSG7NbmfGpiXqknsn87getTEXTQSIyC8KySZPFzIT8XdzvI1/qXEzKewqW8+7d7ttgEZdxtM6cQlIKfS/g5G8+UWnDqzbaPyWYIaPDsI3DnUwfAIFUVy/g5m59L+DmHnwv5GVW2HdJp/G5E2eUoa4++UV8Z2HY4tDPJti6ww2bbrDdRXxUs9yz3bEhb7qHRWx4SfVD3DYjIKVjnWedpSlvn2RDa2achux8tCTlJcTQJwBvcqfpmouuCTZ5NnuVpmzybQ+E+tvcCK1yAdQWRKjA1b5yV9jWcC8YckXcHUnUns/emwuDAKdgyRkDhpCAGAIz4xqbD00vJabKD/7gPc2YWsUnJRtx7hAM+jlxBmIbAYBM/bkyGoWS6xs8PhWY3CLe2/d12gZY0R7ctntdt49O7vW6rAt8BSB6hFJxl/6bcltxNuXuoi3PF/nX6JmI6uaRTb0x7G12QZ+vVrTF3bdoa8qPlWUXHoG3T7d1WgVAAGFhvCSIkFzVKw6RBqUiWt013dGsk1/WAWEcQrlwwpLTRGGwtepNtFNU2D7H5Buttqu8J1ktVAu/VlyM0FM6qv9ZWPyQZbHk=
*/