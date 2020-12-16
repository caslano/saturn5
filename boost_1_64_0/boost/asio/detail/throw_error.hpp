//
// detail/throw_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_ERROR_HPP
#define BOOST_ASIO_DETAIL_THROW_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err);

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err,
    const char* location);

inline void throw_error(const boost::system::error_code& err)
{
  if (err)
    do_throw_error(err);
}

inline void throw_error(const boost::system::error_code& err,
    const char* location)
{
  if (err)
    do_throw_error(err, location);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/throw_error.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_THROW_ERROR_HPP

/* throw_error.hpp
0gf067HPwh9W6awZ/VX1wb0grdNp0wUUfXUPn1eSn6H1lAZbxlenQ2dKrmPWNNd1aO5erGqXrGm6+BDKBak3oBcTX+f8G9Y59xiozt+8/dyDvl6ckVDx6+ixI9s8fUR8nVPWOT3WM5vv30fWo+Se4v52WY/aSn7fdQMzwK3BTpKul5jry+T7fkQ03+Lx7/AN8h2+IWOvx7/F/9pv8XjM9fXzPb4w/r0cP+JH/Igf8WMDHhvw9/+0SrUA0MLf/4G4/nX9VYzWvOHD88eP943IHz983KiiYvSSApH9e8PXwI+BjB003wQUK8eNKp7kG1W4x1ifFJtePfUwePWawjb9LBP3dnGCM8br7/wWLzpbryk4KxWNW6W3uDZUd54yzYp7O8we93at6MrbY/J2beUe93btqV5tU9YB0ce+XdPfEfvW1F3bytkvvdSmnFe/aM1pq9nxb4dJfTmJzvoGKR8FUp/boMpQ6LH4rk/oWNS3YCy4lmMsbkh0HwvrNO/20alRj0XODo6xMH3TNcnZN2oOr2mib/RwRD8ew8LjEa9Kco9HnFEbfTxieJuMR5xZ29J4xP7+aWzt7J8hSmfV39Yy1gWd81XmzeCh9nkjZSTWTrU/fswMYz8Slp9pkW+TqVzy7fOuMgobjcC8oy163hk9xw4qTf3BNUFQnaPOsPtndbKzD3blelXBPnCdJ5b0wy5h/VAVoR+qIvRDVQv6YZcY+iEwF5ZtJD74pB+6QLtzvTrao+PYlrrNBc/4QlJuY91H39ie96NNXoaR8dcoZJQ1YBO7x66n/o3LO2BOinNc85CnMSBPmZs87u+nRtuYzdVjWjm72jamjWFjdnoU8oS9v8yYcX3SXD9snha0ccozHHmsc4w87vPU/TlPuSZlIj92mairaZnkWbmircTKEx3IejAfmTJOE5mO8JJJfJd4xOugvInZOoH0MNISryPQD+pLS2QN8O9i7EpH6/QFwXgd4hdA9jCEf6Cx+87X6asSbH4SuMGCfmp+0/nJpPXc4iibOmtK0B6zWudfaGJw1pzuj625q5Voj5uhzLeNTehiXeYpypCmTIlOn5YwgnPhdqEz4N/7tNAYJNSKUEFb1kKdf4m29X5Q2xbyHaprtOzxQyRm3wxygu1P0+0tk/ZLW9Cy64Q2la0+igRtXI/VPJtIOiBzV0vF5yhirl+aRuu3UfE5BhKdkJjryYSUtDxiP0qZBspUZOqYGhcbm6wwnvfhqd9U24JPD7cFD9RdkC6x52qWp3Uj+FxqGn+SNna+r2X+rNKydAt/Xxub32d0/hB0tdqE1FMv9aS3qrlIh2FMbacq2sarnvrTvL8LMsHrdf5QXUcXqeONdIlZknxEeus26YnwOe1whTepLXslqs/TitITOzj5tiWdQnpxL/aoxLfRbPKOECq1xQ6ptVyP4bBx3SEdavR7KEHbvzP2xv5d2cI1yl5feMyQ1ebZou9ffW6NiRnCdLbZDDKHOSdzOMxmcGi7MDsO+S7MOUfsOMJfDS20YzI2oy71XkG9RV71htkyXdbPYUNC2dhtmbie2IiE9s+q9s527qm+iZpop92oUp6zjrZS3thU/pHlalMJT+w2ldTpsKmkHk+bymUZTjl70Ce1nnKK3Za3jFI2S571Drst8mO326I+h03PWg+byvkdnLJdqWwSvGUTeyXPuUbZJu2VyI/dXumyfpHtlUzMOBfZjmWjs/EcZ8zDlty3Q6S+hZnuMSDXqvqaGQNybQvuV67nantY3dHZvh/hzTjX2b7w+7SLSzxCypn7NMP9PoUn9vuUOh33aYbzPjX9P7KTe4zLnHObH+OSMk3NYfJjn8PRxLg09txi88yWo7Wx4Eg=
*/