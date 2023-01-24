#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
fS9l4WnsTyn/miL5hf23WMxbvItX5TzkwiB2NzjRQXla9RybLdjp2caQRKPH9vvlXgCsouylgxjTOnE5uouX4IsjOCyvMEfciZYKiDdfbOTZ3EyYirgSgo/Fp2FKhXsxoA2nBQqqACKYMZFyRv4bY5lKAq/E/DccJnzM+sgU8yPi7rl3Ek92FL1opzao2xuD5EmSSvvxZ5AiRbDVPWhQmMLzYwTs3yo6u9yECLicJzo+S5dY33zL6cpiXpRlPjcHJ3MHO/R/h/bRCSpWTx72VcjOpqzyorhgIAUinqN2/OQxnUpREVLgQ2ypb76fljqaSj1pJVMWkMlXVQgssCd2lQyOjqJudrEfAlrgbX0FWqANRrCkYEEoWmD60WOIFtiI6w3RAiGPAOdsr82YszBVsecdKEx7caKXsoF28aduhdcP8y91FNPe/DxxMN8a7eTzaGsw4BQ/YvO4scpdzn2I5ZYt6L3bTT7E+s4zEwr1yLyIzjN7uzamouSFVLM5XT3lkZtQuU/d6vpkYBx5OOEtOewtdOuUzab7cEeiO266nURsAXs4ZVVHNgcJpDbFBKS2XJxbbpxbwxd5y212xQB14cEmIQBDppgTTKhj/OBvtRhWAsuW82eeOfFdPSn8u+qJM3zOf2/hxw38uI4fS76VYprvG3rED6e0wpGkJKj1ihVz2GyvTSU55Lx50l6bYpMoBPki3JqcNm86ae3f
*/