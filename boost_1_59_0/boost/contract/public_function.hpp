
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for public functions (including subcontracting).
The different overloads handle public functions that are static, virtual void,
virtual non-void, overriding void, and overriding non-void.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/virtual.hpp>
/** @cond */
// Needed within macro expansions below instead of defined(...) (PRIVATE macro).
#if !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_ 1
#else
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_ 0
#endif
/** @endcond */
#include <boost/contract/detail/decl.hpp>
#include <boost/contract/detail/tvariadic.hpp>
#if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
    #include <boost/contract/detail/operation/static_public_function.hpp>
    #include <boost/contract/detail/operation/public_function.hpp>
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/function_types/result_type.hpp>
    #include <boost/function_types/function_arity.hpp>
    #include <boost/optional.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/type_traits/is_same.hpp>
    #include <boost/static_assert.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
#endif
#if !BOOST_CONTRACT_DETAIL_TVARIADIC
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
#endif
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

namespace boost { namespace contract {

// NOTE: Override and (optionally) VirtualResult allowed only when v is present
// because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e.,
//   Override might be present only if v is also present). However, the first
//   appearing virtual func (e.g., in root class) will not override any
//   previously declared virtual func so does not need Override (i.e., Override
//   always optional).
//   Furthermore, F needs to be specified only together with Override.
// * VirtualResult is only used for virtual functions (i.e., VirtualResult might
//   be present only if v is also present).
//   However, VirtualResult is never specified, not even for virtual functions,
//   when the return type is void (i.e., VirtualResult always optional).

/**
Program contracts for static public functions.

This is used to specify preconditions, postconditions, exception guarantees, old
value copies at body, and check static class invariants for static public
functions:

@code
class u {
    friend class boost::contract::access;

    static void static_invariant() { // Optional (as for non-static).
        BOOST_CONTRACT_ASSERT(...);
        ...
    }

public:
    static void f(...) {
        boost::contract::old_ptr<old_type> old_var;
        boost::contract::check c = boost::contract::public_function<u>()
            .precondition([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            .old([&] { // Optional.
                old_var = BOOST_CONTRACT_OLDOF(old_expr);
                ...
            })
            .postcondition([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            .except([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
        ;

        ... // Function body.
    }
    
    ...
};
@endcode

For optimization, this can be omitted for static public functions that do not
have preconditions, postconditions and exception guarantees, within classes that
have no static invariants.

@see @RefSect{tutorial.static_public_functions, Static Public Functions}

@tparam Class   The type of the class containing the static public function
                declaring the contract.
                This template parameter must be explicitly specified for static
                public functions (because they have no object @c this so there
                is no function argument from which this type template parameter
                can be automatically deduced by C++).

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the static public function body (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
template<class Class>
specify_precondition_old_postcondition_except<> public_function() {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
        return specify_precondition_old_postcondition_except<>(
            new boost::contract::detail::static_public_function<Class>());
    #else
        return specify_precondition_old_postcondition_except<>();
    #endif
}

/**
Program contracts for public functions that are not static, not virtual, and do
not not override.

This is used to specify preconditions, postconditions, exception guarantees, old
value copies at body, and check class invariants for public functions that are
not static, not virtual, and do not override:

@code
class u {
    friend class boost::contract::access;

    void invariant() const { // Optional (as for static and volatile).
        BOOST_CONTRACT_ASSERT(...);
        ...
    }

public:
    void f(...) {
        boost::contract::old_ptr<old_type> old_var;
        boost::contract::check c = boost::contract::public_function(this)
            .precondition([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            .old([&] { // Optional.
                old_var = BOOST_CONTRACT_OLDOF(old_expr);
                ...
            })
            .postcondition([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
            .except([&] { // Optional.
                BOOST_CONTRACT_ASSERT(...);
                ...
            })
        ;

        ... // Function body.
    }
    
    ...
};
@endcode

For optimization, this can be omitted for public functions that do not have
preconditions, postconditions and exception guarantees, within classes that have
no invariants.

@see @RefSect{tutorial.public_functions, Public Functions}

@param obj  The object @c this from the scope of the enclosing public function
            declaring the contract.
            This object might be mutable, @c const, @c volatile, or
            <c>const volatile</c> depending on the cv-qualifier of the enclosing
            function (volatile public functions will check volatile class
            invariants, see
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).

@tparam Class   The type of the class containing the public function declaring
                the contract.
                (Usually this template parameter is automatically deduced by C++
                and it does not need to be explicitly specified by programmers.)

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the public function body (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
template<class Class>
specify_precondition_old_postcondition_except<> public_function(Class* obj) {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
        return specify_precondition_old_postcondition_except<>(
            new boost::contract::detail::public_function<
                boost::contract::detail::none,
                boost::contract::detail::none,
                boost::contract::detail::none,
                Class
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_MAX_ARGS)
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_MAX_ARGS,
                    boost::contract::detail::none
                )
            >(
                static_cast<boost::contract::virtual_*>(0),
                obj,
                boost::contract::detail::none::value()
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_MAX_ARGS)
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_MAX_ARGS,
                    boost::contract::detail::none::value()
                )
            )
        );
    #else
        return specify_precondition_old_postcondition_except<>();
    #endif
}

/** @cond */

// For non-static, virtual, and non-overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_( \
        has_virtual_result) \
    template< \
        BOOST_PP_EXPR_IIF(has_virtual_result, typename VirtualResult) \
        BOOST_PP_COMMA_IF(has_virtual_result) \
        class Class \
    > \
    specify_precondition_old_postcondition_except< \
            BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)> \
    public_function( \
        virtual_* v \
        BOOST_PP_COMMA_IF(has_virtual_result) \
        BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult& r) \
        , Class* obj \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_, \
            /* no F... so cannot enforce contracted F returns VirtualResult */ \
            return (specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>( \
                new boost::contract::detail::public_function< \
                    boost::contract::detail::none, \
                    BOOST_PP_IIF(has_virtual_result, \
                        VirtualResult \
                    , \
                        boost::contract::detail::none \
                    ), \
                    boost::contract::detail::none, \
                    Class \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_MAX_ARGS) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_MAX_ARGS, \
                        boost::contract::detail::none \
                    ) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_virtual_result, \
                        r \
                    , \
                        boost::contract::detail::none::value() \
                    ) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_MAX_ARGS) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_MAX_ARGS, \
                        boost::contract::detail::none::value() \
                    ) \
                ) \
            )); \
        , \
            return specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>(); \
        ) \
    }

