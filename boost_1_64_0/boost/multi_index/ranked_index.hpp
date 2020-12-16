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
y7HnEbQcjvB8zw9C36a8emD0KlOF7ups/T78CK6j5VYYZ1npczm8GKY96uFMhiXs0C0Kt8jEahd6xNpqF1c+tt9fZ3yyLcoiigo3FGpCmB/OCWT5p/3guY8w6i+KwqT0LeDHbsTnFDwDeDXlvacfWo7lB37FKTd6FZrEtDnL0nJE6theYpWp5ni8zDBcHgIHbGY+P2Pw+k4UR2FcEN4NeD+/voYKFubzPOWdDcMgLALPqzhho1PjB7GOYwN4ui92Mz+IM0dwFyewCvVlsku9AeSAxh0k/pIfSe2FQWSFSWJXji7rVVzh73dQ61fxGI/zWiaJ6+eO4mBzPl+nj9F0DuZ5WsrOA2UkM5pO4zjFliLxAy90gwTBylso0VR1G2w80rBrpV4WJq7iUwtq5VCWHhgd0P30uYw3EGFhZ2WQEl42gTbsYq8z+OMyy9JG2o24slivn2D8lihKJ7fSqCo0G6c8dtN3KF8m0rQsozhQXOa21EJfxbx+Xc8OLcuuePq9x4L2iI1Cx8euOSNubuGUmZXBWMTxC/8gh64C94mM1xep59iSPRDIV0V+5FMh6Xdzps/twA/SMBbYJIwT+d5r8CWR5UdZkQpoiqZaiWU9P2fYtNMQbDShUFG/+epj2pYvMd5YpJI5zmWrbKGeKSE03vVxdh5ZRImfBmVCRBA20o9vd9w4N80zK4/cnDGqjsRT1nkXjD8SXh4Ublhg3kfOujLvtl4rDBlZ5BSZn2biymolyjjNZKTCK+0scQKP+dOF9oPAPvXMc9qwNb/JyEfgZp4XudbQly5qAuoIccnYS36G8qci8KzEtspkyD7cVi37ejweN9bsoCx9KylZHFhsfbViz9fnl2zN3jfP1+zAKaKg9HImB1Yx5K9zT+xYYp7rQXEcxmVpJ0wG18cwP1QPWp43zhyi3ErijIvBcciWmb6v51cmoxCun0Zh6ToNIaifMjkW+j2b53p+WWauB22iXjOxEdnVY+ncPLcJpFnoWo6LPGx3QOwu35jnc5ZdBkmZe7ZgGhdnx/sE89ymAKeYrpRh5lJCN8HH2N57yj5/XeVjLDtiBIAD+o0kfff1kU5clHEfZB8gPsgkULsgw3vI4qN4d3rkiTC7l31ua7yErN1Gy8Y7zvyUlPpzKBHTcCslYeStHuLaXQ9RmWcQ23S5Bbhcr0Elvwvoe3nhpd5//d6K+uT5YGfUofIQ9/AO4EYekCHuAseZJ2F4x++D21pxpjsBxM+OI370oQnBT01sgW+5z3yZ49sPQQj+2dsRP/pwgdyxLneMxpsv1O+M8WM4j2n0H6Nv07bCrgOYtOVkK1a/F0LcVxDXvBRHcUvXJDjz4hnBHb2WxkGBeeKDMRLDSeHmuwN8vyn3c6Ss7i6gj77IoNoV/YkC9gqHfwR//Dpb4LEXIx7mu3b8BhOP+KfsHolH8fQt0rOvNxqPscz0/dbrayy7XIGy3BsQOvQMdYIK6xS+/Mf7nzN7TCxC8F7nJwjGvAzC/GbdUOOMZ80E8zrENNwbYv4X90rMVb7LOg/Yq3hnpcuyfCPEt/lMQtx5E2e+H65xSzcehcOkMa8XAftfvNdavonEX9X7q/r9Ma4t/PYRXVemjHXFde24yP6L2PpqXeEx1D7Uab/wZM4fGx3AjlyeUebtto3E4dDH9McNbHOOwPrZh/XDbtKxd87/LPg7i8S2nDyM/ut3Fncg7yw+3BnhkpTOmR2OM12S4hy8jeHM4rL31efQj1t3sZqywYo4bLvZzijM3InHz+WRS+OJbokt7Jhg37ttK+zGabpWPGWcY7WDa0DTdW9iguPUFFPNQpg+lr0FqwXie/DtrRgsOltzR2IxaSzP8o5R2AU=
*/