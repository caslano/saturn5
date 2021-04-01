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
uYLJ1fw1KeWNgU/z1Gupiwby4mnToqbunSTDCnx6f7emhW6Aao8Y+fm784QXNWqgMUrN0Mzw9DqxFrznMAnLabcaBWn9NSXUf5uNifvQ7Uvu3ACDYcRiK6qZvViXPlzU2gBV43C7fZM9ebu3sGxWGthy9dao1AasuM0ghxiAETNDp3uSben9o97cHU6CWjOIFe9daioJHyT+Cj1HtDW2MHvWPdBbI0Ft7FS3DRIjiId8VF7XabfX4rp2JsN/Zz9TztLoTp6ovb13fY2xD1E+v06XSMkuEuJA+UdUJXMK9qWwiPywQW85s2HZzDu0Ul2Rdjp8U9obCMhHpjoaySvx2nxVSnNV9IvYplV9t0EcpCUNGj6wdb1k+H+Q0KSH6JOXf0wji6XJLsRLKv4ZauHMiXFe1p5sWrNiGJe+HcQCc/4y4UTRdHZP1oSTuH5mNHFnnklIwzcduDs8/WxVXdiCvmkNVlVAyCgeM/H4tQyYAkM8zywXCdVeWFHGa4bSh3Nglc9ElvjhyfLDktNXx2z5/rIZTm2WR0zds4aS61NEcE22aMgRqRj0RdUsKQ==
*/