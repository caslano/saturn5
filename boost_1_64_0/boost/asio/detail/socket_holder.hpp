//
// detail/socket_holder.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP
#define BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Implement the resource acquisition is initialisation idiom for sockets.
class socket_holder
  : private noncopyable
{
public:
  // Construct as an uninitialised socket.
  socket_holder()
    : socket_(invalid_socket)
  {
  }

  // Construct to take ownership of the specified socket.
  explicit socket_holder(socket_type s)
    : socket_(s)
  {
  }

  // Destructor.
  ~socket_holder()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
    }
  }

  // Get the underlying socket.
  socket_type get() const
  {
    return socket_;
  }

  // Reset to an uninitialised socket.
  void reset()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
      socket_ = invalid_socket;
    }
  }

  // Reset to take ownership of the specified socket.
  void reset(socket_type s)
  {
    reset();
    socket_ = s;
  }

  // Release ownership of the socket.
  socket_type release()
  {
    socket_type tmp = socket_;
    socket_ = invalid_socket;
    return tmp;
  }

private:
  // The underlying socket.
  socket_type socket_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP

/* socket_holder.hpp
CL+zLkPyQ5B/0d5TnJOeWD89kbWDEfvII+5lpPRdieyAXjWfyxTay/xZ1FkvOrde70Nk/ul8GJ3fEMqfyL3B2cmByD20Kr/VQe3XjDjqxz115IjPHNnh498Lgxk39fUvfJbCc4Nj9upi58jPUsA937MUNqTEhi/BnAfsH77wWQp6hyLDKHvaTzy+ke9+YmSOfD9xms9ZCvgT98yRpXVi4/cMabHHN352J3i8uMlOc72XMfvAMT/yfeBpPuco4IfveQPTU2Pj9OJgI+QbJ50PEa9cyV788yEwP/LzIZ4bXPP5EKG8+jw14Hs+T1bC4Z/Pk5Vw5O+Ke1ZK9LtcN+B71ktOwuGf9ZJTQ5rnfIU0r81ZL8eH3v/6jgudqcsbiYnmO/ul/c5e0LfkML6z1k7LiLPUT7DvUWFVKG5jo+Tsc/ebWkaq6XvqyrHvTPvpqqy+ScIAWmyzgol6T/Vtm02+aH/pQiuXltCb/6cHgzHfUX03Wbhr5K5l7Hyk9rBxl5C1e2PwGGbKXghsivmGG+8esjLbg2nBJpHfcO1LS7Du7mWN2FWeM3j5HhE7717DT607K4L3BXrqWcj/18iL+7x2y4psNRC++2ASfiDNvofr7blry8ycqrXbIEFnIvFnPXTvUvzImq8MbpZ/01z/3qEsb/ZvK6jdMsb6dxKnHwzXs5DdN1nfeIfdv76T92N4OnMYZv96alPPN1P71yWzIN3Zq5OeODE9+VhunNp2iLumZGc1dj42dupXXx7TvpDMFmR223O+lzQKf1siZfYis8O0V9IW9w7X0wof+pSAcxbds6jNqOlSr2XU5m6n5EbfCbh33GqfX2Qbxnvu5wm2zufd0LNqt+1i3wNrf5m7b9stA3bfX3ObH5SMno5+mPQDu4T3Ae5LiLcv6/D3B35d+9m+6X2Gh7vPzX9fYvz9h/770+LtZ/v69iU+bPcfPnTyoMuu/mnLjU+ePOyBl/76GGXkKpv+DXakL5vd4U8nf/RQ//uazT1tTvx9g/77LePvJ/Tfbxl/n6H/fsj4+wn991vG22cYfz/hJ5pPDWgf4GiofYD67fRrDto1X7SXPL93hH9Td4V/7/b8duaq1YdX/3dbxFw1z7xz2pJL9ZFr7Z3rr4V76wLqW6ofvC1qTvBk7fU6FbaWvp30OXC49sqMgKdLnyv9VDgSnqHnM+EoWKTn34HjYLXcWwXHaw3KBGjCdhr8FRzjxkv9KbWVDkbGi/QMy62ppdyWWsrtqaVcIKF2cllhOcpR/LUdObWQC4TaNGpnbYua487TWr+CgNbIwaGwEJ6qNUMT4Wx4OTwXXgPnwNVaa7gGztWaoDK4VfrnYCV8R2sJM007CWbBRdq7uBj2hkvgoKDjzzi4FFYEHf8vghXwu/A78Gp4KdwIL4P3wwvgLnghNB/0K2AWXAb3J9VuzngKE+9VqFV31zxvbOeMNV+8Cfm8Hv+e+eL/hbniceVHPl98uHPFfnPEu+6Onieu/Ryx5ocPNTeseeGvPiccPR988O4jmxOONx+cfg/2jBswal5Yc8KHPx88/B6/OeHazwd/03PBX+c8cE1zwJHzv4c395tHOi5ArUJtQu1CBe4lzKhxqArUStRG1K57j86ZHv07+nf07+jf0b//zr9vbf6/ckFZcZVZAPDV5v/N3P6gTNNpMvPYk/PGj5hy2vD8yuLvOFP/gVYy3x82l6kz7/8o/f6+mu+u9pn3v5bxvIyP7fi4HA/P+a9sFjnnj9zhzPmP8c75G7c05++GZ3/Qf85/z4fe8BzefP+WUyPm+yP8m+Iz3//cEPq7EfE/rLl+/I66j1BzkJ9iuY34En5UePzILygqyi8pCk1q2TH9nUM=
*/