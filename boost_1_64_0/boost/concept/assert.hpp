// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_ASSERT_DWA2006430_HPP
# define BOOST_CONCEPT_ASSERT_DWA2006430_HPP

# include <boost/config.hpp>
# include <boost/config/workaround.hpp>

// The old protocol used a constraints() member function in concept
// checking classes.  If the compiler supports SFINAE, we can detect
// that function and seamlessly support the old concept checking
// classes.  In this release, backward compatibility with the old
// concept checking classes is enabled by default, where available.
// The old protocol is deprecated, though, and backward compatibility
// will no longer be the default in the next release.

# if !defined(BOOST_NO_OLD_CONCEPT_SUPPORT)                                         \
    && !defined(BOOST_NO_SFINAE)                                                    \
                                                                                    \
    && !(BOOST_WORKAROUND(__GNUC__, == 3) && BOOST_WORKAROUND(__GNUC_MINOR__, < 4))

// Note: gcc-2.96 through 3.3.x have some SFINAE, but no ability to
// check for the presence of particularmember functions.

#  define BOOST_OLD_CONCEPT_SUPPORT

# endif

# ifdef BOOST_MSVC
#  include <boost/concept/detail/msvc.hpp>
# elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  include <boost/concept/detail/borland.hpp>
# else 
#  include <boost/concept/detail/general.hpp>
# endif

  // Usage, in class or function context:
  //
  //     BOOST_CONCEPT_ASSERT((UnaryFunctionConcept<F,bool,int>));
  //
# define BOOST_CONCEPT_ASSERT(ModelInParens) \
    BOOST_CONCEPT_ASSERT_FN(void(*)ModelInParens)

#endif // BOOST_CONCEPT_ASSERT_DWA2006430_HPP

/* assert.hpp
Y5a5p/MmyeH7RWrXB/M5G+/bNWI/5/oBwrutvPR+CmwpfvDm4VxjMwL8I48N55OpsFYa8iLtnIfym40M+HGx5nd57PpR7lQPPlYP9h/egbFW9Q9g/hYDQzvEm3YSG76ni3FzrIunIsM86OURcw5SJmEd5W4knDzn86Xj3xs15nZBnZRFVBfCj/s08ObPmXPArMzzOJSEwLN81r5ipns8j/I4cctMkFlV6x7WDZP7dJn5Yeo5udC2kJZ/V8YN4qBwaW6pbTY591csD6FT+7nr+YIW4i0/fa+Z3ELkbuanke8p8oz33CfrMxVkcG/QlDlV+n7hOW4qYCOpBQR8Npl8rxRJ7YR+WD/wHnxTvslRVr4qqkM3j4Qc1zHBlNxBWzzYeW5EtqC0r2jYz412cMEz3hX8H2nXAR1HT4TPEEjopoceIPTmnOPg0KLtRbsrkQQIPOBix5fYxPEdtgN/qKF3CDwevYTe4afzqKZ3CD300PsjtEcvmj3tnEa36ziPH+wX73wzkkbSqM9cBnHknIic+1+2HoNvPao9002AW1gqAcr4mXVz6u9GmyuYz8NU+iGvFkrlkGe/CzytefBtVJ7yKBQOMqkxWd/7Xr3E8m2yRtMTKU883w+QFXYFNMtqld4ZKz2ZwPtdniPTymh6+N7Z5M2Y73giiwuGk3md2GqVv9Y/SP4Kz3V8GSfMmOFj/qp9s3GTx01ZzCNXRgKZYGqxsKJG+u6h46tDz5H/xXffJn/OijAppCNzZDeq4Hi1ZmUkTYcVPhciz0KTCRLWjItVXg8QvpglqpPLxE1tPt2GqnQxr5eY/IIpztThRciIJR5wLVd5fTJJ02OxdJLEVZU+cpWCrstPW3xFIIMwyFw2cjWJ8r2P8LksClUzS0XI7KWY5SPpjKXTXKYy5LnPyBIN2ZDvlxafH0VJ7Lohs5ZuIz5n/mnycRYmCffSzGeNx9qlBOyH2wh/yHiRp0VQpDa/wbod2w/hdZiXiSiMXWatJtGnNPqRMfly5nvSTbJIMGO01TyGHxkrrTjJRVj4KbOWkZrRQT8yhM9nws94kLoZG106oq8O9EtEeBPmuXGSZX7MGo4H7Lp5H+GPmV9Eqed4Kas9NkB29El0lvDnTDiFcCMesnWOE6gve9jspLYrC/LCSQQbrmjo/v34v2h7Sn1HiFjkrPHqg+UbxuQXLAuiQGTYnIimF6o0mZWml4MTGjQINcMSTfMgTTNxeeonvm+wo8HtoN9JkqbDXNfL4iwweUy/FAtVe3oy4YuY7wsB/qZY7XEx1e3rCW/MYp7ywM99Vj+VHJkDfYaWMxJOHOW+y8gOzIBrqSrnWaucRRAmYZoU8LC8NNT6iKDal0RfRIQvZCJLQxHmecmn81u519JaYtiG/k3LGaVh4eSpa/Ie680dX+ySvo62cMLkh+tRaRxGfshmFuG5mvKfBg2/i+5S0BdZTNJNWZ7x0I9VujPLR44f6y6B57SV8t2+fo9/bBYLXpV7nsjwmR9nflQkOVPjmWa1x+Au2hrCGzAvF3nEvbz0ITazpPhXZ452V1QulvrHdbHR1lg6444MReE5lLfMfS3/+wh/xMLESZMwFAwqSRmYVeg1ePS2gMoLq3ZC+AtWpFGUZyJi5cxhCnNRamABZpqg0GEl4NznP8S2C9WRE1V94AILnTDYb/PHTR7BXFcGnhd6bG6lpxM83Du+hEn1qzJv+w8ts4i49ItM23ZQ1kq33IagzhPmqvbCCH/GZJonYeZ66DML/ceNCHHCyvYQGZwJ7rhRErkoA1vcQul/QX1RQw62eay/k0ROyArV2/xIxCiHFmWk7Z+2yuJLESZZ5jHt2LTsM2UbGAxYSiIOOZU=
*/