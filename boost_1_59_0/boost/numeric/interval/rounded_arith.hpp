/* Boost interval/rounded_arith.hpp template implementation file
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP
#define BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/config/no_tr1/cmath.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Three classes of rounding: exact, std, opp
 * See documentation for details.
 */

template<class T, class Rounding>
struct rounded_arith_exact: Rounding {
  void init() { }
  template<class U> T conv_down(U const &v) { return v; }
  template<class U> T conv_up  (U const &v) { return v; }
  T add_down (const T& x, const T& y) { return x + y; }
  T add_up   (const T& x, const T& y) { return x + y; }
  T sub_down (const T& x, const T& y) { return x - y; }
  T sub_up   (const T& x, const T& y) { return x - y; }
  T mul_down (const T& x, const T& y) { return x * y; }
  T mul_up   (const T& x, const T& y) { return x * y; }
  T div_down (const T& x, const T& y) { return x / y; }
  T div_up   (const T& x, const T& y) { return x / y; }
  T median   (const T& x, const T& y) { return (x + y) / 2; }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T int_down (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(floor); return floor(x); }
  T int_up   (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(ceil); return ceil(x); }
};

template<class T, class Rounding>
struct rounded_arith_std: Rounding {
# define BOOST_DN(EXPR) this->downward();   return this->force_rounding(EXPR)
# define BOOST_NR(EXPR) this->to_nearest(); return this->force_rounding(EXPR)
# define BOOST_UP(EXPR) this->upward();     return this->force_rounding(EXPR)
  void init() { }
  template<class U> T conv_down(U const &v) { BOOST_DN(v); }
  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }
  T add_down(const T& x, const T& y) { BOOST_DN(x + y); }
  T sub_down(const T& x, const T& y) { BOOST_DN(x - y); }
  T mul_down(const T& x, const T& y) { BOOST_DN(x * y); }
  T div_down(const T& x, const T& y) { BOOST_DN(x / y); }
  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }
  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }
  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }
  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }
  T median(const T& x, const T& y) { BOOST_NR((x + y) / 2); }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }
  T int_down(const T& x) { this->downward(); return this->to_int(x); }
  T int_up  (const T& x) { this->upward();   return this->to_int(x); }
# undef BOOST_DN
# undef BOOST_NR
# undef BOOST_UP
};
  
template<class T, class Rounding>
struct rounded_arith_opp: Rounding {
  void init() { this->upward(); }
# define BOOST_DN(EXPR) \
    this->downward(); \
    T r = this->force_rounding(EXPR); \
    this->upward(); \
    return r
# define BOOST_NR(EXPR) \
    this->to_nearest(); \
    T r = this->force_rounding(EXPR); \
    this->upward(); \
    return r
# define BOOST_UP(EXPR) return this->force_rounding(EXPR)
# define BOOST_UP_NEG(EXPR) return -this->force_rounding(EXPR)
  template<class U> T conv_down(U const &v) { BOOST_UP_NEG(-v); }
  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }
  T add_down(const T& x, const T& y) { BOOST_UP_NEG((-x) - y); }
  T sub_down(const T& x, const T& y) { BOOST_UP_NEG(y - x); }
  T mul_down(const T& x, const T& y) { BOOST_UP_NEG(x * (-y)); }
  T div_down(const T& x, const T& y) { BOOST_UP_NEG(x / (-y)); }
  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }
  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }
  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }
  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }
  T median  (const T& x, const T& y) { BOOST_NR((x + y) / 2); }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }
  T int_down(const T& x) { return -this->to_int(-x); }
  T int_up  (const T& x) { return  this->to_int(x); }
# undef BOOST_DN
# undef BOOST_NR
# undef BOOST_UP
# undef BOOST_UP_NEG
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP

