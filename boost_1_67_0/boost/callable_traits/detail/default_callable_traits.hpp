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