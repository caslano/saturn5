/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133)
#define BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133

namespace boost { namespace fusion 
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template<typename I1, typename I2>
        struct equal_to;

        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<filter_view_iterator_tag>
        {
            template<typename I1, typename I2>
            struct apply
                : result_of::equal_to<typename I1::first_type, typename I2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
OxsiTOozB6tZZ0TAT6OzadaJUeffIq8te4DH4F3hMSbLfEkH/sseFgT6g84yV/MoaZKZOescacI8qs9TBOvVFf+GqLGsTf1w4C3fFnfwK2CD1NmFlyR5Hr3RdBprHhVzGvHhRmTigdUyM+ngj2UH+CRuj1ZoZB6lTVI0jyK3iQCfdPG9CdBYBr8laqzX/NE+9aiVG77cknQw0Vdfdxpr1jr3XrKBad3a80ZWsW3wjXq+PCnUPIqPJG0exfhDhEheJ010+UqQrneJnye9VqkvPY21+vtJD7+0H3U5nwI87qKJErMrevDSCiSJ4FCOn5wJ9o2tQVaYNpkkCnzeRTtMqXcTCuoM6E0CLceYt+JOvQ3QIqsrto2/QWcfQGMWDd42pmKcyGElQaG+o4WOhpi7/ph6YOVsk4ZW40XBzXsJHQaTrb1c8Z7HsArSixJQR3I/rITt6duFl+upXMl3bBkSfooqNUgW3ER6xhuKkOPwz/wtLCO6a5VYyLmU05xw/8+OmXFuoWZ66RKRh/uCS4I92bY2go2sL4G2l4V6kjZRisnqr3HiscEqgblinMnyFPeFZHXzNtLPm1/KubII0vfOJ/cziV27TOtSwpJVvLOirPoquSYO4NlGIh+V8r2dHkz2OK7OHw9JCcLUd21w7Tcqe0/qezJ3Esmy0pEO7IpZl359fR6ACotWrwGgi1xE5wXJiidLII4nYRLEnpKs
*/