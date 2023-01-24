// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_HANDLER_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {

//extended handler base.
typedef api::handler_base_ext handler;


template <class Handler>
struct on_setup_ : handler
{
    explicit on_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_setup(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_error_ : handler
{
    explicit on_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_error(Executor &e, const std::error_code &ec)
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_success_ : handler
{
    explicit on_success_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_success(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

}



}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* handler.hpp
/OHG20V2N/9CYE7LSD7TB74ID0DWjiythQiDkHgLGSux3Ma0jDW2P/8qj2mTMtdX2TvbG8eoQTn45we8CWKdugz0M/0l/zSWvp/IWGeZGgubz8k83l6/l3Dvr7l+EN+Qx/IzhP7PYiFXud63DYztp8LqXjsOWsC4pbvJ7DfTxqNySsaFon6XzgYRM5qdS8ew7cD6nZ3LVwdw5tdY89SiJEd000NS5RK/Iywa0qBuZXgUTnnSFPL703W9frpkdIsl4M6gU3mCEGijkh7rfzgLPVeUN+GIOyKC4HVsz69TPr9KRXLVk5malsU3Tu0rs3XXHmfceburMYzJarbnBDkJ7ZTYgq0T7r1ZJjeWsGYGbF+dRD0oQA8ZX5370a8WecGdg4GOER606n7fExQn7mmAjmzTbvz2odFfJp1VTTpo8qsxsr2MBWoGCNO2bdvsJPbCmywsie6rWEkZ9bjanDDI200st0CG+RG2BfONgGuCgrJzz38R2LbxKTkyec3u9xdxK4BSk1CgOw5zMMxs2FfelQcw+haHlC/qBrPleHRDCtJ6ZJkwPg62slWdDmoUE4FjY20uksbH+bhojwK9ZXpKy7pltZ8dOWb7Lwl6NM2ZNUXI6jRKxnmLRBoiA4Sn1J81FegKcjn5u3nqvAZKPQE2KfpMBvBAofyiJEfW6+0eEcocYQG7EuWx+/Xbc33uv7H2FxSYYkiP3enAToSG
*/