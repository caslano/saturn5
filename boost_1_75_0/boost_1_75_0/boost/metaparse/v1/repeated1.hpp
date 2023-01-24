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
C/y/iJMBnnr8OjT3ttce6AVUjKQhg3ph/+ugYT5v4+Hj2PUPJ4d+iOLvMSNYxG8tEmtUrBW+RgBjqfE7RhiOkvfgz1eOC61vySMUHrI+j45fzyQp4Y08Xv+V//54JurmBh10s3ZJ3a49yh95eia9aiF/dD4/Pj4TY3QeocMMOkyhw110uI0OGXRIp8P1/Pm/zjTZnMy4CmAp2Xmu2VLSsQq6/hBoSgCA57846O4uTSXzphlep4R09X6mFTySxA1Oz1tNJpjXH1uSw8WTp8Xe9Z/MJi9ndGg2SUcjCZhNhNFpgEfk337Bqdng/odbbGjtiQjm28wWlUGkZPbIlwLjew+hrPchPNv4dEqozY6G7vlzzEPXsbVuTotNWOsuRGsdH7qR2ZahC7PTJQk7HQzbmBn/7bDdN7rjYQMTU4QYsoEewZZ3iEgt7AG1vrIZBy1P2OT4ImPDNpiGbe+jhv0jl3RzFEEa77hGjpusf5xwZna5m+ijoXa5nvedoV3uovvJ2JN9RiN17c0djlQf7HVwVDegMQe42A2ymcL77zf6/yC3TYTY4sg+gfa4FdifqDviZUqSVz201V1vVP9Z+puNjG4f/GZDq0/AvT+9o4pfF/4GAg038jRzoxrTjmL7Tuf0slnmJDWHWCn6GDa1YT6yqQ1SsMom6qeDLEL/AuF/34MOAeGK6nLAppB3Bbz+A/iXBjCBvPIbFMiFD36A
*/