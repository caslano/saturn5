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
    
    T& value() const
    {
      if (this->is_initialized())
        return this->get();
      else
        throw_exception(bad_optional_access());
    }
    
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
P21LPPXf9RKkX0j0H/PfFCU+/BO/Oh/2P7jZBOb/SyRuMSgQ82HiqGYznGzZcf6b+2omun/H8f3M/3Sdbo/pf4KhykTP8k9fuOQ+e5De9H78fw4QGxaGlvIiJGP/r9ATAQ/W64zqnv9IXKWMx1PiwzdU/xOQ8fTzfzLw+0w02O73D+HH/7bTA8/Swf8AecTmPob9nx7mUbj+d6+4T9D/c2v44eKL/HuLwPOfPdxEsoH/kkvsPo5tGiQfgP1wSf4r7ZGvEybZ/0+H4VlGf/7LmXf/vyorAP8p1j9C04+ukcT+V1Mm2LH+1z4CbFhk/9CYHPZE4l8PylHYD74e+nDo5UPyDxbYUdj/8rRGmHtiM6iC7bnt7dv9cFX/F59GIuf0Ys1601mxtMBZ0caq7M+5gp1Jc6tQQzn3CPcV8uyKn05yyBY3rD3unX93XNe8id7sKLeE4eTaIGp+ILP/CGL+dVVaKmzMXuLikLUxrVwqw+iTgS8y4UCgxXa03cS/3M7FXTa4VpxKd76n877qNwW+JcHgUaJ0CQMHFb2WVFoGfxFDc/72o3HOttVz8KR9wszRJ+5S6Ck8//4mjwiQMS0q2SK/irl/7/SWaLKR6IT3gr7VNv+0U0BOTJyqM1Ws0OFOxsrLN+Vu87KfTdVaWELHI5dzt5llKSLuMLnjwgyfpBzxtb5UkkGHa3CYbOiUcGYNy+P9ySix5NxJp101dRLnVZW0nzxxsIEm9bYm7vR70pr3RI5Cb0hzs8gWcvC95JSwK/mfbUQ8I7kV0e+WtHQIH17zSmLkojSk0qh7VubYPQ4el5a/XnaWE7n9efbd/dXkiwboDJPaTboXUY4Cue0kGs9mu/5eoujUgU9SJ03J4JnrewCBA53dG+fqaPMxgpYxClyXrFba2hyTbFYTOhaf9/nP8Bejl/r6KJ5PKuHBUnEUBPkVnpGLm1Iu2mQFy/yaEDeqEVNv5SoHgNPKaKNuxIRfte454rFBDsQGGuLDFgu93/5++oXSxoRghFjk7GdDKFHOfYbyScWWQa83y+7s3Xqr6QUN/BN+3yv0XbOt/C7Y4IOhmh30fWzxe9w61DhkaimrwdTyNnmjtV8yM0WgRed3PftzY0xZ1ptt8kjIzZGTyaWYjC/eGeHZtIZka8Z1OpWpdvDmZrp9OGlramPEJslh15w4PaHNlZnP/MuVSE+/BYjQn/1fWZZ8BXyCyV2PPUmgpjxZhF/wbRmsKS1ELgkeHrL8leXXhbO0P622ymPX9asD4mTEWNFeUWGHaXZwqhlWy/6KU7TkpEXIpwJmKNhZ5NLiGe8R+gehoOLFZIQhzRQJVU9v3Y8zq26qSTTq0gKYeMZbXudXecM1KK3RetY3k0qZSlImemu14/RiP2hZvgEsw8g1wRV7kyXVLgX/GIBafp/1IZfrlof2M9ZiaCbRLd9Wa1mII+k+722MweT5Xbz+JU+8mSuXekk/3qIovepookgKarJMFmCe8Yj6nnQzxvENSvwlwnXDpna0BU416AOvWt/sNKNpbkep5AKjSa4K1jz63S5hfYHb+J1X8mHxtXQPqvTeOM2xuJpx8Rm9BZrkXG306VCP8uyXDj/Lv6iMXNpNZzaz0WGI/sxPFWOD2hW/q4BZfsNa4BZjllQ6bWKySouAeoQ7oXly8WfUtVmY7G59/90TvIOz4FlEXsDsM081riAE/ShbGmuiW7xl7Kym8hUwTb93I4rcslWDdCC2mV1njFbTuHsONvxxau27xDNxA/1t3Owz90ZKni3dcbkw0zZIfeoHz5blnhudz+iOI/TyIbCXNs3mnuIXevQSFsbbiioNplpP4WMhEZXZbJu+mZ1Hw2pRoUtEEyejA1QCSZcGOYuqmpUK516AEnZf3m+9ngK/ql6X3RKmMe+bOlAC9JveT62Lv20qquErtzfyIPxGGnPG4ai4uQ35HW9MSmgWQXcDcV0Rs9+CiFqHponiR6aLdiyRQkRZ8EZp7HXeeKx4TDGJaO0Gwv2RpDEZUvbDT6gCdmMa0i4v8Y5bje6az+q0Tsq2Us62JSRczi96V7sNaBmIXKkA4+BTWY36IN6sExjlRdt4AldXffZu+F9mz5V6G7NqWztpVLMmRfqC52ab/M2B2W74jfJ58995jkUB9f1WE5DmVnODoOdK9+44dgmSilXK3rRJQAsiymv5QtK+mVcAD0ojP6oZfRin5E1o842XdeiP/QS6Z8An/UyXzzgPaK9ptCNPp6kP37XT1n8FLf2Uhn8udfbOnFySYkJs047MsEvQLmmvs4EVchkY6rY+6QuIpuoNfcmOhHoY/n42oH5IKrNIt0auoyszO/FbU1L7yJSmTjAAN4//WPaKaf6TrJrVOt1pSAWkpmEzuK2/a3eO75X3VEpTzp1NDO3i2fbNb/GaO+8jhndbvzbf7sDajcgvvwYwDeeLJEuwqXK/PXyxEm7ekF0ohbZXN7I/ErUjPVOsIxvdjPt5XWdHejBhduZavAX1LlVdLxvgCjOm0mfr7T8c6Pn+d/Pv+XlANj0EGjfdsyk6rc9G6GirNfMi0ljKNOuz9K8bgNWnZvqNhGfKrf79WUTfk1XXyzPviQQ19p1dw0Dg2d3vxwfD2jcGpcZx7Ef8yT0yOvrdT66LodMLPcmdTaLa3ZRmcOcasJvFIHTaqGD41Nl1jOkM4VOWT7TeciqzI/42987AtkFqVUg5yMMqQ7u3mpzndt1ZNfGXg10zq2e6h6gnKhXI+mteghHUWZZAvNLUl2EMH8X6pTLnKep5PyPB8mukddrK7+mJLfezXvPnV/O8XEyHjgDylJKCm7/WP1ojW1HJxJ/2WWNmS3STOz/Hsae90+0cUvnl6OaL8vNdON7Xxo/4WKWqnvKYqCIuD9KhgZtlPHR2kMbW3DpfR6KTsHnNZ11BdVbN/WWSF0Z3owCmG5U4rOZaf37l/1U3Ry7htBDKOPpbCfBkige++fSYzhw0lfVp9LnjuSfwVSd0gON+qtgy2O/873PdTvZYsohxwpjNqL7Xregorl6W8lUJfWZWcZnNm6xOibeSwOcInEsOeKlpAh/9F59ps+bdmMiLgd/nIo40VDC9nRCXDrFSTit0h2qWUY84MKWhrcBVjB7Mb57AAgVC6tcYz8PM1HuZZ8OOmtzJXdPk71tikFO/hxebchE5o6huSOxRjjujyQ2JDOyguiGt0UL7KmzYQeog2UZU+8R3oTnaTDfi/nCf6C55qyXg/EIAH6b8BDqKopsqfLVZ+m5rX43qpijcNC03GZ9d8tX8KuVuvCfu7S4JTt/IlgQXsGbrhVH6tmSu7B0rjOU+ONo9ZctQ0Qi6Pe2V+Y1hYx388s4mjsHu67Une2pTFAjVlCqgpvgGJdwsDrbU7pM2Qf2krTQA6EWZmzeld2q831+/LbY5Z4E53IdOeZTYaKNG8W6TutzeXncnH/XxmcZAuuyYYNJIhN/PprBh262+htkzrhlW5JMIxJsV6FQ0TEjPksUYRY6cfNsLTGXnCdsCKvnqUPS1vAvxKNfMD2oWeX7ure1zUsOstRVZlaGuMl6GUMj/k2Ss2VOde7i9O1bbtxFf/YoK8EGM3JidW7mX5jiiR0ddJeZM/dbs7ONETOcNVIYcrK4XExZpDQcqAnvgqieHPWgDpkMTAp3I7sT4Yy0NrufG766qzCzquW+UEkR3LEImtUeg1n03uozcyleCV+r5HmxaGlhUUE+kQwhSByr+CTpvpVxJfzg6fBraHIpqULgCOnKBp6tzHVYqBRSHXlwwiFFwKm2YO3racqZm+y6uZVAEt8ldVenl/yEPTjyEbjYDKILtk9EylV+LLkEaO44wydmlNoO9XcsQXfYV615j6AuqggIPyKCUDqcnqLmz5v7nizP+DagaCYxn6EVdXhCFAe/iECzszrKjzXnMXbzMpA+xCjYVh3ALaLf2hTvfS45DPkAru0K73dfaan+lONU0hhZME+6FuGU/8TnUK4nY8EyNXhAPs+27sNIY38j1lIxeibsmZx2eTKuuFdPN2Fy0IUuYUJ+otWlw/mx/Ftc2ip51Hku+kgw6MaFC4ubbUqJntyNqxsOur9aTvF9Yn5UPLveu1gWe0QXZ+r6zdTXNkAhwLiAZRD+b5rF2+DRk4oOdx4rG5NYNlELprtMVmq8XUDAOzhqz0cdB0YehQHQko93jZ6r96BKTHk/1QSrjJEt932aVZl0TBRMQgYz1UX5aTa1H+t+ictxbswx26vcal93sPkZBxonXiUDeb4sC6HI0nd2LXlNalg45nnwzlh0zRnKzJwYlXSw2PeqgAOlrekzUwep69dBz8G1bVyHkPOxSEPq+7dQAkcFh6lC2K375poIMnQAifBEu5mbu8YY3lfh3Z4LThjSSC1q1SH7iyRdUpXK21Bh/I2MCEULLnWd0XbhbDR6vUZVSQ/ttzCheQQLwV249A9m1Qy2XrT12bJOkdkbtFuZ6dtlnftal77bzWm0SI/tpEs8kCwPNCgzV07097biU9OM9ecrl6Ba3dwEbB6/OgSqsqy4Fzu529DJ5BKNg38MuSzASHs/8JpDTMGol/totzUyuHxyq8uytjE6eV4Sjbk5hBk1aucZp86Vt/h/qYHsuGGcH7slhW35r+eLDB+93fS0guPvdK4XtF8fY3QWN5X3Qt0HOL4m8zmXK+foKM8yEIuaZoj3m02RRui97mi+9GLadI33c5KSiNpBaH1TTTsU3O15c5Aip54LKpjnP5vkVwaozaqVvQfenjGzR554LDDLbFzzHCUHDqaCyM6haLsjuqsy8NF+iNU2FQnFjaKitVfV+KX9a5szjNs+jld8sOA5qIrI7lfkCabsDvLkb/77hxLhn6f8C+pF/tOkDVPQm78FC9OpjX19derXBYwFULlT03Hc6uRQkF6XxeKTz1uxcxt37umSMnrsBT4gA9ndjro1OlEZAzPLzubAp6FSVhPfcvr3DUzfg+KjRI4utr6UPpncnk+eu3bU75oHYAq6LbrX2EChQnvvII7Sb7JHud4eIUjQ7EPi86eGua9uVCIAA2D2g5tW7rRV6BKvOAbDy0OZdDg80ceuhRADCwLdY4S/CgHwxG9aAt2L2wgea1+pts9yPGnA3CIA1zDCjlxmRhFylpxmf4dI6Yz+PS4NNHyzPFVedkTUNGrUqL1p3v4+kl9Mgatf3hgr84Kaw4ppT7R8gQc07S1v1K7u7D4MOLf0DxFdjWz4XRx9gJClp114ZByhTq8JyHa/UqVnRcv2Xl7sSEZCYjV0joZ0p1TNnYbuCX38SijJGwT6GEvNSZCjJNxeM99gWBKNcTuzPS+sjtpaGBM3fyIVZ6DvQnRWxQHJcNy7dzCKllSC3KU/F+qrzcEmq1M8aq87Q94cRyDnwsCvrXZ23Jyq98/Yye5auWOO8kZRVuh9smXFw3ygcX+8brN160g0ZARu3nFwfRsS8feHddpIUbDqbng2bDTeaEvW7i42ZpYtE3fiEGLuHzTbQq6nTui/jeq1qHzUyrZbfnqcj2059DVFcih23l35X/kcK67eXYibpjrQI3xageSBjemviCAeojd5In513tRxHN7jz9sHU9fLjBlWddBB/y2tKzN1EpDoKKjCSbdN2h3puuTJEK6XmIeO6DEVeEfvovaWfSBOPs7Qej6znImIcgmvQ+1+v3SHQWOxAQtLYsyeILIfjsuxhrx1NvW6Pk5368ExUQ1y8GT2/4Pbu41hn4PTu4+0ehcHD8uNwVaTnmxLV3Lul7GfK9+JKuvHEglpSGotm2sBZbBXYOyRtiYONlg99UKnyfRp32hT07GSLVAoHoXzv2QvijT6XzhYVu7zv3U+8uXj9GlS0e84gernL7CP/cntXNLFGj2cCYr1tDGWOgaLHd69ZtYGWqdBc31G3hk9b8eKt9OAD3Iy2SfSBzGwEqz2S/rDslCAWtDolDiK3VykBIVwokI07bT+sIXdUNJ6rh2np00CfJIeT5AFXxnn7e/3RlvC+hVBnY07xoENEQjc7Wqr29hh84nPctiE9Bu6Gmg0BN5PszzD7vnDOptqrH4t33mpkwNBqEGOXiJ5gmbbHAFZUl0wbZfWt8SVSEflS80hc7j7sL+htg1qc/3UQ8jrtpt/SPh/ClxzqV9r36SwoUYYxw/EbhAUP0id5AU/vKYjd0nhB560Oe966e8KK/RvWIqiIOF0NiYWh4H8FNa7Fmad9Pi56bRzm9Uk4/eGdvn/dSqRyuTJqRlt4MvnXltUDVi99eS85l3EjztAqeEd7BcbIVj9J/fnvyzmPDPHTXvQk8zKxxcxSjiAxXECG74Vms8Xfy3oZd+I11TZxEslHJJvT1BZ4W6Qs67phAHxCBpN1ioMy/2wWkQBKcmSZNGPPpiZDy8XDCzSDwyNjicM3HYODqZ3RRQcZyRmFP+bJdISGUa2lJ+VFh4bGPpfTOsYfuXW0M55D+86LTZEJl0UeMoSt7xsy5u7eVzMMZqwqGblcCtuegnqcH6fOvq6jHcuaqj3Y5hHxKFx2OYwdL/1RApYp9B1njW+K26fAnQGyF/lXQRIK9HVLiPox9ZJ9NYWdEtNrUCQPm7NAxRvFnkOI6X02nP2s8lLjr290554xpzKf2ovpZYAVJkIkdHzk8fpmxGCcupnXhIFZwISqVvbFROfVZ2oq5o/JjwdgxnP6JSYfPBkrNGfLiUXWb3+fLL7nKBU44CLU7k80thAmRs5cbekt4m+OX08PccIozOuC92svwKaN6YpNTy/lf1vL3djYk5VrxNX1uIj5tTItlFewGynsBlpLfib6EONGNrC82Hns0ue5rOjTfRPzeWcU7iU7G9lBm6YfQ1mNaq5+qzrLG1H+kj2MkfjtORaHtX9q1+2rX6K9l7HKcSvSW4kImg7f57K0O5E8l+sjhzcDgz3FQc2lWQeug329RcuHcbLDwEnCLYExl/cX066cf8J7q7fFwvX2f2vryQJG3sqkbW5wr23zcEei99jLgGonyUZuEZtz/hU81HkkVTTwJv3iIp/JZXmoca7FFxkxBbO7AJ/fvdf4VDCq9ojr0NekOx37bPpVn4TBJhnZx/Cr+KhAutLQvQYgXhZ1eG5+Jt1hFIw/SUUykXGV+gI/s2Wr6z15/cQ85e6qfPPFe2DfBs0a3WsME3+lzFYMKj+XV2ts11jD9lmrGHJKm3RfIhU/v15ovy28pidWWMhibwYIZGx/WxCN2lF2YLW2Kbs6/35c9zOp77Q5bw27l3HU8S4tSW5TDuXfH/nsKWauXi4/ASz8m2Sd6hVupiZbcXhFlleuJCaKulPkVIYqDQ/sFww7OtNbf9ZnFWSdtiPp/QlXS8jnlFMVQAmlyt0NWzfPPZTEW9Hj5cPZD3tDxfISpvlL8RrjJj2HwdiyUUrZFFMXcT94YcKWi7ttT6VMOhpr0eQh8yy7ORs5qSW83px48gJqbxWn9Gc15IZ8v8vivejL+zH4PjUVY0rdD4qT0D5hHawGhdbARikjv0Si5XEpg6ihGr4RgdZbaaLiZepfbERK7lDrNXXzrO+nK9go2x23tuTAAkE3ynxiZ6ZbY/arCVi+wIgwFGxk1BTuW3jdKcq0xWVMn+BvsbhrFVZ+McogfeoL1E153BIiDMsoKE4qIB3omDyj
*/