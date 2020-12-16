
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/detail/checking.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/thread/lock_guard.hpp>

namespace boost { namespace contract { namespace detail {

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_unlocked() { flag::ref() = true; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    init_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_unlocked() { flag::ref() = false; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    done_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_unlocked() { return flag::ref(); }
    
BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    return already_unlocked();
}

} } } // namespace

#endif


/* checking.hpp
5+JT/tUjXkOWzr4IPsKO7UVX3LAROWyJTUdP9ef3ufvR7fSvYTjt4Xv0wY/fX4ytBw/+kIl8QvfEl+DxLzxiJVi47TnENDLReSvA0x5wXhL30GfSVkdsIzr7CnDC3nxoj53/Af+hDT6FF1rMvwoZuhn7sZvvQ41C14ORDzGHXejTkVOxa8jg/fSlH3qx/fuwP+O4uTE+aWuwE2NO+hHc+XfsLTGGdi/yvQvs9Ln70DGfEIdF3zSVMcTG8ARYcuknzMET7Bl8D706DqxK7Ozwix7xKzGdOh3QK4yxJrhneRPsShPGQCx69z9okzjmxfgYdceD8VoRW2yGvk/1fzMok7ldPBL8Mgo8c4Q+E1P8BdlrMIf3NrIWQSwpin4/9xZYZx7jbwFebYQfwFzdtwr/vAf0og970CN9H4NXw+FjH7EP5CcMfn4OeuVSZxx28wZiCXnEk0rRJaPwH17B9lo/g7+7wztg7UvxD4uGgoOxnxno1h7d0VdglRWP46dA54lHiVW0BX+D90/NQd7bU3cKcfkSMFI28bYMbNN8vomEz5j8OViR9LEdsYV9wC7guSuH4x+dQnyGfpyVhe+NzL5Au6+D/Segw9J7M+fYgS/hs9vBNX95G/tO3LkXMbI24L3If+D7g91uGcLYwGQN37fF8+i1o9jkObPQTcTe56BHn11PHAXd3zoFPAOPR2aBrUjfgL44/2rsFnJ6J/g3Av3SLBb+gU7DjsC3SfRlJBiddvPwqccR49tN/LUMnz7lA/xLMIAAGz+xG/0xxY/b7kW2L2eci2/BhoGtJKZO6IRO722rmNpUMOTDj6OHWjHHyO1Vi6BVMfFJdP8w/MOFxEGyzkfXgidbfA8PPoe/TuyweyVY6jyw3Y+MoyaYGr/+7uvBA52QiUngYbDoHnzVQUPRbeiOM6HptdBo63Kw/Vjmiphan17IUyv49Hn6WEhsDxn4NIL4DPkZDbFzEfgR0CKJ9keCm+NeF8Tu4QPipROvwD7ngvuj0WkP44PczhyBY2rXg/fQYaOxgfW/hkdXwD/w5KjW+A/YuVnY9lELoedGbBq4bsdP2PIL0WUr8fnD8W/oY6fLwUoj4Sv8ukXM/Wjs/OtPoxtngU8zoEU4ZU5h7v8GzYnLzQRvbkQXDt+Hn3cX65p5nD0ej3Knz+sOIrProUsT7NyV0O8j4gRF8MtWfH3G9mKyrXRrJnSNuxSbSPwtA36s9z1jqYveAf+sBS9YxB9+Qt9fAN4rRj83RTfN+JI4AvGRb2jzSXDlx6wVnk3M6GAsunwzuC8W3dAV/NgZf9UD3m6L3IPFG4C7pxBHW5TNOmhD/JhG8AtYNeZqcOBzyAa4ePrPHnHfncQFbMZBPyNvp90zwe+fsa7MXNdE/p5Fdp9cA03CiWGxLnFnHDRdQUyNV2a/Dm8i06sPg5PKiLUxNxedRnwJnNaAuGiPAczJr6yx3YWdgNenUc+iQeAAH3jyc+QLemRdTMzganjpFc5uZ+MLtsTn9xLrhiZFjLNPAhg1gXh5OO825C+YpHdv8DjxhF4dsVfXIXMDwVQPIvOMaQv2oFsPfLQK5mUyZ//WynUofKGh6Jcv4fuNzOUkxpUDP1yLnroXnTcSfsLHqXE59b+BPmQcPYnV7u9L3Az8U/oTdLkZvAaOHsh4rgCDLsOfzj8ABqJf5/0AbeHPNfDIpevR87SxfSfx0/uYS9YWH99MjCMJXR6PnwEOSCGmUngFMQbqHdMT/tuK7IBNaoKp5q0Gd0H/DjHY2NdsEbYOe1KEn5FJfzsSg2OOU6MFuJ/1i3X4oLvBZJuYs3Ow9W9A50LswBz8irOImVzNeIgFbLoT234vWAl79Ep36Io=
*/