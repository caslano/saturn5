//
// detail/win_iocp_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_iocp_thread_info : public thread_info_base
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

/* win_iocp_thread_info.hpp
MxobiXoMldogsh/nxF+YrShCbflb8euZktx03ZXvL1LVLzJobFbaWII5FLOSnj7vkWQadbMf/oi1WW2OnHkQtjfshXbd1rxA4DOdFoq7G7DOkJ9rfHqku6Yzx3p3YzUe9lvd32FJxTIUIoOFN8uTe2b4aoz3y1KiGd3xa27m8dLChz4V81wjkqqhb57OP9oqqdfbOe6M3EPylAOUMwNitUFUGZUcipFT0/H7uiL54Um52jNiID3OdNIsITqMTbZeh4H5xzUqFJeVR8QUvCxvNP+7HhvlEv38DsB6T1VvPiZkssVHbM+AcuNFaakLjlX+rorJytMBjSzdaNG3cS399yEZzVAPL2OWQNpuoktWOWL0inb0XNcvq+GtyOwaCc1/QepLiLUv1Y9Y0RpzML3mA4KtB1IwPDEaDzNkvPqD9XQ6a+6fv7TUh4k9ZY8UdPOZxalbTF//yzt2VcvCBRdsb5GiuzziE0RDTxsoEDueP84R9Xb6uM+AzqmU7upqKQL8beDXfyeaA/W87zA4LyucZc2yqadZ9AkxS6yGzJG7R5JOKqdd6L1h8ZmvY4a5O2epUJDVd8k+oGRTKs2xfhJWzfl9A/5+94TJnQWD3eblW1b905BnIBIBlY5hb1hiz5pMWRGZBiajr+6STmS3cgVPps4BnRYJCAY0SPB+aD3NWPSTktOMEfXavK7YwtyYZzcVYPkS5b7/SonfLJvj
*/