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
GjRJoV4pd2LjYwJIkSgxSAvyGWvNJOt1jzUd+1t8s4h1wAl64otX/LaMo8+QEvO18TgOt3DmovyxSBAqzqQ3oPhIhWEPnHzArpI1FQ7UUtckpgRyCymlJA9FwzsO86xLHft1ht2HBtESp3FYoHnoLkAxwlj5dH/YDbtm+ixxp+QetLuPw4kavx2c2rn0U/RkmzWinZCIHSPOiTZ7nxbBvPGr6FcvGL1a9503PxIb5MbgtatSkf1Ni/Z3ieGdtLGiaTg8n5xtISDyE9X21F9DKG1W91rThcetDeZ8tnI7xIPzDxfxzOW9hLhWVsWTHNVHfF/6S9l3ZeI/g1Uno1OU054/sxV1fHOrZ+OaZ01Y1hmEYfLhwpHzY2jn3HfEMMRZ3WZLttGSCBLLJ344DrDUAzJEw66AgvH7wulz78mPJDaWf8lYjyQCxZ1a4WxVfgYR9FPMYbT6JkJDilpE/LkwECmICSAi8OmEFfsFqVEfpX1pQ3hSyOaQIS8+mqBjYjlS78Rh3TDdtuKQF90cJC+JMKVsNAOptMkiEJ74NpPRqqJ7neXvhtKwc1/Yl/LXpw2Hx7NAtrtEbLQjoXIS+Hk/5myf78qQti/P4ZROOdLib5Qep9S1mBeC98AExR7abAOcGvdOhF2RiTf4NVINrTI5gLwCjliXEsevx4DU34eZQJxWCU9JdDG3WOeADaUTPz4Hf5iD0MtCWH+bqtSC
*/