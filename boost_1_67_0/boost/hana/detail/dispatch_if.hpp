/*!
@file
Defines `BOOST_HANA_DISPATCH_IF`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_DISPATCH_IF_HPP
#define BOOST_HANA_DETAIL_DISPATCH_IF_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    struct deleted_implementation {
        template <typename ...T>
        static constexpr auto apply(T&& ...) = delete;
    };

    //! @ingroup group-details
    //! Dispatch to the given implementation method only when a condition is
    //! satisfied.
    //!
    //! If the condition is satisfied, this macro is equivalent to the type
    //! `IMPL`. Otherwise, it is equivalent to a type with a deleted static
    //! function named `apply`. When a tag-dispatching error happens, the
    //! condition should be false and the deleted static function `apply`
    //! will prevent the compiler from generating too much garbage.
    //!
    //! @note
    //! When `BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS` is defined, the
    //! condition is always ignored and this macro expands to the
    //! implementation only.
    //!
    //! @remark
    //! This must be implemented as a macro, because we don't want the
    //! condition to be evaluated at all when
    //! `BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS` is defined.
#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
    #define BOOST_HANA_DISPATCH_IF(IMPL, ...)                               \
        ::std::conditional_t<                                               \
            (__VA_ARGS__),                                                  \
            IMPL,                                                           \
            ::boost::hana::deleted_implementation                           \
        >                                                                   \
    /**/
#else
    #define BOOST_HANA_DISPATCH_IF(IMPL, ...) IMPL
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_DISPATCH_IF_HPP

/* dispatch_if.hpp
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
*/