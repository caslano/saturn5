/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/not_placeholder_expr.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
>
class hashed_factory_class;

template<
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct hashed_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory_fwd.hpp
+sZ4kZhHXKktG/uBXG9Ldldo6A56cHh6+it8gKODowMXhkQwyiHSVCxpeefCeWZX/ijIw4On6CcXqAbCvWcO44IpUDLXG1JSwGfOUioUzYAoyKhKS7bEH0yALijkjFMYTKa34fhPFzYFS4vGz1ZWoApZ8QwKck+hpCll97WbNSk1yBw9oP+MKY0+K82k8DA8BU3LlWrcGBCEKwnknjBOlhiOaCi0Xqvf+v20Kjlm0s9kqvppS4VX6NWLrG4RzYpsQa41aAmVoi6Y8y6sZMZyc0eKcHFdLTlThbuDhQFF1pclKMp54w5NGVV1ChSihi3XnIQ1omfa3JQUykTbFHL17CDS2jjKq1JgOKQFz2USiXehEhkt7XlLRBulYdlS/kbJdtgzkAJRQcePIIw6sCSKKRduwvhqMo/hxp/N/HF8C5NL8Me3jb/P4XiI2mAYtQT6sC6pQhQlsNWaM5o9C/5DO93x4isYzGejyTROZoE/HPqxD8fQOfwF/qoE6vrwYwc6nC1N4eHEOz7xDnDB/EooUdtEUW1KjB9Uk0KH0RWM/evA+c7r4gOkldJYmbVkAplGVSpVF8LQXVKSQUo4X5L0q/UT3Y4n0yiMnJ+YSHmVUTg3gWsRFp8cGyOVuP4ST9fswH6B8uCokpdYXLiX
*/