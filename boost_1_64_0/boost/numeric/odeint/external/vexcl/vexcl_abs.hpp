/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_abs.hpp

  [begin_description]
  abs() specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/operations.hpp>

namespace vex {

template <typename T, size_t N>
typename std::enable_if<
    std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        abs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            abs_func(),
            boost::ref(arg)
            );
}

template <typename T, size_t N>
typename std::enable_if<
    !std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        fabs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            fabs_func(),
            boost::ref(arg)
            );
}

} // namespace vex

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

/* vexcl_abs.hpp
1YifYZNmkPx294pqxFYLuD9xdklQ1yWKhriQHZfWMFwgWLlvJOHe6nA4acJpw2+roW804Q4T3mT5SZhl4Xd69fYn4nLOOx5Qo+m5/tarDR3lCp+RN/SkoU80dNvWJxn6VpN+iqFvNPSpht5h6B8x9E2GPsPKZ+gHCp3rzvDe3EGga/sYM1btkbENXmTOiu4D2sdq5Kf3L+eI7QHHc7j0EXKw6gM0D72vOFfkBSb3XN884gvGkifDKBv7IxUGvUbWf8RLOeyaXvdXC01/FXUuYZHRXYlJE+UbfYmpD7ZduZsv7YvlVft+2+QuobzFIeEH8E1N6/KBcTyrXGPO+rJvbEE85aO+8FqNkY99tPgHpjx70z7Yf5Mmedh9Wf09fK2p483GZo8BfV2Oj91GuNjFkf6Obo/x4NSNt0AOSfQISXyluXUknxh5S/vCS/fBkVuib6HvFht+3PhWSKxGRmnue6ZSMRzRj3dnHznMiZU3cJScC/vdHqqV0UWLv1r4YV3d29/XlnDx8rZjXOTgvqxb0xpBTDTnqaxHtuM872sNk6df1+014blRwtj9OoYRzzaYZ00yDL06v8wm3w0m340MI17fF4Qc4fV5T43c9xI5sWdNW95g8JsMfgPxfcZu7f2gtNCho1z6ZkXfEEHfwrnLoWVB+3wecxe2J+7xRPsd+XSN8qsAvRxUQrqsTRiWtZy+q39BufLbVp7rx+Fz5A+7JX/BIw6/sF+HbVLO4L3acq13+CXQ9cawLifiwTO3nF8ijnsamBMDx7fLNe7LwJ0U+p7c6Mm35CZPviPP9+Qb8gL+7e4AeR/02/Fcfjv+So3+drzq0JXNyxbMmDU99DXYxOb3+T2M9O6seU3uN+WzzPhytozXpImdnCv1CFruN+XzZLwDPXoP7BuqzTLMb8Hy7XFyqK62qLra6v4+H2kKnZ7Fr+wFSq+FBX1tM/XnWwYH9nc5cBo37zH9wrdrZF6uy/QdsUuH6VffTfXc6BJb9hHyHfy7oNnv4JdJGYHta2vQ8iI4lDLmT8Pz4TX2W7assb5XE/0t+0qzxirkea8qFeZayPDL/w372hq1L0/dUKdIZ9dQotPvi+6ZF/EGd2PNwGW038h/qGy/ijy17d+k6EnQ+81bQzcrOuJy/FzconXIdqDf17Lv6d7Gsep21pfcQw3y17LdSexdxOberZE3rPqpn3uY5qdMw7y5BuO+jeHH9h7J737ye4Bp2MaDsuLO4PEr433p0HdQ/3okIpV/nl/UDM+v9uJh5OHH/dLnzzOBY1yaw/rj7QG9AedeCmAIv6oJ7tY2rjqkGc84tjQf0rzKHXwJR7n2FL3nE1vWvGzFqqNWtzS2HL7ayR2KYV/9a+rp16EytB/PGay8kYe4ZYnu3r6tS3uDe5jyRl5LbzretbJja0rvxSO+cXO808YXZfHx9YmFmBArWinTRNHGZdId0dmX7qdPadIqmE7TZvH9l4dUXVYOQSd2r6rEjCuPqLGnir9KfdcRmEdpg4+ZeeQOhPWdzieIe5I41L3U4xDr3u2pmnyeYT5p5vNb5vMscdH20hfvaQ8dStARzGtE0XM1shf8vO4T2C7tPsULzPvFiDmBxf6B2Jf1+Kf4Npq6eIX4Pzo83ybiuZo+2vNLNTxnRZvdiTDunmxNJ9x3Inf/tdB84/kTMKO9eDvOSzCN+66YSvS39/pKydjenxFfqnx4Z97OfFXZ3Lgh6JU2kVumbUofXPP+Xq05JJ3Rs/IX93szt/pbjdIT+b9alLvGLzJnqcfwrFaJGmv9tHuWDvTNozeV6or5H+HwtEs6jVMR2bVXJIV90nNqLHhPyqvO20fvEf9XzSn/bdraiAlBWXc=
*/