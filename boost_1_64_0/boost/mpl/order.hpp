
#ifndef BOOST_MPL_ORDER_HPP_INCLUDED
#define BOOST_MPL_ORDER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct order
    : order_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,order,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, order)

}}

#endif // BOOST_MPL_ORDER_HPP_INCLUDED

/* order.hpp
dOZV0D4/dYKX/JqeI/B4ejfX8NlNZm6+rHqAuokow83PFxlL2Zs6OvhL7U3dy1X8sVSx9HlUkentdFF55R3jiWap8V14nl7VQsODL+rsayzZh0j2nltx6VFHGd8ieh41cCAH2c33/EmOrwRCb92Q8cY4WDXT0eG0MZxGBU3xkvpQ0wOxzCuXeXH1/vKg+IXrxS/s0qystbAy8zlh5S25U5DYqDktk7C7NfZqC/YVJnazeZVfWSZlqLtAXptP4Hvm9nO96B/1m29p6wxR7qDL9Afh1x12t/IH3ZFKWm1ih3EQIQQziF3xGWkXfBKnjJfRCSeLcRLAwfrby0kcvmmpizqiszSYDUpJrM1JLDxXxz0NV7HxJXPG1VFqvLPS/N7+QQT3E/LR+pP7Evy1/qoyZZcp7AnSI64+lKufrnxxK3QFE5+j69Hg2ovHxCe4zOrF/w5jTtRVeZTpkW5qVH5B93jj/qUgJlr1iKBmVnC+e1lnqJuIeo7uKClgoBSAcWeiqVqE5k32OibHXUuTaKcTGj8ZQWg+TU32fTwhaKLhGVVZPbmEa7xElk1UlPXoXbRQJxxr49ksaCAGkdc4gYrHFYaZNMAMSKb9gtKY5NRK43eLIn2UF6ubvTW3epkmm0PjFjIvYpkYtBDFGFRMu9zCNe0hNXjLJpdTd6LtIpNYYElbWG2Nb/xcGhQWgnpx/BK0aT2vzm6k0aUUQuz5BUhhnDnenPEs5ewFKjt1snGg5NW+RpdWgsfbgIZtMSX3mt+7PtlKoP2nQ9sg7y4l6C8/lhT0OCQcxkXL+D0tsGGQ8eE84+ov49MXQ2jMqMqNJCauyiNNAf/lE9KgWK//xaKkgEcuILwBmEOcBQk9k6CWoYkTjkLPmpPNaiul24TSB3SR96193nvBnJ8/9bPU+blukTnPoEXMYWPzfZZRfkClOZscS+/sIax1IGfCbXnUcMY7CKr4I0ehkUWaQktMaazIpaFKU3B/gMmn9f3BMcT/5Q4Grfw3Jp9R86EPmXmGcoOJDO5NVK1hYdJOnMt2gkbpVHMCR22BRpN7vmWWERzIYhEwZ2iTBAfq/46EK/oqh2B0eVr554lIMYHfrzwb20C2dIgqxaDfdwvSqFjNm+5wZQL7Mtb/VmJ8Br9tVsk3EOPqu4Qx9mGriZolxeVXnGD0LexvbdyR61ngZPSn8ypg0wtbgF6CXXuTKCjomWSdtVE7xZVMGA6z4t2szMomCR4q99XgbkQ0Yc3vwDYbwAreJxmR7boH3GOGXT4JN/ia82NjuzQ73feoBPE44/PzuBG9YVxPeoYo50HmbJp9rRchwV4zFrCX+emqX+r5tZ6/ebdn8Af32J6vGVAe5jJOoguA69lOXNbXp/vrynruqy//iToAw9eop5MdMMb44dwUrgl2DPUG2/p5bFBOFPVWdRg5HyYFLJnddpP4NzBy2YvwXUhVfDgV3Vv786wCbXu8OaUoXyMeKfMLUzmMyofnewl5J6TSj+ogRvr5ynHkPINytuHeFunreYiAJv1/rLbQPzJ4n56eLGcfdpX4sIu2qpDE5JoqX0blkcGNGu9uC973Nd7FPLFzlxpLhDztu7zb/HLDKoutZFIPa1JLLaSO0KQ8H3BWtA/zt0OfQ3xESZyXnPLxRv3j3J5ZP7XEeLSY95JTXmZMkPkEVS3s3hemdHkPtTqU99KDXN7in6QvL/rehyxvTKv2Z9FfFNVUc/DWOpRneqObVAC/5176llwluVewYNxncMod0D9Z4qHrwpIxlO9yaqOavYcs+UrcUFnWlcM5XMAqhuxvPpBEGklIkc8F2xSBYywEfIolDEt5lpS3XWBJnj5DvmMtLLVzarcKTPw=
*/