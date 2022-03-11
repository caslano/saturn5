//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP
#define BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/allocator_traits.hpp>
// container/detail
#include <boost/container/detail/copy_move_algo.hpp>
#include <boost/container/detail/destroyers.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
// move
#include <boost/move/utility_core.hpp>
// other
#include <boost/assert.hpp>
#include <boost/core/no_exceptions_support.hpp>

namespace boost { namespace container { namespace dtl {

template<class Allocator, class FwdIt, class Iterator>
struct move_insert_range_proxy
{
   typedef typename allocator_traits<Allocator>::size_type size_type;
   typedef typename allocator_traits<Allocator>::value_type value_type;

   explicit move_insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_move_alloc_n_source
         (a, this->first_, n, p);
   }

   void copy_n_and_update(Allocator &, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::move_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class Allocator, class FwdIt, class Iterator>
struct insert_range_proxy
{
   typedef typename allocator_traits<Allocator>::size_type size_type;
   typedef typename allocator_traits<Allocator>::value_type value_type;

   explicit insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_copy_alloc_n_source(a, this->first_, n, p);
   }

   void copy_n_and_update(Allocator &, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::copy_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class Allocator, class Iterator>
struct insert_n_copies_proxy
{
   typedef typename allocator_traits<Allocator>::size_type size_type;
   typedef typename allocator_traits<Allocator>::value_type value_type;

   explicit insert_n_copies_proxy(const value_type &v)
      :  v_(v)
   {}

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_fill_alloc_n(a, v_, n, p);  }

   void copy_n_and_update(Allocator &, Iterator p, size_type n) const
   {
      for (; 0 < n; --n, ++p){
         *p = v_;
      }
   }

   const value_type &v_;
};

template<class Allocator, class Iterator>
struct insert_value_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename allocator_traits<Allocator>::size_type size_type;
   typedef typename allocator_traits<Allocator>::value_type value_type;

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_value_init_alloc_n(a, n, p);  }

   void copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {
      for (; 0 < n; --n, ++p){
         typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
         value_type *vp = reinterpret_cast<value_type *>(v.data);
         alloc_traits::construct(a, vp);
         value_destructor<Allocator> on_exit(a, *vp); (void)on_exit;
         *p = ::boost::move(*vp);
      }
   }
};

template<class Allocator, class Iterator>
struct insert_default_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename allocator_traits<Allocator>::size_type size_type;
   typedef typename allocator_traits<Allocator>::value_type value_type;

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_default_init_alloc_n(a, n, p);  }

   void copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {
      if(!is_pod<value_type>::value){
         for (; 0 < n; --n, ++p){
            typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
            value_type *vp = reinterpret_cast<value_type *>(v.data);
            alloc_traits::construct(a, vp, default_init);
            value_destructor<Allocator> on_exit(a, *vp); (void)on_exit;
            *p = ::boost::move(*vp);
         }
      }
   }
};

template<class Allocator, class Iterator>
struct insert_copy_proxy
{
   typedef boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename alloc_traits::size_type size_type;
   typedef typename alloc_traits::value_type value_type;

   explicit insert_copy_proxy(const value_type &v)
      :  v_(v)
   {}

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, boost::movelib::iterator_to_raw_pointer(p), v_);
   }

   void copy_n_and_update(Allocator &, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p = v_;
   }

   const value_type &v_;
};


template<class Allocator, class Iterator>
struct insert_move_proxy
{
   typedef boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename alloc_traits::size_type size_type;
   typedef typename alloc_traits::value_type value_type;

   BOOST_CONTAINER_FORCEINLINE explicit insert_move_proxy(value_type &v)
      :  v_(v)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, boost::movelib::iterator_to_raw_pointer(p), ::boost::move(v_) );
   }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p = ::boost::move(v_);
   }

   value_type &v_;
};

template<class It, class Allocator>
insert_move_proxy<Allocator, It> get_insert_value_proxy(BOOST_RV_REF(typename boost::container::iterator_traits<It>::value_type) v)
{
   return insert_move_proxy<Allocator, It>(v);
}

template<class It, class Allocator>
insert_copy_proxy<Allocator, It> get_insert_value_proxy(const typename boost::container::iterator_traits<It>::value_type &v)
{
   return insert_copy_proxy<Allocator, It>(v);
}

}}}   //namespace boost { namespace container { namespace dtl {

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <boost/container/detail/variadic_templates_tools.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class Allocator, class Iterator, class ...Args>
struct insert_nonmovable_emplace_proxy
{
   typedef boost::container::allocator_traits<Allocator>   alloc_traits;
   typedef typename alloc_traits::size_type        size_type;
   typedef typename alloc_traits::value_type       value_type;

   typedef typename build_number_seq<sizeof...(Args)>::type index_tuple_t;

   explicit insert_nonmovable_emplace_proxy(BOOST_FWD_REF(Args)... args)
      : args_(args...)
   {}

   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n)
   {  this->priv_uninitialized_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:
   template<std::size_t ...IdxPack>
   void priv_uninitialized_copy_some_and_update(Allocator &a, const index_tuple<IdxPack...>&, Iterator p, size_type n)
   {
      BOOST_ASSERT(n == 1); (void)n;
      alloc_traits::construct( a, boost::movelib::iterator_to_raw_pointer(p), ::boost::forward<Args>(get<IdxPack>(this->args_))... );
   }

   protected:
   tuple<Args&...> args_;
};

