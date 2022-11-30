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
#include <boost/move/detail/force_ptr.hpp>
// other
#include <boost/assert.hpp>
#include <boost/core/no_exceptions_support.hpp>

namespace boost { namespace container { namespace dtl {

template<class Allocator, class FwdIt, class Iterator>
struct move_insert_range_proxy
{
   typedef typename allocator_traits<Allocator>::value_type value_type;

   BOOST_CONTAINER_FORCEINLINE explicit move_insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n)
   {
      this->first_ = ::boost::container::uninitialized_move_alloc_n_source
         (a, this->first_, n, p);
   }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, std::size_t n)
   {
      this->first_ = ::boost::container::move_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class Allocator, class FwdIt, class Iterator>
struct insert_range_proxy
{
   typedef typename allocator_traits<Allocator>::value_type value_type;

   BOOST_CONTAINER_FORCEINLINE explicit insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n)
   {
      this->first_ = ::boost::container::uninitialized_copy_alloc_n_source(a, this->first_, n, p);
   }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, std::size_t n)
   {
      this->first_ = ::boost::container::copy_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class Allocator, class Iterator>
struct insert_n_copies_proxy
{
   typedef typename allocator_traits<Allocator>::value_type value_type;

   BOOST_CONTAINER_FORCEINLINE explicit insert_n_copies_proxy(const value_type &v)
      :  v_(v)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {  boost::container::uninitialized_fill_alloc_n(a, v_, n, p);  }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, std::size_t n) const
   {
      while (n){
         --n;
         *p = v_;
         ++p;
      }
   }

   const value_type &v_;
};

template<class Allocator, class Iterator>
struct insert_value_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename allocator_traits<Allocator>::value_type value_type;
   typedef typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type storage_t;

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {  boost::container::uninitialized_value_init_alloc_n(a, n, p);  }

   void copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {
      while (n){
         --n;
         storage_t v;
         alloc_traits::construct(a, move_detail::force_ptr<value_type *>(&v));
         value_type *vp = move_detail::force_ptr<value_type *>(&v);
         value_destructor<Allocator> on_exit(a, *vp); (void)on_exit;
         *p = ::boost::move(*vp);
         ++p;
      }
   }
};

template<class Allocator, class Iterator>
struct insert_default_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename allocator_traits<Allocator>::value_type value_type;
   typedef typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type storage_t;

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {  boost::container::uninitialized_default_init_alloc_n(a, n, p);  }

   void copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {
      if(!is_pod<value_type>::value){
         while (n){
            --n;
            typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
            alloc_traits::construct(a, move_detail::force_ptr<value_type *>(&v), default_init);
            value_type *vp = move_detail::force_ptr<value_type *>(&v);
            value_destructor<Allocator> on_exit(a, *vp); (void)on_exit;
            *p = ::boost::move(*vp);
            ++p;
         }
      }
   }
};

template<class Allocator, class Iterator>
struct insert_copy_proxy
{
   typedef boost::container::allocator_traits<Allocator> alloc_traits;
   typedef typename alloc_traits::value_type value_type;

   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_copy_proxy(const value_type &v)
      :  v_(v)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, boost::movelib::iterator_to_raw_pointer(p), v_);
   }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, std::size_t n) const
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
   typedef typename alloc_traits::value_type value_type;

   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_move_proxy(value_type &v)
      :  v_(v)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, boost::movelib::iterator_to_raw_pointer(p), ::boost::move(v_) );
   }

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator p, std::size_t n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p = ::boost::move(v_);
   }

   value_type &v_;
};

template<class It, class Allocator>
BOOST_CONTAINER_FORCEINLINE insert_move_proxy<Allocator, It> get_insert_value_proxy(BOOST_RV_REF(typename boost::container::iterator_traits<It>::value_type) v)
{
   return insert_move_proxy<Allocator, It>(v);
}

