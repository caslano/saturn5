// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP
#define BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP

#include <boost/assert.hpp>
#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

constexpr auto invalid_index = ~static_cast<std::size_t>(0);

// integer with a persistent invalid state, similar to NaN
struct optional_index {
  std::size_t value;

  optional_index& operator=(std::size_t x) noexcept {
    value = x;
    return *this;
  }

  optional_index& operator+=(std::intptr_t x) noexcept {
    BOOST_ASSERT(x >= 0 || static_cast<std::size_t>(-x) <= value);
    if (value != invalid_index) { value += x; }
    return *this;
  }

  optional_index& operator+=(const optional_index& x) noexcept {
    if (value != invalid_index) return operator+=(x.value);
    value = invalid_index;
    return *this;
  }

  operator std::size_t() const noexcept { return value; }

  friend bool operator<=(std::size_t x, optional_index idx) noexcept {
    return x <= idx.value;
  }
};

constexpr inline bool is_valid(const std::size_t) noexcept { return true; }

inline bool is_valid(const optional_index x) noexcept { return x.value != invalid_index; }

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* optional_index.hpp
+ByxVzxFgXBNxVuvdHcaLjGojbftjonBsZbBeVtxN4yluW2/m0oCTSjgJ8dP5eJaXssoovX4OSmqT6FOnfqTeehPGmblV6Er2dcwuXwc3dK7xFq2Y9GUjt0Krgd6H00Pd2gXnrI7qpxVDdb+aFjWKtmwJjur8HaVg0DTVdB0NEi0t90ayhG9RzbHFrfd30CuxbaNRbdRbC57ZdlR6rwBq/W7YSG8Sq42Ebc/4x6QCp26cVrwj5zJXbiIOJ4StzRatpcdZVZv1ho7sLqdWC1sR/XBX0nDcuoicvBSSnxoqJPue78+nXo/cL6XSoPolr20PKchc1jhEdxmePx+MJ7UWWh8HJHqBJe3r5dXSGDk+ZtUYdxi/m3GqPMaDa3AosJ3w8572nG+5JI2I9/imkQ1xgRqsm1/3h6657TszPIZt91vf7JkhLZDa2rbEzlqbnDrNf7G4Lzdba/mbct4Q95Pgptad+WhidTgVrzqODDa9saODM5rYpf24LFtX8aWvN0y1WWPtabAMP6N0NWV6EdjtMk3cjUL+vJggA40y7HrjsDD+vlPuVEROGqAlioQ2c01Q+DQyBjluELxidLrIPon1Dv7ObkcQXQFHQqktRjj7lAS7Vpx+MuscLXG2P5HHzgVhU+AQuu3oflCXaGRQ+9f35pKl6pvPLu56f/8h9a7XJi/QWNo26N3FrG2fY3J8M6wzvNDgIxQeRlpHlKEzGGykBFT6OcGl/YRb080zrPKDW2SINdbtMVx52hpKm/CtS31g6E82l6BQNweDJD/k+vVREi3UcD6IcUp7qv8NAyG6HCEWzlCfucIhJ2pKGSCAuI7xbvl6jxUvTVY2/qMX/yyP8156I5ymu+QDuAXQ6Gj+kVFP/xng5fr8IT02GJjYzmbh5BtSNDDHDTkpMTOWDyihietOZrAsh4ZE04xG2al48zSgLTMLG+dr42cstg/e5lZut3pkYVmI1UpWLPuAfHWUn20LcC3GIHzLuXupTUvCTF6JRDtSQFpN6vdzg1/lf1SEUJvrzXmVXsQinxQmuIvffSSvKd3cBHngyehLbQKeLK6NCU00A/Uhupy7Eq5xbKJxkbqek6kHCuphIBC1SQH5VoFL+6zx5SgT9xXxgWlbTfMaAq3krvLaT4RqEGZbwdThVtxw2w299h7Yi0prk0nfqRti/zBcuKH+sXrztZcqGlcz4tb04Ne+VjJVT6Ua9fpF5ewUFj9YvYgdEV0AxujIe9/HcodUQHQ6nS5uH+5NcvxXXx/he8Ga9ZH5u/no/7I8+L31XD7cp2M7IiT0y18c/B14gtTJqeyAjlIxgYeMcMLbDGvD/6z0dFsPKH6qrRT1FwOjjREO/A3VYoNRSm4uddLV4OIWydKCd/KYk13seLSIrKNjsu5Fl1iNBG/3PcLc2h0RKSErqR/vQPkY0OvyJZhyjQDw6l3miiaDkHOTQoYM4clOxGw0WtIdoqM62CzJrF+vCHcLWYl3E6R3lsJtzNwEcKT5PtJM8v3ynDAox+7OWE30bAkj8+EewcuNjitalmrvIeEB3vEtRcZfszYdC4XwJY62aSdHmm2TIdTL+MEubFMl9Ry7WseMknjl1A2bdGELiLjllAm7SaFUtl4Zal4L5eN099C0sWUtNWs2xmgEY/hfHLDvNyT1DBfV5Ze4Syv+AqXhrXlkNFECRXt0suGDtw4vXTWWtw9nm0rCoDdOoDwfMQ6lsMZyaFWZyhjwO/jcXMCYse1yq6sHqVS3iM8yE8EENXHrptgzXV7rtLsprb7xboRLGClJFbajqSOYOc0v7h5HIA7VDdwrbbHtQmdgNZudAKtAwMnwYVq9LfR+aeRnDyk3SOu6E2JcyY=
*/