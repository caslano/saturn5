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
wVpgnldh/sC8YD4wP1gALAgWAguDRcCiYDGwOFgCLAmWAkuDZcCyYDmwPFgBrAhWAiuDVcCqYDWwOlgDrAnWAvNMh/kD84L5wPxgAbAgWAgsDBYBi4LFwOJgCbAkWAosDZYBy4LlwPJgBbAiWAmsDFYBq4LVwOpgDbAmWAvM8xrMH5gXzAfmBwuABcFCYGGwCFgULAYWB0uAJcFSYGmwDFgWLAeWByuAFcFKYGWwClgVrAZWB2uANcFaYJ7XYf7AvGA+MD9YACwIFgILg0XAomAxsDhYAiwJlgJLg2XAsmA5sDxYAawIVgIrg1XAqmA1sDpYA6wJ1gLzvAHzB+YF84H5wQJgQbAQWBgsAhYFi4HFwRJgSbAUWBosA5YFy4HlwQpgRbASWBmsAlYFq4HVwRpgTbBWe5ONwvyBecF8YH6wAFgQLAQWBouARcFiYHGwBFgSLAWWBsuAZcFyYHmwAlgRrARWBquAVcFqYHWwBlgTrAXmeRPmD8wL5gPzgwXAgmAhsDBYBCwKFgOLgyXAkmApsDRYBiwLlgPLgxXAimAlsDJYBawKVgOrgzXAmmAtMM9bMH9gXjAfmB8sABYEC4GFwSJgUbAYWBwsAZYES4GlwTJgWbAcWB6sAFYEK4GVwSpgVbAaWB2sAdYEa4F53ob5A/OC+cD8YAGwIFgILAwWAYuCxcDiYAmwJFgKLA2WAcuC5cDyYAWwIlgJrAxWAauC1cDqYA2wJlgLzPMOzB+YF8wH5gcLgAXBQmBhsAhYFCwGFgdLgCXBUmBpsAxYFiwHlgcrgBXBSmBlsApYFawGVgdrgDXBWmCed2H+wLxgPjC/Mfk3zbZ0LKDiEo4FwUJgYbAIWBQsBhYHS4AlwVJgabAMWBYsB5YHK4AVwUpgZbAKWBWsBlYHa4A1wVpgnvfaWweYF8wH5gcLgAXBQmBhsAhYFCwGFgdLgCXBUmBpsAxYFiwHlgcrgBXBSmBlsApYFawGVgdrgDXBWmCe92H+wLxgPjA/WAAsCBYCC4NFwKJgMbA4WAIsCZYCS4NlwLJgObA8WAGsCFYCK4NVwKpgNbA6WAOsCdZqb7IZmD8wL5gPzA8WAAuChcDCYBGwKFgMLA6WAEuCpcDSYBmwLFgOLA9WACuClcDKYBWwKlgNrA7WAGuCtcA8H8D8gXnBfGB+sABYECwEFgaLgEXBYmBxsARYEiwFlgbLgGXBcmB5sAJYEawEVgargFXBamB1sAZYE6wF5vkQ5g/MC+YD84MFwIJgIbAwWETMfC9oC8eiYgP+jvP/L+5UsPFifmXaHhYbqEzbh2L9ten7g/X6fbSYp58ybYPEeivTtpOYV5m2/cT6KtOWEOtSpm202LLKtF0kps+ubZJYpzY9m7DPCuxlhlgfZdrmiOlaa+uc0b6eA8X0etq2FtO11haBuGFiep/aRsBeMhB3o45zexDsdTFda22fiOme0DYPbNmP29c6IObXpmsm5lOmLS7WrU33oJjei7arxezZ3R4EexHW+1xM3622nyGn9xO1T7fPxPTdaguJ6VnRNhjihorpe9A2UptbMzF9D9ruhfWmiule0jZdn92tp5iutbY/IGfvT9v30kZge2tz509Mn09bWkzXRVtOTJ9B28NiA5Rpe0+sR5m2+RDXXW+/l0Fi/bTps4MlxHRdtGXE9P1puwVylsRsn7lnB5sHe+n6rP3z7gAxfQ/atgc7WEyfQdtIWO98Md0v2sZD3O1iuq+1PSjWpUzbi2Afwl5mw/mW+lzdrdtnYJuK6fW0DRbT+9QW0znd+QMbK6bvT1sebKpYQJm2mWK6Ltr+EGv73PNFe+sv1qlM23pgW4jpmmnbQ0zPu7YjYS8=
*/