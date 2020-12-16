/* Boost interval/detail/c99sub_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUNDING_CONTROL_HPP

#include <boost/detail/fenv.hpp>      // ISO C 99 rounding mode control

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

extern "C" { double rint(double); }

struct c99_rounding_control
{
  typedef int rounding_mode;

  static void set_rounding_mode(rounding_mode mode)  { fesetround(mode); }
  static void get_rounding_mode(rounding_mode &mode) { mode = fegetround(); }
  static void downward()    { set_rounding_mode(FE_DOWNWARD);   }
  static void upward()      { set_rounding_mode(FE_UPWARD);     }
  static void to_nearest()  { set_rounding_mode(FE_TONEAREST);  }
  static void toward_zero() { set_rounding_mode(FE_TOWARDZERO); }

  template<class T>
  static T to_int(const T& r) { return rint(r); }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUBDING_CONTROL_HPP

/* c99sub_rounding_control.hpp
sHIlzyzwz2eDT2dR3BG0A8paqfxm/Pfuryl+CGyq8jxTXA/NH3qLamR3Q61LM8GzX668QHnW3ZDzU2F39/2xXW8+zGbAeG0NYDYYxtdKMLMvBcvv8V/LhLUUzksbmDUTrIBZE8G2wtSK6QTbC9MophHsBCy3GgxzZiXYrmRDO5VgRbAAxW6L+x9Mp9hVwdS9DP08J5iul2F8WwVzY+02CxbA2n0nWDBrt0mwGJiPYjmCJcPsFFsi2HD2vLmCjWY2TbA0ZmmCpTMbKlgGswTBMmFaxT4VLIeNPU6wfFiMYg0Fu8WeFytYKbP6gt1nVk+wR8zqivnCLEaw58yiBStnVkewCmZRgql6GyxSMDNmtcXcheEjEgxnIsHiJ1S+B1SarTjXEwz3tBFsAzPx3FMAS1DsaVVDwuCZyvOeCNYGlqu0uy+Y2URDvvwhmBuzm4KFMbshWPxEwxiuCZYAUytWLFgH1u6UYEkwjWInBBvA2h0XLJU9r0iwdFiKGQxztlSwvVMxfqXd14JdgOkUmynYo6mGvkwRrIy1GyKYehrOyooNFucFNlqJ7SDBSqYZntdJsFuwPKVdR8HyMw350lYcQ6bhnnHiGJjFCvacmZNg5cxsBKvINOSSuWDa6ZgbZT8yFedlBs5gpjDYOGE/0szC75OUe84QLGaWoS+ZgsXC1IoNFiyBtcsSLJHa4SwsWDe9aeMLpwiWKrF0ds95gs1nfREtV9JuB0xbaR3+xwphJuqPlkJGayybPU8cgxEzY1d8Ny3sK5iZxNQS00hMKzGdxNwk5iUxH4kFSCxYYmESi5RYjMRiJRZn1AYNiWffOPsJ7dJZu/6CZUgsU2JZEpstsfkSy+YmjC+HjW+A0K6ItZsp2AmJnZZYscQuSKxEYtckdktipRK7L7FHEiuT2HOJlUusQmKqasbNTGJqiWkkppWYTmJuEvOSmI/EAiQWLLEwiUVKLEZisRKLk1i8xBIkliixNhLrILEkiXWTWLLEUiQ2QGKpEhsusdESS5NYusQyJJYpsSyJzZbYfIllSyxHYrlGLbBaXjXDHjBLrGes3UCxnkmsnJuw51Sw5w0S2gWbGNp9JViYxCIlFiOxWInFSSxeYgkSS5RYG4l14CbEL8nEMJ+zxTxj7fqIeSaxbInlSCxXYnkSy5fYBokVSGyrxHZIbJfE9krsgMQKJVYksRMSOy2xYoldkFiJxK5J7JbESiV2X2KPJFbGTagvz9l6SBHaxZga2s0RLFZicRKLl1iCxBIl1kZiHSSWJLFuEkuWWIrEBkgsVWLDJTZaYmkSS5dYhsQyJZYlsdkSmy+xbInlSCxXYnkSy5fYBokVSGyrxHZIbJfE9krsgMQKJVYksRMSOy2xYoldkFiJxK5J7JbESiV2X2KPJFYmsecSK5dYhXHDfxg3M4mpJaaRmFZiOom5ScxLYj4SC5BYsMTCJBYpsRiJxUosTmLxEkuQWKLE2kisg8SSJNZNYsnchPN1it5wnpgrnDVOAHSKpQh2jVk/wcqYDRDMzNxgg4S+uDGbJVgYs9mCxTMTx5DETDwvpZob5qWvYMMlNlpiaRJLl1iGxDIlliWx2RKbL7FsieVILFdieRLLl9gGbkJsCxSjHGTtbrF2/QUrldh9iT2SWJnEnkusnJv4LYGNT/x+HWZB7f73O5/EYiQWK7E4icVLLEFiiRJrI7EOEkuSWDeJJUssRWIDJJYqseESGy2xNImlSyxDYpkSy5LYbInNl1i2xHIkliuxPInlS2yDxAoktlViOyS2S2J7JXZAYoUSK5LYCYmdllixxC5IrERi1yR2S2KlErsvsUcSK5PYc4mVS6xCYipLZsLZxkyx//f9uhs=
*/