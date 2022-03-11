/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_RANKED_INDEX_HPP
#define BOOST_MULTI_INDEX_RANKED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/ord_index_impl.hpp>
#include <boost/multi_index/detail/rnk_index_ops.hpp>
#include <boost/multi_index/ranked_index_fwd.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* ranked_index augments a given ordered index to provide rank operations */

template<typename OrderedIndexNodeImpl>
struct ranked_node:OrderedIndexNodeImpl
{
  typedef typename OrderedIndexNodeImpl::size_type size_type;

  size_type size;
};

template<typename OrderedIndexImpl>
class ranked_index:public OrderedIndexImpl
{
  typedef          OrderedIndexImpl         super;

protected:
  typedef typename super::node_type         node_type;
  typedef typename super::node_impl_pointer node_impl_pointer;

public:
  typedef typename super::ctor_args_list ctor_args_list;
  typedef typename super::allocator_type allocator_type;
  typedef typename super::iterator       iterator;
  typedef typename super::size_type      size_type;

  /* rank operations */

  iterator nth(size_type n)const
  {
    return this->make_iterator(node_type::from_impl(
      ranked_index_nth(n,this->header()->impl())));
  }

  size_type rank(iterator position)const
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);

    return ranked_index_rank(
      position.get_node()->impl(),this->header()->impl());
  }

  template<typename CompatibleKey>
  size_type find_rank(const CompatibleKey& x)const
  {
    return ranked_index_find_rank(
      this->root(),this->header(),this->key,x,this->comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type find_rank(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return ranked_index_find_rank(
      this->root(),this->header(),this->key,x,comp);
  }

  template<typename CompatibleKey>
  size_type lower_bound_rank(const CompatibleKey& x)const
  {
    return ranked_index_lower_bound_rank(
      this->root(),this->header(),this->key,x,this->comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type lower_bound_rank(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return ranked_index_lower_bound_rank(
      this->root(),this->header(),this->key,x,comp);
  }

  template<typename CompatibleKey>
  size_type upper_bound_rank(const CompatibleKey& x)const
  {
    return ranked_index_upper_bound_rank(
      this->root(),this->header(),this->key,x,this->comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type upper_bound_rank(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return ranked_index_upper_bound_rank(
      this->root(),this->header(),this->key,x,comp);
  }

  template<typename CompatibleKey>
  std::pair<size_type,size_type> equal_range_rank(
    const CompatibleKey& x)const
  {
    return ranked_index_equal_range_rank(
      this->root(),this->header(),this->key,x,this->comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  std::pair<size_type,size_type> equal_range_rank(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return ranked_index_equal_range_rank(
      this->root(),this->header(),this->key,x,comp);
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<size_type,size_type>
  range_rank(LowerBounder lower,UpperBounder upper)const
  {
    typedef typename mpl::if_<
      is_same<LowerBounder,unbounded_type>,
      BOOST_DEDUCED_TYPENAME mpl::if_<
        is_same<UpperBounder,unbounded_type>,
        both_unbounded_tag,
        lower_unbounded_tag
      >::type,
      BOOST_DEDUCED_TYPENAME mpl::if_<
        is_same<UpperBounder,unbounded_type>,
        upper_unbounded_tag,
        none_unbounded_tag
      >::type
    >::type dispatch;

    return range_rank(lower,upper,dispatch());
  }

protected:
  ranked_index(const ranked_index& x):super(x){};

  ranked_index(const ranked_index& x,do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag()){};

  ranked_index(
    const ctor_args_list& args_list,const allocator_type& al):
    super(args_list,al){}

private:
  template<typename LowerBounder,typename UpperBounder>
  std::pair<size_type,size_type>
  range_rank(LowerBounder lower,UpperBounder upper,none_unbounded_tag)const
  {
    node_type* y=this->header();
    node_type* z=this->root();

    if(!z)return std::pair<size_type,size_type>(0,0);

    size_type s=z->impl()->size;

    do{
      if(!lower(this->key(z->value()))){
        z=node_type::from_impl(z->right());
      }
      else if(!upper(this->key(z->value()))){
        y=z;
        s-=ranked_node_size(y->right())+1;
        z=node_type::from_impl(z->left());
      }
      else{
        return std::pair<size_type,size_type>(
          s-z->impl()->size+
            lower_range_rank(node_type::from_impl(z->left()),z,lower),
          s-ranked_node_size(z->right())+
            upper_range_rank(node_type::from_impl(z->right()),y,upper));
      }
    }while(z);

    return std::pair<size_type,size_type>(s,s);
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<size_type,size_type>
  range_rank(LowerBounder,UpperBounder upper,lower_unbounded_tag)const
  {
    return std::pair<size_type,size_type>(
      0,
      upper_range_rank(this->root(),this->header(),upper));
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<size_type,size_type>
  range_rank(LowerBounder lower,UpperBounder,upper_unbounded_tag)const
  {
    return std::pair<size_type,size_type>(
      lower_range_rank(this->root(),this->header(),lower),
      this->size());
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<size_type,size_type>
  range_rank(LowerBounder,UpperBounder,both_unbounded_tag)const
  {
    return std::pair<size_type,size_type>(0,this->size());
  }

  template<typename LowerBounder>
  size_type
  lower_range_rank(node_type* top,node_type* y,LowerBounder lower)const
  {
    if(!top)return 0;

    size_type s=top->impl()->size;

    do{
      if(lower(this->key(top->value()))){
        y=top;
        s-=ranked_node_size(y->right())+1;
        top=node_type::from_impl(top->left());
      }
      else top=node_type::from_impl(top->right());
    }while(top);

    return s;
  }

  template<typename UpperBounder>
  size_type
  upper_range_rank(node_type* top,node_type* y,UpperBounder upper)const
  {
    if(!top)return 0;

    size_type s=top->impl()->size;

    do{
      if(!upper(this->key(top->value()))){
        y=top;
        s-=ranked_node_size(y->right())+1;
        top=node_type::from_impl(top->left());
      }
      else top=node_type::from_impl(top->right());
    }while(top);

    return s;
  }
};

/* augmenting policy for ordered_index */

struct rank_policy
{
  template<typename OrderedIndexNodeImpl>
  struct augmented_node
  {
    typedef ranked_node<OrderedIndexNodeImpl> type;
  };

  template<typename OrderedIndexImpl>
  struct augmented_interface
  {
    typedef ranked_index<OrderedIndexImpl> type;
  };

  /* algorithmic stuff */

  template<typename Pointer>
  static void add(Pointer x,Pointer root)
  {
    x->size=1;
    while(x!=root){
      x=x->parent();
      ++(x->size);
    }
  }

  template<typename Pointer>
  static void remove(Pointer x,Pointer root)
  {
    while(x!=root){
      x=x->parent();
      --(x->size);
    }
  }

  template<typename Pointer>
  static void copy(Pointer x,Pointer y)
  {
    y->size=x->size;
  }

  template<typename Pointer>
  static void rotate_left(Pointer x,Pointer y) /* in: x==y->left() */
  {
    y->size=x->size;
    x->size=ranked_node_size(x->left())+ranked_node_size(x->right())+1;
  }

  template<typename Pointer>
  static void rotate_right(Pointer x,Pointer y) /* in: x==y->right() */
  {
    rotate_left(x,y);
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  template<typename Pointer>
  static bool invariant(Pointer x)
  {
    return x->size==ranked_node_size(x->left())+ranked_node_size(x->right())+1;
  }
#endif
};

} /* namespace multi_index::detail */

/* ranked_index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct ranked_unique
{
  typedef typename detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::rank_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_unique_tag,
      detail::rank_policy>                                type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ranked_non_unique
{
  typedef detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::rank_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_non_unique_tag,
      detail::rank_policy>                                    type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ranked_index.hpp
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
*/