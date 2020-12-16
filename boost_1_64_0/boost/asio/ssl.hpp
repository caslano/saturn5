//
// ssl.hpp
// ~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_HPP
#define BOOST_ASIO_SSL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/context_base.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <boost/asio/ssl/host_name_verification.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/ssl/verify_context.hpp>
#include <boost/asio/ssl/verify_mode.hpp>

#endif // BOOST_ASIO_SSL_HPP

/* ssl.hpp
lLlBpo0G8e3YI/AwWXfPMGKY0DVp61b+kwF6DLTHDJdywrOKE8MYL5V19DNmpVxipu/ByXspYPdBEuegwwlTdoBuP0C/Bm3/gSqfYRj7QcjkmIH5uNL3gxf13R2graCSiCflNxO7BVTW8cm4hd13D/q/qOGQ+03sV6BOiYPcMJ4eGC/LxFi9vG2IvOUF2eZM1s+Fqe+rAfosaKKo9eOziE/bc30pQB8FnfVDLd1BwYljUkbX9Be8LaVu1oetVWecOrHedZr2CDvnlAVPz0ueYOoBxr4RoMvHIes+qOrEMeMVcax3aZzDcm2N2LdgbcCepZwsYWUpoO+kfjeXwphNUmE3+P+3A3SNKoNh0s4zDnsdzc6rLkh1Ocjb0Kmnvxegi0FFlQfDBN9BfJoWf2a5K7PUxJqANVLrvkRe2XTw+A77qQM7Kzr0e+j3YP9KOTgbn7avLzwKmQeU/Im+BnJc8hKlX0n/JkCngvr1dLPA+Zre+VuEg7ZX0hHHvM8Is1FpX+BYF8Yeg7z7OHQ9el1ccWLYAeylKn8f4F5e8nD+izx7UWdt3ePtMKPtr8yHn5u620bKc7+k2i8JfNbxpe1aM/bVcObYkMN+UZxV0t8hQ4BGHlLtzzHOQ+X5o8Sf0Xn8wfxl7WH/XV3f3W3U0G2gkZ+pNmCYKmMoSUPQR5+Pc/nN2C81D9hngfY+o7o99qx/PcaytJeVfeA1trh8NBivodtBl/zcIe9wnJcr88tXdLrRGtoDGq/kQxyTdeV1HpR5dNfV0PNB0Yf187OIhb0clJY4yAVj6T34g/f5lj+9i0zbhbMo6AS6BuQtHW1fPZGy9SbNNbQmg+8X9cmshkwHOaVz53T7wn6HzKLxTG67tcl7LHA+IPi4sPusg91nLew+8f8Dut2nlOvrIdenIdfXQa6HbfHO5pItX0WoqfcmnENuI/2cLy/O+ZTuO6F037LvzDOpY2rojaA9j6h+YpiH7lDa0byAHLeV5Dkjhqnag59K+eNq6Pjja2jZL1Q5DBP5ev2K8TJs3tGqnO8WZJ9Ku69SXw21nVRDN6tyGObyPbB9bLdsBWuozkgbgbxow6howxaDWu4XvzvwuzROSyGzLx2wdLXFxkJDvn4wjS8X+tS9TNPJdG6ZexN0L2TiDGw/LI1e0dQPqng3I463zlKW30RLd7LyuU3tgLctFLdvcj3flTq0IfkVSmfRtxHzBpT8VaWdGSZ0jvdDu4cPd9xhawlSC8ZkFHq+kbNrqP3VNbRe5cMwvp6515N/j3fdoTu5oIbOAu3+lc5TOS5s0XEWPGdnOC/14Wr8iPOYHqwnRawnQrvbtTyMc2HorS19BO7QDdXQp0DLStoZKcIJ4eQaHvDAiWGCvwxYehBbduvDefd4iFZOBHGmkISdoV2HseEa+gXotpJ2Vo44hLiEeIR45BovwHA2f05O0skYnwtyCZSFc3O0/YIe26bRz7nBNP64KEiL8Dd4o3PtzIQoswkzxdwB92v2FZNBWj4MO/hc2DoPHbmshr4I2vZr3QbePBM1vxPt7hon4IHTNMxYFaRVon6zPrPg38rljlOjdGq2Mq6ZHV9UWwN9nnd4yJzc7obeVUOLQY/sVd+tMJ/fPYNNcuYwnOX29oDXrbB5nbZG9Rmzs+XW7iDkdXlw20drqAy6+VGtTznO+Qivf7bCOxz3Gzo/XkMbQWU9b1ecGDZzvoMfqqFbQOsntXwZLvPlmNEHu0nEZXl73tEo3FJD/wDtYmVNx4lhVWz6clxGV2Vuu6mGHgQt+o3Km2PY/7i2Td+NNXQpaLNKyzHvvcNS8L5hc6yaPF/IsAPxfJd5xoD6plDfEMrMf6CG3gHao8pgmLs=
*/