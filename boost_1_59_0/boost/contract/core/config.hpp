
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Configure this library compile-time and run-time behaviours.
*/

// IMPORTANT: This header MUST NOT #include any other header of this lib.
// That way users can #include this header and not #include any of this lib
// headers after that depending on the contract 0/1 macros below ensuring no
// compilation overhead.

// Export symbols when compiling as shared lib (for internal use only). (Named
// after similar macros in all Boost libs.)
// BOOST_CONTRACT_SOURCE

// Disable automatic library selection for linking. (Named after similar macros
// in all Boost libs.)
// BOOST_CONTRACT_NO_LIB
// BOOST_ALL_NO_LIB

#if (!defined(BOOST_CONTRACT_DYN_LINK) && defined(BOOST_ALL_DYN_LINK)) || \
        defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
    /**
    Define this macro to compile this library as a shared library (recommended).
    
    If this macro is defined, this library is compiled so it can be linked
    as a shared library (a.k.a., Dynamically Linked Library or DLL) to user
    code.
    This library will automatically define this macro when Boost libraries are
    built as shared libraries (e.g., defining @c BOOST_ALL_DYN_LINK or using
    <c>bjam link=shared ...</c>).
    
    @warning    In general this library will correctly check contracts at
                run-time only when compiled as a shared library, unless  user
                code checks contracts in a single program unit (e.g., a single
                program with only statically linked libraries).
                Therefore, it is recommended to build and use this library as
                a shared library by defining this macro (or equivalently by
                building all Boost libraries as shared libraries).
                
    @see    @RefSect{getting_started, Getting Started}
    */
    #define BOOST_CONTRACT_DYN_LINK
#elif defined(BOOST_CONTRACT_DYN_LINK) && defined(BOOST_CONTRACT_STATIC_LINK)
    #error "DYN_LINK defined with STATIC_LINK"
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Define this macro to compile this library as a static library (not
    recommended).

    If this macro is defined, this library is compiled so it can be linked
    statically to user code.
    This library will automatically define this macro when Boost libraries
    are built as static libraries.

    @warning    This library is not guaranteed to always work correctly at
                run-time when this macro is defined (define
                @RefMacro{BOOST_CONTRACT_DYN_LINK} or @c BOOST_ALL_DYN_LINK
                instead).
                However, this macro can be defined and this library can be
                safely used as a static library for user code that checks
                contracts in a single program unit (e.g., a single program with
                only statically linked libraries).
                
    @see    @RefSect{getting_started, Getting Started}
    */
    #define BOOST_CONTRACT_STATIC_LINK
#elif defined(BOOST_CONTRACT_STATIC_LINK) && defined(BOOST_CONTRACT_DYN_LINK)
    #error "STATIC_LINK defined with DYN_LINK"
#endif

#ifdef BOOST_CONTRACT_HEADER_ONLY
    #error "leave DYN_LINK and STATIC_LINK undefined instead"
#elif   (!defined(BOOST_CONTRACT_DYN_LINK) && \
        !defined(BOOST_CONTRACT_STATIC_LINK)) || \
        defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
    /**
    Automatically defined by this library when it is being used as a header-only
    library (not recommended).

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users do not define
    @RefMacro{BOOST_CONTRACT_DYN_LINK} (or @c BOOST_ALL_DYN_LINK) and
    @RefMacro{BOOST_CONTRACT_STATIC_LINK}.
    When used as a header-only library, this library code does not have to be
    compiled separately from user code, this library headers are simply included
    and compiled as part of the user program.
    
    @warning    This library is not guaranteed to always work correctly at
                run-time when this macro is defined (define
                @RefMacro{BOOST_CONTRACT_DYN_LINK} or @c BOOST_ALL_DYN_LINK
                instead).
                However, this macro can be defined and this library can be
                safely used as a header-only library for user code that checks
                contracts in a single program unit (e.g., a single program with
                only statically linked libraries).
                
    @see    @RefSect{getting_started, Getting Started}
    */
    #define BOOST_CONTRACT_HEADER_ONLY
#endif

#if     (!defined(BOOST_CONTRACT_DISABLE_THREADS) && \
        defined(BOOST_DISABLE_THREADS)) || \
        defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
    /**
    Define this macro to not lock internal library data for thread safety
    (undefined by default).

    Defining this macro will make the library implementation code not thread
    safe so this macro should not be defined unless the library is being used by
    single-threaded applications only.
    This library will automatically define this macro when Boost libraries are
    built without threads (e.g., defining @c BOOST_DISABLE_THREADS).

    @note   When this macro is left undefined this library needs to internally
            use some sort of global lock (to ensure contract checking is
            globally disabled when other contracts are being checked and also to
            safely access failure handler functors).
            That could introduce an undesired amount of synchronization in some
            multi-threaded applications.
    
    @see @RefSect{contract_programming_overview.assertions, Assertions}
    */
    #define BOOST_CONTRACT_DISABLE_THREADS
