//
// (C) Copyright Jeremy Siek 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:
//
//   17 July  2001: Added const to some member functions. (Jeremy Siek) 
//   05 May   2001: Removed static dummy_cons object. (Jeremy Siek)

// See http://www.boost.org/libs/concept_check for documentation.

#ifndef BOOST_CONCEPT_ARCHETYPES_HPP
#define BOOST_CONCEPT_ARCHETYPES_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <functional>
#include <iterator>  // iterator tags
#include <cstddef>   // std::ptrdiff_t

namespace boost {

  //===========================================================================
  // Basic Archetype Classes

  namespace detail {
    class dummy_constructor { };
  }

  // A type that models no concept. The template parameter 
  // is only there so that null_archetype types can be created
  // that have different type.
  template <class T = int>
  class null_archetype {
  private:
    null_archetype() { }
    null_archetype(const null_archetype&) { }
    null_archetype& operator=(const null_archetype&) { return *this; }
  public:
    null_archetype(detail::dummy_constructor) { }
#ifndef __MWERKS__
    template <class TT>
    friend void dummy_friend(); // just to avoid warnings
#endif
  };

  // This is a helper class that provides a way to get a reference to
  // an object. The get() function will never be called at run-time
  // (nothing in this file will) so this seemingly very bad function
  // is really quite innocent. The name of this class needs to be
  // changed.
  template <class T>
  class static_object
  {
  public:
      static T& get()
      {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
          return *reinterpret_cast<T*>(0);
#else 
          static char d[sizeof(T)];
          return *reinterpret_cast<T*>(d);
#endif 
      }
  };

  template <class Base = null_archetype<> >
  class default_constructible_archetype : public Base {
  public:
    default_constructible_archetype() 
      : Base(static_object<detail::dummy_constructor>::get()) { }
    default_constructible_archetype(detail::dummy_constructor x) : Base(x) { }
  };

  template <class Base = null_archetype<> >
  class assignable_archetype : public Base {
    assignable_archetype() { }
    assignable_archetype(const assignable_archetype&) { }
  public:
    assignable_archetype& operator=(const assignable_archetype&) {
      return *this;
    }
    assignable_archetype(detail::dummy_constructor x) : Base(x) { }
  };

  template <class Base = null_archetype<> >
  class copy_constructible_archetype : public Base {
  public:
    copy_constructible_archetype() 
      : Base(static_object<detail::dummy_constructor>::get()) { }
    copy_constructible_archetype(const copy_constructible_archetype&)
      : Base(static_object<detail::dummy_constructor>::get()) { }
    copy_constructible_archetype(detail::dummy_constructor x) : Base(x) { }
  };

  template <class Base = null_archetype<> >
  class sgi_assignable_archetype : public Base {
  public:
    sgi_assignable_archetype(const sgi_assignable_archetype&)
      : Base(static_object<detail::dummy_constructor>::get()) { }
    sgi_assignable_archetype& operator=(const sgi_assignable_archetype&) {
      return *this;
    }
    sgi_assignable_archetype(const detail::dummy_constructor& x) : Base(x) { }
  };

  struct default_archetype_base {
    default_archetype_base(detail::dummy_constructor) { }
  };

  // Careful, don't use same type for T and Base. That results in the
  // conversion operator being invalid.  Since T is often
  // null_archetype, can't use null_archetype for Base.
  template <class T, class Base = default_archetype_base>
  class convertible_to_archetype : public Base {
  private:
    convertible_to_archetype() { }
    convertible_to_archetype(const convertible_to_archetype& ) { }
    convertible_to_archetype& operator=(const convertible_to_archetype&)
      { return *this; }
  public:
    convertible_to_archetype(detail::dummy_constructor x) : Base(x) { }
    operator const T&() const { return static_object<T>::get(); }
  };

  template <class T, class Base = default_archetype_base>
  class convertible_from_archetype : public Base {
  private:
    convertible_from_archetype() { }
    convertible_from_archetype(const convertible_from_archetype& ) { }
    convertible_from_archetype& operator=(const convertible_from_archetype&)
      { return *this; }
  public:
    convertible_from_archetype(detail::dummy_constructor x) : Base(x) { }
    convertible_from_archetype(const T&) { }
    convertible_from_archetype& operator=(const T&)
      { return *this; }
  };

