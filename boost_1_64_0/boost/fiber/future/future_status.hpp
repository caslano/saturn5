
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
QKTM2OVIXDDhbxP+0W3sn1jkSKVNWicd6y6Q8X9uwwB2RrIRGGgQYEvMtPqKdShxcwRpnF18sl6dr8ND9WfsS8H1J6l5zTpE0FNC179e0vPzqfZh+CnLn3xRX36sUt5k/6kkvEAY8pOOEmsUvUC2lUEbqYS1kDv+nYDJ8n0wqPD2MPtbg47SAKIuuKWchOe25jqUfT3+VEyNynVSKi5yPf8kBOoXYXJMbl1S1RZ1LSpHI1RXpHcT0SvfL7Kq72XBd9X+vUCLlnvYfNFAFo1olu2RrA/S+Mfh5yO8cDnvuLt8eAJtwEH7AyjWuq1EgQrj/64hoFp6er3bIqZ3JYff828dvZvGR0LvaA76p38TvXUjoTeVA90BL5LelSUR03vyrwTfEl4kvbXC0ivlPT+A+qzQv5qj+jvn94Di8unPZvaPgDx0Ao8nSZsEblb+mYa+1hgTfM0i8NptohLB+M+Cl8149Mqmdmw5fDGbT63NvnnYg9uqbfIIqUbLcEcz4fiWcGg2xDFHxWElHHvERn/hXHjEJx2uoHll1H0MO0K6vcMO1ELcZwj3ApsJfasfYQNDDgETYjJvaTD/TPC/EHwGg5+two8meFZ5mvi6xM2iIvHmZW/o/eD3zhAI3rDkNzlFRac/a58joV/0k66/JL8Zsf7lcPiPz+r6y/yxkfSXThz08bOkb0feiKC/WDhQbz29OVsjprf4WW4fftLR+/GdkdA7m4O+zeltHwm93mdN+nfxGxHT63zWpH+3vLPC/t3yh5D+veMZtX/f+3oE9C98xoR+S+T0e58xof+OOyqkf+mPIfTHGOh/ZUsE9B9YzfXljE5f3K9HTP9CDl/rjE5fns+ORF9u4qBv/0D02iKhN3m1Cb8XbomY3sNPm/D7x9sr5PePp0P4/cjTKr//uJljqTD+ZOCDCJzt38ko2G3cNzVnPccWQTzL8MVyfO3M8XWuLL4NTxG+f50xxfflq5XEN4bje+d7U3yLK4uvIcc34rQpvl4CXwT++b4n+fk+GfymVIiAJs+CtMLaN0On0lIq1C8V32QTfK0JXxziG7ec44twvoIhvYyQat1/Mm3voFcib++nq0Lpa5rH6DvxJ6Cv4+bKtbfABN/bkxi+FYhvyrIqtLczIdUc5u0dsy7y9vpXhtK3YTajz/8c0NdjU+Xau9wE3xjCtxzxLVhahfb2IqTam9+atnfi2kr2j9NPlKsvl62NnH9rnght784/sfZ2HA3tjS6qHP+GmOCbSPi+GAX4MpZUDl8Cb2oPxjr9pOYfXlYwhev/jxP8d98Y4Y+9FAl8AYd/65QR/tmI4Pty+PUnjfC3RwSfwOEHhtD/h4jg9z0mzzejK9BAEL3mgiCOvqaAh22/CXwswk94NCL4vgSvjTod0v4XI6E/waT+fYuh/haR0b9vRSh8AcK/ujgi+IIV4eh/9oVI6O9rUv967Fij10dUf4IJvA/hTz0SEfy+5bz/fB2i/2siob+Aw78f2v6I4PsuD6V/0wJs/6sR0Z9gAn/fAmz/w2Hg5VTjgWW6qcYC9mlwNCTJeX6234lORKUlnPb4z0qhdyGFt3edSoDwNh/D28UyvJ0zh4XemECIcNLqO5y2l+vsz/yFfzwPu6uclMyWhljo/DDhvoDhnqHibsVw+7v5OxNNcYwmgltCcB9/i3AzVbhvYYwSk2O/5pp3iP+zlJhKaxNpsMdgM5ADRr7ZNwl8Yvu2ceoCRj3IfYQVqn32ZIJF+7gB8S2t4tlvRZ6WpeYHLmPt1p9i+aEpx0YqB5DiWYI0xyJW95bepZKXgqztRKzd8A2ydj6ydqlk7aPg3hGo6zmScVrVGaybP0pdItvjCTn7xM0b5jo=
*/