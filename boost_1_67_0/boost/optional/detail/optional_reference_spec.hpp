// Copyright (C) 2015-2018 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OPTIONAL_REFERENCE_SPEC_AJK_03OCT2015_HPP
#define BOOST_OPTIONAL_DETAIL_OPTIONAL_REFERENCE_SPEC_AJK_03OCT2015_HPP

#ifdef BOOST_OPTIONAL_CONFIG_NO_PROPER_ASSIGN_FROM_CONST_INT
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_const.hpp>
#endif

# if 1

namespace boost {

namespace detail {

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

template <class From>
void prevent_binding_rvalue()
{
#ifndef BOOST_OPTIONAL_CONFIG_ALLOW_BINDING_TO_RVALUES
    BOOST_STATIC_ASSERT_MSG(boost::is_lvalue_reference<From>::value, 
                            "binding rvalue references to optional lvalue references is disallowed");
#endif    
}

template <class T>
BOOST_DEDUCED_TYPENAME boost::remove_reference<T>::type& forward_reference(T&& r)
{
    BOOST_STATIC_ASSERT_MSG(boost::is_lvalue_reference<T>::value, 
                            "binding rvalue references to optional lvalue references is disallowed");
    return boost::forward<T>(r);
}

#endif // BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES


template <class T>
struct is_const_integral
{
  static const bool value = boost::is_const<T>::value && boost::is_integral<T>::value;
};

template <class T>
struct is_const_integral_bad_for_conversion
{
#if (!defined BOOST_OPTIONAL_CONFIG_ALLOW_BINDING_TO_RVALUES) && (defined BOOST_OPTIONAL_CONFIG_NO_PROPER_CONVERT_FROM_CONST_INT)
  static const bool value = boost::is_const<T>::value && boost::is_integral<T>::value;
#else
  static const bool value = false;
#endif
};

template <class From>
void prevent_assignment_from_false_const_integral()
{
#ifndef BOOST_OPTIONAL_CONFIG_ALLOW_BINDING_TO_RVALUES
#ifdef BOOST_OPTIONAL_CONFIG_NO_PROPER_ASSIGN_FROM_CONST_INT
    // MSVC compiler without rvalue refernces: we need to disable the asignment from
    // const integral lvalue reference, as it may be an invalid temporary
    BOOST_STATIC_ASSERT_MSG(!is_const_integral<From>::value, 
                            "binding const lvalue references to integral types is disabled in this compiler");
#endif
#endif   
}


template <class T>
struct is_optional_
{
  static const bool value = false;
};

template <class U>
struct is_optional_< ::boost::optional<U> >
{
  static const bool value = true;
};

template <class T>
struct is_no_optional
{
  static const bool value = !is_optional_<BOOST_DEDUCED_TYPENAME boost::decay<T>::type>::value;
};


template <class T, class U>
  struct is_same_decayed
  {
    static const bool value = ::boost::is_same<T, BOOST_DEDUCED_TYPENAME ::boost::remove_reference<U>::type>::value
                           || ::boost::is_same<T, const BOOST_DEDUCED_TYPENAME ::boost::remove_reference<U>::type>::value;
  };

template <class T, class U>
struct no_unboxing_cond
{
  static const bool value = is_no_optional<U>::value && !is_same_decayed<T, U>::value;
};


} // namespace detail

template <class T>
class optional<T&> : public optional_detail::optional_tag
{
    T* ptr_;
    
public:
    typedef T& value_type;
    typedef T& reference_type;
    typedef T& reference_const_type;
    typedef T& rval_reference_type;
    typedef T* pointer_type;
    typedef T* pointer_const_type;
    
    optional() BOOST_NOEXCEPT : ptr_() {}
    optional(none_t) BOOST_NOEXCEPT : ptr_() {}  

    template <class U>
        explicit optional(const optional<U&>& rhs) BOOST_NOEXCEPT : ptr_(rhs.get_ptr()) {}
    optional(const optional& rhs) BOOST_NOEXCEPT : ptr_(rhs.get_ptr()) {}
    
    // the following two implement a 'conditionally explicit' constructor: condition is a hack for buggy compilers with srewed conversion construction from const int
    template <class U>
      explicit optional(U& rhs, BOOST_DEDUCED_TYPENAME boost::enable_if_c<detail::is_same_decayed<T, U>::value && detail::is_const_integral_bad_for_conversion<U>::value, bool>::type = true) BOOST_NOEXCEPT
      : ptr_(boost::addressof(rhs)) {}
      
    template <class U>
      optional(U& rhs, BOOST_DEDUCED_TYPENAME boost::enable_if_c<detail::is_same_decayed<T, U>::value && !detail::is_const_integral_bad_for_conversion<U>::value, bool>::type = true) BOOST_NOEXCEPT
      : ptr_(boost::addressof(rhs)) {}

    optional& operator=(const optional& rhs) BOOST_NOEXCEPT { ptr_ = rhs.get_ptr(); return *this; }
    template <class U>
        optional& operator=(const optional<U&>& rhs) BOOST_NOEXCEPT { ptr_ = rhs.get_ptr(); return *this; }
    optional& operator=(none_t) BOOST_NOEXCEPT { ptr_ = 0; return *this; }
    
    
    void swap(optional& rhs) BOOST_NOEXCEPT { std::swap(ptr_, rhs.ptr_); }
    T& get() const { BOOST_ASSERT(ptr_); return   *ptr_; }

