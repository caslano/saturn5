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