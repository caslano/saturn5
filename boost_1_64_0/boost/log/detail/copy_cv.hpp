/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   copy_cv.hpp
 * \author Andrey Semashev
 * \date   16.03.2014
 *
 * The header defines \c copy_cv type trait which copies const/volatile qualifiers from one type to another
 */

#ifndef BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The type trait copies top level const/volatile qualifiers from \c FromT to \c ToT
template< typename FromT, typename ToT >
struct copy_cv
{
    typedef ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const FromT, ToT >
{
    typedef const ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< volatile FromT, ToT >
{
    typedef volatile ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const volatile FromT, ToT >
{
    typedef const volatile ToT type;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

/* copy_cv.hpp
Urd3O2p6IW3bSAFySqHTnuq4tru/fP4/ef/3rpq/reb/64yusfb3bBkDkCTpSUQ2c9NZVa6et8uKchdneQ3IwbrSqqZ30y+7S3+0/lkbXfsa5SsCmOPfeM4k7qa+Yp81yhukraJYlIqQTYRN8bVzftlidlns9FQYz89xcKQKP1Rnt8TltuhWlOdo+9vtYY9Md+EqMLr5OCVqfw9XP94BssmEyhD0yff2roiQ0C4RHUPDeAvYMSwiNLRvRFhMZKiRVxfHuixxesw4u7CVpuKcrZ7rg8tP8kD8okw/0mbPY/Nd9U43aRbG9CDvK3zyuLK8mN0BlQV0fdofKheX5VLOZAzE82r/T+i8wPrNnTV5rYujbAggTFMct1Z691/B/hJNu4ZdPzRM6Q/F23xv+0ntH+Q+xjWLNbbd+nEQEofvuekv711Pq/0r3Te7uF/xJPYutfMHfh/sDnHNQZa6I8nnWcq2OYn+pSbWd9v/O7aca2yKAYxBqcIGy/Y02Y5zhXee2PS7z8TJQ/Zwid9plaZfuuG3uNlvqOH3fYXpl+bS11X7uBo5x/a2ETlnMs4jNAw/OQ/q/V/K4OYIl3LRbkkr7EQZ3FjVsgx6FxUJtByib54/DLCVwzjvcdX+J3le7uY6F9GUQ00cC+cWV+XqyhxhfdsRSucVVlaYY392Wyjv8eb+Bbb9J8t+o31gRlKTnBmv2KJMhAVwPTXOEbb7niPxU+lR424GLZR17Hu71PZx5rb9msH7o3IHGo0+yNccs2GB/XwVlhZWas6Veb18S4Ufojt3xKWte2ZevaD2D3KZ19DW7zcTArnfRMnjYRbiRg5HfiDsxkX2dMH83NIAy6DSdUvbjboOod7cdtNXvWemUvpCNOXPro/ROPt4sh5KP0623a4uajvE1Y184dKuriWTu3KtgtMpR11Stn5taa0ckQb8VBpsdfi5di7lliGhyBmSdxk+eada8sg9bbmQPNlf6eyizc8MfX7q8o6w+na9OGlXu0ztH+xKkTA9+6q2tZx5/O8m94npKkwl9wPeBbEgD/qei0Sxu0yFneXq4H3iIhdUevA5epG2LJt2TFb7M13p/O/nmqXSMZeDz0O8584D41MU1Xl8MYg2vEDOoVH+izu4lMtFwhEP8hP6a+zPWzI6VH/+OsNXVfhIjjcWGwz9SbRrdLL3Z1iep1LCzO9AteeSsObYyCojbLEqR9prsYS3jGGtnFehH+9oj9slYSXuOLlWfa3CDOZZLkzFEW+JI17FoS1rZp70VPfTTmY93U1th7CtjomrKK4sKTPz7AsV3wQ0OmjKm/S/qDCHkq9cQXTlS2xfq8L1442B41O+QvA7C6MTUtp2T+Gcmd/AJso9pUr85NzIvV/G48o5IKzKvyqX+FnChpn+Kj9s5XN1J5dyU6R8qnXgu0P7s6p8vey/fE6r8D8Gl7js5cZ/mSSstdxsvUxmVgReJjMrtl4m56swg/RlUsXReplcofaH+y1fh6v9Y7davmZU6MtXYhvLF3nUsny5/nz5MvosVm+HPosbB3r9O66JOSWv9wejv70v/c6EkgMK/PdlvN/B6z/qh9Sdp32/5OSV+89K3hB5+rEu10Uknj6LEzxnXpv07Z3rE+Z98NTSh/oH3/fxo+r7qH/5i873RVyStc+VI2dGZoyO/vf0fcSp/Fl63SWvffxkWtpxT06tLlx27QaeFZR/ZbdTvztuysWzTuw//bLY9Oh1/+2+EqlQqm1hI+yNbELSzHYY1baj9oUifRCXtPN7uQ9MhOMgesozRfSKRa8DUil6u4ne7nAUHA4zZHuCbE+Ce8ApcE84HY6Ec+AomAP3ggVwNCyEw2CRbG+CW8x3btU=
*/