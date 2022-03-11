///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
//  Anson Tsao        - for the initial inspiration and several good suggestions.
//  Thorsten Ottosen  - for Boost.Range, and for suggesting a way to detect
//                      const-qualified rvalues at compile time on VC7.1+
//  Russell Hind      - For help porting to Borland
//  Alisdair Meredith - For help porting to Borland
//  Stefan Slapeta    - For help porting to Intel
//  David Jenkins     - For help finding a Microsoft Code Analysis bug
//  mimomorin@...     - For a patch to use rvalue refs on supporting compilers

#ifndef BOOST_FOREACH

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#include <cstddef>
#include <utility>  // for std::pair

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// Define a compiler generic null pointer value
#if defined(BOOST_NO_NULLPTR)
#define BOOST_FOREACH_NULL 0
#else
#define BOOST_FOREACH_NULL nullptr
#endif

// Some compilers let us detect even const-qualified rvalues at compile-time
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)                                                   \
 || defined(BOOST_MSVC) && !defined(_PREFAST_)                                 \
 || (BOOST_WORKAROUND(__GNUC__, == 4) && (__GNUC_MINOR__ <= 5) && !defined(BOOST_INTEL) &&       \
                                                                  !defined(BOOST_CLANG))         \
 || (BOOST_WORKAROUND(__GNUC__, == 3) && (__GNUC_MINOR__ >= 4) && !defined(BOOST_INTEL) &&       \
                                                                  !defined(BOOST_CLANG))
# define BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION
#else
// Some compilers allow temporaries to be bound to non-const references.
// These compilers make it impossible to for BOOST_FOREACH to detect
// temporaries and avoid reevaluation of the collection expression.
# if BOOST_WORKAROUND(__BORLANDC__, < 0x593)                                                    \
  || (BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 700) && defined(_MSC_VER))                   \
  || BOOST_WORKAROUND(__SUNPRO_CC, < 0x5100)                                                    \
  || BOOST_WORKAROUND(__DECCXX_VER, <= 60590042)
#  define BOOST_FOREACH_NO_RVALUE_DETECTION
# endif
// Some compilers do not correctly implement the lvalue/rvalue conversion
// rules of the ternary conditional operator.
# if defined(BOOST_FOREACH_NO_RVALUE_DETECTION)                                                 \
  || defined(BOOST_NO_SFINAE)                                                                   \
  || BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))                                        \
  || BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(1400))                                   \
  || (BOOST_WORKAROUND(__GNUC__, == 3) && (__GNUC_MINOR__ <= 3) && defined(__APPLE_CC__))       \
  || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))                                         \
  || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3206))                                      \
  || BOOST_WORKAROUND(__SUNPRO_CC, >= 0x5100)                                                   \
  || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x590))
#  define BOOST_FOREACH_NO_CONST_RVALUE_DETECTION
# else
#  define BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
# endif
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/end.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/reverse_iterator.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/foreach_fwd.hpp>

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
# include <new>
# include <boost/aligned_storage.hpp>
# include <boost/utility/enable_if.hpp>
# include <boost/type_traits/remove_const.hpp>
#endif

