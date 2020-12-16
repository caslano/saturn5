//
// detail/completion_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP
#define BOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler>
class completion_handler : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(completion_handler);

  completion_handler(Handler& h)
    : operation(&completion_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h))
  {
    handler_work<Handler>::start(handler_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    completion_handler* h(static_cast<completion_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };
    handler_work<Handler> w(h->handler_);

    BOOST_ASIO_HANDLER_COMPLETION((*h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    Handler handler(BOOST_ASIO_MOVE_CAST(Handler)(h->handler_));
    p.h = boost::asio::detail::addressof(handler);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      w.complete(handler, handler);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP

/* completion_handler.hpp
6IThCMVOXEQsZAov8S+qoSUGYBoicAHPIVOSj8iHymiBQExCCNZjLy7gIT5Dp/ISGZAXNdAZoxGCg4jBS5jUXiIzSqEReiIYS7EH0XiIT0iSxkv8ByXRCH0xCvOwBrtwHDcQi49Qab1EGuREedRGE/RCMJZhG47jBl4iHiYdz0IBVIEvOqAfxiAEW3EKNxGLDzB/UQcogLKoj84IwEQswlZE4TbeQaanVyAbSqA6/NAXwViMrTiCK/iIlBmILaqjNQZhClZgJ07hOp7hN/7zN3WJamiFAEzFKkTiFj4i1T/cF+XRBB0xCDOxGodwEa/wC4n+Q/0hD0qhFpojEKMwDYuwGrtxFk8h/0t+IC+KoRzqoROGYDKWYDNO4wYe4xtSZPQS2VEE1dEYvTAOS7AVB3AWtxAPm8lL/Bf5UAYN0QUjMA2LsQEHcRGP8R2pMnuJXCiD+miPAZiDcFzAA7yDyEIfQ3p4IT984It26I7hmIjZCMN+ROEGniEBNquX+AteKIYKqIIGaAV/DEQwFmED9uM87uENlBf3QB74oAE6IBATEYoIROIc7uAFviNJNuodmVAQldEMXTAYwViCTYhEFK7hNf4gw7/EGeXhi84YiplYi0hcxCPEQ2Unh5AfVeGHnhiJ2QjDAVzGM/xEihzUC/KiNGqhM4KxHAdxG1+RIic9DqXQFIOxALsQjSf4CZeLnolc8EF9dMAATMQirMUBnMdtvMBP2NzML+RBKVRBffREEBZjPfbgDC7jKb4gcR5+i5KohubojzGYjGVYh/04h/v4CJWXPUZ+VEZDdMIABGEZtuIYLuIh3kDmIyZIi8zIDW9UQW00Ryf0xxCMx2yswjbswQlcwn08wUf8Rsr85A0KoBzqog26YSgmYwnCEIGTuIU4vMNv/FWA/EEZ1EQr9MFELMF2nMQNxOEdfiBVQWoGxVEBTeCPIRiDqViKzTiAC4jDD6QtRI6gDBqiO8ZhCbbgCGLwFN/w38L0atRFVwxHCLbiOK7jLRIVYWajOGqgFQZgCpZhN6LxBF9gi1I/yIaiKI9G6IDBmI71OIhLeIivSFSMuKMwfFAX7TEYk7AM23AaT/ADKYp7iRwoifroisGYhTBcwHPYErwDfNACgZiFCJzBI7zBd6QpSW9GaVRDc/RFMJZiF87iHj4gjTe5gupogQBMQyj2IAp38QauFHMMJeCLfpiCVdiDK3gBVZqzLIqhJlojEMFYjB24iCf4jb/LMBtRFX7oh0kIxW6cwV28hfUhzvBGA3TFEEzDImxGJE7hCu7hGT5ClaXPoQAqoim6YxhmYjV24gCi8RjxSFKOOkUx+KAhumIQpiEU23EaN/AS35CiPHsBb9RFRwzGImzBMdzAG6gK5D9KoR6aoCN6YxzmIBRbcQjncQdP8A4JSF6R2CA/yqEp+mACVmArjuMGXkFUIvbIBx80QFv0RhBmIhS7cAq38QauMjMWJVAdrTEQU7AS23EWt/Aav5GuCr0ZPmgAfwRiPBZhHXbjJK7hCT5BVSVHkR2l0QC9MBlh2IcLeApZjfxEflSAHwZgAhZiA/biJK7gKb4icXX2F0VRE23RF+MxB2HYiROIwQPEI3kNzrWoAD/0w3gswFacQiy+I2VN9hc+aIQeGI/F2IJ9OI1riMMXpKzFbEBVtEEgJmMhNmAPonADL+GpTZzgjTroitEIwSYcwm18RLI69FDkQXm0wCBMx3KE4wiu4Sm+IGldrkcN+GMoZmAdjuEaXuAX0tfjfIhqaI/hWIA12I/zuI33+IM09YklKqE1BmEWVmA7DuMCHuAdVANyFznhjXroihFYiHWIwmP8QBJfrkchVIQvOmAIJmIh1uEQLiI=
*/