#endif

#ifndef BOOST_CONTRACT_MAX_ARGS
    /**
    Maximum number of arguments for public function overrides on compilers that
    do not support variadic templates (default to @c 10).

    On compilers that do not support C++11 variadic templates, this macro is
    defined to the maximum number of arguments that public function overrides
    can have and pass to @RefFunc{boost::contract::public_function} (users can
    redefine this macro to a different value).
    On compilers that support variadic templates, this macro has no effect.

    @note   Regardless of the value of this macro and of compiler support for
            variadic templates, there might be an intrinsic limit of about 18
            arguments for public function overrides (because of similar limits
            in Boost.MPL and Boost.FunctionTypes internally used by this
            library).

    @see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}
    */
    #define BOOST_CONTRACT_MAX_ARGS 10
#endif

#ifndef BOOST_CONTRACT_BASES_TYPEDEF
    /**
    Define the name of the base type @c typedef (@c base_types by default).

    This macro expands to the name of the @c typedef that lists the base
    classes for subcontracting via @RefMacro{BOOST_CONTRACT_BASE_TYPES}:

    @code
        class u
            #define BASES public b, private w
            : BASES
        {
            friend class boost::contract:access;

            typedef BOOST_CONTRACT_BASE_TYPES(BASES) BOOST_CONTRACT_TYPEDEF;
            #undef BASES

            ...
        };
    @endcode

    When used this way, users can redefine this macro if the @c typedef must
    have a name different from @c base_types (because of name clashes in user
    code, etc.).
    
    @see @RefSect{tutorial.base_classes__subcontracting_, Base Classes}
    */
    #define BOOST_CONTRACT_BASES_TYPEDEF base_types
#endif

#ifndef BOOST_CONTRACT_INVARIANT_FUNC
    /**
    Define the name of the class invariant member function (@c invariant by
    default).

    This macro expands to the name of the @c const and <c>const volatile</c>
    member functions that check class invariants and volatile class invariants
    respectively:

    @code
        class u {
            friend class boost::contract::access;

            void BOOST_CONTRACT_INVARIANT_FUNC() const {
                BOOST_CONTRACT_ASSERT(...);
                ...
            }
            
            void BOOST_CONTRACT_INVARIANT_FUNC() const volatile {
                BOOST_CONTRACT_ASSERT(...);
                ...
            }

            ...
        };
    @endcode

    When used this way, users can redefine this macro if the invariant functions
    must have a name different from @c invariant (because of name clashes in
    user code, etc.).
    
    @note   C++ does not allow to overload member functions based on the
            @c static classifier, so this macro must always be defined to be
            different than the function name defined for
            @RefMacro{BOOST_CONTRACT_STATIC_INVARIANT_FUNC}.
    
    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}
    */
    #define BOOST_CONTRACT_INVARIANT_FUNC invariant
#endif

