
#ifndef BOOST_CONTRACT_MACRO_HPP_
#define BOOST_CONTRACT_MACRO_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Allow to disable contracts to completely remove their compile-time and run-time
overhead.
This header automatically includes all header files <c>boost/contract/\*.hpp</c>
necessary to use its macros.

Almost all the macros defined in this header file are variadic macros. On
compilers that do not support variadic macros, programmers can manually code
<c>\#ifndef BOOST_CONTRACT_NO_...</c> statements instead (see
@RefSect{extras.disable_contract_compilation__macro_interface_,
Disable Contract Compilation}).
*/

// IMPORTANT: Following headers can always be #included (without any #if-guard)
// because they expand to trivial code that does not affect compile-time. These
// headers must always be #included here (without any #if-guard) because they
// define types and macros that are typically left in user code even when
// contracts are disables (these types and macros never affect run-time and
// their definitions are trivial when contracts are disabled so their impact on
// compile-time is negligible).
#include <boost/contract/override.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/core/constructor_precondition.hpp>
#include <boost/contract/core/check_macro.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>

#ifndef BOOST_CONTRACT_NO_CONDITIONS
    #include <boost/contract/assert.hpp>
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program preconditions that can be completely disabled at compile-time.

    @c BOOST_CONTRACT_PRECONDITION(f) expands to code equivalent to the
    following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} is defined):
    
    @code
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        .precondition(f)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>f</b></c> is the nullay functor called by this library to
            check preconditions @c f().
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::precondition_failure}).
            This functor should capture variables by (constant) value, or better
            by (constant) reference (to avoid extra copies).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.preconditions, Preconditions}
    */
    #define BOOST_CONTRACT_PRECONDITION(...)
#elif !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #define BOOST_CONTRACT_PRECONDITION(...) .precondition(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_PRECONDITION(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program postconditions that can be completely disabled at compile-time.

    @c BOOST_CONTRACT_POSTCONDITION(f) expands to code equivalent to the
    following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} is defined):
    
    @code
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        .postcondition(f)
    #endif
    @endcode
    
    Where:

    @arg    <c><b>f</b></c> is the functor called by this library to check
            postconditions @c f() or @c f(result).
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::postcondition_failure}).
            This functor should capture variables by (constant) references (to
            access the values they will have at function exit).
            This functor takes the return value (preferably by <c>const&</c>)
            @c result as its one single parameter @c f(result) but only for
            virtual public functions and public functions overrides, otherwise
            it takes no parameter @c f().
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.postconditions, Postconditions}
    */
    #define BOOST_CONTRACT_POSTCONDITION(...)
#elif !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #define BOOST_CONTRACT_POSTCONDITION(...) .postcondition(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_POSTCONDITION(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program exception guarantees that can be completely disabled at
    compile-time.
    
    @c BOOST_CONTRACT_EXCEPT(f) expands to code equivalent to the following
    (note that no code is generated when @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}
    is defined):
    
    @code
    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        .except(f)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>f</b></c> is the nullary functor called by this library to
            check exception guarantees @c f().
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::except_failure}).
            This functor should capture variables by (constant) references (to
            access the values they will have at function exit).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.exception_guarantees, Exception Guarantees}
    */
    #define BOOST_CONTRACT_EXCEPT(...)
