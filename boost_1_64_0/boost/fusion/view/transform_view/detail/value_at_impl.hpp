/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_20061101_0745)
#define BOOST_FUSION_VALUE_AT_IMPL_20061101_0745

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        template<>
        struct value_at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::value_at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
Zv8Y4yeoQ6rgEOoy9BHXABw5fs/irLlusKQxWOhSkAb629L7Gq79+S63XSBIjn2fOCb88rAtHcdEWTi2CYcMNa1uMQZgCQZN4UaH0zYOQyRKjQwXGIZ8+QxB8yuE4PNT1StMdYu55ea203Lbv0QVi/ujif0qAa8FJxLYSbRUPixxIjLagxwU2NC8Uh1lEW7cNsA8wA7ucF8fjKA2y8TSkB1MibrFb0ZNBtUyeShcCkFBRgo9kfaXpqTn/UONI4ZB0tSYTbOvjgKgQcitSzzDyVkLocCIIn6HGnRgkB2InfSBDb1ZbJlh+kS85PvxrsOh77FUMtjavMDsVXMDuJzQJZubwa/khzziQzWPTPwqc6WvIgemBmH+wc3iS5/HPkqYIlGNN9rtkOZwqbw5GZFmorbFpu0RgOkZFJk/R7jaE+ytzdfw9bBj5raHgaqrOy76hGHu+THImhjDUhchsRv1BN5sKu6kIIHjF5X8UszbP7JJe9Kkij8a3yJegxeGwbyj4AUpP/DnA6xUkqzxD8ALSGSCR5qhA5hTc7fwnPySYEnRGCB/S1hLCvhc9w==
*/