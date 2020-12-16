/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_discrete_interval
{ 
    typedef is_discrete_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_discrete_interval.hpp
8/vKBZDJ7w9lesrzFUTP7w/H+1UIj0Ro4/fVCGl+H0HYyu8phEMIAS7jjXincn0Az3eyfHp/F8IRfn83wpv5/SaEt/D7e5j3g3i+l3np/X0IR/j9KMKb+f39CG/h928jfBPh6wjfQfgWwlmE9mcvD25E2I/Qh7ATIY1wPUIJ4RDCCYTDz1kePIswhfcbEY4hnEZIAmYgHEW4E+E2wFbjeTPCBYSfIN6F5ymElucuD55HPI73VoQbEM4h7EAoIDQQ9iEEQbcSIfB/8Jtrf5rCcNnUoZTc72i0Bh815kEWIbS9dVnwyQ8LBF/FsCUIR162LPjhZYHgPGbft395cIEi7uiLlgdVuScRJ7kCW4RwFrA1Gz3YCoQ7NFgbws311mBxp5fWbUirheV2IVygtJTfohcvD3523MtvC0IrYDtDnoz485YH5ws9QjvwL1dk/PGlyyhNGzaPZXSD5huXB9y0FyEkATvb7aQ1n+tmp5bWgedxfjk+9eLmujmA+O4U0lJoDgN27MGejD8q+W1FOEoylN8JxNu2eFJbEM4ARnUpMrqe31zm2zUZ5xE/+UQvHy0UDi4Pfq7Pk3GtJqMV+ENKHa1C/FebAjZsPsM6AaN8zJe8ajLiB5vzkUZ8Xaw5HwXAkDfOB2AvaJZxLfAHFPpDiN+vI2DD5jHsCMHWOLD5DDvKdCKrD3IXKHJPaHk7izh0y4W1INwO2N2uYhjz3amVYQnCPxj2Ks5TkOAvadaVIy+ALKWdjZf46iXrD9cvaFo6GcJpxQGjtFS9SwO2t43TZ/k7tfSNA176KxCmXqLpKuLP6weEYSt8bIbhYzNW+diMIwe8ftGGcL1W1qOId1/Z3AePAyb9cr60EZfVrdMXShviHeE0lUH5HYM9IR29m9qGoPm30t/ykKHq1x0v+f+w8f8PP/JPZ1L9m4ai6a0jCQdGGybu0XnXb0U7qH28lSIwrNcIJHJiiZE0b6DWzd28JJC/jcHLfvVPOgrf8FBiJLFF+Iiqaifnxfl8Psd1KSIHQvqHeocp3hi1OEGev+Iwp9/f0xC+rQnn9If84UZZeUlcoU0le56Qpt0yFS9/WUSF9eyF91nlGx5KURVP0opgzSjvSXtx/qNbHj3XpbeWkM+fVRgfZfH4tg1vTsS5Hlj2eJU8sF7c+XOWAHGcZ/NKO8IvBY1IyfcOcEY4T7WcjULRcv7YLe+TYUOO40q7NzcV69vQpoEElVCprzz9sR/5/iQ/kcPnG43m+rS8d02qUmdxXN0r7a+6p4SmJ5rqjxGhfFtDX5rJtyH2kytZ6mJkgJshUOI/U+iVIzGyrT+WGBiOXXzOlrNq9j+ZXEmdr+UjxYwNrvDfcBTZ9scwtNQLZyyucw1Hy3QdZt8ZvhcwgTsnsop5Wv8RzMkC/QHHTB5fxdE116wZKg4M1nSYuKFFNsPlEJNHX6br4pm+mPfo4b23zMwE6tuDcYeW0uhwLpEHFwXI4A/ohZ1SS/4d8YVGo4ZlZsUME8zZ7zDMOmccL9U6Lm43SFknbGU1+I/gNeNJuWfEU0rkoUdRGF5GaQlC5aei2FjlXLCS3KiJzVBTSSAgNNWGYRfIkEIK3FAO31mUO3gbixWPz2UwIC/LMO7kRkP0GTDHtWPghI9nSw1KV/2LMa4wctQgHQsUhmdwOA2mrYI5l7Vl0N/hZHXiM8devux6A9wPh9rUKEDDdhq1jzOueDLc6QtwRdT4knoPRlnYC3+srY8Aq7hGtWpUSwwV34X8/R91r1/5i9yGOxbRAQD7rwjNcX3m9nU0utLZ2QUcorHlGiPrfUx5NRGHOLmli4VuAHdNNArXGFfmly5eujgQuNIy8H9fOp28GsktXXw=
*/