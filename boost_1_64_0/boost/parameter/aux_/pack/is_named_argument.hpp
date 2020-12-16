// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP

#include <boost/parameter/aux_/template_keyword.hpp>
#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_named_argument = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_template_keyword<T>
      , ::boost::mp11::mp_true
      , ::boost::parameter::aux::is_tagged_argument_mp11<T>
    >;
#else
    struct is_named_argument
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_template_keyword<T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* is_named_argument.hpp
qHFKY2WlDtOeCMJk96ckNtSfdvhzJMgfnbTO88Dc5wHZ0tWb3HK6HvkC6UpYQtIVP53pqs/qmdEmNL5+4tvsiG9DXXlEcW221ZnsFtqyZkc8n/ic8TTrTLajLZssccyWAaozxKU05Gk1MBmII5OFa4rq6i6rri0hU6tXcCRVGUOkvEa3fPY0bricWeweX9HV8a1uxRlFjrE051nFeiy+pG3A8kxE5S9yfyeefSWudNb6PEmmXNdWRhBH7DrPGl5RAs3zHrPV/VE8QbT3ZCBucbe78YNOqg7UhFnPhm7r+m73cUYVRj3OiJ+Y4acjvfwy3/gDMiQZvgdzjT7dnl7l1dV15mC5x30c9ztK/7D3oDcWs8mES9wgJ87CP52e2txrezYorqyqdykzrrp1tStr3dPNrlun1wFa5/PW/MW4H6/PLLxb6b/mfY8Riou8s1i50xndyWoe/TZ173de019s11ZUW3MXn1L3UwhjrF7f+J4y6+jN8zwiZ/UT2neVn95raVnu9CzXafOs0n2E1Iqzn4FcofoqcS9BhbcMOwG3XlJubeO8jUZlp7d8v1lWUKS/IdyqdC5j37gsdDDT9lJU3E4Rtzh1faW3nU6nYv39KFHdK/Y+x3cIK+5UmOrLdNxfUGFPpRz5lZsncPOPyuxu3NRx0d8s3lf3rvP2YPSuvfcKZeckdk4q8697k3RcVhTR4AbaNBnfX6/Cc71njsQnyR4f7Vc1dqz6+LC6f57Hx38pYi/RZs/hX5H9nOvrlE42Y2Y+pz1Hmi/nOlCONqn7Q+Ta1I9W837LaY9OUTh/STr6oy/ye2P9cTH+6MY/+ePayncFngER8yxHsZPRnuciw06bVf4orvVzlUNvDnpXJaHXbm29P8pvey6WtaSiV2O6137tS+Hc2iw6uPUYboX6ybV6ByHSOylsl8J90oYD/ZcQYTvVoK5V3Zd2SsykjtvPeY6WF6g2Mmcnln/WdcKvv9raKd74nO1TB2mfOis9rze0fRc3+M9IqwTawzuQFUaadooPOUNzBNfxXK9ODMxH/gpisDZRJJlrMWufBCOYr+xMH3u8B6TKehASzC/8JvEubNbxlm7MEW8pzxd+yDU9fjepT3HHjet3ojtxckN+1K2eedEV+rvuVe+rcq6/fd6mrndEZTECf8xY++xd6jPbiQHvcY8R9/Hu58USPvc+s4dacy33ic3N2K/xZnse9bbxfD96gHZDdJzrcOnwrbp6/gnDbIlR7936A+w7n01qlP1uYv8VdX9xTAKpPtizi/maC6NTJC1mkk7YjJ5AO1jPKQVmm/y28nOG2zoKZ5x1//NjSc/l6v7ouIHk8DTkfKQc+Qr+3+5Zy97DPs+ZPKz+BF7p83m+jtyD/Bx5FfkA6cABT92iEjzDyJVifl+FXI/cizyIPI8cRT6Kmuu5IJp70ZM9f4MdmGg3DJmFXIJcg2yOWehJZPPR/sh05JuxbT3fjp3pad/GL+t8vJ4/qzDPjk70nIpKiB6r4jY60B8uLym31gLEqvKwlhKBX0F2E6300GchqzIg98+k1/2V0lnaRc1uq61uqNHl94Byt4dcm276bevs+TxuW89RpPKNPln3bfqxRZebBpWHZ5DqVht/UrkbrdzND9irWW5zd5OykybXpn6sXouDfmVFXb3ut36v9M+nHnfX+wx8qMwmy9wLbceIgO5L3lQ68z3ttA71U+rccXVvolyz8uQD49onaaHTV6ddorqfLvH2iv+51ORsm51isSPrupSdnpKvpp0J1NLhys6yxMC67GU2f978UNUV17TM0GuLrbRc8pFxf0BIWl5D25oucxkew+G34D6Ea92+jkcmIDnS/lYjButIvDw=
*/