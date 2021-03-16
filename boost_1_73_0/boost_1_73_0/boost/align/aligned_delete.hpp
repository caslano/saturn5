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
4trsdWwsHZtK/momHg0G80mY5JVtp5nsQWOhepI9WaXTkHHeHewVck9PrpGzRXjv3NEA3i7Ukvjez55BQ60Mzh0t1jBieYfkO0Rx+mvX9t2uRu/Y84re0gVY2wJLzzKPm15lwhzbY1VV122xfUvssu817gRypDug3ufJgd6wDA1b1twuu7+2WiSJlwMF1FOHhCuJI7WiGesinWCsoHlFbjQ8BL/JhmMzLEizrKyvoFvJ1i5CqTo6T2FCSme2J9w=
*/