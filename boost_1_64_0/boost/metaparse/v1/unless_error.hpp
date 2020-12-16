#ifndef BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP
#define BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T, class NotErrorCase>
      struct unless_error :
        boost::mpl::eval_if<typename is_error<T>::type, T, NotErrorCase>
      {};
    }
  }
}

#endif


/* unless_error.hpp
Z2dcg8kMvaIwEvY6O7+zsLEBnBG5geI2eBSK2Xgb9zU7r6OtC7T71+18rruzF+FvUribbNxh8Vb3borb4pHF1ZFlhiLt25TW61lrzJGnOyg+HbQRTRQD3FnaB9uaRJUBezfF7/BhMwmZDBr3GP3o9Q0FZfwRhc82c9DA/KWkrJDjc+ndXWoiDWDTf0rpH0b/pFhbrp9T3McQl9k26AVwFyCuOzWcg/sU4nBj69kg/uIANsnxv6T4yxEPeRzoR9pvKO1Ku6ZIzYWy/Y7irrbtZeIpDnOFa/VcAXOCG9Sc4PcUd6OJ87ewcnA3A45mFV4wR9lt4ajzGHyYy9xu4tDVMMcwd0W66KSwnGjYdUBKGv8Q/Rf8+/4Y1gGtLwq88eF5OIIr7hZWesFxXfZF8bCgMVus91sKHMy//l0oD9YmH43yPPKxKMY94VO+agrPJ6ui7rj3RwpTPsIhx1b4I1NnPf4SBV71Zs7R00fi/WvUeV8H41XI2YSo9ldpfu649g/gXhrVe2EYm/nn4P5n1LUNSufqfH55dL5no2JcP9flQflc2AlIw3gu3pPisujx/yWCwxqxA79/Hvg9BK/Le06IHfIqtwvgNCy3y2vgiUnTZyTOQR6k2/qOi6GcSA8r534MQ23t2z/6rMaEmGzDcd7FlTxfozjHVikF7CkMa8NE2wkvFul6vkJpjg1G37b+BwF3ZYmLa8jTuHDn35Fdl5eTRb0fKw+v98Ex8Bcwel1wapAOejp9mqSB/JrGoQ7/w2EOi7l3pT6A/YohIcdpV46hM/Q6GOm6GK+D8Vsj4Wt/eh1sFvImBd0tLh69/gecLp4j0I51ITICexf43D7Bc0MX3zti4XP0U/BXwx9F8OgnoI92xJrdHnUOLxJjeSc+OmsQMeCieOnbkcKu3V9NcE8dbMJue9Rwf0HdeW2W35dDm6CN5N+uae58a3HMnf9Q/TFnZZ7bnQ4FN7ksHO64WHj/JB7x3B59aomLE7AMly7xcS4juDswHpt5oGf2TXiN0taphP0skEz5vgWk/6i0J/dSzLZC0gviD/K2dvfgDZMAX5mNA06M+eU2bmgr/P9gXxVx1h8Wx1fYeHLzYOPZ38DymPAh6DWo17kRLuQXqHAeKwsrYjwnJH45fYZ4A7nhdLzd6My1s+od9NUxd19Bp68VbTkNbwnvJ98ARls2Qye0xKTtAliP9x9OiLn6tzXG5Zf95stCt1wrvq/B94WQGyNfHvbO2QeI9cWRSZ2RzMWVmjcR/GiP/X9sN9927aMMtr9s63L1jsL0kD10U78K7I8vxp3jDVIWxnj+ItAra6BX1kAPbIpxeyDspF8MPUF1yO1JVAtbMhFz9Q/sJbQfn+fpQPt9VPD6LPF9Ab55fcT/aTuiB3g+JPK+D9+QS9gHYo0YcGeKPPeK73PxDTkkOWadru2+gZgj76R3XHnexuMspUN/qjWbDOOwMqvfFB8KcIg+Q2kOH7ajfl8V9fiO+L5IfN+Eb9Ckulnesv4lmu8BvstFvqvE983i+1bxfRu+IV+E27XhzoVNYeJnGg7i/jXxNRe263YC5yfE9yXi+wrxvUt8f1d8t6k7BZ9Q8n0+6tkl5zKA+6QDS2v5gD0BsOa7VXyvE98bxPdJ4vu0qFjPBJ1P0e/T9NtFv8/Q72L6XRJzfYReyjKCPG7ZLkfZegStlPjuj4o1SuD4HP2uoN+VDq4S7/PAtU3kH5Z2BfJ/gX5XB3khh9fkbBa+b0awltdfUnXoUn3lupjLF8Nnw1/DV8NPw0fin8OXLyucJyicX4m5dTb8MXwhfjh1/lrMrZupO9XZqdtNMfd+3S4eC527nS0L3TmgrruB13fxbgXPH4Q=
*/