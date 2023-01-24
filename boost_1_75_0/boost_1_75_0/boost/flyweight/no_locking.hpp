/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_LOCKING_HPP
#define BOOST_FLYWEIGHT_NO_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* null locking policy */

namespace boost{

namespace flyweights{

struct no_locking:locking_marker
{
  struct             mutex_type{};
  typedef mutex_type lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_locking.hpp
+Kcse0rzazPY8NRT+2uzgzGYdTY8CKrzKdrwXMKGB63qj0MBcYwbvfqnsr9s9pcrefvb2DWL/eWw3/m1Y2ySd4zE/krYXxlr7CeLhaGqspgMVYeUeG/3bAT5JBMgOqDNVk2AiquUmwAHZynWmzuiCfAyxVraEUyAh+ZtFibAQzVHZrZl45ubALcQ68gK2N9mlv9CAyk/fbKmk+HYlQFLWXN1K/wpIxClTLUC4jqqxyltTdWG/9bvQ3Z5MpI/aFGnoP7BqjuIDZQO37Rlq6denayGVUVKp2j6yeIfhQ6vm23WX63unQva5j+hd3gI7Luvdox0iDXWcxHuGs/qGA1Fp38wUPQ/4rN35uZTz+oq//yrCINdF1hcW79CgsvyocgQOObywArxrEI8C8A2TzhPj22uH+/HFaujg5XxibXLAIgHDgHiwULeyGRlB7Bj+VIqn20PsOOvetsDqtNKvEA4z6Z2GTjUShTr6XMFeIv/2zOA9eQbXOn/O/eUQk1ZAk2njnM95jQoaVsf0ytpsF2jWN8/lxPlYAlWWYkoCYjKIaJ2P4NEOZ9ForpxoiR/HidKUqwVgijJX3Qm3WSE7n3qPFI4bJrCYbMjOOFxcW4H0C4dBaMrCapCwKQT8KQKZrSPv2IDalClCmEBpnm+hprZG99wEGrAYckFd2RKka+L1NNGB1QNTvKLuJdKiYqXwpHU6zQrP5N3HXg94DQD
*/