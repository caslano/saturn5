// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_TRAITS_ENV_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ENV_HPP_


#include <boost/process/detail/traits/decl.hpp>


namespace boost { namespace process {

template<typename Char>
class basic_environment;

template<typename Char>
class basic_native_environment;

namespace detail {

template<typename Char>
struct env_tag {};




template<typename Char> struct env_set;
template<typename Char> struct env_append;

template<typename Char> struct env_reset;
template<typename Char> struct env_init;


template<typename Char> struct initializer_tag<env_set<Char>>    { typedef env_tag<Char> type; };
template<typename Char> struct initializer_tag<env_append<Char>> { typedef env_tag<Char> type; };

template<typename Char> struct initializer_tag<env_reset<Char>> { typedef env_tag<Char> type;};
template<typename Char> struct initializer_tag<env_init <Char>> { typedef env_tag<Char> type;};

template<typename Char>  struct initializer_tag<::boost::process::basic_environment<Char>>           { typedef env_tag<Char> type; };
template<typename Char>  struct initializer_tag<::boost::process::basic_native_environment<Char>> { typedef env_tag<Char> type; };

template<> struct initializer_builder<env_tag<char>>;
template<> struct initializer_builder<env_tag<wchar_t>>;

}


}}

#endif /* INCLUDE_BOOST_PROCESS_DETAIL_ENV_HPP_ */

/* env.hpp
/9BB0r3vXu6sY9jpqONhdUnj8ax2hxkBOm7RWZWV+Jjf7P++n/jGUsY3bjv/d70mgKSJ9Kx3OPlWqMsl+mndNzdre4Cukm6X20ZnrtdHuEXO4+NGZVp0OaEvIYcw3whT60nY69WPIm8j5X/stvOLP16EX3wFvy5drpFHnF6/+M6MoorO8ap9/rG1HOlljlaMwKL842+Ta6YKJVTSYyZbZG5nbeM9h3/MDJV+6U0avw6dPk2kKMv5PyX5PnOMCDieVf9/VOqVXWQ9P8BW6io7/3ubv19UJCg//KL97gna1/69f7F3HoBRVGkAnm3ZdNKpCb2j9KoCIQQBQzF0BWJIQi8hhKaCIAgoeCigNKWIgqAn2FFAmiIWFFARBRU8xXaHqFhQ1Pv237dvJsusp3dez+Lzy/zvf3XevCnvn3+S5V17WTs/qtaqP1c6fzH1Ze36LbV+/bZa/z5PmmPytz+Pn9j+mWAkybZeT5f1bZt37Tv/inXu49LXyv/1kQv9Xw/QMvN9+e6mTK9Bd9Qy8335Nkds3pdHFrxuXhtZ8Lp5JWTB6+bxR2zel3/D5n15U6bbsd+U6To/jSx43fwOZNZ188eOlFw3X/hWyXXzpUf+vnVztRZuu0b+8m98P35XiPfjzwa9H59iXWc3jyl5b/7FN3+f9+b/09bXQ63XHp3jkz927qEPbu13On5Sk9gfR55t997/37r777WObm+HEXp93d4+I9S6+795fd2lrpXVNfxRONoX1GPndmp9uz2Mg5fDcrA7nAV7wEWwJ7wPDoTPwcHwRXgNfA3mwqMwD34HC+CPcJh6f344jIIjYWU4ClaFY2A9OBY2gIWwORwPW8JJsC2cAtvDa2FneB3sCqfBbLX+3Vutew+EM+FgOAsOC3qfvkitfxfDm+FC2AOuUuvf6+BCuAH2gTthX/gs7A8PwQHwDXgVfBsugp/AxfCcrIP717mXwnpwGWwIV8IOcLVa314D89X6901q3ftWeB9cDNfDVXAjXK/Wt5+GW+Ae+Ch8AT6u1refgCfgk/A03Aq/gtvh9/AZWEa9L18B7oI14G7YBD4LW8PnYDrcBzvB/bAvfAEOgS/CQvgKnAlfgrfCV+EieBAuh4fgBvgG3KfW0w+r9fM34VvwJPwanoXfwHPwGDTU+/OR8B0YD9+F5eB7sA48AS+GJ2EjtY7eUa2jd4J/hr3hGThIrasPg1/CIvgdvBaegzfAH+BMuAneDh+Aq+HP8D61nv6AG8DHoFOto7vg29ANP4QeePRXrGNn7XYF1rBL16//R9avS9euf93adem69X/nuvXw3aVr1qW/0l/pr/RX+iv9lf5Kf/+s3z/3/f/hv+v3/zvb2AAgC7YBQBZsA4DM1gYAub0NAPJgGwBkNjYAyIJtALSuN+ib/8isPv21LCJofb9zkA+AWCWL9ucna+xs266xv2t59z//b7z7P9z36n/pu///knf/myi7hzPSMPaDFz3Fb4mZEdgncsTY2j7Y2TSQztamQa/nv/WKT+a02xektX1/X68/ph72xf/Al+f76m+dP3nQJ/vY1ccxgG9rlTe+c4wwJjrf0PYByyTPnl67d/6fk7jq3nzPUSPUe/lfic7XYdMcdznruefrtfIp8oy5tp1dhNgO7CYd8V4buwixmzgg8RW9Qb4G9PrrOemnFjJaAv4HfG3oHOQD4DvJ5zjjbl9IHwAHJa1+f9+optZcH5a0Lb1NnNONb5wFjsfcacZn7kRjmOc2R7XAOqz070R3eZ5w/4k+vspZ3pjjHGFEul6RtudWkCN7uGGp+9eyn2JlvFdQtgK3SVn9vQUepzGeEO+12gwEXEwY+tv4O0S/vtfGrkPbXmw=
*/