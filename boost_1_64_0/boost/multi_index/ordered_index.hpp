/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_ORDERED_INDEX_HPP
#define BOOST_MULTI_INDEX_ORDERED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/ord_index_impl.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no augment policy for plain ordered indices */

struct null_augment_policy
{
  template<typename OrderedIndexImpl>
  struct augmented_interface
  {
    typedef OrderedIndexImpl type;
  };

  template<typename OrderedIndexNodeImpl>
  struct augmented_node
  {
    typedef OrderedIndexNodeImpl type;
  };

  template<typename Pointer> static void add(Pointer,Pointer){}
  template<typename Pointer> static void remove(Pointer,Pointer){}
  template<typename Pointer> static void copy(Pointer,Pointer){}
  template<typename Pointer> static void rotate_left(Pointer,Pointer){}
  template<typename Pointer> static void rotate_right(Pointer,Pointer){}

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  template<typename Pointer> static bool invariant(Pointer){return true;}

#endif
};

} /* namespace multi_index::detail */

/* ordered_index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_unique
{
  typedef typename detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_unique_tag,
      detail::null_augment_policy>                        type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_non_unique
{
  typedef detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_non_unique_tag,
      detail::null_augment_policy>                            type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ordered_index.hpp
nl0rcpr+lQ2eTq1LIv1MH+lM2cz1Gtnj+x+7cH3ZZ67a/3e9/8E6Oj8zRv3uWGnhWpEyXy4v6rkAsaw+E9+LnNiO5Ey8KntJ3S98vUb2uI0vddIgsUIp2U/rZ1N+ji+o3Lz6x0GcAvQYudxjb/jyNCuLTIshouCPZoe+t/+A3EsuAi/UpLqfpTcWQ/pJTn9cb/Ue03XffRfs3VTfbsYuv2lNP6zoqjtpKujcGAf8rbVerRBEH382oVXSSYwxRauCPFQODDdY7LnFbUAHrbCaYCjtoqZJqbLbrT1+jMR7GzdoVb9Cv25fQDooWkM+d0J/h0UGi4L0dzI6FgfzdLvtSB/Umhim+Wqkwdgf8hzdob/jbgZpL5rUtI01PIOoaXuuATTIf2VVkAG055eX5+b7p4i/PoWRNSdfgK0vzUOW5E3KBczTja+p6Y8bUJ+HZ9T35SViD6nF21ExRsp7LcANpF4yt/iYzTVoIKSdHdI0CdM9vAtoWoUajvfji4a9o4hTx8qu3icFjHfiZ+uFVN49CjiwcEpPePmD+B2DF1GcDQtpkqRulop5OKKu1IyT83IpVYf0j30sDGU3V38O5A9MUz2Qwc6+Km1WaUhqzvAddbbTmC6RvtxBOpkOyd4c6WxKRtvC07dxOjc7kfgR4xxn5mNyAul02kb6aU7X6WC/K7cDHVqjShp8PTK/nAZdO89Ae9wOoNP+h6ZIxHwGMUYfhX1cjUl3jsDMsRZCmb9t4NG8iZiHTzYxvVXoJqR8TQx7+/HwazTp/a5shG4VJ+vO2rdlC04ZjaS+VE8jKHPpmoAdPLpZZ3Pr4MwRy8hwvIyYv2uZGGbCxXKeQ1y7XXVql0lH8y1izjIMt72iX9JrA0Z9hbxif8F3LSZ9sCH3NdgdcJzf1ZhffNcBh11XHd8IHAuI+ozt1AE4T8tKHdUPvj1Mf4P3U4aftrd1gEL8B+HayWinui22wFc0MbCGo/w92yi9fsujeYc0yH5f3libOwEXH+h4HkeM0qMXKwTKLyc0Hc/mkHYOaZgv3NO8bIHtwzInST2vjIRc5OaesNw7IU/cNs1z2bML3DYWFKWfZA7y4Cadxl+gPIXIYjvwQsdDHjm40AqF8Rd43sIyL90sS4Y8j4M7kfyuzoUFvi8OPCcIvMQXwKAUc+nEjoe/72jefxq8rmf7SernNW9vdQvePYtGurJSyiioWZVNAA+L6f2Mx8r++MEbVnuSrDT2LPX9jAtIH71neTvZs0gg7lkwNscCu0fgpYEb2MrXRbS5KmuFOp6EswIYO69Q6UIJ6v4u71HA/yk9gZwVvKPqW0DCPLkd+A7dWX3XkQ3x/oWKSbAb9hbKa7Mrly+tQeIZzfkPTiK9d6o7kFVHceiD6RUfasctrsFp4/wyfU989leIfUB3oSsv7KMjspM63eMXEbMyOCU9ClRSQR/YDyoAyvo94iqPx1rk2Nh+jTl+ATHwdkkNwH5PjUGc8w4v8DmvLF0n8tyrn/NWBlUMfTm/PR7mt+zIXLGx1O1LZ/PWhuwIJzYrvU/Sn1TTEy+JFqUyD+49+jBPS9pTKe8Duo9dW1D2G7ho66urtmNVGk/TuH5Phm8Dx+7D4Oa3kfTnUDnEP4cWAjKeV2OUG48+y4qiv2CYT1mpvfWeBEBGgA5pvLam82w6S2vysqLGPLnGoACZQZoSYJ5RYyL1Kt5aXTwie8P8cq7PqKDO3lpjPOXds+5dtS75RV4OlcM7w10O+V2umEAiNVDlr3J/A8O8KutPaxnW5saSzB0gMQ3I4y9rOjTnKbkwmRUCeXxfhWEDYKxu1x+Z7UXqu4BOUqfzRrOcztrqBibD2w3zMBSl0npXa145DtI=
*/