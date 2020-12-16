/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   stream.hpp
 * \author Andrey Semashev
 * \date   24.07.2012
 *
 * The header contains implementation of a stream placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Stream placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 2 >::type stream_type;

/*!
 * Stream placeholder in formatter template expressions.
 */
const stream_type stream = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_)
#include <boost/log/detail/attr_output_impl.hpp>
#endif

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

/* stream.hpp
qPELul+d1NmZk+Tm4QvkYamkf4jWCa1znjH4MRLGp77JfCUP5sM1qdrejJ+qmkqPn6Xi5xv+Oc4gkw975dnVSZPIi+j8xI05L3YyTHpWOD00zEYp6ydTfs4v8Z/h/54zK/kW5+/JpzhjU84z5XOVxCtL6uhWb59i4mnskJi6mtPOW8Z8G5e4nyTteBthuNwFQ2HUaiChsnlV4v0Ub6Wvm7rwiZR7d99q53bqpDf/y/xu/q+mvrvxfMYTT0+9qvfqAi+QOH3Pf5fzQZKtzvyAd+FA3H0zP/AOvAdxWVdKSIjYBuDe24XUKs6Xq6yI4CXIpR4/D+JnA7xNbZZcVirnRlaE/CIyNxPpkRce1uUIz/eGafTwxzuhw/PCPk3mxs7JHQ6RP4XSY6d0aJR80JcLRzbXeiXLNXaWxGOvQvxZ3+lck37b7csLja2GDlL2lEmUDRt9/5uBZHpwnKHjybLQeLJhGcPfhjjHkmVxjiXLjvJY8mRNzyFNz3ANZBhyM/80Z0h6xILbiorq5ay2LePXPOdU1C2UuPbOF1140yZ2i/vjnc52O8+El8BcLCPcjsPDuUgce22yNe3EjXRWxJpzmbTvLjS/NyDHqchNpL0sU9LOysaciuraRRXu9KCqbvF8J861sYB/n3X9Z6TcO9FexpmJlXEr6zhmvrBVDTocq4EM0HQ2htJ5Sbzrfo0tpO1GudfdbufxKKftFE3b/o5mvdTwVtK2NZC26kWBXVznjZk4/XStwmPPmuS1/1vNSpE9rYRh6uwtYjtiQU0MezK4jazfbkuxz43Ubdi6Qux86W6xpStxNvWbuHFtgbev0zpPHCL6r326IDRF7SRP1rqwI5Bf9fMrauZUXrx8WUNVfPVhRwv14QW59xlrfqm/qLVOtzhfk3unRc/p4lhLanE9s5PqvCHuhRma9vKsUNol6XG2BfzFTPs4uTfFjN3WyXmyNS80HOu67zS5NzbaJt5h5kWwT9jeTe2/ci8L9oa3kRebNS8a3C8CtZdF5oNZ4y9o77p72pfGLGaWMw47Cj6fdX1B05Zn8ih6TLY8W+yvWPNG/Us8eFfxF5+YPOsDN+S694da25nxa569oG7ZUtqa+m2W+3v8tyad5KT5q53PM8N60H+y1Z7h5qgy4ruUxj8rh3toTvbk7Xcea/jfYiSx09QFSl3yKperY8XWcuB8q/8S3zrn4aR0Ez/CrA3Of/PgGRJuT18uc8h6LE7InMaElyfh7feEd5XvtojwaiS8HhreKsnnBT53LtKFGnEeO1+/i/b/OF97J0/DukbcnEpIXwv/zQMNY5rcHxBWV3voGLifxOPZpGlOB8K9wRntS3LSk9Y6dyS1xz9uTNxTvOs9dfxjwi+XNKdyPlbGgtsk3wuTvXO+En3eYHH7GV8V8/33mH928TEH9T6H3EhxvpIU8lvl9NA1mGslHR/7jsPPaNK/3JfsbESeRsLm45452SwJcxL1+gxngIbzK4nfX/0ZXK2kr3vEOdPZQqj7KIck/0PO+/5kM6e5WOI7z3cSb6/PkcbvIa8xw8vyneWmV8ajz0l4aZ65wXy3DCXNsnaZLc9zMmkv48jjlx3KTuvVSrl3JrXqATOeZMQufpPc+i7xn815unMcUo5Q12RP88dy73gnHZ9dkDzxQ62V67cwEl8qc2q/uRZWb6m4oXyaEogjLn4n6frIU0dD5U4z5uij/dzPJd3ZybnUjSH+FGc2cj2yBfkrEvJXXeXtOw5k6doD95c7al+pfvHlVZ52dJ7k+15yKoP9xPc4Y3nv5uj8aSPi2mr8U6GZr8SimQfxt/THBda5DAnWucrPc1ueqxSZ/jn6t1qyIP0d1+nv9FqucSs=
*/