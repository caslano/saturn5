/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size == 0) {
        return 0;
    }
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* p;
    if (::posix_memalign(&p, alignment, size) != 0) {
        p = 0;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_macos.hpp
QusKXcDZa/woMEMrGvp8qJxehNmLE3oN5pCnsTC7LO0oeD6qOugtmoQVHKdlXBTxjro9OcxH8G+G7YdAKcItnrMvvRf3JSOKBM9SYIGQZH8PJcAMzL+saJuK7yMiot+jB0iPokskCxp1heDuu3xBq6O758KsPp2SmxC4kfidy87THTV54V121S1FovNH1BBbi2KGcYZ/zHaGqDWU+Uc7eJuxIun2dD5NWe6Pfyl3S+P2OY0+wklmZTPGBNvD87evzu2xbf/k8h3SeTDHtoL6Z1a5c+mKhgiIqvZcWw+n6nQPD+OCm19V0/lPa+XAB3anXNuWJSKdWaUhzcxPOBu0oopxr5aIUDg3jcqL2hSGp3Kkc5sk0ItDiJN94J1S4Baw+Vpr5qHiGVTKymlb913giqroVUE3RM0BlFtS6P3ign/y9hvYCx76tvWQC8+yGk9KGqBCZisgbo4DTTXrRVfEACUXs+4l0YTcCJrA5yuLPIUHCLwoLGVgeURYaKFcaMNg0aYLdduSmrFIIVaWaKAnqrwoblRJrRFSRSxzdAwSDxR0W7PqevSJKnAmjoUSAtHn/VNCauy1seo2Knx6EnCEeOCKWo/EIvhDck1MQ1afxUAtbizW4OtIIjtG94tDmO2USB4KRcQcK7XLdq1R
*/