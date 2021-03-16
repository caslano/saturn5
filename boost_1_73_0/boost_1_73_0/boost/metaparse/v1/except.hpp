#ifndef BOOST_METAPARSE_V1_EXCEPT_HPP
#define BOOST_METAPARSE_V1_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result, class ErrorMsg>
      struct except
      {
        typedef except type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Result, S, Pos>,
            reject<ErrorMsg, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* except.hpp
2N9bBAe//Ijg8PRjP8HhycXwRcU5jPd0goO8SoLDOP6V4PA0Ok1w2LFeQ3CYjwcJDs+cniM46PldkvuW4BDHh7YX5xD/jic4+PlUgvNJ8ZNcE8FhPTcIziflOoKDvdxGcPDfhwhOl/IkwcEvdxMc4stegkP/vic42OngeHEO/ftngtOllBMc/C1IcOhfG8HBj64gONjzbQTnk/IYwUHeswSHcbxPcPDfAwSHJ6YjOopzyE/LCQ52P5vgMG8XERw=
*/