    T* get_ptr() const BOOST_NOEXCEPT { return ptr_; }
    T* operator->() const { BOOST_ASSERT(ptr_); return ptr_; }
    T& operator*() const { BOOST_ASSERT(ptr_); return *ptr_; }
    T& value() const { return ptr_ ? *ptr_ : (throw_exception(bad_optional_access()), *ptr_); }
    
    bool operator!() const BOOST_NOEXCEPT { return ptr_ == 0; }  
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
      
    void reset() BOOST_NOEXCEPT { ptr_ = 0; }

    bool is_initialized() const BOOST_NOEXCEPT { return ptr_ != 0; }
    bool has_value() const BOOST_NOEXCEPT { return ptr_ != 0; }
    
    template <typename F>
    optional<typename boost::result_of<F(T&)>::type> map(F f) const
    {
      if (this->has_value())
        return f(this->get());
      else
        return none;
    }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(T&)>::type>::type> flat_map(F f) const
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }
    
#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES   
 
    optional(T&& /* rhs */) BOOST_NOEXCEPT { detail::prevent_binding_rvalue<T&&>(); }
    
    template <class R>
        optional(R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::no_unboxing_cond<T, R>, bool>::type = true) BOOST_NOEXCEPT
        : ptr_(boost::addressof(r)) { detail::prevent_binding_rvalue<R>(); }
        
    template <class R>
        optional(bool cond, R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, bool>::type = true) BOOST_NOEXCEPT
        : ptr_(cond ? boost::addressof(r) : 0) { detail::prevent_binding_rvalue<R>(); }
        
    template <class R>
        BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, optional<T&>&>::type
        operator=(R&& r) BOOST_NOEXCEPT { detail::prevent_binding_rvalue<R>(); ptr_ = boost::addressof(r); return *this; }
        
    template <class R>
        void emplace(R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, bool>::type = true) BOOST_NOEXCEPT
        { detail::prevent_binding_rvalue<R>(); ptr_ = boost::addressof(r); }
        
    template <class R>
      T& get_value_or(R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, bool>::type = true) const BOOST_NOEXCEPT
      { detail::prevent_binding_rvalue<R>(); return ptr_ ? *ptr_ : r; }
      
    template <class R>
        T& value_or(R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, bool>::type = true) const BOOST_NOEXCEPT
        { detail::prevent_binding_rvalue<R>(); return ptr_ ? *ptr_ : r; }
        
    template <class R>
      void reset(R&& r, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<R>, bool>::type = true) BOOST_NOEXCEPT
      { detail::prevent_binding_rvalue<R>(); ptr_ = boost::addressof(r); }
      
    template <class F>
        T& value_or_eval(F f) const { return ptr_ ? *ptr_ : detail::forward_reference(f()); }
      
#else  // BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

    
    // the following two implement a 'conditionally explicit' constructor
    template <class U>
      explicit optional(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if_c<detail::no_unboxing_cond<T, U>::value && detail::is_const_integral_bad_for_conversion<U>::value, bool>::type = true) BOOST_NOEXCEPT
      : ptr_(boost::addressof(v)) { }
      
    template <class U>
      optional(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if_c<detail::no_unboxing_cond<T, U>::value && !detail::is_const_integral_bad_for_conversion<U>::value, bool>::type = true) BOOST_NOEXCEPT
      : ptr_(boost::addressof(v)) { }
        
    template <class U>
      optional(bool cond, U& v, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, bool>::type = true) BOOST_NOEXCEPT : ptr_(cond ? boost::addressof(v) : 0) {}

    template <class U>
      BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, optional<T&>&>::type
      operator=(U& v) BOOST_NOEXCEPT
      {
        detail::prevent_assignment_from_false_const_integral<U>();
        ptr_ = boost::addressof(v); return *this;
      }

    template <class U>
        void emplace(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, bool>::type = true) BOOST_NOEXCEPT
        { ptr_ = boost::addressof(v); }
        
    template <class U>
      T& get_value_or(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, bool>::type = true) const BOOST_NOEXCEPT
      { return ptr_ ? *ptr_ : v; }
      
    template <class U>
        T& value_or(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, bool>::type = true) const BOOST_NOEXCEPT
        { return ptr_ ? *ptr_ : v; }
        
    template <class U>
      void reset(U& v, BOOST_DEDUCED_TYPENAME boost::enable_if<detail::is_no_optional<U>, bool>::type = true) BOOST_NOEXCEPT
      { ptr_ = boost::addressof(v); }
      
    template <class F>
      T& value_or_eval(F f) const { return ptr_ ? *ptr_ : f(); }
      
#endif // BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
};

template <class T> 
  void swap ( optional<T&>& x, optional<T&>& y) BOOST_NOEXCEPT
{
  x.swap(y);
}

} // namespace boost

#endif // 1/0

#endif // header guard

/* optional_reference_spec.hpp
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
*/