/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
4limOKFMy+pkevdPtn2s0zwGj/9iOW4mxPkPP4qu/IHLJ/lLXhrWO1ge8noY60U86qxqYuplPD2K75yMf9EFLust8P4yDxWPMlHszTuhSo8f32N2zXnmdQckf3lX7G1i43t692JRynv3oJWjeWm2JtuXkMjLya7/MLi+ol1sZ7FO3A7XIO16FK69tYtzbPJ9RBf2X9rF1bPPtIsThk+1azz+309/wdbaR7tOgWuH9j3DubhdfV/t2xqyObDS9B8=
*/