#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
0zihjmRejGvZiGXQYnw1IEYsNY1wMtSAKTmGUtWN5Hqw3Lo2orkU4tchDhGb1AYOiaJnFdxyECzron38qUBBUeGUEiXgnwtr2WLAvTqLwlcAIKUMRiXGpe7SNtzIVusknXX6ooC/pXDKAfF99nwDuD0N+e9uc+K/F2pfUqO+vxsYNDpJHmUCOdtw/3A8AXUjwb9DkQbBqNJiO8odGb7gJ4htBdFrLS59VBx4uWxUjEYdDxFOeT086g0xTdFYUzM1BvKo/wSo371sZFMo/GmOR70JKgOxHvCYbweOMJ5EVxdf+J3I6OlR/KnsKph7/ZGD9aYeunMB1vikretbFIpmg8t7D+n0h31g3ae8E0YZx/DmOxP0rY15CJzG877BLolSlusuiexAJ7S7TKOFt7GROs84ib83s9+lbBBGM/4Z9UERHyFYu1kwQb086u0xRrgmI0rYJ5ls48MYAfduklIz2pFS+aK+gylfn2vZXkLP8jaY9wtRE4YJb1FdFpjqZrRgdcejmG3xKHoYp2hGYatqLXMpOoCZwuSr1Dw9KbmhGhrc0yOKXhDMHXukie1/vkpcs31sXIOBGxAM+FeUAKc0gHfAtA7YymdCGNyVAYVQ/Ldbqsx8Sg+Zq8wMTP8fqswsxEm/oKPKMZXiZKXpZLU4WW06qfGN/Os7jY38jV3EL5aRjJvFa8z89hNx1n//xE3Ine8UWQFr9oEAjH/m
*/