#ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
#define BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_typeinfo.hpp
//
//  Deprecated, please use boost/core/typeinfo.hpp
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/typeinfo.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED( "<boost/core/typeinfo.hpp>" )

namespace boost
{

namespace detail
{

typedef boost::core::typeinfo sp_typeinfo;

} // namespace detail

} // namespace boost

#define BOOST_SP_TYPEID(T) BOOST_CORE_TYPEID(T)

#endif  // #ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

/* sp_typeinfo.hpp
mZHv0jdxZTgi7Of8ns1V+S2j/DhZnimTIGXC2xSB/sBtHWPc1rFrz40cu/6Z5rgka9skh9idBbI/tOb4aphC/2XhWSZT02l+Oxr9mMuKcmlsZwBctIJx0m359Ulm1CYPU/vzaYKyrGDTUuaP5Un+mMB12DDzfs4EGCpwLCtpOQLNJ//jP+t56CeXCFqkNxOxxzzsR2+Qs87u6zK6nZiY4WErfzyHMzWuH94mg4KY/p2PukR3UsN2mwWshlmkyVZeObultR2HIFvV118UUVEFFu/Rc4UHtgDdC8Ensn3C79m3+PPN85WsyIW/dt8FaYtPH3t8/lIq8UlW+BSa8Ql9XXwsmCy7mDARFkMX2qkJCZ+3LuE+MyuqFIzkhPSTuXxsVCXIXYbzs2vkmXb0m53+20Rd/y3Dmf7bRKv+2w/jj2lMCjh7wDkOaPVdsQ7U+y7G7yT6novf5+K3m76Px+/v4HcyfS/H7yH4nRL97ovfqfT90TqhLnjVer/LUSOAgzefb0sCfWcignZPkKKyUjwfmSxoSjT/KSpCOmvmON2slpTGbO1twQoHssvGu3PiwPgcwPgTwtD2GRuJTEocG8bnAMYfEybSg4Tzhid6j9tydJSErx7vMq/0i8B4ZtC7SFvMERLPDMo/NozPAYw/IQzNzNhIBChxbBifAxh/TJjmqcJTeFBzi0wxunANccdGhf+40hWQr+QCaNCCrt5bB4ocCmDz8XQhpdxjvpJKuVxWkxUfDY8mB/VpctAuZpiEAIxEhoxz0LNNDkaIGUYHQPVN/M4V3/UpYi7Tsb8whYhCxFoABCSAGwMRgF3lkukmK8keDTLYaDYFZDWQrZKJgMzmj75sbRXGrYu+EIqkMb1GYSSQiAnifQni/fHiM+NGJig8M0HhmfEKV22zHdoGx7ZqPRlgM+gzsFX1nHHhaWz2VL7jgq8ejfT5Dn7Ct/z0wyd896DVCRMTPTttxYdf9HLtgOdBeKrhKYGnAJ4APClfdEzPvPN3aH62+3UJGbxewPs167hb/FQso1s8tV276lm6PxRm38+7CLGo2qet3m0s+3RsGJ8DGH9CGByddhHWfToWEg5g/DFhcM+mXZq3bPVBfDbvssVJ4riv7dOlIm0pR5hX4dgwPgcw/oQwvJVYI+z2I3skHMD4Y8J8c9sH33bLO8ju8TY7iGl/qOAltELgUSH2hwTxvgTx/pjxbbYvrFfs3HjDSBDvSxAfG5vmq8BNL47Hg95FeJkdjdJNHvbDVhqd46XWfUMAokSaLgFvwjcUDmj0UhjopTe/PID00sKeaUwviT5vso4LbTw0ORhXTQ7GpxkmIYCilzjOwQxrcjBTNZhDRi/pA37/RZ0DPu6ALzVvUcE4u0OQuio2jM8BjD8hDLqljIPEKEocG8bnAMavw7Rni1pwpGxRbSbHEbFntZmRpBWoT8eLgJDScQ/iJMglekVPPEoFZ/5H5+p/dGqKo0hQbDGjmmdE96aNnQPx6w3EpvM7MBCjpEBFlBSoiG7942vgoa1/PPTTeNj6e4utfzxs/W/9jbb+tWrr585uSjAY9HhfgnhP3PjYkTwNEsT7EsTHLtw6h7fDaBbE0ygxwoNyJ5T7M/apJK4SH+NJF+64lDTX58lprr3wNMCzGp4yeMLwDIenJ7T8Bz3SXC/B8yg8t8NzHTwXwnNKj7TOs3jnr/P3H/zF5r/8bJSF/zIK/Q2sxyWkLTdmrYkbEwBuzBPMjTktWS05hfi/tUm4QC+EyKMhkqm8xfeLzTXA21hOW50StY3l0PYTG8bnAMafEAbXRLsIK+soFhIOYPwxYfRdMgf20qC+P2ZjQCE0OjK8CqFPVlhOYEHj2gLzCSw=
*/