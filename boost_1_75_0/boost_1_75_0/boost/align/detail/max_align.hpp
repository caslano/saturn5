/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP

#include <boost/align/detail/max_size.hpp>
#include <boost/align/alignment_of.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class A, class B>
struct max_align
    : max_size<alignment_of<A>::value, alignment_of<B>::value> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_align.hpp
AzHTwzgf7gPjbHOiQqWkCzPXk5krjUbL8JswGlQzlJV/MlSCBXATVtQVYElWswmYmCQkgL3F+ohoFI2rAFTnG40Gc+lanU9UNArEWrskOrvWCSkhCUMUy47RUTwYsWNsTpkbRsgUy1QSn8UBi/Uu/K2nLvLEm0z6Zvj2dQr+1vUu/G1TckOopFZ+HK9Dk3LaeLaGKb/9udVQpDBYFa6hMsMU6AUtQLUeMVqJZucsMJJoI14pjt2p4wymcSt+NrpFTC4aDA3RoZVga0O8IWIKw47eEAivIRY0WO0QiDTY9JBP0niCIe1wTlR2XMUDCUEz2iDEY+KKPQ83RAnt0Y1hqMwbi7DsGhjcMZKybIVOgR/6f1RLOpNDZXQGJnDOG5K2VhAgaNhHEKSgjLS32cEA45SLUXgyZyDNzXAUyXFwaXcNz0Gzjzlw/QcHnKgu2FNj56Hrxzyc3I21i7pXNUOPApSIb6LRi1v21rsBhGdQDYY3Mhr1PFjDtM0BHci+vySHctuXlFoaDypRKzKpKzTR+epq7P2iPbdwRCblCL3GjDp4eYlzA2USU5AHGSTND/LEFWh/4CEKplx5iAwPu84zCh3tCvMjXsa8wks5sThwcSZDwMFwuVINTJ/siU22t3+JXqJkbHK0j82rID9OyYQCGVbshxsCTuMtBEHkKUxW3y4SOeE3A0gJC8ZhsCnEQysCwqRzDG4jRGJrTMnY
*/