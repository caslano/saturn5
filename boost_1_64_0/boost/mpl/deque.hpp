
#ifndef BOOST_MPL_DEQUE_HPP_INCLUDED
#define BOOST_MPL_DEQUE_HPP_INCLUDED

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
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_DEQUE_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define AUX778076_DEQUE_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_DEQUE_HEADER)
#   undef AUX778076_DEQUE_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER deque.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME deque
#   define AUX778076_SEQUENCE_BASE_NAME vector
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_DEQUE_HPP_INCLUDED

/* deque.hpp
1rR1lIb9YnPe15W6u4kPli6VW46W/lCfr2k4F76jmmjTmrHerTC4ysJgHmPdvAKZ0HePbina726yDlCX3eHT9d6lcphr5bCcc3hK57ArTr13qjTXuOu9RKfZKWla0rObaBnf4JdxoJ2Q606F6NOeZZSlTBF5Pggs1DpZ9FZGb/SzhEoz+SXSHrcWmVU5JklBhbLxOXgDKGdgAlSbp3nV2V8/5THEo48MJ3IttyuM51sY7+Ra7rpTYbxdtVNNIv2mT5QzwS0ZOcaS9kT/Ilzi9KKc86Wcq9d6Pm3HOqe/XwwvNnK0NxGySvgSdsqcmN0CAwMgUdKu4WbKW5LnMrHWcvI8rEPT8s0PBBNc0uOiy5cV5kvddNlNY/5ynP55QaUpdffPHypUmhc8ekxhJDXsFTVTYskwfeaFPrZj/Mg5rVRPVCHhPLtiDQ950cn3P8dt9uFH3N/bpN10FuUvp9GRzrZqVqOwvNtdsws0ljVxarZFpbnHXTOfTrNF0mgUn2LIxieXO6M2LU+zjo82HlL3cfXWPrbrW+khYstpDufU88XeWz1RjGKzQuFbbrTLlisUNsdBe5NK84Ab7RydZpONtpz1S6erCrBvnEiNXhCw+R/uibL4iNfTJh9JXejiI3IpxOgnwEdQWT9xEfLTEGkPF6V1Vdl1Db8EFk0Z2eAtGxXSj7t5y33lyJi+e6R10zmfliMymQ0qq01uJpOjs9oQp83WqzRPutush06zHjc4NNOETQll7WIzmYanPmlt/bwJ+f9/jvlh+WIa1v9EsWo6x3yLaUNEiMHtlczxSpVL5vj6fAXu1jLHbknwSTtL5rjnOw6Zw6tlDu+xyhzTVmiZo3wMDcN31CdCICljCqhXs+07E1zUO7vUZtt2mvQpPlnaZxQYS2Sia5EhTcO/7GMt1Gi2vtLKcy3n2aHUZuvx2AFMYy7PFDbODGY/TWQ0UUEDZKQzgzHEAYqevXyOoVh8WvTw0l2hp+syH2rCd0MvbdewwIeme44n7fQp/pgJk/jw7lyz4kbnHcJLL8LVLHsLSUDdTV6QHtR7+ticok9TUlAA3wfX0M3nuCCMpGwvwRItcYofzaicamDmJcXFACUtfPqALS0UBR3TX3fqb4lMUsR7it9vY2Rlm514qJKTICbKLvw+WB3uqyrYl1HQEqzu5gHrDD5DKNTQhj6Uy8R6a5KKvJE92iVJN/DcZtuzTOQZSpQOVXIzXfm9S8+a6MFU8uELVQkdX91SXrIlYWn/8pJdZLSF7KhmyTraC8tFxV2m/TDfuJMrUb08iWsxJru56HKHGWX1KoODie+n79GzNs18umb1qFl9VUE91aykOyVIzK4n/BJz6ld2rVzDSSNvgWBS88yJUjJqlIwcOlGNeO59Czuq+0hQDVbcTR8Y9WAFr5G3ApVtCTZRjCloLu7Ll61TXxYn275x7JEXuYTQzShoKpqIBqM+2bkju06jXAeU66oK6jIKdiqU64BynRvlnJ1kQNyQ9Q9eDAJnyfwMVXZJFzQtXXLerqEvRSoUk7vt9zvlTOwE0Qx84DCMkxrjSHP3wKYmAHPRRu+SUUCoMfiTyn9QrPKPxhUPqCow4TnJtD4dVp86Oj41skOZkZhjG3latzsvz6JR8lEwFkZpAUjcjZh//Q4p20xY4kfdzTAFm6xi/AJFdaMdTXiz1yvCa9EDRY9/vSdZ0k1xAauoyB3wh05S89Ik3DtJqVmUUnsqdhEBujQ4Q/hRwX5IOPv1QPcpnniJL8NPrCeWGccKRw3FnyhjyZnfVuLNfog3e8M521m82R8u2F6Vvf3/ssDn91H6BvPwmECCy23ove+2tuVPMxX6j+9Af+/R+ocXy10=
*/