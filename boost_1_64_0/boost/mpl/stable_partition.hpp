
#ifndef BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED
#define BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/partition_op.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl {

namespace aux {
 
template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct stable_partition_impl
    : fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct reverse_stable_partition_impl
    : reverse_fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, stable_partition)

}}

#endif // BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

/* stable_partition.hpp
0VyBXZj9zIoYxBlQdXWbdatx4Aa1WCEnNrbdpvrgE2qpWwjajYvfVlv4SgyK4KARACLjZmTqbpXkfNFtB0qRceeb6muRtaMOWDvqQHRHHYjpqAOqowBhOxa4606b9fLhdhr9Et6feJ04XbjEr4cslKYx7yqW2bVDdyhRGt+nSeLrjPa3juXjmVfUaRLO0LoK+Yi3EYrRbjaYUjfKLtMWVsnV0eHrTEzkcPPuRt1b9J8layZnVaIUp0r2cPQdKRcpf6TpO1JXYjaefKsE6YBgA5HmJN0IpHhyiQaknQQkfBZA/GyHak5IWmrDudji1Ah4yElk3XU0xUUaFPjSMt52IfGUyMS/oP8LBNt+qNCfDkFSO+3BnT+SPKOgvN4n+PNRwGaIHdjk2c9/BSshvoj9KBhrPu2k1jG/Hit9BA/0u1Q5HocCfZhbaiD+O1XdWcP4ns+StfDLkjlMXH9PVX+x0uKDFqUvU/A+KHPFGsWQAUMFCabSeRR+9E0UXJ5vAEYkOXxOuNwzQGz/kn20e/B5FvDu4ZdP8t5luOdYHXmNihwnI3t4ButIv4rsz5FieCvbHkFbUOb+7wUhj/FyHwzjcyfxjvORAfI9Q+yat4iLSYKOpYgAbTMmJ1nREYvQVKx4E2x+N+UIzqPAqWqxGlNQOiYApm2Y9ZNqVV8QyDG8fBXy8lFIVOIsVBJO+onoCnsBkH88H7GeLRYmeCLEH2tYaF2dyl4Hqt1kxaUYFinoyyR8cbIbC5rY7KZs++JC06VdSIQF2iLASqXytiWSBUZV4y/zQgflnUvAEVoxRpihqMaL2zjvCcWJpvKncHJ4rdKpeOjFn0TFzf3fRqNRTzh9ZROwDU/RE26YZtnHpyieWYtOxt8vlUzS3rawzg0E7aMtRtVYeW9eqXEKtTG+vBcmAxGp36vHZOM9Tnlf39Hq8gbi3er/9VnQC1z1cRKlhRWCZEHNKTN1zw3ogohJ0UXsLEqzRZrq4uxS42O+R5uQPuXg/vezTehHGdfdDjYF/ElK3ZdgTsCeoIIHH5Rb0P1eG05M3MxdvKpFaPI64H638Vc63OcD9f3Mg8x6zUx1pyj4eJAkJO7Ph/2SI0d1Ts41XOdyhC/12hT3EiLmhRmeL3aYCYqsvh0PWD0ZHti8L7X9Fu3wBh9c+ACD9cI7GrE7We0305k16s17RjI3tTwtbt34k6ZFwv1DNvO32W6j564E+wc1GlddL7EuTvzCG3V8bH0Dub6BbhKct6S+gWQXMX59iO8Ypz6mBx1qND0AvzAIsz59LfKMWmkXR9ugDse9IGf923+M2Oin1YwQHJU4KISwbeC9MlqY+3zNQfkLiA9s9LnIl2+PJBIxt60pEMTnIhBdwTE6hLSgUHw7gzjFakf/xsYfhTWyKnu4gMq4R8AwSJfR3VJGL05vs9l1Ee1JLjvyiC2bsfc9fyM7M9751wuJ98v9n29mPxx4Stqz+YXRg4aGdVHSVsecQ8whAmAXJNlrR7c/xVJ3JTE6l7hoUcZzlaqMbatiyhjKZbhKvQ6UcXVkGZngxNPAxf/U00LdvjWEPcbYpxVU+bFQCV2ZJAEZBK4fsCTd+DIAsiZscd0Vk6WXzOKAvPBhmWXHXOOwLcQIeNf6ciLsQdj8ke+7ot49Ue+1Ue/DI8vTflluHVglfMc/tFippffyiC9Eyxs38RXNHTfhtZ5f0abE9jCjpa4QaxD9eWEeuocLiD3/ejJCvhnckl1mdFen/C0/AzDxXayExq5rJcrHid++KjZeQqEJ8PLb4xjFiZN+WCvTv7hVpW+evg+sikdvcXyFjZxK+7frpBpGS8cng86I5jY3Phc8ETU+GWXGvLt+0vhQCfk=
*/