
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
/g+SZMFBkzB8VnWt+PIY2WxhD06bEdFc4/RijlS25OUisG+vDwofUdND8u6OuVjIRuzXdvkYfAdwnfTWxsLwFPhYPl87RFyp6djLBj6sRgtL+/N+ceZz9n84U4spOHK9BhPWmHYLAZ2ff5T6e900Hjjy7mTWv9NMHION2UT8HIFSmPB9WbTJthntOzpCCDWC41S9GtS4f8q7kVFbjRMJtGJ2w+r9w2fCe5mPqKJmvEd9At/yGF/KnExiG1gSVTeNhsg8mOtPKxNHWPQieb2m6zd5AiFgqFukjQo0DWPOV1p5MHM8rYEvm9+hiO1YwIX3ja9OHaM7dGup5UFz4d33LQNpsad+U2Jzq2lhuMl7DccYo8TraFrmIyzGH0cYSh2HxFAWFF8hvFSdeB+0v1juVeQWZbUHKt/hGiTYUxeyoed3xLEiVNoH15U6djWQxpFAaXavBI6WgOysV3RjI0/G8hvkZ3osN6uBgUbnwVrNiQ6aQcHaALy6c2cBzya+zOWq+jTEUHethiHu3rc9tuyROxO2nPpKc9w9rC0JE9aViMGNBfGQaZYwVAyrQQQTNoQA+GaHhjkTg1gYTtS7ezXhYC+KAccrfdZACL8WmtpGikML2/PuZw1DxZ+XC2s+hYLa82Y5PT4NKV5h/qtzktc8e3nVYxWFD4z0fSK0X1Cqvr6Q9lUhcY96NiBefX7C6Do/gs2GcsltPJg6D1WNDYp141yn/losUb/lP2BGR7uo7uQcxrQXCL0U7jBT81YRUZ1G7fB5CUITgqY+UNVoUnnaADPSpt/fqgSYA5X0g5u+BYMG4l45yBgj084gqKIjMlU8fZdqf680CRpKsydfZScSl3yrk3ZdG63IJTftPNcHwox9nHLNveXZ9t7C+G+ML2OEgcB0s2Dyxt19Oe8+Vrofhq+2wk9Ygwc6vOgNqlH0ABel9eWB/Aiv3NIO7AGYW72BfQDTLpWB/LY0VWiQikTfD9qL1HyxQUfkpRJwVoZ0xaGVfMtDuu1ZHYt/xf3q0I624qSP4ZIzdzpD2yT+aQXjcpbsvpc8McX2nIwhCybxLdFKb4UZlStaidKPaZAcThH7BnGDEdg2QSVILyavfyADwGGWV81wuUkMYMbtLN64GZJBXETeziDD298UAB0s4tOxrZ89HNk0hbwKdmiRSwhL76MQPc3MnvEJA6xcIpKiMcq1VeRVyt6GMeSN7os/HxEVciOGyMbNM8qRG30jxja+lKXFZR0BNyiUux15k4DWirFCdp07YRaOBiKel+AykeBBPka9NHz5VFAqR7aNnsKJi8hAfqBvFR8CKPXPEsbLTCJcFZauqq4lVh8E93frdI3KVcXAHX3t4Ge94SdhAO3bVwnowSR8JRz/CGUzBB7afKU5GMm7jC9I6tJkwUwq5iKZwv2o01MEPoQVAkcJ6G/NH8Pp0LowO7fR7Xsg9+Nj8NIIdBnm+hIxDmu8SrWTRznc/mf7eodW4/2xWG19Jubw8dfQfhN7AZK8wRrXDIOILEeN96xBZr8O7/J23tdg/4/ITP7Rra40KiDt5tBdkJdMbvDIZqN5l6Hsh+fbHht7IOSJ8qIO7VmsnCRWlBKaY/tUvx3DotdAWebpLFejOKKKGhmNiU0X8Jfw9cqb7Ji9yj6d8SrOgNf9YdM4IPfss/BRHM3Ar09QAGyN8VuTRWzpv9k3o9YFmpqioBvVFBgA79FnWe0tacCjWSIQVpsYj+Jn21B4KGTQT+H81FA9QCYo8xkGDxyBPNhfjt85TAMVXsdDz9EejuJQ7tcP3G5BUEuChzQYJ+FlGm3FbWTn4ezwf2S3MK9PWtKAeblILHeA2NQ6gRtsFloLzOLIS4G2+ouEbqCC2W5g9KMYKZSLTjABvZNz10CEvTyALBrLV1wRXbm0+cjeEsw0enQXXCS6qyyH4ckpsnm09eeRBkuDPdKiv2k1yl4nihQ5Eu3xH7jLRYahlEIxSEcvIVSXkF8zq+5OKaQXixZgcsAuFR+E8Oy7bv9DMWRzF3fyAua68N0jJ8nQ9lH11GECkayQ8gfkoCmGDr32YblCUfsPPurQOMMq+5OTt2O+mIQIRuHavuXBDUewz6+iOwBBs0zr9sfuCHWjlzLqeYMI/PoN+7wFa7axf221KenfUKTx9vh7Own7+/42/s77QWjZSnqOcZZNHx5KYlz8w1jqrwItxTgBWh3ZqTqaAxeUoDGeYwZxNJZKF+oCMleOyXExAiZqtxRWwYgcUA/il96ia00ibq1YUBEKtueMo3kaMXtbbN5ABG652EczHifubquBAM1s5YRr2P7hqv86pXZtAPwrfIIVwMpBCCvjz7KGgU2H7sclGaZvsgREcNORk2muHMhwBgDprNzkH/JpeV9RZfkyxSQYbqqCHeOq+jKVoGeVq2kZbjTRiQXJImb9oYPy71ILQ5h0BPo8HpkXZdHakeR1DxfoQxHvAy2/4MRX+naeA2s3hwA+v8csLrFuGFroQJf+q1/jR8fgctFTdQg5fVrDgdKsYhq0Rdf9uLaVCZCmiMOMhWzgLGLwv03WTgqTcUQO97vHu93gT75rGC/yNvDMSKLEgmhlCtLqDgwJDuMme0gJHhnDHOjhu7vWGA95Xajm0rels8nx8I7YVMC9nIdDB1wo59YU4WEekgDWRlaog/FahqAejRG1vG9hQsdUNK8DRooNF0n510bBLKu02R4qQ1690K5f+x6U16jxFSYoe5Fxk29Aq2oURlSx5XTsQ+k6ibj7lSzIpRUnccI4Mojutjfg/WXyj8M3Lr436G//YTosxsn2ZSO2fkkBlf+7qSIQDHLEEPY0vQ86XkVJP0GQq11IgkkPcuKqPUTvs4c0eA9+T1DmvvzZ4EbW4QG7vgNx3Vsjs4/R1SIx7DTZzjE7VgKFJ/PvuHhoGSMQw4g444FD3ncNEQmiuVRh0epLWH5/3ymGwLtoYOB3XtwHI0HdYfdODSRLtimZkLWcIPIoOAQAIvFsQZJTsySOW0cymngqWmySmNF9eKurxPl69f35DHRaDUieGKU6ZHdFNe1NfUIS/XvqmydDt3yrdvBnv2q78QSUpOTiuGpYBIJZU3Cfwra1AqVTQEFcyqCI8cwuLlN373B1dxGRsfzn6GACYd3+ZJhKugOkDK20jiYyLrxnzY8CTcGR1CXIystHR6I5cSO0H7G65xcKD/1Vtivz08Hn0XFslovATWLYkBzClhGethDW92uWsSGqjuUhQCKt0BdBlummzXaIzRNz09OuSRXtO8iNvpi46yk3voItd8Cx3A2XNd3sIaNuVZonkf267aGzJxY9xXZjZ3VknfvAYVe9iatSQrz/0iB1AoagEck8nIMfbiXyQG6i0XBylGFPHtwHdB6mNKUcB6N50H2SAUnKFmweADVoui3zujzIPPvZUIbJg9qA5+FI1+T70fKURcdPUtxuQMRORnF8qDX7JO1BUxkIhwd8Fnqpuf2Dfjo5vyNb96wxR1GCdkvin7grhxw85ebZNzyAPNqxE25kXDFIbX6NR5x4YbOdl8thclRNZG28lsT/+1UE21JOspY/yC+jdtSGFDRjK1JrATYI7aKQoPiDkx3vrUUkfuBBgNPUdZGgcCG/ujj7RxEGuNtqKB5emW4iUVTQnpjlLZPY6uUlPo6dGEICAqjC3wm24HeAPyS4DkM0wVhNnuUO2CtzvVw/M/4FL8u/9BVsvuCWl6LOC0CcuQlcvgkRny08l/k7yOtLu2PcVK6uq7Z43iyCpF5CUPYIqwizHi1f2CozlpyxLx11mSqTmdd/PLmscRsyjOhfW9kik2FmOtH8pdcT/1lCjyGAwkdRKq3AalsrwMtLCN7wy0/8fZYYEST5oXvqHmFDaMZZk+SELZxdxPXVEWbeUiTIrY0dQIGifuavbIcKO2s7vydx8EiSfiZ7urfS99r7hAklqfhtwgXMgmfLKd5e4BKF6ncyaXCCbiVTQKtXCgT0pNdZF3SO2TvGJl+OZl93INjeQZbX6zg3oWiII/WbV2whbYk57+avgMT1iipnP9wpCsgpr5Pp7f0IvT5GBhlrcIfiCZ30frMKsvsmAYLelGAkmlnVMICGR/Fc7tOjCw+3Y0jZtI4h3cZDO8w7sSV8DggrRBtGmDs71nMNspFv5OnFjjushRX/34vJIRNo4TutcSS0/+stKhOyarDzATfl3+ARMccV6VzvQ8iHb57IBwc0ENl1PgLEax0zFIRLnRPj/J+UXzTLzkePLki94T74mYagOjbk+UQGdSkGjqFsi0JUDGuTdUztMIfiOGjX6Bwu5VnKJ4u2ilEirRtbMxpRdjXn+/IDTqnaCpKYaDjChFuNZHbPqb5ZPlPMSFabi6I3Ul65ghM/mDVRHbkoDCV7fCrZg8K1P0UQU4PjaUBvrQSrEjkc6cFyWF6j31ul3K9WFjds8Lua+Wcu1nQGPSPI6DJlvTjwo1prIFieiun4han3ZkcyfIHMHpUmmUk+ff0BGQJkM8unh0OhYdEuxVsUNL471btC5o7BbbnTOEaoGfSS4Q2SMvUxZxOsSJr9VQ4bjzMa9tm+AkI620XZB3hvzTeVdIz1BqNzaWM1Ikn+FiObfuiEFYQ1OoshzAX0QRNddFyqloLI3AvX5Bqfd9BAyl1XezCgCTdfIF3n1mrlh6hmNQ26u7RJs0phTyhW2A9GmnUiCsFJLyT26dqSo0A3oImsL3ALe9oqKOxWBVVAEpeEm4sBnn2JXO/1AnIwb1AIYAZySs4z3+AivvGQw9FIw7LZEKCcbzfSnPytImj2yXb94Sk97V7Qegv30dnKy4/T3UwC0mlSJQ9Be7jYPmsJTLU1hshFfK+dwe2xh1A7QMQixBI0mVojXENJdXY4AeaIbu0ILLtuOO1Y+AGv9K3M4SH2A752PkKJVCDjpqonaoMKXPu+BfrYUDP8HNFOnkuPWH2UZ9u+iqw2zBmL1qgP6+SM/lwxme/byjeM8Z+qrNLhk3t7bMdpQ4CyfVVRmKrqBlEzRshdnyJF3tCP4IVHE7YxmIsDeRcDLa3IMMeBYpo+8HXEx0H+NE4T9lPcAOGjo3mhgmMjY8ydkTL42Z5PDEEQlPEQCBga3DXAhqzfBWY3TbWBJYBw6KjKnQ/eOs/VzF6CKoc+omoIAEbO0mOGlv67hy+StZv/GFzT9zGosessZgXIuLt9QuZuHxB2T775XAjbpvWxLL74/+HLCB83z4nbwfNtlQY5DuKJkFKrsed6d2uPjz2aXACiSGLy2IJIPmaeQXyg5jn4aePEAwofp9El6Ty6XFVziNIyUiSkh9mzU7A4+h3N8AJl3F9Xz7DOLHNmllVoE5u1QEUnEyDsD1siQJRiUqLIPQ622h+bsLhvwtfZKlK7fyW3R1hYLS+Z9o6Uxl5UaYLqGIErPynwHP9W+0hKo0o1lCQ4MYpsX6+vk5kk1lqA9qzNOwbrtDVidv7JKuDS626BMtDktwwaaqTgbGQTl+hSxkNL7XwYUxKFmsBdXQ6X4WzPUwbWKrKsHz1I7R4nB0T078chS9SEw06tIr03/MLkTtxYAKiNMIm4jxb+1vAua4jROrPQmtYy2rXo7VfbDIDEWs5jYT2st8Edg3p5EjluaGu4d+X71U1enQ8O+ZxE85rTs2rKj++2x+0WkdU9F869tpXvIEzY8vfqyKnlRk1hHjz7U1lusjwKiBUOAnB06/lDNJRFDWEKtZYr1A3oKvWMHZX7aRpxJqRUNFhlfBR5slG+hNBcoM6kyrsQx4mw3I17o8GNywRfKNd8aSjLgl0cL+iibLaJZbnyQmxhxaWJ0Z2IENaiB6xwHfueJ/lUjNHFAhGojr+bJhQpkzpb1gEAdSBpS7baL/800pDTfFUo/x5pXEghd6Vq/cD7DHG0MvqTQLhfI+b4BX343TAGezy+LLyvUwYeykK3ItGrpMLqCAKE9eSwFIYO7bzZVKqsd53nlltqBqgGXBQ3XRMsN1VSlSrOdNnoH1zc3EQXqGazGTQXiYtZvmP9G337W9mHAVp26c5xdquVgTRofHXciHvaT+CcT4ZqzhjZjxRcgQHtQXMZhzaTAY6I93i7SG5PgXQV/C2w2PdPbHcc2Hq9zybwRVavC+qhoABUtGVfQwo2CyVFTxQuCchXDAlSkeud3nBVQ8KelzdS5X7bRT38r51iHr3wG/wXb/iDhMtP//2M/7/Qvx3/fyUa//3pr//7y0/4TV/+dPkv+P/nn/7G/02Tc/n5p+e/48+f4d8vf/+K/+G+l7/g4X/59b/h/1//k+7z1//0k379Mz7F5ddnvOvfkfny09c/4Q9e5sv/g3//g6f+7zb/A37oD/fEXP7h1/i/P33BGz+uWt9I1K+dQNeKGe5SEdrlEjWQ0eSzQrJgm8Mp2Mw+rvbNXR7BRORiwyGUbLx5eXSH0r3EOkSJvcHyrSZ0vY8hrdNVDyWqs9GxEOacKDBhhTxyn5UR51R3TkIpXOcujznkyNKXRAa0Bm1XI8jRJ61C7kMuj9Uzj+JajeMuj/UMOtqU/mw49NRM1F0scMeI1fSx9XofNroX0b1HM/LBOOB7yKn2NJcHDJ03OwcBKS9cJQKkHRqP7GzECaBXe2iSD99palgNDozot6KzeuPg0zflnJH7DT2x7U/ChaVuhZbFYi+w2Gowy+Q+N6y5Abug18FShe65mAE9SWmNisFAqVpQKFqo9wtv7dX2KzDUDQuE+spYj6ngqZ6IKa/skiS+hq29aVdNqI7jekn/gf/SlEjTzfMrwPrVJey1SgVEVY6oNaEdd7VkIjzBw95pNkQwBAEhjMWBJqacW2SOeEs1eVPZWjDEs3lAc+iPFAwMEOpSkB3Pvm+enmso6PjAGijgzVbiAG1yCAfC1T5WiD4WkREKtw8zWY24gvZ9I6OBlRRUqbUWJTCCeKz8W4UEaMRd/vyQsAgOhp4vhkoX0nKhFgREWmLVo2zDGIJNgwdpYQdGCPQOVF1Y4zAQsrekuTlCOCaE/WPdA0oc6p3kFudNEruaCOiWQohho2KWj74cNXCRvqVtDQWN7C0dYXIspNleIyanL/GNcbJXG61fzHfjtqSnM6PV43oVx0Ys0l5bu7cyifsLyWZkrcEhditD65dF7xRr4y8LfWzLb8uv45rFKxy1hwhD/CPAm8RpuqQX3PYzelskhNZ5QnmXm7+IxRJKSdbnScYrrH4JvoLImjvsi1TNrsSmV0AzvO3wQ2MYA8Q7eWkgyb5HkqFGWmQjoXRBT6Cu0S1nJhC4mbD3uwuVe39UMgkY91A7mKNRsGOc7ktMAWRkgTKUrlI7PHjQM0uKaMNFi3Qi0WeoRW38nGp+4jDhjaKG+bNOTybIIVNvuxcuqUkHl1jTpEV/lSn3h9hLAiKjcpWKfMONqbNAzjCUyk+ry+KioiZ4hf2SOqgq8mwksqRtQbelNYhQaC/ik0QIdf17wUHUzzLJvaRevkt7pz0an6AXVG2nyBIvd52/Gowm18b0+7dp1hz2Gf9jHErGKOFKxVWLfJBlZgZB+GfRhTSC4YkxLnKo9OO1GmemsZcpC0nyHOg0jwUyRJXsInBn5ID9ogdNld33/fOP6IuRbx/bYs0uEWRJwGdNE+b/wmKWs0BKq08agdiqcYdA6+YRRzs2ZlzNL9iU/ISXquUWIoUACJHePh2593O2uYuR6NPSB8gVbUVgpLq5dAoGmD6/AHacW5sWKNQzaDIq21wF6/RCEY5fmJgfIQdzarSdxUAO60sKwLwDEpaPB6UY1qpiVj1GAtpy/ZnTPW163Xva7Hudr1KRQdDPlESVdHYAct92j+9Ww+br+xxycZU5RqAae5iG1veh9pr+h0naXzzOgYvVZm60Cs5sQ0dCOOfLDzilXnMMJnTBYa7kv118xDq3svlI0eH7gxhnFjZe7UcR56RLPlQNeWErMj3FZpgkrr7JMxBW+dDqyr5pqOzQsX2T2wjgw6bXNL3C2QTIgyMftGgRLKpWljsto84qWO6SrYcI06OqOB7ChJ3/+2N7HfU2eWWt/RJgtr5lXjY0Sr64HMoDiurJJCixLya37JhBr+rFieH79NYsK48ee4rbvRL3lvrWT/Wr3FqNbaCA9v4FTFtRNQ/E+G7riqlLz3l99F36DOhbVv6dtjwlrVWHVeNyBEkF9X8j9fQV+lAtTJaVJy/s3MAwcv/cyNiDv7ZVazjfn6wZuOPwsuhbvofZDIMwojBCpyTzHau8TNMBzWlqVSpekPf9NF02KvmXcIevzlQFAEs360RjvnPI12uYSQJHO26vvMrk5zkdpg5Af+zWQcpnj9aRycUjhe+ciJDThaJINnb0ZMNPVPRfVGq2rBe/JvXb8H8sebPuAEFwGRAIHX0AEeKbEIaM3sPrQAYDaQQVC3DtPuoFLHcoMWfHtT6SoBWKwWVr3xHsZRPFLWJdzOv16JkD3AVrBmNpH8b4VFHuwBA4aOhkQLhkfdKcYguw5J1/3pKpmhLGp3tycVtyU2Twvew6fMKwDziu0iwiXPLm7cISQh0iKnYiZoRF/TQXbQQXmBfaAjzCDgc5RdwEE1G+bx+nQd1yoGJ09Eq6HAN7fimD5+rg7Ql6pcJrTihtaTSB8ynFsyYpthU//bE1GpHo3gNk9HJwN6/+argA1iZZTUOz9SuMzcI4iagwPEM85FkLAgcllmcmejIcmu2SbjWJaJpT1y00FPND8p1/dbyJnjw0trUPenBtCQesdtqBERdxKrSHx30bZT+1ghvuYzc1G5KhQRCk5dcdthGH0GKNtADJdc+O+S1bhr0dWfsxv0KDRHJUajPyXFUOKREfjy2C2BgRrg7FEM7Q8a1sHRkve9z1NzzUFEtiOnmBU+q8o/gzr02V8ifToAuqUQsbrP9W44131yEzXnUYKrIcCUPkg6U9lxfp/NdDGjJ0JN/g8g+KI0zVNB3l2zj3oQyw+usrYjnweuFvcgUZVd6G0VscAvzOb7e0csVnlDc5TyvtlmiTHIt93nfjGSwMBmV/b191LAA1WJ8TXbj2dvC91UVmQE2YgDBYyd2DZ1jYW/IKXlHCjBjNUZQZ8lkDufopoy1nA+pd0DYD/Z/sJrSVenLreQWYcyOFDL2mVxqMguRtJKLkCZB91T8BvA2prw4lQqddgO8yRN6ytt3bzuOu7dhEPcbeKEiatGPcZUtIjfxD2Xf9gFjylMM=
*/