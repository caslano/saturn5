
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_LOCAL_FUNCTION_AUX_FUNCTION_HPP_
#       define BOOST_LOCAL_FUNCTION_AUX_FUNCTION_HPP_

#       include <boost/local_function/config.hpp>
#       include <boost/local_function/aux_/member.hpp>
#       include <boost/call_traits.hpp>
#       include <boost/typeof/typeof.hpp>
#       include <boost/config.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/repeat.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>
#       include <boost/preprocessor/punctuation/comma_if.hpp>
#       include <boost/preprocessor/arithmetic/add.hpp>
#       include <boost/preprocessor/arithmetic/sub.hpp>
#       include <boost/preprocessor/arithmetic/inc.hpp>
#       include <boost/preprocessor/control/iif.hpp>
#       include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_FUNCTION_THIS_FILE_ \
    "boost/local_function/aux_/function.hpp"

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (init_call) )

#define BOOST_LOCAL_FUNCTION_AUX_typename_seq(z, n, unused) \
    (typename)

#define BOOST_LOCAL_FUNCTION_AUX_arg_type(z, arg_n, unused) \
    BOOST_PP_CAT(Arg, arg_n)

#define BOOST_LOCAL_FUNCTION_AUX_arg_typedef(z, arg_n, unused) \
    typedef \
        BOOST_LOCAL_FUNCTION_AUX_arg_type(z, arg_n, ~) \
        /* name must follow Boost.FunctionTraits arg1_type, arg2_type, ... */ \
        BOOST_PP_CAT(BOOST_PP_CAT(arg, BOOST_PP_INC(arg_n)), _type) \
    ;

#define BOOST_LOCAL_FUNCTION_AUX_comma_arg_tparam(z, arg_n, unused) \
    , typename BOOST_LOCAL_FUNCTION_AUX_arg_type(z, arg_n, ~)

#define BOOST_LOCAL_FUNCTION_AUX_arg_param_type(z, arg_n, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    typename ::boost::call_traits< \
        BOOST_LOCAL_FUNCTION_AUX_arg_type(z, arg_n, ~) \
    >::param_type

#define BOOST_LOCAL_FUNCTION_AUX_arg_name(z, arg_n, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    BOOST_PP_CAT(arg, arg_n)

#define BOOST_LOCAL_FUNCTION_AUX_arg_param_decl(z, arg_n, unused) \
    BOOST_LOCAL_FUNCTION_AUX_arg_param_type(z, arg_n, 0 /* no leading comma */)\
    BOOST_LOCAL_FUNCTION_AUX_arg_name(z, arg_n, 0 /* no leading comma */)

#define BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, unused) \
    BOOST_PP_CAT(Bind, bind_n)

#define BOOST_LOCAL_FUNCTION_AUX_comma_bind_type(z, bind_n, unused) \
    , BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~)

#define BOOST_LOCAL_FUNCTION_AUX_comma_bind_ref(z, bind_n, unused) \
    , BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~) &

#define BOOST_LOCAL_FUNCTION_AUX_comma_bind_tparam(z, bind_n, unused) \
    , typename BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~)

#define BOOST_LOCAL_FUNCTION_AUX_bind_name(z, bind_n, unused) \
    BOOST_PP_CAT(bing, bind_n)

#define BOOST_LOCAL_FUNCTION_AUX_comma_bind_param_decl(z, bind_n, unused) \
    , \
    BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~) & \
    BOOST_LOCAL_FUNCTION_AUX_bind_name(z, bind_n, ~)
    
#define BOOST_LOCAL_FUNCTION_AUX_bind_member(z, bind_n, unsued) \
    BOOST_PP_CAT(BOOST_LOCAL_FUNCTION_AUX_bind_name(z, bind_n, ~), _)

#define BOOST_LOCAL_FUNCTION_AUX_comma_bind_member_deref(z, bind_n, unsued) \
    , member_deref< BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~) >( \
            BOOST_LOCAL_FUNCTION_AUX_bind_member(z, bind_n, ~))

