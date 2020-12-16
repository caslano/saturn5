// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011 Jeff Flinn, Boris Schaeling
// Copyright (c) 2012 Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_HPP
#define BOOST_PROCESS_HPP

/**
 * \file boost/process.hpp
 *
 * Convenience header which includes all public and platform-independent
 * boost.process header files.
 */

#include <boost/process/args.hpp>
#include <boost/process/async.hpp>
#include <boost/process/async_system.hpp>
#include <boost/process/group.hpp>
#include <boost/process/child.hpp>
#include <boost/process/cmd.hpp>
#include <boost/process/env.hpp>
#include <boost/process/environment.hpp>
#include <boost/process/error.hpp>
#include <boost/process/exe.hpp>
#include <boost/process/group.hpp>
#include <boost/process/handles.hpp>
#include <boost/process/io.hpp>
#include <boost/process/pipe.hpp>
#include <boost/process/shell.hpp>
#include <boost/process/search_path.hpp>
#include <boost/process/spawn.hpp>
#include <boost/process/system.hpp>
#include <boost/process/start_dir.hpp>

#endif

/* process.hpp
AdAQln6jjj8b8YhEEsZfWYrtvPEdkct9mFXLY3IDG9HRSpoqepvRAKYt7pZMPwwM8tqzT19gvexsBSnrL2pkURUlNa4Xaii6UXVWxLRsLriqFdYrviErrPJs78Wf3OpqF/2JN466HnJtmypMND46AjaqdnDdgWY2pzdh4YYSOjrHLTsGr8Ei8kZMbbFaAr2pjxXFs4F8/OB5vzJm0pcrNpHMF2iXxoQ59n/ibueZ1vTV0Ys7QtoUiJy/CUNAXtUGIxvuDpnjyOpMxzohNtSILzE/9jGfBj5DaaeJLSwzk1cu0S8D404a1+eXfF1ei6V/vUoiSluSypZ8crT515f8O4ymgL6J/XB9Q+ve8/Xjom0Y+Yn9bnl5G2tg7AoDyVvamMskGnPpwBiPHrFvRCZ2vtgxjgQHd427+wyUoY17+MGA+mVcMb3QRF++c8dXxKyEaGnq3TC84IcIPHeq2bsEKmnLCXMGceLIYEwE5Ow7gz06a7rcU1RQcGyLJx60OqbuZEZz1rP2xRXH4C0hXInUBgAKgBTfvd90IWANQKoieVaYSQucIX/2gQ+QSddqJhNT775QmcMpgl/HrxPcHBsxwI5PfzM9sERWZ4ssdrEwjp1SbjELnT5NX7phehHMrnWSDnpRYauzFNGu1vIiPLMfmr5antkfuA61whkwkM4XLGmaNbDzvA/f/7X0+7+6AT6pvtyD9RLhxHj/1vyYVxY/doUJIuiEtyWCsl7iLBqiZvW/75V0iHfKmWrxfwkC2Sr9pyr/FO2fNET5/fBTIR+AAZjf50+Qr7CFs7HTU8rll5jyh2zHWaajcPb3t52pip2l8MSPQY9lWXG2w923wFc7L699lnG8WhomvFVkBOtbqh41WdgV1PVA8LQvKky3ZKYl5hsd9SrOL3HlrZXvp+O0c6asBnsXpKVrvVgBpljbcpGCXQTYpizdWvKGi/OjU1XEkYjAmVo8aOeTGRJ4ly2h38j8NmolIyWKUAhru/2xE1XEVkTEj+Qq44AsdYLOtjJTt4xcYhmhAu+RLKsli/A38usu0V/nuz4JaihxXvrt41XspYi11K25SksP1ZMQ1pyemajet+IRpyMsXjm5JVr5zyOuuZScciwktt2EHRhaA+R90/MV+CwFhUH3TJTVoWGVc328FnTDRbKVZWLZnpTwBmJKcHc0Md+ToC4z3aku3AywpgulTvu6AvsAovk0mIL8+kh1Q7pmMYIZ/Rxw4+7EYCxA/fNcb00Z9F/OO3h1FTOOmc1fdqlLfgNUKJvze1SUx7jkonZQ1fuPhiqt1JXcLqv0GLQ0X8WeoFEdewz9CuTfBeRMgnwTuOjDYG1fUDlaEUR//RRlDIy3q6cqjmDwgm+oZGt0siVIplRltpJxqepjnnx+H2/+mkurnIo3EJOLFMwfQf6W4UlcEWcB58XjVIpvZKgco6SEiqVyV5tLhqisEtqf0WxyBlLK5XdAQm0EEkn0Ow3p2KR45JN4Qo7q+H/oVc4hR6t+2D893gcUbeTauLNck3SDPn/cepTgNeoymU91rC7Z463ak9aFnaWTnKTLuVnnXCY5y58Iquh7A5qDKxBf+LwYuTtOla8BnKGLnoIEjJ63M7UQtnCtlpHU9NBumqxrE2S9U8f70lP6seam63XsW+pugv28k3uUCuERP2km3RH3+jW2DfG5ectV5KrTALf5Z3ols6GTxWrEmdEpj/YWKcA36BsZiU7LyCIhVfl3tHCjBpDgbNrOPFaizxaE4k30FNvyaJXxVK0y/O4CLYI0QlPFKsV3WeQctcp60yBuJP3I+f0oTibUDdnyq1iI+wJhYq7Sjz1WPfr5s/hdFGd64npyeZCjzGtH8lk=
*/