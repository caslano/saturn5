// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>

#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/policies/is_valid/default_policy.hpp>

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Range, closure_selector Closure, typename CSTag>
struct has_duplicates
{
    template <typename VisitPolicy>
    static inline bool apply(Range const& range, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_const_iterator
            <
                view_type const
            >::type const_iterator;

        view_type view(range);

        if ( boost::size(view) < 2 )
        {
            return ! visitor.template apply<no_failure>();
        }

        geometry::equal_to
            <
                typename boost::range_value<Range>::type,
                -1,
                CSTag
            > equal;

        const_iterator it = boost::const_begin(view);
        const_iterator next = it;
        ++next;
        for (; next != boost::const_end(view); ++it, ++next)
        {
            if ( equal(*it, *next) )
            {
                return ! visitor.template apply<failure_duplicate_points>(*it);
            }
        }
        return ! visitor.template apply<no_failure>();
    }
};



}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
d5DnSnAsDq/agXJx5KXqVB4RfsYFMLA7Lw92HkLAU2w8dRLgrs3J48qTgQc2VzedUwhn6RB+qoCrayDtORfEtUqgkEDPMcwe7wWwUVsPCzmpLq/n5U77CMCH9KSSOe48zHesdjGrJxrPuTjf93HaFhfj8y6nawymU6OJT+xaUVfc1MP7iDzMxtr54+JdabafUObyve1niPG5+0HvG+OEwpqji7trjvfzwrt7F5ZHuKvzZidu0reRPwDDeLp+4Bbq84Nh4NgqZ7pbpOszXZ44BlvlcpyxUx2OO+6ROXXHPWtcnjzuIbzuuOdsN54Fxz3nAF8RadxDeV+nsXrjG1s3tqB/pzpAum4nzLUzZkMbBQ7v13dZHOM26W7e4o1pLLYVMGhTxDydR1jdPG0njpinHRZ34+6L5BU/bmGs48bN3qBE363gWHeT7GW3x3Hrbb+A8zcPBwh3upYGHyLc6f7ZtQMPp76z0+/zyhXXzka24Nr1hNJlY2tnYNrjYK2h0Md5uNjHOQBp7YBM9KZ7Yav5yHAPbK9OaT9G/lLiFJx50YNiPO4eijFtqx6PcS5A25mX8whs3+flZLD99DmNrS/NbsCNhII+J8T+Ux7zBuU60JbekRzRN6DRXaSYrzjeYNsORTwhte0XimU8pf3e6AZ1qsCcFosise3DhTInUCRezkWXB7vR/LgCiUNx0XkOh0fxmLQqDi7np1qHw++dnXU5CrblMedjakOYDXvYxcE02bkFB/PzdsTDMXKug8ssB3el5bPRjcsWv9zB6U0kgz+GcB3Wnat4HMer+H3FqUzI7+y9IsapsvmbJzqYX4ZPJhzzFvMdZfBzlCj/RuJM+xyMi7UpT4V02ENCVv50HCeADMvGfNOzjJzybLHnAzaZD6A/kk2rsxb4PZTfKICTVcKnCadssvAvVPV7Ay7V0VNDdXCdCW4zVyKuEbrwrMG1RpUErApK7cCTHB9hzwlAumoLVXJnsrdnJBEtucFpINvvpLZA5hXYXVMvleNy9ny/HDgDgyNJ4CWk/aSEuftJX8HDUX8Z04WyoQ1CGCnFyTH37NArt3CM+goUztn8ksmNE76lmeOUrhye0jb4q7Zw3KZPc++A74O7efCb/W8izP2mq5xw7tzk6wCLL6ziOJ84b9BttVCONv03a44tD5b+2zRGeiWdXUMY+242H69xyj/l6zrsH8ybr+uRI+brBsTEfL2fMDFfH0Sc5Yv80IexbxsdkS6XqP//UZDDy5nQx7XOhObkFQbz2LBUGzr7yEGOS/oUxmCfBCwqqjTGyn3Ppw3m7iWy6X0W8Aro1eTRhPui6a9Cl0SdrtuVGI46xHZu3ce9udav+hzvXNNLkUOqp5k++w1fj3MwJXrTjXAqIoqH7rLzeP6+w+9KHEzPcr4vcRrfu6P8caUozse8S+yz3QzpQieMXXifEuYefQ6fe/yxEAdfg/4p4ITh9JSfhs/hadwixMH9/NRpHPf9F2Gu//qZE6/rv37hYHj6vxy7/+5XwFG3m6mdVvH0qS2TOO480K/FeNw24jfAwXco1BKa34f7rfGlbllYPfwecYax+WPCuI7tN/xV434em5zzIaAgtf2e3uJTfSCls5AyHZ9n/Tv6u7r5PmYr4lK+70KYmO+7Ii7muzk2FxDp1p53IXkBpCYvd9tqfF+uEIJ3KwR0fuMeFoNuFX8jxcphz3VYAojtywYszGNsaRUd3rBo4zwZcRtyJdU5950KwTct2epypHdil3oc9EvNsfkD0A3to2dy0E2D/ikPzlHyTzeJ/cXTo/IL0eEnBvbthRnuEbgrYKRnR3+i4TE2dHOna0Jf9XuibzwD0o6Ox/dBgrAcAg1yz64=
*/