//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <utility> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/utility is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_UTILITY
#  define BOOST_CONFIG_UTILITY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#  include <utility>

#  ifdef BOOST_CONFIG_NO_UTILITY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#endif

/* utility.hpp
wPfRL3Je2kxubL7b7IklPjoD8x6qGj4/5v0aPbMfaR50z9kyNjlVcDCvxGJhQ/P9zCZZ7TM+jnXMx/EHivk4OraJNJn5qx+bPo4MgstI1fF1MMyjpMThDw/Vvd/TVsgHHeTWQbQ80iU/bK92HcNg+rabfCZmyPEB/vXpd6LIYqFkRPivyNQrKy8piJSoz/xItCBqzTjHUfgZebuPfgAXjm/8hm3fvaNn+x2l4C3plSpS9xSjVJ/WbhAMgtvnxvoohDNyhHo2/LHxA937LSX6IDu3FvGDVk5nzk9+aLC9CGyGwfxYJvtoAtbDTc4d4paj1uqZfkMpkBvDMntlbIxVldb8XhkEjyusj6+Hm9l62EUhrIdxUuuhu/NjeT24MIw+ek58PdzC1sPX8uuheYx214OBcO8Piod7wMOtjh90SS/E2n5FXvAwU6buq+N/1/xhlwkGwriYOtdHt4CL21RD9MPr1uvenbQtKVaTS2hNYJh2Xw4GwtfF8z7qBy4cG57/8rnXQ4KgRMjWi2VqwFYUVVhjoKjCrYtv8pncmXc4OSP9PuTO3E6xvGgDhPaFoor8wnJr8jS+3p2Lo8ln/JpGsvxGX1KfWA5Vof1ADTA0aLDN+euvZ74LLeY/is3/CwonQ6eQSJQlM/+IPS8efL3733+hj1ZBz3inarhrwvO3695t1JACeVFoD1QxnpE8pQjtkpNrjQQ3htkHXvXRtZCTRqvn2onbv9Uz/ZwI94eOqZI8FFbY50FjMHv1Kh99AB7uUs+lp5/whZ7pZ7QHd+veiZI8FA+yz4PGYPLiRz7aAx7uVs/R71XD3/NT8kJu7izKQ7TaPg8ag+mctvjoBPBwj6Nzfe+1O+G1QPX7I642SZSHiAAPETcP9I2POoKHe9Vzwpbt+XqmW+ipDrDLeQV5GCywPwCD6VnS/DQHPIxRz+1T1+E++QmFj4C8ILlPVhXa3x+AwdZDBz8VgYexHjX71ANhv9+sYoRQg1JIbtRjFNgngcH8OA7z02TIT/d51J+n3ooc25toQwB+Xq1l5MfmMQ6tLghbJwIgblnyaD9dC1nqftWwY9uVqIW1kUIxH9AEwTVRJ7BXtsAwPBznp2uwJpwcssf3PApnxsd0VxL2ykSitvZ5qFK1h6zdqPDl/D7ZxW/uEw+w+8RHVO/BviBzn6rKLy4NW9PF49vZ2dDFb2oUj2c1ijdQL8w2W6YOhRqdTSdwfL27/kQ3P+2P+U9wamoefONM3bueBngQJyUTW19ltewsvp3Jid38Jpe2kxf5vFkLvtSzW0ehtvB7ThH6t49ELb7z+suZHrGXn3pj7hNVw58b87rp3rXmrtAoc1eoyo+WVlhTpuLb2fl/lp8Ohxz0kHoecscOyINryHsk5u4VyUumhlWkJHc1SqsRgi4YtwwwwE9fgY+H1fPuP3Ph1/ohNcDPefl+InlnMFDnmR+yV5DbBeO21Vf6jc/CJOaz8AGVy+ZlajFQm34LLhh3za4qP50IPh5RDTOHXws90/s0MubPJpPDrsVAbXrCu2DceZrCfgrgfXnU8Xftd/pFMY+23jg3ViTLnJktBlpXXWTNn8ONw+3WtX5KwfqY7FG7xoADUKflParvCjulOlMyBPgojISbP1SdW3uSFAfhucxu91MiuHBk5z2dXoQ8tYpuhZ/bZV4RP7f4MAutRdUxDLYmxsb30ClsD32Xwh5EHScIrwmbOygH4XZKxcWB4OIx1ZBcuQdayJWUkos8yenCa6Kozt7pykG47eZRPz0CLpx6b8988gUyer1DHcFKSKYWeXyYJQJUlLjuHrP8JheoY7NddeXcQXqmb1Osbn9TkuqX5MHmicpBuP6h0W9ytjw=
*/