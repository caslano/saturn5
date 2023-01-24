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
lSD/aKeDTu3Jxm5dGqq9oBzxVdUA7j0z5GgLcr42tMtzWPqrE8dhqRyvoltABAgBsyfbBlLBGS3lr8c90pmE73pDTw6vlHY7UWK0gpQop/bLW70hSCryXShq9tKiba0qrzsprwfjvO7X8rpfy+tOyutBLa87Y7zuDLBADa/7tbzu3MPCNbzu1/K683UWruF1v5bXnTuU9HFe92t53fmikj7O634trzuPKenjvO7X8rrzh0p4nNf9Wl531iv5x3ndGeN150ElcZzXnTFed77LAjW87ozxupPyejDG607K687nGFTldSfldefTDKoAGCzn0/K6k/K6X+X1YIzX/Sqv+1VeD8Z43X9fLPpwXvervO5XeT2o5fVgnNeDQ3m9pfoaYPQPgNENi8QiiTjTJOvtKr8ijwOThtDrT90J/hq/H0d26akpTH18LQEH2Tqt9vgJ9XEfpdMUKX1dTIHspArkSen4CqYKWE/A2NtwQIja8ZSQCw8I3Y//NvKpqEomUj0++D7qOqhOfm2i6uSzK1jvmIPnAhA1T9YabltLuW0/KgqtPCpmPItDQ7OtHaUNH2HI1W+gZrl6xfDe9QVasf/fDvW/Her/VYfC+cEND3akvKE3totFPbbjT8C8Vupail2qR9OlnsSblvYenIV4stcAB3Nbf6BXeBARymoMPYpzKKq+YLCwhn6uVz63rlfYsKKDFNVSyEqF9yoChKoq
*/