// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    

#define BOOST_IOSTREAMS_PUSH_PARAMS() \
    , std::streamsize buffer_size = -1 , std::streamsize pback_size = -1 \
    /**/

#define BOOST_IOSTREAMS_PUSH_ARGS() , buffer_size, pback_size     

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED

/* push_params.hpp
B9+DL8BD8EVoBXg8AuQbmAQHwBZwEmwFF8O28HrYAd4CO8I7YAZ8AHaGD8Iu8AnYFe6B3eGLMAsegL3h+7AP/BRmw2/gfsLRhXyJ3+p5HQTVvhf+8HoGtKkl356NkG7q9yvZ/+c5OAw+D8fBfXASfAGeCV+E0+HLcBb8DVwu+6CVw3x4Dfwz5zfAN2CVXP+RXH8E1ljYE74NX4Pvwjfge/BN+D58C/4dvg//ARHrA3gYHoLfwH/CAJH6F2wHP4Rp8BPYBR6GfeCn8Dj4GTwefg5Pg0fgeHgUToFfwfNhM18oXzaH18vxXbAVfBy2gc/CDvDPMA2+DzvCQ9APP4WdYHM/6QvbwM6wE+wCh8KucDjsBs+APWARzIRXwSx4D+wLfwT7wZ0wG+6G/WE1HARfhzmwFg6Dn8PhsH0gdL4nPAHmwJFwBBwFT4Ynw0lwDJwOT4PlMBeug6fDW+FYWAXHwW1wPNwDJ8BqOAn+Hk6Br8EzYQ2cBt+D+fBTOBV+Lue/kvPJwZDd+sAZcCCcCY+HXCcfq3jIXFs1p1nl494Iaax+y8nvPlgOW8KVsA9cBbPhvbA/vBQOhZfBifByOFmuT4VXwfNhBbwYroHl8Dp4Fbwe3gQ3wlvhJvgAvAfuFHcegrfBfXAzrJHr78n19+Ed8EO4BR6Bd8Kj8HtQ7YsDySvqPvIE90k9C6p6FjxZzp8Cr4GzRH+OnJf9pWT+KnkF2e7aX+pUqWefBvvBsTAbng4HqmPZtyk8NxLeJ+7ofZtkf5oAnA7TYR7MgmfDIfAceCI8D06G8+AiOANeDmfBCjgfroVz4Xo5vg6eC7fJcbj9UCPhyTG0H46TeOVI+Ffr+XHkVdFPRopFPx09H+wKU2A32BF2hxkwG3aGPaDaawb2hr3EXr3hKNgXjoX94ES5T/Zl48a6fdm2u/ZlGyrtl+NgR5gDO8MTYBc4HJ4Ej4enyvkxcAQ8XY61XTK97TJQ7DLIaZdeIf3LDXaZI3aZBzvA8yXeF8ABcAkcBAtgLiyEF8jxcnghLBe9S2ARvEyOw/5Xx/B/ovg/WfyfIv6fKf6fLf5PFf9nKP85Fv/zlf/oif8z4WXqWNqVPhn7L/MrtsPhyFYpV+7nORoGH4DHw53wZPgQHAMfhlPgz+F0+ChcAR+Dl8PdsAI+CW+Dv4C74LPwGfgc/D38NXwX7odfwt/DVnb9CGbB9oS3P+wAc+EfOT8DvgHnwb/AlfBtWAnfhXfC9+Dd8H1pv/8d3g8/gB3sehI8EX4Kp8LP4Qx4BC6F/4bF8At4MTwKr4PfwLuhn/D8EAbgThiEu2BL+AxsBZ+HreGbMBn+DbaB78N/2vUX+C/ox/4fwuawHdfbw+c57g73SXk2So+L5llEtrv23+0k++V1gckq33M/JI/o/Xcr5P4aud+5/+7qIOGAl8NUeIU871dKvvse7AM3wOPh9fBUeAPMk/Pz4dVwFVwDr4Vr4U3wGrhZ3Lkd3gjvghvhg3ATfBTeDNW+avC38Bb4B7nvj/BO+KYcS/ksYzTJA4byeaE/FI8L4Ti4BKp98mAxvAheDK+UcngFvAOWwHvhxfA+WCbtjHJYDVfCX8FL4T65X9JJxgXSJjOk0wgph0bCdnAU7AZPkvjkhsfKgVMN761zqRfIuibqvrkwE54PR8P58GN4UI/fUuPZdL/eGwg/tZ9dG3gzbAdvhWp9JNgL3g77wu/CgfAXcDDcIuXwVjgX3g0vhd+HV8F74PfhffBReD98QsUjlI4/hq/Dn0q+/JnUY3fC9vARqNpT8FT4BJwIn4RT4B6prz4NF8JfiDsHwuONYFeJbwbyUrg8l/dMAUyHC+X5uB72hEUSv8VwhJw=
*/