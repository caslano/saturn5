
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/integral_c.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#define AUX778076_OP_ARITY 2

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/integral.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)
{
    BOOST_STATIC_CONSTANT(T, value = (n AUX778076_OP_TOKEN s));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N, typename S > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
#else
        : aux::BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type
#endif
    {
    };
};

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN

/* shift_op.hpp
II+LiA4PIsdUecr5KpCVozsQ9DGG9fkcTFlTs/jmW8uouo9gnUdgEx8Nvs6anGShp1PIJ1p5w8tSiZIfZNPUPUpwXyFCjSpFvGWnA4T1zVnzW298G6jMdxwTg+vIVbTkkzQdqRvM/W2nU9AJTx5/RhWSBluoSkUM5D2cIu5F0BXjuyzozlBMtN3IIscMhuEpJ7bqVRNlRsfyiwLchf0RyxcMSaLLohp0duJcWpQuRtnC+2l4+Cgaurk3te+poZ0T/PB+mhSXV5DDydQU0ns+FNmB2ahU68Dlq5YsBdE0/6U4O20qWCOd08V/mDuSan8zrjbpD9h8yWHfI1xwVbD/6fHoJ1RnosgmagzFzy31OGkhRu1fjvKiy23Utmkbj77UjFOC8epE43MaIdHNeukHUtKAeexISg62eLrRnh8dGFJwibS8A6jDNgNR707i0OMxiNKYTCcs2phv79W0Xj+PXRLMg9JPbqf+kpLYn23BZthYow3xdCzdF0H2ETD8eRVrAjJxdPgMVOnM4PWpdTT+ziMc+7GHtPdu434sGpdVLvEn/Bj9EN6LNO5PK5drIVlyDvEAIcQWjkdQz1E+broJRQUtx8tLLWQ55RYFTDgP7uTMZiwpwc36CvbR8gFJflVmz4/k0ngPJXIP+wmOSkz6oYoZl5uYse5rHMv9yo/0DYYwF2zwvOcLGxF/UpQ3oLcK5WyCjDni5z/mvStbqZdpMb91bivmuD1E6nY7qusoI3+PLDxPTGFx5w3wzD6cf9q3GI31dmyrQLfPr5JlrK43NkUk0cOWWuLdBUj75IUFP6zYY1lRpKx/gZeCfYPzK8YxeidLycpv6fPTNXQp34pm76nAVNenNPeuDmbekeKOdwS4/P0GcrUcDfEKEUz7wEHOpvAYVEzXpCfwzKzR1DLsKF3NEuw3a5rO9xY4wzzTnom8HoHbJYPow/EGhDbvxuF+T2jAsts8/M5zknC4QyoF1Vgck4ukxmOQcVZDVlY/GhTchRM1e/ACZUzqy0u0vHan4d+cIVM3FuOM00lxyivetqaaRvWeRkpVhkj9eglyAYNISM0HB4KlIPy5DAl1gdRepIoPonn0YLcpuxVzhb7PkmLJsW+p9+DnzGa2B4XtNedj1KTwFwbsgx8INooC+HnSohJpSDujIYooQkV7SFJRQpFSURpI8pYG7UJSaMkqUtKSdhGlQhpKNEQTUUrqOa+vcH93nPuvi3DkPyNlaJ4cIw16OjC9mxbjd13CiGuRcOgFTDlpBSv3e1R/cU/439VosrsHsuadLZ27K9HuVg3zbm2mc/vZeNn/MIbeKgBq07Ao4xeOeK2BTogjys5EoMRKcLb5R3Sdr82362LF88wkHjmsD5PkWHyscRfrOitiqGInGnetYnHPjzLw5H60+7gI+xW1Eb9gtyjfPACl7esoO6iipfk3sVRhJcy2XMM8755Ykv8UQ2amM9O/UnZ74cXY18vkpOo7/NPLlBEhc5jRZbVQOHGYHbz/oKtpJo/Pj8NglTq03d0ox3y+zAEdjuNMy/k8lmIk1c9eYvatWWK9/3ZGGq5iyQNzPq5uIaCzjMOrnOX4g854WmIt1qqO46y463zw2RY6BtpNOWM9tk8zkEm/hsAl7i+WnAzBv/JgjE6YAttJHfm4UAmflx6gc9+5lEdNZclWN+wMPy/Vu2RggGlPXlswFZaZZXyTos2+I11E5b4aWC/9T44+6IgertF412jMz09acN+DUsadfS1bVKojfd1DaIlgBo6PlAvK/yIlqIscMreAB97MEDODe+L7XX0sXvmZ+u7+sv/6PwzRq5WKDUnc5bmZe08kw/D0PTqU7mGOyxHsuXmCrXxCsGI=
*/