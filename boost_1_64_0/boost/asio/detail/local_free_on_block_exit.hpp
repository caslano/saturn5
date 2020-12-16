//
// detail/local_free_on_block_exit.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP
#define BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#if !defined(BOOST_ASIO_WINDOWS_APP)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class local_free_on_block_exit
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  explicit local_free_on_block_exit(void* p)
    : p_(p)
  {
  }

  // Destructor restores the previous signal mask.
  ~local_free_on_block_exit()
  {
    ::LocalFree(p_);
  }

private:
  void* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_APP)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

/* local_free_on_block_exit.hpp
GuZeRO+YSQN3sgZ0+M9fzqR1OvwBhtzpunbJpC9huA6nXTOpoMN7YoJu8P8w9a6eTd5mt0yao8PN3a0BHe7HSh1ej7W6mrcNG3V42J7Ou6iHXQdG6BZP3cvYnKvOH2K27dm9M+kqLLA9XPyKedPhs9Cvm5zdx7gdP7wbhurwnRihw+fvm0ljdfh6TNTZvkw6B0XnCj+ECTr8Oqbq3Fcz6SCku52XH8DKGDNvtZ9r1Dk+Gm1d472+Zs3oEp+DRbrCV2Ne7MP3YKlu8AtYolv8AVboNMKawUKd431Qdb0FPgYzdYnPwRRd4asxR9f4HtR0g19ARbc5v7/15lpKfAOyus57HOAZ0SX+F/p07sBMuh1t3eQjC5k0Rle4jfE6e5D1gkk6fAOm6vBizNZtPuDrrkWX+AEs1S0+4WDzqavcM9J86iJfhUW6zo9+wxq4x7lGZdJnvumzusQvY6jOjvYOQNIV/sEhrlHX+FWs1OnQTLoJVd3kfb9lLeoiP40ROtw5xnXp8B8Py6TJunS45xEzdZUXYoOxNXjQEZm02vYc9x9pDetwdaz3y72u/ehMWnO8uY3+fiZlfmhudY2PPSGTxkXzrBNdg86e5P1zsv/WDd7tlEyartOp3r0Ystj+/DTm2R5+8jRj0uEmlurcJPcc/Tp8+RnmVofnIzlOtWy9IaezZ3oHoKIL/APM1GWehaqu8UOYo5v8MRo6e1YmHYrlusSrMU5nf5xJu2KiLvDpqOkK34kFusGrkP2j+eGtJrtGneMRaNunyGdig67wXDR1nZ9Fv27xRiSfzZ5tPWOQLvB4tOJa+HKs1TX+9Dm+R3Sej0RZl/hiTNF1fgF13eLOn1jTusBPoFe3eZ8p7qku8tUo6Dbv8VPr3xiK/CDm6hZ/5zz3Tjf4t9McU+fOz6Qr0dB1PuFn7ouucmclk0bq8FcvMJ86PB4V3eRdfm6+dJGvxHJd53cx8T5zcmEmnYiyrvBN012jbvOvZrjHOl3sPYl5usa5S6wr3eB30HTM8Nhfusc6vBQD7BN+FUN1+OZZ3jU6/E+M1ZVLzT1W6+xlvusx9E/GyUN+5f7aXuAdqj5re4mXoxnj5IOv8FvF9hpfcaXzLnHt/C+M0OGPMUaHh8/2PtfhEZiqw/ujqkt8Mebp8DVYrMPPoKnDq7FWh1/HRp27yjsE440nPAoTdPgSTNXhBzBbhx/EAp2uzqRvY4kOP4aVOrzNNda8LvE+c6xPXeE9r3U/nLfN91/n3XW/5m1+7ftLh3fBBB2ehqk6XMUcHb4cC3WDX5jrudO56z3X2Fu3eexvzPMD7gu/h4bt2Vom7Yxhtud5CpbbHv76jZ5hHT4WG3SNn8Jw+4ert7oHOnw5JkT/LpO+uNCxdJEX3e451dk7MukozNZlvgQbdJX7MVezvwvybOrwvVihU907B+nBHnZ/73ONOjwTI3T+fr+jUNRtPvcB31+6xl940PF1hfsa3r26zNdioQ6f+rB1r8OnYZ1u8/6POG/DtfDFGKJrfOZSc6vrPPxR91EX+fxlxhP7PJZJ2y33vtIFLmFsbOd7MFk3+AWM17nHM+l7mKDL/AjW6fDdTzjOQz2bvO0K90uHv4SCDh+AsTo95f9jqs+Gb0RVh+982lrV4cexVIefQL8uPGP8KDtOeG7T/Orw9ajp9Kz7+Wf769JzmXTK8679YXPFt/W737H9r+ZklWdK5152HkzUbd73Fe89+zd5p7/ZX4cvbnk2dfgmrNe5VzPpZEzU4XcwU4f/iZrOv5ZJd632ftCl1zPpDgx6pIe9G9eYCx2ehhE6PGatudLhEzBR59/07v+HedN13vYdz5cu/jOTfoPy0h62f9t86vA=
*/