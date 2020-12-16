//
// detail/wait_op.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WAIT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class wait_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  wait_op(func_type func)
    : operation(func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WAIT_OP_HPP

/* wait_op.hpp
3wfuBf4WeAB4HHgMKPT4FPgR8AzwY+AFojyA6cAngdcAnwIWAl8EVgLrgdXAI8BlwKNCX+AbwHuBbwLXAD8E/gL4B+AW4KfAHcAvgG8BTwM/AH4p9AdCd9SPyJ/3yvA+n11wbciuhPt3D48rq4FDmE9+BnAt201ZB6xjOyiPAx9iuy4Psx2qOuAv2R7Ke8BHgCeAG4GngJuZP34L91uRXhLwUWAv4A5gFvAx4DTgTmlPh/dZ0P4Q4/h4PeQ6M4+9nf2p7HcAl3C7vpHb823AVcDbmQf/DtZnGXA/8Bbu/8uBnwFvAuLjG6U3Gng331ed/O6LNsD3JfrVGm7vM9keiBPYFVgA7Am8BjgOOIfb/cPAy4FFbOdgLtsFmQd8GFgM3AicD9wCvBb4KPvrgaXAN9key0fAamA42z1pxXZPLmS7J23Z3kkqcAmwD9CF/4cDa4C5wGXcL5YDpwNvBZYA7+T+sRJYA7wHuBy4Gog2Q/ezCfgA9491bO9A6PcB8EbgZ8CbgV8A1wDPAe8DdgpBewN2Bd4FHAW8GzgeuAo4EfhT4Czg7cArgWXAm4AVwGeA64GvAjcAjwIf0s7Dczz2Kxp18/DTWntRAcrVBShXr5E76MvOSoBySmFgcvZCazshf9c+jwUo5wxQzhWgXF2AcvU+5L7Sll+AckpRYHJ2P3J7wvEsDpsSpR3AhQ63B+4Y3Dk4ezL4zOFgo8KvbQozGxROxNXYoWAbFFr7E/8e2xM/lN2JFdDfyvZEXXLov93+RFNtTwRqcyJQexNsa8KXnQm2MWG0L3EwObTJNibOl30JvW2J07gXX/YlwjqGso0J1b7E+bMtYWVXwo48vW1L/HfZlWCbEhb2JJpnS2IkyqYQbiXcbrijcKfhYjqFKn3gcuGK4VbC7YJrgDsD17YzbEfAOeAWwdXC7YE7CncGLikFNnngnHBL4dbD1cM1wp2D69QFtiXg8uAq4GrhdsA1wJ2BS7IjPpwTbjncDrjDcGfgkrrCpgVcMdxKuN1dW2xKtPxafi2/ll/Lr+XX8mv5tfxafi2//67fD8f/X142l+j/m8f/Lzikewgu6A1iK1iZSDVfPU2RwmGNFEZBpcUFVcUsQDz6tRoe/X3MVX8lc+9OhJsr9vQPwZqdm3v3soH5Y2fm5Y+eNgk01YWkhHt/XLr7HBj8cn8cx0u3OifG4R3lmb695Me5Hnk+THI4yLPPB0hmiOd8GPm7Ux7hCZRHZanm3OoLFD6A/FOlfArJZyRCEPeEg4V0ps0OnzjjfwbYHWVxL53ZGQruMM9+z9WZ7nMy7MfapP9z5+qZ3nTal0hlRNdmmpwzd8pzLlJ3ee4P+uE69ONrdmAGx4cOXpyRbZmHvhfvc0yBKxZ7HYda1SW1HSqXVca65Hi9LOuSwy3rzuGRMa2rXIRnUXh7ritVPk5T9v65pNX9k6t0ZZ1tUtY5FmWdqytrbbnWMQ/8A7z3YDlcqeDBNpTrtLFTA+gj7niZVuXK4XbZ/ivIv8i8nLnNLyaZPC53NY10yTd1lPzhlGe52K+Lc7zXcfzJkK+i8PlcD2r8VMs+0xt9JgntLRJlc5/oMyEDo6MiImMiw0EIlRE9HqeaRwoqihD1TC3X5aYMhfQ4nkQfEBZVl5ZUVZPMxdTe76V8Lzec2xYVsY3CEiUfwZvkv4DDVR3bcbjUmfr3oHCM87jXO9JxrzHlgkTKwL307+rjqA9cR30E0Md3MAH8PLg2cLPhygQfcrZJWwygj7vj9bdqizLcuo9LGWPb4vY7mMJHcdtS5XtYtoNc4ACSGWvaDkZle7eDIvi17aCU/NEczn5uBxsjxJlRtR1cYtoOdO2V2oH9Bxh/tO0=
*/