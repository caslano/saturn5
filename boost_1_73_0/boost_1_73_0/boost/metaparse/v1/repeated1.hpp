#ifndef BOOST_METAPARSE_V1_REPEATED1_HPP
#define BOOST_METAPARSE_V1_REPEATED1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated1 :
        foldl1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated1.hpp
SlJg0zEH5QIAALgGAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI4N1VUBQABtkgkYNVV22rbQBB9X9A/DE5NElN5bTfQRiguwXWTkMQ2iRpaKC2KNLKE5V2hXd+gH9/ZlR07iftU+lAQuuzO5czZMyNfo9JRqLDL/Ewkkh4TXC1kGasuuwyCkb3BRT+oXnrDwaDfC1hRyuVKz4TAnM2xfJQKIZdjxXy+9fd5FfKAHcA9lmTnqixG5pdY5Cvaj0MdVml4u9mGTqsFw2uHfQo1ehDM8C20TmEg57TTbkH7xDs59cjm4jZwWBXQA1OAq+wHT8IJglqoKCc8DutJoVFoN1gVaAyXmqd6mjvsMwFfuSmGsQcrVHRtjW9QjHXqwanDHBZVi6asCitVEqQIxawsTMkyAZ1myoIA85QwtRhmJUI0K3PIxkKWqMAkw1KR//NEEIoYgjIUKiF6+iKScSbGkAkIKUoUoVLJLN/wDp3lEix7TeYTOIGRfkHgbTZO9QqSTCBFiRHj17W1O+8c9iqpB1E6ExPj4FDBT+Grc4pSjCb/Jtf/I4A1CT5fK9hKu5dnxq+SdmQ/yKRC1GWp1oW9ubZnyHez44twihWjIGkFrIFbddVaOBD0rUJ6N0YSz1WgCikU
*/