#elif !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #define BOOST_CONTRACT_EXCEPT(...) .except(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_EXCEPT(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program old value copies at body that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_OLD(f) expands to code equivalent to the following (note
    that no code is generated when @RefMacro{BOOST_CONTRACT_NO_OLDS} is
    defined):
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        .old(f)
    #endif
    @endcode
    
    Where:

    @arg    <c><b>f</b></c> is the nullary functor called by this library
            @c f() to assign old value copies just before the body is execute
            but after entry invariants (when they apply) and preconditions are
            checked.
            Old value pointers within this functor call are usually assigned
            using @RefMacro{BOOST_CONTRACT_OLDOF}.
            Any exception thrown by a call to this functor will result in
            this library calling @RefFunc{boost::contract::old_failure} (because
            old values could not be copied to check postconditions and exception
            guarantees).
            This functor should capture old value pointers by references so they
            can be assigned (all other variables needed to evaluate old value
            expressions can be captured by (constant) value, or better by
            (constant) reference to avoid extra copies).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{advanced.old_values_copied_at_body,
            Old Values Copied at Body}
    */
    #define BOOST_CONTRACT_OLD(...)

    /**
    Program old values that can be completely disabled at compile-time for old
    value types that are required to be copyable.

    This is used to program old value copies for copyable types:

    @code
    class u {
    public:
        void f(...) {
            BOOST_CONTRACT_OLD_PTR(old_type_a)(old_var_a); // Null...
            BOOST_CONTRACT_OLD_PTR(old_type_b)(old_var_b, old_expr_b); // Set.
            BOOST_CONTRACT_PUBLIC_FUNCTION(this)
                ...
                BOOST_CONTRACT_OLD([&] {
                    old_var_a = BOOST_CONTRACT_OLDOF(old_expr_a); // ...set.
                    ...
                })
                ...
            ;

            ... // Function body.
        }

        virtual void g(..., boost::contract::virtual_* v = 0) {
            BOOST_CONTRACT_OLD_PTR(old_type_a)(old_var_a); // No `v`
            BOOST_CONTRACT_OLD_PTR(old_type_b)(v, old_var_b, old_expr_b); // `v`
            BOOST_CONTRACT_PUBLIC_FUNCTION(v, this)
                ...
                BOOST_CONTRACT_OLD([&] {
                    old_var_a = BOOST_CONTRACT_OLDOF(v, old_expr_a); // `v`
                    ...
                })
                ...
            ;

            ... // Function body.
        }

        ...
    };
    @endcode
    
    This is an overloaded variadic macro and it can be used in the following
    different ways (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_OLDS} is defined).

    1\. <c>BOOST_CONTRACT_OLD_PTR(old_type)(old_var)</c> expands to code
        equivalent to the following (this leaves the old value pointer null):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        // This declaration does not need to use `v`.
        boost::contract::old_ptr<old_type> old_var
    #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_OLD_PTR(old_type)(old_var, old_expr)</c> expands to
        code equivalent to the following (this initializes the pointer to the
        old value copy, but not to be used for virtual public functions and
        public function overrides):
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<old_type> old_var =
                BOOST_CONTRACT_OLDOF(old_expr)
    #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_OLD_PTR(old_type)(v, old_var, old_expr)</c> expands to
        code equivalent to the following (this initializes the pointer to the
        old value copy for virtual public functions and public function
        overrides):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<old_type> old_var =
                BOOST_CONTRACT_OLDOF(v, old_expr)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>old_type</b></c> is the type of the pointed old value.
            This type must be copyable (i.e.,
            <c>boost::contract::is_old_value_copyable<old_type>::value</c> is
            @c true), otherwise this pointer will always be null and this
            library will generate a compile-time error when the pointer is
            dereferenced (see @RefMacro{BOOST_CONTRACT_OLD_PTR_IF_COPYABLE}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
            (Rationale: Template parameters like this one are specified to
            this library macro interface using their own set of parenthesis
            <c>SOME_MACRO(template_params)(other_params)</c>.)
    @arg    <c><b>v</b></c> is the extra training parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function or public function
            override declaring the contract.
            (This is not a variadic macro parameter but it should never contain
            commas because it is an identifier.)
    @arg    <c><b>old_var</b></c> is the name of the old value pointer variable.
            (This is not a variadic macro parameter but it should never contain
            commas because it is an identifier.)
    @arg    <c><b>old_expr</b></c> is the expression to be evaluated and copied
            in the old value pointer.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis and
            <c>BOOST_CONTRACT_OLD_PTR(old_type)(v, old_var, (old_expr))</c>
            will always work.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.old_values, Old Values}
    */
    #define BOOST_CONTRACT_OLD_PTR(...)

    /**
    Program old values that can be completely disabled at compile-time for old
    value types that are not required to be copyable.
    
    This is used to program old value copies for types that might or might not
    be copyable:

    @code
    template<typename T> // Type `T` might or not be copyable.
    class u {
    public:
        void f(...) {
            BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type_a)(old_var_a);
            BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type_b)(old_var_b,
                    old_expr_b);
            BOOST_CONTRACT_PUBLIC_FUNCTION(this)
                ...
                BOOST_CONTRACT_OLD([&] {
                    old_var_a = BOOST_CONTRACT_OLDOF(old_expr_a);
                    ...
                })
                ... // In postconditions or exception guarantees:
                    if(old_var_a) ... // Always null for non-copyable types.
                    if(old_var_b) ... // Always null for non-copyable types.
                ...
            ;

            ... // Function body.
        }

        virtual void g(..., boost::contract::virtual_* v = 0) {
            BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type_a)(old_var_a);
            BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type_b)(v, old_var_b,
                    old_expr_b);
            BOOST_CONTRACT_PUBLIC_FUNCTION(v, this)
                ...
                BOOST_CONTRACT_OLD([&] {
                    old_var_a = BOOST_CONTRACT_OLDOF(v, old_expr_a);
                    ...
                })
                ... // In postconditions or exception guarantees:
                    if(old_var_a) ... // Always null for non-copyable types.
                    if(old_var_b) ... // Always null for non-copyable types.
                ...
            ;

            ... // Function body.
        }

        ...
    };
    @endcode
    
    This is an overloaded variadic macro and it can be used in the following
    different ways (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_OLDS} is defined).

    1\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type)(old_var)</c> expands to
        code equivalent to the following (this leaves the old value pointer
        null):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        // This declaration does not need to use `v`.
        boost::contract::old_ptr_if_copyable<old_type> old_var
    #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type)(old_var, old_expr)</c>
        expands to code equivalent to the following (this initializes the
        pointer to the old value copy, but not to be used for virtual public
        functions and public function overrides):
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<old_type> old_var =
                BOOST_CONTRACT_OLDOF(old_expr)
    #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type)(v, old_var,
        old_expr)</c> expands to code equivalent to the following (this
        initializes the pointer to the old value copy for virtual public
        functions and public function overrides):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<old_type> old_var =
                BOOST_CONTRACT_OLDOF(v, old_expr)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>old_type</b></c> is the type of the pointed old value.
            If this type is not copyable (i.e.,
            <c>boost::contract::is_old_value_copyable<old_type>::value</c> is
            @c false), this pointer will always be null, but this library will
            not generate a compile-time error when this pointer is dereferenced
            (see @RefMacro{BOOST_CONTRACT_OLD_PTR}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>v</b></c> is the extra trailing parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function or public function
            override declaring the contract.
            (This is not a variadic macro parameter but it should never contain
            commas because it is an identifier.)
    @arg    <c><b>old_var</b></c> is the name of the old value pointer variable.
            (This is not a variadic macro parameter but it should never contain
            commas because it is an identifier.)
    @arg    <c><b>old_expr</b></c> is the expression to be evaluated and copied
            in the old value pointer.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis and
            <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(old_type)(v, old_var,
            (old_expr))</c> will always work.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{extras.old_value_requirements__templates_,
            Old Value Requirements}
    */
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...)
#elif !defined(BOOST_CONTRACT_NO_OLDS)
    #include <boost/contract/old.hpp>
    #include <boost/preprocessor/facilities/overload.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
    #include <boost/preprocessor/cat.hpp>

    /* PRIVATE */

    #define BOOST_CONTRACT_OLD_VAR_1(ptr) \
        ptr
    #define BOOST_CONTRACT_OLD_VAR_2(ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(expr)
    #define BOOST_CONTRACT_OLD_VAR_3(v, ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(v, expr)

    #define BOOST_CONTRACT_OLD_VAR_(...) \
        BOOST_PP_CAT(BOOST_PP_OVERLOAD(BOOST_CONTRACT_OLD_VAR_, __VA_ARGS__) \
                (__VA_ARGS__), BOOST_PP_EMPTY())

    /* PUBLIC */
    
    #define BOOST_CONTRACT_OLD(...) .old(__VA_ARGS__)

    #define BOOST_CONTRACT_OLD_PTR(...) \
        boost::contract::old_ptr< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_

    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) \
        boost::contract::old_ptr_if_copyable< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
