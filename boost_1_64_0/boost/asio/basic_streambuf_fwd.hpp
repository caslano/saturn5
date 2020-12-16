//
// basic_streambuf_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <memory>

namespace boost {
namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

template <typename Allocator = std::allocator<char> >
class basic_streambuf_ref;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

/* basic_streambuf_fwd.hpp
BDBFSmiWmfMNrBRPVKTK67nNjJ1lhlPWM6VBmX08skX1gZbiiSu+vlwN76pNYWQCLJbu14XqMHTC9IvZfCi64hcl5TQSJc1J86tJmYRN2eI+OCboLTCKPlK6DxPJxTY8etw+KM2xQTSk5pprynNTpV/64bNyUPCFWo5YK78WmOwS7u12oZIn5aFJMnmVdmVU0fzncLeuR1xZ7ENoKc/3RFEQCSdgE86+OPC49E/Xoxba1/33dawYRpL2GJ+79S5+t4BgGol5l8qHtIqxQTl38Y99bhbPJp6E1jnmWtjJop80cX5OaVE65Wl2uJwV58THjwUXfSbs7/Xt3/RFicIM+l5/sSDZzreb1qOt+j+0MJc82lfk/rBUJ+ssFauGMeZ19j/Vn3bviQYBLczmDPETeS1PZAwyXhkxWHVYkPiwuAWAx1qUqe7HSDQvtR0OP/nhMm0kWSx/FgGtsdMxHnm53lJLm6aVuLBmV9ksiQJoAzyN2rmaRMSvfRKdIkalPxVC/xGhYoPZ8t11dQUuHpev+Rssc1P4+EHrWHu/dqpg7f1P2VUrmLVQ71yoWPtr1Sv7vp3Ay+rhuOdDeczDMLDhGhsewefY472ZAdYtPOXnDk+vYD54qalxQoTpS7XQ8fvZ+T6T4yMTeLp5tqKqzSq7bkqrFpmTtdFaCaw+9UKby9vSb7Le9RTdKIcvz88whkTd2LWdfePFMBIMXBX0ZiH/hPjDAylPr4+S/B37DP3umnNrWFfCO/YkzNIniXzQvC9/Ez3Cc1wh4gIHG38+blcwk70y9ROaSr1kRhbL470f5zU0br7/GlzOOaYNYxjpeY/fSG1zcxXWVRDAnVKi1me7YEDnA4WPVGzs1x+AZxnjZyXcXu2r46ep0qQ23s4+Hydnkkg4r0MpXqBrUOo1l5e1adDfsY9BA/MzK6epauHCU/TXGUrpuxlgaK/ig0m7KvbftRE2M8+7TFZ55dkzoHPtetrjLlmV9lGDymXVwidK+hNaJNijoZECu7GqKNUO59LaCdk9Gwm3DbiYkE82PG09v6XfON1JsaI7mN7HJWikz5gob7Zv/fOxhzf4cILGMK5amroPEt9gLAtI8Y2CIAjaeuYA2oBf8Ktaj492ZgteHSuarFZzjQ+qMqHEKmhRKfgk1HZcmOmFgbwV6fOPg2ziMstVo++Mb4l+dEP3CTgyyXNzIVVAqjO+Ifb0sPgQ/IBf4uWxyZPeBMkkh9t4NKy49NqeloqaH6tVXoQgCNrYZ9Xo59wM0uSL8/ebG1aNGZRRzUd8pMKLu9Aufz8ByYLh6C5S2OPNWms0rGfq71qTSx2+KRVikrxcgSFA8qEvlMj+MC2urKNAgpbemJXaSsNsfGbSu/xg+ro0YXyCJReAqOfK3J9jYvgIVf8YAADApJFK9L1/FZI6vV2vNvdvyNSggDkfhpf9SQd/lk25by5At2TaefWBQuAbXPl0vJLxK8WD5260XwmSyG2VXgxhPybTN28bYxvH14+X31n+5qx3KiZ1u/zW/gmR9uPv+d777jpBSad2Pg8Igr5CG7AlvTru4lFP6LFwopM+4TjbB72XJIeWzoSHJh7ZzWzgfZtNO+iZVpOAdv4kcd2RtCtvpz0vQBAEBwAAl/Q9FFH8qftRjQch0h/ftdnbOcvLtToqFLKwVZ/X6OTxz4sq4bVnWxJrV/IG9T6spvu3s5D3sploVtqE6XpZ3u7U02C5MPqFO6N1sl6UqTTaMlRR8IMDFtxf/4G8pAhiJtYAekcs4pL0rfoAAMB+pH9+vIjkOIHfBTYQUuBnG/ZMvXILluzKybew+FbRtxJcjVg5yhXZO23VcD5IhZTnwezx0x9g63vo8s8=
*/