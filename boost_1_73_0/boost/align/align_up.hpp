/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_UP_HPP
#define BOOST_ALIGN_ALIGN_UP_HPP

#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_up(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T((value + (T(alignment) - 1)) & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
pfbCNbIBtBfe4aCx8wcCvAZjhWJbqGsEuOa12BrK0VlVolhMFuxqudhCkgG45wAUSY1pL7xLOaDcHt5BTqMzY1uoksSfeD2LKWK/dEEqKEZf2a6fhn90G4Xk9c5yTR0BIpeFdncK52mmbVq6BebM6UkJclPbVSMbMS/eCRCeFm6W8xkluSlY1zkrh99KGR60ckS3TZO1ujtD6TGQKugPCvuNqAgC/WZqdFs1F/MsOQkLC85g
*/