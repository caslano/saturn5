// Copyright 2005 Daniel Wallin. 
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP

namespace boost { namespace phoenix {
namespace detail
{
  template<typename T>
  struct decay_array
  {
      typedef T type;
  };

  template<typename T, int N>
  struct decay_array<T[N]>
  {
      typedef T* type;
  };

  template<typename T, int N>
  struct decay_array<T (&)[N]>
  {
      typedef T* type;
  };
}
}}

#endif

/* decay_array.hpp
stzjuupDPnFz2KJNTTUCbJAXxvnuSQ27zdkqETlij90JcDHjGoXAZ66mHW1pMtneMue60fGlvyTvv2dMzqAa2w7RpLR4rjG0UhT/q/AETIykieHoChnYVPT20ApleTQp5Gc7Ax9jntJAmddtPVEndGDeU7zkcZo8ua0aK7stF6BnlNnGS7uIP9Wkalg5TKwnzmYxGSlld475AeU4OCttNUfGHRlEkSbNez0gUOtgPLQzYKClExxOvh03Dz1Mgc/810R7V5DQcMxKCfGjLY3ouDMRRvKcuuLRVnHQQum3XCmGv4uu/NOcpcy3yadzuSVBPFwQXbCMcrBWxy5eMU9ZzWTfFsCiVKpm49LlPJBNblaC0yJjPXTcHwMcMNFhBpnOXoMHIWzaY0HCXAR9PKXd/26pFyWaHr/tEi9NaoqlFsuAXxCBuUhaFzVyGDIepsHyY70QtuXLfIYRlkRTjxcmz9SkTmCB3ySY/PnvS7YYkY+sooRzti3uH1XnMTQbOIxRzrbMN8Nc640oXWMtWNcZm1MbAOZgEgx1FnILZuSRFQ6PEDumSybhX38SCg==
*/