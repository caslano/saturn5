
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