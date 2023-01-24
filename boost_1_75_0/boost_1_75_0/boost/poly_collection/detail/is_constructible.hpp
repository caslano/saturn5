/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC_FULL_VER,<190023918)
/* https://connect.microsoft.com/VisualStudio/Feedback/Details/2118677,
 * fixed in VS2015U2 according to
 * https://blogs.msdn.microsoft.com/vcblog/2016/03/31/
 * visual-c-2015-update-2-bug-fixes/, via github.com/dodheim
 */

#include <boost/type_traits/is_constructible.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
struct is_constructible:std::integral_constant<
  bool,
  boost::is_constructible<T,Args...>::value
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#else
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
using is_constructible=std::is_constructible<T,Args...>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif
#endif

/* is_constructible.hpp
clC8+mPP/Fvaah8aEVOQ243HE3nvWobDJm5ciYVkX0ehsz7IaJ2tBWgERVm3+0b7+IM/gM/fHt2Lyfttig2+tcGCN9AY1sQAwy79vUQ7w5j8mXct/TeWLY9v363O50uR+y7OYjmrOCfAmSQmm9BunVYp37j5+3yndB6FRAtgCL7FNwoAcug9/lB9rHQlYg9nti8YN9fhIdGO4lTi7EnQSLnUJmChYaexVRJLb+HeRTEeFKnaSMB9FjbYorG82O5FEHP5q0s35rMEcz8o6edsol7KF5Vu8WdpI6MfjXSZr4lzkq8evRQ/fKtPsDfB00WbWcJtfFGopet9rMs7jyMu8uWNTrL5fPkgrkYoRV38OOhZ2y0jvVkqEHHJp+WLhenhxmA04q/iCojsD6liyXeVJo+2DRr/deW7hwFRW2a/tegAMQVyMdaEE+QXUX6YwZbrRBWJVj7Pc3UD3E6wTZb3igQom6pdtbfoiZHnSziq315BTR1sIShwejhx4WHK4TMxGfLSSH8MVz+RZa2ZfEjZZ1boBeFk1YzlyKTjt2lziCRMFcZZD8pJ8AW+1ACmqsBohBUBucyfUdr8yd3xDswhr8U4lX5AnH3kgPfBj74MsPvXbg/S5RzgaVeIaHsgt4gNOX0COPAoxhSLtZk8zU5G5eotjOTz6PtR9xRLUGzQyq56DdTAFsTNlm4Fw/ttPJ1yMPr7cWHR/ZVZemch
*/