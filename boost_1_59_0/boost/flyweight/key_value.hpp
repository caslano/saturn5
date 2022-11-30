/* Copyright 2006-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_KEY_VALUE_HPP
#define BOOST_FLYWEIGHT_KEY_VALUE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/flyweight/detail/perfect_fwd.hpp>
#include <boost/flyweight/detail/value_tag.hpp>
#include <boost/flyweight/key_value_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <new>

/* key-value policy: flywewight lookup is based on Key, which also serves
 * to construct Value only when needed (new factory entry). key_value is
 * used to avoid the construction of temporary values when such construction
 * is expensive.
 * Optionally, KeyFromValue extracts the key from a value, which
 * is needed in expressions like this:
 *
 *  typedef flyweight<key_value<Key,Value> > fw_t;
 *  fw_t  fw;
 *  Value v;
 *  fw=v; // no key explicitly given
 *
 * If no KeyFromValue is provided, this latter expression fails to compile.
 */

namespace boost{

namespace flyweights{

namespace detail{

template<typename Key,typename Value,typename KeyFromValue>
struct optimized_key_value:value_marker
{
  typedef Key   key_type;
  typedef Value value_type;

  class rep_type
  {
  public:
    /* template ctors */

#define BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY(args)       \
  :value_ptr(0)                                          \
{                                                        \
  new(spc_ptr())key_type(BOOST_FLYWEIGHT_FORWARD(args)); \
}

  BOOST_FLYWEIGHT_PERFECT_FWD(
    explicit rep_type,
    BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY)

#undef BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY

    rep_type(const rep_type& x):value_ptr(x.value_ptr)
    {
      if(!x.value_ptr)new(key_ptr())key_type(*x.key_ptr());
    }

    rep_type(const value_type& x):value_ptr(&x){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    rep_type(rep_type&& x):value_ptr(x.value_ptr)
    {
      if(!x.value_ptr)new(key_ptr())key_type(std::move(*x.key_ptr()));
    }

    rep_type(value_type&& x):value_ptr(&x){}
#endif

    ~rep_type()
    {
      if(!value_ptr)       key_ptr()->~key_type();
      else if(value_cted())value_ptr->~value_type();
    }

    operator const key_type&()const
    {
      if(value_ptr)return key_from_value(*value_ptr);
      else         return *key_ptr();
    }

    operator const value_type&()const
    {
      /* This is always called after construct_value() or copy_value(),
       * so we access spc directly rather than through value_ptr to
       * save us an indirection.
       */

      return *static_cast<value_type*>(spc_ptr());
    }

  private:
    friend struct optimized_key_value;

    void* spc_ptr()const{return static_cast<void*>(&spc);}
    bool  value_cted()const{return value_ptr==spc_ptr();}

    key_type* key_ptr()const
    {
      return static_cast<key_type*>(static_cast<void*>(&spc));
    }

    static const key_type& key_from_value(const value_type& x)
    {
      KeyFromValue k;
      return k(x);
    }

    void construct_value()const
    {
      if(!value_cted()){
        /* value_ptr must be ==0, oherwise copy_value would have been called */

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        key_type k(std::move(*key_ptr()));
#else
        key_type k(*key_ptr());
#endif

        key_ptr()->~key_type();
        value_ptr= /* guarantees key won't be re-dted at ~rep_type if the */
          static_cast<value_type*>(spc_ptr())+1; /* next statement throws */
        value_ptr=new(spc_ptr())value_type(k);
      }
    }

    void copy_value()const
    {
      if(!value_cted())value_ptr=new(spc_ptr())value_type(*value_ptr);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    void move_value()const
    {
      if(!value_cted())value_ptr=
        new(spc_ptr())value_type(std::move(const_cast<value_type&>(*value_ptr)));
    }
#endif

    mutable typename boost::aligned_storage<
      (sizeof(key_type)>sizeof(value_type))?
        sizeof(key_type):sizeof(value_type),
      (boost::alignment_of<key_type>::value >
       boost::alignment_of<value_type>::value)?
        boost::alignment_of<key_type>::value:
        boost::alignment_of<value_type>::value
    >::type                                    spc;
    mutable const value_type*                  value_ptr;
  };

  static void construct_value(const rep_type& r)
  {
    r.construct_value();
  }

  static void copy_value(const rep_type& r)
  {
    r.copy_value();
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  static void move_value(const rep_type& r)
  {
    r.move_value();
  }
#endif
};

template<typename Key,typename Value>
struct regular_key_value:value_marker
{
  typedef Key   key_type;
  typedef Value value_type;

  class rep_type
  {
  public:
    /* template ctors */

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)&&\
    BOOST_WORKAROUND(__GNUC__,<=4)&&(__GNUC__<4||__GNUC_MINOR__<=4)

/* GCC 4.4.2 (and probably prior) bug: the default ctor generated by the
 * variadic temmplate ctor below fails to value-initialize key.
 */

    rep_type():key(),value_ptr(0){}
#endif

#define BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY(args) \
  :key(BOOST_FLYWEIGHT_FORWARD(args)),value_ptr(0){}

  BOOST_FLYWEIGHT_PERFECT_FWD(
    explicit rep_type,
    BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY)

#undef BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY

    rep_type(const rep_type& x):key(x.key),value_ptr(0){}
    rep_type(const value_type&):key(no_key_from_value_failure()){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    rep_type(rep_type&& x):key(std::move(x.key)),value_ptr(0){}
    rep_type(value_type&&):key(no_key_from_value_failure()){}
#endif

    ~rep_type()
    {
      if(value_ptr)value_ptr->~value_type();
    }

    operator const key_type&()const{return key;}

    operator const value_type&()const
    {
      /* This is always called after construct_value(),so we access spc
       * directly rather than through value_ptr to save us an indirection.
       */

      return *static_cast<value_type*>(spc_ptr());
    }

  private:
    friend struct regular_key_value;

    void* spc_ptr()const{return static_cast<void*>(&spc);}

    struct no_key_from_value_failure
    {
      BOOST_MPL_ASSERT_MSG(
        false,
        NO_KEY_FROM_VALUE_CONVERSION_PROVIDED,
        (key_type,value_type));

      operator const key_type&()const;
    };

    void construct_value()const
    {
      if(!value_ptr)value_ptr=new(spc_ptr())value_type(key);
    }

    key_type                                 key;
    mutable typename boost::aligned_storage<
      sizeof(value_type),
      boost::alignment_of<value_type>::value
    >::type                                  spc;
    mutable const value_type*                value_ptr;
  };

  static void construct_value(const rep_type& r)
  {
    r.construct_value();
  }

  /* copy_value() and move_value() can't really ever be called, provided to avoid
   * compile errors (it is the no_key_from_value_failure compile error we want to
   * appear in these cases).
   */

  static void copy_value(const rep_type&){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  static void move_value(const rep_type&){}
#endif
};

} /* namespace flyweights::detail */

template<typename Key,typename Value,typename KeyFromValue>
struct key_value:
  mpl::if_<
    is_same<KeyFromValue,no_key_from_value>,
    detail::regular_key_value<Key,Value>,
    detail::optimized_key_value<Key,Value,KeyFromValue>
  >::type
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* key_value.hpp
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
*/