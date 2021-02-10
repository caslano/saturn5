/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
SAqeuMGiJ8pUPih4pJdnwaMgXthTNP/ESFSyJI/npZgdvDg8Wn2mlnYU9NUcxo/AsDQeb1R+qPp0eFWoxVD1NuvGumjWlVtLaJ0o35RslIOhCntHfHPGAmB0otbAYzhsqappAagmCkIihZ081sOqjsk6JhlkInYZCfSIwxNL5Y9Gg5pnTijqEJG2VZ6tHxcyxsQzY4ybI76YI4icRHcYjDETWXWqBsankSiirXhxjhxVixyqjiZHjseog+PsE+QxECjKkPrp9FtMwKP1CEh11GLLjjuHDuly1IhZ3UQHgCgYdY+RGFsbULJmPT2UTC+8x2UOUp0h4e7zUKj7ACrC9fg2DJg65bIXg9FHOfV4+XwGx5ToOhpigFjc4ZUV8Y3K+ASASl/hpxyaOZJdthp/XjROe4064Ztju6Pjf38asALz54ppyFxIBIOnRgu6sNCmJsd55asX4FojWXNFMkORCjVhzaKBYJVXGM+ADxrwQCtfWjG5tf2TeN0Yd0sJbVFkYa8a0iad4/pnzyOz9o2ToOyh9aw5I9R5yzs3mbaaNNLNkndKV87R4YUl71Sd/5j4X0zcFxtQNZ0t5AW6oIM0MZGSVxUKEWStnyYy/7fYaMkUq8myVVpUPMWHB7ZOi/5/jv9r5lhNljXHJoz4
*/