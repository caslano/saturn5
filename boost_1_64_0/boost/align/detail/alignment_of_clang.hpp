/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
cW9h6L2zqhVtAVYfgSxj6/bt8t1lCtjrLU6VOqrK5Hrs1M88EDsArAjR5QswkXCe6GBept38r77FCHdoy9BFdVS4wb4zJ80U7FCvKHx/Flqzt6pIXaq2Bj7u37u1hQgbyTZp1+JV7Lk7ZUMI34zpSstIUceqLjXTOkrYYVj44I442ErYT05RGiWB9XPPgFaCjxuxzLH0+hSmvNhM7zamyuoXzQnZAodZ9sO5uxLDFHBUBhPTWNQmYyD38Hq2A9MJcVjPTWqEA1aW+ObxhjmZR/dWFcqIPOGYqTdyrvebV9woQZxk1lz64x4Yhfgl1B7acH19uQJRVtBKYA1KaPFhK7cE7qItRNouegVB3P1JLES2o3TEFozBCKnBynY9pUtA1HscW70rfLoROoj4mXiQC8GdV8bKcytWVhfrIlJ6kHZT5ShnTT9p9JM2Ta+KLc5iQHs4CkkHRzdU3+kIrgwDS+OCAr00hMN0n6WiVLLFBmzzC5IlLmVf9724c1ftzGDoZ//PC4HuCiLf4Fztn9EVJVxz4KETvCVTlK0LPina4nco9v+fN4atq+B8wQ==
*/