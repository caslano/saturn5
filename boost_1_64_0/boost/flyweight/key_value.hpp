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
LFF91Yn8wskN1CvnQdWMwdMegsFrDpmfyU682lyaerTx2JAf0frfVTl1+z2IWTzPq3PyRcWjsJQJdCc4W7+pHPDE4b3Gkh+a2VVlOjdz9cW8LQGdQwJRsbYnKSY7aY2/A+EnbGpA08pkjjE+fK90IXrJuKQd+5sYTGd/PUFmYSnaUizaUmRsS6KNtljJ48fwqkNJw07iVx0AIykUapC1PRO5uqXmIdKugA2MGqmfuqQnd9aCVtKbcxrs3rYzd8WGznykdqZJcu/2VIdUtqP0N6+2C+XcAjmkU23zab2Fjp5UrLaU8s30T1+iJ6B75PyMptD5X0GlUhlxF+qvyGixI6Xu8OeQ80vhc0frjmWws8SxpxA3T0L6l2atUFNSoq1QH0oxqD9SWvOrWcqFKz+dZiWRvhR2CGlNZ5aFh+ojUKgLWaEWwqaPRmeMQNj2j5cKjrpX8JRQmQf4mW3N53ubzZfcipvYG0+vKminEE64ebtsHWaaqD83Bn0ehtSWPuD9joaVKSvEb1BVwsHacpgGjBVCM/A1IFl6sPERTdtmo/7Jxvq7ivoXScG6pfy9F4HBsD8Ll4NQRvsxsNUuxiG4IykJnvFnCU91ZyGSAx3o0JOYLTfIzJfwQ3nnjsCkqhs70nYT2cyWm1AiWlokZoffgqfM9YdOggqytsXcD5qy35pC1XPr3wCfrW348oVWfqzaIpDXsLDDSd03p6qevD94P3qnvCTcVu74MoBnXm0bWqEObJIbvFs7ANJYVZzsNm7vOKch8RdzfXr7TQvZb9vL5pdws6JiiMJHf4M8fvGF3G+zfnQSbExJeBQvehZD4ZyZSYYu4C6DfLHRq7SLpy2xONL+2ntBcM/NhMdA84iCmb2oPJahA3vmS352y0hFW0IfqQd0Zk/YWsVS5iN9Ll9nfU2bS+3Hz7FuhIN9z7Ev0fekSrVQI31PVQe/Spgx0HlhuPaTi1sAqdckAj5uy9GFYmIDdd++mMrtPQ73YVcVr6S1VxKcT37gA3m1owhim4R4BSD0gqtcZGatp4x2mdp63C/NxvEz799H2soFJlfcc2OX1Dzwr3bruQkxuBTC8jxh0WYerG9a37eYCtH+d7TBnv5uUluz/u16dzz6uy5R8J2/rrevD36/jUkftr4Hrz0efnFJG9VeUeLa9m19TJGaqv8kLARb+CmHtV7/qaj2qdbM93Co+KbX2/seOz3m/vwwOZ7vEYqCv/VQHN+jgMB16KSkhrj05WlR9Ts/qbenL9+TqfRX5fsx9dXL1fLpH9jr32mZZvrmJsXTv32j4E/5Mo7+/by1Wf97UoNt/S/B5tWeSCvm7bVCdux9j5PQLHypgO9B8GMl/HihsrfR/tbqeuaRR5HNfr6SxTgPhzMkvF+3cTYHlfhjJCL1Kk1//wxVvp7UeIpT3qCEbP5svEzZVXn2KM/tlGevcuEyG5+hq2Z8DB0sdTC1P/IC4lADJe78WaThFtX7qF6Cu524ksq9v1ac31DIsb9Hgyznp3JXU7k1SrmA9pxSLqDeFC0koN8R0BwFqEirVICKVKBiR2y90bH6GeTluduaz/fGyAeCY+wHOBg83G+km4sHMMuJGVkyg2QgCOjcFgf9vhj0ZR379qnzv5Xh/nCh9oJTTltL+x9Debf2Qqos3vT8HtNKn1TE03cQhyNvQJyOXupqe704ktokvhyJ7/f28a1qGl+WxDekZ5P4TMvRZB2dn9CdxQXTuSCg19a6G6INX9zKgacNCu7kmaYdsU659vSxB9xUt5TtFyZYCz30Ej+7uOCjF9SrpJ+XoHpRIanh4PCLXKNR4Gx51BGFXp9CL3T3rAAJ3Ba+w44TQBXXstZpr3iYAbY=
*/