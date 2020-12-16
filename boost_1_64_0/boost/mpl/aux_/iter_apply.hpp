
#ifndef BOOST_MPL_ITER_APPLY_HPP_INCLUDED
#define BOOST_MPL_ITER_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Iterator
    >
struct iter_apply1
    : apply1< F,typename deref<Iterator>::type >
{
};

template<
      typename F
    , typename Iterator1
    , typename Iterator2
    >
struct iter_apply2
    : apply2<
          F
        , typename deref<Iterator1>::type
        , typename deref<Iterator2>::type
        >
{
};

}}}

#endif // BOOST_MPL_ITER_APPLY_HPP_INCLUDED

/* iter_apply.hpp
C6XX53ClBBgSbkr38Gnu7+3Xor1nj4y8ni1NSaI/6/xEmml+cn+XLNMJi2RHNVaUkdpg//DIYH2YhrIx1v208WM0/rqA/v3l7eHdvqVPHf+oQE0tcYjQxopcn6XHiMNX1mHSoKz9rv4BYf0jxcmLed6BwSFiSipxThMUU8c4yfQ0nw7siGJvk3cuUxoo4owzjtEFhmVdIWnbu9USayyCvC9k9Hev49rAv2UXL4m0K9OPjRyoEbaNw9jXWnUyOoyT+iMCwjFLZRYstmJ6WrrjrGli1PRpebMZjAnMjgJWpx9JhG+1KHy1JjpalI+cRv2WNV0M08eZEgJpr8sTUodSQBqRSUoPj5JdqbUx6sHRkXyQr/ekD49Qc45BNzIyTBMQkW0uGIVootW6yEh1THhAWJjwo40KJS00IEYdEZk+Z20wlyW0IVox93RnEdLGIROD2R5cO9LGGEtXsmeaoThnpUTT11H0R3FdShMXpNEEp28Q+fRAHRARLK6VSdWqmHaMPioqMlpn2m5i65hNS3xQU8/pKAtxZYNEU3pYZIDYFDGsBdfGVObDYozjyGssbYeA8IwLJdTBjCMNlwqPde0vVv7zYXIRpafjU6szlrE6XEux6oJEYWcaDkGxchQiG1EflLF6Kgo5LFgaM4bpi/7oGEpZHy42U1hAdH95BeWdQU6klOU6gqqvf0CYWtTDYt8IiYxmCcRA8+HyPpEpLSiU9WdBomMy5zVNISONHTEuU782PGO9sszLVHTmaRHEnEamX4PKMiyG0lAbK6ksw/RiH83Un9005E2SJS1K2gH4EBAhatTPh8WouXgqneWo0w/FWfNFybDN08SCsrymqZrSTdfYMqcP1URHqgWeCNN2MZaR2CUCYoK0WrnUsw7P2AOk4WKzpw9nRtpgabur5Q0vdgF2wxDTNEx55HrDVBFkHY5DUbmm94ezHkJjlnxUxaJCME9jLw0UKaY0U90l2IqyMxsmHwVkeRp518s8XCMN0pkqRlO6WAGKPjDMVMbmw/UR2limFhCW7Zpm5JPa1XKWTOmmSVKj6cxrZlEWEabNl14spmFZ6nKR9qU63ihcrYkMMvXLNRVTzyhK82Gm5QoXCy2qkIx1FTlNw+S61wyk0ZU47MhZjOns9Hj+zP/n+6JIY0NG6vuHqtNPr1SfF4dIE/WeqF1DI7VBmszDuH6hlb5voCIKHiK+r9BHi6GfD9dHBAdEDzENE6X52fxEPZD9YVBl3P+yro48LDi9oNWRIaIE5JXPtA3M610xbJCenVnzhTreNPxL9btp+N/YOwqwKIPsJh1LKUgtKgIqKQpS0iFIY6ESS+fCLqXYioWKLQaCiR2IiQUWioAiFiIgiJhgI4jc+4Nld1nu8OK7u+9uYHbevPem3sQ//8z7Z9AnEGQMnoEshDEsMpzDEwFPPHh8x4Xifih0f/0Rm1qCpAU8LXv6Cf6M4MehySA4dkQo2jD6Pu5Bqmi80XHxKXHoqMOOAFQsxM9l0LGun8GLW3rcGeGedEBxBMuLm8a3+JAUhz6FgRPvQmD4+n1/TQL4OOWBjPLiYkNZrCAYYfH5CDqfjWRHxPKHxUSF1gQPnonO0dE5TB8a8jobxIa2zhctNw/0WNyP1yX2cKHDuh+0Bxi/ueLl5+Ok3T8Ph4AJhvNkQbEcfD8xcY8pfr6OpgjO/poybFRga3xuAAvjsPU+DE8FOxXwZHBJYGegPBgcgYcVA8sEGFwUXoDzC4FdAjC4KJyJhx0MdivKg8E7AJYGVxHsCZQHg4twHiSNqwCL43AlHidCewKwKA434fGogG3H8gYwmGIsnkFI+GLgx+HUyxiPBFga4MVwmI7zq4EdjvJjsAE=
*/