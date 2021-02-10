
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
PbhjSqwtuiQWkVXIkCNLiQxrIw9t2+PfHZaIdKAC2Xq0XudYFUr0ql2oDaP4LrthoGr7i4feH+Pp8Bdng3xTf63Oq2Zt2Nf/Z3yHkR+GwJ+oHXQ+hf67L4w2b6cPWETWnJwkeIWc+OQvvrz+vKLPK1ojPV6z5xEy5XmXOddB53Pp9L+6Jw7ZOTTOjqXE5fkP6G9QSwMECgAAAAgALWdKUk54q9MRAQAAwAEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMjFVVAUAAbZIJGBNkU1rwzAMhu/+FaKjpxF8GLsUExhjo4VCQ5Lt7iYKCWvsYCkt+feT06XZyfKr148+bBiJK0uYKtO5xsvxg9PNh5pStS/LrFDlsUiKPFOfb4fjV/6hjF4dRt8fqSd4v3ToOKGuRmWq+SJ5wnDFkKqWeeALPVMY5NGimgYtjwGFtFQxetXAONvjIwe3jls42xpGAcQUWFfDYIliO2LXd7+pfN9LKlVJ0jnCSnCQJFLfjtzyNCBE3KxEVGTO56wsvKjGGGLvtNN6uz8V5SHbbeNepKfslJfS76OYhH9jyzq+MXTNBLVlC7ZhgXOLELcNrSU4IzrYUOt5o8x19goAQ/Ch8rXM8PIqvH93oxeXhOun/QJQSwME
*/