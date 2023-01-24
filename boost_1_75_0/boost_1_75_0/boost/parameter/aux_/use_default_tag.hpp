// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_USE_DEFAULT_TAG_HPP
#define BOOST_PARAMETER_USE_DEFAULT_TAG_HPP

#include <boost/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct use_default_tag
    {
        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(use_default_tag(), {})

        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(
            use_default_tag(use_default_tag const&), {}
        )

        inline BOOST_CONSTEXPR use_default_tag operator()() const
        {
            return *this;
        }
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* use_default_tag.hpp
e+yZlfptTA8cvd+bFPstbjv9eWeziOV1vHkDrPW9SITF1lX7b8fej6wlg/dEm28zMJUsE7U/XRQT2PV61c3AeQgAb4I4n/bmDJ97zQbvsYs8reOAsv0SWdaWfeoefQBBfKg32PRBbig3ylfmpbSvHOUzriXlKXB4WAAz8bR/fFgAtfqYlgLzbgRdakPqx5pXWT1y/bsmxNxnONYk+NGyP+l7Sn0i7udaefraTGYYfGTsO9CEf4Fp5MIHHA+vF8BcAT3PUnkCEB78MAVrYeFrS1DX+/l7vZbLefHFSvhq9hpqJPyerj8OvtzVF5z6ZxQBCLhe8cGia8Yhn0BccxHP33rzIMuyd2fONggAb4sEuNo7KEL2Ri4wxIgQ5gA8qz8GiII3jvtlJFxuu1mZxTpwEf0/N4HA2AcA563scXQx63zgPK3sk4p+E/GjWn9YzjyAgkuDHAB91jtX9Xoj+tqJH6WtphQBDtymhz4B/hrRp3heohe4/5c78/H9Z3ce0/nTnQMmm5wnkhlCjP/NneUf1VeGfTbH3TWN6evLnU5Gq03uLrfWFE+9lkcj/yAZecvxoscZk5+IYp7BpSiSiezV63dzt/JKDlgOZxl6SrlznC1LNxAJnuZqJ4NUxvmriBCvQ5H7GTFP2xmrGdGZ8xCYFpbp44CnQEgsU1m+toyex4H27g8MHO7l1++W7tONOTLljkK+hlQuGCGh7ulW
*/