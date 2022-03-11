/*
@file
Defines `boost::hana::experimental::print`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_PRINTABLE_HPP
#define BOOST_HANA_EXPERIMENTAL_PRINTABLE_HPP

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/intersperse.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/tuple.hpp>

// models for different containers
#include <boost/hana/fwd/map.hpp>
#include <boost/hana/fwd/optional.hpp>
#include <boost/hana/fwd/set.hpp>
#include <boost/hana/fwd/string.hpp>
#include <boost/hana/fwd/type.hpp>

#include <boost/core/demangle.hpp>

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <typeinfo>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace experimental {
    template <typename T>
    struct Printable;

    //! @cond
    template <typename T, typename = void>
    struct print_impl : print_impl<T, hana::when<true>> { };

    template <typename T, bool condition>
    struct print_impl<T, hana::when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
    //! @endcond

    //! @ingroup group-experimental
    //! Returns a string representation of the given object.
    //!
    //! This function is defined for most containers provided by Hana, and
    //! also for objects that define an `operator<<` that can be used with
    //! a `std::basic_ostream`. It can recursively print containers within
    //! containers, but do not expect any kind of proper indentation.
    //!
    //! This function requires (the rest of) Boost to be available on the
    //! system. It also requires RTTI to be enabled.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto print = [](auto const& x) -> std::string {
        return tag-dispatched;
    };
#else
    struct print_t {
        template <typename T>
        std::string operator()(T const& t) const {
            using Tag = typename hana::tag_of<T>::type;
            using Print = BOOST_HANA_DISPATCH_IF(print_impl<Tag>,
                hana::experimental::Printable<Tag>::value
            );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::experimental::Printable<Tag>::value,
            "hana::experimental::print(t) requires 't' to be Printable");
        #endif

            return Print::apply(t);
        }
    };

    constexpr print_t print{};
#endif

    // Define the `Printable` concept
    template <typename T>
    struct Printable {
        using Tag = typename hana::tag_of<T>::type;
        static constexpr bool value = !hana::is_default<print_impl<Tag>>::value;
    };

    namespace print_detail {
        inline std::string strip_type_junk(std::string const& str) {
            return std::regex_replace(str, std::regex("(?:struct )?([a-z_]+::)*([a-z_]*)_t<((?:struct )?[a-z:<>_]*)>"), "$2<$3>");
        }
    }

    // model for Sequences
    template <typename S>
    struct print_impl<S, hana::when<hana::Sequence<S>::value>> {
        template <typename Xs>
        static std::string apply(Xs const& xs) {
            std::string result = "(";
            auto comma_separated = hana::intersperse(xs, ", ");
            hana::for_each(comma_separated, [&result](auto const& x) {
                result += hana::experimental::print(x);
            });
            result += ")";
            return result;
        }
    };

    // model for OutputStreamable types
    //! @cond
    template <typename S>
    struct print_impl<S, hana::when_valid<decltype(
        std::declval<std::ostringstream&>() << std::declval<S const&>()
    )>> {
        template <typename T>
        static std::string apply(T const& t) {
            std::ostringstream os;
            os << t;
            return os.str();
        }
    };
    //! @endcond

    // model for hana::optional
    template <>
    struct print_impl<hana::optional_tag> {
        template <typename O>
        static std::string apply(O const& optional) {
            return hana::maybe("nothing",
                [](auto const& x) {
                    return "just(" + hana::experimental::print(x) + ")";
                }, optional);
        }
    };

    // model for hana::maps
    template <>
    struct print_impl<hana::map_tag> {
        template <typename M>
        static std::string apply(M const& map) {
            std::string result = "{";
            auto pairs = hana::transform(hana::to_tuple(map),
                [](auto const& pair) {
                    return hana::experimental::print(hana::first(pair))
                        + " => "
                        + hana::experimental::print(hana::second(pair));
                });
            auto comma_separated = hana::intersperse(pairs, ", ");
            hana::for_each(comma_separated, [&result](auto const& element) {
                result += element;
            });
            result += "}";
            return result;
        }
    };

    // model for hana::metafunctions
    template <template <typename ...> class F>
    struct print_impl<hana::metafunction_t<F>> {
        template <typename T>
        static std::string apply(T const&) {
            return print_detail::strip_type_junk(boost::core::demangle(typeid(T).name()));
        }
    };

    // model for hana::metafunction_classes
    template <typename F>
    struct print_impl<hana::metafunction_class_t<F>> {
        template <typename T>
        static std::string apply(T const&) {
            return print_detail::strip_type_junk(boost::core::demangle(typeid(T).name()));
        }
    };

    // model for Constants holding a `Printable`
    template <typename C>
    struct print_impl<C, hana::when<
        hana::Constant<C>::value &&
        Printable<typename C::value_type>::value
    >> {
        template <typename T>
        static std::string apply(T const&) {
            constexpr auto value = hana::value<T>();
            return hana::experimental::print(value);
        }
    };

    // model for Products
    template <typename P>
    struct print_impl<P, hana::when<hana::Product<P>::value>> {
        template <typename T>
        static std::string apply(T const& t) {
            return '(' + hana::experimental::print(hana::first(t))
                    + ", "
                    + hana::experimental::print(hana::second(t)) + ')';
        }
    };

    // model for hana::strings
    template <>
    struct print_impl<hana::string_tag> {
        template <typename S>
        static std::string apply(S const& s) {
            return '"' + std::string{hana::to<char const*>(s)} + '"';
        }
    };

    // model for hana::sets
    template <>
    struct print_impl<hana::set_tag> {
        template <typename S>
        static std::string apply(S const& set) {
            std::string result = "{";
            auto as_tuple = hana::transform(hana::to_tuple(set),
                                hana::experimental::print);
            auto comma_separated = hana::intersperse(as_tuple, ", ");
            hana::for_each(comma_separated, [&result](auto const& element) {
                result += element;
            });
            result += "}";
            return result;
        }
    };

    // model for hana::templates
    template <template <typename ...> class F>
    struct print_impl<template_t<F>> {
        template <typename T>
        static std::string apply(T const&) {
            return print_detail::strip_type_junk(boost::core::demangle(typeid(T).name()));
        }
    };

    // model for hana::types
    template <>
    struct print_impl<hana::type_tag> {
        template <typename T>
        static std::string apply(T const&) {
            using Type = typename T::type;
            return "type<" + boost::core::demangle(typeid(Type).name()) + '>';
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_PRINTABLE_HPP

/* printable.hpp
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
*/