  class boolean_archetype {
  public:
    boolean_archetype(const boolean_archetype&) { }
    operator bool() const { return true; }
    boolean_archetype(detail::dummy_constructor) { }
  private:
    boolean_archetype() { }
    boolean_archetype& operator=(const boolean_archetype&) { return *this; }
  };
  
  template <class Base = null_archetype<> >
  class equality_comparable_archetype : public Base {
  public:
    equality_comparable_archetype(detail::dummy_constructor x) : Base(x) { }
  };
  template <class Base>
  boolean_archetype
  operator==(const equality_comparable_archetype<Base>&,
             const equality_comparable_archetype<Base>&) 
  { 
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }
  template <class Base>
  boolean_archetype
  operator!=(const equality_comparable_archetype<Base>&,
             const equality_comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }


  template <class Base = null_archetype<> >
  class equality_comparable2_first_archetype : public Base {
  public:
    equality_comparable2_first_archetype(detail::dummy_constructor x) 
      : Base(x) { }
  };
  template <class Base = null_archetype<> >
  class equality_comparable2_second_archetype : public Base {
  public:
    equality_comparable2_second_archetype(detail::dummy_constructor x) 
      : Base(x) { }
  };
  template <class Base1, class Base2>
  boolean_archetype
  operator==(const equality_comparable2_first_archetype<Base1>&,
             const equality_comparable2_second_archetype<Base2>&) 
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }
  template <class Base1, class Base2>
  boolean_archetype
  operator!=(const equality_comparable2_first_archetype<Base1>&,
             const equality_comparable2_second_archetype<Base2>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }


  template <class Base = null_archetype<> >
  class less_than_comparable_archetype : public Base {
  public:
    less_than_comparable_archetype(detail::dummy_constructor x) : Base(x) { }
  };
  template <class Base>
  boolean_archetype
  operator<(const less_than_comparable_archetype<Base>&,
            const less_than_comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }



  template <class Base = null_archetype<> >
  class comparable_archetype : public Base {
  public:
    comparable_archetype(detail::dummy_constructor x) : Base(x) { }
  };
  template <class Base>
  boolean_archetype
  operator<(const comparable_archetype<Base>&,
            const comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }
  template <class Base>
  boolean_archetype
  operator<=(const comparable_archetype<Base>&,
             const comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }
  template <class Base>
  boolean_archetype
  operator>(const comparable_archetype<Base>&,
            const comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }
  template <class Base>
  boolean_archetype
  operator>=(const comparable_archetype<Base>&,
             const comparable_archetype<Base>&)
  {
    return boolean_archetype(static_object<detail::dummy_constructor>::get());
  }


  // The purpose of the optags is so that one can specify
  // exactly which types the operator< is defined between.
  // This is useful for allowing the operations:
  //
  // A a; B b;
  // a < b
  // b < a
  //
  // without also allowing the combinations:
  //
  // a < a
  // b < b
  //
  struct optag1 { };
  struct optag2 { };
  struct optag3 { };