namespace boost
{

// forward declarations for iterator_range
template<typename T>
class iterator_range;

// forward declarations for sub_range
template<typename T>
class sub_range;

namespace foreach
{
    ///////////////////////////////////////////////////////////////////////////////
    // in_range
    //
    template<typename T>
    inline std::pair<T, T> in_range(T begin, T end)
    {
        return std::make_pair(begin, end);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_lightweight_proxy
    //   Specialize this for user-defined collection types if they are inexpensive to copy.
    //   This tells BOOST_FOREACH it can avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_lightweight_proxy
      : boost::mpl::false_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_noncopyable
    //   Specialize this for user-defined collection types if they cannot be copied.
    //   This also tells BOOST_FOREACH to avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_noncopyable
    #if !defined(BOOST_BROKEN_IS_BASE_AND_DERIVED) && !defined(BOOST_NO_IS_ABSTRACT)
      : boost::mpl::or_<
            boost::is_abstract<T>
          , boost::is_base_and_derived<boost::noncopyable, T>
        >
    #elif !defined(BOOST_BROKEN_IS_BASE_AND_DERIVED)
      : boost::is_base_and_derived<boost::noncopyable, T>
    #elif !defined(BOOST_NO_IS_ABSTRACT)
      : boost::is_abstract<T>
    #else
      : boost::mpl::false_
    #endif
    {
    };

} // namespace foreach

} // namespace boost

// vc6/7 needs help ordering the following overloads
#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
# define BOOST_FOREACH_TAG_DEFAULT ...
#else
# define BOOST_FOREACH_TAG_DEFAULT boost::foreach::tag
#endif

///////////////////////////////////////////////////////////////////////////////
// boost_foreach_is_lightweight_proxy
//   Another customization point for the is_lightweight_proxy optimization,
//   this one works on legacy compilers. Overload boost_foreach_is_lightweight_proxy
//   at the global namespace for your type.
template<typename T>
inline boost::foreach::is_lightweight_proxy<T> *
boost_foreach_is_lightweight_proxy(T *&, BOOST_FOREACH_TAG_DEFAULT) { return 0; }

template<typename T>
inline boost::mpl::true_ *
boost_foreach_is_lightweight_proxy(std::pair<T, T> *&, boost::foreach::tag) { return 0; }

template<typename T>
inline boost::mpl::true_ *
boost_foreach_is_lightweight_proxy(boost::iterator_range<T> *&, boost::foreach::tag) { return 0; }

template<typename T>
inline boost::mpl::true_ *
boost_foreach_is_lightweight_proxy(boost::sub_range<T> *&, boost::foreach::tag) { return 0; }

template<typename T>
inline boost::mpl::true_ *
boost_foreach_is_lightweight_proxy(T **&, boost::foreach::tag) { return 0; }

///////////////////////////////////////////////////////////////////////////////
// boost_foreach_is_noncopyable
//   Another customization point for the is_noncopyable trait,
//   this one works on legacy compilers. Overload boost_foreach_is_noncopyable
//   at the global namespace for your type.
template<typename T>
inline boost::foreach::is_noncopyable<T> *
boost_foreach_is_noncopyable(T *&, BOOST_FOREACH_TAG_DEFAULT) { return 0; }

namespace boost
{

namespace foreach_detail_
{

///////////////////////////////////////////////////////////////////////////////
// Define some utilities for assessing the properties of expressions
//
template<typename Bool1, typename Bool2>
inline boost::mpl::and_<Bool1, Bool2> *and_(Bool1 *, Bool2 *) { return 0; }

template<typename Bool1, typename Bool2, typename Bool3>
inline boost::mpl::and_<Bool1, Bool2, Bool3> *and_(Bool1 *, Bool2 *, Bool3 *) { return 0; }

template<typename Bool1, typename Bool2>
inline boost::mpl::or_<Bool1, Bool2> *or_(Bool1 *, Bool2 *) { return 0; }

template<typename Bool1, typename Bool2, typename Bool3>
inline boost::mpl::or_<Bool1, Bool2, Bool3> *or_(Bool1 *, Bool2 *, Bool3 *) { return 0; }

template<typename Bool1>
inline boost::mpl::not_<Bool1> *not_(Bool1 *) { return 0; }

template<typename T>
inline boost::is_array<T> *is_array_(T const &) { return 0; }

template<typename T>
inline boost::is_const<T> *is_const_(T &) { return 0; }

#ifndef BOOST_FOREACH_NO_RVALUE_DETECTION
template<typename T>
inline boost::mpl::true_ *is_const_(T const &) { return 0; }
#endif

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
template<typename T>
inline boost::mpl::false_ *is_rvalue_(T &, int) { return 0; }

template<typename T>
inline boost::mpl::true_ *is_rvalue_(T const &, ...) { return 0; }
#else
template<typename T>
inline boost::is_rvalue_reference<T &&> *is_rvalue_(T &&, int) { return 0; }
#endif

///////////////////////////////////////////////////////////////////////////////
// auto_any_t/auto_any
//  General utility for putting an object of any type into automatic storage
struct auto_any_base
{
    // auto_any_base must evaluate to false in boolean context so that
    // they can be declared in if() statements.
    operator bool() const
    {
        return false;
    }
};

template<typename T>
struct auto_any : auto_any_base
{
    explicit auto_any(T const &t)
      : item(t)
    {
    }

