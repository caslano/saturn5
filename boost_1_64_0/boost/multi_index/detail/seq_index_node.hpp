/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* doubly-linked node for use by sequenced_index */

template<typename Allocator>
struct sequenced_index_node_impl
{
  typedef typename rebind_alloc_for<
    Allocator,sequenced_index_node_impl
  >::type                                        node_allocator;
  typedef allocator_traits<node_allocator>       alloc_traits;
  typedef typename alloc_traits::pointer         pointer;
  typedef typename alloc_traits::const_pointer   const_pointer;
  typedef typename alloc_traits::difference_type difference_type;

  pointer& prior(){return prior_;}
  pointer  prior()const{return prior_;}
  pointer& next(){return next_;}
  pointer  next()const{return next_;}

  /* interoperability with bidir_node_iterator */

  static void increment(pointer& x){x=x->next();}
  static void decrement(pointer& x){x=x->prior();}

  /* algorithmic stuff */

  static void link(pointer x,pointer header)
  {
    x->prior()=header->prior();
    x->next()=header;
    x->prior()->next()=x->next()->prior()=x;
  }

  static void unlink(pointer x)
  {
    x->prior()->next()=x->next();
    x->next()->prior()=x->prior();
  }

  static void relink(pointer position,pointer x)
  {
    unlink(x);
    x->prior()=position->prior();
    x->next()=position;
    x->prior()->next()=x->next()->prior()=x;
  }

  static void relink(pointer position,pointer x,pointer y)
  {
    /* position is assumed not to be in [x,y) */

    if(x!=y){
      pointer z=y->prior();
      x->prior()->next()=y;
      y->prior()=x->prior();
      x->prior()=position->prior();
      z->next()=position;
      x->prior()->next()=x;
      z->next()->prior()=z;
    }
  }

  static void reverse(pointer header)
  {
    pointer x=header;
    do{
      pointer y=x->next();
      std::swap(x->prior(),x->next());
      x=y;
    }while(x!=header);
  }

  static void swap(pointer x,pointer y)
  {
    /* This swap function does not exchange the header nodes,
     * but rather their pointers. This is *not* used for implementing
     * sequenced_index::swap.
     */

    if(x->next()!=x){
      if(y->next()!=y){
        std::swap(x->next(),y->next());
        std::swap(x->prior(),y->prior());
        x->next()->prior()=x->prior()->next()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
      else{
        y->next()=x->next();
        y->prior()=x->prior();
        x->next()=x->prior()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
    }
    else if(y->next()!=y){
      x->next()=y->next();
      x->prior()=y->prior();
      y->next()=y->prior()=y;
      x->next()->prior()=x->prior()->next()=x;
    }
  }

private:
  pointer prior_;
  pointer next_;
};

template<typename Super>
struct sequenced_index_node_trampoline:
  sequenced_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  >
{
  typedef sequenced_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  > impl_type;
};

template<typename Super>
struct sequenced_index_node:Super,sequenced_index_node_trampoline<Super>
{
private:
  typedef sequenced_index_node_trampoline<Super> trampoline;

public:
  typedef typename trampoline::impl_type       impl_type;
  typedef typename trampoline::pointer         impl_pointer;
  typedef typename trampoline::const_pointer   const_impl_pointer;
  typedef typename trampoline::difference_type difference_type;

  impl_pointer& prior(){return trampoline::prior();}
  impl_pointer  prior()const{return trampoline::prior();}
  impl_pointer& next(){return trampoline::next();}
  impl_pointer  next()const{return trampoline::next();}

  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }

  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }

