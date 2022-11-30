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


namespace boost { namespace hana { namespace traits {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_void = detail::hana_trait<std::is_void>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_null_pointer = detail::hana_trait<std::is_null_pointer>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_integral = detail::hana_trait<std::is_integral>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_floating_point = detail::hana_trait<std::is_floating_point>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_array = detail::hana_trait<std::is_array>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_enum = detail::hana_trait<std::is_enum>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_union = detail::hana_trait<std::is_union>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_class = detail::hana_trait<std::is_class>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_function = detail::hana_trait<std::is_function>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_pointer = detail::hana_trait<std::is_pointer>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_lvalue_reference = detail::hana_trait<std::is_lvalue_reference>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_rvalue_reference = detail::hana_trait<std::is_rvalue_reference>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_member_object_pointer = detail::hana_trait<std::is_member_object_pointer>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_member_function_pointer = detail::hana_trait<std::is_member_function_pointer>{};

    // Composite type categories
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_fundamental = detail::hana_trait<std::is_fundamental>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_arithmetic = detail::hana_trait<std::is_arithmetic>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_scalar = detail::hana_trait<std::is_scalar>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_object = detail::hana_trait<std::is_object>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_compound = detail::hana_trait<std::is_compound>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_reference = detail::hana_trait<std::is_reference>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_member_pointer = detail::hana_trait<std::is_member_pointer>{};

    // Type properties
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_const = detail::hana_trait<std::is_const>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_volatile = detail::hana_trait<std::is_volatile>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivial = detail::hana_trait<std::is_trivial>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_copyable = detail::hana_trait<std::is_trivially_copyable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_standard_layout = detail::hana_trait<std::is_standard_layout>{};
#if __cplusplus < 202002L
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_pod = detail::hana_trait<std::is_pod>{};
#endif
#if __cplusplus < 201703L
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_literal_type = detail::hana_trait<std::is_literal_type>{};
#endif
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_empty = detail::hana_trait<std::is_empty>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_polymorphic = detail::hana_trait<std::is_polymorphic>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_abstract = detail::hana_trait<std::is_abstract>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_signed = detail::hana_trait<std::is_signed>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_unsigned = detail::hana_trait<std::is_unsigned>{};

    // Supported operations
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_constructible = detail::hana_trait<std::is_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_constructible = detail::hana_trait<std::is_trivially_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_constructible = detail::hana_trait<std::is_nothrow_constructible>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_default_constructible = detail::hana_trait<std::is_default_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_default_constructible = detail::hana_trait<std::is_trivially_default_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_default_constructible = detail::hana_trait<std::is_nothrow_default_constructible>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_copy_constructible = detail::hana_trait<std::is_copy_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_copy_constructible = detail::hana_trait<std::is_trivially_copy_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_copy_constructible = detail::hana_trait<std::is_nothrow_copy_constructible>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_move_constructible = detail::hana_trait<std::is_move_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_move_constructible = detail::hana_trait<std::is_trivially_move_constructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_move_constructible = detail::hana_trait<std::is_nothrow_move_constructible>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_assignable = detail::hana_trait<std::is_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_assignable = detail::hana_trait<std::is_trivially_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_assignable = detail::hana_trait<std::is_nothrow_assignable>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_copy_assignable = detail::hana_trait<std::is_copy_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_copy_assignable = detail::hana_trait<std::is_trivially_copy_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_copy_assignable = detail::hana_trait<std::is_nothrow_copy_assignable>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_move_assignable = detail::hana_trait<std::is_move_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_move_assignable = detail::hana_trait<std::is_trivially_move_assignable>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_move_assignable = detail::hana_trait<std::is_nothrow_move_assignable>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_destructible = detail::hana_trait<std::is_destructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_trivially_destructible = detail::hana_trait<std::is_trivially_destructible>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_nothrow_destructible = detail::hana_trait<std::is_nothrow_destructible>{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto has_virtual_destructor = detail::hana_trait<std::has_virtual_destructor>{};

    // Property queries
    BOOST_HANA_INLINE_VARIABLE constexpr auto alignment_of = detail::hana_trait<std::alignment_of>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto rank = detail::hana_trait<std::rank>{};
    BOOST_HANA_INLINE_VARIABLE constexpr struct extent_t {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_same = detail::hana_trait<std::is_same>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_base_of = detail::hana_trait<std::is_base_of>{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto is_convertible = detail::hana_trait<std::is_convertible>{};

    ///////////////////////
    // Type modifications
    ///////////////////////
    // Const-volatility specifiers
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_cv = metafunction<std::remove_cv>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_const = metafunction<std::remove_const>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_volatile = metafunction<std::remove_volatile>;

    BOOST_HANA_INLINE_VARIABLE constexpr auto add_cv = metafunction<std::add_cv>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto add_const = metafunction<std::add_const>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto add_volatile = metafunction<std::add_volatile>;

    // References
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_reference = metafunction<std::remove_reference>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto add_lvalue_reference = metafunction<std::add_lvalue_reference>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto add_rvalue_reference = metafunction<std::add_rvalue_reference>;

    // Pointers
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_pointer = metafunction<std::remove_pointer>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto add_pointer = metafunction<std::add_pointer>;

    // Sign modifiers
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_signed = metafunction<std::make_signed>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_unsigned = metafunction<std::make_unsigned>;

    // Arrays
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_extent = metafunction<std::remove_extent>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto remove_all_extents = metafunction<std::remove_all_extents>;

    // Miscellaneous transformations
    BOOST_HANA_INLINE_VARIABLE constexpr struct aligned_storage_t {
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

    BOOST_HANA_INLINE_VARIABLE constexpr struct aligned_union_t {
        template <typename Len, typename ...T>
        constexpr auto operator()(Len const&, T const&...) const {
            constexpr std::size_t len = Len::value;
            using Result = typename std::aligned_union<len, typename T::type...>::type;
            return hana::type_c<Result>;
        }
    } aligned_union{};

    BOOST_HANA_INLINE_VARIABLE constexpr auto decay = metafunction<std::decay>;
    // enable_if
    // disable_if
    // conditional

    BOOST_HANA_INLINE_VARIABLE constexpr auto common_type = metafunction<std::common_type>;
    BOOST_HANA_INLINE_VARIABLE constexpr auto underlying_type = metafunction<std::underlying_type>;


    ///////////////////////
    // Utilities
    ///////////////////////
    struct declval_t {
        template <typename T>
        typename std::add_rvalue_reference<
            typename T::type
        >::type operator()(T const&) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr declval_t declval{};
} }} // end namespace boost::hana

#endif // !BOOST_HANA_TRAITS_HPP

/* traits.hpp
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
*/