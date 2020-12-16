// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_INITIALIZERS_THROW_ON_ERROR_HPP
#define BOOST_PROCESS_DETAIL_INITIALIZERS_THROW_ON_ERROR_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail {

struct throw_on_error_ : ::boost::process::detail::handler
{
    template <class Executor>
    void on_error(Executor& exec, const std::error_code & ec) const
    {
        throw process_error(ec, "process creation failed");
    }

    const throw_on_error_ &operator()() const {return *this;}
};

}

constexpr boost::process::detail::throw_on_error_ throw_on_error;

}}

#endif

/* throw_on_error.hpp
qblmT8o72/ks6CesZ+vWWKmLstMmjjbbG9Pk/l8Z5wxzmFtr2Y817fuLOC4o/xNhC/G/udPZvZZ989kOPCITNcczzNF3fm7t++rMFZ0f0e/O+K7H6XxzK96qrUyxumn4jdZeXrfL/VDdad+bVhKfpma78hbR3UarJcycg1dDdPr4vwuVniHrjempRVjzJsXdOH4tE3d6yb2Fku+TzDbUQLFL21HF8UHR7W6b0yypYIbxcbk/ytwbbIFcn9SKIXtICyWsTa32mvGuVX69L7olCbtL6piMotR9pFEREs4bkuDVOZbd43WHe/Ucb5gLP6lTgPZUNEbVM/HKXkeuw/z2itTFhlUfrVB6pZXedNP9vA+94aFevZY47eh2rLLzmOl2Xn6wu0lce7h+h+twdCJUnRbp++MzvH+vXqGMI5NnRJ55ryGzyr3Io836QZVnJfc51BE87+a33vlYTf46YnRMB8w1PO/zJf/zpGMljaIqDRWHZ97pGceu/Tx+fpkOOD7Tou/8jDk9w5a+9c3AidRZEzKynZ5hSz/CfPas+dHL5V49rYKc5z1I4uIl0YpiosT88Xn+TvknZ3Cb7wAr/pKHwXkSnIe2+NjP61/nC3jaHuPCtMO0IK+OBfIqY1zagAapTdLa9O6aNjFrZLbE9z1J/ymO+YQ9q10Yg57M/3XOI7vuTp+keYZz/qBry59joktwmH3oWMcGuT0kXuoHDpG36paTcr+x/Xtvkmar73+T+5WN/JN3WDEfbmOui7k0/8Ls+Wf7TnlP8mqK+eyRJlxLmpjvdOKOjLjb8uyYyKw42vMsIz44zzDkWepT9jxjI85eVp4dKjzPsHf5eZb61OXnWepTV5Zn6P9unjV76vfzrNtTznkWc4V5duifmGfGnqO+xEvz7Cz6eQXyzMqvA7+TX3lXkF95V5BfeVeYX3l/kF93/UF+PVxIfsVeYX4d+KfmV+AdNj8p4NHTmAjMk5hWPGP7jPySrKLZmpVrxB+5RN9sg3wsuhXYHdLlmI/7riAf911BPu4rPB/N9l70036NDPqXwh3zFjeCvxGt9RpiN52cDZPwJCcjJOzEXtySfWSNNp3yW7OtG6kq9rtpZXBdZFyliCxVC0eaRNsoMZE8KyHnz9OeairNqSo0pxzbUkr/W/RX+vWL9LykjWaUsTgC4LN9Gwa3o7yFvIeHSN+N5O8/XM7QlTQi3ZBLukkJMdYh7i6pyV/5AOS93ob45Uka5Y1gJU527ghN8jdL6om0PrkTMoeNdW47Yc8qDzcG9NvLbHl7GbP0rPJn5n1a78yJN42x94c+Krohmj/tF/KsjCLMlf1pX85qHxf3BdJenmPHvxRJ43iVxlnyHKu42No7N4pchVl9ey4W//kuDPrWPJysztTGRGJmYkojWxdIu5GZ2f78Sksfjtwou/LcOqcd9tRzYO6Tmi56F/mzno0ccx3jYdHvgL6x7m24Wd/tV8+NURbjSZ8EzFYsJmKkLF5Gm5Awm2WROlDCkqOJLFCOVFpsTQlYfkl9d2+A/bHbcoWkxdhhozP9jYTg9re1vmsleswyrq2Vckob3Ln8+suumxNitN+t/bSzxK+RWhylvbfmcarXcOPK2uii7/xd7vg9bek7fzMk2vQTlb6930FT31TG97dH4nRac9pLOwEOF/vz9TtxfQsm1nDH/h2m9qKOELe+Iycqa5NJJVW/mrp8CZjf1c1F93l1TdmV60SbHcKJDfu+3m9JWKro5ejT7I9xWrc6XdzJJHeuYaVntKoLCJXIXQH31RpDdv5lGDsQJumjEfe7ULdzza/n5PpbrSklaTzmMa22vR9gbI7tPTpadKvz3Y8fys+HRRYq3/fNeZ4=
*/