/* Boost interval/detail/x86gcc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP

#ifndef __GNUC__
#  error This header only works with GNU CC.
#endif

#if !defined(__i386__) && !defined(__x86_64__)
#  error This header only works on x86 CPUs.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

struct x86_rounding
{
  typedef unsigned short rounding_mode;

  static void set_rounding_mode(const rounding_mode& mode)
  { __asm__ __volatile__ ("fldcw %0" : : "m"(mode)); }

  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("fnstcw %0" : "=m"(mode)); }

  template<class T>
  static T to_int(T r)
  {
    T r_;
    __asm__ ("frndint" : "=&t"(r_) : "0"(r));
    return r_;
  }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP */

/* x86gcc_rounding_control.hpp
DL1L6r3zQudvm6xlU7MVKb2XwCwKGILOwCaN91pqMVNl+DdLr5hbYnH0TrFYGjGtl5/n4kstbZhnQEgPl4wXPAFlsXRpxFRvVfL5nH5Ll4aMmy/k5B05x/kH+TiDjpRjmL5cyXqv9F7LLbHYTv+AI6SY67WAIZGaISVbMhV+XYpbETN4B/rfdkaKphoqzKSYr+5smk04OSE1IaRGqmlvP1cyf8Jsd5X2a0nesaVs3tSu7lJGdjdezIcUc1HQpZi0+Z8pAtHbZexk7GAJGALd2WXk8q6U4pRdUwsgpOzMasM/MyRKOqRIOqXg5ou57cvFnEAPjJEki5Gys6T3kuzbdSn5EVORXnYW917QT0svKaM4coqsKpoi0IIBQ6DPytmRnH4TrEVDjsC2CzmSudzlSOamx8Egw6episbe0N6LLZFcqnthutGmgxD8d/PydUnLpCvFgrGrcYz1j0jmTT7GyZUKprM0JHluGXlDCMSVT0I8WhrERQz1dm/QyGKLG6pqPzE+Fltc1rkeabHFTaIn/k6qDGZNbcQelrusZESEJOPpMUYacbOmZlwPq/iP2mLXgrHJ2MMyF649pMKIaKgHrFze+Qfjwin/g6wEVsMYSzoZu6yKqUjvJeWMR1MeIXR77DpUNK4QCHil98ruznqs/kyR+HwDimQ11KW4gjEXUpYVMkrG1lnAkMh8nyGJSwkoAr0cMATbhd5WpBcQgE/TdYym4E3i3RnjVMp7iDkGq9S/cCR+pDHOzqbTJaQIdolCjqA/xziOqEO9N4GMwY5a3qlWvM/0XmX+rEJfmvE2Vg9N0ktjLEkDjrEEIQe9rFzWuIO7LB2rYKpWS+mqubFZSleMtU1JonFL6aGSa7yYR+qCcQzlsIvdNMEapljKIdZ3ryq0nqn89il7lrOulIPlqJjiiCk7OUUpxZHX36mWxRR59Z1/UJdBR0Dx7IO86cIaqbE1Z2rOIzUEqekEKubZ2JFuypyzuH4TOF1CjsC9U8wt5b3+AUNUsCW9lygTzZBkoo+q6XdTi6vLgATMVk1lz665oe0R+L4YLAhT7QSK9xLoGI+x86450wwEUrmQy2e3L0icWQFD4mXzKQL3V0CQuOV8isBhtnMx63hvwvRmWw1/5oi8svm9JOGi+T2wp4lr43WlR9BVEBhGYxzjRdUYZUhEkUUaeBRRvEBAyGdNbV2fIDBcPIJkaaDTC5zcfvqcsfpCeu8l2d3SWSylnRWm+94+ReLf8BgSI9ZLX0zvabqC9JNjZOyRNxWyAWXnrKkT0yfoDRFTr4mmSLbnfAKUuKQnPMJS8poUc6Ye8256U+EcDEKJiyWkDJraCD5DOvfwEjgbfYZkfe0zpDPcYzjGIT0eA/c3PwShCem9oCzTkpGbTwsCJnyCt4PnaUHh4PKIosGVLotmSD5dMj6ypNNL52w+DYNEosTzkOkV02jtgCASnnlsQGfxu3gyLdwfC9hZY9M7IEC6Dw8bnzT0SYOiMZ/O5iueyecPMVHU1N/5UoEJtqgDcoWd8qImdP6BmebAMSsa2ZogEU3epl3JNJKhSxApSBCE4tJjmC8VILy9l4nP92+RSabHkII8BG5yjyFQK/rAuvchOBsVkKqDiJg1npZdjmQnPiRB40uWPiEt7wh0csjK/YNayWblGE1eJ6fg7mxujIY0+NiL0hb0hkU1O2gcCNJDK+fk/YwPkWkXsoQh/D3E4YK00/AhkaUhSeLj7mENGTv1x0gSs3KMlNubFWN/JzlV40MuvSz9n1zedH9tjCqxZkOSRHo6+N1LEpKoGfAFFF1RHnAGOMY96xNGBGPVZxRLxucLNGNXE13WS4CkTO9h7LD0KbIYY58ji3g=
*/