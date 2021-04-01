//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
o3nyERKiEil8n4C22RKKtoWyC3fPWJgDblcObwyZldzUzQydG+1QU//1YZt7X0ZW+vFrtB/2j2TNA/vlAf99BL16feP/f23GdJjW6b54CNEeNUNkRHTv3dsJLDseyY/kFXTJv3UsrWHW9iY6YOsBcES1hRZBvVChn6ATp1G5mCSl1vWdMZAuJppRhPtJ3/BA+Aj5mzWc52sNe8jvspedtciLOmF1+DSwxsP/kQsCp8sJ/+h78xJ79rcqf1GllpumFn1H8yY37vRTR/WD+zlEItQ7cpclHj1yiJVCnOGSP0VUe68Sesw2kmE4MD7ots5uOTTvAqV+g9fM4qBsUa+adwRSFH3WWErqhk709Z7Ab1j1Ia0cPu6Q57Ki8/eDLcB5NtmOKzSaTPiQMF1dCht8vCoHSfr/crDeGZ9n0eR7IT9V3si0ouoXw6MC/PffOLmGD0ecdM5kTzgA603reOv52ksNm1f9mVjf30SH2LV1rQKh5Ak/0Om+ncdergaZGgiEMhkwIL5psLjsBdpuQwCufqMH9/6z6/o4M+joV0WEYEufGZfcFQ+l5nU20Q==
*/