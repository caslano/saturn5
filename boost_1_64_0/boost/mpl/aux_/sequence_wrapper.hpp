
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

///// header body

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/enum_params_with_a_default.hpp>
#   include <boost/preprocessor/enum_params.hpp>
#   include <boost/preprocessor/enum.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>

#if defined(BOOST_MPL_PREPROCESSING_MODE)
#   undef LONG_MAX
#endif

namespace boost { namespace mpl {

#if !defined(AUX778076_SEQUENCE_BASE_NAME)
#   define AUX778076_SEQUENCE_BASE_NAME AUX778076_SEQUENCE_NAME
#endif

#if !defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)

#   define AUX778076_SEQUENCE_PARAM_NAME T
#   define AUX778076_SEQUENCE_TEMPLATE_PARAM typename T
#   define AUX778076_SEQUENCE_DEFAULT na

#   define AUX778076_SEQUENCE_NAME_N(n) \
    BOOST_PP_CAT(AUX778076_SEQUENCE_BASE_NAME,n) \
    /**/

#   define AUX778076_SEQUENCE_PARAMS() \
    BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define AUX778076_SEQUENCE_ARGS() \
    BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , T \
        ) \
    /**/

#   define AUX778076_SEQUENCE_DEFAULT_PARAMS() \
     BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define AUX778076_SEQUENCE_N_PARAMS(n) \
    BOOST_PP_ENUM_PARAMS(n, AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   define AUX778076_SEQUENCE_N_ARGS(n) \
    BOOST_PP_ENUM_PARAMS(n, T) \
    /**/

#   define AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    BOOST_PP_ENUM_PARAMS(n, T) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,AUX778076_SEQUENCE_LIMIT,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#else // AUX778076_SEQUENCE_INTEGRAL_WRAPPER

#   define AUX778076_SEQUENCE_PARAM_NAME C
#   define AUX778076_SEQUENCE_TEMPLATE_PARAM BOOST_MPL_AUX_NTTP_DECL(long, C)
#   define AUX778076_SEQUENCE_DEFAULT LONG_MAX

#   define AUX778076_SEQUENCE_PARAMS() \
    typename T, BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define AUX778076_SEQUENCE_ARGS() \
    T, BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , C \
        ) \
    /**/

#   define AUX778076_SEQUENCE_DEFAULT_PARAMS() \
    typename T, \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define AUX778076_SEQUENCE_N_PARAMS(n) \
    typename T BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM_PARAMS(n, AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   if !defined(AUX778076_SEQUENCE_CONVERT_CN_TO)
#       define AUX778076_SEQUENCE_CONVERT_CN_TO(z,n,TARGET) BOOST_PP_CAT(C,n)
#   endif

#   define AUX778076_SEQUENCE_N_ARGS(n) \
    T BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM(n,AUX778076_SEQUENCE_CONVERT_CN_TO,T) \
    /**/

#   define AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    T, BOOST_PP_ENUM_PARAMS(n, C) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,AUX778076_SEQUENCE_LIMIT,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#endif // AUX778076_SEQUENCE_INTEGRAL_WRAPPER


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct AUX778076_SEQUENCE_NAME;
#else
namespace aux {
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser);
}
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, AUX778076_SEQUENCE_LIMIT, <boost/mpl/aux_/sequence_wrapper.hpp>))
#include BOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// ???_count_args
#define AUX778076_COUNT_ARGS_PREFIX         AUX778076_SEQUENCE_NAME
#define AUX778076_COUNT_ARGS_DEFAULT        AUX778076_SEQUENCE_DEFAULT
#define AUX778076_COUNT_ARGS_PARAM_NAME     AUX778076_SEQUENCE_PARAM_NAME
#define AUX778076_COUNT_ARGS_TEMPLATE_PARAM AUX778076_SEQUENCE_TEMPLATE_PARAM
#define AUX778076_COUNT_ARGS_ARITY          AUX778076_SEQUENCE_LIMIT
#define AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#include <boost/mpl/aux_/count_args.hpp>

template<
      AUX778076_SEQUENCE_PARAMS()
    >
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)
{
    typedef aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_count_args)<
          BOOST_PP_ENUM_PARAMS(AUX778076_SEQUENCE_LIMIT, AUX778076_SEQUENCE_PARAM_NAME)
        > arg_num_;
    
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)< arg_num_::value >
        ::template result_< AUX778076_SEQUENCE_ARGS() >::type type;
};

} // namespace aux

template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct AUX778076_SEQUENCE_NAME
    : aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)<
          AUX778076_SEQUENCE_ARGS()
        >::type
{
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)<
          AUX778076_SEQUENCE_ARGS()
        >::type type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS
#   undef AUX778076_SEQUENCE_N_ARGS
#   undef AUX778076_SEQUENCE_CONVERT_CN_TO
#   undef AUX778076_SEQUENCE_N_PARAMS
#   undef AUX778076_SEQUENCE_DEFAULT_PARAMS
#   undef AUX778076_SEQUENCE_ARGS
#   undef AUX778076_SEQUENCE_PARAMS
#   undef AUX778076_SEQUENCE_NAME_N
#   undef AUX778076_SEQUENCE_DEFAULT
#   undef AUX778076_SEQUENCE_TEMPLATE_PARAM
#   undef AUX778076_SEQUENCE_PARAM_NAME
#   undef AUX778076_SEQUENCE_LIMIT
#   undef AUX778076_SEQUENCE_BASE_NAME
#   undef AUX778076_SEQUENCE_NAME
#   undef AUX778076_SEQUENCE_INTEGRAL_WRAPPER

}}

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == AUX778076_SEQUENCE_LIMIT

