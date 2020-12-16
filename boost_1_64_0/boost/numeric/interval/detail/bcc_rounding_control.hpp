/* Boost interval/detail/bcc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP

#ifndef __BORLANDC__
#  error This header is only intended for Borland C++.
#endif

#ifndef _M_IX86
#  error This header only works on x86 CPUs.
#endif

#include <float.h>      // Borland C++ rounding control

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

#ifndef BOOST_NUMERIC_INTERVAL_KEEP_EXCEPTIONS_FOR_BCC
extern "C" { unsigned int _RTLENTRY _fm_init(void); }

struct borland_workaround {
  borland_workaround() { _fm_init(); }
};

static borland_workaround borland_workaround_exec;
#endif // BOOST_NUMERIC_INTERVAL_KEEP_EXCEPTIONS_FOR_BCC

__inline double rint(double)
{ __emit__(0xD9); __emit__(0xFC); /* asm FRNDINT */ }

struct x86_rounding
{
  typedef unsigned int rounding_mode;
  static void get_rounding_mode(rounding_mode& mode)
  { mode = _control87(0, 0); }
  static void set_rounding_mode(const rounding_mode mode)
  { _control87(mode, 0xffff); } 
  static double to_int(const double& x) { return rint(x); }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP */

/* bcc_rounding_control.hpp
6CG9c8F4LoX2SBxK7wiDqq6Vt8FXTGm/hfkwO31jgh2tPxgfXz3Ty0G0/mC8n6e2jqC8Tod5MfvXztEeNHYYH8On4Y3fUL7AeGy/K3aYTPkCc2V2csFfG2iNwfhc5/3bJYnGPrjq2D9//HYfjR3GY7tEM5XyLHKwsI8d6xdO3xlgtswGrtNk07wI99QuT8ijugTjcf9n0SHKl/kwPvZHI3dTzcqHeTBLPF80j2o5zJ7Xz+UZtIdfENolBT/RUu2BVWdmXe/3uTQvqVX7ct3iF8NagfGx/9Qxj77bxAntbOs17Ei1B8b76VAQfIL2PxiPkfbL3R60jmDezMqaLvSheYHx+ez484UEqtcwHr90583taF5gPEYjx1/ZRu8yMGdm/ovzz9G5dYi5KpDZ8y8dF1LdhfG+PBgfVEpjh7nwOWsUSvEbDtPytdLM5zp9l4L5MNucVvxvOmMKz9sy9NhTygmYP7PI0fXv0fhgEcx+7v5sGO0rQ6vOy4hnvc0ptrDqvBZcfHOe6iDMk1mzrN/NaAwwL742E5120xlFeJ7K7Jfx9O0J5srr4Js+a2h/gPGxZ4b/5UdnFJgds8ZNdtF6Vw0z5Jk5rj9YO7WknIdZM3P8+ufvaV5gtswWqW3P0LcSmAuzntnqRhR3mAOz2Zt9tlPOC/c8MX/M51QnYHbMNnWJ96K9GObI7PRVVU+qrTAnZke69LWlfUUYX+aDg60oX2DOzHxmvKYxXBOe92No2/tUQ2BaZlFW3xXSWhletV1O/2EUPx/BtH/NCKV1BONj/xA7bzXtxTANM9fTW3rTuzaMj93tRZvD9C1dsK5HXzeg86Bwz77WA0fR+RrmxmzzB2vDPg1z5bH96u+ZtE/DeGx/XRU6hvYqGM/BdVebhdE7M8yDWY2Hfb6g/ByBPY7Z/OHPatCcwXhfBg4NoBqZBOOxHdvy3ECaFxiPw6ym2gyaF6FdhdkXd2ndwrx4Tnx6i3LiBMyHWesleyiXymA6Hr+2yWMpX0ZWjdGIS2lJlC8wnmfvUww5EQPjYz+UahVC6w/mwPN6/elSWn+wEGYLD/+2n+IOc2E2+EjBCoo7jOfEkeZLHCjuwj1dbtS9SL9XG1V17OFTV/1MZ1OYJ7Phoz49RXUXxsfufvhrsg4wni+tju67QbEVnjdob4MpFFuYL7OOt3Py6AwG0/DY7nH6m+oEzJzZZzWPHaS4w/hch1X/w4FyHnZI+V3yR8vquqE15fwYOutXmsXFt9aUE2PNVTWYbf/Ny57OZzDez5EVt6mGxAvtTj7yPEnvOUI7j4cbF9C5FcZzt7QoZiidNWC8n+ebxbylOYPp+PozeTSa5gVmxexSoU0OnUNgdZmZdnhF3z91X1St17dbF9rQeoDZMQtt+vYbmheYmq8H7ZJrlEswHqO4+bemUC7BeD8Lb+ZtoTMtrA6zRu1+e0VrRWi3o8YaFdUJWCAzhw8rW9DYYTyvp/X7LJDe8WDOfOw/Hn9D6yitam112edaTDUSNqTS4ivNT+N6kvoJ43OWu/wmnT8LYM1Zu7o7A+i9qgLG4x69cBbVa804c1VNZr2D5yyhmgzTMNt0axrVz0RYLWaj17+JpfMujM9ZC8+pvvQtFubB1/TjgevpGwSMz9npi7+vofmEeTKbOHrhRFpj46ves31efcqXYJgbry9uqjb0PQvGn7ei+Vnaq1IEc0ycX5fGBzPj9WX18Sg6K8J4LuX/dvksvR8J7VpaRNKZLxumYTbVpTXFKF8Yw/uAEdl0xoSZMnsxIeUy1TqYJTPPVdc60JqGeTFrer0ZrfdHwhh6Nb+YSrUOxuNwp6SojHJ3QtXx6fY320D7A8yeWULyX5SfkbA=
*/