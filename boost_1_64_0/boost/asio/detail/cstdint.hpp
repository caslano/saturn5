//
// detail/cstdint.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDINT_HPP
#define BOOST_ASIO_DETAIL_CSTDINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CSTDINT)
# include <cstdint>
#else // defined(BOOST_ASIO_HAS_CSTDINT)
# include <boost/cstdint.hpp>
#endif // defined(BOOST_ASIO_HAS_CSTDINT)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_CSTDINT)
using std::int16_t;
using std::int_least16_t;
using std::uint16_t;
using std::uint_least16_t;
using std::int32_t;
using std::int_least32_t;
using std::uint32_t;
using std::uint_least32_t;
using std::int64_t;
using std::int_least64_t;
using std::uint64_t;
using std::uint_least64_t;
using std::uintmax_t;
#else // defined(BOOST_ASIO_HAS_CSTDINT)
using boost::int16_t;
using boost::int_least16_t;
using boost::uint16_t;
using boost::uint_least16_t;
using boost::int32_t;
using boost::int_least32_t;
using boost::uint32_t;
using boost::uint_least32_t;
using boost::int64_t;
using boost::int_least64_t;
using boost::uint64_t;
using boost::uint_least64_t;
using boost::uintmax_t;
#endif // defined(BOOST_ASIO_HAS_CSTDINT)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDINT_HPP

/* cstdint.hpp
Hf47/Xf57/bf47/Xf5//fv8D/gf9D/kf9j/if9T/mP9xf4Hf7ff4C/1F/mJ/ib+Nv9Tf1v+E/0n/U/6n/e387f0d/F5/md/n9/sD/nJ/hb/SH/R39Ff5q/01/pA/7I/4O/mj/pg/7q/11/k7++v9Df4u/q7+bv7u/h5+wd/TL/oTfskv+xV/0p/yp/2qv5e/0a/5M37db/iz/t5+0w/8lt/2N/mb/S3+Vn8ff19/P39//wD/QP8g/2D/EP9Q/zD/cP8I/0j/KP9o/xj/WP84/3j/BP9E/yT/ZP8U/1T/NP90/wz/TP8s/2z/HP9c/zz/fP8C/0L/Iv9i/xL/Uv8y/3L/Cv9K/yr/av8a/1r/Ov96/wb/Rv8m/2b/Fv9W/zb/dv8O/07/Lv9u/x7/Xv8+/37/Af9B/yH/Yf8R/1H/Mf9x/wn/Sf8p/2n/Gf9Z/zn/eb9WnSg1t862Gmv6P1au1bp6+/oGxsYK/QNjfaODI+ODw0OFyWalksdXW3lsvbK5q3dgrDBRLVSnKoVKPaw+pEoTJRNPTnT3LHUomzBzlCs6XSlNZGXZtNN4w22sMduqNupBmA4qraTqwsbK1oRDfpNr1zc3i7Mp1GBssDzcHC3W0SwMVskSsJQBYaIQV+qt6mS10uybblRLcTGXR2mXdSsJ3PKBXTSISw11F3qHNkAapZcNjhfGxkcHh1YUStOV0kaHRc0Vh5yCdSZyqsih6sWZSmG2Wa27Iijkcu2ZQjEoOTzGI4/Lz2tot2bE6Ynm3FxaqeHh1QO9Q2mWgaG1awZGe8cH+sOaHBI2yeMK6PmSRbYkr1a07HDoist1rLTVKCwbitjltvorBoaQa/XgLgP944NrBgrF8l65Au0Grgj9ruRKOraCPuUKUo9wRehfZ0EhaKHglCHPDq/L26rZwzzYu9ipAJxVGIxTcGh8YMXAaKE0M2sS5bZFoOKKycAvDEI7iku3c/iqWdxVCqayiPwGgvwGsp40tHb16rALGqJ9DXTjw8t2HOgbL5SalWKrYlAobhCowIC6ir7xgXQeD/UPLEfOHAls7rIwfB6LtisunVtvvh7amCN94+uj+jScggVLlWarMFkrTgWGIJ+rz+TSjWo5l4fDOzzUzKCgkwYQuFy+BkEHDYIcDWCT8d5lqwdM+7oSmDifh/qWIK8St3hewdbW2bjgmDk4Y4kBi7OzhXKxVdS0HhqTQ4uVGYsCM1uDO2doaJFBgdvEwE5rB4b6BuJ11iI1MW5kiG0T9grBuZzDlmqVYh0+7kqgaZYNcza1Maxpo3FjdmuW0J2wp5Q7mfROYIFbDCx2VJPFdq1VmCkGGw1hrVKfak3nUHqiaUfJ4mjRcBhs1LbkkoVJU3lUb+MFFoGNw9bC0GC/SVu9mVcY70h0BoTStePLl5ocvNYhdHfHl3Q79gaXTiub0QXtVd9c6vX6nsHl6uSkhpkWjYXdXM3tJdxct63FWpOwBVyjXmkWa9V9KuVWdSZpasMIFIN3agQ9skJ4lImwmiFklVqVVtqKlnaSoAMZNFssbYSee7ex0c+2BdVN1J2F8zYddGoah4ec5tYODa4bGB2z9zCuBOOQz6NHuQKYOmt+uGCf6QsgtDuYFAai0MLYFFomr7UDY3gHsOkgILSPGBQs4BKmqpgtrj1A2qYAZVth3eDYoL00uTxqcFldCaJvuBjONMrtWiXloGRxolYx6Im67iJQezIDI9PCWSardawsOE6WYx4Hz1ZHabmnitNLIwVpFCvjWBtEVadxOZ5OKF9HrZMWt2lhQsArJ/aqlOLS1Z6ybgIgbQKKzMy1aaIkr2aMAqlimmhnxQjEKGISGJmKyUANk8BwaMIugNwmMnU=
*/