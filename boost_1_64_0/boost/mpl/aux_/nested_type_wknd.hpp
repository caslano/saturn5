
#ifndef BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x530)) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))

namespace boost { namespace mpl { namespace aux {
template< typename T > struct nested_type_wknd
    : T::type
{
};
}}}

#if BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    aux::nested_type_wknd<T> \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    ::boost::mpl::aux::nested_type_wknd<T> \
/**/
#endif

#else // !BOOST_MPL_CFG_GCC et al.

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif 

#endif // BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

/* nested_type_wknd.hpp
mfQgq8eUMLNaF19kvl/yzKujdX+XVYfbu45t2elFAe+w23LbkPOPxrZq8ZwW7Pjt5qP0ui9GZK9dsEKdd21EUJfe0zZLvQXdx5+z4n/6Ptw+OSK94oPlLcTm9KsnSd6/lfm6bfd8aURd6ZuCLnUaikdVsT+VsSLIk/I+TtfPtXQuf/5rUKvVOVcpx9pVR1RpWNO62/Oo7r9XDJj5feg3cQ1HsbRMzW/fKlv+LqwlrMfDU6W8kJRvA9s//FC0aBPvL4WjxM8z8iReBWWnLF661+7xHFXB93GneZOGvhV0vdSuTSPlCmrcheQHT5JDUwNifd5eehNTsNG/0dujqVsOTHNrOSe5Q7CEHnb+tnu6tZlVsGrvdqsPzYJvbbw5bPrT0XXm9+4UFXSbCnU7PsOFli/cW1u4WpD7vUz1Ft3u9m836kjksTXrT/Yb8Fj5NH+WcvYyp/qdlo3sNKv1r7H7Vwcd8rbmj53n/SSw3tmMsTTfsnp6hzpzPlR/EGZj317h1yhuyuWpB+4N0/xyq+wuOwvHN/yp5kmj9z6+16BNJXv3zTflNr9rqobXmliw29O23selNVePaFWFOjaljsDM09o8716ffRd7nbt7MeFhkOfKWU43H47oufbeY+rpwfuWa/bu7PZ9X6/CTXK3Gy3Sqj39S4PeZdOObV04K/dYL9vRsiE1JFUGxp8Yr+DnlMse1tP14NOiDpMdj+/vZ9fm6dndNVN2N2wTO/1FxFH6y+rI3BR79yVlXE9bTAk9vuHo5eVPXT/VFPQNt6nddCYvKnR4/OL3wy64uKQ1mnVNebJlp6nlj/oNfnA1qe/9Xk8CBvO/J3v32Jkww2l1yscKd09pJjwR5D8TZK+vVlBUvelvozS7d75vvJHulvvilyHmzUJXdKzWIjX9/juvdvUa/WLbtOLbg5KP+T1kH1wO5skrVrZbMcrmyrHX1QVr/lqT2tioaoV6/V0inqosBn79lul/VZhUfcK+CtPXxlm7WEoXt78san8y/fzvFyflbrG8zXN+/32KKmb5ncdDFW8W1XU6d+JMtXE3DwzJLrfpynKfE70qLp6aO6k173enw9tOuWTvLGufeOXOqpWVXO+PVKYnfw2jHtU5e/D75oaHKy4sOrzBev68EbWpvML7Y96pF4j+6iyh6s1zzP1eb/nmquNmOoyav3fUtR1LtzZ+dtxBtupO/6ZvnNc+7LDh7Kyc/lMKmy69sD70nuWEUxaXatQQ88xmlRv2ziP15sBe6xILet29md3/Zb2Jd+Ondi97eMeL3NUZeenPrwzLbnDfwbfqwYIXcqfPwx9s3X4orqjfk1tvEhacvGTZ6V5r9/H5dZ3GTqwRpaZ+/+Aza/1ShyEO8w46+W/MjpyN163vyr9xfrFTmeQC2zi7a8+7D6z1oGHIu5i7XwYLTtqYta/nM+Fsn+u76zrIkry/XjqZ1HpMx3enmszplts7fUxeQaClw/3hQ0L2tP1G1xmf3NNtQdrLp5VVO76fP3B4fIe85BcWAsvjyXs0iqYFkVaLrZPc1nwfNTjjbdj52j6/3fAZZeNS7dOrz8KT1m8L8fB3HpXZV32l/u7GJ0ZHuHs0fLdp+Nds+ajCFQ9O0Udf2vj5H0o58Pakp814d791aVVPVJ/64PvNDQE8Cz/xhu2VBF+qLLC78+Jsx+k7PQM/p//a8Jtt5nT+4vUdBRY9a56QzcgsLOqusqu2et7lp2UPWCxYPX/DntaHB39L6hbx/s1rz5St0b2WWj6bOm+n9aS+T26nPTCf2GvorctrvzkEOt6PjKByzvHL/Lrp0NC3w+Y0blXG8nWL8b352ZL6x1O9LqWsqFyQ12+XJmdhvein9+s=
*/