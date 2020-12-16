//
// posix/descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of basic_descriptor.
typedef basic_descriptor<> descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_HPP

/* descriptor.hpp
7iXsyfNAwnbgfxY8iXuRsD34U4p5bjP7urjYnvAEwo6Cxc3QguVgzlmkW0z6YBXYSthOcCX+PaDZMya8Df9hXGz/+GQzfjDcAj/ujbNI20ZoysFBc3BF0PN71hzSxB3i9wncBMK34M/jsosiXGzveeWV8f3nu/m9E5p9uPfjfxZsA/Pm8hssBg9Bcwx33A6/CnkJ244rugoe8ADuOO4N4msIy5xEPLiX8snkQrKH+D2WsDbQu59N2oQ/CU6YBw08sb3tYvxVOOce91b8I8EJW5AL2jpwO24WYXcTtwe3F/8q/C+CzeABwk7y+zg49mp0OR8ewqeCq3DNuBOk9RD4BM65Z34E/6u48AJo4X2WsLH8LsHZe+mN4N24/bgc/FuhGQlmlmN7FzdrCjzEHccl7rUfgLYNzDkfWfmddw35wE3AvxJcBCbuxW8hvI7wnbh9uIO4PMKPg849emsh+YB2F7/nI0cbvwcRdgycAWZei5y4cn634hbxezdYBzr39vcTto+wk1ORFzyC/zgY3koYv4tA597/IvzFYCOYswjdgLGzAI/xexZhR8C1YDOulfDM66Dj9z7cLvzz8Vch807cftwRnFWBPnGLcDW4XbjHcEdx6etPnw04/Xf67/Tf6b/Tf6f//lV//5L9/6ZIo54B6Pb+v23n/3leFI+yqJFskXakuaK5JVLWXL2lmSxI/GX2WvjtGr+horaupcm2/behwYreAxBynB9Ym6RrLLjBihXw77sxfn6gtESl5wPbSCMXCgSvHyvfSLN3/az4i2VNNkfOGzjTYE3W8EzW7+rcdphywJ9I/FiJH5sdtV2wqbre2B54WuLPlWccmSLxkWbNcMwuzGF9Rmz/JxkdpIzveF/Q3uO2bkq0n+Ndu58Bkj/CTP5c6/Qje/Cffr93BjgNrCaNItL26jlSu7G+opliM3kOOfK8OEQOha9fkupd05kftO+t8XPEvxL/FYbfrPM3N8jz5soe/nqJH52UDX2J4b/G2khNzYXn4FDhQc7qpjIxX6A2GQ3tTPFfiv9y8eckqWz8VdZU1Nab8xNXSXzPJGx9iB699WCu6Lxe6AqS/GzifO9mO66/+rHPI37alaG93NAek7iRVrbSZu6Q+qNnPmQvjr/Gs9fXNph6fDXPhjIpm/gX7EQ075bDXli9PjNW57aJ/x7188QderZG9ZCuabBuac7OXCA8s0IHrT6EzcM+jt7hqOWbK2EhCXuPhP0i9GELatJ8ckDcbofaTZJnjcmOykuD4FGEqXy/FP7ZoQe8Mkp6X9N88p+xrzJA5Pu7+mP0b5X9+3LqdE0q63JjxCZem8e2h9LsgmaUTdOr9enM5H6O72XddI9Bd1m+TbdtamZygYcu9swj0K2x6dK3jTDPdNOgENqe0NwwzmMvT2lGpukZg743FCSeMTgXfx8rumd8EmfjUvIwDHcZLo2+pAeuJ7+biZsAfigPOj2HYPczjf67ZvN4BHmbmVUi+7Uh6XPm7nD3OfuIox8gXvoBCXss7DqLImFtYbPHJu25gLADhNFeCXO3V/3OWNOQNmns/VCXCKMuJezJN+pGYw0uT+/e2mTvN97i14+JrEFjBTzuc2PniH8h651pif2esXVzrtCcx9rvAO3bYukMCRw/KiQ+0298MOfRFgvNuayhhsw9N33HRceI0eM6Hic844LRr7vcRJe671mue/GLdc9zPq7OHnujuqyORMRAol1ozAHk5JNplyFtl6pL5Rkg/V1KtP8ibq48/xu3xMfXbHlyRTO7y0Z/T0n8cDM2ZlN3z9A8j+3E+Q3kkbrltH2BDIQ1ur7HX9Vb72PjIYPBVrCS/IbfIfllh76sOXIK9SfKd64=
*/