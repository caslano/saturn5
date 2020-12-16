//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
// container/detail
#include <boost/container/detail/transform_iterator.hpp>

namespace boost {
namespace interprocess {

using boost::container::make_transform_iterator;
using boost::container::transform_iterator;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
NekHDSSMMdf6XuQRNd4vRhxnQDzeP16rudxnM2oe738gnnZ6vJd0pMwNjvfX17iGr/inB/mX1amWvyPc6lapH3Defwye3VZLHeH31D7uh46wETuj5qJvLazV+R1q7ZzbERekXbbn8LqRTbYXWHK9nHhYhiWwXBdZL7IqRLaXB92D6+1ik1mjxwFyO+JyhttR2xlu1X9f8dAM+9luH82wr2d1yLaf7bYi236225fy3KzS2QwpNHpRubB0AN2l9q7n6PFnPl9C5bSryLxgH/Fe6L5HPcdxh1Lu/Nx85ziied3ur3KOJa78WSWzirnMnOOF5ref9a/XrD4j/1FGV9FHkjE25xdKX2jvOHff9dzgM3j+qRbn2Af797f07siw5/RVnh/L5ctrUc47uaQ9i7suL5t+GjePX5gvdpG5oFdQiNNzqU3wqkBpaXluSSYdpgRvx1pR0C6eS2FmGg3x71T3NVCJ1xTbvIpjgfVN7Rry64ZV7TrONqPD0vvbUOoLlUalbXTk3w66VR1rT/PaXBkP4Boyz7X2zi0h/3Sjj3y736VI7Z3BNx1Klp+nz+c4oeUm8awP8phJ0RHeaLMjLN+udm/h3wP+s2R3TzEq2705HJ8lZ8TWfNYYtQu7HdmSbyhTuC2w76Ep4cBeicQD6tgQaQyp41JcfZgNyCvAt7hhrDGeyA1/jTGUdxfVOa3bOPu55q1Rf6+NvX0XlQm9036GspRLO2n7bUF/VQmZSeUScvmhXvdnXU63uQjibWZcgH9FLtBNlB6QN7bmM12onmQP98pS9ugh6eksd0+lhqaHV4XlG4IyPh8X+cgoRdyIJcqMah2VDul1XqRLeqrOxxB6x8Ww0pk2GeeXcIHYmm2QoWWbXM4eI0AN5YyZCHVeAOcF42JOZlnRDGueEyB9m57d17RnVp7D4tq1EHv//eTfydn+JKyep0pYGpn13rA7iCfd2SZ1+FD5oc8tJb/urrrpLvKLsnTTbfTcFGmKsn1b6+zv7uf+qDKK5zKS9i66CpeFjAMyNug82uag+6Ve/IbGz5Q9guuldG7mxK4pPTNH9R85MLOwvIDK+1Oqm9K5VdSNhLXLyqr7b7ItTyrueIrbPi7tmO9M5xfqhbOc6ZyflV8OmRVWWo1Z4Z8lL7xaXv/CfDnPfK90ptBVzrz+EeFjbHnlpQktQ6vOY0yldJ+sRboRt6Tb3m72uqRxZzxC29OIq0zQbPLzDWvNOIx3h5ZFzgLne/YoG4n9PWiaXN9PVV/fCPfL2+ZTug5taRyy0JnGx8Cbak9jcXnp7LDqK1W3SdGJSFFztknNq9fta5EfXbfkpvUFep+9vlMWOfP4PBKRYc+jdL3w6iKjFn0v49/oe0/Vou/NXswxJJk85jbBP2+rb/U4n1dhSzHGqcys0mzKo5yfdRXN1oLfy+YSb4JZB//OAT0Oqm9Wof9aZaD3ypSEnMv4KfnfbnQB92oQl5Xscc1MsWxIq4nvK6MftLqbQEdBmrd0UaiNbSPxfmhcipxfA3oXRHosuKZfLXOe1JrP1Vf8a68O71uIpsK/D/yy1vIx2VIoyH/uO/LgftR7KY8PY1bVHytDo8LWoem8JapPnjuvo3iw90Xm0q1nB5+53ZxU3/ggkWfrIE5z0Kjsxp9OPNk+sjjpyJKup59F2zOU+4m00UnlbVaveiax9+rIIz//FbYRn3Jv/NziVWdaTHz6hgXDHl2x+5EDhtGonnK/+9ENz73xyrzTVzfYFXdxxA8jkb7zlPvy+3/79mcvpaQsfWncgrxb7juOfQ0Ryj0l5d7xn7/xY+LYQ1cnjf190n7sw/Eo93kXtk3e0Wjdo/9cuHPlazf+fSz2ZpvKffQ=
*/