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
A/w+E24kVOmLgs1gDGwNY2E7GAo7ar2JJ02pviaeFIkn3HW+ATnOtrSsmni6wQLwFljQ+M++CfaEZbS5CTcVlS3hFpdw/fK8tPQ6ngn3UZikytaV7+3iL9Uj312lnLtBFW4PWFL0yaIvq9IBqyh/Uu7dpdzRB9KXI/GEe6SvueS7BQxTsu3Kl9XP+Ivy8Fdf/DWAKt0NxV8HVJz4Ky/+VLhNxN8w8ZcOY2GGlO8IGAeHw3Kid+qthYRX2qPeNkr5brJNOI9DvX8OFtZ9gKm3rbCUmDvhZkq4ZT3CvSjp/A4mQPzo+suBKh0/WaYevocponfCXS/hVvAIt5aktzZMVOUn9VvPNnLVUNpRHVhe9E67PCPhNvJol8+LvOyVdrlP8vsS1PmDFeHLsDp8BdaBh6V97ocNlV7im4ZK7p+3Xcagxkp8X0l8X0Nl/q2E/29YVfS1VHlJuP+Wdv8jbAov2aa9XrZNe/0OdhS9U47ZEn89j3J8GGtbPzdM/tbDSqq9QSW7GywT/1pYV+tNuH1QZyTcZhJuBKqLhDtb6v0uWAPOlfDmw3qiV+W/wNL5wbHJzwIJfzEqeYAJf7CEXwA1S8KfIv3ZNFgMzoCllb3U03RYWcxrinltlS5YH86BXVU6YC+4CPZW8cO+cCEcpM1d8ijpKeVRjp9Jfj+HUerZKf3fBWmfX0L93VJYUsydcM/8TbilRc6TbRNOGWmfFWCcanOS//LSr1VwpdcaKP2HR7jNJNzmEm4LCbethNtKyrMNLCfmTr2nSrg1POp9mcjTcsu0n3ul/39Q+qcVkv/7Rc5Wwupi7/R7mRJ+ZY9+L1PKeaKU6yQJd4r0e1kS7hRX/7tdwovw6H+rSnjVoCqf6uKvhXKLP7d8h6Lqir+V0m4flP5ntW3k/CFplw+7nhtxt+c+197LF/+/Cpr4L8Ak1Q8UNP7WqzSIv2niT88FxV+9Aib++lCZN4BlYOMCJh03w9qq3AqY9tUUNld5ge1VvcMuKo4CRv5bwr6q3uEQ2BoOV/UPJ6v6h1mwIbxD600670Odk3RmSDoL6nZu/pIlnWUKGDlIgYWV3MIEVT4wUZUHLKVkFSYrOYaVlAxIPqrA+qq+oKqParC1qi+oZLImTJfwHDkdPMik6yadrnz9k1/6JxgGs/2mvc7xGzmaC4uo9g/j4TxYTPRO/5Qt4f9Lwnf3T90l32mwkRpnwDawP2wLe8Lp8BY4X8wXwF5wL+wND4v5UXgbfFvlC74P+8LzYv+jyOf6wSY9X0t6ElC7JD2PyXNsizwXn4Dl5XlVVz/XTTq32UY+noa3wmekH9xuGzl41jb1vwMuVONjeLeKBz4En4OPwN1wC9wDt4l+lzxP98AX4MsS/xc6HpOPhqgzQ+QbcJKvEN0+5Wy3tNey0s+Wk36gvLTbHKXEfyObcpB2d178317AjGOGwupwGKwF02FdVaciVxmwMxwBe8NRIl+j4Tg4RuptLFSyMB7eAyfApTAT3q/6KfighLsJTpb6zYIn4FT4EZwOlRzNgDmi/w3eCX028grD4F0wzjbh1YGjpf6TVRzDTL5DLT0f0r/jnXxbue7uu0F362/Q3fYbdHfwBt2dcbkrZuV118Gf6+7cDbrLcbm7kC/eW1zxWunXdtfZ5S7uBt0l/427IS53qTfg7j4sW4i7CdFGrp9BzQ817l71m3Zwym/617N+01++5Tf95TswTc0rYT/4ERwu5llqrh1iZU+FH6Ofq8alcAX8Bq5T40q/ab/fw9PwB7/pjzaHmv7oR7+R28vwLzX3hkkk9gpsAn+FLeFvsB38A/aEFvEOhX6YCQvCWTAOPgDj4cOwJEzwMUaCKTAFpsLysAk=
*/