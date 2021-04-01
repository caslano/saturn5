#ifndef BOOST_METAPARSE_V1_EMPTY_HPP
#define BOOST_METAPARSE_V1_EMPTY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/end_of_input_expected.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/define_error.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result>
      struct empty
      {
        typedef empty type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<S>,
            accept<Result, S, Pos>,
            reject<error::end_of_input_expected, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* empty.hpp
N/uKsk1ofXEwRE1jf1xgy3IE//lE9p56Xr7PCU4tGeSvQC6TNMQb0lsxUutKMqTjNEVlFb0REfIfcPTrgGvOj6kidNIoyvpDlkl2VgCc5tFPfwOZ7Ci77ykbFzck9yAEVkQ8rbjzpKsRbpo1OtBics9qsnGY2GemGl4Z+9eXpgaBAFbgGL9Syw8wAhHBT83W+yWFHiFZ0TsdhphdUZyCvMm/+w4UngVZgFCw89EeC8Yb5DB1ygsCExoK0vdr/3XGJVcKDssofcN8zQIVc6zKMi4NWW00z+zKPPvkaOmwyL2cwp8q8pLvCayUsRJBlLJHFNLP3H822EhWIMsl6/vLaWr2OUcklOXqTiX22aA4eaf33t2K2Xpy4yNzYkTeR66bBxvaHO6pRnaJwMmZmp70ZNpCFDcJj3ZWR1PcMkJFMgM6GYOL8ipX9U5yYLYDwXY/D3ASP2UO0+hz9dmibhbWhJMQ8gnILYF22bqfHWUXUnkJyYfIoZ7/K5+MkbkbT357k7gsTr/mSqFOqKkav98LWrxECTCn7SNK9nlKSNkioXBGWu6PXaAdCkoVjQ==
*/