/* rounded_arith.hpp
0q1QeB0ofOxR1yPp1t9n6tXbRaoVU+tW/XbU86jv8i4U3uBCTwtEh8s1PrgjP+n7dBY1uCHjvM5d0PX0s654J5RFsuQv90onNUYXHH6V5fx9B9mlpL/suJnanUx+f8r9zDn3HTrnEINOlnSgAWHFNT1OCkhJRNXg6J0jKTaw32L7b3o4cYBuvZm1ByQfMpGqhpCF1Ud9HweXlrXgyp+1t3SJBPtEhtQzyysVrirycJJotKJkctYEnEnjAdpzNtcNuNmIR3vtbsiLz0XusCUFo0OIXDTdYPFgO5KVut0TexT+0KzMxrb7YBhl5GvqUYgWor16qhwtnXZdE9ti3rOTAAIs/dOizzBtJs72d84X7D3l3v6no7EA7WLwdyzXZ/j43bjvFPR9MWCil1oNbOJ4McWfiS3Dc8XLcTZDeTUwv60tCYa764i6F+ZbedOPSViEp6v8EJApRiJvNim8DIpBdEqGAHgolMR1hjudCOxcQLyCeZ6NwSIu4YQ14FHz2Rbe+8IjLO2hxy4vKv+/nmxuPxbpvuQFTGXN55IZgYXdblI9odXVZyQSof2XHT7k22mLCVjp88YBypOHMEVRhScmtjLQUL8VFKlGxTLJa9U0gu8JmnfZ2CUTcDbQmcjeMRPi2KlJ2jm4KpGjG+fF633HoZLR4ubVzMZNpYbtkVGXTArzVv0T9aWe6D73VC6z1a5ymMQQ5pxeVpZh3tzrVZpNpt+0IyPDLRje6wdiFlQGJpNA5UWnwXY7qCJ3tfKL1G/CITyQ4ZWg95Gc3DFM4VfcKWDbKRTO6AIHSVOJZcrlcIdOhXQlL+IxGwXCgcgj/gXI1Da9Z2LM/DhVArs2zHIsTe2KNhPptTFHv9rs9m/fmntLnyRLL5XypGtaTsXPdeKsS9rgxlmqj5wtJtiftQM0pb5e8S4sVFJF6dJlFTvD+5afWCWWDAtumKiYaqfsrcMwGsti3NmfNTaDXeth2ZYaX9v7R4lawXtu6u1/lVgSxz+LIY4uDdu2sklM1Ij9FgfRQo6c12D98t42jjHqRSm5KN8e/3Xpu6fUpNwrQ2hT71OCay8bU695FXp0ta/ZF+6aXIwyDoVIdGa5GAgmc7MCUs96t5/+BJwm4LZUmfqkaSWc9Hf8mJ3/08a6Ya/CvWH/6HwVjcHhmW99+qVhU3ipbIW9XUbkhVtrYmisuzTTQPG1bVfsRY/NyALbm5kfFF0keZGx8eoaiVSz/54oeoI1mhiyjL69uMX29AXR5UI9AcgCFUEHsBBr81Ot4WgeI2fBxOzZZaKkiC6LMooVFNriuhmix3N0zzmDGLRkKeLt5blNUDB+0jXJci8gPb7icGqeZqH+LT1+7xzOmfzGNK2uaLtIuYoT4mFoQQbh3PKMnF58xxnpHi+/sL3/12lX8AhGU+gV0wScKp08V6NzAnSlcAeEepff19rOhwxpdQTkg2R2CrRMdidNIxcI1OroDwC5NQCKkgcw21oSbKV8ChT5phQORSXiD6qVBw9Ksw8kKb+nRTMXBYRDYwesKdkG0NmZxZU9fdKwYuB1a9/QkRaHEKLrgZl8b/YONTux9lKVAa7F2os1Zgz6gjpWytlj1f97l6J+z6tRAJp3Iu26gs3/H4XCRmtTVYhDikR07pSJ4MNHuD1RfKq4e5w93XIwpgUFs0uCozdARtt10r0ERfHpDRB7IkWTPcnHPVw5Qt502i29mb7LzoFjy9xTRYkEb5MSJFrdcicO8FNYV/1loyYar+nzizkrt/Yp/cKrNUznIdSw9k4I7witZLFIO/AvM+Y69JX8tftXiveb779Z35BdF1nSprplWfvsjuIZIQC5yRFqyo2Ge+Mtgw7cxkVfVdefWwq/Mldom/TKVanaPY3AuwZK9oiUtN5Df+qWlGXdfdTj7MDU/eHm3NOuyBFur9NDTYGKhYPfd82sO65DPPd+DBMTNDefO8YUUxfNB3DZcV6uN7X7r0Ffkt27M8PhRxjSUa8h5g92YWQpiO+s//ILCwVpUK99ZvboI2txaw62+L2m0X3frvg7c+/FTe+ZS+um9sd6+y6wbqdyakbfQp94bwL6YFAoc6oOjpjrYM/z636i4HDOE0UlSe2HVk+xdzzVZHEBHGm+PxsKb7FvppOwfC7LGGQ+BzTPvx96Hs/2pcbnmZ6P7nQW+7/LCgZtv6/dXSxwWTM10T9DKno5wcGDfdatCDkFvxsBF6vSs1fFBkLTW/D54CBfLI2MVip7J3WK3ffQ40mSP8LUGgKZVA0dzydGauFdO4ccet8UxGjd/XfL+FMyahTCa2xKytsnZRP6hadDG6IkSK4TtdeHMp+vSxH8awifFpjH2t3jK249dsKoekdoZ0Y72zuWrmgZjR90aEreKkTZc9rEmTqHTgU/ME8B8Pc4Z08PwyuFKnmrdmkonwG+OidzKmsuhQpEe3m8OCyNkpfheFmXuRHvJ8/ovY8eUCDYlilunAHbzh8rbtx3/ivJdQaGxdT8zjrnmmLG1Wl+WNk++YFGBrbxPSuiHb9r++/8hgahXyQDDbmCASrbGKd6Wm8QIPyRjZm+Kpn6oKTZmXu+hjBn1HMIF9A2bksx4HBQhf783CvFEWZxkNRDEd61odXowC4sNIhbOqMhx/dCtv3W4WliDrp4Ib/tNfcor3NDR7S3pM38cDVJYuMGd8SkklimuCZ4imiDVNiAa8nCzQprF8iIcK/rTUzcwtqEViLDENixxW9OBimxQp7FjeI+BN9cef3qekxbuvrSH0EYlxL/e9RpdUw8EJic1MHaNLovfgNwlFNjLvPK2YxfdzXcM1WhsoT1vLKdZL9IUSi7Ot9kb8Y+EW0EEfPkieR4hrG5cuUi1yMG/PUR5az4rbhDcyc7vXOSD2b6ZxlzAgph+/JXCus+6r0Pt/vQ8PsVwcb+F1bG+gCBtJ5lzoqWoJbm0ycv7EzioK3nPRQQc/rXdCrtkqbortkAdziH37/31MDyYRjBT/9ridjxbeskxLQt1Nf6ApM1M8NJ7EPNTmsILnccv5y/1zh2uvWZdtqLNrKIZ6Lcxxh6T2aOs/xpO19w3YB6pRaLfN+2JPfEdifdK3u7FFHXAA3Qe/kyysq+/W1VH0Avdyajvo2o8yPf3esCNyLRgLlpIekAvF0n/V7nPvb2tyroUJOc10f94blUjkinG4NHpzwPV7vjEdpW8Ccye6anRynDRlL3lFYkLkIGZ2ZOj1js9VV0PkQ2txwlI9s00s7ZvnaX7NphBP7wSbX6MxNVBXL/X+yBHdgKCPQFYVuJJxtptEPfSltKWtaa4SMeh0n0Nhuv+klBcVxOYD0G6jj2FCOGx2Gxxp3SyYBHf7iTiSSKMm0LI1DweJnMuAONZXt/gEOCbPtaG71TvYPFoO06Kqk9FsqzU5cCU7tlZhb1NAW5Mxsb+hsNbDwJLb9cZInb4eOQg+q1VcJ8DQw9zQbnx6t8gbXDYK21zAzr5hEKPOoyP+igH0dTfgaMCTONEmO4AQ0SJeLk9r5aizqMvTarrypH7iz8KzZr4j6oHRmm8/IM3PCVPnKoMlR7g+IWQhPimL/T59ftQOplG7VOAnWgMPfNGAu7OaWjUWpnwnXiWzcWAIrQ8p2AMga2qgzrvCNX8kSpI4AulD7xPFbFEV9QxfmpbmZm9CDhQfOVLHpC8P4bbOmsxGK3F8O6IwbpBpeDk2KIe7qdJJM3Ku+s6H9X//wDKxpdQCJON4l9mBV+6u8fdSwQOTld+icJ+nIym55uPRlGyfgiyJg51Mxf5LT2U2nnGkII+eh35v8R7dSbaqwp9V34Hkz6M4dTqqq6jgEMuy/P4dv1v3NprJa1O9ZNCPimqmOrfHQ+Pr2uU93XM5tIUQYURUfZaQtseB24rqQGaJLYVNKCNiaRJz/aDDJ4auwAq560Yc7kyi40PcrCxElnUaPHR7V+O597qg+KCIEkovlNZhUMl2tkaNkh6aP3JoQN/yx4jTx+UsT7RQtvotMt1LezZavrUvKde7TJ58ysTm05Er8fJe+a+kFu2G6zbah2adDB0JRgLQUMNgNv83odJ88eZQ0lJsa8KKzAToUZt8muwtZpL6SW281d3hnTT1kKlmCeednnTk6Fg8tr/EaOPipSspHU2D+od1CQ68sQc7MmO3l/dQhmaTnUEd1CzA3b4Hm12NBnSfhVeq1gSKMvJfknMfSpCdnB0is2skgWwRMWH6Gil1bJThHjm/FZaZAOpoAvl/XvMRfI2yW5d81w+UQRcn5EHW7wQInjGgBdx5msAwIMDFQ67SGgcgGCOZpzSkTNz60L6smZAEn1zFyYdgVIwmp3gIY5FszQlcBhSAbWulkLrdoJ2Troogjg2DjCohfLbsak21nFSE10nMvICJadOpRGZ7Jb+HeJ9WaPvGGJtQR+BYY7FECMx32cXOj2RixOKh0rO2QswTJdvXIBvZUbfeZR90iJPOJBh5lM21UzlAgvNHdTRXF4JH7LZGARzeF3jPsjycb3pxGimtcCuSxKGuaox4hU0YeVkXcCDASXDKGiJ+h1bvaxKHb4x1rOegssB2wK2/n1gHQ1aFN/SNJ25yJfc/+Xm48tUL5EAG4PhIa1QOA3KLlNVyqlWBbuRHqcszm3SeMt9SD/OXO0ugibv6SH/7l2tAE+yNZR1SIS/Z+bfQpFjY5QE25DTLkgye7OkKFE4ym0ocVUDGvf3UGxrZJtEqO+GWTquGN2G+F7jPZSs4H8N20Jf8iKue5viF+6cVvY4QgnLwPga8labPFwF4Z7Ggtja3aDJ+g3Fv3gFA0SdZP+ReTPSF98GCvRpmUe1dBs69Ds5Nl8La95iMsyGr1HSCsrTkVK6F9uMD36VRbpMnTugWJG0Nkk55QzdwHoN47lRogzvUxc4oJVDfydJOrZvYf+0v3yonTE8WIjTMaHmK6T/bXkGqIeuZ2z9REZqdD+Dls/uSB/gVa4m8OQJZ1rZa1MyKpW8ZAYBXZdWyrZs6FJgU5ISoVRYantWXFhvBfSta6dQMeqhcxnxTdStGs0LU+VnHtAg1yMwVYAhAzv42DKxF2GjUMriiAxVUu2pSdLfF/hI9sKC32KmiZ9wNON8WzS6zUg7Q0gxHsrdUJCtS9TLH3MBkJW2xkTx1x43X108lf9XXrs0jJkv8PpdyMiHef7sv+pm/hHOZpOUBSZ+YhY/xY/f+fu6R5DwstWTuI5Sa8oeixlvCr0vb/MpbjOdEmJ4jj3e63l9v2qk96h8nCPQFS1cp0sU+KY4GHoNWNMB0KCUpyBLeJGap+UCqiARbtZh7rQMPWfH25WyQcHKex6uhPnzbp5psUvdVStLTkknzADo7VVT7umww3k+Rt3lETzM1VkYdYkQm4kbUHfNX7nEz+vrgczPqShMw0kIRX1Snqj3igJvC5G8QP9a2oIZIyHbUmt8Q35CLODjELV0277+H9A1Qk4YCURttG440qN114diWfswoLqM/kUl7BLohVl2DmkO0XRu9ID5Vh2faXzbSNi1z4Xlsh7q6q0Bfm2+wANQJGnSj5v4ncwUgmkWvfJUo/Bjo5Mpr936g2aV/jZ9vWEpg62LEUZgnQdBX5hjycooDR48bWe5fiNjkaIbJr7CMQ1nKtETUURh/W8wIZ34s/BeshcKGzvFp2UnnzLtDbE1lq8BenvzltdbcZtn+oE+7cc8LSnmuiRLvLfev4u8xprD4gKvW+OG8PzIwUbwstMPiDNdEdGmynlXXhTsdlJ2ijRAi+9pc+Gd9tiOGJteBhTrVJWtez1jLoHO8zm7zvCI+VSawojaFqFnCn5OfzaB+o8yYD3EGqLhIt9zZHvs3Wc+8BWzvjsxGYcFD8gV5cwPdnTI7Rh5dUfu15jANXtZdu7XFh06D2LGNOfkVvfNYhEY8bicZ2r6I/Gp9sNKYFfXfsqkxUznqMNwEeFcL4EZKOcDrtpB7J6IO+LeCQT64J0eK2EylrHQ6RSxf5FUIw9fCI/oBGbtzd1F4o/jBeKPmwAepboIjuDrtcIevL39HKROpuX76TFGDeB8RQLS7k5YxEtfihY9k8Lg0p3eg+DVgX8AHdO48Ao0qTSnJSls/QY3I6ssxeB7erecrS9D3Isjt5KszMNp04geWyxYuHtwUJb81mOmTMXY2nhQu5yvCrG+tjgz68m/um0Te4cp40x9FpkpRTLvouOmM3cyOgqqr1P1ap6ei38VkfN/EBlElbzY0C+xWK1JqAh8A8hjkBndvkxMtnqTQ6REHaNouzHRZyVqg8QquX+V2PgaEsdtluodAsBF7hO/XKNfCHudntbXik1/XG1SbvGuR2MPqn+r7nC1GbMndMEo7o/h7Be98nDoQ8xICIdywYNdzfUDr66dN6+ruFhnWhGgYA9cv0yzP9tGJ5A53hpA/qmhaQ6yr4v4p7q9vPYXwQsA/ah8uWqPSCJ0lEUbl/cqwJM6W0OCaGnloab5EShCyUiy6aZimLBVdMkDIo/6GHggfFrlzgH7FjJuWxNFUhMFDCMVLJdRMWLCTcawnPpBhRuZcXlS2AchWx93sZq+lGMRi68sgY/ZA+hR82CfsSRsgyuAbWgjnEHf/GNcCU4lI5XK1Kud71M3Qs1ruTw85YxPZp3mR2Dt2bF47bp1/N7sFC/aX1H17gl77yss7PUD5DXOJd/0N4Kjrber6MtnbRYFzj7q7XIVakVCYsIXRqE74pWFfRYZ5YmWjNRokQYQ/0TrjeYd14VYDZO2S0DXSSS6C4iF+zgRu+D6JJrmYj2HrPy8c6cXXyHSmFecz8qRZaj5U18VaTnFjmBmXWYX0Kjyc66J8z8YSlxxiiNF0BHgC+6Wk7KMYIrH+T2S8XlK5AyxjvOwp9NRhu5J5KxSTu06OdZvneROJ8PCFS4HKMEKqgWBckFPsEE/11+XqJV5I7NDIPmmV8p3T5DsgbeiKaZZ0FbtnEirDPz6+VeqH1TY2NgeU91uLoj9naArx+cDT+uiWtyIl0thPJ6s+TDKtsrHXP/jtP6gnJnIVn1Td84it6lSZrXMK5SQbcn8/huwNwsrJLnBvf2IScEjSNYQ6C0JnbeE+58+nfcDKbLbB6xZhFfstkqP5gTkUt5MqkmOChI1Ri0I4LKYEuy6V105oodnhph3No/84pMx0y7MV2Ltm/r/iPyPHy19NNbEB1QklgCHVGpZWC4q5VBIAsz55tI2ki3bDsZF/Ca1WaL+VlrK9nSO0YJj47hRN0GvOnXoB3pZNmvbZ9q1k3/bkLuzdMwTV8k3LLog+QasZ0Omc9FyqF30ErJ2VZ+XNCqgl6cMMEyv6KdafN23F2sBEXkxVVdLPv0sCiZbEPPqZIdYbUaQBuiSKlFMtiH/OkFsKqpTXhPDV5fyuvAC0yAADoIVbRP/qaUA74PnDPjYCVVJkDi8OKUvedYDqj8OyxtV4TFzyLwZPef+H8emM1iGImJJnd8hJh+JAufvFXb0oWZV4Hl5Tro6rd6kidoySwRsA/CRlSqH9Mh/s/FQC6SFaP50OwBgRlAoxNgwrq+roOal72gsqS2Xxw80QU1W6Hu4LLFTVmhJgDjKjhLdLQyFC/dNVqxqA6x8YHl4TvB2Q/EaOzK0vnN3cxSl4T7UcmmVxZKtu3iArpI6+EXuZOaL8fuQJ5orN7p
*/