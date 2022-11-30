/*
Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_DEFAULT_BOOST_CLBL_TRTS_HPP
#define BOOST_CLBL_TRTS_DETAIL_DEFAULT_BOOST_CLBL_TRTS_HPP

namespace boost { namespace callable_traits { namespace detail {
          
template<typename T = void>
struct default_callable_traits {

    // value is used by all traits classes to participate 
    // in the <callable_traits/detail/traits.hpp> disjunction.
    static constexpr bool value = false;
    
    // used facilitate the disjunction in
    // <callable_traits/detail/traits.hpp>
    using traits = default_callable_traits;
    
    using error_t = error_type<T>;

    // represents the type under consideration
    using type = error_t;
    
    // std::true_type for callables with C-style variadics
    using has_varargs = std::false_type;
    
    using return_type = error_t;
    
    // arg_types is a std::tuple of argument types for
    // callables that are not overloaded/templated function objects.
    // arg_types IS defined in terms of INVOKE, which means
    // a PMF's arg_types tuple will use a reference to its
    // parent class as the first argument, with qualifiers added to
    // match the PMF's own qualifiers.
    using arg_types = error_t;
    
    // arg_types without the decltype(*this) parameter for member functions
    using non_invoke_arg_types = error_t;

    // An "approximation" of a callable type, in the form
    // of a plain function type. Defined in terms of INVOKE.
    // An identity alias for qualified/unqualified plain function
    // types.
    using function_type = error_t;
    
    // Used to smoothen the edges between PMFs and function objects
    using function_object_signature = error_t;

    // An identity alias for qualified/unqualified plain function
    // types. Equivalent to remove_member_pointer for PMFs. Same
    // as function_type for other callable types.
    using qualified_function_type = error_t;
    
    // Removes C-style variadics from a signature, if present.
    // Aliases error_t for function objects and PMDs.
    using remove_varargs = error_t;
    
    // Adds C-style variadics to a signature. Aliases
    // error_t for function objects and PMDs.
    using add_varargs = error_t;
    
    // std::true_type when the signature includes noexcept, when
    // the feature is available
    using is_noexcept = std::false_type;

    // adds noexcept to a signature if the feature is available
    using add_noexcept = error_t;

    // removes noexcept from a signature if present
    using remove_noexcept = error_t;

    // std::true_type when the signature includes transaction_safe, when
    // the feature is available
    using is_transaction_safe = std::false_type;

    // adds transaction_safe to a signature if the feature is available
    using add_transaction_safe = error_t;

    // removes transaction_safe from a signature if present
    using remove_transaction_safe = error_t;

    // The class of a PMD or PMF. error_t for other types
    using class_type = error_t;
    
    // The qualified reference type of class_type. error_t
    // for non-member-pointers.
    using invoke_type = error_t;
    
    // Removes reference qualifiers from a signature.
    using remove_reference = error_t;
    
    // Adds an lvalue qualifier to a signature, in arbitrary
    // accordance with C++11 reference collapsing rules.
    using add_member_lvalue_reference = error_t;
    
    // Adds an rvalue qualifier to a signature, in arbitrary
    // accordance with C++11 reference collapsing rules.
    using add_member_rvalue_reference = error_t;
    
    // Adds a const qualifier to a signature.
    using add_member_const = error_t;
    
    // Adds a volatile qualifier to a signature.
    using add_member_volatile = error_t;
    
    // Adds both const and volatile qualifiers to a signature.
    using add_member_cv = error_t;
    
    // Removes a const qualifier from a signature, if present.
    using remove_member_const = error_t;
    
    // Removes a volatile qualifier from a signature, if present.
    using remove_member_volatile = error_t;
    
    // Removes both const and volatile qualifiers from a
    // signature, if any.
    using remove_member_cv = error_t;
    
    // Removes the member pointer from PMDs and PMFs. An identity
    // alias for other callable types.
    using remove_member_pointer = error_t;
    
    // Changes the parent class type for PMDs and PMFs. Turns
    // function pointers, function references, and
    // qualified/unqualified function types into PMFs. Turns
    // everything else into member data pointers.
    template<typename C,
        typename U = T,
        typename K = typename std::remove_reference<U>::type,
        typename L = typename std::conditional<
            std::is_same<void, K>::value, error_t, K>::type,
        typename Class = typename std::conditional<
            std::is_class<C>::value, C, error_t>::type>
    using apply_member_pointer = typename std::conditional<
        std::is_same<L, error_t>::value || std::is_same<Class, error_t>::value,
        error_t, L Class::*>::type;
    
    // Changes the return type of PMFs, function pointers, function
    // references, and qualified/unqualified function types. Changes
    // the data type of PMDs. error_t for function objects.
    template<typename>
    using apply_return = error_t;

    // Expands the argument types into a template
    template<template<class...> class Container>
    using expand_args = error_t;

    template<template<class...> class Container, typename... RightArgs>
    using expand_args_left = error_t;

    template<template<class...> class Container, typename... LeftArgs>
    using expand_args_right = error_t;

    using clear_args = error_t;
    
    template<typename... NewArgs>
    using push_front = error_t;

    template<typename... NewArgs>
    using push_back = error_t;
    
    template<std::size_t ElementCount>
    using pop_front = error_t;

    template<std::size_t ElementCount>
    using pop_back = error_t;
    
    template<std::size_t Index, typename... NewArgs>
    using insert_args = error_t;

    template<std::size_t Index, std::size_t Count>
    using remove_args = error_t;

    template<std::size_t Index, typename... NewArgs>
    using replace_args = error_t;

    static constexpr qualifier_flags cv_flags = cv_of<T>::value;
    static constexpr qualifier_flags ref_flags = ref_of<T>::value;
    static constexpr qualifier_flags q_flags = cv_flags | ref_flags;

    using has_member_qualifiers = std::integral_constant<bool, q_flags != default_>;
    using is_const_member = std::integral_constant<bool, 0 < (cv_flags & const_)>;
    using is_volatile_member = std::integral_constant<bool, 0 < (cv_flags & volatile_)>;
    using is_cv_member = std::integral_constant<bool, cv_flags == (const_ | volatile_)>;

#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
    using is_reference_member = std::false_type;
    using is_lvalue_reference_member = std::false_type;
    using is_rvalue_reference_member = std::false_type;
#else
    using is_reference_member = std::integral_constant<bool, 0 < ref_flags>;
    using is_lvalue_reference_member = std::integral_constant<bool, ref_flags == lref_>;
    using is_rvalue_reference_member = std::integral_constant<bool, ref_flags == rref_>;
#endif //#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

};

}}} // namespace boost::callable_traits::detail

#endif // BOOST_CLBL_TRTS_DETAIL_DEFAULT_BOOST_CLBL_TRTS_HPP


/* default_callable_traits.hpp
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
*/