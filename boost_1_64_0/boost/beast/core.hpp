//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_HPP
#define BOOST_BEAST_CORE_HPP

#include <boost/beast/core/detail/config.hpp>

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffered_read_stream.hpp>
#include <boost/beast/core/buffers_adaptor.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/detect_ssl.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/beast/core/file_posix.hpp>
#include <boost/beast/core/file_stdio.hpp>
#include <boost/beast/core/file_win32.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/flat_stream.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/core/ostream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/beast/core/saved_handler.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/beast/core/static_buffer.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/string_param.hpp>
#include <boost/beast/core/tcp_stream.hpp>

#endif

/* core.hpp
pif0TcCH9T3AwX4LUEL7FhJWEzYTdhH2Eay96VYRYQahhrCOsIXwBOEAIevF5PcCySN5JI/kkTySR/L49xz/Nv9/8O8Olf+/HxVZ5n1riT6TLNB3rfbJJ3nYuf+Lbe9bp520YM502UdQvgKgJkIb5pqyd7XwJPVdl8rltO1xp37o9F2rphdIemqG4fub9+4m3chXrqxtNO/cTbp3H3S3zyDyGJ9BS1zvv1t0H+UpCXA8aJf4IMyNeWctbTEcD+rvfBcg5xaafFLnsP2VDbdrovLui1T3gwk/5rrZV4fo3la9Fax3ZAx/8EzxKVe92vCyTXofl16X11dqek1butHVM0WevQfDfFh5dGXrlusTl+tzzr3PKdf0vO/vmua3v2corzRQB1UMksZqUUOwHlQuJ7Cd2J+mF5h2Phe/ndPC2xnephnp/ja9gOySwDbxRYWMKWG6BrUJubhjStN1zGSYMaNjyp/u3nfydE136+SFg9YJ9XP3fUbsmJgt57z7ryr/IyPYHprCdBdnTDS1YwtNnnbvPQib99rCLG3PiC7+9ryC7OZ47Vlcceni+XNmhNn45nbsgXTlxZp2L21ojNY3mPFOHk/bf3bQbZc6ePY11ut6dHJCV79OfkWZu9rTyWnT5obpZJdLJ/2Ff8jN0sx/pCegk10enbx8EOOAOhCnDu3oZK7Dpe4WbCf72tOJPaxqK5cuD9aLyucE3U+xFdIT0Ms+j15eOQi9uO6P8fRi5tIDAXr5OmVa18TTS2X9qrrGIH2oXI5py75OtMU9Xy3P9NfvNfIVmvqZDbDdiyep29qR7rqpTPi4Jj3u2on0uGsn0ttfOxVec/Brp7UjD9/a6ThH7/rtQbHqvZDwOnovDdS73CSCdK75c8LWTZqeH7pu0vRE101ue0JPHV83OXZ3Qg+/3b1B+6O+9rsXTYE6QCbufZL0zq+ZPG0MbU9jT3973qI96/3tcS+YAtuzPv44Ij3ueon0uOsl0ju/Xlo78tCsl5xxUNor2A6aA/UWPg6a49sA6R1aKyXQZv+6uSzb35b9tKUlrC1moRTcppb4dkB6+/e+lms6tE5KoN3tr5McfSzJ8evjHfSxP64+WCQF6wO5+Guk/QnoY/81nV8jrR3ZuTXSLGeOyA22j+z1fn34F0iBOkE27vqI9PZ1kr2+8+ujtSMPbn2U19uvk3fRSUmoTnRxFGwjyHV+faRtianf+jx//f5E/cpc9aNyZ85cUB67QNL6TfKs35CLN6ZJj7tGIj3uGon09tdIZesPfo006TA+XzrO0X0f/xrpz1w3Gqx7W/VBOid/3DUS6XHXSKR3fo00qRPPlj7izJ/5ftv7gPI2+9vvXiQF6QCZuPdH0ju/RpqU4HOlTX397fkrsrv87fE8VQpu0674Y4n0uOsk0uOuk0jv/Dpp0iF6ruSMhZp+wbawL1h3oWNhX3w7IL1D66S57bfZbwer+/vaIt9QWBvC2mIWSkFtQi6uHZDe/j3Q2tChdVIC7U58nbSuwK+Pf1JmYXx9sFAK1Ady8ddJhQnoo3BD59dJkzr5LGmWM08MCLaP0rj6MAulIJ0gG3+dVJqATko3dH6dNOkgnyOdMNCvE2sc94hQnZiFUpA+kOv8OknbElO/7Uf465dC/Zpc9VswZ/7Jp8z0vYiT+m3wrOOa4o9p0uOuk0iPu04ivf11UtOGg18nbTiMz5KcdcLOQf51Uhq63xyqe7k9BOkdmbhrJdLjrpVI7/xaaUMnnieZdfpgv/1loIMWnw68L+IC9YBc3Psk6Z1fL21I8HnCU4X+NnWlTft9bfK9iAts0/74Y4r0uOsl0uOul0jv/HppwyF6ruSMiU1HBttD9rU=
*/