    // temporaries of type auto_any will be bound to const auto_any_base
    // references, but we still want to be able to mutate the stored
    // data, so declare it as mutable.
    mutable T item;
};

typedef auto_any_base const &auto_any_t;

template<typename T, typename C>
inline BOOST_DEDUCED_TYPENAME boost::mpl::if_<C, T const, T>::type &auto_any_cast(auto_any_t a)
{
    return static_cast<auto_any<T> const &>(a).item;
}

typedef boost::mpl::true_ const_;

///////////////////////////////////////////////////////////////////////////////
// type2type
//
template<typename T, typename C = boost::mpl::false_>
struct type2type
  : boost::mpl::if_<C, T const, T>
{
};

template<typename T>
struct wrap_cstr
{
    typedef T type;
};

template<>
struct wrap_cstr<char *>
{
    typedef wrap_cstr<char *> type;
    typedef char *iterator;
    typedef char *const_iterator;
};

template<>
struct wrap_cstr<char const *>
{
    typedef wrap_cstr<char const *> type;
    typedef char const *iterator;
    typedef char const *const_iterator;
};

template<>
struct wrap_cstr<wchar_t *>
{
    typedef wrap_cstr<wchar_t *> type;
    typedef wchar_t *iterator;
    typedef wchar_t *const_iterator;
};

template<>
struct wrap_cstr<wchar_t const *>
{
    typedef wrap_cstr<wchar_t const *> type;
    typedef wchar_t const *iterator;
    typedef wchar_t const *const_iterator;
};

template<typename T>
struct is_char_array
  : mpl::and_<
        is_array<T>
      , mpl::or_<
            is_convertible<T, char const *>
          , is_convertible<T, wchar_t const *>
        >
    >
{};

template<typename T, typename C = boost::mpl::false_>
struct foreach_iterator
{
    // **** READ THIS IF YOUR COMPILE BREAKS HERE ****
    //
    // There is an ambiguity about how to iterate over arrays of char and wchar_t. 
    // Should the last array element be treated as a null terminator to be skipped, or
    // is it just like any other element in the array? To fix the problem, you must
    // say which behavior you want.
    //
    // To treat the container as a null-terminated string, merely cast it to a
    // char const *, as in BOOST_FOREACH( char ch, (char const *)"hello" ) ...
    //
    // To treat the container as an array, use boost::as_array() in <boost/range/as_array.hpp>,
    // as in BOOST_FOREACH( char ch, boost::as_array("hello") ) ...
    BOOST_MPL_ASSERT_MSG( (!is_char_array<T>::value), IS_THIS_AN_ARRAY_OR_A_NULL_TERMINATED_STRING, (T&) );

    // If the type is a pointer to a null terminated string (as opposed 
    // to an array type), there is no ambiguity.
    typedef BOOST_DEDUCED_TYPENAME wrap_cstr<T>::type container;

    typedef BOOST_DEDUCED_TYPENAME boost::mpl::eval_if<
        C
      , range_const_iterator<container>
      , range_mutable_iterator<container>
    >::type type;
};


template<typename T, typename C = boost::mpl::false_>
struct foreach_reverse_iterator
{
    // **** READ THIS IF YOUR COMPILE BREAKS HERE ****
    //
    // There is an ambiguity about how to iterate over arrays of char and wchar_t. 
    // Should the last array element be treated as a null terminator to be skipped, or
    // is it just like any other element in the array? To fix the problem, you must
    // say which behavior you want.
    //
    // To treat the container as a null-terminated string, merely cast it to a
    // char const *, as in BOOST_FOREACH( char ch, (char const *)"hello" ) ...
    //
    // To treat the container as an array, use boost::as_array() in <boost/range/as_array.hpp>,
    // as in BOOST_FOREACH( char ch, boost::as_array("hello") ) ...
    BOOST_MPL_ASSERT_MSG( (!is_char_array<T>::value), IS_THIS_AN_ARRAY_OR_A_NULL_TERMINATED_STRING, (T&) );

    // If the type is a pointer to a null terminated string (as opposed 
    // to an array type), there is no ambiguity.
    typedef BOOST_DEDUCED_TYPENAME wrap_cstr<T>::type container;

