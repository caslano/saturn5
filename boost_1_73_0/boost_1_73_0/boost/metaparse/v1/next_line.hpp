#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
TpxyVzfamY1vOM4IsR2BHjWvwgdoMhi2wvueFbINMxsW4XqUGA/hXGEB3IA/eBaNmB0HFOXiaKPYtTXzi7L98aEtInyeEhFJw5wWOk+8igk3d37/5PptPK1toOl4te+Ub7enxXfgH4fEJTkl5TQRXTAnr5A3z2c9jfdaldjRvW2sbL1nqyjVQ2JcyAYo/ktKFB+9VMmYFkP9hcqyQltw+dDALhIXr2YQ5L8GcKt2hp9fiJPTszAy4Wo6Bm+F1T4=
*/