//
// detail/cstddef.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDDEF_HPP
#define BOOST_ASIO_DETAIL_CSTDDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_NULLPTR)
using std::nullptr_t;
#else // defined(BOOST_ASIO_HAS_NULLPTR)
struct nullptr_t {};
#endif // defined(BOOST_ASIO_HAS_NULLPTR)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDDEF_HPP

/* cstddef.hpp
W/SIhWKRWCyWiG3EUrGt+IT4pPiU+LTYTmwvdhC9YpnoE/1iQCwXK8RKMSh2FKvEarFGDIlhMSJ2EqNiTIyLtWKd2FmsFxvELmJXsZvYXewhCmJPURQToiTKoiImxZSYFlWxl9goamJG1EVDzIq9RVMEoiXaYpPYLLaIrWIfsa/YT+wvDhAHioPEweIQcag4TBwujhBHiqPE0eIYcaw4ThwvThAnipPEyeIUcao4TZwuzhBnirPE2eIcca44T5wvLhAXiovExeIScam4TFwurhBXiqvE1eIaca24TlwvbhA3ipvEzeIWcau4Tdwu7hB3irvE3eIeca+4T9wvHhAPiofEw+IR8ah4TDwunhBPiqfE0+IZ8ax4TjwvPiM+Kz4nPi++IL4oviS+LL4iviq+Jr4uviG+Kb4lvi2+I74rvie+L34gfih+JH4sfiJ+Kn4mfi5+IX4pfiV+LX4jfit+J34v/iD+KP4k/iz+Iv4q/ib+Lv4h/in+Jf4t/iP+i9s8L5Ivli+RL5Uvky+XniSSSia5FFJKJX35CvlK+Sr5avka+Vr5Ovl6+Qb5Rvkm+Wb5FvlW+Tb5dvkO+U75Lvlu+R75Xvk++X75AflB+SH5YfkR+VH5MflxuUB2yx65UC6Si+USuY1cKreVn5CflJ+Sn5bbye3lDrJXLpN9sl8OyOVyhVwpB+WOcpVcLdfIITksR+ROclSOyXG5Vq6TO8v1coPcRe4qd5O7yz1kQe4pi3JClmRZVuSknJLTsir3khtlTc7IumzIWbm3bMpAtmRbbpKb5Ra5Ve4j95X7yf3lAfJAeZA8WB4iD5WHycPlEfJIeZQ8Wh4jj5XHyePlCfJEeZI8WZ4iT5WnydPlGfJMeZY8W54jz5XnyfPlBfJCeZG8WF4iL5WXycvlFfJKeZW8Wl4jr5XXyevlDfJGeZO8Wd4ib5W3ydvlHfJOeZe8W94j75X3yfvlA/JB+ZB8WD4iH5WPycflE/JJ+ZR8Wj4jn5XPyeflZ+Rn5efk5+UX5Bfll+SX5VfkV+XX5NflN+Q35bfkt+V35Hfl9+T35Q/kD+WP5I/lT+RP5c/kz+Uv5C/lr+Sv5W/kb+Xv5O/lH+Qf5Z/kn+Vf5F/l3+Tf5T/kP+W/5L/lf+R/cZPvRerF6iXqpepl6uXKU0RRxRRXQkmllK9eoV6pXqVerV6jXqtep16v3qDeqN6k3qzeot6q3qbert6h3qnepd6t3qPeq96n3q8+oD6oPqQ+rD6iPqo+pj6uFqhu1aMWqkVqsVqitlFL1bbqE+qT6lPq02o7tb3aQfWqZapP9asBtVytUCvVoNpRrVKr1Ro1pIbViNpJjaoxNa7WqnVqZ7VebVC7qF3Vbmp3tYcqqD1VUU2okiqrippUU2paVdVeaqOqqRlVVw01q/ZWTRWolmqrTWqz2qK2qn3Uvmo/tb86QB2oDlIHq0PUoeowdbg6Qh2pjlJHq2PUseo4dbw6QZ2oTlInq1PUqeo0dbo6Q52pzlJnq3PUueo8db66QF2oLlIXq0vUpeoydbm6Ql2prlJXq2vUteo6db26Qd2oblI3q1vUreo2dbu6Q92p7lJ3q3vUveo+db96QD2oHlIPq0fUo+ox9bh6Qj2pnlJPq2fUs+o59bz6jPqs+pz6vPqC+qL6kvqy+or6qvqa+rr6hvqm+pb6tvqO+q76nvq++oH6ofqR+rH6ifqp+pn6ufqF+qX6lfq1+o36rfqd+r36g/qj+pP6s/qL+qv6m/q7+of6p/qX+rf6j/ovbvG+yH+x/xL/pf7L/Jf7nk986jOf+8KXvvJ9/xX+K/1X+a/2X+O/1n+d/3r/Df4b/Tf5b/bf4r/Vf5v/dv8=
*/