    typedef BOOST_DEDUCED_TYPENAME boost::mpl::eval_if<
        C
      , range_reverse_iterator<container const>
      , range_reverse_iterator<container>
    >::type type;
};

template<typename T, typename C = boost::mpl::false_>
struct foreach_reference
  : iterator_reference<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>
{
};

///////////////////////////////////////////////////////////////////////////////
// encode_type
//
template<typename T>
inline type2type<T> *encode_type(T &, boost::false_type*) { return 0; }

template<typename T>
inline type2type<T, const_> *encode_type(T const &, boost::true_type*) { return 0; }

template<typename T>
inline type2type<T> *encode_type(T &, boost::mpl::false_*) { return 0; }

template<typename T>
inline type2type<T, const_> *encode_type(T const &, boost::mpl::true_*) { return 0; }

///////////////////////////////////////////////////////////////////////////////
// set_false
//
inline bool set_false(bool &b)
{
    b = false;
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// to_ptr
//
template<typename T>
inline T *&to_ptr(T const &)
{
    static T *t = 0;
    return t;
}

// Borland needs a little extra help with arrays
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
template<typename T,std::size_t N>
inline T (*&to_ptr(T (&)[N]))[N]
{
    static T (*t)[N] = 0;
    return t;
}

///////////////////////////////////////////////////////////////////////////////
// derefof
//
template<typename T>
inline T &derefof(T *t)
{
    // This is a work-around for a compiler bug in Borland. If T* is a pointer to array type U(*)[N],
    // then dereferencing it results in a U* instead of U(&)[N]. The cast forces the issue.
    return reinterpret_cast<T &>(
        *const_cast<char *>(
            reinterpret_cast<char const volatile *>(t)
        )
    );
}

# define BOOST_FOREACH_DEREFOF(T) boost::foreach_detail_::derefof(*T)
#else
# define BOOST_FOREACH_DEREFOF(T) (*T)
#endif

#if defined(BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION)                                  \
 && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
///////////////////////////////////////////////////////////////////////////////
// Rvalue references makes it drop-dead simple to detect at compile time
// whether an expression is an rvalue.
///////////////////////////////////////////////////////////////////////////////

# define BOOST_FOREACH_IS_RVALUE(COL)                                                           \
    boost::foreach_detail_::is_rvalue_((COL), 0)

#elif defined(BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION)                                \
 && defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
///////////////////////////////////////////////////////////////////////////////
// Detect at compile-time whether an expression yields an rvalue or
// an lvalue. This is rather non-standard, but some popular compilers
// accept it.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// rvalue_probe
//
template<typename T>
struct rvalue_probe
{
    struct private_type_ {};
    // can't ever return an array by value
    typedef BOOST_DEDUCED_TYPENAME boost::mpl::if_<
        boost::mpl::or_<boost::is_abstract<T>, boost::is_array<T> >, private_type_, T
    >::type value_type;
    operator value_type() { return *reinterpret_cast<value_type *>(this); } // never called
    operator T &() const { return *reinterpret_cast<T *>(const_cast<rvalue_probe *>(this)); } // never called
};

template<typename T>
rvalue_probe<T> const make_probe(T const &)
{
    return rvalue_probe<T>();
}

# define BOOST_FOREACH_IS_RVALUE(COL)                                                           \
    boost::foreach_detail_::and_(                                                               \
        boost::foreach_detail_::not_(boost::foreach_detail_::is_array_(COL))                    \
      , (true ? 0 : boost::foreach_detail_::is_rvalue_(                                         \
            (true ? boost::foreach_detail_::make_probe(COL) : (COL)), 0)))

#elif defined(BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION)
///////////////////////////////////////////////////////////////////////////////
// Detect at run-time whether an expression yields an rvalue
// or an lvalue. This is 100% standard C++, but not all compilers
// accept it. Also, it causes FOREACH to break when used with non-
// copyable collection types.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// rvalue_probe
//
template<typename T>
struct rvalue_probe
{
    rvalue_probe(T &t, bool &b)
      : value(t)
      , is_rvalue(b)
    {
    }

    struct private_type_ {};
    // can't ever return an array or an abstract type by value
    #ifdef BOOST_NO_IS_ABSTRACT
    typedef BOOST_DEDUCED_TYPENAME boost::mpl::if_<
        boost::is_array<T>, private_type_, T
    >::type value_type;
    #else
    typedef BOOST_DEDUCED_TYPENAME boost::mpl::if_<
        boost::mpl::or_<boost::is_abstract<T>, boost::is_array<T> >, private_type_, T
    >::type value_type;
    #endif
    
    operator value_type()
    {
        this->is_rvalue = true;
        return this->value;
    }

    operator T &() const
    {
        return this->value;
    }

private:
    T &value;
    bool &is_rvalue;
};

template<typename T>
rvalue_probe<T> make_probe(T &t, bool &b) { return rvalue_probe<T>(t, b); }

template<typename T>
rvalue_probe<T const> make_probe(T const &t, bool &b)  { return rvalue_probe<T const>(t, b); }

///////////////////////////////////////////////////////////////////////////////
// simple_variant
//  holds either a T or a T const*
template<typename T>
struct simple_variant
{
    simple_variant(T const *t)
      : is_rvalue(false)
    {
        *static_cast<T const **>(this->data.address()) = t;
    }

    simple_variant(T const &t)
      : is_rvalue(true)
    {
        ::new(this->data.address()) T(t);
    }

    simple_variant(simple_variant const &that)
      : is_rvalue(that.is_rvalue)
    {
        if(this->is_rvalue)
            ::new(this->data.address()) T(*that.get());
        else
            *static_cast<T const **>(this->data.address()) = that.get();
    }

    ~simple_variant()
    {
        if(this->is_rvalue)
            this->get()->~T();
    }

    T const *get() const
    {
        if(this->is_rvalue)
            return static_cast<T const *>(this->data.address());
        else
            return *static_cast<T const * const *>(this->data.address());
    }

private:
    enum size_type { size = sizeof(T) > sizeof(T*) ? sizeof(T) : sizeof(T*) };
    simple_variant &operator =(simple_variant const &); 
    bool const is_rvalue;
    aligned_storage<size> data;
};

// If the collection is an array or is noncopyable, it must be an lvalue.
// If the collection is a lightweight proxy, treat it as an rvalue
// BUGBUG what about a noncopyable proxy?
template<typename LValue, typename IsProxy>
inline BOOST_DEDUCED_TYPENAME boost::enable_if<boost::mpl::or_<LValue, IsProxy>, IsProxy>::type *
should_copy_impl(LValue *, IsProxy *, bool *)
{
    return 0;
}

// Otherwise, we must determine at runtime whether it's an lvalue or rvalue
inline bool *
should_copy_impl(boost::mpl::false_ *, boost::mpl::false_ *, bool *is_rvalue)
{
    return is_rvalue;
}

#endif

///////////////////////////////////////////////////////////////////////////////
// contain
//
template<typename T>
inline auto_any<T> contain(T const &t, boost::mpl::true_ *) // rvalue
{
    return auto_any<T>(t);
}

template<typename T>
inline auto_any<T *> contain(T &t, boost::mpl::false_ *) // lvalue
{
    // Cannot seem to get sunpro to handle addressof() with array types.
    #if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x570))
    return auto_any<T *>(&t);
    #else
    return auto_any<T *>(boost::addressof(t));
    #endif
}

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
template<typename T>
inline auto_any<simple_variant<T> >
contain(T const &t, bool *rvalue)
{
    return auto_any<simple_variant<T> >(*rvalue ? simple_variant<T>(t) : simple_variant<T>(&t));
}
#endif

/////////////////////////////////////////////////////////////////////////////
// begin
//
template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>
begin(auto_any_t col, type2type<T, C> *, boost::mpl::true_ *) // rvalue
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>(
        boost::begin(auto_any_cast<T, C>(col)));
}

template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>
begin(auto_any_t col, type2type<T, C> *, boost::mpl::false_ *) // lvalue
{
    typedef BOOST_DEDUCED_TYPENAME type2type<T, C>::type type;
    typedef BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type iterator;
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>(
        iterator(boost::begin(BOOST_FOREACH_DEREFOF((auto_any_cast<type *, boost::mpl::false_>(col))))));
}

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
template<typename T>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, const_>::type>
begin(auto_any_t col, type2type<T, const_> *, bool *)
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, const_>::type>(
        boost::begin(*auto_any_cast<simple_variant<T>, boost::mpl::false_>(col).get()));
}
#endif

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
template<typename T, typename C>
inline auto_any<T *>
begin(auto_any_t col, type2type<T *, C> *, boost::mpl::true_ *) // null-terminated C-style strings
{
    return auto_any<T *>(auto_any_cast<T *, boost::mpl::false_>(col));
}
#endif

///////////////////////////////////////////////////////////////////////////////
// end
//
template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>
end(auto_any_t col, type2type<T, C> *, boost::mpl::true_ *) // rvalue
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>(
        boost::end(auto_any_cast<T, C>(col)));
}

template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>
end(auto_any_t col, type2type<T, C> *, boost::mpl::false_ *) // lvalue
{
    typedef BOOST_DEDUCED_TYPENAME type2type<T, C>::type type;
    typedef BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type iterator;
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type>(
        iterator(boost::end(BOOST_FOREACH_DEREFOF((auto_any_cast<type *, boost::mpl::false_>(col))))));
}

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
template<typename T>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, const_>::type>
end(auto_any_t col, type2type<T, const_> *, bool *)
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_iterator<T, const_>::type>(
        boost::end(*auto_any_cast<simple_variant<T>, boost::mpl::false_>(col).get()));
}
#endif

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
template<typename T, typename C>
inline auto_any<int>
end(auto_any_t, type2type<T *, C> *, boost::mpl::true_ *) // null-terminated C-style strings
{
    return auto_any<int>(0); // not used
}
#endif

