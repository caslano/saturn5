//
// detail/win_iocp_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/socket_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recvmsg_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvmsg_op);

  win_iocp_socket_recvmsg_op(
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recvmsg_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      out_flags_(out_flags),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recvmsg_op* o(
        static_cast<win_iocp_socket_recvmsg_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recvmsg(o->cancel_token_, ec);
    o->out_flags_ = 0;

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  socket_base::message_flags& out_flags_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

/* win_iocp_socket_recvmsg_op.hpp
sPqBXGel8TVFbCto5vs+cRHKfmro4wgBen624/jQ5qCKijxlEjf3CNQ8at6SVhNP206sJSXn6dsMiK6zUAhsiEFkGHXlIgUe7HXIGosbMNAzpE29jKgm5mNlMKiEbEsMMffdB6GjnRMB0bi7YIRy/LA+/eNT8ByfGUsuUK/L97z6Xxio11ZJltVkG8x9X9VGV+00bmP71td14EOE/CAAzJv+lJpkuZhY/L9GMTCMdzROhZfG8z3s1cWdLeEgkdxwBgYvlp+i1O6bna1RsmgeTuOjW9pxCmrILke3KWlL4sSb4/9CRGPOvwSJE3GaWBRkaGMaPalCg3bbvXfz+2Hjvq/0b/ZFHaGVm75iJmpNTNiWj5B5vmJIiITxhdLN3esSmB9btyIVSJROXbNHNeoJMbdlfPUiBH+V5LAvsj9W+7IrYEvV6mqg7NLaLWWawdkFwh49UgHBk3u9ZO130Y3OH4mzJTSRvjeejHj2dV6Wx+IJxe1CsIQYXLTLaq05fdIhLTbJ4F4oTNPFz9MMfUjUsaZqqGVCCfov2ALxLJkEoK0n0CarwPsrb3nh0/Fz9AEUH5JhaUdDI4gkD/0emzv84lJbQVOz3m8lIaTWHTC7fVAxD258e3Q1TYnU4PXuxBAIFFCPJ+IoeM6v9T1DAaCg91QNSMcxuDbpO1aZcdh6eL9qtp7zLWI/iSmDKVicEQwLRtdiCfDUrLEn5v8Rm2AAq2n9VtOCgIrz2b280kyIZUV7iq7KcM1ftmkfUKmj10Z/GmHvUuHZRMm69dJrhtta1BKW+g+MGCUE0w7QrvCO9jZT5knOGWWUhpqmmUKc0phWIiQ9dnqfzCSdqLbrpLvA9K6enWtdX6keG/1knQ9aGWPHtkjEGIrQnjardHpfZSnPjg82g7U+jvP8OLmeHOZap+iEOtbfoFwezkxepuvAXC7/UDNfwt6I5YA4LgdX4p16uwYeL+bOcNxcV1dmX27dVDKWOs8o5vRIV45eDvxrVTB9t8S35F190tgG+PScOlwWxei1uupo7s7gxDQBzhDGAC7V9cClxnHFQZ3V9Qbi5ybNRyCjvUHlBp2CJ0sq64plH3heSzNGU080/RTR0zmkT77T1TFq+besKVY7pSUe6AANrLI5ljrXlB13MXqLVZPftbhmmYc/2bzFy/yKPIR863eABaKjQATw8fnqd7eNFv4Qbt+9Rbk8TtnzyN2bRBktjrpv/U/o2VDtGYyXGduTSP7zKRTUxzlUzDnAmfOxIbvVKbMDOKlj0IoyuCvxpacjyltVbwCyNsa7o7S/QhFGULEj7dv9DGsL1jmEnhD8ueqd4eogmPB42q/lpifVtWG5xL9X50NX40bMjffn6jo68zFSTFNZFZxvyFZw2+AjhgnEftsNWMH6WXbbr6zP3hv/q2lxEICYG37r4dj+9x543bCet/JLu2aNTuanpLY/XNFxcmwkz3bQusTW6jSwXtG6W8bN/ag9+RY8llS8YI4nCf9qdFwLPp4mtBwdFSvsNBKlGZeZ0ubN6JqNdGSaxRAzcqD0v8/N7EhSbRhXUZFkncvnUbmDnEsTgu3rR2Y0HcRcZlYLgaiA6KiuMu76WQhM9g02DPYex7Y1qeMjN+Zams/5Kl2eUWdIp2qtgEMlmQku0E7qmEMzLtDd2XYINludlyFrxGCINKimbGwnpOmR4WP05ltdyPycjzZO1RaK//TqBtrKVs6WzJbInFO4mSEecF6V76Xa+r5cONuTTAewt6C/rbCXev+jNzkpMojYiibNBeUHG2lx4GywLICbbqalZV9wHcB/lIebsw+XwPMGHc/D0bdq3s8QWXBbbncHqIHQoUmtxSp1nooF5yep7bWCMfPR0u1F4YkvMeXoMt31rA7JMxd3wLTxDigf3dXsxMABEAAk02hc2Wv6ru/R4gTSG/0UTigIPaUul1BjnyHHkpLUZcghAh7TQPCa7gByWDWqSnz3u7h4GFlS4VOD+2hoole3Xjiw6yBudHUIfQA7125gnUP1O/2v13WV4eDfgYZKWhF/wvFi4rCMkJIoHsrwgaRRUOU0bK7kUu3vlJhxQhoXl0H4KGoKdbVUcEYWc8CriE9j43EHnqXu3AZDdPKdCzOUoIzZHmxbzbN3GIcjBDlhD7mBMpG8C5jtGI2MKfbZp92Ur6JISy49WxnYgx8IhyFr0uxjt8kG7Mp2OAchC9JM5I3JvnVwlJJbiaF/2TM7czDbosSqASzuVy9H6gVzwbuvC01Y86ELwqwEApBG1ZBd6vAs9DpBNRH6ZEJSuZSq7iS33ocpC6pKLB/qKQsqG7aD1mX1EHMq/PoEF9zHKc94d9wpcdla/taXgs3RHexNAjO5Ufoye1nXiUXkMxVdw+G4Eh25Y/oJO1ObiwefOoptLrFNEXsyQslYJjfofGB+34GeQx07GnYVjMk/4L4wPXe6btdE3UTdK8BuiMDwKXUB6w7JAMmJA7rZsEGblRrAOT1X5LYOSgAkMv9s+H+Mgdndjl8H3xbfD18duQHQ6haL7iEQLslLgxjGwErARsBOrGjCY9oI4griCeILjwgaIsp/U2mkJKRUpFSkZEQtRF1EXURtxCLUUtRSVMU/spNreI7RIBSCPC2hopuOTRx3qL5QabBsezpEW0RbRGtExbXb5dbPtbOMb0mbII4hbYCze1AvkCCOPo4rjieOI449jiqOBm7lIL2v86X8g/xUfIy3W9KkMcoI4xmuuIyrPEOROtGHwFgWp7zISGSnpkPeOviGCVlYJ0TiJIGG1Fgho7DsGTVpb/WZ/wA7EjsKOxo7BrsVuwg7GDuEMpsyh7KWcokymRKl1eYWh1/T4MWIe8LMsiXhDL16UAHv24OivktC/CPKnzOUx8d54sZspGzn7IFs1+yy7JWsQBkir1KnR7lJuVm5RblVuUG5Ubl+uU65S7mbuUKwPzHf4cjeySfJsmm8qREsp7+xTKdDWabWodqi2q7aQFojLYkofAxhlHOn1q3apFqv2qvaqLpD4nBq2fFra/LRKd4fj9glyUO1qux8Na9akHAUElBeKstpyxbGpytLzcQ8u6BK6J8rTi4xxjr7veAkyfraBKCnPcHHe0RP+67oLVfE+3F4xeFSCIXLCU2sHhfk+7FDRdLyQfMEhckpTKxW7M6uV4f/Pdmxqhkmd12nySv+Xex5Agr5hUzTveNDI9v+xcHFgRtka0B6ZE5kjmqaYhpuJmamaZphWm1WJm8G7wGHBccDWwe7AI/CAqISmjBtiVoqxBRq+nh7ifueG4xnPAwVVBYKO5P5kboqfzZM948d5Hawccj7EKe4+LczVmMS90tdfPDgE4M5QK9NHH3kpJR4rCH+50qAuKo+sW2tTGfEZL5t8U6jxFlbaG/O3QEqo5Qe/Gi0SJMo4JFARaiwZXKffa1st70yFAYpWYqZnHuowegqwS3DU8MZ4EXbbT5PnoTRFEFfBwxQ+Q7s5taVyEXIRKI2HpWp0npBlb8hxJ44NVw2I715i27/gl1zkFugc6Hz4HH889wL3I/cR9zL3BfcqslR7WHtge0D1UdVh45dCXnBjfIOD60Tk5OQo5KLkWOTb5Bjkk+R45CjkZehHaHd4WX8K9yH3FPc19wd3Lfce9zz3A/cvdyLnyEdQ3ijFtq6CYFQBrqxN5FLot5k1S9xNR2z400kE2qzDxPrD0FxgrV3ubVwuXZms3U59aDEkbX+GSB1Xnw9hz2/K7TmW2oWZ4s8YXOPiPNIQL4g/2JWj7YzYmsPv/NMwL19zyiWH6Mt/03bhCFR+bh6r0n/WdueycxoTaN4W91D3pPJT/9Nu7hdgYqsLtI4ThVt5JHfiJL/V35zXbZmcl5aGbg7/haKim68Pk3FfagLsrKUjpSOYv+EqwhFcHj6h6VIRH273b+IkSFkjVIRG/OAibV1/n9RI2PIEqUeNuSA11VTS0vuGxKq1yY2xVUYBQ3h523Cx+aWnyEiTqUmNugh7/MjK8j8pTTWp6UCJeZWnlXIDxbPE+hW/zA+3b/VrifcOYOJyxEdZYNekAr5TTCziQFJR0skQ16kCnswKoc7Do2PEM9P7p4NSGoAYgByUFdQJ6W9aLdQgGi9aLloAw7RdtF0y3M+zX7LNyVh7h4S9VXFcCyOWYM9q8STjtdu7XhzesHVGrRoaPJFskg+ZJ1uuXZGc8e2DLhMuH6h6y5qNrVI8ElpmWAdph2ve6ArNo+YiY+E+hMlf2garA7ICOYCFWj72QLkUq45xJ0ngxjHuygmSD5xMF8GuvP0UzonqqhccldXx60BJKJrDAC8B8k+x4u3ywct6fSUCQ7nywtfEvlFPyIuZfqMxxEGrY12+tz3SjZjbmlY8QIOuq4XbNnJkQAKqTE3OicSGgzTMLo/1eUS0zCYtU3SDFT/M7rEJiyTlkLMlWGMqqf81/AU81CJsDRRrBIOhzbAGRPdDOw7ha+miIWucWMoto27iQ09jPgmxETvHmKQFTkqTh9u0CVihj16C367sLyhOHxhvsxkTouvsOazt4UCn0f2QBn+q/pe5BktsNmUPE9LXage+2xOjA+aapATHIJpgRs9ExV9BeAef+R35PeUGpSalFqkGbCcNqyWg5azlpKWolabttj/wr/bP8r/hhiiWTN6p1ijFXEI32by7sfWFi+Hh3727dhCaLxiN7iHHAcfVL7KubR4AqasTMeG6U1HF3Y0mvPK6KMKTEVORaogFUiFI2cQwGs6cf4mP6Al3EPlfvatanrkr38zVVt5GInIdcg1WRcIz+cNF+96ksHgmD5Eh1zq9PG01n/DbKAZYWiO7lOCP3gQNvCwjDeM9xKzAbMZcwkTIHxsfE9cYmt3WlfPLhk4o3AMoepodXoUUi7pPblQQThzMXT9+macgRit2TVq9btDk6bI3yayOlCbtKQaZMrJnmtVIvoGyawY4HhY5/LBKz1rlFY6LyADNy8u+jPhmhaxcds74VoerXF1mqMzqmrIhhBdc8XqSsyb+9Q9dt1X312wueI03Arq/1iKJvSohpcTLHj78iVMqe7y1S3M8vCiLazBA9ofSQ5S4CxqHaHhZGgtkhNZzhRmblQNHlEOHkUQfrEXZfBe3zVgjS4Vu7+hUbjOA6e7sj3I1DKH5fWU8dPNL9PCi0DnfZbFe0yL8h8vBmRTnNJ7cpfv8z7z4XJWUGoFF/7QrybZpovL0rSkXQq+h3e+d2Y6c6r3i0e99iBOok/jt0e54ic1/O8Od+/oulSi/yN2fdzt9LpV5HilHutKZ3dYbvg//v58e7eA4aKNjjSqidvwtu+P0OWIEIMwNyCfl0niVHhItyqtWzVEsB+s1cKGrumcctvuDUnT+eXqTxVbX3T22eWj/LiUTTegJTkUju4TsclHHbWd2ZftMIntWuvND/TpLdAsdMObHZzqJZb7XDMNKSI7FqdM7XEH825zHe5fe+XFnrYd1x33HyDfprOGp8M61gC3Q3M26ZChV/IGDWE1itXPFufdo0Vj8Y7wV+lERevWtZDd+3JVx1dCerfKWDE+o+Lz+Zfvm9/K2LE4C94XaC2f59ijESG/rEC3BIik3OWYoRux63HC1mcTOGlUHTuBzzpfwvxdeea5G8COG3cxEaSdtAYNFs//Bt4IlhFY7Ie802hl6cswIZU0r5KSiDHd4GdXD/M8Kj3jtxLiVs4AHdrG0jaczxfXZA2yxs9wT7rNjMipJB7qgjRNJuQ/zMPde9G9wYFmAP+JjCRoBjSD+maQISgOrOMf8yAGPPH3pAICZAgSIQuuTYVQHWLgqw/l0QNUsw5/jx8cwyibuHwgJvwwBextH6CKnx8NBx5R5LAbntccXAw+xLi+VGt5uPusPUgzCXp/aX6huqiGVkA5HDbYT2gvfMiVxVZewxDatcWV9UcMMRFdYMhCYEvpmXGGhwbtog6oD27BJhHcoB4iIBScyA07jif0Jtd35aOIaQXM5NJRzkv2vtKdmnwK2y2A1B2efy6AB+jnhlcB6o72qV4ceTS89YdM/Ucs0T5Hoi31moYSmoaahiz5NiKRofkPfpt4d/n9ATo/cybfwnWcxij6VfPo1gjXVZ7Ahhxi6MBffNSkdDVNGfdJ0FiKqCRPyYap6bPal8cfrmN5E9oL6UyLtDBdwOYkqId3bUKxDQpyWDoleVqvnmepz6WXgFdPeHWcPSHaUcefMFdrkreLrHQNlTXsuZ7I6dFxR4pVyApc53Nm7HQCOgTSlFDJldBC0zi8Am0w0y/vsvFrSL9y685T2it7jcEhH0h5r1GrENMkRR+a9eGxxNJTHEdxVuOgOLDzlNSWsUXLrol0wQfBQ3CU7U0DLKYboJJ3fc/C75vn6D+VE0v6rVStrfDupWnzTzjnN/zuJb3HJ5POEd8FX4JpjOVCVUb4D7ctS+hbYSGcfOmqW9tN1TwmBNpQp7lVKQyRsR+ZXRAKOFGmOhSaFdYy4PR8fX2Mjse+JNz4BMJ09lwTEnUm897Sg6nGq6ea2N80SdQHoqRNErexkuLkox2eqfh7cTK2ZphBqlbOzfGvrp7Pf0mZbcMiY9stIG8NhCbwRsejyp26n4t3EPvMKURlmjI02HJc5TqMpn6/LbM8FCcZ4rnirKGL05kNDAwlU4G8M4Ti0nqrw5SR8+GBot7Em8QPYo4UZ8oo94vKzqLdobhuCMB1+OMcz3acgp+nE+OB1vsMorOQ6CnXW/Qx58mJe5eB27uBwyL6z0IlWflqUuLiSUYmBNT4tVQGERqY8iXisPd87Ktt2JVbu31Jk8PG//08O2xV8EJ51rw5mNu8WCDK9c8gN3CNC4mTQSueSrL7BLV0czKWWJXfbHJBxO6NWcrAkQM3H5lU33Pi9t9hnLmsiH1bLmlNXKmJkQxRIjc+3wTJLFXyPH8QCRIHI9jmsXv4rMvmoiJpUeGTU2zjXFlSWJ9YPIYDX+QOX/fKQvVm3qI83AvDyS6T7C7nZyB0tyCTYnKjb/Lg5oKAX/KGkZ/opvcbScoqzMnJysc8W+Iw3Bem5CwgmzIPqFan1BLfC0IKqkb3/NqEbnjWAR6Lc5AR5l/RZVenxCZuUdqA46pJunjGpP6nuNSH6kiji3uZJqTIqp9uSbnu+eTfhagHlRy/CW+RlkwtmJuVs2UcUSFdjhDiK5OTWkVn5dRNIp9CJycFn2h9lEPw6S0f4cXevZF15Fl0OH1rWpTOyBb6L7X68RRES8SgYuKgU1/cRcKW0c+vGvXi9TZSfDKFTnmRLfy037uKNgk86M0bignNxwr7dOZqYIflCl40BfAZn17pPrxSzeCBHHNRkHVVKpeF2ei+AaHCpZpAZFhuIZAOXviZWwqYVN2MEfS8SZ2adk1gX65H7BfkFexaBtt2pePI2uljC+eoRoWzSPbk7R4egqmDioUS25IR3a6DimnC/UbsMhmFTSmOUNhhjFfPYzw68OSVlHIB8PoWAgUlufsswHBOGazSS4yqXE6NaabRhb42LOoS/4iU1OwZ4ey5ZSEitXOISpk1uLMlvRMHpTX6qwGmlpY5oNOMtYrBUheEIEy2dPF9u77U8c0zv7MFtcalw+tt1An60WkduJmm0o1Zk6WkcJNOEfYbF9FmAy8Sn/mbMr0Q1bRZcJK4xxKWj9YOSSMSGbva
*/