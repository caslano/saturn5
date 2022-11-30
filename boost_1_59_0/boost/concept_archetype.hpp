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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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