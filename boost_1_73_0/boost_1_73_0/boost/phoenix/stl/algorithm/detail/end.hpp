// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  end_(R& r)
  {
      return boost::end(r);
  }
}
}}

#endif

/* end.hpp
UbqcWtAk189Jpd0TDTuubBB/qh17qe0+g0eJJ+2YIrx0Q6E+52umubV1divqR1eYX9wk1x4ZojfDtKWPqhvTKG4S57HQeQ6KPVvIngN2exbNXzLQC+dV6naNoa9Bw6Ynkb5ONmzwLfZ8LOFGOW8unEK4p/q4o0rbiW+Z/3K60d7hmh0dOJNonKXQELx48NcaAftOg+yDQl9n7o9wLrufh7RqIuop1pdW8pXOacC5KMhXkrkb5yq6LStyTMQ25Xg=
*/