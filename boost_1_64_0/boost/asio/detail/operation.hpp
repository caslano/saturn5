//
// detail/operation.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OPERATION_HPP
#define BOOST_ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_operation.hpp>
#else
# include <boost/asio/detail/scheduler_operation.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef scheduler_operation operation;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_OPERATION_HPP

/* operation.hpp
vzwTxYYi26LbYtsIY6K0ITFtpsN0mi7TbXpMwwyYQdM0Q2bYjJhRM2ZKi63F0eJscbW4WzwtRkugJdhitoRawi2RlmhLrEVaba2OVmerq9Xd6mk1WgOtwVazNdQabo20Gu117YH2+vZge3O72d7ZHmrvaw+372mPtB9oj7YPtsfah9ulI7HD1pHa4ehI73B2ZHa4OnI63B2LOzwdx/8XASFUz5iaGVUn4+pjZHtMW2sqx8xszWn1tdraUtucbZltOW2L23xtgbb6NrOtsy3ctqftQNtwW9+m6KbBTdKe2J7ant6eqeMYHcMBjh3oqO8wOzo7+joOdMQ6hjtsnamdzs7MTnfn4k5fZ32nsbluc3Bz8+bQ5r7Nkc0HNsc2D29O7ErvSu12ded0e7p93YHu+m6zu7O7r3tP94FuCU4Uk/HamC2DWYowO05mJchsxFodGzM3uja6Nxob6zcGN5obwxtjGx1tbkYcaou22Ta5NhmbzE0Rxupsj24e3CxdiV2pXZld7q7FXb6u+i5Ht7PbzVEHu4e7U3vSe3J6FvfU9dT3dPb09RzoGexJ3JK6JXNLzpbFW31b67c2b3VvW7zN2Fa3rX5bJ1d8WK+5OVGmIpuZaqabOVxvH9e7XmeWeT1gBluaubJ9LXtaBlskNJE3Lj+3OlK7HJyzk5G4unJGR9PXFe7a0xXpOtAV7RrsinUNd/m6je660dkIdjePzkh6j7Mns8fFKN2M09Pj69EbcaKoUjc5NqVvcnLGOZvcXJ3YpmHO2sYVcpy4U964T07cDUZHXUegI7XT0Zk+eo1cnTlcp+ZOs7OzM9TZ1xnu3NMZ6awfvV7m5s7RaxbmmulM6nXT2bS9eeRcSUd3OvPK9WRuw1v2bIlscWxN3+rcKpGJMkmHvPXA1tjWxG2ObZnb3Nt82wI6j1GeKzS4hX/F2A45R+czvWV4Y3NbiHsvyr0ntlTR7zm4O92j9+Yp33Onik2vxbbUbYu5QuJJlRC/iGeaLvbk02vC0zds9vGUSWsiz1g6z1gOd5OPZ6y+tbn1L+2bL3jrZBjFX1AViAhEgcvzFB5EZQSiAlGBqEBEVkZWICIQlZGVkRWIjLHRwdpFICorKysQFYjIyspKznlzmnXbHevG+N+YwnN37/Ll/b3nPefL18l3c/TYGmTtvgvOm+ch+IrO++cD8JWfT8DX8rw835zb9w10CO4A/ZF8P/w+w11M/C4239tFg7XwSsQXg4v0YgQGJxeLiyX7BnVpXobomuiyf8luHql72LvoWvYrajNAH2U/FN5HJfqogQqxh5LJEF00RoVYnfVkNwmumlftq95VfDW4Sq9GqNVtZwWgvQ3CYtCegvf8x4lXaw2+gp+aqFIHNer/NFDPLdhz6IXguums9cBYin7I0RGL6+V1iZ6wadUV0bQ/TabD6Wg6mbLK5XQz3U2bqHNnFs36s2Q2nGXomWI2n6284rtZA5Vp33RvejfxzQB9NL4pbuY3q5v1zcb1s2nvoV6NvIVe6t7rJmrUGtULzprQzs5Z72wA5RxBEyZnC/TX+mx3Jg2Dbvahm0PUdAKdWH5XfrdBRW/rmZwPUdHbeu7OWc24Vrq5K90WTAUXTdTybiXnF2vvr+DyfiXHqiWUmCrMarLX2Gmo5tjrufxh84NNGuw677gYujhERdlxK1R0M2lwthRNa+FjAvWoeG1jZUNyiknAJmraEB+sWgGtZOVWqF0JLduignbduGYVW1C1jtcwux57HQtoG2u5gsKxntvrnWrampazzcxu2Jlt9GZPapehTpOb5U3JKq2a9q3hyu9WaZiPoXeji+xi7E+oc9m97OG5xJcDfzLVRLq9q4dallwP790=
*/