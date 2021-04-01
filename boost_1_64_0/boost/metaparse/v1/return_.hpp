#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
rH2tyQQthZh8BJHEvbZ2HB7VL8BxDi7yunUdFrvRJiB2XR0BpZE5c9oXnKTtBoX3xDoKlFbPmiALtiVKILUCUC+VNsBQRP2t+7hLebWqTddYfVqAY3poRjcHrWXxVWKIqoQ4WWG9GXlZ0h5j7T0JS01DEz2k6OGf3eNotPIjIKlATkITpUwkKoc/iFWOC7hxy3pH2bAvGH6c5+5o5Br32Lco8AhAV/rLtmrZuk5i1Rr6cahMqJqp93GWTWnydbVOmNg5jobLKTqBc4BIEGjd9W+xU/4HRmEQrhCEYWrqD96brpOZ+SuLgAlEUhtZi/OCQZjz+34ktHjrTZHhiPAxyVEPTZBv4O46GhEuzxiJD9azri6z7e66fwSHBBnkhUrvVUVXTJttEJZraZfltEkehA0Wtg3GXDaPpwEBXOMyahWAmwNY0HfRCYGe7X/NbvUOp+mU8Hzg1yE5nELA+9Kg3kX8vcuvQxQkuBWDocDHpzjjuZ5EdgNuHFPbjiT5gV1oStQcb1lK0N5yvj7i37za6HGPPxOMEFmFfdnUK1A4v7jC6hpI/HLAQNM4+A==
*/