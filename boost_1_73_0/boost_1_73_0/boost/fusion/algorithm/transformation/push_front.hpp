/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_07162005_0749)
#define FUSION_PUSH_FRONT_07162005_0749

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_front
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<single_view const, Sequence> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_front<Sequence const, T>
        >::type
    push_front(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_front<Sequence const, T> push_front;
        typedef typename push_front::single_view single_view; 
        typedef typename push_front::type result; 
        single_view x_(x);
        return result(x_, seq);
    }
}}

#endif


/* push_front.hpp
wkNdKpI2srtIAh9nI/se5k0cmW/7ve43axX40MW3IR8RlX5ZZe2UkEOJ0YwV4VvEVdXKc9Oh/flXeJywIKOAAlxmPM1eOhze2rk410mQdhKu861HzQu/pDX82ZZrQegXBV1E8cjs7JgkFyAtu7mUsMUTs5P/or5bSCRbPCjOr+qOrzIHxfmVFJlpp0KkqWyrEpLD5OuAlxMVi4eq+M0LIcmzDKFSpJupEhwnEIcq2ZFieKlNmRfi/HPTQj4i3SmqVTq6K66GfV6dq3FcuvLqxDq/OnGtvH1CnV+dunDDPofOr84cXzW/jCYkLXw+Kf3qteOrzLl1r4YLpTLHa+c/i8vk/iY9ZDv/uZM9C39zwNjNnrTR6OMk1/t/HvE/YA6Q4FIOt6mpmIkfzeONgZaeXQEmdgi4aUMjKXWegX9gGGAgY5NdGbDB1Xm30/rkf1PJoDmcnI34h8tV9AM3E4z5piCWG4iyNOgU0QxE+4GWfQS+R60tJ4rGR8ytPN0fDfe839T9HfOn9NV1jJSJ7BwVcAaMUgBNEqfHpu8TBhDcgm7sJMndPv8KV9bbMFisDw4OdkshqYPs6QzTgHSbJDDv73wPV9fhKk5qXiWItn/RvOqOCyiTRSala2n7cAxV8S4pDbcxQd+fGf4l33sR
*/