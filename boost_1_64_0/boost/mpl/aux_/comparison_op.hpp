
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
#   include <boost/mpl/bool.hpp>
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

// MSVC workaround: implement less in terms of greater
#if 0 AUX778076_OP_TOKEN 1 && !(1 AUX778076_OP_TOKEN 0) && !(0 AUX778076_OP_TOKEN 0)
#   define AUX778076_OP(N1, N2) \
    ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) \
/**/
#else
#   define AUX778076_OP(N1, N2) \
    ( BOOST_MPL_AUX_VALUE_WKND(N1)::value \
          AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(N2)::value \
        ) \
/**/
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : bool_< AUX778076_OP(N1, N2) >
    {
#else
    {
        BOOST_STATIC_CONSTANT(bool, value = AUX778076_OP(N1, N2));
        typedef bool_<value> type;
#endif
    };
};

#undef AUX778076_OP

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN

/* comparison_op.hpp
ZeQ41HJYIIZtLg9bw1fVcjgPHI4X4sFmgobgdwoH2fESfw3xonB/r06rbO3xqvYkyPZ0Fc25P7g587g5j21QzWkvm3MFrR01OMifwg0jAiFEzInVbJDSjzoDbblDuZOhIKNZwu8ULpz8zBIh20SRwfkhG/VumdvaA9loYt7AFKSyvadGAjrQTS3O6+lGupS8gR688hJQP16l5jmRMWT5q4PLj9B+d+j2u8O1n/drzjbYz9P6fUkhLYCy8sobvZQeauSGqRfr4LCPFaqTQcfHHjYdj3A8PjQLhQU2VnfNWvYfb+jzTBviuxmETD5mpJGKwxkIbCH2Wuwhu29iTpz/Jcj2bUGhUjAIlMBYqKhgPgj1Dnv/aDQnUA9JPwB1cnBmsy8dUlaAjP60S6HlcOtmlVORMMPRwQpI9rLxZZBuC/wMCUyT5QbCaP1qYzW3CbZws3jhF/wGC994Ub0CQY4rRHNhi7Zq69m8MFrxL6gaaEtb+W7g/Qncvqe5mcWvqNvUEKdUpQ56OPjc8Q3Sh47O9hudTcAn4NrUjhQgpbjTpyTtcOaW98im8yhFxzT3PKPWWyAJQEnfbkY1ylSMubJip1RtTx/pG84jOlbV2Y3rFGBCRuoraR409sU5TIDVyfC3X8vrFTUiOfeHHlnJxjfXxVDaMkrLdz9qtKEDLoKm8z2vnaCHiYgNQpndud+rzFho93BmbQjWVjhmHZEGS5PSSENMdQYXmKYK1JnE+PifU5k6xmQNB2JsCnF9QAH2iuEez8M92zbcPdaiVxr5IkVSz5PsHtGR1ndwRWIRBrr6snkI71LllK+RQ+ihMynPPnJOc8szyrU0nXeAF8wnRIktT1bIPcC4jsqhxV1xkLEYn2IXr0ASrWxuk0e0yXVmbKf+FR/ND3R4Tcu7NOOd81oV+WubAu4pSSCfkGTTk+eArKkzWa5FjbOo5X87ot9PJ7wZ2T89bnvk951D52d+88rNlj8Tmv/lAAfMcstrP5Diq220w1Y7STAtQ74Q/pKJ0rroEtj01OZcFFyAEoxBAhclSNAGP4HPVPCZmjHzlv5nk56PoGb2Us10PXC+z2V0qdrM7PpohYtyKN+wq5HVrbLGUdY4o3vYrHHICu9wyM7Pr2ZXz4DC1ML/2ij7r4Vd+nZ80mY0BEUuGUxNCrrwdTS+1EfTBF8WkYBvV0sC6R6odv6OhazN2MNXUEd2wwIVTnlarkIgCjSnV87sxuyhk8Kv94IuaMrTwfi7ri0Ltc1StSVqZL0Mri1wi7l5brFGP2hqnLTOUGQdwFkDF+cDCArc10lhTJusV8NJeU6XiXO6V6E8p0tA7IdCQurCqdv9VXw3aisWFefv5MXy0llyunNVnY9ezweIIw6DVzq0sYa6mqRt4VY01gDpMjDcQOPo+jQPiPgo9MzDEbrwZDuG1w3MSpyQsQ/igXQdFCYnXqF/Yzkm51nnhZGcf/xpXLnh7wn+b722ZzMnkiG/Ypxa+m43BqwHi/QIn0a+VepUO6x4j+Ov2JmC7Oa+uzhPK5XnUs7jn+rUfh/KELi2jmWEA/tZFYq3JKmgK8ovYYeE3Q2VrgHSVjfZvEpZZHa6717UZzxGBaoq31qJKqUsGMJX6ZQI4Ss7qyrh6wNPsMd3EXuKwKjHNB6lMhEYedW1SlycLF0U/H1F/OhMJDeZZ0mauQzL26SlwXZef8BZrRwiqJlTuJmzbM1MXVkD7IH3fsXNvITdvOCzhpriErEU4Ld/ghfgcD49lEmU4HtWgeAoLc0jWbJ1MI3LTkezeN7Gq9ZNK6yBiqWDbJ3gWsyybRbXfp5RoIvWy6g1Fw1fv9t387VlJJj544qZLyUa4FW2u+dh978=
*/