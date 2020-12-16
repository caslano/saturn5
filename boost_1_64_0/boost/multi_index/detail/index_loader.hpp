/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_LOADER_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_LOADER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/archive/archive_exception.hpp>
#include <boost/noncopyable.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/throw_exception.hpp> 
#include <cstddef>

namespace boost{

namespace multi_index{

namespace detail{

/* Counterpart of index_saver (check index_saver.hpp for serialization
 * details.)* multi_index_container is in charge of supplying the info about
 * the base sequence, and each index can subsequently load itself using the
 * const interface of index_loader.
 */

template<typename Node,typename FinalNode,typename Allocator>
class index_loader:private noncopyable
{
public:
  index_loader(const Allocator& al,std::size_t size):
    spc(al,size),size_(size),n(0),sorted(false)
  {
  }

  template<class Archive>
  void add(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
    entries()[n++]=node;
  }

  template<class Archive>
  void add_track(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
  }

  /* A rearranger is passed two nodes, and is expected to
   * reposition the second after the first.
   * If the first node is 0, then the second should be moved
   * to the beginning of the sequence.
   */

  template<typename Rearranger,class Archive>
  void load(Rearranger r,Archive& ar,const unsigned int)const
  {
    FinalNode* prev=unchecked_load_node(ar);
    if(!prev)return;

    if(!sorted){
      std::sort(entries(),entries()+size_);
      sorted=true;
    }

    check_node(prev);

    for(;;){
      for(;;){
        FinalNode* node=load_node(ar);
        if(!node)break;

        if(node==prev)prev=0;
        r(prev,node);

        prev=node;
      }
      prev=load_node(ar);
      if(!prev)break;
    }
  }

private:
  Node** entries()const{return raw_ptr<Node**>(spc.data());}

  /* We try to delay sorting as much as possible just in case it
   * is not necessary, hence this version of load_node.
   */

  template<class Archive>
  FinalNode* unchecked_load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    return static_cast<FinalNode*>(node);
  }

  template<class Archive>
  FinalNode* load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    check_node(node);
    return static_cast<FinalNode*>(node);
  }

  void check_node(Node* node)const
  {
    if(node!=0&&!std::binary_search(entries(),entries()+size_,node)){
      throw_exception(
        archive::archive_exception(
          archive::archive_exception::other_exception));
    }
  }

  auto_space<Node*,Allocator> spc;
  std::size_t                 size_;
  std::size_t                 n;
  mutable bool                sorted;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* index_loader.hpp
klp+PLChfauhdYeQjfoGinno6tLw/s3QdzaGfTEP3TZ3z4b26xFNnDg1tWB4/lqnq+fRL23u9S8CF/L8bEQDHmHSN+r0nWF/ayAWRulfq9Ph2mYXSm7K/aY6vaeC/m1jA5FyP6+h73SHILSjZJ4wMs/VtK1hfwfy6hiZ76rTz9ttYehvY3Q4UNN5In13RO/uXVq7ohFLI/prkQ4UcKAW80uE/wVIh0PEhn9hRL+KdOUNsgf80IQj+qs0XR+cIGCBtMkXa7oaZzvd9bq9hOH9TEPb7g+6TXtCX5emzT5W09fU8SIwXjAyP1ynd9bXu7u1yJEeXNc0pZDOCrxyur8rltC/9A8jWneYdQZD/XabznPFYC4hJqKYOcCYPD6AGK/2flFks6b/WwvGyMvrAdEuzmZZezU+W6Rt31l11BmEwa0e0WNJI8YH1NS8aaPbfFTntdyF6x3BJbWB9Qxx8tSUh35LB45Jx3+6U0kYlZBnC8BG1nnQ7D0tbaW/v7fefQaMT2lw/6jr53f3xpCgG9K0VVHL82AKWVEHnHFnsPWMerx2DebhFNMdAqQC93bQIpPfXQlmuauadND16gg/UKxRfnMEp3rnrNJ4FXROK8CSwTyaY6q9/iWdHwwrg7k3w+wsK3+o/sVajxBzimCCy9D4kJWuG5Z7lWLUWQxk1ttQZyjQCKTcDyQ4v6uW/v0rIAxkzRtMPI6BtgIQ6sKTGUbP3JCRMDJcQvf0aSeI0BPKvCnzMYJx1l+439szbf0MAEqjn2JK67FRIluTcU58ViNPGemlWpWsqJgAXRBk9PPmgfqpVwL6ozHfyHoZyoKug796m/DcfVNC6Mxdlah6/BT6oV4e8YRqDhpnUi34uAa7TbBqTiFYaQoOfXLF4DcRr7uX4AeGYQnwpvx7I7y/X7/UP7FACort9/wRjwfzoBGLe511P+jGmtANnpFzrZaT15fx3P7lZ+h5ujD9MHvkoH44uxIs627omjZ9fS2rGWKlvpcnd/QFQViJaUUx2FcbLPTOusr9Gb0d9cFfGWqomGvGi/GVhbpAhpPmxrkHNril19Q+/u3eoNPuXFLLPn2OmRr6w59J6N0dIMJdkPSexm/e8G92LvX3pjoPNW39TSgrl9tE/cP6vPFHGiMHTXX6e2FX3wqs9rrK6NC990DlCz/EclriwAYCOpaTF/OeQMMymiKCzNve5UlPVf+APlpx2s7THZlpx5BzS6cIfXqMvrISzI/orUn0hXmkz9h09a9zRP6RSXSQr3yonqLoVfD0oFjVPUaUSNVZ0WOkM5KmhYo2RmpoCfB5Y1S0i78G/mytid2G90I+c+2Irnt7b6iOiTodlYS0z7+Z0l78Ykr78lsIbcj5vvZWStN8OG6v/6DWpeVVry3rAHTwbt+dDf1XhL7a3VM+ENr55M5GF699H+iifX5fueKa1/nW1b1lsaB1pHoq1gmrVKeb+mB1TDrWRRcX8VAPkg541dfLuq/r4mdZEDmZ+g6rvniXSneW1V6asxpAfcF37v0qbXujd6k9rH//y3GlpdXTw6c39HcrenRW+gb/QcA3DA8kvna9ltVcdO90GunYXNqXynxnfly3Z/cyGH0nMH3qU3X65rC/3zs5wt+ZpG+T9AeO0iEZ1yuPoentolMQmsdoL+rvXRjpwTcpDY4Z6ztJ/zL0N3ya0tXF97YOpYL876H0pna03jcb+kZdj8sm/V+Yrutx2ZT12GdMOtZjaGiPQhrWY2jkHf9sTVMe0H21eO6b9KpJr5On+uBPDj5QD76qdQrMPrfXnEPfs/FDv1rTLp94QhiadOCp6vS8txNW6ouD6XGT3rncpJu7otNqfdIyVRyl/6xO3zQ=
*/