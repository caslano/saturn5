//
// detail/noncopyable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NONCOPYABLE_HPP
#define BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};

} // namespace detail

using boost::asio::detail::noncopyable;

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

/* noncopyable.hpp
qE7XOibyOsdjMFIXeCoG6RLPQaYrvOAH7pExNPn066wTXedP/NBndZNvXGpN6hZvusF3k85+5J7faE50Y5m1eZM50W0+aoV7vddx+C+32keXfuY4q8ynLtzGGKnDp/zc2tPhT2C6rvNG7I0x8C4MsL3NA+vWZIyBR2CHzvNE7NFFnomduswLsF5XeTk26zpvxFbd5F3YoNt85C+8w50rz3/EMp1u97vlDvdR13joL41NV3juGu8E3eDL7nTtz9mHT1jrWdDhXSjo8I3rzJ0O/wHzdLiFqq7/uiP9aL3x6xZfdpdrfN4xuYU+HU6/cW4dPgVVHb4dK3X479ik87+1lhqeL93mC3/n/eb44cofXI/t4fsxVlc3mCtsjvHwRuzQTd6FrbrNA+/2HOmMR2CZzvNEbNBFnon1uswLsFJX+Wnsc65so/X4R+vzBfvzsZusbV3iLVii23z+PdaZrvAvsFA3+D+o6nSvsWGtzv2pI52ISbrAn8NcXeE7UNEN/i/KOttsnCjpCm9Dn27z27Z4rnWBz0VRl/hyjNUVvgkFXeef/Nl7XLd48H3WpA5/BP06fCt69tmHh/3FfdFlPvwB70Nd5+JWc6UrvAaLdJMHPug9pnM8FbN0mZdjnm7wa7e5LzrHU7FeV3gFxr0Yfz6y7w706rTds4jRusRXYv3/3CNehdW6wQ9jh27zkL9ZAzrH4zFdF/lSTNEVvgHzdJ23YLZu8X5sNZ7sIe98bNYFPh/D7FPma9Cja3wXxukmP43ROv29I70R/T6b59OxV5f4SiyN8fMqLNYNbmGPfdo8ZIfPxvh5PPbqIn8Ow8xDhW/AAF3nLdgQ4+f92Kmzh40fM3SBz8d8XeZrsMO5anwXemP8/DQm6PQP48cAnefTsUyX+EoMdt4qr8LmGD8/jD26zUMecd91jsdjkS7ypdgZ95pvQE+Mn7dgVIyf92OyzlrGj8G6wOdjpS7zX7HYZ9v8uUfNp67xax5zjTrHazBZt3jc454dXeLP7/Ts6AZvwwTd4hFPmNuXjmLPLkbp8AH/tI+u8q1Y0W/MfC9qusm377Z+9hsP73/Gtdve+I/zP2tOfDa8CINsD3/tee8QHf42JujwSkzT7Rc8p/tcl8+Gx/d7h+twCdt1Zb93yCvWtq7zC1jis5l/PYN9xpN/TZb6ULe9wk9hoc4OyNIlmGWfKm/CWttbfPRrs5RsDy9EpsNLMFI3+dABWWrYPzwXTR1eiN26wX86KEvzYt4GOTZmxGf5kddlqaDzB2fpjNdnafDL7h1vxfSYQ/7QYMfRJT7kkCxt1hW+Cwt1eGdHlmo6vA9rdSnL0hwMjvnha9Gja7wG/XHfeRsG2N7i57Ha9tSZpcOwXud4DPbqAk/FVl3iOdigK3wtduoar8EO3eBt2KNb/Dw266zL3HZnaf4r9uf7e4zZtecOzdKL2KPzh2Xp4MONUxd4DUr2b/GnhmZptq7yR4/IUi6anzzS/Mf+bzAejLW9ziOGmQdd5E+/0Wft0+DsqCxNsz3PfVhie4XHDM/SYtvL3J3L0oo4Jve8KUuT4jhceov5t73Nq3uztOwVzQOPtpZsz3gEZug8T8QoXeSZGKfLvACjdZWXY4qu80ZM103ehQm6zQNHZGmyzvjz2BzXzhuR0vDU4s++1b2IueX/YbXORlpvxzrmAcP9WdVZ+tsoa0/njzc3b8vSdp8t8kNY8Zrh7B693X3R4elo6vCT2KPDL2OQ44SPzWdpmK5xP0qOGb7sHZ4NHf4qqjrcj2W69M4sdZ1gvekG3zzGetPhAe92fOcKvws5HS5inA7PxBQdnvFe91KHv4lFOo3P0oWoGluFn8AynU5yTZirs/c=
*/