#define BOOST_LOCAL_FUNCTION_AUX_bind_member_init(z, bind_n, unused) \
    BOOST_LOCAL_FUNCTION_AUX_bind_member(z, bind_n, ~) = member_addr( \
            BOOST_LOCAL_FUNCTION_AUX_bind_name(z, bind_n, ~));

#define BOOST_LOCAL_FUNCTION_AUX_bind_member_decl(z, bind_n, unused) \
    /* must be ptr (not ref) so can use default constr */ \
    typename member_type< \
        BOOST_LOCAL_FUNCTION_AUX_bind_type(z, bind_n, ~) \
    >::pointer BOOST_LOCAL_FUNCTION_AUX_bind_member(z, bind_n, ~) ;

#define BOOST_LOCAL_FUNCTION_AUX_call_ptr(z, n, unused) \
    BOOST_PP_CAT(call_ptr, n)

#define BOOST_LOCAL_FUNCTION_AUX_call_name(z, n, unused) \
    BOOST_PP_CAT(call, n)

#define BOOST_LOCAL_FUNCTION_AUX_call_member(z, n, unused) \
    BOOST_PP_CAT(BOOST_LOCAL_FUNCTION_AUX_call_name(z, n, unused), _)

#define BOOST_LOCAL_FUNCTION_AUX_call_typedef(z, n, arity) \
    typedef R (*BOOST_LOCAL_FUNCTION_AUX_call_ptr(z, n, ~))( \
        object_ptr \
        BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS, \
            BOOST_PP_TUPLE_EAT(3) \
        , \
            BOOST_PP_REPEAT_ ## z \
        )(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX, \
                BOOST_LOCAL_FUNCTION_AUX_comma_bind_ref, ~) \
        BOOST_PP_REPEAT_ ## z(BOOST_PP_SUB(arity, n), \
                BOOST_LOCAL_FUNCTION_AUX_arg_param_type, 1 /* leading comma */)\
    );

#define BOOST_LOCAL_FUNCTION_AUX_comma_call_param_decl(z, n, unused) \
    , \
    BOOST_LOCAL_FUNCTION_AUX_call_ptr(z, n, ~) \
    BOOST_LOCAL_FUNCTION_AUX_call_name(z, n, ~)

#define BOOST_LOCAL_FUNCTION_AUX_call_decl(z, n, unused) \
    BOOST_LOCAL_FUNCTION_AUX_call_ptr(z, n, ~) \
    BOOST_LOCAL_FUNCTION_AUX_call_member(z, n, ~);

#define BOOST_LOCAL_FUNCTION_AUX_call_init(z, n, unused) \
    BOOST_LOCAL_FUNCTION_AUX_call_member(z, n, ~) = \
            BOOST_LOCAL_FUNCTION_AUX_call_name(z, n, ~);
                
#define BOOST_LOCAL_FUNCTION_AUX_operator_call(z, defaults_n, arity) \
    /* precondition: object_ && call_function_ */ \
    inline R operator()( \
        BOOST_PP_ENUM_ ## z(BOOST_PP_SUB(arity, defaults_n), \
                BOOST_LOCAL_FUNCTION_AUX_arg_param_decl, ~) \
    ) /* cannot be const because of binds (same as for local ftor) */ { \
        /* run-time: do not assert preconditions here for efficiency */ \
        /* run-time: this function call is done via a function pointer */ \
        /* so unfortunately does not allow for compiler inlining */ \
        /* optimizations (an alternative using virtual function was also */ \
        /* investigated but also virtual functions cannot be optimized */ \
        /* plus they require virtual table lookups to the alternative */ \
        /* performed worst) */ \
        return BOOST_LOCAL_FUNCTION_AUX_call_member(z, defaults_n, ~)( \
            object_ \
            BOOST_PP_IIF( \
                    BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS,\
                BOOST_PP_TUPLE_EAT(3) \
            , \
                BOOST_PP_REPEAT_ ## z \
            )(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX, \
                    BOOST_LOCAL_FUNCTION_AUX_comma_bind_member_deref, ~) \
            BOOST_PP_REPEAT_ ## z(BOOST_PP_SUB(arity, defaults_n), \
                    BOOST_LOCAL_FUNCTION_AUX_arg_name, 1 /* leading comma */) \
        ); \
    }

