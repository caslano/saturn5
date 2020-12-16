//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP
#define BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

#include <boost/chrono/config.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/ratio/detail/overflow_helpers.hpp>

namespace boost {
namespace chrono {
namespace chrono_detail {

//  template <class R1, class R2>
//  struct is_evenly_divisible_by : public boost::mpl::bool_ < ratio_divide<R1, R2>::type::den == 1 >
//  {};
  template <class R1, class R2>
  struct is_evenly_divisible_by : public boost::ratio_detail::is_evenly_divisible_by<R1, R2>
  {};

} // namespace chrono_detail
} // namespace detail
} // namespace chrono

#endif // BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

/* is_evenly_divisible_by.hpp
Ey20Ja6T6ibPT+rW+NfVNUm7qP9cxfIRNN7aBPUppnnM1bRMjpPrm15FK9brx7R6JPtaqk2kyQx5t9yr7PIj7Sl5l/mkWGF5VV5js8gJEX+SV9jdcqzjr/Kq6BhZ4PxQ9nTVl7nub+VQT6IsiftUDo/3yuKEr+WYpDhZnrxDtkmJlpfVXybfbHDKN37Q/Uayrtfq+jNtKum6Hs/YSrlaxsttaqPMM/0sCswvyzbWGNnTtk96cG6tn/19mRaVJq+I3iPdMc1ld9dHMjm2hcz0fCQbexvJAfEfyqaJLeXwpA1S1nPL+ilL5CP1j9Lv0DC+1wc0ljyMuULrRmwbiscbR89gvO85INpp0jWZxs6BTHuPbNhX0ByCaS/Rb9jepEK8SStZW6ZOmjerk7Yn1VH7NnUseraYjXMIP7nuVEc9r6gf4m9WZA+WXU99Y5lop7cd0+6k34YHk0aL7qqx1l+dMt+vfrRNU8oxzXzGNU995Vmnvo7vqHqx/pmQaUhjqXQni1vVThUvjmMc3mWOF9+bd6gXbMnipO1xtdueLI7bd6nXouPFmejH1UuIFqP6chkP0G9Ae6INYtpVpMspil/NYtpX9AyaY9MwE2+E6PYfta3qhGWn+j5ig/rR8bg649xIz/4Q5r+06hnS+onXyZbDmR5B48wmsscIpr3UgMZC2ZfrlgXaZzRGfOOJx/PztvKIH9Ur6oA5BnFx69U+W7zQIl5Sn9k9woN7fxrtEbHObepjVwOR4N5GZQ/kctrQvOBvvt89okkq+01f/YhWQfq+nTREbpTfawusL9s3qr3R69RO13a1z/OY2hv/NJU7jPm/Irst9dWDaB+l0llPw5aj9Lam+r5E502zmFZJOk1JeFMck/dp6Wq5paNaE9FArXB0Ufc6W6s17rbqvrhkpcsMYZmRZP9D8b3EMmXX3lNRlv3KG/G6inYcUMnO19Qx/P40iFvk+40hmXss1X15GNO+oXq2kr4+MB60mdQfG4s0fYxg2uMmWqc0iBRzzTeb31LZtnc9nVKW0Dg+kHm6Ruk8X3iixCEltTMq0nJEqQiz5nR8rSxOsxbrfp36xGDm/wuV+byyid8qnnNQjMmDdH+c1mSdSkFLp7592OUQr6tP9Rms+Qd10Hba/A3GX6+uJ/PdRe2wQmmi6hkbyfRNVGak8PFOB22iiX7zG1jE9gZkJ6Y/TrwJvrkr0dYSb1qKTUSlUN/hswxZxHuzoD4Gms2gYa1F4xt6skEbyH0fpRu0tTwvkyLVoD0sqB+B1sygCd/5BooJziRa0/R66kQDPt+gsgzeBuk3ir0Nma6tAr090bula9r8BnyeAEXyuhArV6KR/sG0+aR/EJ9MqMmnUmvSTM1qypozatJMXWrKmnv40fR9n31I05rTOLNA4wNd+6h+dzY0iyWm20yVsq8lz/Rc5IPievv1WqTzLm2d+2rN5B2uxia0j+C2pusojTWYC3FZev0PVrU/yoo2NTTN1t6yfiOO2j7RPnJ8o70Ws1nMcd2tdY7rbpqe+Kbsn3xK5qX8TmN5slUEPVPzIZ9vWmJ6RuZZGmqLIgaoz+0tVf3oIeb5sW20F7xKvZYwQQ5JOq0GpSSZWJ76RS+Sj8Nc4YypmXmdfNMyQw6w4VR01FbZ2blA+5M7Uv3V8436c3yC6W/JnWR+ykSfPPWh+SS/Fs9qkVqkfjKtsqaoNyI2y/vsuZrmvFvd7/pS2xA3WotLjJfdkw6rjJTxiuWpv20j+T4NPWKs6XrTV2KW+W0tK2Kk3B652jTVGSXXxfQ2/dUzyNQ3caLcm5Sn+qWcNuqfof8+knxqqln8TdXX+mg3WUYoa8QAbbijvbw5aqkpyb1SezE=
*/