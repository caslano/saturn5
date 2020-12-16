// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_

#include <memory>

namespace boost { namespace asio {

class mutable_buffer;
class mutable_buffers_1;

class const_buffer;
class const_buffers_1;

template<typename Allocator>
class basic_streambuf;

typedef basic_streambuf<std::allocator<char>> streambuf;
class io_context;

class executor;


#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class signal_set_service;
template <typename SignalSetService>

class basic_signal_set;
typedef basic_signal_set<signal_set_service> signal_set;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_signal_set;
typedef basic_signal_set<executor> signal_set;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

template <typename Handler>
class basic_yield_context;

namespace posix {

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class stream_descriptor_service;

template <typename StreamDesscriptorService>
class basic_stream_descriptor;
typedef basic_stream_descriptor<stream_descriptor_service> stream_descriptor;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_stream_descriptor;
typedef basic_stream_descriptor<executor> stream_descriptor;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

} //posix
} //asio

namespace process { namespace detail { namespace posix {

class async_pipe;

template<typename T>
struct async_in_buffer;

template<int p1, int p2, typename Buffer>
struct async_out_buffer;

template<int p1, int p2, typename Type>
struct async_out_future;

} // posix
} // detail

using ::boost::process::detail::posix::async_pipe;

} // process
} // boost




#endif /* BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_ */

/* asio_fwd.hpp
Uux3JM4Nxb1P45qZz51q+4/KmMAPcwyii+jtiatS8LvROOTSTOupkralxd/zF5z3u5TzQrkXqC/ui43QK7knhdSw3LXm4on/LfG/t+i+EVc2OJw8ova8fl/a1nFmn/NZuY4Ou0GrwV5rn2iJnuWuM0XCzfT+Vu6HmH3CgTCN9VbUWnmTVDh/ljQu4yvuCdXKeJpqsz1nisZa75ysjLThWeNsZ5L+LPVivGO96M+HD8SeOUYuYyNO8tUF2i/+N7g0TEx/HpB3eEJQm3QL7aT9ofX4NvK3jTZGuTQHN8zv0b+KGwNdn/CenKrX1t7UacMXqKcywiO1buHlVBvHaPee0s6Gbg3rp70Seb20xai/bP5QNwTNURki7cYRvPHLOLofa8afZyrNSoOdKg3axKhxTKmqrfwestXeX6PcJETRWnFvYW4eL+gmnR8F3RwpbdliZv09iWv7WrVb5Zp+gQLtgwXFjmtLoxzctc69lfZIHXIsTvs9vbI7ZIaEvNWNvK4usifQCf7+OB1t26tVvSft+fRo9MqY4jKvJI9O0GPNAnOkvUVnFjf6SXlX2OYR5OROsKVFu+eNsHSPMdwIaU595nfD86eLhhvLuLbrdGxu+POnLy7HnwQHf8ZY/uwP9qe00nmsuZrTpM8t6g1ze0Oq0dvsOEfccndHczWvKWJuikN/suh8ic5av0747dGGzrogHW8LU6dIsE6oe1DMVq5viA3ef9aaKxVtO8vWjSnPg3JbXGDf1jiufZgH1L6uyDAFz8edpvaEff4KzSuKL9tkLwot8ypms3H+btDet1sU38SsjLH6tkfze66K0zxLjjvq92VwFmY25g5MBZ8lv2jT2R70e1VMoB+9otWHbndH5D7bvTsVKyGrjKmC+YTr8rCYGW5L/1ScIbNYFd3Tcdbvt5XuNkw1rnep6+r8roHZy+8/YxZijmD2Y97B5GFmqN8HMLsxt9vDr9y5D3OnTV5TxacWlPgoN27GJPnUb+XenqB4bxO5JTuF+QlTG3tTbe7MVXopsQGTyv1v1N7GJ23yOsjrYjxqL2IvjFK/47U+7LlgrBEz9lywnvs98q6MkTGPpvof71Oc+7q1T/GCF4w9dRuae+/OtmR1DNl0S5ZqyCaYsgZNDNlIS9bYkA2yZI0MWSNLVt+QlbFk9QxZrCUzw+eyZGb4vpC6r+D5zXssmenvVkvW0JCtt2QNDNkyS2aG7y+WzAzfLEtmhm+SJTPDN8KSmenX35TVM8Nc1ZKZYfl1gykz3fvUkpnu7Vcy+7nRWy2ZmR9rLZmZLo9bsoZmfC2ZGZbbLZmZLjmWzEyDNEtmhvk7S2aGuQey4D2nW1kyM8xFLZkZvh/WX7q/9JeWzMyj154zZWZYxrx46f7SPTeLbMy4cTmiI23Ov3M/af+4jozPWeM9It8n7Xnk1tiAyKsUsv/00OAzqZX+uQvO+1InXlRyWx8KYZRvcts8MNE9jkzmBtu+f5HzLei8t/Vu5BIn63tO5KeQB+15LfLzptz6xiEs0lb/ILrg3OXVQTLZe9uUWW1PCbeDPAp5haD9tCsG6gntNWT+6yY7Cq4NTQu6XhF0vdl2bV9L9pjsRIM/bt6JMA4O9+8b8oZfP4/RuzTiS/tdhc1ajy7ZYX5X1Rb9j2nJRrIyK15mMW7Fp9IyRqrcw5c5zByeoCdqu5gJWcJV3xzjtHTU9xwC3ZbWtVTbu6no5LtiCElTNNfhTyXm27yNOYeZwyjKNozTHDe7+7Gm+0xxsLW124tOXVrzFcy+hdk7/bIwp3lulpvmGG8OpS972FjbPNT33vRr7MLVOtrTSJ3mrSl3uCv9LfxSyZ6ZTfdqpsNcNMuO2deB3xM=
*/