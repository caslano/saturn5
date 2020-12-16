/*!
@file
Defines `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_GROUP_HPP
#define BOOST_HANA_CONCEPT_GROUP_HPP

#include <boost/hana/fwd/concept/group.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/minus.hpp>
#include <boost/hana/negate.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename G>
    struct Group
        : hana::integral_constant<bool,
            !is_default<negate_impl<typename tag_of<G>::type>>::value ||
            !is_default<minus_impl<typename tag_of<G>::type,
                                   typename tag_of<G>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_GROUP_HPP

/* group.hpp
atfn6vU+n09//rHs+7mePPd1uO/7zR8b2DKw5WA1sFVgH4N9DtYEWwe2HqzrP7Zs7WB9wPqDDQLzg40AGw02FiwENgFsMtjhYFGw48Gmg50KlgCbBTYb7BKwNNi1YDeA3QqWA5sP9iDYw2BFsKfBngf7C1gF7HWwN8HeBauDfQq2GmwtWAvsB7BuH2/ZeoF5wQaAdYANAwuAjQEbB7YfWBjsELAjwaaCxcBOApsBNhMsCXYR2Bywq8AyYDeBzQO7EywPthDsUbBFYCWwxWBLwF4Bq4K9DbYS7COwBthXYN+AfQ/m+WTL1h2sN1hfMB/YULDhYKPAgmDjwfYHOxAsAjYF7FiwE8DiYGeAnQ12PlgK7HKwq8HmgmXBbge7G+x+sALY42BPgj0LVgZbCrYMbDlYDWwV2Mdgn4M1wdaBrQfr+umWrR2sD1h/sEFgfrARYKPBxoKFwCaATQY7HCwKdjzYdLBTwRJgs8Bmg10Clga7FuwGsFvBcmDzwR4EexisCPY02PNgfwGrgL0O9ibYu2B1sE/BVoOtBWuB/QDW7Z9btl5gXrABYB1gw8ACYGPAxoHtBxYGOwTsSLCpYDGwk8BmgM0ES4JdBDYH7CqwDNhNYPPA7gTLgy0EexRsEVgJbDHYErBXwKpgb4OtBPsIrAH2Fdg3YN+DeRpbtu5gvcH6gvnAhoINBxsFFgQbD7Y/2IFgEbApYMeCnQAWBzsD7Gyw88FSYJeDXQ02FywLdjvY3WD3gxXAHgd7EuxZsDLYUrBlYMvBamCrwD4G+xysCbYObD1Y18+2bO1gfcD6gw0C84ONABsNNhYsBDYBbDLY4WBRsOPBpoOdCpYAmwU2G+wSsDTYtWA3gN0KlgObD/Yg2MNgRbCnwZ4H+wtYBex1sDfB3gWrg30KthpsLVgL7Aewbp9v2XqBecEGgHWADQMLgI0BGwe2H1gY7BCwI8GmgsXATgKbATYTLAl2kbGZnewkzxyxIRstGN9XPs+efs4fHLtbbJqxp6M9PnTM80Wb55QN5o/G95PP9plJsT032U9c9qDYuE3PPEA+r1jb50XHamJvGJt9711zHXt0dZunn7GOpauucawsdpexSxeHXnVs+pdtnnOMdbty230dWyZ2nrHnF83t51j4qzbPvptsonx+4I35QzRnYocZm3bkCxc4VhH7wFjrkteGOlZY0+a5w9hWO96xu2OTm22e4cZGJ84/3LGE2G7GLineM8WxeWJHGZv1me89xz4W28HYsr3uX+rYerHnNllYPv9uWdcFjpW+bvN4jW116KLjdX1iA409E//Po/p9Yhd32WyrPpv6c63Dv9o8fU1c/1dT2mdJsec2xU2Sz+23Dt/esdHftnl6b4o7UD4Hex10kWMhsYM3xR0kn+/ZP93NsfS6Nk+bZ4NFN9qNOz67xrGrxY71bI5744+P/1F7UKyPsU/vab/FsYZYyJj/o4ubjvn/3ebpsckmy+eFwS53OhYQe3STHSyfzzj9zZ0de1Os+yaLyOc9Tqif+3872bNSrM8mO0I+b3gXPVfEBm+yDfWfuey6jGPtrc05i8q/e8SvvNix/mLtm+xo+feK6MBJupcbm+qy4WKHb7JjNnxf/MpTHEuClVub956zXPvSUmNnu2wZ2HKwGtgqY+e57GNj57rsc4hrgq0DWw/W9bstWztYH7D+YIOMne8yP8SNABsNNhYsZCzpsgkQNxnscLAo2PHGLnDZdGOzXXYqrCEB35cUa9s0R2fIv0+cHljlWFqs76Yz9XjXGX6rmG9jnHfjPl++46CZjj0sNnSThTecqSPmP77Bum6K3zDv4WC4rLO5ydrBvGA+MD9YACwIFgILg0XAomA=
*/