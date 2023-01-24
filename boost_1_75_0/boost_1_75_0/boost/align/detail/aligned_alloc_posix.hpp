/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
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

/* aligned_alloc_posix.hpp
lpjXxc2TJKZvf8xQrohQ1rkH1YVuZoe0x1bhRpkzXKf+ukI0P3QDBNxnOT+9NztArVcX6+gWqzP+61832fm3vhNAfo656tpQ0EgTlQde6jjJe1Z4+4wxdy8zE5u5XlbLCNpUeF7yp5fzlZrJvx4WAeH8nkyvnjtbpWj4kz8BojaUtIwnBnkn9g89fx9ld39NgPToUJcinnwD9DdP21j0wstj0N57nTJo2J2O4l+XFKA8SeY2nsbwPhCCn1zGFKDn9M1WuVro+/653gp+aFWX0tzl3xO1+Eq6xBgjw/cNvp0ZuFCzogUIei7SoLn4ZLZo5uIulSxZTr1baMg0g7yZbo+JjqrVG6DPiK5vnqhY9DJl6m+QGVQafgWy6Ld4He30T5HMeAoy50mYfyrXxTHOjPt4l6Q6nHRhTA2Dv/fpxk2jU+Pfv9f49iAMqAg+83hbtAgRdheDeOTPdv9tngXyVGEGTN68DigZIJRzu9xeCJYH6ihUzA84BnvmA9bohGfvhbg/lu8/7Fiqh5TONDVNTZKEnLfKRHkwYqs+6Vc1SScX7bu2judWl5h95SPEDeAdkLvNTw1d7UDU+/+Gb+hogQR/9IdbvTs35HWn6S3fHP2t4AJOw/I8NhdJwFfurmqniNEvtsrKRxm0aAGbn2oPPJ+nsSrgXLfCEQKNBo1tvwvP250VWK3gZ78194+2688r6dWLqJcrnuZSZs9e
*/