/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   as_action.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object adapter for compatibility with Boost.Spirit actions interface requirements.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object adapter for Boost.Spirit actions
template< typename FunT >
struct as_action_adapter
{
    typedef typename FunT::result_type result_type;

    BOOST_DEFAULTED_FUNCTION(as_action_adapter(), {})
    explicit as_action_adapter(FunT const& fun) : m_fun(fun) {}

    template< typename AttributeT, typename ContextT >
    result_type operator() (AttributeT const& attr, ContextT const& ctx, bool& pass) const
    {
        return m_fun(attr);
    }

private:
    FunT m_fun;
};

template< typename FunT >
BOOST_FORCEINLINE as_action_adapter< FunT > as_action(FunT const& fun)
{
    return as_action_adapter< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

/* as_action.hpp
MebT/DP5p0Qb43kg7jeP3+8X5EEVrS3GIV2QBwMtKvIAz9TIg3X2O+p25MER5MEnyIMLyAP+ToPw/xyvI8t4H2kWZ5yU4WGWSbbgTfpx5DDtyk7JzbQs8q62He8b75M7mnqQ90xb6Ez/T+R+lh7klGUH3RJySJ5mzSC/WdfTvcUPyc/a0sk92z56tPT78gZ7OgmrsJaerHhI3u5IJyWrbKUXqx6TjzjT8Sy8nt6qfUj+JDadxMZto1LDT+QLrnQ8C6+nYc0PydcTU0lq0lbKdRbxk/jY65tEC+YPmmo/qs2QRxmW39RB0HmC7bY6335TfdFxW30FOr8Te1v9GDrn6dcB5gfuf2ayF8mEfqnKBSWORmsZZI1WWzlrbEgrmjLIalNnRQly0RRLGjlsaaSYI+JoJ2sa+RDtQqlSLjrAlkHO2lxKlfKN6Gh7BvnZ3lxpGOOi2Y40IldxKa1rNqIrnGkkoFZzJa2+i74cm0Gi4lzK4CaN6OuuDOJo2lyZmOCiHyVmkvikuoyPLUX8/HgZ/CHRF23XFLJNbaZdVZNNd9WelrvqSIxZZ2HMutx+S93o+F3dgzmSo7G31A9dfvo4sAvMXB6GKa++cpnKZfcSS2PM2lO7oPY2XVTHWW6qi6xX1LW2G+ou+2X1oOMX9WPnNfUc0u1XPHPy8arwP85tvBoiZF2r8/qWaCIhWlXE02EK0dphbP0U+qEhtnvqePRDCxz31FVO9EGx99R9Lh+9vnWHWc7bvruJMonVWmleWgbGu6MssjYT491lNqattxu0N9EXvg//X8Uy7QeXgfsPFf4/rHb//l4kUovRbuH+5bTull/4/bNsPtpEu7+2FGP7FRjb58T6aYfQD9YXaZ0Bs1jc30jq4/5+Wk+Tn/YMv79RW4H6s4nfX8b9jdo3qD+XxP1DhP8z/P7v42TMMppdu6OWM4VrjS0mrY01SOtj07Qhdos20+GDfjhA2xTro73qCtD1z4J5Wox7jcTBx72t0Qb2svhg3Mu0WTZfbY39D7Q3Xhj33kM+++rj3hDh/yzvTxTC00TI9vIxyh6kqaoFaGbNbrqhVsAYso41UGuNZ4iu9lBtlOOGOtIZpC2MvaMucYXqaTIUZoQ+FnfyOCWZTBiLmxEnNTdOYizuhzhJWm6czmB8wtNE+N/E7/9xIkOeRGn31NKmYiJN/LRMjOUH2b200Y4gbT7yZC3G8q+4ivOyGyr8nxQ6DRCykblyXnbbJfkSvLtLXlYTtVSyR5uk/o29KwGvokjC8yaT93IMuUjCIWIg3Gc45QgQ7itAIJwhkBuSkItcBAgQThEQUEGCchvkEBElSEAQVFZBUVlFRReVxWPRZXfRRWU9cOtVuudNv5qZxL2+3W/Jbm/t1Oupru6qPv6u7mEk9NVjfjvtmSFp0kchq+xzGiVJVxuts98XniR9E77RvqlNkiS33Wjf0ylJCui8yX60R5LUtOdG+6v9kqTOURvt7w9JkgYM3Wj/w6gkza9LIf2I5b0Bdejk6AZ16O4X7IgJqeNIaOTnyA33cyyCOqzuFOTY3sPP8XQ/P8cp8KvqtYcN1x4RHXFcZvfHbFKMxmtjY/dlPLNgn7maN2fSbmmiB7uz6LlMx78q+TB+f8+VOn6htEmu5ts81+v45VKqzO/TbAH+/CFO/lXPzuw+D/C0vCPrHfSeEF6ppLd5Rinp9IyyssczSnm/Z5S9Q55RqkY9o3A5FfBObA/nO196dmB3cJy8wWPwOybd4uTDSp73YWVBwGFlfb3DytbGh5VDzQ8rJ9sdUlidMP/P/Z35F3onyycZ/0Xkc33CvW3RQUz+XuAfH4jfY+B6IK91L/QDmfHsTl7dfk7eHqU=
*/