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


namespace boost { namespace hana { namespace experimental {
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

    BOOST_HANA_INLINE_VARIABLE constexpr print_t print{};
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_EXPERIMENTAL_PRINTABLE_HPP

/* printable.hpp
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
*/