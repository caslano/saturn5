//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/utility for most recent version including documentation.
//  see libs/utility/compressed_pair.hpp
//
/* Release notes:
   20 Jan 2001:
        Fixed obvious bugs (David Abrahams)
   07 Oct 2000:
      Added better single argument constructor support.
   03 Oct 2000:
      Added VC6 support (JM).
   23rd July 2000:
      Additional comments added. (JM)
   Jan 2000:
      Original version: this version crippled for use with crippled compilers
      - John Maddock Jan 2000.
*/


#ifndef BOOST_OB_COMPRESSED_PAIR_HPP
#define BOOST_OB_COMPRESSED_PAIR_HPP

#include <algorithm>
#ifndef BOOST_OBJECT_TYPE_TRAITS_HPP
#include <boost/type_traits/object_traits.hpp>
#endif
#ifndef BOOST_SAME_TRAITS_HPP
#include <boost/type_traits/same_traits.hpp>
#endif
#ifndef BOOST_CALL_TRAITS_HPP
#include <boost/call_traits.hpp>
#endif

namespace boost
{
#ifdef BOOST_MSVC6_MEMBER_TEMPLATES
//
// use member templates to emulate
// partial specialisation.  Note that due to
// problems with overload resolution with VC6
// each of the compressed_pair versions that follow
// have one template single-argument constructor
// in place of two specific constructors:
//

template <class T1, class T2>
class compressed_pair;

namespace detail{

template <class A, class T1, class T2>
struct best_conversion_traits
{
   typedef char one;
   typedef char (&two)[2];
   static A a;
   static one test(T1);
   static two test(T2);

   enum { value = sizeof(test(a)) };
};

template <int>
struct init_one;

template <>
struct init_one<1>
{
   template <class A, class T1, class T2>
   static void init(const A& a, T1* p1, T2*)
   {
      *p1 = a;
   }
};

template <>
struct init_one<2>
{
   template <class A, class T1, class T2>
   static void init(const A& a, T1*, T2* p2)
   {
      *p2 = a;
   }
};


// T1 != T2, both non-empty
template <class T1, class T2>
class compressed_pair_0
{
private:
   T1 _first;
   T2 _second;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_0() : _first(), _second() {}
            compressed_pair_0(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   template <class A>
   explicit compressed_pair_0(const A& val)
   {
      init_one<best_conversion_traits<A, T1, T2>::value>::init(val, &_first, &_second);
   }
   compressed_pair_0(const ::boost::compressed_pair<T1,T2>& x)
      : _first(x.first()), _second(x.second()) {}

#if 0
  compressed_pair_0& operator=(const compressed_pair_0& x) {
    cout << "assigning compressed pair 0" << endl;
    _first = x._first;
    _second = x._second;
    cout << "finished assigning compressed pair 0" << endl;
    return *this;
  }
#endif

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_0& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

// T1 != T2, T2 empty
template <class T1, class T2>
class compressed_pair_1 : T2
{
private:
   T1 _first;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_1() : T2(), _first() {}
            compressed_pair_1(first_param_type x, second_param_type y) : T2(y), _first(x) {}

   template <class A>
   explicit compressed_pair_1(const A& val)
   {
      init_one<best_conversion_traits<A, T1, T2>::value>::init(val, &_first, static_cast<T2*>(this));
   }

   compressed_pair_1(const ::boost::compressed_pair<T1,T2>& x)
      : T2(x.second()), _first(x.first()) {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return *this; }
   second_const_reference second() const { return *this; }

   void swap(compressed_pair_1& y)
   {
      // no need to swap empty base class:
      using std::swap;
      swap(_first, y._first);
   }
};

// T1 != T2, T1 empty
template <class T1, class T2>
class compressed_pair_2 : T1
{
private:
   T2 _second;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_2() : T1(), _second() {}
            compressed_pair_2(first_param_type x, second_param_type y) : T1(x), _second(y) {}
   template <class A>
   explicit compressed_pair_2(const A& val)
   {
      init_one<best_conversion_traits<A, T1, T2>::value>::init(val, static_cast<T1*>(this), &_second);
   }
   compressed_pair_2(const ::boost::compressed_pair<T1,T2>& x)
      : T1(x.first()), _second(x.second()) {}

#if 0
  compressed_pair_2& operator=(const compressed_pair_2& x) {
    cout << "assigning compressed pair 2" << endl;
    T1::operator=(x);
    _second = x._second;
    cout << "finished assigning compressed pair 2" << endl;
    return *this;
  }
#endif
   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_2& y)
   {
      // no need to swap empty base class:
      using std::swap;
      swap(_second, y._second);
   }
};

// T1 != T2, both empty
template <class T1, class T2>
class compressed_pair_3 : T1, T2
{
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_3() : T1(), T2() {}
            compressed_pair_3(first_param_type x, second_param_type y) : T1(x), T2(y) {}
   template <class A>
   explicit compressed_pair_3(const A& val)
   {
      init_one<best_conversion_traits<A, T1, T2>::value>::init(val, static_cast<T1*>(this), static_cast<T2*>(this));
   }
   compressed_pair_3(const ::boost::compressed_pair<T1,T2>& x)
      : T1(x.first()), T2(x.second()) {}

   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return *this; }
   second_const_reference second() const { return *this; }

