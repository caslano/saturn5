/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_COMPARISON_HPP
#define BOOST_PHOENIX_OPERATOR_COMPARISON_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_BINARY_OPERATORS(
        (equal_to)
        (not_equal_to)
        (less_equal)
        (greater_equal)
        (less)
        (greater)
    )
    using proto::exprns_::operator==;
    using proto::exprns_::operator!=;
    using proto::exprns_::operator<=;
    using proto::exprns_::operator>=;
    using proto::exprns_::operator<;
    using proto::exprns_::operator>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* comparison.hpp
rV03/p5aS4x6Sd+xOZbLRGcrOtTZDBpuOX3TRTt9p47WUR4k+S+5IE2fw8fS0buUa5GM3RFK1wfQNtpneft9gkbRTZrN39GYuQkgMQw7XmA4ZW1fGVH+H/po/+5psPzOAPqCkjgepL4XtmJkl9ZQ4gYNRgTGQ0QtLhzvjX+hgRNRCyYykNhIEtUdgKItfY9/0XCHjhv9G3JWHAtvmxpkORcRqXyUz8X59Cyl7gDRh0i5aqAURMOhoko+N5xlbd2W+7CL97MKTIcC0bMQn0UOzMyitm7rioVjmJV5GGYuJIfyh0KvZOKampmecO/4Yl4unjZeYu+5WJWVvegUl97DG6tbYVt9jP3KxoiO/Zl/FcTOQN/mlCHjNzaWJk5M0Y/S9QFaKrrzda5oEYDvs/ngog8YjeXtTDzrHhaIiD0xSXM19nfZsJ+mgB6OQLHnCIIHerELIlzUk5CedXm9oQEKuU4DMkcHQhoo5hT4zr8ZeDmV6MsD25jF70kPZZrZQE2A4EU9Zk0bPTVWb2ZGrvlhIbo+9oG2Wo49Gufr7YyIxvknf7bpiWAAzZLtIiEJ13Q4anQnrujbid9TZU80kPxvBv+Wq9W20jFHV3uXrtbjtKodpoq6oajZCj9EZKbru9diT6TQu69xoRfxJzm2J45nGxRn+9mrxcJWBDSNS52o3eN8EZ2vKkW+pTrfOTrfoejv3gzRjHKz+3zzIf5BOY+VnPOPIqnL/vTbLU1YrZuQLk0YpZrghZ84vjiAZq5UgH24mCtgodmviID7sAKqcO1rUsFRWMFTuoIfSwXPt3IFeBRnCRkXIYcEfVyQTQ5NBfrA8v/QRCILNywTRdoIacfGvkN/dqvS86hhjp5A027aozLtRsn4b9Hjf6vDNv5Sns8QhwDrhULt6rgoru5vtE6U7wBL9V8nzPoafrQ+qWwpnoe7mG+b85CQlpH6fLv9wcTzbdXDfc+3FyTydJco+69XeX7mGUo0oRxDjbWbqGG0q+xrV4i9zVPk6jyf9swYXvXN0zkrdIYqcxxRWE/AsqmoNG8OU5oc9UbJOXm+xaoJZktfYczIdbGGb54NUHkrxlsrpPv3L5bSuiYVZM98ZKt1YIvRgU0c0fuXJBzm572SbGHTmmhh06qOaUv7Yrp9K2P6LuRAYElY8BC9f5/sWnpElqcckZsUtCXS3THmbyML2xNT4pGFbRzB4UZYvRX6TXh9UZVNjn98ZSqczC20OQ4lRnmVblO6YDGAsYju21eocEfEEiq83vBVCxX24sey/6m3ySfiKZRIN4C8iB3b4xRY4bamwI+4u958iQftWRduva28Upfer1clMS5PPahWZSuuym6aA7e77XNAwC1jcBTjk2ZP7YP6cIcutfWRe4yuYiirYzo4/Zx7ZbbpmlbqmhbbajpE1dRNdikd6NgaYGPgIJhXLX+yGZDSau0+FMs+qDugv8D5yxaG8yDB2eoqMyeUdVjNfDRl5ferQldyHA6+PHjGM6pJ0NNr+vZ0SJWptkQGna/hIU7U0LFrJQgPCeR6HOSrCZmZ+UW0CvKcSIl+CdlY6OT/o0buWhtyXq6IzGHNo+EHgHDOG+N/2W0T7+jx30yZoblkQH+P3YECtCqy/CZaqXQ3bsXTyiwljrNM7oGeQ4TYrc7PQR8dGM+Ahc379xGWxbGBSHZqnN+34TyD0eg8xMlHYoJ84zX2qEQ1yZD+riF9bIM0QEFqS/JUVWnewASY/bQ7rjkNuqG4uj04BX55QgOhivTgcfA3LTge/rqD46zqyE/pZ7q6+U6rujtfZHJzqa3XeiJox9PXEUWEBsZNJq6/fomeE6kiZtMpesgjS26xr+82omsHwiYiLM4=
*/