///////////////////////////////////////////////////////////////////////////////
// done
//
template<typename T, typename C>
inline bool done(auto_any_t cur, auto_any_t end, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type iter_t;
    return auto_any_cast<iter_t, boost::mpl::false_>(cur) == auto_any_cast<iter_t, boost::mpl::false_>(end);
}

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
template<typename T, typename C>
inline bool done(auto_any_t cur, auto_any_t, type2type<T *, C> *) // null-terminated C-style strings
{
    return ! *auto_any_cast<T *, boost::mpl::false_>(cur);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// next
//
template<typename T, typename C>
inline void next(auto_any_t cur, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type iter_t;
    ++auto_any_cast<iter_t, boost::mpl::false_>(cur);
}

///////////////////////////////////////////////////////////////////////////////
// deref
//
template<typename T, typename C>
inline BOOST_DEDUCED_TYPENAME foreach_reference<T, C>::type
deref(auto_any_t cur, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_iterator<T, C>::type iter_t;
    return *auto_any_cast<iter_t, boost::mpl::false_>(cur);
}

/////////////////////////////////////////////////////////////////////////////
// rbegin
//
template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>
rbegin(auto_any_t col, type2type<T, C> *, boost::mpl::true_ *) // rvalue
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>(
        boost::rbegin(auto_any_cast<T, C>(col)));
}

