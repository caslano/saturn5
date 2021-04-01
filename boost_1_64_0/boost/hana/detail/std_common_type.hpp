/*!
@file
Defines a SFINAE-friendly version of `std::common_type`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::common_type`, except it is SFINAE-friendly and
    //! does not support custom specializations.
    template <typename T, typename U, typename = void>
    struct std_common_type { };

    template <typename T, typename U>
    struct std_common_type<T, U, decltype((void)(
        true ? std::declval<T>() : std::declval<U>()
    ))> {
        using type = typename detail::decay<
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

/* std_common_type.hpp
uBuftIMLbSQGq5hOs3QwKQICK+iWMXd0VkWsmxUTeLWheXS9zaHDiZq6fVwUoU+Esn++sycZCVJqp15npCRXSG+Bu0ZmC9BhF8nPq++JjLJeFfxpewem0/DRHePeNmvlYmPbtoe7KSSNVXsuUVDTVhT9F5A1RVMnQjB4sW4v+PQQpzKxEFRBP9ogyEqJgYlmiEOjSyAOYPLIDAqeTuMGPexz8O8YwVtAU/1/m8raNyQzhm+MZmd2fUC6YxWooFsSivuMdJRod36dTtJMyuNm9+8DjtWlAAW2320gj584gkLQyy6Ao1O/naXp2kohNa6jorRXYBaPSqkQtr0sXoN/95nX/dyHLmG9dIuGVr1TiVBJfDTff9MLwNe922pE/JoXnso1SGJ2pW4rfSmTEzSPmHn7gOF0kPTAVOZBQ/uw0YGn9fY6fsurvA068p4Cu04Zmihm62qtHmXzqxQh+417bPjSUYnzXGubLRgtUbQzxwSb883AT7mUqPFd5xOD/Jg8kRNhlZ43E8vx//EhIFxA8d4Sa6g9B570wzNH1L1m24aAwVpGuBzAA6FCGg==
*/