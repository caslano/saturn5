/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_DELETE_HPP
#define BOOST_ALIGN_ALIGNED_DELETE_HPP

#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_delete_forward.hpp>

namespace boost {
namespace alignment {

struct aligned_delete {
    template<class T>
    void operator()(T* ptr) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(ptr->~T())) {
        if (ptr) {
            ptr->~T();
            boost::alignment::aligned_free(ptr);
        }
    }
};

} /* alignment */
} /* boost */

#endif

/* aligned_delete.hpp
ban3zpufwqp5XpQzZh+Q+EvcEJkUSwQnRc7j+eCSvHpwzQVbTjYy1iq+nZS3GwQv4+1b6T2E/jkxtT8UIfVq4ZkSvLeMp4pqyN+DMtqvce2NXURr39iHTIuTVJKGtcI6XFyvZNILMGCCIFvNc6XhMuG8plBrh6Cck+8kVL7smNU4tzAx68DR8iJHAG19+Dsm0/Cum3ZiEINgk9E+xpLjDuE+QQAam1KlNI5Jm/vNUKrQoPRk
*/