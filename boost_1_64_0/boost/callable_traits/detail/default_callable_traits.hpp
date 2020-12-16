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
j1lq64/Rsb1qz9C11EuuydTB258Saslxt963y+A2fpwp8K7FyHJPrIebXygLvhXIe65pf+f8WuY1C5GnhUHvaQ3fFFltezf3r/rZ5gRUl7DhZqzB9GnS/1Ic1rYHbGWRzXT+g/LV+1vjq2vqDuF1rL5ZSzwXmLXXKkochXK+HBM+3iafaeTH419f5HN81uEmjFlDKdmbJ1bRPR6jeTBjqtRv2kJdVhfMGEyU9tfkiV8txhfcziiPAbbwY0z/RSM571hnsV+uiTtb/JZhd1kdMDfY4k4TvxY0/dxq7aEV2LuefLdL6LeifE39aq99DWb/D2OnXHzXm88F4pZs3CQvffYiPqZ7zn/vJi+V26lzSdO9dY5nRWp2zrhsn7pm+reXidw/XEcY6aH1TcNepzqIXuPZ0kdvleEMba1YE4+phyZMa9PPXiD2LmYfDA1jf5ZomJ5mvbtFYm9nxlOaMLb93tfNlGeBozM9W5EaTztxa0K/qFPPb9IjcdHHaquPk1oB83zME7mbHaMd1cx+81dLfKn2NcU0Pofo7cPGfsJdnMZCE+crM6TvykWMJo4EvziO+sWhe8Ob9QnXit8sd/H4H9kvx9TZkVIm99PjVkHWP5sh+7/jZ8rrCLW4KfWkNjkeb62FtrE/rSzbs+tFOVcVM2ekjoR/yOwBckCupxV9vBXNc8w9R/rm/fvjRMf/caaEVzt9d7O0L1HzimvJ458p08Ei34W4XOaZflTc+tPN9IH/3vmSf1vhfEn37W6/fUTM+nDPif+DrnaONxwx4sadLPG+62SkHbVjpGOb47hly+MxksdarwZqPtSlrl3PHJUFMEr82HNA/ApxrW8lks/j0QvVCVstWgxjBIKbPmoSo8WYMQWGAX6r3eidYefVOxGAdHjKSNcuXCZlaNXr279VG0vdkovdWnvdoordWnrdzkz3urW8yrvu4YFiOR3P6avndhl7utj3G3uG2B8z9lwd9+DVcXJ/isxRI1Po85wdpfNZnsbEYnZj7o31LIZl13m5k6enTpqcPzE9N9BzlntI5VuYZ+c+sVdWO0/cG6WOB9R3hNXnrq6JKPaVvnpO6/d28auhek/DmmesnkfHE6mOMvs6bBXZNWLPMWHjzXiKflH0ZdjNv/FcspdXkl959S4uH5+yyKtQvOZ+PdgQ7vSUxY3+ZZGfNWZqfkHOtKxAZaHyw02eRdyEHZuOW/QpA1ln14T5khKczXzD9mbNyH3i3tis32grE7M+5SMi86N1lX4XJJv4FlhtcJX1HIM8N65F9kGR3UM75A1aNhoePenzTNDr2S1+z/GJ2Mf+XCGM73qutmeB0cdHROZTqz5lHmYV6YwOojeKeJUa7JiLeS9m7KBf+Wf7lX+erfxlfdIA9+c83/vTjCs6JP9lfS7pa70C3k2dqDjPVifOf2+qbEtzf3UV+xC1M7JkPnZCBrg3NWxzsxZuF7Gfs5dlOhD/arCj+H8r9mwTvkmJe3mg8Wtoxg+2F3tlnRPKs1fs7zEScZn9fBnA3NNtROZTez0g3hJrlnJu8z1odFSGyDVTuzcfKtifrYUT8yyTvj4iHxowfbpWKTrkX9cjSX71qLexp/u9u2qe4zbMr26lFcuU2C8pRcfdL0U+VnmXR7/Mt9cl+aYyCsavTuleLuTFzRLGFW45HVUcfVnX7Da+qYc49J1K49zrzraGOJ919rKqulY69F00UD1T+brmG2N7UZr0nTPgO6+GqW/q031in2jGrdqeAeZdaKvIdA9taZk9kIjH/zurUDI4Sut0uQVST0KSXdnWw+4JPnWNsOY99JixZ4ba48qAdXRseGOJKzRkrjPEqu+inN0h1iDeWle68028CX4=
*/