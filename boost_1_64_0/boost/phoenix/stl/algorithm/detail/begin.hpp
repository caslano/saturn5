// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  begin_(R& r)
  {
      return boost::begin(r);
  }
}
}}

#endif

/* begin.hpp
xH3rbldvfLyx8vXEGua+dF3ph2pII9PPrSV0auw0sP48b7bJgnc2CnHL0TtrGqpScce5qTj+OFgZKKzZyqr7bJlaGaByloLtuXQD62EKmTlfb5P0vbW62h8dlR3q/+d+s0ctuNF1PfgJMqLiDz4T4Ud16YuYLIcxD7CPf+jW5Gm0Lh3iKtbaHOOq5pEHVFo1+5DOt7TThDhWOVmjQWZzFfU+VYhy/teHS5EChB+xQgklPG5mXdZztvLguDjAyhQx4v8mvSomLgyv6jimBMpAwLn8dmJvLJEKWz4t/eaprXfGN2GK902y54Ji8jpOPY2FN7yRL/DQ8jNwUdhBTth/OkkKVwTHqnYjPn7MSawOmfx0EoL5YT4PsKLuJ8KMlcRhYnL+x2VSDFZblaKv4P7/Ce0IoH4dHA9onEKgtVGGATYoud/HnqFryVhwsOdl3rIPptkibbMxg+tc/XXk3Dus3I0FgW66ftv0Y61K+VmEikSidkM9kP/qkOiCC/TQKM++QrZzMsHU3VcXpRJR4e7fj2TMbhNYfMqBdjw7KRduJOe79kXxA3fbVxX9uA==
*/