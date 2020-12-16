//
// asio.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  See www.boost.org/libs/asio for documentation.
//

#ifndef BOOST_ASIO_HPP
#define BOOST_ASIO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/basic_deadline_timer.hpp>
#include <boost/asio/basic_io_object.hpp>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/basic_seq_packet_socket.hpp>
#include <boost/asio/basic_serial_port.hpp>
#include <boost/asio/basic_signal_set.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_socket_streambuf.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffered_read_stream.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>
#include <boost/asio/buffered_stream.hpp>
#include <boost/asio/buffered_write_stream_fwd.hpp>
#include <boost/asio/buffered_write_stream.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/compose.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/defer.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>
#include <boost/asio/generic/datagram_protocol.hpp>
#include <boost/asio/generic/raw_protocol.hpp>
#include <boost/asio/generic/seq_packet_protocol.hpp>
#include <boost/asio/generic/stream_protocol.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/io_context_strand.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/io_service_strand.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v4_iterator.hpp>
#include <boost/asio/ip/address_v4_range.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/address_v6_iterator.hpp>
#include <boost/asio/ip/address_v6_range.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <boost/asio/ip/network_v6.hpp>
#include <boost/asio/ip/bad_address_cast.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_entry.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/ip/multicast.hpp>
#include <boost/asio/ip/resolver_base.hpp>
#include <boost/asio/ip/resolver_query_base.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/unicast.hpp>
#include <boost/asio/ip/v6_only.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/is_read_buffered.hpp>
#include <boost/asio/is_write_buffered.hpp>
#include <boost/asio/local/basic_endpoint.hpp>
#include <boost/asio/local/connect_pair.hpp>
#include <boost/asio/local/datagram_protocol.hpp>
#include <boost/asio/local/stream_protocol.hpp>
#include <boost/asio/packaged_task.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/posix/basic_descriptor.hpp>
#include <boost/asio/posix/basic_stream_descriptor.hpp>
#include <boost/asio/posix/descriptor.hpp>
#include <boost/asio/posix/descriptor_base.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_at.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/system_context.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/time_traits.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/asio/uses_executor.hpp>
#include <boost/asio/version.hpp>
#include <boost/asio/wait_traits.hpp>
#include <boost/asio/windows/basic_object_handle.hpp>
#include <boost/asio/windows/basic_overlapped_handle.hpp>
#include <boost/asio/windows/basic_random_access_handle.hpp>
#include <boost/asio/windows/basic_stream_handle.hpp>
#include <boost/asio/windows/object_handle.hpp>
#include <boost/asio/windows/overlapped_handle.hpp>
#include <boost/asio/windows/overlapped_ptr.hpp>
#include <boost/asio/windows/random_access_handle.hpp>
#include <boost/asio/windows/stream_handle.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/write_at.hpp>

#endif // BOOST_ASIO_HPP

/* asio.hpp
+TTx1yTu29dI8EKO8zPXqGssHS7lDYgpFRHcRR60GCey62WD1ZOe0+Ou/EMXYVVBSq/Xb9IPyun+sCRV24WykhqXSn2o+y5T54G2aU6ZMu89ZV86an+E6P6VkEsLMltJMocn3pC/vQYLafQsaqzZoHjALsryaIuP3Awo+0L+ZzfYnx2CLLMk3xJXsvNn0P3Z7SC52BZEVV1K9YfCKvIH7Kd9B7T/YWA+NPsHH8k/KSPYb47uS/VolPq7sjop+54Qr5+oeMBEmAZqDRXXkEwU523RkJSoAnEDuYbilmr99WRME0R8a7Q78gkxbwIjaZJKassBQON3NO66CukdApBqw0XNr2Yw6Ar8zq/Q+dKCGtulYIQHky0yCPlWRMI5IJN2G7XTeS9w9wn9HVhZ8ZRaDFNLjfiCM6b0ty2pN2ry62V7+GkfZQxkhIZohDqYAS5rk+SVBjpK6uB7qZIXfADntA5mzzZnPuRArCoDxs1D9pZc1E27AkYMRD7vMOZtejmtv+qKh95C+ubqap5B9HynzNcLjxTvMZP/tDfSz9Qp2qSR/C+K3qR2ED8tb/MxNBm3kVRXcbk+DhD8WvKZSh+ygkHIEfnv18g+f04/VkmqUlpNt6QcD4+ihmG/I/v3BQ3N7SL/vZPije7SD7bawE/h7++b5K/TFd3nAWVDf0ofqiF/ncJiLSPgEq3A13Ad66nezH56f8r2GDMay20VT9FyLKLA4Xhf6S9i39GY1lb+0Hkvy2a+/M+h23S/6YCvWkX+4ptkY/vIf6pJmatOO2mwN+nkerKXGmXL08EZ3WBwI1m+8Az68aouJOvTLZHvGHQO5WG1X1rpo25wLm3hDL8upK7VIHVJsayDuhKePES03/PKPg9icBoNA9R9pHjyYsStssuR+ZVf/t4PrdMAsKvtacirFyTPdTDuqSP92QQJvg1Alsnav70fGdgfc+QP00ljYmMLPyMaXy+7tp454HUu+ZvqIWQhudpTZdIuvI8YkzpLvgRA1x6AtTqpe88HYVeDhkbVZcWe6K74YHNSv0nLKKi+taxA41+CdL4o/vZGDNJXwfn0FsAlnXVDrsgeHAB4dx4Q0Amm82rD1KUf1ZbcoIONk0jNHgFxqelwvrVf99E2iB01zunSpRpcBjFOQoaf0vsDR7gE9yJ7SHM+6q0T+0O+ke7dYTVVBvmu6/K3yyAqLstwd0Hpf4oeltim88/BgfF7Rda2u+KDO3S/xVNtswyOxBdU65Mu/5Ault80flGXaMNTdM8qAyosoyxVXT2/mtQImSNldNZ9MwEk6OrorS7ktQR74wegj4zvJbprP1dmrFbpmn2dX/6cF/RtYlfYH01Hlqbd7eBXFSEvBZMtaQSXhsOQ5fdlcP7DQrh01BG+c5s5/S0u+bxln9dl0WwtRjbsHKCf5Cu9nZTNdsVXrWi31yJqDAkg9UQmcvwtEDN0bjyVjT3BWPabTtv1m2E/+5v0K38kGCQhH93QepZG26WbGetFh7RTNALleQmXj6UgNk5D8O8lKSuqxk0EfGIVH0xX/FwkRxQ1+hIJYvcwOKcW1H2USY+uVbNAPm26RU3lnzSCS+801vPLpRo/EZ/YQOOvoshOLUW1VQ8d4KdzKKwN2d2jjBg/6axd3Ej1Ly/7yNqd9XIUcQP7kXIuAZc/yOROfA8ot0fvXyLknxxuK38sEszUCisukt0iOToXkvQz2r8lQDjFwXnTIMRNUI0V4ylrbgpIlOEeohjf3X7ST6/JXzyC1BFnUreyQDwKRshIb8DoHAjU/iU1tjvawe83uvCxgfwvMnRm7NN54AvTlYq62esiHVhE8VVHmtwaI/u8KqCQJ1x6arDPz9T+KIs=
*/