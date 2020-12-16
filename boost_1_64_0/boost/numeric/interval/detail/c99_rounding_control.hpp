/* Boost interval/detail/c99_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP

#include <boost/numeric/interval/detail/c99sub_rounding_control.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<>
struct rounding_control<float>:
  detail::c99_rounding_control
{
  static float force_rounding(float const &r)
  { volatile float r_ = r; return r_; }
};

template<>
struct rounding_control<double>:
  detail::c99_rounding_control
{
  static double force_rounding(double const &r)
  { volatile double r_ = r; return r_; }
};

template<>
struct rounding_control<long double>:
  detail::c99_rounding_control
{
  static long double force_rounding(long double const &r)
  { volatile long double r_ = r; return r_; }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP

/* c99_rounding_control.hpp
azdQsGSJpXAT9pwB7HmDxHXL2n0lrluJ5UosT2L5EtsgsQKJbZXYDontkthebkL8DrD5nC3mGWvXR8wziZVLrEJiKrVxM5OYWmIaiWklppOYm8S8JOYjsQCJBUssTGKREouRWKzE4iQWL7EEiSVKrI3EOkgsSWLduAn1JVmx//c+lsfazREsX2IbJFYgsa0S2yGxXRLbK7EDEiuUWJHETkjstMSKJXZBYiUSuyaxWxIrldh9iT2SWJnEnkusXGIVElNZGTcziaklppGYVmI6iblJzEtiPhILkFiwxMIkFimxGInFSixOYvESS5BYosTaSKyDxJIk1k1iyRJLkdgAiaVKbLjERkssTWLpEsuQWKbEsiQ2W2LzJZYtsRyJ5UosT2L5EtsgsQKJbZXYDontktheiR2QWKHEirgJ5+sTitG3XzLUEGuV8v8z5PM/Z5RGMK0Ra8fbiecXmKbyeT7/+z0Z5qa06yvmp8RyWV9EK5C0K4S5GLHfYY5G7L7E3sB0RszOxrj5wYzdM0ZizWHGxt5F0i5V0pcMSbuFMJozIbYbYHZKbMXvyTtZP/sLdoQ9T7QLMG8j9o/EtBrMqRGrozHergMsgBkfX5rGkLsDxPwEeCjtBgq2AuZlxH6E2THjzytizxsknj81lNf/+91GYipbigMZzRnMzoh5SywM5kgm1AnJ89rBjPVzkKTdeInNktgyyRg2wDRkQi2HuRixYzCdEbsimZdHknua2Bnvp1Zi3gBjY4/gJsYIZqwvSTCNEUuBGRvfWMnzZkielwvzIBNqiMROS+55W9KXfyTt1PbGn+cHM5a7n0isEyzYiE2StPsaZqyfBTBjMdoFM5YvRyRWDLM2ltcwo3kNMzbXFRLTAByN5TXMaO2BeRmxRJi3sfoC0xmLg8QWSp63WdLukGR8xTCKrXA+u6s17KmzxPdwrSFGXwn2XmJqB+PmKDEviQVKLFJin0gsQWLtYB5GLBXmw4zP52yYozKfs8V92sGwjuYItpH1RbQdEtsvsSKJnZFYicRuS+yRxF4aN0yY8XnRwIy1c5GYj8RqwdRGrI6kXZzEmkusA8zRiPWT9GWo5J5pEpsquecsSbtsia2Q3HOdpN1WSbtdEjsgsSKY0byW5NIVid2V3LNMYm8k/TRxMt5OAzPWTgfzEoxqHczDiLWS3LOTxHpI+jlA8rypknazJfa1xPIk/dwAszNiO2HGYntI8rwTEjsnsWsSuyuxMskY3ktMo5PUQZixsfvBKH5iPYMZrWcS6yB5XjLM0YiNlPRlNszPiG2GeRmxYxK7DXMztm5hxuZa7Yw5NWLeMGPzEgzTGLEYmLHnNeXthPNEO2fD+WwuM3PWHt/d4tOZWSjXbh+t8l9VbXQ1zLepaBg3/raFffyDvR/wlwp/PeroqbKq/JkJ/Wz5cUuVTeXPTOlnadkq5b9nRj+b5Kr/mTn9zKya/mcW9LOtFvqfWdLPmlxEf/47JvrZx+t8E7u66B96464KUzVW9VQNV81RbVIdVd1WfVB5VfukWrdq46t9VW1DtV+q3ar2rpqnSaxJF5M0k8Um203OmPxlojYNNE0w7Ws6zXSV6U+ml00fmqrNAs0SzPqZTTXLM9tr9rvZczMzc3/zePPe5hPNc8y3m580/9Pc1MLPIt6ip0W6xRKL7RYnLf60MLX0saxt2cpyoOUMy3zLQ5ZXLcstdeoodZw6Xp2oTlKPVM9Sf63erD6hvqs2s/KzirfqbZVhtcJqq9UpqxtWZVavrN5buVhHWre0TrEebp1u/aX1POsl1iut11tvsz5ofdH6sbXaxt+moU1nmy9s5ttssDloc9HmsU2FjZsmUhOnSdIM16RrcjQ=
*/