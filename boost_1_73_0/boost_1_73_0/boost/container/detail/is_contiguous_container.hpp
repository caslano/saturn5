//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_contiguous_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_contiguous_container
{
   static const bool value =
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<Container>::value && 
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<const Container>::value;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

/* is_contiguous_container.hpp
NkvZh9EkCJcCyC1hnCwQjigolarlh+EwaxuOmQxzkclhtimFW6rlv7KaIZslWYOoFSgBraQOaHsHliJnhV6xRHhYtwvOZOlsaSFglQ9FA5Jy3odDV0ZllwKFuK+Woy2hRvZM6UWKSmq0VSmWO4ZY1j5Q0TYVwmFZ0C4XWHgH2iqnjbE3hdig9FU2JX+mZVvuOYgKWYHtxRDENiyIZNKB6yA5j64SuPamUy9MZhCdgRfO+ngXQXiK2mCI2gC9qxsqkUUDbFlzRvMd8B866ZabnMPoajoOwrMojRNvmiTILz7zp2kSXPrwBuzD9+C1N1riv9pgc7bQGoB37tu37ms80G8pJXKd3lDFqkLolqOyJAaPzyH0Ln3rKYT5K0DHrvpsSbEZivFe6o1UsFgrU+KNnE3UeBZGkziIrZ9YlfE2p3CseXTyLD9ZBjETeP6I3kB/gv0SlcNRQE9QQ0mKVut/XxOr9z4a6FM/Hk2DSRJEoTUh2CcCtWCV0grCodn44L5n/JCao2dY0kxUOSqC6bkQX6FoOq1aUukhfS59PIC+B26nw74C0poXwUM2k6m/k8vgzd68mJhxMcP9UG69kbS5RfoVpbkeHysjPGs5Ud1XFGPLlWtZ1yVFaeN7zhp9yyN2ITgXK5o724AmH0qy
*/