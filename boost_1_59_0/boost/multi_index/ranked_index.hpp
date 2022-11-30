/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
  typedef typename super::index_node_type   index_node_type;
  typedef typename super::node_impl_pointer node_impl_pointer;

public:
  typedef typename super::ctor_args_list ctor_args_list;
  typedef typename super::allocator_type allocator_type;
  typedef typename super::iterator       iterator;
  typedef typename super::size_type      size_type;

  /* set operations */

  template<typename CompatibleKey>
  size_type count(const CompatibleKey& x)const
  {
    return count(x,this->comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type count(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    std::pair<size_type,size_type> p=this->equal_range_rank(x,comp);
    return p.second-p.first;
  }

  /* rank operations */

  iterator nth(size_type n)const
  {
    return this->make_iterator(index_node_type::from_impl(
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
    index_node_type* y=this->header();
    index_node_type* z=this->root();

    if(!z)return std::pair<size_type,size_type>(0,0);

    size_type s=z->impl()->size;

    do{
      if(!lower(this->key(z->value()))){
        z=index_node_type::from_impl(z->right());
      }
      else if(!upper(this->key(z->value()))){
        y=z;
        s-=ranked_node_size(y->right())+1;
        z=index_node_type::from_impl(z->left());
      }
      else{
        return std::pair<size_type,size_type>(
          s-z->impl()->size+
            lower_range_rank(index_node_type::from_impl(z->left()),z,lower),
          s-ranked_node_size(z->right())+
            upper_range_rank(index_node_type::from_impl(z->right()),y,upper));
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
  lower_range_rank(
    index_node_type* top,index_node_type* y,LowerBounder lower)const
  {
    if(!top)return 0;

    size_type s=top->impl()->size;

    do{
      if(lower(this->key(top->value()))){
        y=top;
        s-=ranked_node_size(y->right())+1;
        top=index_node_type::from_impl(top->left());
      }
      else top=index_node_type::from_impl(top->right());
    }while(top);

    return s;
  }

  template<typename UpperBounder>
  size_type
  upper_range_rank(
    index_node_type* top,index_node_type* y,UpperBounder upper)const
  {
    if(!top)return 0;

    size_type s=top->impl()->size;

    do{
      if(!upper(this->key(top->value()))){
        y=top;
        s-=ranked_node_size(y->right())+1;
        top=index_node_type::from_impl(top->left());
      }
      else top=index_node_type::from_impl(top->right());
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