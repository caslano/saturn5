/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_FACTORY_TAG_HPP
#define BOOST_FLYWEIGHT_FACTORY_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a factory specifier:
 *   1. Make it derived from factory_marker.
 *   2. Specialize is_factory to evaluate to boost::mpl::true_.
 *   3. Pass it as factory<T> when defining a flyweight type.
 */

struct factory_marker{};

template<typename T>
struct is_factory:is_base_and_derived<factory_marker,T>
{};

template<typename T=parameter::void_>
struct factory:parameter::template_keyword<factory<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* factory_tag.hpp
f5d8/eIDbRlTi2HXc+JBifEoppYl84G+dZdQ5li2byeqfPzSkQwac4XkSs+JcwUjZv64sovOJ9S7pSTU9njEI4T5z0wTOKj/I2T/Nk3DQSCz1AeA+KNWb2x8GnU09XQCqrbG8SP153QmO6fR2DZEPyxRVlhbI7XxiAJH9ohCd7Lku9moz3V48wpiAonobevw57uUw11pxW2hiVEN+lo4c5EhqLsp0cTaH1Pg6DWG7e1z4ayRYui1TbkixWTyDwr6YqjkzzcmmlRxedYIg6Aw1GWI07Ifp9BsLzKZtHN3zLixmxvZ7q3co59CxlN+6aQDVTeFu4YLRXwbepOXAR4G1Lt4Ng5yOQYbFgfEHZ955YUgvex1I3cxcGSPK3aPMArMpfEgyn/CFfJUbv+tQUra51tDgXh1Kq4dDlPRnhQKyblNTYldNydLLzHa/7UcW+TF3RoJiJPyHYXsBwVgDcPcNdCDD4fBxChkoTADLBR+U+fl9A3GeQGh34Q0MTEJN6gTMzq12FJ+BVCD4/unkddFjQMTj/j71OQzdFfg9E9lKK86P/svtx38Qy7Pl3vwnGUUYwRmLc5g0tDDIZ9yeLfGsDqenRBQJB1bAi2kPOQ0Mv0O3xOnhTIC7O28VacdZHi33+HHaJS7lZ6Ixeokv2RTxvVJNK1L53ip7alzQfgmQy3ZG913Q047myyl2bNrZkUGt/mkNEAvOZnTL3F3
*/