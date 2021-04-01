/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)

*/
#ifndef BOOST_ALIGN_IS_ALIGNED_HPP
#define BOOST_ALIGN_IS_ALIGNED_HPP

#include <boost/align/detail/is_aligned.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, bool>::type
is_aligned(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return (value & (T(alignment) - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
lQA8/vJJiHLf3NMgullVC3b00+tej0TMNegfNQEYpRxmxal90uU1fhxEhL4D+wsTb9VE9Rpcl+C0zA2VpFwyiBTe+VIwHVREDNqco6KwYo0dzisCLf1NaAr4nfYcFirFAQX4CU4x2au1bQ89ri8B0fbdjqmJ1TCUyRaJEGPvATwojsDlYHRvSbxqnnKktX8m3TKGoey19lS/VvtGC+2edt8cS7SIpbW5/R9qL8eWCHObtCoqziSzCGeh3+Jee8C8Nl4EJ6u5IUKeU0axHPtrdGrdIGJ/KbxGE6wswIVHWeW110C+7n0wUrlyRvmavalzWX3LEWM5dgDT0v0Q3AtwzT+OIhoi5bQUrxxMjcu4IHm1EPH6RECtBrVbHXa4FUQDRt5jJfRKJR/Li2X2vl0DpgXWtTiUzevdB7pyBjtwoCsP+dbCJmkcaGgplx+sGZ30zFVEJE+kwuCcGFLt+e2gMCVAQCIeBeXllylIjaR3xsrE90g+paM1mzX9Ycz3eiK+8IA+/3fdKFujQSWV5h17hpWAeUATI0nxuRUJDRb5sRGnm4fVF5oXzBXxdg==
*/