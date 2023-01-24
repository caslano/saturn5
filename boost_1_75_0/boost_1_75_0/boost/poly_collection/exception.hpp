/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_EXCEPTION_HPP
#define BOOST_POLY_COLLECTION_EXCEPTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <stdexcept>
#include <typeinfo>

namespace boost{

namespace poly_collection{

struct unregistered_type:std::logic_error
{
  unregistered_type(const std::type_info& info):
    std::logic_error{"type not registered"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_copy_constructible:std::logic_error
{
  not_copy_constructible(const std::type_info& info):
    std::logic_error{"type is not copy constructible"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_equality_comparable:std::logic_error
{
  not_equality_comparable(const std::type_info& info):
    std::logic_error{"type does not support equality comparison"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* exception.hpp
BCP7lqslY7kkWPiQ9up7AF7IAcqaMtah8kuG4K2LvvDDUbeQaE0J4BWIDkVCtngzDZnZERTqgbk/3VnkOFV3YRWgzN2l4xduFCYP48oqPu/dNgiRv2cF9mv5ENJu6tDfPv5pn7Zr+/yRp2+Dm5ci4NqDNuBa6JFlWOjxQ3zN8fYIYWcO8JJbcWDTVUu0XbJ/xqEBcPbx8n6NTZyw7O4xMQKM1Ojf39C4vL9Ohieco1md2HHG8Ecj/Pqd5+Ezens+PzlTLCuDTYa2Z6SzX3y6E9OtnP5JTchb2j7VuN9XlhCAWOWHDpjZR3vkC6i3GunncM7t1UnXx6r24YxIV/Hg+w4rzTbUaC1j6uXfaGBkfKc0tJ3OXHauUGMfIHB/v1K1poLGuE67QNkg79q4x0aTJzHvvwAffER2W+wz7idEm1o91tiIIpGLivNICWrn9pULSBPCt2fGC4GsxbmYeA9rkFzQ2Be2nuQXgPEqmANPL5/AB6avAENhh3eWGJ57eVIjUbeQATzIOh49mMHc7ifYdpZ3mtI70Mw4FRocHP/Hsaeig46URo53TlHIVh6Szo2pz78DivMPe4u91JI76pEMlRIuoptCk06lmzg6/a+E0tDumx0t+Xzu9VHmpA/A9qJr1RPNlc7lZEK21LfnOaj3SPI/WDyBIVP67X899ZT5PzeP1rE0k3O0s7B0+afu0QY63siJBgsxDpHaisXo
*/