/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<po_array_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
xaeLJrdv21mgTRggsqYwKuMQKMWldlsCBVK42XLD2z3C5k4AiggRlBNBuz0kLHE7aukDpqsREhYdlxNm6ubphk/ZrDCu6+/YgXCeJpuvSQJ0DlcHYP8kpiu9TT1JxBKmVdzLZAktHZEQzRJWls3mDvO7s/y1PhKEFQ3hhnYKg8YUPqUzLsmSu3a4pBcmGUBZERCGBGV4R/mLfMtg4ZOtVOPTFKhuefQihjCX7Gq43cfFe7i5ZgKUfq8T4ljC9C2iIZElrEgqVC6pBAFcg1MG0avK4PbdFi3d58lj7UGn3+tBgUdW5/D1yNni5aRDK9P7yrcVYhxzngSKGfDE3vmlFcxy0DdsaCzpBD7Khm+UHBjfFGK+sRFA7TAOcvOQ8V6LDzRHPhBna15QHsJWF2CUHo8+GOHjoSSxIH00ZhBH2XK6UTkqLmfl0J7V5blC4AhE+REEESb243sf+ON+V2S/+10RolAxGKWlbWp6GEQk7ervpw+O7C8/OEIhPLYCYb8+UoT1fHx+dm7avQysAHSX8iFYsQf4RC9KUN7FpQlaoRarSAKRhMCF1e1TUOAEAsgNAbwOpL9Ora/5LzQVgql40Blhe4uPZxdpQxBpQ8hPuzigD9hHKFJHmJ88lThO6iTEkanxiafwIp4YRwYpFJlMHFgEBvbB2R0T+G+sAqHCFIrAKk7gqOLNTFDGKBDcOYH/Nv7OMv5OL/5Oij8zVfwpUyBokiBUxio6EX3W3dxlVwHXZhZiDjQQZ4MKxhhqP7FQnAY9Z35h+5QOl5tyoNw7yF1yvQ+qvIWcgubQ30Jw8XgNUaK7xxfCy8cX6FrvBf9ebyJtwVryudWVmeklVAnn3XBs7uxDeJiuvUwFD0qo4PgZriydhf5uMyIMGQRIlHC+hp497rsYC2IG+m/MiEoCBM2Y0+o+I5RgPhZAe+wAU1X5KazkfajcTFhYXJ2HkuZMMxMJEYhA8RPY79XOH8t6S5Q7dRYwz8Qt7T8jJxhVJwKbEUTRvcAlZF8gAY3SMV9YOxcWZknUrq2zXlM4tNA4VnMJuHlNY7CdwG/5NQ4KmvxUATVNZbB7bHKG/BhLAmzttIXpcwcToMyJIh3sTnW1ZEWlyjB+pzpdG0TpNqw0DGgKpA3j4doEwrrsoqU0SfkjhhdGqoniCPSe6ZX5meU5hKCqSSgDG5lTzQRvzArg8vFMzClkCDHoQRfQnGoneGNWBWweNGzBRb2quWhH3OmLa9zTUcwDvpDZjhA0UgEVbkMfAXZpU2kCkIVL+ulXVqdXD2lHHYJIF0GUdvmAXxRoKgmUW9DiAvrn2V7Thowx7mKmUUO4LJGAuDmJEaYOGrKKhVYMWXETEj9qP+K0PZIUAmJ+Ya++wMpDkMKj3SQYHjBZcJUYccYMDzRqjPCyZEI8RUacKINAlZU86DLmxcqkCLE2idX26Vg5GG6cNON5ttbXMSwHWwOP4WuAjmzgRuzxUO9zjg2HfR+B9n2gi0Qx4imzXBP4gILeMXScZ1D08D1HV81SLcCggBBBdgTNTq9O23QEIZkP+KlsPyYAKTxysz5sHHORMAfUomhSDOopGGszJ39M+4q5UQCh0ABAIT7iN/DhxbPmZm0/itF2HJOyxLsNhzFvOLCoZ1chiMQRRGnxdgPcobnkPMCQMkQoIeb8B+aicS7FHPNCnHpzzCJJCLQf8otx6uspZqqEoMdvxUan34pN/T6OQ10/4rYjiBRbbzRaWIpiSdbHwrWlHA4mV8UdH6Nhb32d8DUc4GvQJ+FCUH9gO0SxQsBH95QD60kr0WbGqhFkjPZtjgslwOSBn4EDDntlO+nlVFk+ASdwJKnZHpZZYxvCizPouL0SpHk=
*/