template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>
rbegin(auto_any_t col, type2type<T, C> *, boost::mpl::false_ *) // lvalue
{
    typedef BOOST_DEDUCED_TYPENAME type2type<T, C>::type type;
    typedef BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type iterator;
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>(
        iterator(boost::rbegin(BOOST_FOREACH_DEREFOF((auto_any_cast<type *, boost::mpl::false_>(col))))));
}

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
template<typename T>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, const_>::type>
rbegin(auto_any_t col, type2type<T, const_> *, bool *)
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, const_>::type>(
        boost::rbegin(*auto_any_cast<simple_variant<T>, boost::mpl::false_>(col).get()));
}
#endif

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
template<typename T, typename C>
inline auto_any<reverse_iterator<T *> >
rbegin(auto_any_t col, type2type<T *, C> *, boost::mpl::true_ *) // null-terminated C-style strings
{
    T *p = auto_any_cast<T *, boost::mpl::false_>(col);
    while(0 != *p)
        ++p;
    return auto_any<reverse_iterator<T *> >(reverse_iterator<T *>(p));
}
#endif

///////////////////////////////////////////////////////////////////////////////
// rend
//
template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>
rend(auto_any_t col, type2type<T, C> *, boost::mpl::true_ *) // rvalue
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>(
        boost::rend(auto_any_cast<T, C>(col)));
}

template<typename T, typename C>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>
rend(auto_any_t col, type2type<T, C> *, boost::mpl::false_ *) // lvalue
{
    typedef BOOST_DEDUCED_TYPENAME type2type<T, C>::type type;
    typedef BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type iterator;
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type>(
        iterator(boost::rend(BOOST_FOREACH_DEREFOF((auto_any_cast<type *, boost::mpl::false_>(col))))));
}

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
template<typename T>
inline auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, const_>::type>
rend(auto_any_t col, type2type<T, const_> *, bool *)
{
    return auto_any<BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, const_>::type>(
        boost::rend(*auto_any_cast<simple_variant<T>, boost::mpl::false_>(col).get()));
}
#endif

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
template<typename T, typename C>
inline auto_any<reverse_iterator<T *> >
rend(auto_any_t col, type2type<T *, C> *, boost::mpl::true_ *) // null-terminated C-style strings
{
    return auto_any<reverse_iterator<T *> >(
        reverse_iterator<T *>(auto_any_cast<T *, boost::mpl::false_>(col)));
}
#endif

///////////////////////////////////////////////////////////////////////////////
// rdone
//
template<typename T, typename C>
inline bool rdone(auto_any_t cur, auto_any_t end, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type iter_t;
    return auto_any_cast<iter_t, boost::mpl::false_>(cur) == auto_any_cast<iter_t, boost::mpl::false_>(end);
}

///////////////////////////////////////////////////////////////////////////////
// rnext
//
template<typename T, typename C>
inline void rnext(auto_any_t cur, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type iter_t;
    ++auto_any_cast<iter_t, boost::mpl::false_>(cur);
}

///////////////////////////////////////////////////////////////////////////////
// rderef
//
template<typename T, typename C>
inline BOOST_DEDUCED_TYPENAME foreach_reference<T, C>::type
rderef(auto_any_t cur, type2type<T, C> *)
{
    typedef BOOST_DEDUCED_TYPENAME foreach_reverse_iterator<T, C>::type iter_t;
    return *auto_any_cast<iter_t, boost::mpl::false_>(cur);
}

} // namespace foreach_detail_
} // namespace boost

// Suppress a bogus code analysis warning on vc8+
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# define BOOST_FOREACH_SUPPRESS_WARNINGS() __pragma(warning(suppress:6001))
#else
# define BOOST_FOREACH_SUPPRESS_WARNINGS()
#endif

///////////////////////////////////////////////////////////////////////////////
// Define a macro for giving hidden variables a unique name. Not strictly
// needed, but eliminates some warnings on some compilers.
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
// With some versions of MSVC, use of __LINE__ to create unique identifiers
// can fail when the Edit-and-Continue debug flag is used.
# define BOOST_FOREACH_ID(x) x
#else
# define BOOST_FOREACH_ID(x) BOOST_PP_CAT(x, __LINE__)
#endif

// A sneaky way to get the type of the collection without evaluating the expression
#define BOOST_FOREACH_TYPEOF(COL)                                                               \
    (true ? BOOST_FOREACH_NULL : boost::foreach_detail_::encode_type(COL, boost::foreach_detail_::is_const_(COL)))

// returns true_* if the type is noncopyable
#define BOOST_FOREACH_IS_NONCOPYABLE(COL)                                                       \
    boost_foreach_is_noncopyable(                                                               \
        boost::foreach_detail_::to_ptr(COL)                                                     \
      , boost_foreach_argument_dependent_lookup_hack_value)

// returns true_* if the type is a lightweight proxy (and is not noncopyable)
#define BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(COL)                                                 \
    boost::foreach_detail_::and_(                                                               \
        boost::foreach_detail_::not_(BOOST_FOREACH_IS_NONCOPYABLE(COL))                         \
      , boost_foreach_is_lightweight_proxy(                                                     \
            boost::foreach_detail_::to_ptr(COL)                                                 \
          , boost_foreach_argument_dependent_lookup_hack_value))

