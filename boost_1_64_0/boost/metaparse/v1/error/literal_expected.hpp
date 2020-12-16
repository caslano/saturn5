#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
othr/RTJ5Nx1XMwpuQ9G/cV0PuP6fXRomcB1AufDrbJ5rr8COB6ARrbg+yddsqztRPH24RFi7yDqW4Iy+XRRlWVajF33Jhn3aU+o32lTiG5PsH/LT9DwDc/Nu7W5JMfvBu4XcRchYsfJvBIP1ZblCxuqhXjv/3oyb8xrOeV/Ojt74kyawu/nqg6ulOMdu5e0tfkYI9pcJcdEnrG8Ss6lsRIVZ/59ynoyPe5ylA4C99CUyyV2fJIYhf8KbiTfhWqn3ir70UivvTcLrmEfZ7mY1+5tIB7/QzxegWE/4lhZBlMG8TvPKcFqxOvkSklX032a1VyHtBsaXn4KxvmBXx7wiWp1OEUyj8uom9/L7X5ymoysaP+L92fdwO8w23bOz0pl7T33E3oz3WmOA6xluQLvah7fIdvjHEtuj3z/jWw7ieTxvV+sbacWuL55abnmsYwVj56MTez3fuwYw2SIrINPq/7plRGfmSfS/DBNeipCJHVwRUdkvoAO44bxobqYaD7TcF0hIrffp7hChFfj4IJWDvxjFHTxyBPRR18ptaQORvkTE811LNBqTOVf6ly/KWCvpgLr2VgaPyV/tG9e3bfU91e+KMshoibXgVsFrpaZQtIY8gpEvdfK8vYReMpXzPYHyrF1OxMk5HqjXYcZL/d1691cAjpQPN77CkZ/ah6i7Q/U1oI3ROuCbeP5dHLItsk2nC5tLMUyDxdrJJgafWcmsrBFYE+dYHtX6vrODqYNk7UF96iMFg6Xfw8y0Gcozr4LcFwHMD7fb4RituWStZ3x3x60+t7YYG3aOaDzNvVbAXkWzLo9I3BPF7i47w1YeWBBI/2/u9r/X+SzPvS79zY12+9rA3ad78Tt5emP8XYEzOc+5bER7Xt+l5DXB+P2G3Plx3ir4fVS38fymi/9Dlq704nixUEfPxNcu9g9Vf1Jd/2D1lPVV3RbeWxu67UEcxnH7ZG+bD0w8btxllduU3R9a1PH6B+p/9jec9+3caxO9E8wLjJX8cM0X/Iet68zngpmNB1Xs/5YjoqjISE0PAyCj28uYyXlztFQ/5JqS+obO6C/W+heK8GWpRj2G4JNCdijBPuogD1OsHkvZNgfCPauFoY9RbC7BOzPBPuDgP2VYEfMYdjfCTYkYP8i2EtfzLD/Euyzgi7V6WA1QbcdwQZexLAdCHaEoHsxwUa3Y9hOBPuggO1MsNdtz7DdCHaLgO1JsEcEbG+C7fAChu1HsCMFbC7B1gvYQQR7n4DNI9jtAnaoV1b0+eEEe0DAFhCsIvqynWAXCFgnwW4WsG6CPSFgvQTbQ+j5lQSbELDXEOwGoftjCNa7I8MGCZYTsGMJ1rMTw1YS7EAxTlcDVgTsrWKsjRLdDw2/RP6anVTK+jeq2pZ1qAeFXJAZq4qNuNO649H8POR38LyNQSPispXQGsIhV7Yh9RANxVoa7tt4c5dgz++WB0VHbzhQOyc8R9gtWlmQcj2HAxMsVtg+mP56E/R40nRL6hzQZ6kP8wT7kICdTLB3CNgkwU4TsBLBThSwOsHKAnYqwTIGlmicmA2v+v6L6pssP8TEuOhzfqzbg8sG1wTeqOk0OrLvRQ+uHVwzasaAxL89hA/HHc8CnoRygzFt4/+B/fLZERrnHnr4d7k6VoSk8Mu/k/BhKbx+fndnKJaEUys/iC386QsEHc8ZScx1Xt5J8bhAvXw+8JFGvDYyt8D+VPJT6rvSx9tHYfHhNdwhocOPAx/Ahb6TuZd9KLs/hh/o+/S3pwM44135OrkEfG0YItO/HM3sRyuHRtfiSYW1x7tLdsKX+7RPi4cF1vatHl411LfSEAkdnxfuC3P5qDyFdybdaYW8n/++MC1GfT0=
*/