namespace boost { namespace local_function { namespace aux {

template<
      typename F
    , size_t defaults
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
            BOOST_LOCAL_FUNCTION_AUX_comma_bind_tparam, ~)
#endif
>
class function {}; // Empty template, only use its specializations.

// Iterate within namespace.
#       define BOOST_PP_ITERATION_PARAMS_1 \
                (3, (0, BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX, \
                BOOST_LOCAL_FUNCTION_AUX_FUNCTION_THIS_FILE_))
#       include BOOST_PP_ITERATE() // Iterate over function arity.

} } } // namespace

// Register type for type-of emu (NAME use TYPEOF to deduce this fctor type).
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::local_function::aux::function,
    (typename) // For `F` tparam.
    (size_t) // For `defaults` tparam.
    // MSVC error if using #if instead of PP_IIF here.
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS,
        BOOST_PP_TUPLE_EAT(3) // Nothing.
    ,
        BOOST_PP_REPEAT // For bind tparams.
    )(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
            BOOST_LOCAL_FUNCTION_AUX_typename_seq, ~)
)

#undef BOOST_LOCAL_FUNCTION_AUX_typename_seq
#undef BOOST_LOCAL_FUNCTION_AUX_arg_type
#undef BOOST_LOCAL_FUNCTION_AUX_arg_typedef
#undef BOOST_LOCAL_FUNCTION_AUX_comma_arg_tparam
#undef BOOST_LOCAL_FUNCTION_AUX_arg_param_type
#undef BOOST_LOCAL_FUNCTION_AUX_arg_name
#undef BOOST_LOCAL_FUNCTION_AUX_arg_param_decl
#undef BOOST_LOCAL_FUNCTION_AUX_bind_type
#undef BOOST_LOCAL_FUNCTION_AUX_comma_bind_type
#undef BOOST_LOCAL_FUNCTION_AUX_comma_bind_ref
#undef BOOST_LOCAL_FUNCTION_AUX_comma_bind_tparam
#undef BOOST_LOCAL_FUNCTION_AUX_bind_name
#undef BOOST_LOCAL_FUNCTION_AUX_comma_bind_param_decl
#undef BOOST_LOCAL_FUNCTION_AUX_bind_member
#undef BOOST_LOCAL_FUNCTION_AUX_comma_bind_member_deref
#undef BOOST_LOCAL_FUNCTION_AUX_bind_member_init
#undef BOOST_LOCAL_FUNCTION_AUX_bind_member_decl
#undef BOOST_LOCAL_FUNCTION_AUX_call_ptr
#undef BOOST_LOCAL_FUNCTION_AUX_call_name
#undef BOOST_LOCAL_FUNCTION_AUX_call_member
#undef BOOST_LOCAL_FUNCTION_AUX_call_typedef
#undef BOOST_LOCAL_FUNCTION_AUX_comma_call_param_decl
#undef BOOST_LOCAL_FUNCTION_AUX_call_decl
#undef BOOST_LOCAL_FUNCTION_AUX_call_init
#undef BOOST_LOCAL_FUNCTION_AUX_operator_call

#   endif // #include guard

#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_LOCAL_FUNCTION_AUX_arity BOOST_PP_FRAME_ITERATION(1)
#   define BOOST_PP_ITERATION_PARAMS_2 \
            (3, (0, BOOST_LOCAL_FUNCTION_AUX_arity, \
            BOOST_LOCAL_FUNCTION_AUX_FUNCTION_THIS_FILE_))
