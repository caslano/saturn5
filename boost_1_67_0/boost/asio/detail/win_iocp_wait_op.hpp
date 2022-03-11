//
// detail/win_iocp_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

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
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_wait_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_wait_op);

  win_iocp_wait_op(socket_ops::weak_cancel_token_type cancel_token,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&win_iocp_wait_op::do_perform,
        &win_iocp_wait_op::do_complete),
      cancel_token_(cancel_token),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static status do_perform(reactor_op*)
  {
    return done;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_wait_op* o(static_cast<win_iocp_wait_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // The reactor may have stored a result in the operation object.
    if (o->ec_)
      ec = o->ec_;

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_NETNAME_DELETED)
    {
      if (o->cancel_token_.expired())
        ec = boost::asio::error::operation_aborted;
      else
        ec = boost::asio::error::connection_reset;
    }
    else if (ec.value() == ERROR_PORT_UNREACHABLE)
    {
      ec = boost::asio::error::connection_refused;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, ec);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

/* win_iocp_wait_op.hpp
U00FyDrFSUL3rR5ZK2pugKk3Gvt0FYqa4kCkqXgZ5GP2VJNaU8Fy4+b6z3VB8MzedK6jDCSB9J2OIqmKZ6RFyeioMCDxi1qZu0fXiE8/UouUhZfF/l2EFV62GtfBcyimQ+hAwC3WbGlBgeOQXKvWkt02crybfLt2ZzLQjN7bwd0CSdwFe4rTsappxoPs58l0Fhoh8aeUAAjhL9zIPp+kl5ERsRsYipT0LKDB4I6jfBHQblrS+a1ImBjebbWel0qol9beJy9WRg0RQ3JoErcOFtqD7VsBdp6CyS/n+XZUYgxuJX3pmOO7ZjoIXlBWB6V0Xj/GHrg03rMWqcelCD9s6/vtGHtLF+lLgOgZYy4BlNuo7F8DvI6SekdaOCyuhLDn38NcNmCcfykb0lCDmS8m6ibYTHFJJIAds+R4rlllJBf+ucMTuRDivux+eLtxaEq3wDSxEAxhJMZU19MeWCnILsT5LyJNDfQOvPguL9zEjdes7sPr5rcgS5azRNIMGy5yu8vTTbxo9GC97+omXCvwc+sdLHJc7F5xFFCWBXAWAw9IvtiTsueDNgNJkBFZexQp7kt5Bkce9N1pxhHjdFUtfE6Wx4BwAgbSWHDwQ9DtYhjNw2ZktwkdiWR8R9Ko+W4QdYGJuqBgM19fX5rfilzhlrniHAFzWSEJCsT2G00VsuFEaeXRv5oxDq6RTMXxbDcEg0NNC6AQjxX9M3H5fiWWU2sNw0WvYRnQ9WxGF01dICS1v0k9IqEI2JU001pJYSqZFY+fwEeeLSAsLAqDHb79TE2mIoUa2GejG4ktPCzapRAQ2NHFaem0pg7LQnTmhWeJHVhw2QAXDBNQptV0GH4AwnPwmI/p4qoPHl5pY7L12pmrJsNjcTiUTKge4xdc/vt1HYBHhj4oU63dWjNNZjXICv+WFbn0YBzPkT1VX2ciRpE7mSAi0puqtbmTRdXFRVZ/YFvrqIlDZHpOpTk9686Cj7sEUmNTmulejnUxLmy2Su2hOL/1pKUfW/n88o1lkDLUjzDg0/+46PkjvBFv/33mdji/39HchcyQQw73i4PfUpPjUHm+WqpqxRauxr2big//KbiPjEKOteSTIMIkw0mylaazRgaFMNn1bDgzJRMLQIREnUlYhwuVehidl9NGsns9x1gFeKIRcEqUvNuAgomuR5i9yXxRd/QOLf6UHN3VAXoiAqGmajxOZSMlmZY+lOAdWWWFPeu8cHP48y6lWRXs6b44thmblcYXkosMU3QYbsmdxVF5mxptR12wj6RUF0Hg//Wmp7J7XaYcXUIyb8Ndv6hvWYRl+RzxGaYxtEue8GYlP2quNaPC6RWRDbSBNpoLeNjuL/ADhWoGDmmIPc3roLwsy/Pr4CU1dUYmASH8zRZBg4ToC899LNfo0lHiGERepokWzTk9cBksGE1o6YvWqn6HWTUKFM/lWz+a1mOapE1PLdkLZIs2rmFFHXko/vT1ca+OA7gFTgym5p8eieYrnA/A+zOMoE6EWGu/USC5kZkmjYG8JHQdbum5tAuFgu2ijZc/bs/w8AHOhlHuscwWggP/FR11wDbIcmDh8+ENhOoCFkuQhm7LQ46EB2sJ93+1AJ1koCIB0SEylYT7N6rH3ru3k/YK7OfkjCphlmU2SbwDzG61Z+IpjstDjw9+dPXDFm/yVZqNpa6v2+61ZELTyXxlVhx41ykUOUbYt92jKkHjuD8dWpsyPuvQyi23uf3lnp1JHinyo1rAeCEVQ33xrl5+NYORIDRRpI5UcypVwdCtHkfvRS5LR1T0vYpjMVHAw4gLSoB3yVNUdAa8i3VgyaB+LDs8XRbe/TvLN/TR+MTqXpSr+CXIY1nEC+Kvu3FJ/rhoPvk7hNxMsdBM0wSv/XBDP9y281pTE581Mq5gyvsYabJz0obmxVnnRUIo+6e9UeVEmw8X5Y5bXknsr3l2tXfV/CqtZiuIwb1ezvSwGzuAoQn5yaV1OqQX3UtE2f6FJMVXNOaI+pZCnUVYRdRgPCOccmn60Efswxo5zXzHkSnAxE7jqevL5InQfIxCse7NzcMChEnmq1vQkPKbNtjyGqEEUDQe79HgTiaIXO5CpL1GhaOjEBfe9vkw6LekqAceF66FlEA3FVmqxgRi+RaDIKQPjP8gnWxS4gOVhk4VkYSwGXj9a5gx0nibtTjHxidyMgIALXkv7kkhOaTcJSFtBfczsQGyrxuxCz2j7n8Ee34lQVVOC/lVgSaONOEiIiICvCum732SYU4PX1rQiSN4hkXYAnpjqVF1m87lbEaH36F0BymB2Zs1EC5cKf9TZ/l5PHsPDILLWKh0fVvFkpPFbuzv5dN69u4xlGb8LfRzLy6TpYVZ44ZjB7dfP/LqzYzTSgALJrkdNDjlJ9AmFval0GDnKULyNLBYqeMHRbL4C/ztSRNsZpLD51CJt3VmNIprul4Q7dxMZY6IyhalV0TE6r51f4EcO+0c006I2M0rdCiUYxX3Kn9dtFE5CgMj456At0Q8wAHUkEK+2+vZCovP4LalG+Z3oTDQAGLQ0MzyTdB3UwqNestN/Sg+87STOBI0hKuCat6H4uLb5aUsW1CbwSifQSMIQU0F3/N3fzlXp7LtdSlI0W/GBTR2W8j7RqCjZoWwYS/P2MGji0TnlUSk5hvWSYfjXqOX3MRYVEkTCqh8GQtfdb/Dyoff8O99ZW9FyOsBhczCK96DIerWYCkEcZB1jdfFGaw1rKUQYj0EeM6YQFA788HPdsiXOyj/nenGn+5jmJSt3ptjG4tCo0El/AtLep+zjX6OLYyYQBjhmPn8sVKtjbI2L0XpCLc6FWx2HxJZehHyangm7RXNjVqHNhtNkdUa3fVb/v1i6I87b4W5MLVTgtbVT/zd7iHFYLcBQ81GNRSJxo3PVvHAmwoq7vJC47pl+cc1delKSnj/Vsj9rUginEsSxoQzs/71UdJxyqk5CPOAJN7EiPSikdZH43t79eQ0gf13/3wRXlft51L7Arriddle/pbSoyfFFup5wF/p/zqwEpi2GFK7gM6LuUfwQxR+dj2vaG8icO4FzOvknXGH/Fp/M7RaouC3Zf+5xPcEi4shbuNo/p4vk70epwgRvZ1nqLdqHqUciTFoUUeeVCgpdyTD81ugK2fysm24OUp7COhS/HnOPGOULn8uqHBbHzcqIwySHm9mFtQbzHTdGG6TOZXkhSWvs2vW5oa9A0cKkic2jcEHFZ//+pYFm+EvRD3WMM3A433Osu9px2POCYLf7lbSSiSJQMUIJWXqKnslNwMUdlHIFwYJT6eXMs+yTSqeHQQjIIU4U5I+uHc9YesxUzBULzIfmRF3xxCa4LKlMGOpMSuaDSDTF+jxctSsZeyEvSYV7OVLdlfGEvbPzFUyvJ/dKV2l1rPumXkXfxbSOq4T/g6DOxh5PJtT31Rvcdk3C5dOaDHsYbtQPg2dIDBVNFU2TSW/SCqmZYlpkP1QpEYmJJUzSh1zWiM4BCGzXq2xXbZMzYxBKRnNdu5RCToFUaJ6qqOL500xi2AuhWg83JYlH4eoU6kXomXpFnPAkuYZ7KbM3Q6LboV7NHqarA0aZEOj5Ok8BwIWtuIBGGJqlneR1qaUGLXC49BfG1/7dSZEbIpJERLjj8IDQdBm6+2j7ZPHPQyZzbA2p0+IjxN8o+Emq1+473iWodkOxP0UNM7ye6NFI5cQAw2AQiMjgy3cmJjZd92Dh5OPU2pQuj8peLPJscO8ro8GgT6qqdiNTkrLUuSC/oLnuoT3hQohRaL/6I5i3Hg0KtB0kdYiLms09LMz9mIS9/MeBNpnebf0xDuyzcdjFkNphQO+L6YsljQdhISXjNfXM3wodcfl65hag+k1MEqQT+FYVXkv7uoQ9Px+XtU+C5PZpX83eR+HRiw1DkNHbAVQ1h7uSOHCuHkWBBMrweSDQWei0P9g22ka1csdiRxux5W+F4zyaZLFO8/lXO4+Y4tgD+A4DQ+alk7aWHKpCVoZshTkTGRJ07AMQ1gu8xm5nYomiLvA2Iee2gje3/Mu18BVOiJRObPWWzZtk+Kj8DzZYAoVNiLijzhdIw02v3DjUoAeT7sqs1d/RUUmPbpt7VwDOFOzHUewEjvVaaFV1QIoOdOBIJ2WPCAzyvQ8j1PMptfoZJINVBl4N5Kv/AMsB2fgaUafx+B1MCQVzvjoXy3IV9YXne/ipqCNC8UnDBmrhcw6Y/v3kJal4RUiQvv1UKjzfHNZtn7DDyW9PB5yOQLfp+c6cnmNtdDj4vKZWGNYx9/rvzVQRWDyUUbX2FBL6Pk+L5tNMJq8G2Y5q5HQCLKSsRAL3oE/4hiW7vh9XrP3HKmzlIxzWnWAKX8WT/YcyzYC4K+hsG+6CJpfh3QfoVk6sVux9JjmQzM5jtbShUoXNs35aY3K8pr77lZo2b8j5nngQ+6WD5mAWWPQm3m+zLuekqMdWZXMeJiYSoL3EDMKoDwth4mLLW70Sm++CaYAgROZNNHURdnXd9VknLg24bC1gT8EQeUUyySCW4qggPWwGLuS3UmGXtqiCG3KD/HzPyLo6RcI2TZugPeqYtoGdjsmOvkDxKTjqUIedrsG4VgJLQo1ORpKP/ap5sYXuS7WPi+jSQkPedyEXF2PnHHjWl8vO5jYU3e1BTl29c0aPe/zg+y9O/qgkfqX9Ie/PWmuT/m4f2yQSZcYup+UYKZQ++4R7W4uRJQ0KzdIBNMzM6iQgX5fZowvlEi737FA/SJnG1S17g86Oar12x6CuYdXcWhFyRRcf1lbXHs5Tgo8cmu7WesahnHGAeXXc8kSG7grikG3v0/22AlEH2QjkpUXDfQaEmgcVPaLtHyn9Gm2uZnxDt/doJeR6UzfiUdAZo+DI9aVo29zJrtUS9fpbDHCaAK/jLPSuYSaSOtQhdddP9JGSWPQ7wk2TNjXt95sAF1XkQMQASGDP0j4oNG7f+Np+1Wc5nrP6EdTSjQlGJq9T21Ph8DwU6Q80eDdMsa+8h6Ncz8Q+Qd1OCf51uSAQTGuxstEm9ZgjDrDFLHJDOR4CNMrQyY7kphx6q+B5jb4hOzLpiXXshZUDNX91OgOMB9CStjgYnFBwreZGkPcW7oZvCT2UeS4f360EvcXOJURKjqP/ybT8Vbw+/tVH+9btelMQKuUDs0niSBWXKeg+YREKRD2A9ky6dGgp6yqqnp0k9j5Qlg9juELFtC22FStGz1pJ1oKQNv9OZFSfv9gVq6/1es/O3gRQ9QYxJzFvLjdUDRhz0bAtj5dtvHDBTfnbqidJaW9jbjIAKGGYB0Xmc05Ycq7eaztaZQdU8d8KHKT8h+xbI8F8c9NllYGxqrApCc2etuDHEgMzsziTer1yaDKadA2MdQkpyLoExRUMKt/OeujS8ADQJSpr4qSw0ONQRFmxmU4FguK3QruwhLxwIzZcN+0HY7UMVJb8GJGK4WqqpqNqK6mo5nn2EnB9CPuyweue72KmE0sUZXWtZCTWEbZR40+kuKfIhbDzjKeM+D/TrUlRFqeDGNi2BGki0HDtGGW8Gye+u1wVCYOXw5AVwKMmz6kC6ADQCN1tEBrv9kTGUcKCPwKBYNGjkHcukoXwBL2hJMAwUXiOKVqot7XpuR+N9GEkzKDqoi4yZP/aY7In/T3LyyI4Oza0yon8Aj0KAAVDc1hJfZfnNdzeZ0Wm4wMDnu95bV6Y+kMmkNFcxzRizuNm7NFAbNM++5hFaMN9MGaX7AMgZsP8d5TIfJ+S0OAX6o5a/0PWNUxSD91RDa0o/picF7hQ/uDfMMWJUqsgIkbEC9Q0onrq9IJgOzOAR25RMhrgkEmPAAU5AlRIIwJ/uxzL0Bk6+l1ACvlerSZyr2Ge37WqToq3m0Pl870pfvFvBTxAblE5QUSGo/vzY5j51f4VM3omaOpygbl32ygQlDO/2aZHekGHM168B/BxPN/nLFfQcvMcbI2xhLD5sXpRqjneUw1HUJLCjG1RPa3rbBdTrWE57EWxemPURZ2aLV4o1tCaoyr/ERIVjb3ITqU+0vgysG8WR5mXlAvvlfeZrjp5F4NWIzqWf96ngLC8iXyGY4MqQjQBPabIF6BbmuKBAYcEZfpYIfbqDv0mbCQtk9C2QNBCAHPsvMGs75H67OneGgbsYsGtO3le98fDMe6WTrgiMWn2pwPDjwAQ7IUN2A5/XFlE3Ra6rzt4YmnHDZuR7Ozz7ZFpcJn25jquDE/iW2UYxmW7HnF2Or3J2nxnTSXG2xEYyFlaF+zeHwWDGT2GL7rF/KLNu/bjb+FMAYVyhbm7VfV1rKhBkzRx+jZZZAtJuYpwNd9w7x7crGq4JILKP25PnFVSfagZsxYoAf3m2ux0QMD+V4kgarOj3AzED/GAwUmHAuu/W0nQqHG7N+T4XVuKjETsh9luASNmJm+bTMK+VvQ/OfL8zTH3dVj4qrHE+iX5DmlUhwGqwHeA8aZJ66o2VS6YhxjBRhMZZFEMiBuAOrTZKtk/asyr8gp/YsQDuvzRuCGXVngU1JZJXhW+pMh3PgGUh2fiT65uEA0e3vQ119MqE6mca5NFQBRUxkbENw1KSLZ6eaSSV51CAl/i+WEDAA2MclP2QM0gqHm9nJYlAvIjoAwCoIEh5EOfwvZS2OccwWRMna4J6ekd/u/0ChrTIT7DKJN/joOAmHJOjqMF9j5pTm8cfi6T+X9Mo1DqIWZVZ/xUDL747gc7+cFzK/vyooushnH+zCmONVC4WAxb+bzuFn6XkEhc0nDcNiOdDs4zkQ7wbHtFZ7xdR6fISdTH9KeClXTdwoLH+9vwfLihyl0p31l77ApSDcXsU4CwV3fHnRIS/kQR5kPxBMOxQ2Ga4lYLrBJ83094cJ9o7G/mbGzaQD4LVd5mK51/VN0KTOM70waXU5gqT7nBvRwlCRvN8jdCFM06vsPuO3i05CLLE7hEJGNAiERrahRD8I9FM7OMPQ8DD+zuZypR+IJ9CcUg8HIFTAFrFAjU5Izu+2+gj3vQ0LJd7ZC2nYKfSFuLG3bH/m3pA4fppQJQYbDDHg8SuGQBOq9E6s2Iw/fGukUGRnOx+x/cAMAn2uE+qZDgIxcwQFKiTEq7EMnbfWaxL7zap4uNgighZUMRuNZ7k0Z3ksUzcl/SqAC0B+64bb1tNdiB2HyKBX2rPb+bdEDmk7l3lROrv+UUYI58hMCXHrT+/dHLCDQvgLFwGJ/CXayzKV1eyq3t2u+ScQCxcM/NbspWFLWI0+NRu9+8IWQBQ3VCppOLfcZo9rtUigYaIIw3W+DNNPk12smBD5BaH9q71HjoP1GsK1xcAa6LLU5ro223eGFpnh4QBFK7e367NX9oHUGsVI7sygPG7dVopDLDtXY0ews12m2aiKoE+QZiqALqCH/Ys+D/S6oQe6I6gGo/BratJUVWOHUvDiBtZnfpYBMV+UijtE8jWPiSuA7/a3tfSeCXnwRXKDMOkDF6E8vG9Yv/0wF3J11yoMwspQhZodfr3EQbTCi/L/zsBZ1jlvvdDzllXl9ks45jRBx8RnnqAb6XcV5SlWpfKzN8gS+hlGTU4krKN4USyfSMmf5P21QdpZmLq/i/U5Y8sYvFRBFL0q92IYvxIa9DOb96BB9JpXl+ZZ5XS+WFiSTyMcnpFZJqkyWVKJJS/Vc6i31GzdsfnZ3A5nIDCg/sJ2S3OEdjuIcoT5v7gAaRhoW0Q8Z8hg4g49uOKGkvP6yIBzwuWIqDFyEXcp63iSdDmqlWnWmGU6OT3tq9O5VkPC5nh6neJyXAM6OicmpLu0fwwly+XEtzglktEAhHlne6w3wgKa1xg7rBuQxprpVEshzayI2Btq1vPmKlRz3nfU+91yrfbaazExyixvHZf+MeYKfCMthPW8Kd6Y2D5HbAcs0XELPtwR2ieAAlaZ+i+d0cRYQ3Cf02LzEc9Vdj/yuJp/XNxn5Bw1ZR8hZrJvA4Et4Hqc63Xl5x6cIYx4M8VazvN1dkz+nBH0hiVKmEaVWNsiu266runBuVq5oLa76caQJ4oK9cYRT7iMl+m8nUQQ/HrA1Ttkes3yvrNleFxWHZ7UpE+xBEry0X6c/T2knKdNZd/jVFLKeklDgsD5KMDx4W8VoJ8GbZ4xjjjGkv6WwhfxsNhlzVy3sOK9seJ+0qGSOxVRuOROMTo3eKfHidLODq+9e3i5Dk3Zx39fRNeJIsg/ZZ3NNlhLiEC7lAorw3A9fPo7tZbcVo52ok4FFpv8bDJPbqXaWf9t2NwBTOxspAZ/4gUc4haJcXWusxQaBMDo7MKP2GAiBr1EEmGc2BZGCzTeQf5gQl2eyXfuhGxT3XLtGpNzylQJCC3WYJMcu1c0gFIIv2BMc5NpjIgHMl47tquxAYY7ZN0lTSqxhUHF2daoCw/9KWw+MIQSVCN+fMtyqKHvWQAcLsTaS6oVbrORcwZuk9OZDHicRzivVUHw3+LMccd18a0CfPgBkhNK67VJTLqjIEiWmKBu7fluqLTu/VFGqW6p95to2CGbgMDF8jq6POWsr/CJjQ/DnySgbHxqa7VzUHxiOZCzihgzhChJYzisn7iGtlMNJmqdOl9Mt37Gpu8vSuQPvsC2mY1O9x4w8zxuowlSVmgUafgJVL3LzZ4pl1mE7MWjKF8Qc/8VOSU2JCwIeUjCdx60ZH6jQ9DLtEgnW34NOzWtmjFPLcGNQhanHuXuXrjUDOP36PqRKhLuNPnAlFK8VMhAlABROaL/s69MsBC+Rcxh7vvsIiCcV/y3GLLEbrZ0/qCXRtbgpB4+vbs5+NHQ+8jTb3EzHD8zIXJ2apgZ23VWcL+D3QMZofJ01mb75jBxV7xwQCGR0/ecq/Qe5oBNDnv4p7nw17qBrpiiLVNp0uuVL7yeQcoj6pvE8Q8wNKDVvwpkEcJLwrADWhSRelOC9LAx+C20ZaDZ5zJneQwANVFqeJT8KJjB8Q3pfQEaunOc1uvgtung4xzsMRoamuh7K+gs1io1wCpp6GKXyFmRQzPZz+6zvjXnM6q6V4AqhHRETRRfwZWK7x/ygjEwrNga9DmdUytHd2LW+WradaUCW2nVJpywbxNZ3vufzlLLsZmVtupJOKwbjGCgMH9oNH+qDsPzv1ex5YoDkiq2B2Lxnkxmz0ckUUC7BOCRxDlJGZHELnKWpttPFJFVdFddcgev4E2aRf+EiKTey2Ym/z67M+9Wp91RSg1AJs0g=
*/