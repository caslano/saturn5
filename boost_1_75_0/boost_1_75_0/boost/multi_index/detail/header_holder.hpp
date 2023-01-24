/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP
#define BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/noncopyable.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* A utility class used to hold a pointer to the header node.
 * The base from member idiom is used because index classes, which are
 * superclasses of multi_index_container, need this header in construction
 * time. The allocation is made by the allocator of the multi_index_container
 * class --hence, this allocator needs also be stored resorting
 * to the base from member trick.
 */

template<typename NodeTypePtr,typename Final>
struct header_holder:private noncopyable
{
  header_holder():member(final().allocate_node()){}
  ~header_holder(){final().deallocate_node(&*member);}

  NodeTypePtr member;

private:
  Final& final(){return *static_cast<Final*>(this);}
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* header_holder.hpp
YKjTmTSBCs5PiFcd16QQV2vkiaDR3QFx/yu6a6pl7OkaVMtY4926Vn7trULfE0k8Vj6XtBQXi70ojj04WUGYFviIPFeSe9iL3hW8PB7NmPFYJGkgpkbPHW6zKB/7w6i3/C7Mn2Wrl4xjnTJt5PfWmGujf1s1OegMyVfmZgp/Nhp0KpksMrgHPhETkUYVOr8aodlxUR+1dR7OhtWDe0YQ2buqJWiS53SQz5J03hHf2FZojuSOHr+9SOUqRkT+PknR9v3xLZTfObKEyV9u43LKRAI7XqXJFOFXUYjutVeTHuCqq7XrP/Xm3F58/ca+wXKGrlt6ydEivW+X0pycMXsjzpvFdxcKHOnyfKQ6nBr70C2tIe+WJU1TY/O33dhb+4b43mY+FaQTO9q5JZ3Yvbf8HdguppPY+LpWwZv+SlN1F8M7N66Zsf1H5xbHdlVya8f2Gn1s5ya3BtbXX25ubPdeqY3tjiubHduiTi2NbX1SK8b2GjG2u5NaA+/vLzU3tldd2czYHr24xbG952+B1MY2QR/bq1oFq/RSc2P71BXa2OZe0WRsg/Y4cSbgDRqpaMA/f7NmQ+kg7yEy6ZJ/E+AzufRN8X+CgBecsub1xJ8OBarV5yi3ObCGBhHpbP88lAqwiNrSbmI2XDcHWw7MnygsB/SNYxYHzYd5R0NfWtKrWfnRc1GL87JuQGP5UZuPTJyPUcAPkSWrjrcGUG4b
*/