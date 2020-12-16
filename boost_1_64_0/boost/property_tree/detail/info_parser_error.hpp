// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    class info_parser_error: public file_parser_error
    {
    public:
        info_parser_error(const std::string &message,
                          const std::string &filename,
                          unsigned long line) :
            file_parser_error(message, filename, line)
        {
        }
    };

} } }

#endif

/* info_parser_error.hpp
ydmadGIeV+kwIaz/TdbN44R4RIk2m11jIE+DCdPPOedX9XdKu8bBpvXk9nL6qL5pMiJoGAcxMhRpMyb8MfVn9X32IW/9CJnDR6fvD7WvqF3Sjr30nF57zHcqdJly4jU1+nJ9MWEt5znKz1TfV6i/nIJX6vdJauF95oI12yIkOKbN7rPsQ8l+DYYEh+rB0e2dy9oaoak9InUH15Q+C1Zd//U7uvbXtkaIFffViMAxcY4ouu8OTt8/n55He8Cc7X/ahzRV90KXBbVzOZ/7dff0HmXbsf24e9fxY3MztOE9/Vvs6+vdy5blR5ziA+zDmBX7b7JHhgINZqw80Ncgztm9ucdc9hb6IEGWMi3GhCL2Jcro/z/TPv67903/0KTBkOD/34uI/v97ETlGhP7pdZFN0hQJ/ctbINIUqP//+wqr/7Yfe6Ro0v//9xJWAl8DESHGAQsue47/fc8g+f/vFdTpE5PnXFw7p3WDBBlKNBmy5LLncjwxUuSo/v97AmPOOk8Qsh8b7JBKG6OYo0aXKeFzu79su4a4TYMhwXnUkPAPvYdiSOhH9mOHy37RezuK7/I+5N1qyoBQ1b7//5m5tf//zFyMNEUa9Flw5n3eExLniBJtZpx5v/P//2fhTqjSY8aZmj5JcEyZ9v9/1u2KH5Afh///+bYWY8If9H0u9jimSp8lV/yQOcAB+f//LNuYlf///Noex1TpMefMh/VDijwb1tUMNVZeZtzU//8z1ysvVwOuc311oKTdfOr/fg+/eTXnuLo5xeo17EOSMmPOWp93yVNnSOj0vTnD0/fn1zHG//9++tr/fx+9TFg/beY3ct63uO6bav6IcwdNcd/faz7QPvQ1SvaR5w56Dz53MME3hIIzbLJLihw1OoxYsPaQcwcbDxGf6v1/+txB+Gk+PyStPWRDu/Hscwf7TzBWGvrKPV2fD3CO1LmDVe2sfQZkn++cDzx3ENV/kmtw2Ufb74nnDq74ZM87X/kxnn+i9pO032qu+8zyOs6TePy5fV2qrwc6Fznnb59eF/O2nPTZ5lNtc77iUzxP8GznIcbQtshT7EOGOeue2yJFljIt5qycjkveMQ45eL7+XmjfZ8uB4Nh2Gs9ybo7ke5JSf5+rloznkO1Tz7ffoa9jSXMmZZ6KrdO2baHsuYPp31x7j1ee7GtD4hxToU/wFM///X+/E7Uq7pGhTOvx5gJbKfblI46pPVJNWfPcWX1UydH4h3VDnL/Ea4PYP318fznc0/ogZq5krlvX+0uvhbYtX2G+2JYWryOPjHV7njNfWH2C+UuUQ4/3X+58jF+mJvu+3tS+Dld8qWtycu6gIMZfcm7vTb1X+Js1wPlHHk9eqt+M1xOx6XH0RGRKmJDzrdN8qXqK6RPzTzup3fj/3ziasXJO6xUV2oz+/3eNCucwpkf5+lusn47lqt73abcDx4jXYCnfyOl4X6yPc7q3XI8TcRqo9Tncey8+t3XY2iG//FKuhF/h/bRaxZj93Tp7JV/Hv9I6/mJjVcfxi+yrr6RYPYc58RVfB39VDb/sa/yOOfB5n5+IM7Emrtu++UVfU3tc+JrPR7giRc+PP+E5UoSdo9n12f8XfDbxLZ9Nkfqm89xFjn93rr/ZJg7EjRXz8gLmsXhEiKHHEfoR84PSLd0vJLUPL+jakrqzbXc1T/yNzmOxfDfzx/nD4s6drBHak7s7p8dh7fhdPe+YtmOn19Uf7Tu4T8iyGnXuO1pX7nPuYMbkvubl3rmDyr0d2zKOts+cbq9u95Xfxc/t+3Ku8xXOHXSv6PHV1HFhnN9UI2NdE3fEMz92TTmg821j/Y76ikM1LDFU05OfuJdajmX7M2pI6zSqcfAln5c=
*/