   void swap(compressed_pair_3& y)
   {
      // no need to swap empty base classes:
   }
};

// T1 == T2, and empty
template <class T1, class T2>
class compressed_pair_4 : T1
{
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_4() : T1() {}
            compressed_pair_4(first_param_type x, second_param_type y) : T1(x), m_second(y) {}
   // only one single argument constructor since T1 == T2
   explicit compressed_pair_4(first_param_type x) : T1(x), m_second(x) {}
   compressed_pair_4(const ::boost::compressed_pair<T1,T2>& x)
      : T1(x.first()), m_second(x.second()) {}

   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return m_second; }
   second_const_reference second() const { return m_second; }

   void swap(compressed_pair_4& y)
   {
      // no need to swap empty base classes:
   }
private:
   T2 m_second;
};

// T1 == T2, not empty
template <class T1, class T2>
class compressed_pair_5
{
private:
   T1 _first;
   T2 _second;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_5() : _first(), _second() {}
            compressed_pair_5(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   // only one single argument constructor since T1 == T2
   explicit compressed_pair_5(first_param_type x) : _first(x), _second(x) {}
   compressed_pair_5(const ::boost::compressed_pair<T1,T2>& c) 
      : _first(c.first()), _second(c.second()) {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_5& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

template <bool e1, bool e2, bool same>
struct compressed_pair_chooser
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_0<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<false, true, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_1<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, false, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_2<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, true, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_3<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, true, true>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_4<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<false, false, true>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_5<T1, T2> type;
   };
};

template <class T1, class T2>
struct compressed_pair_traits
{
private:
   typedef compressed_pair_chooser<is_empty<T1>::value, is_empty<T2>::value, is_same<T1,T2>::value> chooser;
   typedef typename chooser::template rebind<T1, T2> bound_type;
public:
   typedef typename bound_type::type type;
};

} // namespace detail

template <class T1, class T2>
class compressed_pair : public detail::compressed_pair_traits<T1, T2>::type
{
private:
   typedef typename detail::compressed_pair_traits<T1, T2>::type base_type;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : base_type() {}
            compressed_pair(first_param_type x, second_param_type y) : base_type(x, y) {}
   template <class A>
   explicit compressed_pair(const A& x) : base_type(x){}

   first_reference       first()       { return base_type::first(); }
   first_const_reference first() const { return base_type::first(); }

   second_reference       second()       { return base_type::second(); }
   second_const_reference second() const { return base_type::second(); }
};

template <class T1, class T2>
inline void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}

#else
// no partial specialisation, no member templates:

template <class T1, class T2>
class compressed_pair
{
private:
   T1 _first;
   T2 _second;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : _first(), _second() {}
            compressed_pair(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   explicit compressed_pair(first_param_type x) : _first(x), _second() {}
   // can't define this in case T1 == T2:
   // explicit compressed_pair(second_param_type y) : _first(), _second(y) {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

template <class T1, class T2>
inline void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}

#endif

} // boost

#endif // BOOST_OB_COMPRESSED_PAIR_HPP




/* ob_compressed_pair.hpp
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
*/