#ifndef BOOST_CONTRACT_STATIC_INVARIANT_FUNC
    /**
    Define the name of the static invariant member function (@c static_invariant
    by default).

    This macro expands to the name of the @c static member function that checks
    static class invariants:

    @code
        class u {
            friend class boost::contract::access;

            static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() {
                BOOST_CONTRACT_ASSERT(...);
                ...
            }

            ...
        };
    @endcode

    When used this way, users can redefine this macro if the static invariant
    function must have a name different from @c static_invariant (because of
    name clashes in user code, etc.).

    @note   C++ does not allow to overload member functions based on the
            @c static classifier, so this macro must always be defined to be
            different than the function name defined for
            @RefMacro{BOOST_CONTRACT_INVARIANT_FUNC}.
    
    @see    @RefSect{tutorial.class_invariants, Class Invariants}
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT_FUNC static_invariant
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Disable some compile-time errors generated by this library (undefined by
    default).

    Defining this macro disables a number of static checks and related
    compile-time errors generated by this library, for example:

    @li The static invariant member function named as
        @c BOOST_CONTRACT_STATIC_INVARIANT_FUNC must be declared @c static.
    @li Non-static invariant member functions named as
        @c BOOST_CONTRACT_INVARIANT_FUNC must be declared either @c const,
        <c>const volatile</c>, or <c>volatile const</c>.
    @li Derived classes that program contracts for one or more public function
        overrides via @RefFunc{boost::contract::public_function} must also
        define the @RefMacro{BOOST_CONTRACT_BASE_TYPES} @c typedef.

    In general, it is not recommended to define this macro because these
    compile-time checks can guard against misuses of this library.
        
    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{tutorial.base_classes__subcontracting_, Base Classes}
    */
    #define BOOST_CONTRACT_PERMISSIVE
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Code block to execute if contracts are not assigned to a
    @RefClass{boost::contract::check} variable (undefined and executes
    @c BOOST_ASSERT(false) by default).

    In general, there is a logic error in the program when contracts are not
    explicitly assigned to a local variable of type
    @RefClass{boost::contract::check} and without using C++11 @c auto
    declarations (because that is a misuse of this library).
    Therefore, by default (i.e., when this macro is not defined) this library
    calls <c>BOOST_ASSERT(false)</c> in those cases.
    If this macro is defined, this library will execute the code expanded by
    this macro instead of calling @c BOOST_ASSERT(false) (if programmers prefer
    to throw an exception, etc.).

    This macro can also be defined to be any block of code (and use empty curly
    brackets @c {} to generate no error, not recommended), for example (on GCC):
    @code
        gcc -DBOOST_CONTRACT_ON_MISSING_CHECK_DECL='{ throw std::logic_error("missing contract check declaration"); }' ...
    @endcode

    @see @RefSect{tutorial, Tutorial}
    */
    #define BOOST_CONTRACT_ON_MISSING_CHECK_DECL
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Define this macro to not disable other assertions while checking
    preconditions (undefined by default).
    
    Not disabling other assertions while checking preconditions can lead to
    infinite recursion in user code so by default this macro is not defined.

    However, the @RefSect{bibliography, [N1962]} proposal does not disable
    assertions while checking preconditions because arguments can reach the
    function body unchecked if assertions are disabled while checking
    preconditions (e.g., when these same functions bodies are called to check
    the preconditions in question).
    This macro can be defined to obtain the behaviour specified in
    @RefSect{bibliography, [N1962]} (at the risk of infinite recursion).

    @see    @RefSect{contract_programming_overview.feature_summary,
            Feature Summary}
    */
    #define BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Define this macro to not disable any assertion while checking other
    assertions (undefined by default).
    
    Not disabling assertions while checking other assertions can lead to
    infinite recursion in user code so by default this macro is not defined.
    (Defining this macro automatically implies that other assertion checking is
    disabled while checking preconditions as if
    @RefMacro{BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION} was also
    defined.)

    @see    @RefSect{contract_programming_overview.feature_summary,
            Feature Summary}
    */
    #define BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Define this macro to evaluate and check audit assertions at run-time
    (undefined by default).

    Audit assertions and implementation checks programmed via
    @RefMacro{BOOST_CONTRACT_ASSERT_AUDIT} and
    @RefMacro{BOOST_CONTRACT_CHECK_AUDIT} are always compiled and validated
    syntactically.
    However, they are not evaluated and checked at run-time unless
    this macro is defined (because these conditions can be computationally
    expensive, at least compared to the computational cost of executing the
    function body).

    @see @RefSect{extras.assertion_levels, Assertion Levels}
    */
    #define BOOST_CONTRACT_AUDITS
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    If defined, this library disables implementation checks (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    implementation checks.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of implementation checks
    or use @RefMacro{BOOST_CONTRACT_CHECK} (recommended).
    
    @see    @RefSect{advanced.implementation_checks,
            Implementation Checks},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_CHECKS
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    If defined, this library does not check preconditions (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking preconditions.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of preconditions or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    @see    @RefSect{tutorial.preconditions, Preconditions},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_PRECONDITIONS
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    If defined, this library does not check postconditions (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking postconditions.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of postconditions or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    It is necessary to disable both postconditions and exception guarantees
    defining @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} in order to disable old value copies
    (see @RefMacro{BOOST_CONTRACT_NO_OLDS}).

    @see    @RefSect{tutorial.postconditions, Postconditions},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_POSTCONDITIONS
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    If defined, this library does not check exception guarantees (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking exception guarantees.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of exception guarantees
    or use the macros defined in @c boost/contract_macro.hpp (recommended only
    for applications where it is truly necessary to completely remove contract
    code compilation from production code).
    
    It is necessary to disable both postconditions and exception guarantees
    defining @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} in order to disable old value copies
    (see @RefMacro{BOOST_CONTRACT_NO_OLDS}).
    
    @see    @RefSect{tutorial.exception_guarantees, Exception Guarantees},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_EXCEPTS
#endif

#if     defined(BOOST_CONTRACT_DETAIL_DOXYGEN) || \
        ( \
            !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
             defined(BOOST_CONTRACT_NO_INVARIANTS) \
        )
    /**
    If defined, this library does not check class invariants at entry (undefined
    by default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking class invariants at entry.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of entry class invariants
    or use the macros defined in @c boost/contract_macro.hpp (recommended only
    for applications where it is truly necessary to completely remove contract
    code compilation from production code).

    This macro is automatically defined when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_ENTRY_INVARIANTS
#endif

#if     defined(BOOST_CONTRACT_DETAIL_DOXYGEN) || \
        ( \
            !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) && \
             defined(BOOST_CONTRACT_NO_INVARIANTS) \
        )
    /**
    If defined, this library does not check class invariants at exit (undefined
    by default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking class invariants at exit.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of exit class invariants
    or use the macros defined in @c boost/contract_macro.hpp (recommended only
    for applications where it is truly necessary to completely remove contract
    code compilation from production code).

    This macro is automatically defined when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_EXIT_INVARIANTS
#endif

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
         defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
         defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS)
    /**
    If defined, this library does not check class invariants (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking class invariants.
    In addition, users can manually program @c \#ifndef statements in their code
    using this macro to completely disable compilation of class invariants or
    use the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    Defining this macro is equivalent to defining both
    @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS} and
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extras.disable_contract_checking,
            Disable Contract Checking},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_INVARIANTS
#endif

#ifdef BOOST_CONTRACT_NO_OLDS
    #error "define NO_POSTCONDITIONS and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when old value copies are not to be
    performed.

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define both
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of old value copies or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    @see    @RefSect{tutorial.old_values, Old Values},
            @RefSect{advanced.old_values_copied_at_body,
            Old Values Copied at Body},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_OLDS
#endif

// Ctor pre checked separately and outside RAII so not part of this #define.
#ifdef BOOST_CONTRACT_NO_CONSTRUCTORS
    #error "define NO_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not checked for
    constructors.

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for constructors or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @note   Constructor preconditions are checked separately by
            @RefClass{boost::contract::constructor_precondition} so they are
            disabled by @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} instead.

    @see    @RefSect{tutorial.constructors, Constructors},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_CONSTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_DESTRUCTORS
    #error "define NO_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not checked for
    destructors.

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for destructors or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @see    @RefSect{tutorial.destructors, Destructors},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_DESTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #error "define NO_INVARIANTS, NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not checked for
    public functions.

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for public functions or
    use the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @see    @RefSect{tutorial.public_functions, Public Functions},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
#endif
    
#ifdef BOOST_CONTRACT_NO_FUNCTIONS
    #error "define NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not checked for
    non-member, private, or protected functions.

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for non-member,
    private and protected functions, or use the macros defined in
    @c boost/contract_macro.hpp (recommended only for applications where it is
    truly necessary to completely remove contract code compilation from
    production code).

    This macro is also used when contracts are not checked for private or
    protected functions, lambda functions, code blocks, loops, etc.

    @see    @RefSect{tutorial.non_member_functions, Non-Member Functions},
            @RefSect{advanced.private_and_protected_functions,
            Private and Protected Functions},
            @RefSect{advanced.lambdas__loops__code_blocks__and__constexpr__,
            Lambdas\, Loops\, Code Blocks},
            @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_FUNCTIONS
#endif

#ifdef BOOST_CONTRACT_NO_CONDITIONS
    #error "define NO_INVARIANTS, NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not checked for
    preconditions, postconditions, exceptions guarantees, and class invariants
    (excluding implementation checks).

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}, and
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS}.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts within specifications
    (so excluding implementation checks which are contracts within
    implementations instead), or use the macros defined in
    @c boost/contract_macro.hpp (recommended only for applications where it is
    truly necessary to completely remove contract code compilation from
    production code).

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_CONDITIONS
#endif

#ifdef BOOST_CONTRACT_NO_ALL
    #error "define NO_INVARIANTS, NO_PRECONDITIONS, NO_POSTCONDITIONS, NO_EXCEPTS, and NO_CHECKS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS) && \
        defined(BOOST_CONTRACT_NO_CHECKS)
    /**
    Automatically defined by this library when contracts are not checked at all
    (neither for specifications nor for implementations).

    This macro is not a configuration macro and this library will generate a
    compile-time error if users try to define it directly.
    This library will automatically define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}, and
    @RefMacro{BOOST_CONTRACT_NO_CHECKS}.
    For example, users can manually program @c \#ifndef statements in their code
    using this macro to avoid including the @c boost/contract.hpp header all
    together:

    @code
    #include <boost/contract/core/config.hpp>
    #ifndef BOOST_CONTRACT_NO_ALL
        #include <boost/contract.hpp>
    #endif
    @endcode
    
    Or, use the @c boost/contract_macro.hpp header and related macros instead
    (because the @c boost/contract_macro.hpp header is already optimized to not
    include other headers from this library when contracts are not checked, but
    recommended only for applications where it is truly necessary to completely
    remove contract code compilation from production code).

    @see    @RefSect{extras.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_ALL
#endif

#endif // #include guard


/* config.hpp
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
*/