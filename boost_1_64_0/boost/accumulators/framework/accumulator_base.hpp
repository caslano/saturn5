///////////////////////////////////////////////////////////////////////////////
// accumulator_base.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/accumulators/framework/accumulator_concept.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    typedef void void_;
}

///////////////////////////////////////////////////////////////////////////////
// dont_care
//
struct dont_care
{
    template<typename Args>
    dont_care(Args const &)
    {
    }
};

///////////////////////////////////////////////////////////////////////////////
// accumulator_base
//
struct accumulator_base
{
    // hidden if defined in derived classes
    detail::void_ operator ()(dont_care)
    {
    }

    typedef mpl::false_ is_droppable;

    detail::void_ add_ref(dont_care)
    {
    }

    detail::void_ drop(dont_care)
    {
    }

    detail::void_ on_drop(dont_care)
    {
    }
};

}} // namespace boost::accumulators

#endif

/* accumulator_base.hpp
RkR+K0SMP0+0K/kpUf9MJAvclWIp7B+LhNueIZLITEEGn8ygSgBy9xiy1+v2HDLZ63/iJ/f/i+USWo629xlMW/pLXDAnjUp4zsCqwJ4V4Ho7Kb8Ya5T6Le3O8RDJKl1Zbsrve8QKTd5XNaduJ44/2I/x3LHkYh/3836+iCvFYQoh94E+KlLU3b0Lk5DH43xwpRAqQ+FPy0YvfX6FyZB1c5fVVxD3sI0niNtfIGhudGAf46K0R+qzomkT639vpHTpfpHSVbKr8C7IicDuX+zRd4DEQYTPI0BFgKpvEQF/QJZcYPnjQbQh+J2VpF9vIX9lZq6F5sNMVnSg0lyq9Ax13OgxWMNeodSLH6TUK6axnDtXLO4YDNqwMcHMMQ0J2rCUYGaKIb2Ut+Ae9At+29qn9jnXZaloc//ta4ZuFFvho/ULywlom9pUd1xZYFOctGzHxH2sqnXXEzB6F/HeutIWvQA35ojFD9Z/2mCu3/y+zITHpO93XmVoMN18D0QyHfeEeLFj+3lJVA+K/ApYKu1zFQL0W8KmvCoNpW4FCF5aHt4BQ/baSlO47iRpUjo4EZDWU9QakAgUxEfovRCmBk9gg9NMkNgwB/568BfVYj1AV+Kvir+snB6pahZQMDOBIB4K1RyaFb1OfhmeL/zw3ko0C283/XmI1cjvDQ29me7vA2b0yhqqenKqUGAgNOtcMde9iAhDZggCOjS0I/rD94rRHy8Y/TETwpJ963+N9PHnnSPTD9pH+mLWfy805NUO7BT9mpJPvKSKbxd5xsDjIU8uPCp5eME4D1+5hG+3dsmYknXTBoj9HJ26kZJH/Ee+CZXYgtIxIbqS2k9cakM3tRLhRLwAcgOAhLUQ7VBV/b7lPHMWHxgOZfsXGu2fYrZ/+b7oN1aV+sECKdjdhZHoDQ4kWeuDv41udD8STD8RfK7ebbWwVX17ZnRX8BwSsAgRh6X1pYjwy22FRkzb4Mke56wwVXQZ5nqeKbVaXV3GnPMFmPp49tTP4YA7TvdDJKTSDnSYB3E8wlL1pN+KNflcq9gFzJ/C8iNbIIkye7CI+7WVkD6+9xqnKz0S6SjW5UdslrYBpVGhorAjlonCtontmD7OLCwVhUFKjGulmRkBK/jk6yw/LgwkeRpuITiXxFFLQq9w8MkIcSxJoRClknqwGbv5h/AJX1LhhYCu4VzOFE9JxohMp3Cm7hSSLDMVXqsGyvaoz32HmbrQQdkAjJ3SmS2zcMuKzyuKDyRZG35JWC06jZEHdBTP5ZL7GakpbM2rnCGJ2hWnLBPiJnQQdd6zM0QnvsKKMHSrQqztFULHfYiVWQfwi+43uAPlfHvKy2K3EQHVBoHmen3T9CjR/tXCREt7iwx95CrR3n7T5TYYPQqZm0OffKfR9VZ8u/S+S/n7WP7Ys0AIKfnjAk5ZKCguz0F7vAGQhLIQhS+2oJBHfseJUigHiR7HcXHFlOkNXqgo13QBy+DlLNmTSzCtCxMxkSJAPcizaYv9mjLK2KxtfUmgbxtdsx/E3mw3KX3/NC2KwjKLHPdTMO57VguwP5galRqQuUQoz4o0+u3l3HKwNhtoSN2whD6nE16Njf/epwS2xjC2VEokqHaYzHP2EgNZuFx+KO9mTs3RhjswfJFaDF3bNM7Si7K/UGz0nf11A7lrpkooWREMuAm5Y7QVpgEH7bkPOnW3xK8kz7tfZPxmaV9nwRxe2+7FrHrlYpMjGEVo9ejz/mzK4s7C0MWUwwqRMNHGGkiUFaFsunwOS9qQqrs++3Veghuc+lT4KLbhSaFoQoHUXpWHNFHRAbZWnn/8OzdA63F6SR+LPuMxoWzrS/IMBICHeftvvB8cfjd/rcQXc2M=
*/