#   include BOOST_PP_ITERATE() // Iterate over default params count.
#   undef BOOST_LOCAL_FUNCTION_AUX_arity

#elif BOOST_PP_ITERATION_DEPTH() == 2
#   define BOOST_LOCAL_FUNCTION_AUX_defaults BOOST_PP_FRAME_ITERATION(2)

template<
    typename R
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_AUX_arity,
            BOOST_LOCAL_FUNCTION_AUX_comma_arg_tparam, ~)
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
            BOOST_LOCAL_FUNCTION_AUX_comma_bind_tparam, ~)
#endif
>
class function<
      R (
        BOOST_PP_ENUM(BOOST_LOCAL_FUNCTION_AUX_arity,
                BOOST_LOCAL_FUNCTION_AUX_arg_type, ~)
      )
    , BOOST_LOCAL_FUNCTION_AUX_defaults
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
            BOOST_LOCAL_FUNCTION_AUX_comma_bind_type, ~)
#endif
> {
    // The object type will actually be a local class which cannot be passed as
    // a template parameter so a generic `void*` pointer is used to hold the
    // object (this pointer will then be cased by the call-function implemented
    // by the local class itself). This is the trick used to pass a local
    // function as a template parameter. This trick uses function pointers for
    // the call-functions and function pointers cannot always be optimized by
    // the compiler (they cannot be inlined) thus this trick increased run-time
    // (another trick using virtual functions for the local class was also
    // investigated but also virtual functions cannot be inlined plus they
    // require virtual tables lookups so the virtual functions trick measured
    // worst run-time performance than the function pointer trick).
    typedef void* object_ptr;
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_AUX_defaults),
            BOOST_LOCAL_FUNCTION_AUX_call_typedef, // INC for no defaults.
            BOOST_LOCAL_FUNCTION_AUX_arity)

public:
    // Provide public type interface following Boost.Function names
    // (traits must be defined in both this and the local functor).
    BOOST_STATIC_CONSTANT(size_t, arity = BOOST_LOCAL_FUNCTION_AUX_arity);
    typedef R result_type;
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_AUX_arity,
            BOOST_LOCAL_FUNCTION_AUX_arg_typedef, ~)

    // NOTE: Must have default constructor for init without function name in
    // function macro expansion.

    // Cannot be private but it should never be used by programmers directly
    // so used internal symbol.
    inline void BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC(
        object_ptr object
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
        BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
                BOOST_LOCAL_FUNCTION_AUX_comma_bind_param_decl, ~)
#endif
        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_AUX_defaults),
                BOOST_LOCAL_FUNCTION_AUX_comma_call_param_decl, ~)
    ) {
        object_ = object;
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
        BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
                BOOST_LOCAL_FUNCTION_AUX_bind_member_init, ~)
#endif
        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_AUX_defaults),
                BOOST_LOCAL_FUNCTION_AUX_call_init, ~) // INC for no defaults.
        unused_ = 0; // To avoid a GCC uninitialized warning.
    }
    
    // Result operator(Arg1, ..., ArgN-1, ArgN) -- iff defaults >= 0
    // Result operator(Arg1, ..., ArgN-1)       -- iff defaults >= 1
    // ...                                      -- etc
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_AUX_defaults),
            BOOST_LOCAL_FUNCTION_AUX_operator_call, // INC for no defaults.
            BOOST_LOCAL_FUNCTION_AUX_arity)

private:
    object_ptr object_;
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
    BOOST_PP_REPEAT(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX,
            BOOST_LOCAL_FUNCTION_AUX_bind_member_decl, ~)
#endif
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_AUX_defaults),
            BOOST_LOCAL_FUNCTION_AUX_call_decl, ~) // INC for no defaults.

    // run-time: this unused void* member variable allows for compiler
    // optimizations (at least on MSVC it reduces invocation time of about 50%)
    void* unused_;
};

#   undef BOOST_LOCAL_FUNCTION_AUX_defaults
#endif // iteration


/* function.hpp
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
*/