#if defined(BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION)
///////////////////////////////////////////////////////////////////////////////
// R-values and const R-values supported here with zero runtime overhead
///////////////////////////////////////////////////////////////////////////////

// No variable is needed to track the rvalue-ness of the collection expression
# define BOOST_FOREACH_PREAMBLE()                                                               \
    BOOST_FOREACH_SUPPRESS_WARNINGS()

// Evaluate the collection expression
# define BOOST_FOREACH_EVALUATE(COL)                                                            \
    (COL)

# define BOOST_FOREACH_SHOULD_COPY(COL)                                                         \
    (true ? BOOST_FOREACH_NULL : boost::foreach_detail_::or_(                                                    \
        BOOST_FOREACH_IS_RVALUE(COL)                                                            \
      , BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(COL)))

#elif defined(BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION)
///////////////////////////////////////////////////////////////////////////////
// R-values and const R-values supported here
///////////////////////////////////////////////////////////////////////////////

// Declare a variable to track the rvalue-ness of the collection expression
# define BOOST_FOREACH_PREAMBLE()                                                               \
    BOOST_FOREACH_SUPPRESS_WARNINGS()                                                           \
    if (bool BOOST_FOREACH_ID(_foreach_is_rvalue) = false) {} else

// Evaluate the collection expression, and detect if it is an lvalue or and rvalue
# define BOOST_FOREACH_EVALUATE(COL)                                                            \
    (true ? boost::foreach_detail_::make_probe((COL), BOOST_FOREACH_ID(_foreach_is_rvalue)) : (COL))

// The rvalue/lvalue-ness of the collection expression is determined dynamically, unless
// the type is an array or is noncopyable or is non-const, in which case we know it's an lvalue.
// If the type happens to be a lightweight proxy, always make a copy.
# define BOOST_FOREACH_SHOULD_COPY(COL)                                                         \
    (boost::foreach_detail_::should_copy_impl(                                                  \
        true ? BOOST_FOREACH_NULL : boost::foreach_detail_::or_(                                                 \
            boost::foreach_detail_::is_array_(COL)                                              \
          , BOOST_FOREACH_IS_NONCOPYABLE(COL)                                                   \
          , boost::foreach_detail_::not_(boost::foreach_detail_::is_const_(COL)))               \
      , true ? BOOST_FOREACH_NULL : BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(COL)                                      \
      , &BOOST_FOREACH_ID(_foreach_is_rvalue)))

#elif !defined(BOOST_FOREACH_NO_RVALUE_DETECTION)
///////////////////////////////////////////////////////////////////////////////
// R-values supported here, const R-values NOT supported here
///////////////////////////////////////////////////////////////////////////////

// No variable is needed to track the rvalue-ness of the collection expression
# define BOOST_FOREACH_PREAMBLE()                                                               \
    BOOST_FOREACH_SUPPRESS_WARNINGS()

// Evaluate the collection expression
# define BOOST_FOREACH_EVALUATE(COL)                                                            \
    (COL)

// Determine whether the collection expression is an lvalue or an rvalue.
// NOTE: this gets the answer wrong for const rvalues.
# define BOOST_FOREACH_SHOULD_COPY(COL)                                                         \
    (true ? BOOST_FOREACH_NULL : boost::foreach_detail_::or_(                                                    \
        boost::foreach_detail_::is_rvalue_((COL), 0)                                            \
      , BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(COL)))

#else
///////////////////////////////////////////////////////////////////////////////
// R-values NOT supported here
///////////////////////////////////////////////////////////////////////////////

// No variable is needed to track the rvalue-ness of the collection expression
# define BOOST_FOREACH_PREAMBLE()                                                               \
    BOOST_FOREACH_SUPPRESS_WARNINGS()

// Evaluate the collection expression
# define BOOST_FOREACH_EVALUATE(COL)                                                            \
    (COL)

// Can't use rvalues with BOOST_FOREACH (unless they are lightweight proxies)
# define BOOST_FOREACH_SHOULD_COPY(COL)                                                         \
    (true ? BOOST_FOREACH_NULL : BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(COL))

#endif

#define BOOST_FOREACH_CONTAIN(COL)                                                              \
    boost::foreach_detail_::contain(                                                            \
        BOOST_FOREACH_EVALUATE(COL)                                                             \
      , BOOST_FOREACH_SHOULD_COPY(COL))

#define BOOST_FOREACH_BEGIN(COL)                                                                \
    boost::foreach_detail_::begin(                                                              \
        BOOST_FOREACH_ID(_foreach_col)                                                          \
      , BOOST_FOREACH_TYPEOF(COL)                                                               \
      , BOOST_FOREACH_SHOULD_COPY(COL))