#else
    #include <boost/preprocessor/tuple/eat.hpp>
   
    #define BOOST_CONTRACT_OLD(...) /* nothing */

    #define BOOST_CONTRACT_OLD_PTR(...) BOOST_PP_TUPLE_EAT(0)
    
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) BOOST_PP_TUPLE_EAT(0)
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program (constant) class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_INVARIANT({ ... }) expands to code equivalent to the
    following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined):

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            void BOOST_CONTRACT_INVARIANT_FUNC() const {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for public functions that are not static and not volatile
            (see @RefMacro{BOOST_CONTRACT_STATIC_INVARIANT} and
            @RefMacro{BOOST_CONTRACT_INVARIANT_VOLATILE}).
            The curly parenthesis are mandatory (rationale: this is so the
            syntax of this macro resembles mote the syntax of the lambda
            functions usually used to specify preconditions, etc.).
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.class_invariants, Class Invariants}
    */
    #define BOOST_CONTRACT_INVARIANT(...)

    /**
    Program volatile class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_INVARIANT_VOLATILE({ ... }) expands to code equivalent to
    the following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined):

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            void BOOST_CONTRACT_INVARIANT_FUNC() const volatile {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for volatile public functions
            (see @RefMacro{BOOST_CONTRACT_INVARIANT} and
            @RefMacro{BOOST_CONTRACT_STATIC_INVARIANT}).
            The curly parenthesis are mandatory.
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}
    */
    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...)
    
    /**
    Program static class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_STATIC_INVARIANT({ ... }) expands to code equivalent to
    the following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined):

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for static public functions
            (see @RefMacro{BOOST_CONTRACT_INVARIANT} and
            @RefMacro{BOOST_CONTRACT_INVARIANT_VOLATILE}).
            The curly parenthesis are mandatory.
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.class_invariants, Class Invariants}
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT(...)
#elif !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/core/config.hpp>

    #define BOOST_CONTRACT_INVARIANT(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const __VA_ARGS__

    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const volatile __VA_ARGS__
    
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) \
        static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() __VA_ARGS__
#else
    #define BOOST_CONTRACT_INVARIANT(...) /* nothing */

    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) /* nothing */
    
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts that can be completely disabled at compile-time for
    constructors.
    
    This is used together with @RefMacro{BOOST_CONTRACT_POSTCONDITION},
    @RefMacro{BOOST_CONTRACT_EXCEPT}, and @RefMacro{BOOST_CONTRACT_OLD} to
    specify postconditions, exception guarantees, and old value copies at body
    that can be completely disabled at compile-time for constructors (see
    @RefMacro{BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION} to specify preconditions
    for constructors):

    @code
    class u {
        friend class boost::contract::access;

        BOOST_CONTRACT_INVARIANT({ // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        })

    public:
        u(...) {
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_CONSTRUCTOR(this)
                // No `PRECONDITION` (use `CONSTRUCTOR_PRECONDITION` if needed).
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(old_epxr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_EXCEPT([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ; // Trailing `;` is required.

            ... // Constructor body.
        }

        ...
    };
    @endcode

    For optimization, this can be omitted for constructors that do not have
    postconditions and exception guarantees, within classes that have no
    invariants.
            
    @c BOOST_CONTRACT_CONSTRUCTOR(obj) expands to code equivalent to the
    following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_CONSTRUCTORS} is defined):

    @code
        #ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
            boost::contract::check internal_var =
                    boost::contract::constructor(obj)
        #endif
    @endcode

    Where:
    
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing constructor declaring the contract.
            Constructors check all class invariants, including static and
            volatile invariants (see @RefMacro{BOOST_CONTRACT_INVARIANT},
            @RefMacro{BOOST_CONTRACT_STATIC_INVARIANT}, and
            @RefMacro{BOOST_CONTRACT_INVARIANT_VOLATILE}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.constructors, Constructors}
    */
    #define BOOST_CONTRACT_CONSTRUCTOR(...)
#elif !defined(BOOST_CONTRACT_NO_CONSTRUCTORS)
    #include <boost/contract/constructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_CONSTRUCTOR(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::constructor(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_CONSTRUCTOR(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program preconditions that can be disabled at compile-time for constructors.
            
    This is used together with @RefMacro{BOOST_CONTRACT_CONSTRUCTOR} to specify
    contracts for constructors.
    Constructors that do not have preconditions do not use this macro.
    When at least one of the class constructors uses this macro,
    @RefClass{boost::contract::constructor_precondition} must be the first and
    private base of the class declaring the constructor for which preconditions
    are programmed:

    @code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

        ...

    public:
        explicit u(unsigned x) :
            BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(u)([&] {
                BOOST_CONTRACT_ASSERT(x != 0);
            }),
            b(1 / x)
        {
            ...
        }

        ...
    };
    @endcode

    <c>BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(class_type)(f)</c> expands
    to code equivalent to the following (note that when
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} is defined, this macro trivially
    expands to a default constructor call that is internally implemented to do
    nothing so this should have minimal to no overhead):

    @code
    // Guarded only by NO_PRECONDITIONS (and not also by NO_CONSTRUCTORS)
    // because for constructor's preconditions (not for postconditions, etc.).
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        boost::contract::constructor_precondition<class_type>(f)
    #else // No-op call (likely optimized away, minimal to no overhead).
        boost::contract::constructor_precondition<class_type>()
    #endif
    
    @endcode
    
    Where:

    @arg    <c><b>class_type</b></c> is the type of the class containing the
            constructor for which preconditions are being programmed.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>f</b></c> is the nullary functor called by this library to
            check constructor preconditions @c f().
            Assertions within this functor call are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract failure (and will result in
            this library calling
            @RefFunc{boost::contract::precondition_failure}).
            This functor should capture variables by (constant) value, or better
            by (constant) reference to avoid extra copies.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.constructors, Constructors}
    */
    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...)
