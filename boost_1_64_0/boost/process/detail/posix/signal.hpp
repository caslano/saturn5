// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SIGNAL_HPP
#define BOOST_PROCESS_POSIX_SIGNAL_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <signal.h>

namespace boost { namespace process { namespace detail { namespace posix {

#if defined(__GLIBC__)
    using sighandler_t = ::sighandler_t;
#else
    using sighandler_t = void(*)(int);
#endif


struct sig_init_ : handler_base_ext
{

    sig_init_ (sighandler_t handler) : _handler(handler) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor&)
    {
        _old = ::signal(SIGCHLD, _handler);
    }

    template <class Executor>
    void on_error(Executor&, const std::error_code &)
    {
        if (!_reset)
        {
            ::signal(SIGCHLD, _old);
            _reset = true;
        }
    }

    template <class Executor>
    void on_success(Executor&)
    {
        if (!_reset)
        {
            ::signal(SIGCHLD, _old);
            _reset = true;
        }
    }
private:
    bool _reset = false;
    ::boost::process::detail::posix::sighandler_t _old{0};
    ::boost::process::detail::posix::sighandler_t _handler{0};
};

struct sig_
{
    constexpr sig_() {}

    sig_init_ operator()(::boost::process::detail::posix::sighandler_t h) const {return h;}
    sig_init_ operator= (::boost::process::detail::posix::sighandler_t h) const {return h;}
    sig_init_ dfl() const {return SIG_DFL;}
    sig_init_ ign() const {return SIG_IGN;}

};





}}}}

#endif

/* signal.hpp
RrvknROxX0kaT+A7Hr3e0S0Sv89T3jHLeBX/iX2EEs6bXOb7hKGp2X0zc6zf/TvjkfUY1b7DKB0ibyL0OoEfSJ07UGd/GWk673I5Xkl9nlKlP066LjZecEkaa53VeesTIvvaByVD8lzunky53nruL+NrV2pi8uCUHOqp/BxCpJzqIXZrDcbDBImPDBnmCTX7R8ZWfX3NNZc0jY3KjJBC6w6q+jeTulTR6ybNkv23XMnUbY2rnEqnxx7pzj/nhmWtxq+k7/4WYvZ/ehrpkpOyzPUeD0ialpLmaRkTvsuNphvVVD1OS5oHPO2NfMbDcKOys4SR4jzkTPa4pZydlHNW0lwWYunDTI4lnUga8ScoI+2PC1FrXLHJ0lv6/E2Vdq2hvQ1cNVVbj4osz+WmDyY6rjU+ctTju+/1jMtdCUZHVyXDLEsWCNNj41HJFy3x86Rd/TISU8z45+S6Kq3H3U+yH2KY4yxDf68xQ+I+YVaoaNxH+IVrU443K0Hyp6WotT0/KrQ2G92fKHNiofVAl/nrmDVI19HpKVzHtrLvlmMs8KdPNtvUPaBNK89r0yD9PjZH4t43rmW8TSWIL5POs8FRhafgLEK2I8GY66ikfHtU/eUeaB63o9QrTq+p6X03uMDJb9gwzgPnJspzs343+Fgp37tBf5q1Os0NRabZS5rRcd40Dc5LEy9pfO+lxnjTRIy7P8oVpdM9ElBWZ9ItQRYVPb6yJY2+Znkqy822tO1jc/6QPj2g9q1lLvaX6RkfU1Q5uyRf6C+WU0A5d3rbED5+sL9uTwa087C/naHju0e5oots52UROt20wHY2h4H1a+OU+kkZ1VQZKRGqPo7xT0SFhUe5J74d5fBEhXm8+SjTKfUjBBx7CvnG+o5d4D/28oA0K0nzbClvW+/a5E+zKiDNTjPNuqLSHCfNOO+xQu5aFZjmAPuN2C9dOtC/rLAv2XjyTyBMJIwi7SSlI7hLyZWvGZRAvCmfDO8mTFGcqniP4jTCz6V8f99r+Xu6/lt/J1R4n+XYDdW6ijP4+zU4E44tLb5pEmLUenj1LsBHrUDue+b+4hDTZ22vw+9XdqVe83SHKdPfEd1myhr6ZZtNmV4bdb0p0z5wS01ZPb8s3qXXZL3WLzvu1LJrxNcWmcx7TFmD0rISs7wrVub45MzZWp6S1p97YI7IV1rkvtVMuQchTw0pvg4HmczfsxKQqTk9Xq2rKnnN+Vzku7XfnHWevDZmoK9OBvO27G9R+/PUfmmPb3+Z2j+o9gfIWA7Rzygp8i9+O0TWUyxI4O9Q+a2cl8vPvpRMue8WWgdSfgOie0qVdBc7/Nd9B9m/SOKptiqnu0P/ZtYyB2nk3s5f+reR6LfSJL6Kw39vSZT9x43L6JEeRnP9u2VQmDy5SL4wm2MpWSE/Y4f6neVff7WrxDdwXEUPX+QoIWVF2ZSlZAHrwaZlpKRmUJyv7qVs8ilZwG/39MzMLNPX+XGJ/5y1rGICv7utf7tlSZpv+K1QljXRmpIOue6DcN/vW/pumKSLdZi/Yxh3lnm5jqSPlvTHSb9K0r9vFKUHNcvhHBmm/nWD5NvJ2Qg1njPKn3dOKjCfbuXhqy15nyJEOepFecKjXKHkDbwXxaq0WeyvIESFjhsXOM/XZJ/zKfPXLDWn3WP+LWGLmr/KOALmL3s9rMwPU6W+pfT8UFjG3KK//a7X8tTXNWOXfRm7+pvxjDFkaowhK6WfUfVYsdPbyjW6SfqUe2TFwtdo09L8I2uukQ7Gw90J3t9D5jXaLz2pP9UIHOf6t/ADvnHCr12X7XsEytJjNE+eh6VEPUZXS/wPRiX+tXs+JX/R14Yae3MlTXnb9wsqvx7/ark=
*/