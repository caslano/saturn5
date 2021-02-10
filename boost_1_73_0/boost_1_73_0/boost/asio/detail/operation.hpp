//
// detail/operation.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OPERATION_HPP
#define BOOST_ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_operation.hpp>
#else
# include <boost/asio/detail/scheduler_operation.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef scheduler_operation operation;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_OPERATION_HPP

/* operation.hpp
353KBIAA4UwC84OdZycsq9xh02vVlYnGZkYBfVX04CapOsU5UvcpunUjo4hE6gS/IbhnkTGObJgrsUJyl+zl33ThjLJSt3Wmy21jbdW5qxHl6vPxMXqPBB8AJohyReDBoLuzv73TPzyyfO7IlXWLvl/W7b8VR06Or44DHHEl5aLvl5T7b5/m67Pzs5s/B5P1Re2ipxe1W8+sZ406TR9cM5xN0mR2y+iq7HaYF+ltjcy1wuRq4FUOI5aauIJSd0F6lMbCOtcgaC0F1Up9xEVKM94C5dVMwYhCRyyH/rrgg6R7hBeA8n1ptoJhPaeMgPthzQTaWrGuYEHKkFfOFh3sc0qmVo0uWolPLeeVEPvPmrb7xCKB0dcbaf5d65NySrUm5WakNd4bx2IHSBWjv7goofe5KsgcaSXj5ImK6F4f/P1JZQyfVlSCIVVW8DD6esHD6EEovmvh7EhUVUGx0JXWvKBh0IW4u40O48Da4J962yJjsPlv6a78RolFFfX8AyekOf5cWaWjtnDUeKL510mzLtBFbKnDrVRtXD9/WNUaipNesHlfO/h2lcew9ADVQk0dXW9pthGWbFLTrS4f5nPXbGl6uBOAGcPsPGqKAR2NSGZwVrc7bmZdVUW70gfQLfJFJ6MnFJ18+u77KTJt
*/