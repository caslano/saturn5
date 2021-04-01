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
Igndgrqc9ttYdQKbI8qSmFIvWLZgHq4Gmm2TrQs9Cz2+WLfchOv32Zjk++EKYMy4RioPuZODfdGwtRJhzQ0Z73uPvIxrYsBODU9i/lXblqQCyJwt9euSAPxQvktSfSU0oDPpiBhW4qayBf54aYi52vciEiuT5XkGSifm95NB+WsCw4xoT2FR1x5UkPCMjRABtruScYOSrDI/eaPuDQAQimUUFDeT9Je9A0G9zeFqLxtg84KEyM6ZI/6RO2iMsiwL1S3slvxK1zHtg3XvqLSJN7T2r7vKDk5zWa7hn9XXwY5VB7Cr+Or9GqjaFTh8jE0r0CLTd7Ah+m40s/HzHOqTDxV5yJ1IX3+bZ2b1XvTjLXBJdHYS2NDvJg4z2mhdJOCAabubv0tuiRlQEfPMI/titXsSRT7acrFCwn8Z08TGVAItLYiDGnR8IS7VJNf+WnvyE+ThAgVF/Ntq22fLrM2kfr0CX+zY3oqhzZewfQ/f0grocwePSSQNWfzU7NHcnh07eqZJAV/7MboQbDA8/WApuKaQo5NvKgqfR+r9c+i/Ous3kI9vOfiY4X6JgA==
*/