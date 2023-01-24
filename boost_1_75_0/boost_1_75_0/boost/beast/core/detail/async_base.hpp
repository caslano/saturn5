//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {
namespace detail {

struct stable_base
{
    static
    void
    destroy_list(stable_base*& list)
    {
        while(list)
        {
            auto next = list->next_;
            list->destroy();
            list = next;
        }
    }

    stable_base* next_ = nullptr;

protected:
    stable_base() = default;
    virtual ~stable_base() = default;

    virtual void destroy() = 0;
};

} // detail
} // beast
} // boost

#endif

/* async_base.hpp
UqOxy7lGDCEiUpqccX9IEaLTc8UPDMDAaG6Y2sAJnbk1DuOUFgw0lnoiX8OtH5p2+N7Uow5K6MiVlG6RjxyqdKazwiyOfKSJIP5lz5RCaMvkZE7jsiaZ538ko4q3FNp/Z/EIYaLytz0ucCBSPjFCZzohr3m9V7SMVyVXLFFdFxf//DxwZ6mcNXIuKemdOu6HgixbnNFXzmGhwZ35iiuw2XKFTiuEXlrLLSg5K7YMrvjjU8pz1GR/2X7R1I0ahnCkOY44NGJU3b+e4epMjo0ppjlCnG5Z720vXRFNbmthSCg547a3vWXupma+toJIeXiedpLCh4Z0fruYqLLOunx9LO8P3pYC8PcsUs0YRsNMd3yb9fUij/N6WnLLLqU99+Zhfeqk1mUkvElya6tPi2NgIaY9Q0l7/Iqbe0P6+Z2TOYdXHC4NfmSgLqVjUh4V8y4Z1VsICHJB9iBHbNjXUf776vEf9ZCS93o8sqr1by5BbWr1HUTOifW3BTLOeSB32TXGzF753Br+qo5cS2+MmVwn/t6RjAekWl+a3hMBgz+MxCY64iW34HcJElY6IHH8WO4G9hExdTdS8TgxdVYlndvk21kKKc5cWlVZ7gjgvk2YPXWM8hgk6kU3qEUx1U4u3GvyFmn4sHwSQKH30GRFdr7Rr9szYXs82POnWO5+Cx0DHDzTPX2dZNlMAB/ugXH3Fs3Mk4w1tO9wG+RGzTT2
*/