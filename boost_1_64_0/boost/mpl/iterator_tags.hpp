
#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

struct forward_iterator_tag       : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag : int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag : int_<2> { typedef random_access_iterator_tag type; };

}}

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

/* iterator_tags.hpp
xr26gIECf9QFKOxwLWkt1HDIr7UsZzoTwkLSTyOk/jNUTQhiv3+4j5wPeJ2k3O4VAScF4XTjLD1B+CcEisVgSRODhbxRfLCqD1BhF/oo0qeJehH8JdQN3bYbXomZMLlnivMqLp6FhCx5mOXr1JUou73w49T49sYLcxPbG7/dP2Z5c/yB0fdHeyWB71RFT5z8haq+WPGUztDxlOKfrxolfFJSQ4umOl81xIHqoXnAbJjiZ25eR85XY9zeK1+fSRurD6kenPHEtH/TpiHsNXGKzXUSbeTgqZq8KwXh01KEMDg+wDwAoMq3h3jFmCXaPvsbwWHD2j6+Tbui8WmqcUZbaC4lc1D0hiE+/JEdhH8JK0N8eNWmAY1yAifTP27aWNe21z/B3hH9Q1P1sZ/2qH/cpDLUJNE/RFv+B0n0D+Hr/1O7/QN3spbvO8Bvgr+jg/A5ByfRP9SmRV90oH9II3jqg/b6p6lXRP+QypjWtkf9QxjWvZtE/xBtD9Uk0T+E74YfE/QPKcyTvusAvwn++287Bj8vL4n+oTaZZgf6x0eGhffb65+CnhH9Q5LXv3OP+ocw5L6TRP8QbV3eS6J/CN/nP8TvH6W1r2zpAL8J/vQOwn/cL4n+oTZN+Fz1T8z4d77w+8M6OIL5A/apQgdzhS7FLvtU+fzICfKpjcngq1t6DpccBPfeh3YiUYXW8rHyjp3ke2JPq9RPT+hx3hNR/HV++t/8uBrt58hdg893+FBioSix52GftX7flKHjZSkzQyrZUqyGDtbBufNarE1ZHyaHKL2KKR2hKG3FJeUfdzV1+JIy0RO5ih9C28L4/an6a0gG70+My1RcirYqSUubSiWUcufqVWE303ERv6uIWj2Lk+Z0RxI2aYYFM6erCGldrPc4n9SDCSK0sthhr4VwUvtX8yCX2rg3U0w4+cOc84VkXkkHdwoJ+m/IXrb2e6n9b6r2Uyt0Gw/SAWL7KfpbeVfXKm2hIA5Oaon8mdem83hptI+Xb/axxksXBErA3Bhpvk+2ITEo+CV4j7RRPASXfVgahPmqG01IdbFoEWVCwR9uHkijCnvbNvakH6+cxy6BOwOXxWp409vWoDwFW4XDzHySBJYX2XiPdCM7VEi3NpjETv+HfTCLaXc5D2bjLcnARsy4D9zyWkPjHvRW4vFOPTPKlWC85+L+r5f5XxcdrkX1xulEP8Y5mD1OzYvTRZgCMW4ryCTcg7jCEDlOyfE8Gj8sy7LNj4kSaj8BIk4vcb6RIb+VfZOx4B36Bmj6/hpXemmOfQhspSSE7zYfozUWtZrwVTO5VpNBHuXcPiQt8fBDm4iOIiPJBBFHDBfWWmSnl/GA8cqHccwajGEv+u5CsRXf5EhVVw/cYrhI7oiB3woNa29ql+rzQZJfCDtNu09vwwG0WyRIlmpX80A4V82kOkzr5VVoCiThaiHhYNUYnSIHSN3POkA6+NH+bvul2eIf+ugKDNmaWFAKxznalD23F0ShcHDDFRiY441UNoFX/Y39N006/UoPexPBFSrhMVPc5teIgsyIh7+C7oLx00crNpyz+4/wew0hFcvCnQQL7s+jp6L8LsJAFUFw4RyhaxVQoXOI6FYnE5WpieJ3iGbAuurt0MISn1/mJ72wv47aH2dAcY/ejz8bB768R/v77Ze+i4kP5nBiP2SeXZlybFWM4qViOoTaUX6XYdT09Skl5hwhpcpbXVhPJjCXVd661+3lh1DJpZuopFST8sJL7sVWVGc3GiLJbNNjxB8bqar1iong/51h1Ob41K7m5WZU5z8bqeDH081KsUtoT0KUBF2fDw+z+2o+zPYp4WkcT1hV01weHB9TwzvcMiv+GRlP1MNlHNM=
*/