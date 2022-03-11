//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_10.hpp
iEbYwW5VGKkDcEAFslO+UGi2kqaJkgU9Vcr21pyJEPK3HHv9KclGpT3ZyWH2Zy2+gsTINpJ9UNFN2q3UbwjZyz8svtkJ4EmNciAWvuIbFmexkRjawNPXWRdNxbk5q61JMPDBWO48NOZhj+YDcgKzojbJemoK9GQFzm5Zuu9oVmS8o79eYlefoaPPhYXjMZewlhGFQsqQ9/WjuW7UFH9sED4I2p0Y6/Nxo0Rd7z2IuOSx7unkDI7EeKDfGTZYxaxmeLQOZY9O9NdP/IaBhOIqL0rGqHmv6b/1Sc63kxr1ensNGV/M9YSrhYKtTO5jf9lOfGK65Ix5E7eA32Qi/G5GfO51IVKS8CdpZkg4EHiqk8LrI/TJmuU9i5BFdEb+s4e59pAyLUK8O9rlZ/ywS/8dv12wVSDEl0MwV+NPzUjChE4atrBK0SPPIgaxqHY5vu34sQNerRdk4fh0R3ckCkawcd5DA4CIevpwOWC/NEWy+6kahzUnbJSaRv31oV040XjV8SMqbyUQ1OEvYwSdxZRNR94E3qW9SAfB71cCmO3Lomkcn1GaptlO5+FFJBZzK/tIST2YhYuaV2pw14tcAKkenBQmNEgFKw0EIVusCzyWmjxzbmsvR9u1bOXycWMcWcYOr3KI9+e1ksArGI0hdQ01EvJv562izPHxhfFR/eGjjXyOydt9AgaI5uu2pihVV8wmVWoBSll6CnqTOph0wuw/TjfiVbmoeiMiwYodp8S1nONL8fA3AkuO5RfYD8QR3uhwMQR3qOnrTx0+aauYYnEP2VsaOgOM8C5CXbsJYOMsXKHG8gpdevHbb77LVmU9eTyGoX9q7MxrS3BB6dATvOcSkyNlZYjCZ6TlcPgP66setuZrv3Q4eKcnbIRH94xXreiBzk+pHa8UqbZhjv1tmO75ixcXibxsXDPQ4VU0b+Okf9mKAUphJHkL0Uju/BpXurKkj26k59/u50CCVzJNKD7vx9pAk17yOTyMhgxeUTfVf8ELV5DJOen32PnuXAW2lxwrQBfyhF6vkSDAuB1rxyPYr6igtfYU8uQDc1aqd8yhCqdtYfewqxOWXEAJCDxHSsKFW3jPDQvnv+/oCaBzpeY5Da/U1qqfV/Bxr+ar2oPxU7shOEjhAGYOlrktdgdAhFPjJC9ClHYCaU8aDZRXIDp0bm7C4Qc4Cjba4FhXx46PeZUUCUqCvmrl8wMMpy/7le4u2OE05M1YNAzCQcH1yXr92FfjxDaDRc1PT7TxKKiPBiq057yIVjVRmFu1L8Y160qC74b90zsNuQ4kxqiwZajRhKtwsVhHxMVFZJQS8BzWMatMlocHTTJEshgi1a5uHxLfjdN9zLljiUrf0VUPNIQblkdhnAjbOCL8bOzCzMWD5Y/qwiTQwtJJcUMPrBtumW6mSGi+GFMSuRMMwQTtlcSBfFgYJBeIRNe0fVCNW5VdWUCTL+Va5KyxcC8DR8TV5l9XCelN6CbDVpYNtwS/A49YcqkjX/5DH1eVAPE+T2IPbmb+w9oq30zzqYtWJj068S5xxuVLea1cXNFAEICmB3UvxaEgsjGKaTbDFYFWLoI8rNRU6Zrt7qzCy3U0xMXSKtkICDwP0/+0nBgvjpbOumMP8miwO8mENRkmH3f70BXkH9nzVSAKygRvJUviGntUMwu2e3emGmk0zenbwmOKHAj5PzvzOsF3MpShImZuXj6JJlW7zYE+eE/6U+UEi1PtiNSX+PQiCuEM09Pkw1Eya6it0OUqYOneNNSZDkJZONrCYz3pfez0vcNxsYXaDmDt97Z70VWl0eWplHNCfi9WKl9wFvt0OXRTvyVvIiWyUmwBxO+b54zPW/APMWUMu2Gl3yTfoYVsd/h2qZ4okIGR50TRpX29soRxfAJ4OoESMO2SrBaMmdlZpiyoKebpo53j1NZUmgwSJphJzyDEqTPIShbQddU3GOGPza/mRtuUauWw/9sYT6Ty9Qbv5oXjmJ5dAGRW/IWY/jcUz5851EGBtTCcgnhClme34/eWto2sAcYsi5GR6K9NyY8hBA59O99CRf4EfHMD2tFO2ueVPTQYlx52zTVoPb9UoUSugJXN5bxW6MqnVJXas3UQn8Or2yFjB5lCHw1Z4cYrotLuAlJNMhGS/1+ql3pAUWkF+6M+tiP52RM4jw7cpfg3vNnoBbxhwrHmJLRveHBmJ4GHzu3GFoXSmOEtf1GIiusGgdXFkxOhlgjFkO0HNthPinijjEhBG0EQajigUEBUrYwr1suSXtAlb3FCJetUHy4nfGShnBhDbA4WXaC3IE04jSiKeNcjf3i2ppg1vXXwUj/GEfHX53/f91ddiWbBO9OlB2+EkMzvFL3/nPeuyA9A7EQcuXG30UwxEXRhBfNJMHD6pmlxtc6RIiz+afzMjXegCz1N3iiKb+REWhgdpO1/1gmiCdUkVCsv9PO2iNIncsYBKdPQ+SGonkHS2+28higuT9eQERO30VEcMZV18j5reUfIvldWQwXFgI+xqjDuPBXYTj7IBFJ+R30owRQOT+xfAxv2VDNieYT6Cqk9Y7bVKHdgG2WRNlyOocoKBpQIOQEaUvBrrEW7psrF9d8hQrLMb9LwJQj3cQ4jTFdJ4RJBWq7wHRK/oP43IDvzyIMCpzu/e4w3tfAAftB+HtYrwC3JYrTF+b2LfM3h3c4WZC+mK39mjrZgZQes3fbtUwEiC+m2RegqHLY7tRyZDC3sXETB0Cew5Zo2wFjmD7g3hDYn9h+8vitvkVSXNSH7lGdDk5czEDtxKJfMxN5OxJ1VP1DyyU2tZe4+6P2LeMVLkrEd2Mt23ROC5YWXK4r2GmkUAM+/krMjuPvS8cgHnJzDPIOaYN51s/GOwsdV2Cn3VJlRBGmVspF2bGCqkgATkaZl2bQ94+awG0irVVZfnf0aXs3le8IaQW9APjkJMu7skWKe+ixS6jAmcOAOLBjo79Qn/p2PGng3dTnvjNpaeJfxiS+y/2rhnyHbWdFJhgBzAXEhUmTyDW3XS3lTASpojwjzxxiy48uoIBbqQJSVWNKtVAGOE9laQIntsYpALDMSG3nzQM0WVK+sZcD3OpKzd0Tv7QBZFbqUs2ECVT+GiySVtZjemFqQrbi6dWxfCm06c0Sbj6q5JRwqIjEZZ9s/tcMdBh8wRHNjmIvuxywzlsCNsbx0k9uBs6H+owcIHyP82+R/lxFuKNkf4jps8r3B+rJv7R+l7pGDFD93BwfVK8Sc4YRaXvhx8T+1JI/lz1QAKq333dKpQzZWGr9PwUanEI6QedmLKNarBEa33wm+BjNptZ+XwV7Gy/WZJhyCUGIiAr+aad1pFukZ2JmqIEQURDEA8TZf5HU1oYv6NnyEZ615WAyD3myEyqtTprYz2M38cNkQUvXy9KJJwsSkCD6TSY8ozOTihajPMbOyEGXFJnrqVgmJV0YMw86emMdzbyF5rcNh8NMtAXTDgo2UF5oetGMBGIRBCYoCjEs7APUGDwZVlM4DIWkweNfdT/dkl2y5RxnhEr02wegzvkYi9JWDo32itV/Vjkuqu1TbaCDrdUXAA1q6oKDUQKDo3eY39dco1cVGVibTaLUpHtRKJXM3xG20dnuvvqdBIzflj59cRGHGlYt0N8k+TvmP5b/vDQIgNVE8OmMJb/MIjNafTEIzKqEboqsWdP4HEn5GaKXkeHwnzJnpz6duWZGAh0BSylmBi3WJzGLXJbL03L1iomV1IuAQGMC0RO+FTdX4PCCKl850Jq54A8UgMPZ2qmDT437D8oaIKJFmryCcIYnnez960o1wWvV+VwLnp9xsKu1QLx6GaHro23IRU1IOoRPqW5JlpyltAwnUz//85b9hu8vawhYoWnmXgfa0SyOCyrqgIU8mUaVFgWLwmDbccMbSw1vXMmlqvKJPNQsq+XuRvqxJ8UyUkRMbFmnI78RlTVzKetIN8ykXKOEbZLXZrcg/lAKmHI9AkeApG85p0EznGU8YSCEExF/DI8SAC8SGpCfxilr/O2MtZP50s4KYro+z5HEOb+bT6Al5iFps3v5hcFIVAMDqaF75SVftFmZvqsrO0kCFlHycjJ1aEnTh7NQ/XW4FEtiWC4+D8xdp3nJsOo0VIjkWjFC88tgYEHdrSOxIItcVlHyKjTRo/ME2YTemVqZslnUNhwViyGI4LDZacKsIIktT0uASglIGmvweEUMsuD05SOKmlqa/SIw/i9FAbdpTBAMVg0iITe2lFKUOivA4lhIhwCfEH6jOSltTGcb69oxWjuej0tdTz1fFf5IGC2g8MfsXsswPlylkOcBYuuH0cZIUYyOvpQqU5ICfiD6fCGgMCAD0B/gPyB/QP2B/wP9A/IH8A/UH+g/MH9g///7A/YH/g/AH8Q/SH+Q/KH9Q/6D9Qf+D8QfzD9Yf7D84f3D/4P3B/0Pwh/AP0R/iPyR/SP+Q/SH/Q/GH8g/VH+o/NH9o/9D9of/D8IfxD9Mf5j8sf1j/sP1h/8Pxh/MP1x/uPzx/eP/w/eH/I/BH8I/QH+E/In9E/4j9Ef8j8Ufyj9Qf6T8yf2T/yP2R/6PwR/GP0h/lPyp/VP+o/VH/o/FH84/WH+0/On90/+j90f9j8Mfwj9Ef4z8mf0z/mP0x/2Pxx/KP1R/rPzZ/bP/Y/bH/4/DH8Y/TH+c/Ln9c/7j9cf/j8cfzj9cf7z8+f3z/+P0J+MPiI50Rs5A+gLpFU2eDKKmqAHOIiSSTxcbQ0IrJv5TNBq2GQhllMtOmQ/bYxBpIjS3lrjmlWzL7urIZhHzd70nRCtlK5JU2giTV/MovnbLcqj+SA8FeZHMxx6tUEV249XOLXYbBFRvyr3gKOby+RiaAR8VGlpuMJ+5X5JCHD5IgBO0ZvXva0IdZnhOqlKAiPdGEBc+x+2OxJGw0dkqAcpHp+2f4VQKD6DKhzRifscDInEFnX5Zo6EUizeaediSFLnaX6cmxNOZUKnJxMShHoUUruwAQPuJsBqVF2b1ayQY4ee6SY2aFaoZo94RJt97jAV9eRHA0MLC0hDWKniZVhF6QAFrWPgqMra+iA02eC/Wcqb04uAC8q3PlWeSYrL1WMAySFxupi1EtiAHUjjlujjv0SifjHtWbggX2fvw4yGpqz2VVToTeR5Dr4qH7DUDHdOeQOLekfY/GAXZ4tM5kehHsDB/+xrv4izd2bHFo+b8z7iLsl+DrJjnivioiQ9HZjJly7bPgixrLZTL2LRB5C8uKAJSEqEh2SlHluklKxdbUq/NqKq4F8X/DzXlklj6QRpQPsZ1sjexLghkyoBKLsNcIfHKSAr7x5lnnD2OCe4vdg9FbgwJGZwVI0HnKb8TGBfAJowYZyzsFluwewGwVFb7xIZAbPUA+ucEPWoqbCvNunrc8T7rIXp/+Ugb5u6gq88qegnuj3uRHEWl6tovsEcQz6nZ6WsKk4y46Ik94sybClf142dOWlLH7Xb+0OAbqotY5dPvGjuIl665uMLhzbyl6aTb6xDtDjLE2MJXkX5yc9luBJBaS8EOhv1Mk5B+ZbbhoBfe+g+PNJsXpac0hoBGDXHczXAoUCbmHlth4htQ+jQJIrpHEPzGItJQ1PZ3eUuDQu9G61+ILku68nxt57G0PBVJgIG1mcb5OYSln0w54Dc5WSiLB3zrxKi+4gJYxw0aQKdf7TLVUXgDP5BuJ/bHTC/VToAnCZCJBtzqhlf1El+ZsqK+6giZg/bLPoIfV71krkQLRr8QyAvxo1Pma+v/Zq/sxTuI34BbTNmiP3CnO0COjDox5xDeMjEJVc3OAk/WB+sEiLr9bh7e6N9Bqg8RsfswyEIKPvxlgy6Sx6FAquDkF1RBaqdDvAQdVxcJD4zUx1x1UTSDHzxArugyHJmDFl5YBAhOQgyoCWRqv4wb2+aXMRvLCL3v2iAWnpkzrlca0iaqUhnmdIIZ0aVzCMQb7x6i/MFfggMoedLCIGUXbcCQ3JmkdiRMx4QoR3kggcyf+JICpc6Xr/t5opZH32inTG2y+4HXwqOUsYxFnw2Sx/JOUjduLHXnsgWB36YWFFZpNQbyECMUC/+8fEW9XZb5aeWAgSPxFWUWlZ2zQGxaV/Mn7g1GPz2wgBGLz6qXLhK5J4ZYGo6Mnhl5CGxl7TNMyrMSWgDQb1xmq25DlNoVPb+kU3+BJG3zDil3df5dtpzXBaOqUOKMCApKfFKY0qeFta9MBEUlhriOsYoQ5a9/95+Ue+l9VKG90lhAFgQAd3vxU+f/CmyOqLgabGInl6wvY0/p1c8Y44Hgc5TMblxZQqEGNXXQl9A6VIxfHzoerRl93AYPHrEo6aY4stF+jyP7zshTFBrU2J9fDAJ2H1e+x0uyblGvcL8aH9lYzYvsIwohsPB2Cf4wWpRlWyCleMQg9+/hiRFqP5Yube63rMc6nNqtBG/3P1P07THhQ+NP/IiBh0NH0CjFuu5QOvHJ/zpKtSzs1v+WouCeJjYyH9yd6RsT24oIibXi4NNmCrhxMkV7TNHaeEvLKkV2Rphb4aiTeS77M9+0tK8g2CSfvt/cjbuPs3uPiI6q7nduisoBVGiC1xmJ+DqaQWZ8UMuKhCnBAUVa8sX1uvEhmmoX/mDs3JXGYLOpMlg5gE9fPsMnqv2EZ80Kkuut5J9pwtfVcYBHUAcI+SFI/LiYokBiE6zCTQvgSe2eHebo225ayfm7BTw9dHwZQDNbatjcS5VRsi8nIXMm3ccrsKnqpxP22AkzJOMpM556jnF9Nk9O7rzqQSaaAeJDPt01jvdFFwMg7ngeTquH9GUMNxEvc14xBXk3DcZYbvQanrd+XSpzOSYoclflbq89BsmuOXQqyYhTvhVFexz7wBicLW8qj6mFEy8yeB/AUoLjt+VCs/97KErwA5S3hnmQLiFeXknvC3Ol4k1FnLLk6zHN2iRmoxTBPKTfhHQNsFZWMRPhdQqRcXlJGLgr0Rao2fVv+w4u8T18O0TMYbnLLjyd+dnMVNXlaio2ogB1R+nWhbBF7rn6DgHy29GIChzXrL2rwHBYd3vn7+fDLm2VaAiszH5DPNak8dRXU/JX8PmGQpnrKkD00uv76qIsYgjXcDWjHrktMjLuKW7HZIc+dKHbe8S3KxnIm6MphxMMJhlpd6WkL2PEUAVlyBT96f3Lxu3bveD7NGlpcdHRmX+4xeUwjJazh16FzOMuBK7fkOzGfbLrdwLkFsOAvABaZEWWd6xCsxlqY0NGakxxE8hsnFEhGwqtcLtCg9fFwnZwi1DhDwcT6M0FutSfdqEfbMu0S+mSOc+0jHlZULgrB0+cTq0z3BToIOQGXXWF+HqFa+ao+k9uuZ0aU+rLeU636FCs4y1ty0S6H36sBZ7PArlN57CH+PlAcTFlQAZ+WBAH+VkF0SotvTiWIpOabvtJoElFdriYGKZIqpX5I7EW5+UgoNrZ/+0uv8PgdkR/XUF4AKm49bt9O5uV26gzwVVZbma3/iJvWz0kK5STtzXa6K1SXcYNWQGSEikHILTemoCOpZ69g98cvDvDDHGg2wpSGrSYBBOD4AepFi2/lilO1jKn8qCGhOfVfYxh6xTuQPW0bfq6Ak+ybrfObFCfXvwUIlgXdKZY7asa61ZfBoCchI8NMOuKmLiyLVmfe9QfZ6/PDK6iyckBiFh2aVmbpw3gi0iRCxQM9y447kEXgdjvgM+JEAFZIyUvq9PxFcUEUFXChOWpZW08Fe8A3bmOnCxGZ2k97GcND5eshZHOQIWKP9Vh87Loy4SiWC6V8KigQ31ApGq5SfaSdW9YQn+pX4mIWbPdjHaGmTlXUA2BWcFUsZ36ULQpXjxw3qQwOJLQKETzWC2CrPVLwS2+dLYN4iOCA5fbvBGWP4ObVXVvIhdwucDDu4mEfqUFlk7gedoSWU+FUJ2iqf9k7o/cnbbrXxXW8ilaehe/hKoxKTWgXHYsVTtSV6vRZlkBCPCBiLMLzrMkaOl0Vm5IjToBJLzDaMMSW6lTwAaXbwfsCQNBGbBntZyOsYUBXvHZpmzUlrfM7w5lfIx4X57VdVYQIzJJTUIJkUyXlv+1g5vbi0i+dT1fT+d+8nxuKJY8JNUJ88PCjByVivViLxsVG38KG79mMWgUU0u+fg/e73i1HVZgwA8zGSGVvaKAvuUXsnR+za9BuloNOwwWaqBz9i1qCALtUtxoWg2DOVQf1isR/1mk+blOcOLrZ926nmISMZveydh4/F7n8RehzCVbEddR0PnhYcHvGG9UIjOCpBb3ViTR6opD62qP3WzgNFKJAgQd0x1duZFwUPvUVsbtl6guNlAKUYsiVZ4pV0LhsQUVCpiMuNhddSw/cK+jow/y9eejY2TpZI96jmup1ZJI5b3wG+hs0+sj3yA1gArxue5qEvAZn+maiwu+5qPXevSrRBFs7wkNEYTkTCS/wPjz5SHJn9km1pFFTZZQftyiO4gr6F7fPfaNRbh25jrTv4wftHM9rCsNJ3tWUYj8izSzwBh2RNHlz0LvziHcDCSx1g11x3gCSvvQuCMclqZYngHZmiSVzIt6kqZOPZJXKYLx5E7nw/SiyM0R22/5h3n3ocGkPAY/2zvJqmPWPhZacg/CXT64vB9MpTijMwb21nE9ObVOkEDVMaQOmwvqPD3FQBfU8swmXmNNRXQ+SjX54S2yGMhAUC9c0aMa9E44bjxaZFOJAF5DzUtrbu1CDqOhaZXj8ikCBmuTdzwHcDJgLzHJR8CvuYBhN/zBYEHSO1IbPQAUAS+r1aWtjkY/CB7406ecIu3dfWzDsBiYqUL3iP8Z0mdNlJ6HBqDmjj7ewF3ll1H79Z9Q5kgaMxd1NtSNF6KImWTIsjBlDK3M/KPQZsHWczYaHi+3sNC7PDWKbltBB4d8GXcrqGEsjsc8XzlyEsFkjSlqTL89DePRL6GOJsGcYu2X/TfitWLGHxL/9ca/OnGyQWnZkvnK4YqxMxsKsjk53BrU9OfA+BhhOMP/vTTN5lQ1cME5KrDvLicQlFChVFPLVqWFC7wCs6N9KVGS+clN3hzxJFDcd9UzzhmSYQQoyphpZkV+zBk1ryj/1d8v75uEM7VpXks2MV/THYM5ujEMcFc8Qp7OA6lC6C/nz1WwKAGUun18RAJ8QXFyYGhHOV3z8bGrbvI46Vm9uhJXdWf0m3MrvakMeF6Gh0DhXuiklg6qQGiLy5IZ4TQmIHYWrqNHUDEs=
*/