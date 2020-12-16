//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONFIG_HPP_INCLUDED
#define BOOST_LOCALE_CONFIG_HPP_INCLUDED

#include <boost/locale/definitions.hpp>

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOCALE_NO_LIB) && !defined(BOOST_LOCALE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_locale
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled


#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* config.hpp
zAMsAix/LGHbnbgSV+JKXIkrcf1V11+1/19VK7b/+2f/L87/Xy32DA8R3wbI0ot96VZDxgS4Bvd9Pwm/AIJff32TKJK+AX5d2TDXndej7+83XMFvi0eAu4XNQFXf2tgOO3pL630za1t2ESfeDbnuNxbULlkmxFD2lCdIuguMw+AB/WzDrVszk3lzrZF7Jr7K1lbpb1/uB2wrn9/qOhErdR742Z8MOB+gW4tkXlyLZF7Su3yfT+3XZJp8cJOEf3EPv36U9741poDP8wCvAXRrlyqvE0YE82+pbDRjA5TK5wtc7YYHFhMeYxKgA6Dbo1HzyizoO4+fjmXB+bAhmCSf3+xKR96icraQv3N0ezhqXpS7tgkbITJtrpI2V0mbzbT4SpXV6ZVLz0jL8n6V6eqg13KZzzzGGdhyRB+NaieSXC3SL8OaRqGM2/AMQPBTnSO/pMPyzpRp7wLvx7GugmmsPAyR6eYZw4zTJA+d5GHr9QxcWCudUduk2pdEsxvZEmuyWBKUtiJP5wZtGdbICLcX6cDvKbl9f5+Zib8ZA6HGYQyEbK7njhXr0so7kaHuj7GNh61Xq22V+2MTZB6yjZn7Y2grqg8E6J70rPN83BN1Je+pdcv18U7zGfWt2LMIvWZRr7HsWdaSdWMYoAmzZxnNT5Vp9C1SDrihCHqsUfsQ0TmJbVbDsjejW1cnLf4LtT8X5VLbyvEyTRbaSoq2b2AeZpt0WdrkJfL5+qjLPM27r/DA9udS9KR7v5le/54pfeQcmW48dDgI65SuqO/DNTLthnhv0kA/Xerp/Dys/6Dz+W1lAU5sc9A+NftNQkdCt1mqbtk+oS/TJ0o226a1raj7l3O4z34tdX8N4Ea0gV5tG/DKTWHKzXFE3tL7JqFew9Pb7+v1WurBZakHTV1rymBd2NR1r33b0PbXavqqIgOXlLnRp4xTa9aKNH6jUfK+24jiFKw3Q6DfVwaPKRPSUoFD+0zLPUL/u4/IYLqAELwA6YYPNdPsPIJpGEfiItDMk/1e7DaTDnuultqQPRfagNqGzPpiO1LvU2n5bEfaPontSdcnZWramdrXZA6N9HmzGJkFasPaWTUmX01tUK7Qz9wh0D/AJfQzsk+Ho6mfVR34PQrFUCrmHux8wFBAJ2A78GvUhZUP/0c1Sj9n17ZJp2/bpp1fukyzOtIP1rV35sG5QJLMo1rkkA56iGvMls+Ha9q9lrZRpT2BtLp3QOV9m/UkbajSTPpzZJoM7Tuhln1d6J1oaJNpl2MMGmr2i/VGaE60maTJ5G+XMYX8hb1X4rVS9DdJpik3Uox83gNH8t40lLWVfNdyUZm5UIhbtJG0bdMGpfe1k69C7xrTbY10g+S7NtpMsyPbUiivGqRJEmlyp6QNyu/Lq8NMN0XO3Su3wt3B5tzdlHMt6k20zUwHe8m0tbF/J1WbqiTcZxvhvIP3ZN2b7yHqFPdYp6QX9SLqKot1pb4bx3OffXMyuBngXqQNhL8b2GY31PYmmU5nXfWwfrX2cUp7I21IOJP+G5lmpN5mrs7qt6qprVEZaxfL5/loJy7tu0J6x/v71KmQj3XCeybfFv9Vkh/2d/TxtWAl08eOaRt7N3RaOEPqFOYd3qrW2sqW6pniA29jI53vQRSbBdJyXiTTVuFLVT+Wqmn9is50+mFata1H09VEVVfgOcLOo1rcI29m27XR01RPpD+6JtCXBfVU11Jb6+WHt7fa36DoCXfsbKcs8szzOLftkPIwb9Vn2+wRik859oP3I60vyKeoQ291o491Q/7G9LVvv0w3Qm/7FFGvskn0jQPy+XBdPau07HNbaoHN/ugw+TzF7HePnxHzXVDql3VJWcLqV/I=
*/