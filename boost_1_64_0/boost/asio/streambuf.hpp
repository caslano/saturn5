//
// streambuf.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STREAMBUF_HPP
#define BOOST_ASIO_STREAMBUF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/basic_streambuf.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of basic_streambuf.
typedef basic_streambuf<> streambuf;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_STREAMBUF_HPP

/* streambuf.hpp
Wp/S5sV4wsL2gDZIHMQweywjL8uWGmmI5Sf4i4zjGm6cHqfTMVZeCP52Sta8JybXJqmTW0bgb47x2qnr9KeWYMweTmN/DtFToGCttr5OLLWwtfug35E4yAVj6eV9EBD6dgX6dkUPuw/ShvNOyLdto1LHItPMQZoGpKmnFaMsDbtXVKgJ0z7QRK02dl1xYpjo1x7ZKuocNB8I052gzjotT47L+NCBPQ7sSdB6gUt7FxN7CjQocZALxtJ72qiJv+VcRj2MML0etLtSbtA+O+RhPE8pS6Bfmns0f8Fmf+A7myaF7+E4zhpB7Wl9HMZtvZ9rOE3DjFcn6NXQFZ45mabnD1s+ZIpSZlZzBT6Kw2H6UCRMV6q8GCb5RT34RRr8og78Av6GRiW/qGL/DLuEraByWh8nHPe25ZQ8zGst74eO7XFQtl7L3wX3SI/yob+pD9ONenqG8348KLYFM4RXXSOv8Pr1+U7MFT70pCK9mw7TDfN1X25dmNY8P0xTDfN835fLrEnRiuEjwJt6aAV45QrcA6jUlN0DyOA8eC583s7FHlFowKf7xO2dC91PmE5/E8bfHDXmOZbphm0Pzp8XcN+yTKfN29vLJ17hkjA9BtqvytSxqn4QqtoxyfnC/SlfFqZXgy5p1Mb3s4hX6sVlkFPCdAr39Wfq2CZhGzuM31zFNrbs8A9nrv1yHIEHmnqwsavD9BfQuqZ5Dl2biZ35Dsx5iYMUxnjpsO2LgudlvDAO3+X2ep7JmXdPpB9BOQfdx798d4XbFKavD9MC0H6tThzjY4jn0XltmJ4L6mtWeXCMr89lhEXeGcazNFp/ueKkY7O7T+PgTdXl+Fn9buK/1W0+O0fD9BLQYIvjmzmu9hWrYrB/ysD+qRU8o4GEBZSc3zPbsvSa/LMJ/LMR/BPvvexU/FPwL3++DPy0hT6/1TlCVfvyqvdhZ9gHeKbf4aOfrf19Ur0LJn0s5ez7hOVPhunoT4XRiGoMTseCtg9en/G92oe334x6/bPjdDZ8Y52BuvejXJz7l4W+x8NWTt6fXm3L+rqfZLAFP+GivmosSzs28J+Ru8P0SdDKNvXdHOPzPn9PmD4C2mKGyzkwK5w0bJb8QNTF1/pV+dvHOHY5y8ocnsA9ork4Q2ij+Zi78iYRn7+ZFahHrgVpm6kV8czU098eqVV2dB5zvup82HEQzvhm+7agI70Pf6B++a01V3z4I7D8SiYdfiWrnp0Ju6quOchnMizGOtbjYphOArV3aGt6LmVhedAiiYMYJu7pghcgL0IaYvnZ4yBm9794s8PeC7GxwMbtrN4wOhi/s5k/XmOC11fZMJW47rrv4TC9EbRtnsYTGK7rrvcA+wFoVyU+MUzkMZu8XXF+19bH3BLxOD8s/RRr0UOQT+dr5TG8mv/lvp+F6VLQPXoeDOd1UjbGUWljrHg79nzdpTBtAkU7K+udGL88bPo3bUO9HwD1dzq/ieNcFp+xPr9GmaCbeX0cYQewHuj2Fo+G6XegaJdWb1ecGMb7n/vim3mP5DYn+D4p/QfsE0C36nVjuD4u+S/npeZZZcuOiiXxoOQ1faT78IV+OYszyCfD9Jk/hSm4QH0/x5Q/fe293xVBWjFVZ/HJ7r+E6XpQdoF+RlBrYX8DbVZ5M4z53Wd5ibZwxY0L4nRBbx14D98hS9/oCc03+rPMO2f7i7dgNru9ByTDTZv5UWVJ77DPG4+h32D3G4rQnaDxhfOc9nkIJxaujx1P3nVDnG6ATu6qLHz+Dwgr+XzF16ttn1gXoZekI7RmUaU/GSb4/ZDJ73XbfeyD/hWmIdCIGU/q63Pm+ltn4e8BbVP5MkyMA5d8jFeF6VVoQ/jtd+rXsA4=
*/