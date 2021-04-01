/* Boost interval/policies.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_POLICIES_HPP
#define BOOST_NUMERIC_INTERVAL_POLICIES_HPP

#include <boost/numeric/interval/interval.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * policies class
 */

template<class Rounding, class Checking>
struct policies
{
  typedef Rounding rounding;
  typedef Checking checking;
};

/*
 * policies switching classes
 */

template<class OldInterval, class NewRounding>
class change_rounding
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::checking checking;
public:
  typedef interval<T, policies<NewRounding, checking> > type;
};

template<class OldInterval, class NewChecking>
class change_checking
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding rounding;
public:
  typedef interval<T, policies<rounding, NewChecking> > type;
};

/*
 * Protect / unprotect: control whether the rounding mode is set/reset
 * at each operation, rather than once and for all.
 */

template<class OldInterval>
class unprotect
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding r;
  typedef typename r::unprotected_rounding newRounding;
public:
  typedef typename change_rounding<OldInterval, newRounding>::type type;
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_POLICIES_HPP

/* policies.hpp
7Z7vXaEpRtCp8yw2dxs7yxUulX18opO7PC7Yym4SZPgON9J94VPfk6Ykg6fPoL9Cupd8KhdIb2P01tQAyXsmIM+npWLL9CXX/I/6+P6fteuCFUupDnNBHqhVv0WNp/It5KzXhS5jCXh1emUTbZHq1ZUuF8vVO5VpXkV6p0J67taosH7T6jA8voa8kU6542cmjcpxGOfPYW008oE8ZuaHPSi40JZdWPNwb+9kyhU91BivMIwUjq/yPcT8HEQ8h4/XfXBy2LKvl59XqRnLyIiwNrdw6iF0f25/E7PUgPA1zpLiTW8trSa0bt40sbAimJ35yvf04hB1YjgkUmgB1j5XT6p1hK6EEhElokPqX7381eU10YLlMNWC3FDi0jsCRPHhDtyQ/ms3oD2Q6kAnkNgELnnRtKlpIo4XxJCl/0qkGT+8bAhTrRHe0bnevcB9HTVuB87qG5hLqIIzRrhFKjeZOJVYhPOHmR4YfzUGuYeqxpuLdwbaZUv7vK3q4/5qxXKGrx0S+0bUNYFOantmBjS3r9z3ednRKL/lC4kv8USt8nPXbVycrgTguc+cEA==
*/