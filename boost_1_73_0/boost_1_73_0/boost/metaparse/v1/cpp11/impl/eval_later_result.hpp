#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct eval_later_result :
          boost::mpl::eval_if<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* eval_later_result.hpp
iVqcRh5J9UIqxfPlfJnBZgH3pZFHUr3F80o+/Ntkot5NI4+k+iDlr4psvz+ikqiTaeSRVF+k/HXsG/YtP0xUj37kkVSauNZ5IzclEjWxH3kk1S/A26il761ms+yb+pFHUv0DvM43L/6ArWI92488khogqKZxNU8R9V0/8khqYIDXqNiDbUYT1bI/eSQ1SFzryRGTXyFqan/ySGowUt6iv3nt3E9bEHVjf/JIaoh4Xlv6TfqaqF39ySOpdKT8fvk=
*/