#define BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(OP, NAME)                       \
  template <class Base = null_archetype<>, class Tag = optag1 >                 \
  class NAME##_first_archetype : public Base {                                  \
  public:                                                                       \
    NAME##_first_archetype(detail::dummy_constructor x) : Base(x) { }           \
  };                                                                            \
                                                                                \
  template <class Base = null_archetype<>, class Tag = optag1 >                 \
  class NAME##_second_archetype : public Base {                                 \
  public:                                                                       \
    NAME##_second_archetype(detail::dummy_constructor x) : Base(x) { }          \
  };                                                                            \
                                                                                \
  template <class BaseFirst, class BaseSecond, class Tag>                       \
  boolean_archetype                                                             \
  operator OP (const NAME##_first_archetype<BaseFirst, Tag>&,                   \
               const NAME##_second_archetype<BaseSecond, Tag>&)                 \
  {                                                                             \
   return boolean_archetype(static_object<detail::dummy_constructor>::get());   \
  }

  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(==, equal_op)
  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(!=, not_equal_op)
  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(<, less_than_op)
  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(<=, less_equal_op)
  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(>, greater_than_op)
  BOOST_DEFINE_BINARY_PREDICATE_ARCHETYPE(>=, greater_equal_op)

#define BOOST_DEFINE_OPERATOR_ARCHETYPE(OP, NAME) \
  template <class Base = null_archetype<> > \
  class NAME##_archetype : public Base { \
  public: \
    NAME##_archetype(detail::dummy_constructor x) : Base(x) { } \
    NAME##_archetype(const NAME##_archetype&)  \
      : Base(static_object<detail::dummy_constructor>::get()) { } \
    NAME##_archetype& operator=(const NAME##_archetype&) { return *this; } \
  }; \
  template <class Base> \
  NAME##_archetype<Base> \
  operator OP (const NAME##_archetype<Base>&,\
               const NAME##_archetype<Base>&)  \
  { \
    return \
     NAME##_archetype<Base>(static_object<detail::dummy_constructor>::get()); \
  }

  BOOST_DEFINE_OPERATOR_ARCHETYPE(+, addable)
  BOOST_DEFINE_OPERATOR_ARCHETYPE(-, subtractable)
  BOOST_DEFINE_OPERATOR_ARCHETYPE(*, multipliable)
  BOOST_DEFINE_OPERATOR_ARCHETYPE(/, dividable)
  BOOST_DEFINE_OPERATOR_ARCHETYPE(%, modable)

  // As is, these are useless because of the return type.
  // Need to invent a better way...
#define BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(OP, NAME) \
  template <class Return, class Base = null_archetype<> > \
  class NAME##_first_archetype : public Base { \
  public: \
    NAME##_first_archetype(detail::dummy_constructor x) : Base(x) { } \
  }; \
  \
  template <class Return, class Base = null_archetype<> > \
  class NAME##_second_archetype : public Base { \
  public: \
    NAME##_second_archetype(detail::dummy_constructor x) : Base(x) { } \
  }; \
  \
  template <class Return, class BaseFirst, class BaseSecond> \
  Return \
  operator OP (const NAME##_first_archetype<Return, BaseFirst>&, \
               const NAME##_second_archetype<Return, BaseSecond>&) \
  { \
    return Return(static_object<detail::dummy_constructor>::get()); \
  }

  BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(+, plus_op)
  BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(*, time_op)
  BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(/, divide_op)
  BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(-, subtract_op)
  BOOST_DEFINE_BINARY_OPERATOR_ARCHETYPE(%, mod_op)

  //===========================================================================
  // Function Object Archetype Classes

  template <class Return>
  class generator_archetype {
  public:
    const Return& operator()() {
      return static_object<Return>::get(); 
    }
  };

  class void_generator_archetype {
  public:
    void operator()() { }
  };

  template <class Arg, class Return>
  class unary_function_archetype {
  private:
    unary_function_archetype() { }
  public:
    unary_function_archetype(detail::dummy_constructor) { }
    const Return& operator()(const Arg&) const {
      return static_object<Return>::get(); 
    }
  };

  template <class Arg1, class Arg2, class Return>
  class binary_function_archetype {
  private:
    binary_function_archetype() { }
  public:
    binary_function_archetype(detail::dummy_constructor) { }
    const Return& operator()(const Arg1&, const Arg2&) const {
      return static_object<Return>::get(); 
    }
  };

  template <class Arg>
  class unary_predicate_archetype {
    typedef boolean_archetype Return;
    unary_predicate_archetype() { }
  public:
    unary_predicate_archetype(detail::dummy_constructor) { }
    const Return& operator()(const Arg&) const {
      return static_object<Return>::get(); 
    }
  };

  template <class Arg1, class Arg2, class Base = null_archetype<> >
  class binary_predicate_archetype {
    typedef boolean_archetype Return;
    binary_predicate_archetype() { }
  public:
    binary_predicate_archetype(detail::dummy_constructor) { }
    const Return& operator()(const Arg1&, const Arg2&) const {
      return static_object<Return>::get(); 
    }
  };

  //===========================================================================
  // Iterator Archetype Classes

  template <class T, int I = 0>
  class input_iterator_archetype
  {
  private:
    typedef input_iterator_archetype self;
  public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    struct reference {
      operator const value_type&() const { return static_object<T>::get(); }
    };
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return reference(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class input_iterator_archetype_no_proxy
  {
  private:
    typedef input_iterator_archetype_no_proxy self;
  public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  struct output_proxy {
    output_proxy& operator=(const T&) { return *this; }
  };

  template <class T>
  class output_iterator_archetype
  {
  public:
    typedef output_iterator_archetype self;
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef output_proxy<T> value_type;
    typedef output_proxy<T> reference;
    typedef void pointer;
    typedef void difference_type;
    output_iterator_archetype(detail::dummy_constructor) { }
    output_iterator_archetype(const self&) { }
    self& operator=(const self&) { return *this; }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return output_proxy<T>(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  private:
    output_iterator_archetype() { }
  };

  template <class T>
  class input_output_iterator_archetype
  {
  private:
    typedef input_output_iterator_archetype self;
    struct in_out_tag : public std::input_iterator_tag, public std::output_iterator_tag { };
  public:
    typedef in_out_tag iterator_category;
    typedef T value_type;
    struct reference {
      reference& operator=(const T&) { return *this; }
      operator value_type() { return static_object<T>::get(); }
    };
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
    input_output_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return reference(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class forward_iterator_archetype
  {
  public:
    typedef forward_iterator_archetype self;
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef T const* pointer;
    typedef std::ptrdiff_t difference_type;
    forward_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class mutable_forward_iterator_archetype
  {
  public:
    typedef mutable_forward_iterator_archetype self;
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    mutable_forward_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class bidirectional_iterator_archetype
  {
  public:
    typedef bidirectional_iterator_archetype self;
  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    bidirectional_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    self& operator--() { return *this; }
    self operator--(int) { return *this; }
  };

  template <class T>
  class mutable_bidirectional_iterator_archetype
  {
  public:
    typedef mutable_bidirectional_iterator_archetype self;
  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    mutable_bidirectional_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    self& operator--() { return *this; }
    self operator--(int) { return *this; }
  };

  template <class T>
  class random_access_iterator_archetype
  {
  public:
    typedef random_access_iterator_archetype self;
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    random_access_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    self& operator--() { return *this; }
    self operator--(int) { return *this; }
    reference operator[](difference_type) const
      { return static_object<T>::get(); }
    self& operator+=(difference_type) { return *this; }
    self& operator-=(difference_type) { return *this; }
    difference_type operator-(const self&) const
      { return difference_type(); }
    self operator+(difference_type) const { return *this; }
    self operator-(difference_type) const { return *this; }
    bool operator<(const self&) const { return true; }
    bool operator<=(const self&) const { return true; }
    bool operator>(const self&) const { return true; }
    bool operator>=(const self&) const { return true; }
  };
  template <class T>
  random_access_iterator_archetype<T> 
  operator+(typename random_access_iterator_archetype<T>::difference_type, 
            const random_access_iterator_archetype<T>& x) 
    { return x; }


  template <class T>
  class mutable_random_access_iterator_archetype
  {
  public:
    typedef mutable_random_access_iterator_archetype self;
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    mutable_random_access_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() const { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    self& operator--() { return *this; }
    self operator--(int) { return *this; }
    reference operator[](difference_type) const
      { return static_object<T>::get(); }
    self& operator+=(difference_type) { return *this; }
    self& operator-=(difference_type) { return *this; }
    difference_type operator-(const self&) const
      { return difference_type(); }
    self operator+(difference_type) const { return *this; }
    self operator-(difference_type) const { return *this; }
    bool operator<(const self&) const { return true; }
    bool operator<=(const self&) const { return true; }
    bool operator>(const self&) const { return true; }
    bool operator>=(const self&) const { return true; }
  };
  template <class T>
  mutable_random_access_iterator_archetype<T> 
  operator+
    (typename mutable_random_access_iterator_archetype<T>::difference_type, 
     const mutable_random_access_iterator_archetype<T>& x) 
    { return x; }

} // namespace boost

#endif // BOOST_CONCEPT_ARCHETYPES_H

/* concept_archetype.hpp
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
*/