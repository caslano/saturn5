
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace mpl {

template<>
struct at_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef typename if_< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , T
            , void_
            >::type type;            
    };
};

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
DzLR9pekyseN8zzwB/O656kvqIBXTkddy+TJdW5XvWN2k1dWs6Ve+GccL+/i4O6JjFk5DmkHpb403XqHy27FdBKf9kZObd2JvRi/jMU6HI222bK11uaTtX1hYZ1459rU5TZgjHpHLGd3+6wNss0ueyV1/L8L+Rbk1zu8Pn9AWvttHX9z2gw/UXcjfuuP31x+fXVa7MV65Mca8602ux0Dpj61XN/4Jajw9THa8zvvUbdb83cTyvVRtoPj50oqZr11Ms7AwXqTkQZg2ZQlar05fNg/ftml/L+dLcqR47BbDfWh1mNcL+oRY7tB9TiIfgXXW8TtD9RnHPK1R43anPxVrZsNEesmeBw+h+PwO/L43B5pIMot1ra3wl/Q5PVie6vk2l4df/r/sIvrLWU9FiElYL1tS4zHva0OZ1mvHHhDC06mc3p+XqpeV0od+huwS+odtbJX2+dTILYeaQ8s956ixbrayOXd81y4nugluvf//vR7Fsf+R7I+9qTfKU8Y/dZDKWz1OH8YZ4fV9eb8ZdRbSb0k6g2l3qywerVyvdsrBwn2Uq+YelNYsWOoN4p6C8LqKZ/9DV4cQIzu2iqtRdSKp9YAaq3sScsub7XWI9tLqu3H+5dcpEHQ6gqrJTfXyeqfBgeCE7vwr4mHUfITGAtj8EY9PhO5jm7P1Kul+lsSfmvPNfymzgK0qvE1uz6px9cE18eIHSTVRrPuR3J+YeWT4eqjyfVnjuGF1Eqg1s7UWtALLS8+4gaqV3q51IvbUVKtgHr5SInKOStIL0jF35tt0vfxR1Ml3t2pcy6D6rWd2m/zvLaa2nFPRdB2u7rvDH2M0fsDPijntgRoL0eS8XvLUzy38VzYFz5od1h2qKvXpcC5rYK+l/TnuY0xdIPBISiX2RbyjmyX2zXP69BvZq112iVAu86xHnNCYuuWh8R3PmKIrRv79OZxhmO68yaEycvS87btzpsYJi9TMtyXzYIjuJDMlv1qvajxfUPz9Dz9AqjV8Tv4LeReRq3jlajfwv5qrIw0T60Xbfl2LM97HKtRYw3vW3jLErhAs+4D18PlrPvhPGaHISWh3OKnjXXvlZ04hwRfD3t/3IaLn8zVr2s7SarlUD8bKRn6nU9HnG+MjJ61e4rrtPC3eq+7UW1M0a8M+rWOfrn4fzoKKQV+ZT6j+qX9feiHpRd18P0IaDW5tPtH+reB/w/+FdXbTylwv8x2zABJtRL6UYh0GE6ebZofQe3B3jzTXffnhzD+bArnD+9Z16M+7oQvg5V6eyb4/gXbFijDVarbYKzPJO6t0bwO7sntSHmW26FuQO+vd6H+Q8v0cfOtHR8/9AElvzbm8dw7fr5y/LiqjU/1eWnBtWLc/K8aN9dimtjnwL6IxdsExzR9vY0Wm/QNOALcCGrlYGyLjQ1TbhPL/QKq9y59AuXYhkfbPky5tSz3Ebgj+DH1UiS2tdkGT8GHbcAESbNjuFwzkofLncjvFiQnl9uXsZO5oAWcCiaCeWAyWATuBRaDU8FpYA1YCvrBA8AWsJyxegcyJq6SsV4LJLYxQQf1ByCdIrF9QP3dqL8759engoPA4eAIcA8wHURqnQCOBCeDo8AicAxYCu4FTgczQSuYBdaBE0FZuz6w/tgWZBsxUQquv4MqtOUaJLbtwFL6vwPS4VzubPp/DjgAPB8cCF7I+lsITgQvAfdlTFw+Y+EKwKvo/9X0a5bENhk4knrbI1VRr5nHQwtoAY8F48HjwIHgCWASeCKYAp4C7gGeDu4JngFqMXhsi7GN1hwSg+eijhtMAI8GE0E/OBRsArXYXLax2PZqDonNvY/reQAcAD5EPx8Fdwcf5/9oCZgOPgWOAtsCfrI=
*/