//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_RGB_TO_LUMINANCE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_RGB_TO_LUMINANCE_HPP

#include <boost/gil/color_convert.hpp>

namespace boost{ namespace gil { namespace detail {

/// - performance specialization double
/// - to eliminate compiler warning 4244
template <typename GrayChannelValue>
struct rgb_to_luminance_fn< double, double, double, GrayChannelValue >
{
    GrayChannelValue operator()( const double& red
                               , const double& green
                               , const double& blue    ) const
   {
      return channel_convert<GrayChannelValue>( red * 0.30 + green * 0.59 + blue * 0.11 );
   }
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* rgb_to_luminance.hpp
/qrjQp9XXzOzKmqvpXw3xJLkvUNSiGWpl/dOHJCiRKCw9EbsLtto9wvywGb9DEY8EkmCZI++naMGjs1xGrofps0ilCF7YvvxgYb4OzMAq/o7IvGio9iVjHLliWFlX+gHs6xAprU+XyrpeTnieWCZ+QZs//7a99chjoVSHUjCDv8rO0AkEsEgS9Kn7xw9N7Qv8lAddwFVmgKdpU/gSVO45rzqigPaeuyeLadgf0O5y30iTLW0KFP4EL5SCBZA85fB63Vgk+bEyssjl4ainHyZI7rJadIvbd8tKjzkyi3OjPTIW8OzJsvJISovSqx4s9M1TulieJHts8yKuK1mJbVmWkvWDlTUf6mg9fQ/ExV96BWbZTzsqM6TtlF897vv7YEvagmtNJT/QjDzcq7qOmOmtDPRkxJWDRzU9p1L8qShQ/BjgeeTSweQsqvSk+I4qIVTbwzNVXpjGBcvN4ZcMWrZJQwvc8QRHgVkAgYABgGGAEYAxgGuA0wC+AEhQDW9d6XF02xylcVSE5XXI0T5HfcJn5lZaOujS/ZQpBeChMcHEJVyzyqZFHu2iCis4eyZd+pJpKbKYvjGMtW9cAIrPcdKZAR1AaQXVhNHhaLqIUkzZX6Ss0mMZfrwAKZ+WZLgRTcgHqWaAtt7Orwx7Sbgo0ocR2rZfl4pZduaI2zfAhymB6F4wajXvfCuuFjZdrDqPxbUKNtM+aHz9xWZFb70QqrUX7OcrLxzUAIpCXhtY2OF+KW/FOKb/qqtmMXoAk/KAWsxhqEYHi1GeV/t6SkFupFch29ktJQnMMAMrlmWI4Or7dtShbLZJ4iUszXRZpqouY0pkovDlCiXe+xl8V/Zm/LffVX/qaJSoaTPfAVUjKtQba0qZl/8StumJBvn5DBrb9riDf2Ep6O0bNxeCqmGkZCGTzc7vQ2lbkA+VFYNd3rewRFBppX5uo8Ka4elYVfIRNVXrRb/Wung9/povdH0Zmke38ilBTqwhk9og+Qe25jgH873T1qretmo6AREiuQGTzQPzBT/9vA//JL4H8uC/2BJdEAGG5KS/yYOEjhepaQ4OjRpqiUZ5rNMy1kvkyfzfaoqedwjkuRwZ5ghCTKB+0i8reii4aY1suCaVWF+y6H5fPfiCymA9bZFlg/2aI8fh2cB9SvzbBGSJgLearIQmrBmm5rNCB1ZX5M/4LGVjpKS0GPasCtstbRy/bzFLBokxaJJwVw4Oz8kp/b9JJ2NA+S5w3I0ouNEvP9y8r9XSGuNYGu1ytEx9Xu+DJ+n4cUR+UE/+fmghtwAmV3zS+8aR8zJpH24Kh3TPTTBz/E4ToN/ezESfg/BsWGF4LaOMMWNldn1IrKCfDAWmAN8d/5Wb31GqueKV/BLFkXJaKcHTt2zlGJQ5bJALrV+ZMLNAti6acqrZFfisRxC8qN7y1vSp0WyNrSxVsnRIUvUZqYW/oV/SOGbsPCJiAcPZyB97eMWi+4jn+4y6cCn+tNPbwngkwIGVV7aK1blBy0+5z8QuS8fXQcq+PMpX7USti1aUYZeNEv0odP5cz/pFjTPKHRQqOI/lrwn5X9elJLnIl9TmK39OcRX84qk0jwzkHg+Rv0J8sCI6nAvzMKgRXlNz1h5v3Zz85YdVEeVbqCmfqzA/lZM7RWmpopxTiAcF4im5iEgkWPNkpp7JNudyOV+5MIs5ru1ScbTR+cfRgP6l11ua4vqyufjJDUQQybhTI9V/PCzCFW36354QfVqIQtTkMWuY/WurpLq1a+uXj0r7y6SdyVH37eXVndFP+s8tA84LfSBHlro7Y3i/rCwe2oVdscAu/M+5ELBBglV2E3yx/YN9HHbLZdbe3TYG/oXZnlhiDZV8Ag=
*/