template<class Allocator, class Iterator, class ...Args>
struct insert_emplace_proxy
   :  public insert_nonmovable_emplace_proxy<Allocator, Iterator, Args...>
{
   typedef insert_nonmovable_emplace_proxy<Allocator, Iterator, Args...> base_t;
   typedef boost::container::allocator_traits<Allocator>   alloc_traits;
   typedef typename base_t::value_type             value_type;
   typedef typename base_t::size_type              size_type;
   typedef typename base_t::index_tuple_t          index_tuple_t;

   explicit insert_emplace_proxy(BOOST_FWD_REF(Args)... args)
      : base_t(::boost::forward<Args>(args)...)
   {}

   void copy_n_and_update(Allocator &a, Iterator p, size_type n)
   {  this->priv_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:

   template<std::size_t ...IdxPack>
   void priv_copy_some_and_update(Allocator &a, const index_tuple<IdxPack...>&, Iterator p, size_type n)
   {
      BOOST_ASSERT(n ==1); (void)n;
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      value_type *vp = reinterpret_cast<value_type *>(v.data);
      alloc_traits::construct(a, vp,
         ::boost::forward<Args>(get<IdxPack>(this->args_))...);
      BOOST_TRY{
         *p = ::boost::move(*vp);
      }
      BOOST_CATCH(...){
         alloc_traits::destroy(a, vp);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      alloc_traits::destroy(a, vp);
   }
};

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type>
   : public insert_move_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy(typename boost::container::allocator_traits<Allocator>::value_type &&v)
   : insert_move_proxy<Allocator, Iterator>(v)
   {}
};

//We use "add_const" here as adding "const" only confuses MSVC12(and maybe later) provoking
//compiler error C2752 ("more than one partial specialization matches").
//Any problem is solvable with an extra layer of indirection? ;-)
template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type &>
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type &
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

}}}   //namespace boost { namespace container { namespace dtl {

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <boost/container/detail/value_init.hpp>

namespace boost {
namespace container {
namespace dtl {

#define BOOST_CONTAINER_ADVANCED_INSERT_INT_CODE(N) \
template< class Allocator, class Iterator BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
struct insert_nonmovable_emplace_proxy##N\
{\
   typedef boost::container::allocator_traits<Allocator> alloc_traits;\
   typedef typename alloc_traits::size_type size_type;\
   typedef typename alloc_traits::value_type value_type;\
   \
   explicit insert_nonmovable_emplace_proxy##N(BOOST_MOVE_UREF##N)\
      BOOST_MOVE_COLON##N BOOST_MOVE_FWD_INIT##N {}\
   \
   void uninitialized_copy_n_and_update(Allocator &a, Iterator p, size_type n)\
   {\
      BOOST_ASSERT(n == 1); (void)n;\
      alloc_traits::construct(a, boost::movelib::iterator_to_raw_pointer(p) BOOST_MOVE_I##N BOOST_MOVE_MFWD##N);\
   }\
   \
   void copy_n_and_update(Allocator &, Iterator, size_type)\
   {  BOOST_ASSERT(false);   }\
   \
   protected:\
   BOOST_MOVE_MREF##N\
};\
\
template< class Allocator, class Iterator BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
struct insert_emplace_proxy_arg##N\
   : insert_nonmovable_emplace_proxy##N< Allocator, Iterator BOOST_MOVE_I##N BOOST_MOVE_TARG##N >\
{\
   typedef insert_nonmovable_emplace_proxy##N\
      < Allocator, Iterator BOOST_MOVE_I##N BOOST_MOVE_TARG##N > base_t;\
   typedef typename base_t::value_type value_type;\
   typedef typename base_t::size_type size_type;\
   typedef boost::container::allocator_traits<Allocator> alloc_traits;\
   \
   explicit insert_emplace_proxy_arg##N(BOOST_MOVE_UREF##N)\
      : base_t(BOOST_MOVE_FWD##N){}\
   \
   void copy_n_and_update(Allocator &a, Iterator p, size_type n)\
   {\
      BOOST_ASSERT(n == 1); (void)n;\
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      BOOST_ASSERT((((size_type)(&v)) % alignment_of<value_type>::value) == 0);\
      value_type *vp = reinterpret_cast<value_type *>(v.data);\
      alloc_traits::construct(a, vp BOOST_MOVE_I##N BOOST_MOVE_MFWD##N);\
      BOOST_TRY{\
         *p = ::boost::move(*vp);\
      }\
      BOOST_CATCH(...){\
         alloc_traits::destroy(a, vp);\
         BOOST_RETHROW\
      }\
      BOOST_CATCH_END\
      alloc_traits::destroy(a, vp);\
   }\
};\
//
BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_ADVANCED_INSERT_INT_CODE)
#undef BOOST_CONTAINER_ADVANCED_INSERT_INT_CODE

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, ::boost::rv<typename boost::container::allocator_traits<Allocator>::value_type> >
   : public insert_move_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_move_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type>
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

#else //e.g. MSVC10 & MSVC11

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type>
   : public insert_move_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<Allocator>::value_type &&v)
   : insert_move_proxy<Allocator, Iterator>(v)
   {}
};

//We use "add_const" here as adding "const" only confuses MSVC10&11 provoking
//compiler error C2752 ("more than one partial specialization matches").
//Any problem is solvable with an extra layer of indirection? ;-)
template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type &>
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type &
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

#endif

}}}   //namespace boost { namespace container { namespace dtl {

#endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP

/* advanced_insert_int.hpp
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
*/