#define BOOST_FOREACH_END(COL)                                                                  \
    boost::foreach_detail_::end(                                                                \
        BOOST_FOREACH_ID(_foreach_col)                                                          \
      , BOOST_FOREACH_TYPEOF(COL)                                                               \
      , BOOST_FOREACH_SHOULD_COPY(COL))

#define BOOST_FOREACH_DONE(COL)                                                                 \
    boost::foreach_detail_::done(                                                               \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_ID(_foreach_end)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

#define BOOST_FOREACH_NEXT(COL)                                                                 \
    boost::foreach_detail_::next(                                                               \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

#define BOOST_FOREACH_DEREF(COL)                                                                \
    boost::foreach_detail_::deref(                                                              \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

#define BOOST_FOREACH_RBEGIN(COL)                                                               \
    boost::foreach_detail_::rbegin(                                                             \
        BOOST_FOREACH_ID(_foreach_col)                                                          \
      , BOOST_FOREACH_TYPEOF(COL)                                                               \
      , BOOST_FOREACH_SHOULD_COPY(COL))

#define BOOST_FOREACH_REND(COL)                                                                 \
    boost::foreach_detail_::rend(                                                               \
        BOOST_FOREACH_ID(_foreach_col)                                                          \
      , BOOST_FOREACH_TYPEOF(COL)                                                               \
      , BOOST_FOREACH_SHOULD_COPY(COL))

#define BOOST_FOREACH_RDONE(COL)                                                                \
    boost::foreach_detail_::rdone(                                                              \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_ID(_foreach_end)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

#define BOOST_FOREACH_RNEXT(COL)                                                                \
    boost::foreach_detail_::rnext(                                                              \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

#define BOOST_FOREACH_RDEREF(COL)                                                               \
    boost::foreach_detail_::rderef(                                                             \
        BOOST_FOREACH_ID(_foreach_cur)                                                          \
      , BOOST_FOREACH_TYPEOF(COL))

///////////////////////////////////////////////////////////////////////////////
// BOOST_FOREACH
//
//   For iterating over collections. Collections can be
//   arrays, null-terminated strings, or STL containers.
//   The loop variable can be a value or reference. For
//   example:
//
//   std::list<int> int_list(/*stuff*/);
//   BOOST_FOREACH(int &i, int_list)
//   {
//       /* 
//        * loop body goes here.
//        * i is a reference to the int in int_list.
//        */
//   }
//
//   Alternately, you can declare the loop variable first,
//   so you can access it after the loop finishes. Obviously,
//   if you do it this way, then the loop variable cannot be
//   a reference.
//
//   int i;
//   BOOST_FOREACH(i, int_list)
//       { ... }
//
#define BOOST_FOREACH(VAR, COL)                                                                                   \
    BOOST_FOREACH_PREAMBLE()                                                                                      \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_col) = BOOST_FOREACH_CONTAIN(COL)) {} else   \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_cur) = BOOST_FOREACH_BEGIN(COL)) {} else     \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_end) = BOOST_FOREACH_END(COL)) {} else       \
    for (bool BOOST_FOREACH_ID(_foreach_continue) = true;                                                         \
              BOOST_FOREACH_ID(_foreach_continue) && !BOOST_FOREACH_DONE(COL);                                    \
              BOOST_FOREACH_ID(_foreach_continue) ? BOOST_FOREACH_NEXT(COL) : (void)0)                            \
        if  (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_continue))) {} else                      \
        for (VAR = BOOST_FOREACH_DEREF(COL); !BOOST_FOREACH_ID(_foreach_continue); BOOST_FOREACH_ID(_foreach_continue) = true)

///////////////////////////////////////////////////////////////////////////////
// BOOST_REVERSE_FOREACH
//
//   For iterating over collections in reverse order. In
//   all other respects, BOOST_REVERSE_FOREACH is like
//   BOOST_FOREACH.
//
#define BOOST_REVERSE_FOREACH(VAR, COL)                                                                           \
    BOOST_FOREACH_PREAMBLE()                                                                                      \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_col) = BOOST_FOREACH_CONTAIN(COL)) {} else   \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_cur) = BOOST_FOREACH_RBEGIN(COL)) {} else    \
    if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_end) = BOOST_FOREACH_REND(COL)) {} else      \
    for (bool BOOST_FOREACH_ID(_foreach_continue) = true;                                                         \
              BOOST_FOREACH_ID(_foreach_continue) && !BOOST_FOREACH_RDONE(COL);                                   \
              BOOST_FOREACH_ID(_foreach_continue) ? BOOST_FOREACH_RNEXT(COL) : (void)0)                           \
        if  (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_continue))) {} else                      \
        for (VAR = BOOST_FOREACH_RDEREF(COL); !BOOST_FOREACH_ID(_foreach_continue); BOOST_FOREACH_ID(_foreach_continue) = true)

#endif

/* foreach.hpp
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
*/