template<class It, class Allocator>
BOOST_CONTAINER_FORCEINLINE insert_copy_proxy<Allocator, It> get_insert_value_proxy(const typename boost::container::iterator_traits<It>::value_type &v)
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
   typedef typename alloc_traits::value_type       value_type;
   typedef typename build_number_seq<sizeof...(Args)>::type index_tuple_t;

   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_nonmovable_emplace_proxy(BOOST_FWD_REF(Args)... args)
      : args_(args...)
   {}

   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n)
   {  this->priv_uninitialized_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:
   template<std::size_t ...IdxPack>
   BOOST_CONTAINER_FORCEINLINE void priv_uninitialized_copy_some_and_update(Allocator &a, const index_tuple<IdxPack...>&, Iterator p, std::size_t n)
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
   typedef typename base_t::index_tuple_t          index_tuple_t;

   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy(BOOST_FWD_REF(Args)... args)
      : base_t(::boost::forward<Args>(args)...)
   {}

   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &a, Iterator p, std::size_t n)
   {  this->priv_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:

   template<std::size_t ...IdxPack>
   BOOST_CONTAINER_FORCEINLINE void priv_copy_some_and_update(Allocator &a, const index_tuple<IdxPack...>&, Iterator p, std::size_t n)
   {
      BOOST_ASSERT(n ==1); (void)n;
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      alloc_traits::construct(a, move_detail::force_ptr<value_type *>(&v), ::boost::forward<Args>(get<IdxPack>(this->args_))...);
      value_type *vp = move_detail::force_ptr<value_type *>(&v);
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
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy(typename boost::container::allocator_traits<Allocator>::value_type &&v)
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

   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type &>
   : public insert_copy_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type &
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy(const typename boost::container::allocator_traits<Allocator>::value_type &v)
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
   typedef typename alloc_traits::value_type value_type;\
   \
   static const bool single_value = true;\
   \
   BOOST_CONTAINER_FORCEINLINE explicit insert_nonmovable_emplace_proxy##N(BOOST_MOVE_UREF##N)\
      BOOST_MOVE_COLON##N BOOST_MOVE_FWD_INIT##N {}\
   \
   BOOST_CONTAINER_FORCEINLINE void uninitialized_copy_n_and_update(Allocator &a, Iterator p, std::size_t n)\
   {\
      BOOST_ASSERT(n == 1); (void)n;\
      alloc_traits::construct(a, boost::movelib::iterator_to_raw_pointer(p) BOOST_MOVE_I##N BOOST_MOVE_MFWD##N);\
   }\
   \
   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &, Iterator, std::size_t)\
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
   typedef boost::container::allocator_traits<Allocator> alloc_traits;\
   \
   static const bool single_value = true;\
   \
   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg##N(BOOST_MOVE_UREF##N)\
      : base_t(BOOST_MOVE_FWD##N){}\
   \
   BOOST_CONTAINER_FORCEINLINE void copy_n_and_update(Allocator &a, Iterator p, std::size_t n)\
   {\
      BOOST_ASSERT(n == 1); (void)n;\
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      alloc_traits::construct(a, move_detail::force_ptr<value_type *>(&v) BOOST_MOVE_I##N BOOST_MOVE_MFWD##N);\
      value_type *vp = move_detail::force_ptr<value_type *>(&v);\
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
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_move_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type>
   : public insert_copy_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

#else //e.g. MSVC10 & MSVC11

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type>
   : public insert_move_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<Allocator>::value_type &&v)
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
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator, typename boost::container::allocator_traits<Allocator>::value_type &>
   : public insert_copy_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

template<class Allocator, class Iterator>
struct insert_emplace_proxy_arg1<Allocator, Iterator
   , typename boost::container::dtl::add_const<typename boost::container::allocator_traits<Allocator>::value_type>::type &
   >
   : public insert_copy_proxy<Allocator, Iterator>
{
   static const bool single_value = true;

   BOOST_CONTAINER_FORCEINLINE explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<Allocator>::value_type &v)
   : insert_copy_proxy<Allocator, Iterator>(v)
   {}
};

#endif

}}}   //namespace boost { namespace container { namespace dtl {

#endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace boost { namespace container { namespace dtl {

template <class T>
struct has_single_value
{
   private:
   struct two {char array_[2];};
   template<bool Arg> struct wrapper;
   template <class U> static two test(int, ...);
   template <class U> static char test(int, const wrapper<U::single_value>*);
   public:
   static const bool value = sizeof(test<T>(0, 0)) == 1;
   void dummy(){}
};

template<class InsertionProxy, bool = has_single_value<InsertionProxy>::value>
struct is_single_value_proxy_impl
{
   static const bool value = InsertionProxy::single_value;
};

template<class InsertionProxy>
struct is_single_value_proxy_impl<InsertionProxy, false>
{
   static const bool value = false;
};

template<class InsertionProxy>
struct is_single_value_proxy
   : is_single_value_proxy_impl<InsertionProxy>
{};

}}}   //namespace boost { namespace container { namespace dtl {

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP

/* advanced_insert_int.hpp
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
*/