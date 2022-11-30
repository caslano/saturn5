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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_DISPATCH_IF_HPP

/* dispatch_if.hpp
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
*/