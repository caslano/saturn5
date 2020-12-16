//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace compute {
namespace detail {

// default = false
template<class Iterator, class Enable = void>
struct is_buffer_iterator : public boost::false_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

/* is_buffer_iterator.hpp
tV2vXtt+VJ7O3/u4cedupCnTYcyGS3WNDUna5lKn59pjw8Gn5UWSEl0OP6PPFGgwYk34s8bBzxwFbrbnbzi2U8dvudR/Xr+q/jG5vtr8Z0vC9+gl9r/kGuOEIm1mRL5sP2nK9FgQGdpPmhoD1tS+JkemBEbapcDoG2q0W6PgepSZ4F5qf3vWJk1GrAjv7qW+G2lKtBizJvJ7cYiSpUKHCRv2/2AeEOOUFeE/ikmUDGXajFkTWYtJjH05VJ1zhm3fNmtfmRZD/n9fdZoKXWYE/+w1jklTocuM4F+8xjFpKnSZEdx4jUMS5KjSYcqGyF/lzzHBv5sTu3upa/SYEfyb64BDEuSp02dO7+/isd3dP30z2+wfvXfQofmHswfitgPbOUGPL8cZtLdqxZrwP8xxjkhwSoVL/VNM4mS51H/if9VrdJiwGunL140PcXLU6DGj/Nv/rTsSo07388bsC9rgcgPxGH9FHuyLdyNibHZrctyMODkC35ADhyQoEPc/Jieus3Rfu3+X1z/UhLJ8S33PmRParXsyYM3lPi8OKcrMCMrpStQYsuVuA3kzZM3JF+VCgxFrrvQVtSNNhQ4NuUW/aR9tNhyMtUmSIktC33I+R2So0mNO6NvGhbuRo8mYNZf6jnNIUaLNhC1Xm6ghOWp0CX/XOBAlS4U2q916HOupev/ANUKS6I/VY65OHJPheluPSVAlR/Cf4jBkQfBfcuOMkeNoMORm/xL/i8aXpn4P6PxWzsT+bmzoeu9q3MnP2iwIHfv5ndk7zx641o/V6SfymakhCXJU6XO8W1MjT50+C672U/UjTYk2Y6pzeZH/lfcBbvRrc4k8DUZs2F96jTinNBlyrd9okyQT9V1zKX25GTEyLOW1J+8sFbrMCcprtVu/okCDIWuu9n3nUpjKX36hn3ltt05GWD7zHwQD1/qePpGhTJspwe/bT40hK8LiXI8Tmoy4mph3I0OFLnP2dmuFxMnTZMyWy/3COWSpMWDD5RbGgxRluszZ+6VYxMnTYrJbD+RKxBh9V4zHqO9jHUc47Rw2WPvR5zt87TuzvxmTokCDPvPdWguX42bEyFBkRZMR1wr6eYpj0gT8zipB0e+tctfwOxBzbuv94+SK/t5OkwnZK/k9DdEriEuZzu4+7g2XcswZhBxzNe5Gl/DZ/U6OM4iTebj4Z9Oex3W6TKg97Ox+nWZ+EwrpBzcjr+8Hj/3fepn93fqfcfvWmf+tgVnjUP41+9K7NTV7zAllzEtiFGgy+/+aoxyRokKXBf9fc/RuZKkReow5QoxTGgw5eLy2yVAlJ88afVZEHue6J0GBBkNWDB/veiD8BONNnBx1BizY260VGk1qgwodTp/kuMsbd4b/0lfSVzqrv1X7vWRam08Sj0tdWe3tO+bgqsboGsaBE1p3P/t/75OfEfT60W6diTx1hiwInkcMjshTY8Ka0/OaE7QZsSQUNnacQZwKbUaEb3v2wKU+ZXycu+/YpO21bKNkvT64hDl4AW1fzLEXNbcv4twLyt2++sGZ/J8Bc9b+5Pn+txZFhy0383qcOgMWBCOOYXxBuXI95w5YXFiO+/pyEc9Zci0x70aL/6/1kKDBioi2b0ScHH2SF3eufC/3T7UhSZEmQ5bs/Uts7kaaEm0mbKn5rEWfOaF9n2PjiCQFmgxZsuezTtciSpai9suX8jvaS7v2aV5GX9m/rFyJcUqVHjP2Lmc/OWKX189PmYNh55zPeFGkw4y984tDistFzCHSdJgRvKC+EadIdLdmR40FYXW+HicU6bL4zxju1sRoMyOkhjciSZXwJT0nT0b/OkzY07fc5eWxbz9lukzZcrBb5+OE4eXUn73Ley9iqg8=
*/