/** @endcond */
    
#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts for void virtual public functions that do not override.

    This is used to specify preconditions, postconditions, exception guarantees,
    old value copies at body, and check class invariants for public functions
    that are virtual, do not override, and return @c void:

    @code
    class u {
        friend class boost::contract::access;

        void invariant() const { // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        }

    public:
        void f(..., boost::contract::virtual_* v = 0) {
            boost::contract::old_ptr<old_type> old_var;
            boost::contract::check c = boost::contract::public_function(v, this)
                .precondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .old([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                .postcondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .except([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ;

            ... // Function body.
        }
        
        ...
    };
    @endcode

    A virtual public function should always call
    @RefFunc{boost::contract::public_function} otherwise this library will not
    be able to correctly use it for subcontracting.

    @see @RefSect{tutorial.virtual_public_functions, Virtual Public Functions}
    
    @param v    The trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and default value
                @c 0 from the enclosing virtual public function.
    @param obj  The object @c this from the scope of the enclosing virtual
                public function declaring the contract.
                This object might be mutable, @c const, @c volatile, or
                <c>const volatile</c> depending on the cv-qualifier of the
                enclosing function (volatile public functions will check
                volatile class invariants, see
                @RefSect{extras.volatile_public_functions,
                Volatile Public Functions}).

    @tparam Class   The type of the class containing the virtual public function
                    declaring the contract.
                    (Usually this template parameter is automatically deduced by
                    C++ and it does not need to be explicitly specified by
                    programmers.)
    
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::check} declared explicitly (i.e., without
            using C++11 @c auto declarations) and locally just before the code
            of the public function body (otherwise this library will generate a
            run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
    */
    template<class Class>
    specify_precondition_old_postcondition_except<> public_function(
            virtual_* v, Class* obj);
    
    /**
    Program contracts for non-void virtual public functions that do not
    override.

    This is used to specify preconditions, postconditions, exception guarantees,
    old value copies at body, and check class invariants for public functions
    that are virtual, do not override, and do not return @c void:
    
    @code
    class u {
        friend class boost::contract::access;

        void invariant() const { // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        }

    public:
        t f(..., boost::contract::virtual_* v = 0) {
            t result;
            boost::contract::old_ptr<old_type> old_var;
            boost::contract::check c = boost::contract::public_function(
                    v, result, this)
                .precondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .old([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                .postcondition([&] (t const& result) { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .except([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ;

            ... // Function body (use `return result = return_expr`).
        }
        
        ...
    };
    @endcode

    A virtual public function should always call
    @RefFunc{boost::contract::public_function} otherwise this library will not
    be able to correctly use it for subcontracting.

    @see @RefSect{tutorial.virtual_public_functions, Virtual Public Functions}
    
    @param v    The trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and default value
                @c 0 from the enclosing virtual public function.
    @param r    A reference to the return value of the enclosing virtual public
                function declaring the contract.
                This is usually a local variable declared by the enclosing
                virtual public function just before the contract, but
                programmers must set it to the actual value being returned by
                the function at each @c return statement.
    @param obj  The object @c this from the scope of the enclosing virtual
                public function declaring the contract.
                This object might be mutable, @c const, @c volatile, or
                <c>const volatile</c> depending on the cv-qualifier of the
                enclosing function (volatile public functions will check
                volatile class invariants, see
                @RefSect{extras.volatile_public_functions,
                Volatile Public Functions}).
    
    @tparam VirtualResult   This type must be the same as, or compatible with,
                            the return type of the enclosing virtual public
                            function declaring the contract (this library might
                            not be able to generate a compile-time error if
                            these types mismatch, but in general that will cause
                            run-time errors or undefined behaviour).
                            Alternatively,
                            <c>boost::optional<<i>return-type</i>></c> can also
                            be used (see
                            @RefSect{advanced.optional_return_values,
                            Optional Return Values}).
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    @tparam Class   The type of the class containing the virtual public function
                    declaring the contract.
                    (Usually this template parameter is automatically deduced by
                    C++ and it does not need to be explicitly specified by
                    programmers.)
    
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::check} declared explicitly (i.e., without
            using C++11 @c auto declarations) and locally just before the code
            of the public function body (otherwise this library will generate a
            run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
    */
    template<typename VirtualResult, class Class>
    specify_precondition_old_postcondition_except<VirtualResult>
    public_function(virtual_* v, VirtualResult& r, Class* obj);
#else
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(
            /* has_virtual_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(
            /* has_virtual_result = */ 1)
#endif

/** @cond */

// For non-static, virtual, and overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_( \
        z, arity, arity_compl, has_virtual_result) \
    BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
        arity, /* is_friend = */ 0, has_virtual_result, \
        Override, VirtualResult, F, Class, Args, \
        v, r, /* f */ BOOST_PP_EMPTY(), obj, args \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_, \
            { /* extra scope paren to expand STATIC_STATIC emu on same line */ \
                /* assert not strictly necessary as compilation will fail */ \
                /* anyways, but helps limiting cryptic compiler's errors */ \
                BOOST_STATIC_ASSERT_MSG( \
                    /* -2 for both `this` and `virtual_*` extra parameters */ \
                    ( \
                        boost::function_types::function_arity<F>::value - 2 \
                    == \
                        BOOST_CONTRACT_DETAIL_TVARIADIC_SIZEOF(arity, Args) \
                    ), \
                    "missing one or more arguments for specified function" \
                ); \
            } \
            { /* extra scope paren to expand STATIC_STATIC emu on same line */ \
                /* assert consistency of F's result type and VirtualResult */ \
                BOOST_PP_IIF(has_virtual_result, \
                    BOOST_STATIC_ASSERT_MSG \
                , \
                    BOOST_PP_TUPLE_EAT(2) \
                )( \
                    (boost::is_same< \
                        typename boost::remove_reference<typename boost:: \
                                function_types::result_type<F>::type>::type, \
                        typename boost::contract::detail:: \
                                remove_value_reference_if_optional< \
                            VirtualResult \
                        >::type \
                    >::value), \
                    "mismatching result type for specified function" \
                ); \
            } \
            { /* extra scope paren to expand STATIC_STATIC emu on same line */ \
                /* assert this so lib can check and enforce override */ \
                BOOST_STATIC_ASSERT_MSG( \
                    boost::contract::access::has_base_types<Class>::value, \
                    "enclosing class missing 'base-types' typedef" \
                ); \
            } \
            return (specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>( \
                new boost::contract::detail::public_function< \
                    Override, \
                    BOOST_PP_IIF(has_virtual_result, \
                        VirtualResult \
                    , \
                        boost::contract::detail::none \
                    ), \
                    F, \
                    Class \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, Args) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::detail::none) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_virtual_result, \
                        r \
                    , \
                        boost::contract::detail::none::value() \
                    ) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, args) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::detail::none::value()) \
                ) \
            )); \
        , \
            return specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>(); \
        ) \
    }

