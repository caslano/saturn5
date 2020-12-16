#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
KxG/gt+Fm/nRUfwKvgA386Oj+BX8DuNP4S3xK/htrcT86D8x/rzV/1+f/Wv5OxU/Be/SLvKP9uMY4fgGPsz43iSOhfV7fIjxK/F2tdxMwwca34S3jF++7llfEJfrC3o8j6v6VwGX/Z+e9GW8o/Cq5/ixNzzjJ7gcP/F4Fu+qro/Hi7iMv8fV/N/VuJr/G6ynf0303w3C/x00nv+bwr8OGs//HYJ/GTSe/zsU/1ztL/9PT/284qmf43L+NS7bd/hM1T7HLxXrYx+BX+C4rb9VcDn+hMvnd4Pn+cXl84vL/j9cji95PI9fIZ6v5/BhYn75OvwwMb/8BXyomF/+Ip4S8YXZt2r1V5O/3cL849zf4H7He+8b1R9ux7PGx+Mt67fhaeOP4OFfqbf1/c3gcn1NXPa/4rL/FZf79+GyfuI5ftnjFY9X8WnO/C37fd+CTzTzqzr0jb7v3+JnOW7b19/hZzhu29f/xse7bufPv0t8r+i/eBUfKPov3scTjtvxocR78WAbtf4R3s5xu77o3ri7vr1t3wzAP3fctm+m478S69Nn3yd+2W1/2/4bfA/HbfzGDXh7x+388Jvwtsa7DYjy9wj+VuA6ecZb2jcfePoPP/TUbz2ewOX3xZM+hS8W86djGyk/xPc9jh8rvu85T/rZnvRVfJxIvxkfK9JnN/F+ifRT8PHq/J70mz3psx8xPq/WD8LPE/5n/ERx/PTHfP/U+Dgu55fh3YUX8X6tws9a5N1rvgrfEe9e83D9u3jYP4p3Nr4U37b2NK7BtzX+GR6O//4Ob2N8VE/n/d+sx4cK+L6q/Ym3Ex58qj2GH13LW73xnyy+KGi8/t4UfKHjdvxnKn6b47b/6jL8ejF/ehb+MzF/OvUZ91/N38G3VvGBuLo+eXxaIOI/8Ylm/+dDm6OjJT+PB78W/ZfN+FMi/j6FLxPx9/Px40X8feILs3+V/f7h+4vxyyx+o9g/agr+c7G+5VT8OtH/mvyS/nuxvsEgfH3A9Q3dXN/MV8Sfi983Hh8gfl8RP0ikX4EPEumDr5l/ItI34UmRPoWr8w/B1fnznvTzPOkreEqk34AfLNInv6H8U/G/+LYqfgI/yh2/tvun42Oc49v1XR7FT1L5+1c86C1+XzPeS60fiXdQ7TuP5/Dj1fqXeFrFV+EfB43339uMb3Lc9s9/in/ouK2/dt/C/E7jc5qjt7EH/rTxt/CW9dW/pf9S/L7e+FLx+87BR4vyoYrL+ud3nvqnxxO4rH960qc86dOe9BmPZz3Hz3k8j8v2q8eLHi/hg939D+3+5HirNjZ+xVmf7d+MP7RuHL8Sa91Zxkck8bR6v/FjxftdwGfW6V9J1P4fj+Gj8bTjj+8TzW8t4ccZ/xIPc5tr2znorK4/Pl58/x7ATxTr+yS26iz7j5IeT+FLxPzQIfhiMT9oKH67aB/PwMcZX75X9Gtn4mONd9jbGZ/cujPrszfev30nfLZzfez6UN3xWcbd9aF64DMdt+tDlXE5vo7L8fV2ndlfrvH1jeOzXbf7f+FX4I2u7wH4YLxR/8PF+Hei/yHYpnOwv5g/m8ZPEP0zI/GRYn21Ei7j1/FTxfjuBvxkMb77Jn6SGN99Cz9BjO++jY9U+4+37yy/3yP/y955xrZSBHHcofdiej96DxcnTkITvffeAsGxHWJiO8bnPHiAICB6770XUQUBBKJXiQ4KCBBNgOi9S/TyT3Ln3cwzs7fF8IUIkpf8vDN7W2dnZ/fAd2bs95PAF5c49U89Cr4/F58Ivh8j/50G8kdaxW8bz8O3zwPB2fW1gl8FzsafK/h74Oz+Kji7vzovn34BcHb+V3Af/GjmfGcbeJY539kJvj9zvnM=
*/