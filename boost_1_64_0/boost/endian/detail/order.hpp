#ifndef BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/scoped_enum.hpp>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__

# error The Boost.Endian library does not support platforms with PDP endianness.

#elif defined(__LITTLE_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BIG_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#else

# error The Boost.Endian library could not determine the endianness of this platform.

#endif

namespace boost
{
namespace endian
{

BOOST_SCOPED_ENUM_START(order)
{
    big,
    little,
    native = BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

}; BOOST_SCOPED_ENUM_END

} // namespace endian
} // namespace boost

#undef BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

#endif  // BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

/* order.hpp
RdxpihSkFBmiipSlKTIkpUihKuJKU6QwpYizL4pwphQZmpYihhooYhhSxNiDHvED2Y14We4j7sp9xJ3Zj3haLBUYsDQEpwBP0rWBxCVJa5oExN0z8Jck9/EkPBqPYQEOolr/DApy/kLidpPgaOlyZSU81Owkp6wV02H6+shL6A/3l94ect7rcpIoCL95uLKH1CtK4lU7zg2t5L4s3tV8EtASfJgA0g89avYGwPPHrWv4siYyptHwB2TeQpyYLD4JBNJaaufbIttLyPPGa46FjdRZ0hDABL29ZEQZztdW6fCdDjv5tUAYbxkiebNqQUmmSjiTVhNkkiu9iZCjcVh7L/zik/JpVbyJVsXNUBDyaThYJQK79yAiCECuMbYj0dFEIqPDSYyrmVGKcEJ2REMV5E7CWbFBG6RuE4YVrd0AWc2QNpBsYEHRa1YL8mEuVcauwPZ0H45wVv3DEf3Ddv3DEfOH7YYPW5EKSgydXKwWh7Sw5DR6xuHgxSY9x+fJBfomWqBvt2UYDiWBdCIT1HMyVdZwrlp1R3lxLeilaFgF7rDz4niDpOMQ0DESu2GJDFJ6mAuteHqikJwrs8FGRnZwNXzMTO6JP6ftrzW50chVF0EukO4w7LmQjEVhq2G35HoPYKuCwtPjir/17djgiv/gfpbyv0nI/1dY/r/G8r/OMCzNSflfiSTUrMn/sJZAdl8k80pN/jczGVNNYu+NSDgs8pL8D1h8EihTyn+/Lv8DKIcFwfsEwftw75Pkv09vL9mIWXT7Ga7Jf7+S/35N/meqxJyJ5D9vF0AOJf9vzKObFwnU4aLLF/keSj8IoYchzQpHtFITY6Z2q/3MNvKEUK/0F54DMFfy6gwCs0mOTxcRiGpg0GoNRB2YoEDryNAv/toaPwUdwXzcC2yodEeNfoxz6oKVxxoFTYQETVhN5froiWE5Gb6oBKsPBWsE513sc6suWIMI1kVFUArWoMrebBSsnMiC1YxtFqxMlRnpjAQr0xELVuv+WgvWZikbI5aCtTmDYM1U2G4obMlOlSxY61CwHv+m2PlrGpSqWcnLOpSXn31JyUt3nOVlxLDMrGdlmVzYWVOGNys1+XiCIEVi6eQcz2V4fVSP6yNrrRmhuarMn8cEKmmh6jLQQlm+j+Vg2uLGHEpMtprV5HNATWZAC+TuiuWHWnrs1N38Kjf3m5DRYaMfeHWH3AuGtR/ASsqkrt1KuvY37dYqdA1ht+n0tiIns48BnIbxMhe1J4sah9Kssgkoa1/oJs6pqPkPGZGu2U1K+w5ZSwvHMMs2W5ez6+Xw403KRNpkEI/aEdhW1qbpOX6t1KZbSeg/Dv9nUpoxW4M6/usWLUOZLvBmsh3UC0G9rT+I7LMFn1Zqe8jQDPo4TxSOYYkH+lCuSwy8kdhr3Z40JIjSO5Q7+YliGUjPLAp0PTqC4j7wmhD3dYPi/qB/6fXpkX9R84PtxUOtT5/clz7NcJoxVBYUnv/TqnahnEPWmeYQVRCnER0ZjCfLyaTj/0Rx/8kQLSe59vSpn5+Ib2bVXElOluQmrfvebLTu/q8ZyjOsGVTKainYt/3fKPdnxAaV+37/hHwXToumPdUTnk3uqdJWMjJYT2z28GIbpIV7e0q2dJKYdaMEaInnVTwJx+pwi3LfPwEA4K69+Socc5q91u6A0GPYSwk8KUJefovAmy+3DZH0/hrnPSM6ZLETTJ1oH8HHXckZW4rcU5X7V+M8VInyL/0Wxf3oivl5+447JSE+3qwzQ7wKMswM4ZNawxUkcZhmX65GbDkwi02VKFMlisx1uRSk2AxxKsgIBeHJRyIE2B74ywpND6QMooYz3j3UvNWDFEkkFCsfWgw4zG0=
*/