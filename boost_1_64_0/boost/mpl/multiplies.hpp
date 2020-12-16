
#ifndef BOOST_MPL_MULTIPLIES_HPP_INCLUDED
#define BOOST_MPL_MULTIPLIES_HPP_INCLUDED

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

#include <boost/mpl/times.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// backward compatibility header, deprecated

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_OP_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#else
#   define AUX778076_OP_ARITY 2
#endif

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(AUX778076_OP_ARITY, typename N, na)
    >
struct multiplies
    : times< BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , multiplies
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

BOOST_MPL_AUX_NA_SPEC(AUX778076_OP_ARITY, multiplies)

#undef AUX778076_OP_ARITY

}}

#endif // BOOST_MPL_MULTIPLIES_HPP_INCLUDED

/* multiplies.hpp
4FbVyfpMsrolKISjnazNknWMRvid32Q9KVmPehXCHU7WQsl6SLdwjc4K3RisDh4NTI+ZtGuEvnQGloUmeURwMKVx8Wkm7UQq3g7Fgyata7CrKnueSUs1vhUnupx6XmiNau0JAPQMuQrBGlLzRY0I9TbhwR4HLinXHvmDSVw8DDhPEwFb35pVhls4iL9thHK/0b74tT68306E/Heba79Fovz5bY3y4GfXPJK974li2Hm0hF8o0PvoX+xdC3yUxRHP3SVwJBdySNCzRo2CFouvGq0PxFeJVUs0QWO1RUutttezWKsJUjVgDI8cITzkLWBBUEBRaaUabcQEU4mW2qCpjW1qI43tF++qV3uVq42mM//5du+7fN8BWrHaevyAu9nZ2dndmdnZ2deZWckB+/fXWQbsP2boARtZ7tRZBlEWywnb62eqE7ZHYY308ODrOuutyPoVnfUFHMkvoDvAXGSSLXdRHK2IVIIIlf+2JjIZRNyaSJiIoOQn15oOQydfVVbhx11mGwfCGmN2+K6mcRtobL1TTytx5r8gOd+9bhmMq9wzJfucjiAc48zb9ZWqZC8e9yBbzWuFeTMmwpPoUkfcu3DEvQurhK8PNEeErrz60zFX66KSuulJdrUJvYNaoabLWzk+OfDTXXGE5JcB/Mmgao9Dg7namclBLRLVYn++4CH4jS8VyBD/1RvkhPGpPOHtgF0F/EYLpQP6UXrYpNQFY1xAZrCQlOtAFev2CS/Zq0EZ1DZfb12QmJaH1fKTV6sL64D/pjjlQDg9eKgusxJlniFl8i1hRtV9Ej0P3kG1CLmNdyfJlSmluOWFdstDFq7hccJ47gaZLvJdJJWX1NPFa7hYpCSf7ECtOWzsqCvfMR53sv1KeDYnnlT1k5IeIdh49A6p+usE5/OYFJRj706EIXKbmTtmBqqfdpn97qr4qrHuMg4FHHevZecrlzCmXwllZgk1BNdHxLFGvHwW+KViiwOUP1jsSplsPzE3mnzniSmf34/y7mmgjL1dyMJeKsIF15Ugq+oeWn5i5sQMMxKKP/0yIEVaIIOuinEU6JCUJ65VRvrY4KWaqWplNaZJuViMP0U2LeFgMGbdIwRAYlSzKzNvBs9NnE7jdZYZAzP1abxvs62G2h6QaWpGCw8rUJY/ZiaVpYPvfMSIgC3gj4m5MK9InPa54Ld0E30PrLZPlTnRoEgNWUhKlLH/BlQwMxhS6HD8T7nZ3INrjC7OrzwAQufD/PJNWWOWq/lK8R0K3k6qh+9tn+rh5VP3Ueu1U640l91uXGS6ABUHpoQvvyl3Beln9vdCb6Sit+0bzvTy9pmexGsemqXff5P8q1Tg0OmyzBj5KxlaKb6jQ4W8vU9Ce8TI6PIETx/IxGKj+RddyIBd6FvIDNMQIrNP+WJMnqV0OR+pVMtzViiTRVGzO2AZDsEzSLgS4AJz7nrTdKlqYbBVOw78TCZcYb7/87aPbq+kWj+4dO7e1w9eTxO/P2mBc7zfMy/9esWf6tOWh/TeK9OmG9vm2/eXL6zfO/+/vnkv6x+qfune55pyK7/PNeXy5PtcDAllGL+WjTPB+bfhZ9OCD/I+l/n+w3RZL69lfyZcIjtbSuSNxmfvZBfTpYw4p/lvDuBZv95nqzkt+SJeZBcNdX6ilMVwqdhfYCx5W0X1Nr5geryu8qEywQnGMkyP7jtXfKDjTY71wUN1XZke1uuoG0ryRCael8PpxOlDmIcnXQzZlg+sZxWWeuKOsLKbks/gBTw8r10tWE8y1s5dNlIFIHVbSoGeJJa2JKfLBjFeL6+G87j3XtqH+fiYmpT+g7+aN72e2WN7NAobN8gnHF3ce9NXeYQFP4ji1i9ycV8=
*/