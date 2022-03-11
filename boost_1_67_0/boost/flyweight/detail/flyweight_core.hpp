/* Copyright 2006-2018 Joaquin M Lopez Munoz.
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
#include <boost/detail/no_exceptions_support.hpp>
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