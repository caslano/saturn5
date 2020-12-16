/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP
#define PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    template <typename F>
    inline typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

    template <typename F, typename... A>
    inline typename detail::expression::function_eval<F, A...>::type const
    bind(F f, A const&... a)
    {
        return detail::expression::function_eval<F, A...>::make(f, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function_object.hpp
RGNXUbiDy7eQ3uLwQGbdzVymiX+bfF4S1HGxlsr4rY1P3Zq2hmmmZnUZr3NoqFHr3vc6QafWN3luEDRqdUPrFbSgtfkO6+1U7gztBKnKQ8lvaDVV1XG5P3In4TQVjg9Bd+Lx7ieGl6mZ/dOTGI7EnbFDcy4GA97esdEhNeWIen6di8M8M3GDso7GzfztBb7v2SKNT/r7e++k734N8ph+dI6+B8Zfd09vc+OW7sQ+TX+7Re/p7t3a7Onp5Xtfe01+bV/u5+znseRQ0CfC+5qiDo+DP93PsHH9jPkAMHRHw8Fwm52c47zowYmJwQ7mPjU0ijr8mIMbbbdnWtNBw5o6YblNa6AlTF6fYh7BRSfy527PwMLBKZOZx4I653OmYC5pavrZgI6DkTxZimPQIB5n05Se5OAHupz3zB4V9L9Gpt9r4hjMK2Xt9wQ/b+pYYljOM6Z+bbq2GY7iZ2wGNSWOTBvaIUnDVAua4Xv3C/r+CV0UoRso5m7eNn0fwwwtJq3HNFyvYLq5q3TR0PldFPzBdDSFtmI+315s+Ogn/OS9fsRtZrsWqQMDjvuNt4zp6FGQndLdzXwnjWZbYMVfjP0bFBw0847udxcLuc06Hzo0PnjAXGHje2Ldn2Tb0n1cScvY9RnGSBlPcdrQuJkQNJKxqfNMClpriAY3GBiqJ2nMrI2ZAFnjTN3PfdRgqIf4EMNjz1cNnR6aIUCCdTP5OYHR43Cb62fP56Po5IOmy/oJVw5IjBu3NLy2TKyB4dh9B6T114WTGntkOmo/JBq75yXxexOE5jp5h8HK9wPGh+WbfaetMlPm5o2dtomHcKPmRcUO59scC2yhlJZ1xUsdWcMl4/ufAjvdAjyyZKz75118JHe+OzV1qy4nyR9GN6G5Ywchv7mXeZOpmx49EWAJijdlRoxOdb8/jIHajpgx4T0O3U/N9Dm7jZBarSJ5PTr7Fat9qGFIKeV7QWcicSznhx29DWYbk8+pW+z0GODI4wEjpchnbnaJHHPwquIkLpsnxswc/JYl7jjs87Luu701GkMitYkXmHHd0QufVCoRj+WzQu5BjBkGwhiPxzQoy+QQjpwNTGNOvc9ppylmBLkpzgJjqBKnWqazsK176u2yTUmPYTK3g5dHuXymLmm/gjFjGzQvLxEzjpiHAGi/iOqjP+GOD9EpoOemLz05ER5/5smje2citl+7eZg3VqfNHIvxh+fMIzv8OuArRMG+PvePnQ49yNLo9Wy/S0cRxJ5s0ezJoikQBljve554m9yT9ZK1fLlcKGdTSexz0mbs5Mz0UCtuYzYJHnXidcd7Ja9MspROp1KVorfQ/d2x0b3be5PQM+J3Mi/4bcqWcM5WLhSTOGT1N94Mbvn7JC5Xz+dTaWwvZzXuUYQbkPw2l+vpfK1QrydzGYNMbF+VWH6fV66EPfpuhcUUrN+JxfdD+L7yuPreGsICAZtWbT2Z+PRXgb6a6DRnEhn2GeivBr3LpwdWLU2s/v2/w6AtTXgNuEIo45X8SXGqrA6OYTz257I+j9cCt9bn4Xc/Ht+If1HwN0T8R5XrCOgep4UCBt/fgO/HbJ5+Xkfx/VYL779fg7yuvM+ma/QenLsFlzD044IuEUSnPTh3Cy44x7xpZXBGvnOTb8sbf5yrpZ9TfUe1Sv4eHwvOPUteanh4GgNbfnB8dOygfW/q0+Is12tUS5mnNuuNbC7k73cWOKLDc9TDWXCQx3eD9OQW1uzfkR7oyzn3Is75mMDmbwCXe7J9z+OXPj0oU6nWyO6wrxP5ct4RYKj4WJlR6d27NHeKvPohZRXZ4Z+WD+BcgOnfVYcTZ9auj3/G5SPvG5JvggDlUWj/7PkS0hNjv10=
*/