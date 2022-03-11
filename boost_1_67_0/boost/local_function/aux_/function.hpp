
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