#elif !defined(BOOST_CONTRACT_NO_PRECONDITIONS) // Not NO_CONSTRUCTORS here.
    // constructor_precondition.hpp already #included at top.

    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        boost::contract::constructor_precondition< __VA_ARGS__ >
#else
    #include <boost/preprocessor/tuple/eat.hpp>
    // constructor_precondition.hpp always #included at top of this file.

    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        /* always use default ctor (i.e., do nothing) */ \
        boost::contract::constructor_precondition< __VA_ARGS__ >() \
        BOOST_PP_TUPLE_EAT(0)
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts that can be completely disabled at compile-time for
    destructors.
    
    This is used together with @RefMacro{BOOST_CONTRACT_POSTCONDITION},
    @RefMacro{BOOST_CONTRACT_EXCEPT}, and @RefMacro{BOOST_CONTRACT_OLD} to
    specify postconditions, exception guarantees, and old value copies at body
    that can be completely disabled at compile-time for destructors (destructors
    cannot have preconditions, see
    @RefSect{contract_programming_overview.destructor_calls, Destructor Calls}):

    @code
    class u {
        friend class boost::contract::access;

        BOOST_CONTRACT_INVARIANT({ // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        })

    public:
        ~u() {
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_DESTRUCTOR(this)
                // No `PRECONDITION` (destructors have no preconditions).
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_EXCEPT([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ; // Trailing `;` is required.

            ... // Destructor body.
        }
        
        ...
    };
    @endcode

    For optimization, this can be omitted for destructors that do not have
    postconditions and exception guarantees, within classes that have no
    invariants.
    
    @c BOOST_CONTRACT_DESTRUCTOR(obj) expands to code equivalent to the
    following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_DESTRUCTORS} is defined):
    
    @code
        #ifndef BOOST_CONTRACT_NO_DESTRUCTORS
            boost::contract::check internal_var =
                    boost::contract::destructor(obj)
        #endif
    @endcode

    Where:
    
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing destructor declaring the contract.
            Destructors check all class invariants, including static and
            volatile invariants (see @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.destructors, Destructors}
    */
    #define BOOST_CONTRACT_DESTRUCTOR(...)
#elif !defined(BOOST_CONTRACT_NO_DESTRUCTORS)
    #include <boost/contract/destructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_DESTRUCTOR(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::destructor(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_DESTRUCTOR(...) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts that can be completely disabled at compile-time for
    (non-public) functions.
    
    This is used together with @RefMacro{BOOST_CONTRACT_PRECONDITION},
    @RefMacro{BOOST_CONTRACT_POSTCONDITION}, @RefMacro{BOOST_CONTRACT_EXCEPT},
    and @RefMacro{BOOST_CONTRACT_OLD} to specify preconditions, postconditions,
    exception guarantees, and old value copies at body that can be completely
    disabled at compile-time for (non-public) functions:
    
    @code
    void f(...) {
        BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
        BOOST_CONTRACT_FUNCTION()
            BOOST_CONTRACT_PRECONDITION([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            BOOST_CONTRACT_OLD([&] { // Optional.
                old_var = BOOST_CONTRACT_OLDOF(old_expr);  
                ...
            })
            BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            BOOST_CONTRACT_EXCEPT([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
        ; // Trailing `;` is required.

        ... // Function body.
    }
    @endcode
    
    This can be used to program contracts for non-member functions but also for
    private and protected functions, lambda functions, loops, arbitrary blocks
    of code, etc.
    For optimization, this can be omitted for code that does not have
    preconditions, postconditions, and exception guarantees.

    @c BOOST_CONTRACT_FUNCTION() expands to code equivalent to the following
    (note that no code is generated when @RefMacro{BOOST_CONTRACT_NO_FUNCTIONS}
    is defined):
    
    @code
        #ifndef BOOST_CONTRACT_NO_FUNCTIONS
            boost::contract::check internal_var =
                    boost::contract::function()
        #endif
    @endcode
    
    Where:
    
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).
    
    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.non_member_functions, Non-Member Functions},
            @RefSect{advanced.private_and_protected_functions,
            Private and Protected Functions},
            @RefSect{advanced.lambdas__loops__code_blocks__and__constexpr__,
            Lambdas\, Loops\, Code Blocks}
    */
    #define BOOST_CONTRACT_FUNCTION()
#elif !defined(BOOST_CONTRACT_NO_FUNCTIONS)
    #include <boost/contract/function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_FUNCTION() \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::function()
#else
    #include <boost/preprocessor/facilities/empty.hpp>

    #define BOOST_CONTRACT_FUNCTION() /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts that can be completely disabled at compile-time for static
    public functions.
    
    This is used together with @RefMacro{BOOST_CONTRACT_PRECONDITION},
    @RefMacro{BOOST_CONTRACT_POSTCONDITION}, @RefMacro{BOOST_CONTRACT_EXCEPT},
    and @RefMacro{BOOST_CONTRACT_OLD} to specify preconditions, postconditions,
    exception guarantees, and old value copies at body that can be completely
    disabled at compile-time for static public functions:

    @code
    class u {
        friend class boost::contract::access;

        BOOST_CONTRACT_STATIC_INVARIANT({ // Optional (as for non-static).
            BOOST_CONTRACT_ASSERT(...);
            ...
        })

    public:
        static void f(...) {
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION(u)
                BOOST_CONTRACT_PRECONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_EXCEPT([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ; // Trailing `;` is required.

            ... // Function body.
        }
        
        ...
    };
    @endcode

    For optimization, this can be omitted for static public functions that do
    not have preconditions, postconditions and exception guarantees, within
    classes that have no static invariants.
    
    @c BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(class_type) expands to code
    equivalent to the following (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS} is defined):
    
    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var =
                    boost::contract::public_function<class_type>()
        #endif
    @endcode
    
    Where:
    
    @arg    <c><b>class_type</b></c> is the type of the class containing the
            static public function declaring the contract.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).
    
    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.static_public_functions, Static Public Functions}
    */
    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...)

    /**
    Program contracts that can be completely disabled at compile-time for
    non-static public functions that do not override.
    
    This is used together with @RefMacro{BOOST_CONTRACT_PRECONDITION},
    @RefMacro{BOOST_CONTRACT_POSTCONDITION}, @RefMacro{BOOST_CONTRACT_EXCEPT},
    and @RefMacro{BOOST_CONTRACT_OLD} to specify preconditions, postconditions,
    exception guarantees, and old value copies at body that can be completely
    disabled at compile-time for non-static public functions (virtual or not,
    void or not) that do not override:

    @code
    class u {
        friend class boost::contract::access;

        BOOST_CONTRACT_INVARIANT({ // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        })

    public:
        // Non-virtual (same if void).
        t f(...) {
            t result;
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION(this)
                BOOST_CONTRACT_PRECONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_EXCEPT([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ; // Trailing `;` is required.

            ... // Function body (use `return result = return_expr`).
        }
        
        // Virtual and void.
        virtual void g(..., boost::contract::virtual_* v = 0) {
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION(v, this)
                ...
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                ...
            ; // Trailing `;` is required.
            
            ... // Function body.
        }
        
        // Virtual and non-void.
        virtual t h(..., boost::contract::virtual_* v = 0) {
            t result;
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION(v, result, this)
                ...
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] (t const& result) { // Optional
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                ...
            ; // Trailing `;` is required.
            
            ... // Function body (use `return result = return_expr`).
        }
        
        ...
    };
    @endcode

    For optimization, this can be omitted for non-virtual public functions that
    do not have preconditions, postconditions and exception guarantees, within
    classes that have no invariants.
    Virtual public functions should always use
    @RefMacro{BOOST_CONTRACT_PUBLIC_FUNCTION} otherwise this library will not
    be able to correctly use them for subcontracting.
    
    This is an overloaded variadic macro and it can be used in the following
    different ways (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS} is defined).

    1\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(obj)</c> expands to code
        equivalent to the following (for non-virtual public functions that are
        not static and do not override, returning void or not):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var =
                    boost::contract::public_function(obj)
        #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(v, obj)</c> expands to code
        equivalent to the following (for virtual public functions that do not
        override, returning void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var =
                    boost::contract::public_function(v, obj)
        #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(v, r, obj)</c> expands to code
        equivalent to the following (for virtual public functions that do not
        override, not returning void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var =
                    boost::contract::public_function(v, r, obj)
        #endif
    @endcode

    Where (these are all variadic macro parameters so they can contain commas
    not protected by round parenthesis):

    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function declaring the contract.
    @arg    <c><b>r</b></c> is a reference to the return value of the enclosing
            virtual public function declaring the contract.
            This is usually a local variable declared by the enclosing virtual
            public function just before the contract, but programmers must set
            it to the actual value being returned by the function at each
            @c return statement.
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing public function declaring the contract.
            This object might be mutable, @c const, @c volatile, or
            <c>const volatile</c> depending on the cv-qualifier of the enclosing
            function (volatile public functions will check volatile class
            invariants, see @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).
    
    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.public_functions, Public Functions},
            @RefSect{tutorial.virtual_public_functions,
            Virtual Public Functions}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...)
    
    /**
    Program contracts that can be completely disabled at compile-time for
    public function overrides.
    
    This is used together with @RefMacro{BOOST_CONTRACT_PRECONDITION},
    @RefMacro{BOOST_CONTRACT_POSTCONDITION}, @RefMacro{BOOST_CONTRACT_EXCEPT},
    and @RefMacro{BOOST_CONTRACT_OLD} to specify preconditions, postconditions,
    exception guarantees, and old value copies at body that can be completely
    disabled at compile-time for public function overrides (virtual or not):

    @code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b, private w
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

        BOOST_CONTRACT_INVARIANT({ // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        })

        BOOST_CONTRACT_OVERRIDES(f, g)

    public:
        // Override from `b::f`, and void.
        void f(t_1 a_1, ..., t_n a_n, boost::contract::virtual_* v = 0) {
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_f)(
                    v, &u::f, this, a_1, ..., a_n)
                BOOST_CONTRACT_PRECONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                BOOST_CONTRACT_EXCEPT([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ; // Trailing `;` is required.

            ... // Function body.
        }
        
        // Override from `b::g`, and void.
        t g(t_1 a_1, ..., t_n a_n, boost::contract::virtual_* v = 0) {
            t result;
            BOOST_CONTRACT_OLD_PTR(old_type)(old_var);
            BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_g)(
                    v, result, &u::g, this, a_1, ..., a_n)
                ...
                BOOST_CONTRACT_OLD([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                BOOST_CONTRACT_POSTCONDITION([&] (t const& result) { // Optional
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                ...
            ; // Trailing `;` is required.

            ... // Function body (use `return result = return_expr`).
        }
        
        ...
    };
    @endcode

    Public function overrides should always use
    @RefMacro{BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE} otherwise this library
    will not be able to correctly use it for subcontracting.
    
    This is an overloaded variadic macro and it can be used in the following
    different ways (note that no code is generated when
    @RefMacro{BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS} is defined).

    1\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_type)(v, f, obj,
        ...)</c> expands to code equivalent to the following (for public
        function overrides that return void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function<override_type>(v, f, obj, ...)
        #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_type)(v, r, f, obj,
        ...)</c> expands to code equivalent to the following (for public
        function overrides that do not return void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function<override_type>(v, r, f, obj, ...)
        #endif
    @endcode

    Where (these are all variadic macro parameters so they can contain commas
    not protected by round parenthesis):

    @arg    <c><b>override_type</b></c> is the type
            <c>override_<i>function-name</i></c> declared using the
            @RefMacro{BOOST_CONTRACT_OVERRIDE} or related macros.
    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function declaring the contract.
    @arg    <c><b>r</b></c> is a reference to the return value of the enclosing
            virtual public function declaring the contract.
            This is usually a local variable declared by the enclosing virtual
            public function just before the contract, but programmers must set
            it to the actual value being returned by the function at each
            @c return statement.
    @arg    <c><b>f</b></c> is a pointer to the enclosing public function
            override declaring the contract.
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing public function declaring the contract.
            This object might be mutable, @c const, @c volatile, or
            <c>const volatile</c> depending on the cv-qualifier of the enclosing
            function (volatile public functions will check volatile class
            invariants, see @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).
    @arg    <c><b>...</b></c> is a variadic macro parameter listing all the
            arguments passed to the enclosing public function override declaring
            the contract (by reference and in the order they appear in the
            enclosing function declaration), but excluding the trailing
            argument @c v.
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different line
            numbers so this macro cannot be expanded multiple times on the same
            line).
    
    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefSect{tutorial.public_function_overrides__subcontracting_,
            Public Function Overrides}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...)
#elif !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)
    #include <boost/contract/public_function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>
    
    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function< __VA_ARGS__ >()

    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function(__VA_ARGS__)

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function<__VA_ARGS__>
#else
    #include <boost/preprocessor/tuple/eat.hpp>
   
    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) /* nothing */

    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...) /* nothing */
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...) BOOST_PP_TUPLE_EAT(0)
#endif

#endif // #include guard


/* contract_macro.hpp
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
*/