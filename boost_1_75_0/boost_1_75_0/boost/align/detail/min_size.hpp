/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MIN_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MIN_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct min_size
    : integral_constant<std::size_t, (A < B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* min_size.hpp
0ebPQApJ6tpqy7f1DoJr9KLCAXfj4XcP4AcNilldsBqvQ6iLILJTlMOgqYtiY+lfHbDqMgavyP6MCe2sI5RzhSNUPraaR7zGIT4BAFpQh7iRRzycDpo3GsWdZ5fR9w0CS9oHzazCa10FrMEjZZl4SbYllEz9SS4Q8FYyk7OSGruVdEDCHJAemaS+mBwjox8NxGqnmF4CV1RW7uChKc/Dk8y6uz6TiZXQIvY1n4JT2En1v6z7zFBZq/OgrmAVXeFUp6VtIupaWX+fRfqOdUjZhkcs0iNnscyOdKEsyCdFntZ6J7Q/p679HwpBmEYBsCxEBsURXEokT3OFFN1/J7ZMDbriV2NFkDYslID66wIpFelMV+3grl472WABqg/LqsEpqP7yNIimKgu7cxe64Op/n8bpfTVVnMuhjEZbuXSt7stotJrd4mV99aWQtJsnzlWPzcKOA++vl6kk0NAOltpoO7WvopHGTq1NNAquo+bHUfvY83cQ8lmkc9eKYtPjStOT35PhJTafSK0TfmyFfTotscC+RtiAcxQnnmZfWoR4RZzt55LY0LAIlHCx/zDPRQ9JF1MEeAPzFIx8ECVfFtz0fbpw/jtAFg6TUMNkhkevDeeE5DAZ7XUav32FO9GHTXmK5ItbQIp0oR+Ya/CCPqRcAYCuvneM0ZtLvL2Ir7HHj/E4Xv29DuUSj5LTHYZ3fR38GA//pTs3F7QClPcO
*/