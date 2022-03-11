/*!
@file
Defines function-like equivalents to the standard `<type_traits>`, and also
to some utilities like `std::declval`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TRAITS_HPP
#define BOOST_HANA_TRAITS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/type.hpp>

#include <cstddef>
#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace traits {
    namespace detail {
        // We use this instead of hana::integral because we want to return
        // hana::integral_constants instead of std::integral_constants.
        template <template <typename ...> class F>
        struct hana_trait {
            template <typename ...T>
            constexpr auto operator()(T const& ...) const {
                using Result = typename F<typename T::type...>::type;
                return hana::integral_c<typename Result::value_type, Result::value>;
            }
        };
    }

    ///////////////////////
    // Type properties
    ///////////////////////
    // Primary type categories
    constexpr auto is_void = detail::hana_trait<std::is_void>{};
    constexpr auto is_null_pointer = detail::hana_trait<std::is_null_pointer>{};
    constexpr auto is_integral = detail::hana_trait<std::is_integral>{};
    constexpr auto is_floating_point = detail::hana_trait<std::is_floating_point>{};
    constexpr auto is_array = detail::hana_trait<std::is_array>{};
    constexpr auto is_enum = detail::hana_trait<std::is_enum>{};
    constexpr auto is_union = detail::hana_trait<std::is_union>{};
    constexpr auto is_class = detail::hana_trait<std::is_class>{};
    constexpr auto is_function = detail::hana_trait<std::is_function>{};
    constexpr auto is_pointer = detail::hana_trait<std::is_pointer>{};
    constexpr auto is_lvalue_reference = detail::hana_trait<std::is_lvalue_reference>{};
    constexpr auto is_rvalue_reference = detail::hana_trait<std::is_rvalue_reference>{};
    constexpr auto is_member_object_pointer = detail::hana_trait<std::is_member_object_pointer>{};
    constexpr auto is_member_function_pointer = detail::hana_trait<std::is_member_function_pointer>{};

    // Composite type categories
    constexpr auto is_fundamental = detail::hana_trait<std::is_fundamental>{};
    constexpr auto is_arithmetic = detail::hana_trait<std::is_arithmetic>{};
    constexpr auto is_scalar = detail::hana_trait<std::is_scalar>{};
    constexpr auto is_object = detail::hana_trait<std::is_object>{};
    constexpr auto is_compound = detail::hana_trait<std::is_compound>{};
    constexpr auto is_reference = detail::hana_trait<std::is_reference>{};
    constexpr auto is_member_pointer = detail::hana_trait<std::is_member_pointer>{};

    // Type properties
    constexpr auto is_const = detail::hana_trait<std::is_const>{};
    constexpr auto is_volatile = detail::hana_trait<std::is_volatile>{};
    constexpr auto is_trivial = detail::hana_trait<std::is_trivial>{};
    constexpr auto is_trivially_copyable = detail::hana_trait<std::is_trivially_copyable>{};
    constexpr auto is_standard_layout = detail::hana_trait<std::is_standard_layout>{};
    constexpr auto is_pod = detail::hana_trait<std::is_pod>{};
    constexpr auto is_literal_type = detail::hana_trait<std::is_literal_type>{};
    constexpr auto is_empty = detail::hana_trait<std::is_empty>{};
    constexpr auto is_polymorphic = detail::hana_trait<std::is_polymorphic>{};
    constexpr auto is_abstract = detail::hana_trait<std::is_abstract>{};
    constexpr auto is_signed = detail::hana_trait<std::is_signed>{};
    constexpr auto is_unsigned = detail::hana_trait<std::is_unsigned>{};

    // Supported operations
    constexpr auto is_constructible = detail::hana_trait<std::is_constructible>{};
    constexpr auto is_trivially_constructible = detail::hana_trait<std::is_trivially_constructible>{};
    constexpr auto is_nothrow_constructible = detail::hana_trait<std::is_nothrow_constructible>{};

    constexpr auto is_default_constructible = detail::hana_trait<std::is_default_constructible>{};
    constexpr auto is_trivially_default_constructible = detail::hana_trait<std::is_trivially_default_constructible>{};
    constexpr auto is_nothrow_default_constructible = detail::hana_trait<std::is_nothrow_default_constructible>{};

    constexpr auto is_copy_constructible = detail::hana_trait<std::is_copy_constructible>{};
    constexpr auto is_trivially_copy_constructible = detail::hana_trait<std::is_trivially_copy_constructible>{};
    constexpr auto is_nothrow_copy_constructible = detail::hana_trait<std::is_nothrow_copy_constructible>{};

    constexpr auto is_move_constructible = detail::hana_trait<std::is_move_constructible>{};
    constexpr auto is_trivially_move_constructible = detail::hana_trait<std::is_trivially_move_constructible>{};
    constexpr auto is_nothrow_move_constructible = detail::hana_trait<std::is_nothrow_move_constructible>{};

    constexpr auto is_assignable = detail::hana_trait<std::is_assignable>{};
    constexpr auto is_trivially_assignable = detail::hana_trait<std::is_trivially_assignable>{};
    constexpr auto is_nothrow_assignable = detail::hana_trait<std::is_nothrow_assignable>{};

    constexpr auto is_copy_assignable = detail::hana_trait<std::is_copy_assignable>{};
    constexpr auto is_trivially_copy_assignable = detail::hana_trait<std::is_trivially_copy_assignable>{};
    constexpr auto is_nothrow_copy_assignable = detail::hana_trait<std::is_nothrow_copy_assignable>{};

    constexpr auto is_move_assignable = detail::hana_trait<std::is_move_assignable>{};
    constexpr auto is_trivially_move_assignable = detail::hana_trait<std::is_trivially_move_assignable>{};
    constexpr auto is_nothrow_move_assignable = detail::hana_trait<std::is_nothrow_move_assignable>{};

    constexpr auto is_destructible = detail::hana_trait<std::is_destructible>{};
    constexpr auto is_trivially_destructible = detail::hana_trait<std::is_trivially_destructible>{};
    constexpr auto is_nothrow_destructible = detail::hana_trait<std::is_nothrow_destructible>{};

    constexpr auto has_virtual_destructor = detail::hana_trait<std::has_virtual_destructor>{};

    // Property queries
    constexpr auto alignment_of = detail::hana_trait<std::alignment_of>{};
    constexpr auto rank = detail::hana_trait<std::rank>{};
    constexpr struct extent_t {
        template <typename T, typename N>
        constexpr auto operator()(T const&, N const&) const {
            constexpr unsigned n = N::value;
            using Result = typename std::extent<typename T::type, n>::type;
            return hana::integral_c<typename Result::value_type, Result::value>;
        }

        template <typename T>
        constexpr auto operator()(T const& t) const
        { return (*this)(t, hana::uint_c<0>); }
    } extent{};

    // Type relationships
    constexpr auto is_same = detail::hana_trait<std::is_same>{};
    constexpr auto is_base_of = detail::hana_trait<std::is_base_of>{};
    constexpr auto is_convertible = detail::hana_trait<std::is_convertible>{};

    ///////////////////////
    // Type modifications
    ///////////////////////
    // Const-volatility specifiers
    constexpr auto remove_cv = metafunction<std::remove_cv>;
    constexpr auto remove_const = metafunction<std::remove_const>;
    constexpr auto remove_volatile = metafunction<std::remove_volatile>;

    constexpr auto add_cv = metafunction<std::add_cv>;
    constexpr auto add_const = metafunction<std::add_const>;
    constexpr auto add_volatile = metafunction<std::add_volatile>;

    // References
    constexpr auto remove_reference = metafunction<std::remove_reference>;
    constexpr auto add_lvalue_reference = metafunction<std::add_lvalue_reference>;
    constexpr auto add_rvalue_reference = metafunction<std::add_rvalue_reference>;

    // Pointers
    constexpr auto remove_pointer = metafunction<std::remove_pointer>;
    constexpr auto add_pointer = metafunction<std::add_pointer>;

    // Sign modifiers
    constexpr auto make_signed = metafunction<std::make_signed>;
    constexpr auto make_unsigned = metafunction<std::make_unsigned>;

    // Arrays
    constexpr auto remove_extent = metafunction<std::remove_extent>;
    constexpr auto remove_all_extents = metafunction<std::remove_all_extents>;

    // Miscellaneous transformations
    constexpr struct aligned_storage_t {
        template <typename Len, typename Align>
        constexpr auto operator()(Len const&, Align const&) const {
            constexpr std::size_t len = Len::value;
            constexpr std::size_t align = Align::value;
            using Result = typename std::aligned_storage<len, align>::type;
            return hana::type_c<Result>;
        }

        template <typename Len>
        constexpr auto operator()(Len const&) const {
            constexpr std::size_t len = Len::value;
            using Result = typename std::aligned_storage<len>::type;
            return hana::type_c<Result>;
        }
    } aligned_storage{};

    constexpr struct aligned_union_t {
        template <typename Len, typename ...T>
        constexpr auto operator()(Len const&, T const&...) const {
            constexpr std::size_t len = Len::value;
            using Result = typename std::aligned_union<len, typename T::type...>::type;
            return hana::type_c<Result>;
        }
    } aligned_union{};

    constexpr auto decay = metafunction<std::decay>;
    // enable_if
    // disable_if
    // conditional

    constexpr auto common_type = metafunction<std::common_type>;
    constexpr auto underlying_type = metafunction<std::underlying_type>;
    constexpr auto result_of = metafunction<std::result_of>;


    ///////////////////////
    // Utilities
    ///////////////////////
    struct declval_t {
        template <typename T>
        typename std::add_rvalue_reference<
            typename T::type
        >::type operator()(T const&) const;
    };

    constexpr declval_t declval{};
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TRAITS_HPP

/* traits.hpp
+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
*/