  static sequenced_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<sequenced_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const sequenced_index_node* from_impl(const_impl_pointer x)
  {
    return
      static_cast<const sequenced_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with bidir_node_iterator */

  static void increment(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }

  static void decrement(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* seq_index_node.hpp
TZbiXqXobBMJzPybVyiNdamLDe9Vvki6Fh1qn4M+IivH7FzZXeodgkib+I1ZvgOzq6FdyBrLNesZ/SH4dc0SaJfeNjxPfaoZvqtAtkC25xP6/1TqQs0wdvvaks/npYXl8FDfkuxnE5vtyhbl9muJugyzibI2ZUfXr8a5cNhYm5juoexK3tfqt1eTbcLC0sXNf/taPauziZaeym4d3DtJPQeyiTIWZS3n9VR72MTakp+FSMt48sVPxECWjlmpA4VzYuyS+cEM+wQvlHNMWnizNlgHQ8lSM/vz5rWXqCdZXfl+1mP6w8a9zii0yzqbsGrJ9ijpOqB/E8QXu57SCWVPFtbvjLrE2URaq7J8XU6obxFusiXfq5T2b+OZeJYlttpEO7uylB2aBCOGfTbxQJb3kP6w4XmqvYgh3iYimP3S9Zt6D4JsFLMq6WerZ1L7bWKuVdnBkcWGYFwfsYlZQtnZK8XVu/VkfzGrXmDHaPV7GZs4y+xpzdgJKO8YHf80ZYO3RtxFDCdsYoeHspmXiiD2MJdNDGJ5XrcmrkB7uvTlZRtyLhDted4mQizKll7viD6Kv2gTJ4Wy8aNGLoRdsomPrF2OZ+3ZFnZdn+7T7Rc3YTdsYi+L758FRcPV+976dJkr1fyszndtYhOz56+C+qpzTJu4wWzOj5vd1P7zNrGHxTfxxUO1v/4DudZJy+ubORJ99NCG5+gPksbE9i6X0EdkwqpsdpOKHdEPT22inlCW+/hMK2In84YZnvHpTP8eRAKZF0y/l1Ai2W/MYnIXeIW6PLOJysza7P4V9zjjyFLCDM/Dybowa/K+0HO02XN9XZ6meYw8o8guynZJ2kMsS+B9dV6QaMPvDe/RHwbu3XoV6ci8YfrYo8nCmBX07fcLYicryiwh3xi1D8EbvWU4escf5ZHVZZZoq1UBbU32p6as9PWimA+x72zCXyj7ZdqoOehbspzMqnZePA31JDvErHberX/B3ttEKWZOUaUV2uyDPAZI82t98jfUk2wKs7tTKqlzqf/QMYDFcCHllEPqXiytrZ7K+sTtPY41+SetdZqyvp9dJ7HWaXbRl5VX7lDwA8RO1pHZX/MGF8AYtNhFSmbHPjbDuVQUWSVmkb/tqa/um9p1/dfCcvcG6mm1i5bMAiPzjMLcJCvI7N6UWHUtSlaR2Yd3ndTv1TzsogKzyl6Z1bkbWTXe1i2sY9APHvry2l9cmQFt5mkXXVl79qxzOQT9brOL2ULZmfMv26h7sXbRmFnW6/X+Rp4Ou6jDrPWmYnMRO1kXZp1++qh92px2UYRZid1d1f1kshXM+gVPExiDXnZxhNnLHn+Wh3nbRTpmdVz7f0ee3vrylpxopfaEJdvArNf5uDNoax/9WHq/tovagyGFXexj5rEvEnURKe26+XemS5WO6Fuy6cyOPumAY2oimRfMcM84lV3U52N+5IVFGLtkAczeNBiu9jIhO89syMjNuRC7r13MYNYh+2z1O+/UdrGa2epV82eoe7F2EcXs0vL1aGsXWU1m4Wl8jiD2tHYxgFlEYoNOSEdW3KLsVe4zt1HP9Pbke6rSXn87oKFd/O3iF2b++b+swnwnK80s59RTvsiT7H9r3d2ka+bZ5dW+2WRhzN4F7/mKdslgF4uYZTt2Ij/iC6AYmA3s/QfGRDTZ78xm/nin3vMgS68pm55nxHe0dSY5PqVdupCuLOZRZrsow2x+/3/Ut9Mzu48vnqwKs3oDe79Gnlnsohuzv3OVRN/Gke2RlpB0/7rBj6Noz6x28Se3sisRe1CgXAukDVyQ9S7yJKvF7FjVs8GYY0F2EWNRNmGd+j1XWA672CaUvVqbshjaLKdd9GL2rMIWtQ8=
*/