/// primary template (not a specialization!)
template<
      AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct AUX778076_SEQUENCE_NAME
    : AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >
{
    typedef typename AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
};

#else

template<
      AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct AUX778076_SEQUENCE_NAME< AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(i_) >
    : AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >
{
#if i_ > 0 || defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
    typedef typename AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#else
    typedef AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#endif
};

#endif // i_ == AUX778076_SEQUENCE_LIMIT

#   else

namespace aux {

template<>
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)<i_>
{
    template<
          AUX778076_SEQUENCE_PARAMS()
        >
    struct result_
    {
#if i_ > 0 || defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
        typedef typename AUX778076_SEQUENCE_NAME_N(i_)<
              AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#else
        typedef AUX778076_SEQUENCE_NAME_N(i_)<
              AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#endif
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* sequence_wrapper.hpp
lsk0Mf0yn5J6CibrhiMgOgter21ooMlkyj29XLDvXGCzuD7gqorhOPVHNjZKi0Ozu5gaAz7S5qSDbLDYOoSNduQtn6dQZEkrs46fRl0rB7ORSVo0m89A5YfdiJvizsUzrKjWUBVPv1ki56Qn0x2rRwO0o/lGiTW49NiTdGfco4ml6XCJV4bZ1gwms1yO7lnEstq2T6RzZzquPl5H9v0a2RPPw7RUpT85XNlKa/qMppHfXGjxHFFolbeT16mn/PCbZNo9259N6hajjU4j2bRVn2nuwhM0fZEQycqcRb7MKoR8WozY9ek4qDmKX9jeSWlJ0YgQH4x8J22eGzSezLap0F4ZfaoYUcy3bLWg0c2jeTDe0iFfR1awqA6NCy7xbPaaAoYI1hhK1mCBAAN49+YQbk7fwxrtclByrZyc66Qo6ZQF189tJ2WdQOq9r54kK1z4R6dCXPFcz39U9MKUPWf5VssS+qJ+ixfqTqEtiiPx7awhzj+1EqxDDKS0BcdwZUYndlxIJtOholBSymRHz8VQSoMTjOqGkf70QxhhOBbt+6ZR2fg7tK7qGZM4KEZ6dz5TjMd39HOwY1dud9DSaS204s11KrQ/gPGKojAYdgIGe/Tw0iiKHwwcBn2nBP5eSYNuopiN8fuMpp6B7O4yETjKLqL2sAxcyStli0/pUUi7CkXJ2cJnsaDtV84l+bobpOWTRZGr0tkizwLke7fz4HxFipgzma3TKyKxAWbUExlHP/OcSXOpKdXscsQtqx6a7j6Gx5Yvp4lsBCnGxlHshst87uGFlBknDvtuHTzWVgW7KU60hdGkSHkydoqHY1I8Jm6dQmViLym2MZRPYh6CfshG8vJzFLJ6JxW0rKHD8ru4dGgsfhRP5oEL7WljjTFfd3kmipVU4HprJY1pGMESCqWhdd2bywVKUfUDLVgsjMRtpS1s+IMqevo0lLqaxuH47DBkz3pNfM9CkrvWRqPKn8DR1o0C6rpQ2/iOxv2Rz5Nv5FPKlIu8ytoV+63jqboyARcHqrA3H19QT5+RfGF0BBruq3PTTgvSKjZiSUk3KVpVB17KrzHvcj7hzVNUpU1miy4sR7/rh0jCMItGaVxiUpNOYeT9+whL90fDx1xqggPN0D4HTbMG8vp5gvc07qUcx4nM1Eifng7X4HY/v9CwAXn0SScDa3Kes+oEX8F85Tlm1QeArUqBw30lfNVNZA61p/D0xk4mH51CN5RX0prSy9R5cimec0cIq0/CQRttmndkOBbaWaAhxJ453pxLb/1L2Zf8dZBfU8LuHLKj7RsFa0/dFXTthTA0T8RgUcJkanU0pk+Gkfx8aBeON9QhcPQESozdARe1IvjX9uLzx36Ffc03SrR7SisiFzJV+cHoXvwHb87QociugahP7kMVE1vgUeNFlqtDOd+xDota27n7aj9IvD1CN6b2oG5tO9Pz66DnRjOYiGg/irSKQ0nRNQrK7MWQB2Qk2rPQIFsBvv6V3dl0FR9PqeGgkDdpxpuzEjEBblQkxN5e4pgs/Jx7igtWx1zu0t13BzDhxg5+x3uNAH+7jg6jhxjR5IkPKCKN8bLw2XCETujqsrDKTkR6vyFH35NUN6aIBVc8FvR3Lww49IJMJqbDbdkesuwdgJNJabQrrD/tzrxJoptzcFx4CspWprF68WQyuHMSvXPukp9zFbM+Xw++QZHmnHuMCJ0yaOgdonvOXdgh+Ia99wQgXn89uVyfwBruXUOehTvTPbONNgmFcxXrMTDXduIdsjG0q6SCber+AzmJS/jsmeKoEWpmdYXX8MyhlKk0tkJ25lkmnWyHKKd0Zrk7FMWjW5hR22AUfpFmivrxeJlqwVXehpIAyaI=
*/