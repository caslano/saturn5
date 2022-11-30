/* Copyright 2006-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_FLYWEIGHT_CORE_HPP
#define BOOST_FLYWEIGHT_DETAIL_FLYWEIGHT_CORE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/core/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/flyweight/detail/perfect_fwd.hpp>
#include <boost/mpl/apply.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400))
#pragma warning(push)
#pragma warning(disable:4101)  /* unreferenced local vars */
#endif

/* flyweight_core provides the inner implementation of flyweight<> by
 * weaving together a value policy, a flyweight factory, a holder for the
 * factory,a tracking policy and a locking policy.
 */

namespace boost{

namespace flyweights{

namespace detail{

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
class flyweight_core;

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
struct flyweight_core_tracking_helper
{
private:
  typedef flyweight_core<
    ValuePolicy,Tag,TrackingPolicy,
    FactorySpecifier,LockingPolicy,
    HolderSpecifier
  >                                   core;
  typedef typename core::handle_type  handle_type;
  typedef typename core::entry_type   entry_type;
  
public:
  static const entry_type& entry(const handle_type& h)
  {
    return core::entry(h);
  }

  template<typename Checker>
  static void erase(const handle_type& h,Checker chk)
  {
    typedef typename core::lock_type lock_type;
    core::init();
    lock_type lock(core::mutex());(void)lock;
    if(chk(h))core::factory().erase(h);
  }
};

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
class flyweight_core
{
public:
  typedef typename ValuePolicy::key_type     key_type;
  typedef typename ValuePolicy::value_type   value_type;
  typedef typename ValuePolicy::rep_type     rep_type;
  typedef typename mpl::apply2<
    typename TrackingPolicy::entry_type,
    rep_type,
    key_type
  >::type                                    entry_type;
  typedef typename mpl::apply2<
    FactorySpecifier,
    entry_type,
    key_type
  >::type                                    factory_type;
  typedef typename factory_type::handle_type base_handle_type;
  typedef typename mpl::apply2<
    typename TrackingPolicy::handle_type,
    base_handle_type,
    flyweight_core_tracking_helper<
      ValuePolicy,Tag,TrackingPolicy,
      FactorySpecifier,LockingPolicy,
      HolderSpecifier
    >
  >::type                                    handle_type;
  typedef typename LockingPolicy::mutex_type mutex_type;
  typedef typename LockingPolicy::lock_type  lock_type;

  static bool init()
  {
    if(static_initializer)return true;
    else{
      holder_arg& a=holder_type::get();
      static_factory_ptr=&a.factory;
      static_mutex_ptr=&a.mutex;
      static_initializer=(static_factory_ptr!=0);
      return static_initializer;
    }
  }

  /* insert overloads*/

#define BOOST_FLYWEIGHT_PERFECT_FWD_INSERT_BODY(args)         \
{                                                             \
  return insert_rep(rep_type(BOOST_FLYWEIGHT_FORWARD(args))); \
}

  BOOST_FLYWEIGHT_PERFECT_FWD(
    static handle_type insert,
    BOOST_FLYWEIGHT_PERFECT_FWD_INSERT_BODY)

#undef BOOST_FLYWEIGHT_PERFECT_FWD_INSERT_BODY

  static handle_type insert(const value_type& x){return insert_value(x);}
  static handle_type insert(value_type& x){return insert_value(x);}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  static handle_type insert(const value_type&& x){return insert_value(x);}
  static handle_type insert(value_type&& x){return insert_value(std::move(x));}
#endif

  static const entry_type& entry(const base_handle_type& h)
  {
    return factory().entry(h);
  }

  static const value_type& value(const handle_type& h)
  {
    return static_cast<const rep_type&>(entry(h));
  }

  static const key_type& key(const handle_type& h)
  {
    return static_cast<const rep_type&>(entry(h));
  }

  static factory_type& factory()
  {
    return *static_factory_ptr;
  }

  static mutex_type& mutex()
  {
    return *static_mutex_ptr;
  }

private:
  struct                              holder_arg
  {
    factory_type factory;
    mutex_type   mutex;
  };
  typedef typename mpl::apply1<
    HolderSpecifier,
    holder_arg
  >::type                             holder_type;

  static handle_type insert_rep(const rep_type& x)
  {
    init();
    entry_type       e(x);
    lock_type        lock(mutex());(void)lock;
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    base_handle_type h(factory().insert(std::move(e)));
#else
    base_handle_type h(factory().insert(e));
#endif

    BOOST_TRY{
      ValuePolicy::construct_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }

  static handle_type insert_value(const value_type& x)
  {
    init();
    entry_type       e((rep_type(x)));
    lock_type        lock(mutex());(void)lock;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    base_handle_type h(factory().insert(std::move(e)));
#else
    base_handle_type h(factory().insert(e));
#endif

    BOOST_TRY{
      ValuePolicy::copy_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  static handle_type insert_rep(rep_type&& x)
  {
    init();
    entry_type       e(std::move(x));
    lock_type        lock(mutex());(void)lock;
    base_handle_type h(factory().insert(std::move(e)));

    BOOST_TRY{
      ValuePolicy::construct_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }

  static handle_type insert_value(value_type&& x)
  {
    init();
    entry_type       e(rep_type(std::move(x)));
    lock_type        lock(mutex());(void)lock;
    base_handle_type h(factory().insert(std::move(e)));
    BOOST_TRY{
      ValuePolicy::move_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }
#endif

  static bool          static_initializer;
  static factory_type* static_factory_ptr;
  static mutex_type*   static_mutex_ptr;
};

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
bool
flyweight_core<
  ValuePolicy,Tag,TrackingPolicy,
  FactorySpecifier,LockingPolicy,HolderSpecifier>::static_initializer=
  flyweight_core<
      ValuePolicy,Tag,TrackingPolicy,
      FactorySpecifier,LockingPolicy,HolderSpecifier>::init();

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
typename flyweight_core<
  ValuePolicy,Tag,TrackingPolicy,
  FactorySpecifier,LockingPolicy,HolderSpecifier>::factory_type*
flyweight_core<
  ValuePolicy,Tag,TrackingPolicy,
  FactorySpecifier,LockingPolicy,HolderSpecifier>::static_factory_ptr=0;

template<
  typename ValuePolicy,typename Tag,typename TrackingPolicy,
  typename FactorySpecifier,typename LockingPolicy,typename HolderSpecifier
>
typename flyweight_core<
  ValuePolicy,Tag,TrackingPolicy,
  FactorySpecifier,LockingPolicy,HolderSpecifier>::mutex_type*
flyweight_core<
  ValuePolicy,Tag,TrackingPolicy,
  FactorySpecifier,LockingPolicy,HolderSpecifier>::static_mutex_ptr=0;

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400))
#pragma warning(pop)
#endif

#endif

/* flyweight_core.hpp
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
*/