/** @endcond */

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Program contracts for void public functions overrides (virtual or not).

    This is used to specify preconditions, postconditions, exception guarantees,
    old value copies at body, and check class invariants for public function
    overrides (virtual or not) that return @c void:
    
    @code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b, private w
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

        void invariant() const { // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        }

        BOOST_CONTRACT_OVERRIDES(f)

    public:
        // Override from `b::f`.
        void f(t_1 a_1, ..., t_n a_n, boost::contract::virtual_* v = 0) {
            boost::contract::old_ptr<old_type> old_var;
            boost::contract::check c = boost::contract::public_function<
                    override_f>(v, &u::f, this, a_1, ..., a_n)
                .precondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .old([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                .postcondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .except([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ;

            ... // Function body.
        }
        
        ...
    };
    @endcode

    A public function override should always call
    @RefFunc{boost::contract::public_function} otherwise this library will not
    be able to correctly use it for subcontracting.

    @see    @RefSect{tutorial.public_function_overrides__subcontracting_,
            Public Function Overrides}
    
    @param v    The trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and default value
                @c 0 from the enclosing public function override.
    @param f    A pointer to the enclosing public function override declaring
                the contract (but see @RefSect{advanced.function_overloads,
                Function Overloads}).
    @param obj  The object @c this from the scope of the enclosing public
                function override declaring the contract.
                This object might be mutable, @c const, @c volatile, or
                <c>const volatile</c> depending on the cv-qualifier of the
                enclosing function (volatile public functions will check
                volatile class invariants, see
                @RefSect{extras.volatile_public_functions,
                Volatile Public Functions}).
    @param args All arguments passed to the enclosing public function override
                declaring the contract (by reference and in the order they
                appear in the enclosing function declaration), but excluding the
                trailing argument @c v.

    @tparam Override    The type trait <c>override_<i>function-name</i></c>
                        declared using the @RefMacro{BOOST_CONTRACT_OVERRIDE} or
                        related macros.
                        This template parameter must be explicitly specified
                        (because there is no function argument from which it can
                        be automatically deduced by C++).
    @tparam F   The function pointer type of the enclosing public function
                override declaring the contract.
                (Usually this template parameter is automatically deduced by
                C++ and it does not need to be explicitly specified by
                programmers.)
    @tparam Class   The type of the class containing the virtual public function
                    declaring the contract.
                    (Usually this template parameter is automatically deduced by
                    C++ and it does not need to be explicitly specified by
                    programmers.)
    @tparam Args    The types of all parameters passed to the enclosing public
                    function override declaring the contract, but excluding the
                    trailing parameter type <c>boost::contract::virtual_*</c>.
                    On compilers that do not support variadic templates, this
                    library internally implements this function using
                    preprocessor meta-programming (in this case, the maximum
                    number of supported arguments is defined by
                    @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
                    (Usually these template parameters are automatically deduced
                    by C++ and they do not need to be explicitly specified by
                    programmers.)

    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::check} declared explicitly (i.e., without
            using C++11 @c auto declarations) and locally just before the code
            of the public function body (otherwise this library will generate a
            run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
    */
    template<class Override, typename F, class Class, typename... Args>
    specify_precondition_old_postcondition_except<> public_function(
            virtual_* v, F f, Class* obj, Args&... args);

    /**
    Program contracts for non-void public functions overrides (virtual or not).

    This is used to specify preconditions, postconditions, exception guarantees,
    old value copies at body, and check class invariants for public function
    overrides (virtual or not) that do not return @c void:
    
    @code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b, private w
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

        void invariant() const { // Optional (as for static and volatile).
            BOOST_CONTRACT_ASSERT(...);
            ...
        }

        BOOST_CONTRACT_OVERRIDES(f)

    public:
        // Override from `b::f`.
        t f(t_1 a_1, ..., t_n a_n, boost::contract::virtual_* v = 0) {
            t result;
            boost::contract::old_ptr<old_type> old_var;
            boost::contract::check c = boost::contract::public_function<
                    override_f>(v, result, &u::f, this, a_1, ..., a_n)
                .precondition([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .old([&] { // Optional.
                    old_var = BOOST_CONTRACT_OLDOF(v, old_expr);
                    ...
                })
                .postcondition([&] (t const& result) { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
                .except([&] { // Optional.
                    BOOST_CONTRACT_ASSERT(...);
                    ...
                })
            ;

            ... // Function body (use `return result = return_expr`).
        }
        
        ...
    };
    @endcode

    A public function override should always call
    @RefFunc{boost::contract::public_function} otherwise this library will not
    be able to correctly use it for subcontracting.

    @see    @RefSect{tutorial.public_function_overrides__subcontracting_,
            Public Function Overrides}
    
    @param v    The trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and default value
                @c 0 from the enclosing public function override.
    @param r    A reference to the return value of the enclosing public function
                override declaring the contract.
                This is usually a local variable declared by the enclosing
                public function override just before the contract, but
                programmers must set it to the actual value being returned by
                the function at each @c return statement.
    @param f    A pointer to the enclosing public function override declaring
                the contract (but see @RefSect{advanced.function_overloads,
                Function Overloads}).
    @param obj  The object @c this from the scope of the enclosing public
                function override declaring the contract.
                This object might be mutable, @c const, @c volatile, or
                <c>const volatile</c> depending on the cv-qualifier of the
                enclosing function (volatile public functions will check
                volatile class invariants, see
                @RefSect{extras.volatile_public_functions,
                Volatile Public Functions}).
    @param args All arguments passed to the enclosing public function override
                declaring the contract (by reference and in the order they
                appear in the enclosing function declaration), but excluding the
                trailing argument @c v.

    @tparam Override    The type trait <c>override_<i>function-name</i></c>
                        declared using the @RefMacro{BOOST_CONTRACT_OVERRIDE} or
                        related macros.
                        This template parameter must be explicitly specified
                        (because there is no function argument from which it can
                        be automatically deduced by C++).
    @tparam VirtualResult   This type must be the same as, or compatible with,
                            the return type of the enclosing public function
                            override declaring the contract (this library might
                            not be able to generate a compile-time error if
                            these types mismatch, but in general that will cause
                            run-time errors or undefined behaviour).
                            Alternatively,
                            <c>boost::optional<<i>return-type</i>></c> can also
                            be used (see
                            @RefSect{advanced.optional_return_values,
                            Optional Return Values}).
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    @tparam F   The function pointer type of the enclosing public function
                override declaring the contract.
                (Usually this template parameter is automatically deduced by
                C++ and it does not need to be explicitly specified by
                programmers.)
    @tparam Class   The type of the class containing the virtual public function
                    declaring the contract.
                    (Usually this template parameter is automatically deduced by
                    C++ and it does not need to be explicitly specified by
                    programmers.)
    @tparam Args    The types of all parameters passed to the enclosing public
                    function override declaring the contract, but excluding the
                    trailing parameter type <c>boost::contract::virtual_*</c>.
                    On compilers that do not support variadic templates, this
                    library internally implements this function using
                    preprocessor meta-programming (in this case, the maximum
                    number of supported arguments is defined by
                    @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
                    (Usually these template parameters are automatically deduced
                    by C++ and they do not need to be explicitly specified by
                    programmers.)

    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::check} declared explicitly (i.e., without
            using C++11 @c auto declarations) and locally just before the code
            of the public function body (otherwise this library will generate a
            run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
    */
    template<class Override, typename VirtualResult, typename F, class Class,
            typename... Args>
    specify_precondition_old_postcondition_except<VirtualResult>
    public_function(virtual_* v, VirtualResult& r, F f, Class* obj,
            Args&... args);

#elif BOOST_CONTRACT_DETAIL_TVARIADIC
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1, /* arity = */ ~,
            /* arity_compl = */ ~, /* has_virtual_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1, /* arity = */ ~,
            /* arity_compl = */ ~, /* has_virtual_result = */ 1)

#else
    /* PRIVATE */

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_( \
            z, arity, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, arity, \
                BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), ~)
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, \
            arity, arity_compl, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_virtual_result = */ 0) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_virtual_result = */ 1)

    /* CODE */

    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS),
            BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_, ~)
#endif

} } // namespace

#endif // #include guard


/* public_function.hpp
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
*/