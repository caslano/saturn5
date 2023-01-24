/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP
#define BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
void adl_swap(T& x,T& y)
{

#if !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  using std::swap;
  swap(x,y);
#else
  std::swap(x,y);
#endif

}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* adl_swap.hpp
ovFU4r2OV2eLjaKWFkd4uuiOFnmzbTQB6Zpf7x7lvTbIfxREbyTt6TD69sI+RE/2IqnByVSS4lAtYC+8CJW1RSftxXtJmKkkJu0SHompuEt/+uNQIcylNsocJTg7xn9R47EhG/u1xs9iY5vWOClk44e0xmgdXBeuNW4fsnGK1hgFiHURWuND60I17qw1fhkbt9Earw7Z+GSYaIyZoKCFaFwYsvFWrfFSbBylNR4RsvEy8pp2xfVf11ZreF3IhtNFw6R17bSGESEb3sevB9K1rr3W8uDaUC1vCqOqH+s6aM3eDdmsMyVd+0omN5r7QjaptxIpQB9VPxcLj7dqxcLHx410y1+QPm6f8vbF1NBpNEwSDY0293QBxl7XXRAlIlIYsIH4SUvYQHGj+Nw9s22au2fPecLdk/EvHe+gm1M7ij3sMzuotNMldGpUDNftWFa4gdkJ6p4I9brvZ+mvKy0Ket3RWUGvWzcr6HXvzGrmdc/CDeFOYkRsbDjC+ydL8P4pdZServ34OGb0iU/w38jHKJ/Jr7CnMsS6AbPYO2ndOMrS9IVy9FFgLso74/D3DfpdRr8v0e9z9Bug3/n0O4d+p9Gvj36fpN9x9PvwOLFXy4uLyhgh8svBxn6Xwa4636dt7Ht65V/YszNNnjELCPhLydq2pydq9ams99h6YNTpW8ivZCHy6WFb2K9kGdX089aTsRD3OUYhvw0kBI+F
*/