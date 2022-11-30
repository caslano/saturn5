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

#ifndef BOOST_UTILITY_DOCS
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
#endif // BOOST_UTILITY_DOCS

/* ob_compressed_pair.hpp
bRCagAVQmoqEG239tAb2U80YE7AwTN33xHaPYAlOnULpqqE7us3v9hunCvQxqZFuY7JcSZ9dlnLqu3otwTTWR3ukGpmPj6K631zpaJaB7R8iECjaZO96gTdvHGTT9Hg84cu2xgrRJRVh0131JVpSV9XXSe9BKU27cZIDRIaWdDdgKH8bTZsTIg3OjE1tMdX5zCXntWqpbSgsGxRpR63Wz5aMgEWyZbHwjGSWzURYlhZjKz/X4yfCGxB+IQ/LbFacR/PdGJrKJXJR1S1ukrpalxvBokX7WWkDIWtBY26y2WqArv+FUTbDahlkzDDsqvE1efb4dE41X/1/hVz5vv+7KABLXCjjYmSaCSCWfnSjfx8hWoCtYKSRZ8r23SGFTpnr185hbci9tTzpfJHg9GrvqsvjV38BDgvu4aUCibpDeMb2iKi57TDKchUA9uPnP1/f/UesYXX1RCNGT4OrSNMLXxMX+Ski0aSee27s+Qs4qD526ctgEgrOUurCFXsINrEFZIVAp0yBSIHYn3dzWtmMdfBy12ngozzHjdPWhYb8KhxVcPcSlTPvpwbdTCusf/UdNIDLNgwDp1cfcaNO2NVFq8CiCjfv+joVLeJI3JZj824wPF9V9ZH+SoiF/kfonhxJ27J3LbKyOkfwiNDwUUieJHAYHoe4T5UFBmIy3tKiCYj9/zCcAa4HvLhxENAVBxqWP+BU0KCvEg2VWH06R13z6PvHMyCPTKE6gG5HeqyxatrJoULHDLPzWRXlDyoJgHg88Wq+iWSSxmLF+PUegN0UTWaZ4hvz3mWW4cIsKoCobxFiXlwK/6dcxFdojcdXNEuGjHJ/pD0RRFPRROzg6/EARt4APatz+y9zOFP8YPWkkkHeaoaWrm5ueU7uLc+fJanl//BOdAsAjRbw24/ZTTiQCKwu8y5nO6GbQXUPG4iEXhlfl4/1xNqH8sQNgfjOIC55ekBPq44B9+hdDFg93QPxNXDUIjbI7dpVOlNdiGeo+tfbt8yc6uUIJzmjHyaAdmQXdgn88+CWo9/ebano+h8/PNYuG8bLZugW+FvRImdLMVT6E7Yv1bxYpbuf04MIeqGYU7rUVplvcZodDp/9L6jyDqDO5S5gicEZtVITKMCiLDBsOkoaOk9K89gapKZqk/WroV0UXO8oez0tejzsUsFlNqRg6fzmYcDbcmcgK/4sDGsjwIwrkmf7/+qGXL5461yAEI8zEA8r8wDhLVKrT6gURF+Gx2caaF2pH94QGteUmuL/5V/LwbIei2+zECC4ajUcHaGumj0LlahjW/QNQU4tHHlgmhKJd1lQmXRcJ3JLxT7bJE0qGVocmRTS2+wGMWXr9oXaD88mLFH4GJeOxlAWrhMahO9mgjDC8nYq26Ni/pAVMLyWNRoGWalhpHJAdRKvdr6gnMPP9IV9Rw08UVgk2kWu61vneOYNxWiXcmkJ2/M2u2n/0cFpeOtpMN8xyeW3O6cY0OwRIjPHnRpoxd6rCMbLvQxKwjF58+zjr96jpYDwvB9Sw3WjVr35atdX3Y3OV1dkkay78wm/KNuUT683Xo688afcXgcmTwBwZo0XdXsVISZsQtJWaaDTbIeSbObpnWBPW/jb7V6ifvmmCqhTjEYULmin+576o1vG4/Ndb6E9zKemBLtCe2+MxacMIzCHKsdLD4nDlA8km6viPMN9CLnHn/1CL1I2HjOaoHANZys63HyqadJOxRwevkOmjgROuTWQRG/VdXLzuBr4qPBHJExE38fqti/TmxiIqTrpLSGQjXIawlOgs0yJt5l34AyxmasJd74MIJx0/luoK2DvyU2h6h7em08GivLxlBGO/7B7+e/WY/dXOtgwxqVp7jgZ4orJe7/n+b38sCL7s325g7dgoTN9AURSkcPhPH3o245B7frCya/8ELnAkT3zPjLS08e5DyM5JFsI29ZV22mDiwXUXF6Xs5q//EyYrt0JZ2oKyRp943JM52Wo6BX+yVk47yZoCCHXyYLTeolc0LNL8VTJeWa2u6kkYlRu3YMRGUNNP1eCIJdKY4omfq7QwdnhDXLDaqfOm8Vs9rRWzcLOvL/BJ/nBMH9kt3oz3Xe57ORdPOYv2DkcKcW4GuAyo3B6yINKWKDC2VbkRusQ5Ik5iE6boahK279UH/3m5Wmeep1PwGP94teQ7TggC4cB7ois7HiO6kBzgUAhqCpz1NdOdxnYYSMvgmBDm8Cs7W5XOFjBDV67c5vfhCMCSg+ApaRTLnQZzi7AOozFgyTJHvXz6yxRqBDXAmurJ44tJjTCDLJRzNFXQnYvrrbO6/r5B/usb3Dtkts1cmS7ngVhim6tnRgIw34k0Zs6x75Pgp9XCJSi+ook9ZkxVqz+jI+GtC3BeN21gNvmayIu0LO6ZEioQ1WTwSquh6zfhXx+6VpsHIS7hBmn5i+GfWo6Pt2NTzQvyGgM9gHmtZHzFryBYBZxtPERwyyw4PbrwoCNGTn5I1qoiBd5tNNvJodFS5Mr6g4qK9NyoV2R6yiLWYp/WcprP9rjhjEMnaz98etKhmaREzZVOZI4uYh1BRRrFwHoLAc0XjWDziRiNQ1e4pWyd3UbHKj/3+CUyTj7psj4w244WTovVNC8yB8lTRDNLfX41zG4RjfIi10KsGJOsWkPnHkG8wnL5v8P/x2bSVgUq9GE3WNC/7VE+7EB9eeTBAbrK3s9Ar7witomFxjYxGiB9pS8XLO6eEEIiHo9I2wcVxwww5TfS8ShtjmWfMYg/YAC7+794WoKU8I/4QT1MK37PTi32xiALm+/uTQoqjc2I0FalH62NHf9+YfSSU/0KLKad5lnvPXCdvkgKuMCDgnY70+l4hVdBGZ2OZ72upx5KVuexst3Xol5N4tBILXZPbXiYQXxE8DHnZQktJdfPyUIksYia83nr/vE1o74KholwET26Juoz+0XJlYVOEx55pw3g+TW1ILn1tzOj7hbo1BDhQxwWRZpn2IhOQaAKKF21qslNCzP7+yj41aJ4/Br7BDhO0GCNKQtb/ckLK/ZXNVcQxsn8C2ar0I/Mvi8OlLFtcZVjY3mccKWtFDELK7U6mnbCTY4EMKUG6X+xL1rENsA5d/Y5KPjRTIcVnY4307IFOVukXuURHdn2e9P0rDGtkaWOPro9QRhKTdyl2nQKXpntVksUyDjTB4hH116sHSX0SSTPeIN8Ot69RwLya4OWzuHUI04fJ3nxoIZNpNKY/K5NWOo+U4WBSapX3oZ1Cw8NQdcAw75oS6zCY5VaVuc87lrFFMTOjQw1DLzoB2etosPSRT+zGUcZhqfZBk95hroagl+SXcHjkNtLggWrlYC8SAeTj0ULdXC91wm9+PRHJFAG8ZOSHt25q3W494LHIBiJNgRH3kVf/gwukYjvqr6zvhKuVAB+X3DnduaWIA5O2yog3fxpbYmrsQcw3TA/7zSQLaDJe5Y/Mn4td5Fs64gn32hxGICyGJv+J6ucHvASx8hhJ8My8klaH405rmo54t4JPWwHt6yUVSk2Cihi3sAwr+21TsTmwTwQQQvPhsjeZxRQ0P+EQsjXr84LhApQp5RcH5X2TsSZ6YHPHPdX2P5HmfGSdvU/Fyl58lJFE1jMH5zZcA790+y8utV8h50ydclWyxbNKBi7YdQe9xIelCJWIW5VIzajvo7vpAAwidIXAvdAx9aPPyI41czYQX7rqlGtF5VZrSB8WKEURivPPqKiMu5a0MBc73sMb7ezEPEILrgZ38WwqUK/Fe0PKT//FuxwdveeGhHZeEZB0YJwSfg1izRLljlc1DEAH2PN8BhKeja3gvC3CbhWv495QYDu/8evzqxPgywZbrT6hkeO4oGLUvZUAupbMgesF1W6zJFJVEuSBttB/fKFhvg+8bdMqGUqGInH4e/sKYCvSXp33J0zrLdyqzCxqvFdWIacMeTZC1KLuJJD/ALhl+8Gp5iJFae4cBc/i2wuxpuVG6RblXTrJtRz2/0B/BZzPcJv3/hIxD+uB8CzbHHGw2W9UzrP63Mjxg7svgQHZRXo7GpJpVoLWDoCbG07jp4r7FGpb+KrijIaPeE8YaDa2dzBmULVito3TDx5v1T34TIeZ6DiC3x5DZM9oc2zMZsf6DVrPJhmXwuKdI5lPyDxURMcpSfEIYZHOoXyZr7SNQ5FN3cDBmwpOIO3n3iqM53Xv5AOqOOrE9WmjcFF4ubtf4IMKsB2Pk1ttlI5/5mV1maWjnb6lEPxQBNZpYF8RH6Z8CSK/FWODSvbUxPxdwz8fnJgHBUrjrKeIlw8x3ewtwGyaHFGJlwU/WCJgyxfy2W0ocz09oiEfnXxwy+hwsWNwBTt87HDkosyeDDlt+BVs3XWikCGtQ+HbCuiqJd/82cj18JuQKFp58hLCWAndpVK9xf4dDbRmpLgeVg9pi38xNfsBqE1JeaPZ39tD7QaDDJ8qInHLawx8HXk6Q3tK0m/0/bCF2LaK4Sg49Kk2zBIMvQNeMhy5YFhUA2kQ0kzbOx2ThZoOzMI955rH0dCbvB0gzBPr+PZFoGw5L+oV5ISCgtSMQXXBUhCGprXV0OohUCd2SVkU7EI9biQmPYw3gKXKoLmpiS0HjqbnhD1IgdnaXJ8OQjezyyzwe6LnNUZ0Hv52TeiUYV3lWWqPV57nW3oni0eHdAWVRYqqcK7z544h4xLwSraemI06Q1tUjs1j8K+h73RhdoQ+o1i5RoKfiCsz6UB3PLEbFowhEVeGX962cwTNG/+f0GhZjnyuiS3NR8EfRIzaP9A/+XVAUy2IrJrijC0OYV2Qw5E2F+um5N5pNQUx9grIuFHiCEOog1SeI33tqQgidF8626DC18maXxE4XBHrn7CbqtfeqojyAa2H/hiEoqqUmjuoUTAkhMW8tF3WaM1VVV/zzbFYipTxz9srKUenfuFb4cJJ0E0fpaLFS4WlaFucUDBrb8YLpYBOW2L+EFA8BkZ7rWaLP4+Jc4pw0FRwzpJMQonutuSuMkkpfVq67Hh6x9U6/r2brI8231DvfkivVQO2IFfQUWZmnewHrSvnhpqhlNV63qqHhj9RjzKVHgJ89AGR+idF7Pd9asMavpGw9YThbVk9puT/Pa7+suokDLfo1lqcr3r+R7oPGgOh8JcNGE4czRsc2kYGI7s/tbxLZ9z3DvXj2OU95OPUzNW3NmS+xO2ZAK4TIoGm8TO0+rw1blmPoJuyCOD06CD+iEQADADe63M+TK2vnz/fZSuOnvXYq6KzV6bHDXaA6Z+buQGRhCYhPQ2JF7o6gXJ4di+NxxzIXSuzSjB8cCmXt9aMoCpUQngvzWhzhybXMTgwTFvBUgkxfubKYrWRQ3B4bDKMCJ+iedxHo4V5FvbVxGGmLjgQlhhXt9s00pBv51/hlZL3om5loSA5cvsoZ1adEKxHkHMBzCTqDNMXdAZskgE/WQ1qUnlbmxf7Uj9bOrvKiiqB9JVWtAe8urIe4XInZB8wG7ZcQddTXY89EeqP0X/Gc1k9blZMwgOyFjZWYMzPlq87rZjXEonK4ACTqnlfwjg2OHc6dSQrP60A9DJc4smJTxg7tzGs0fQVYZdxBN+0r+IgBETwQ1ztZFWfMb4Wklg1npMKmhmMNBLMlj79Hg2wO/gqfUX8mSAR17B1x9FG2MCI7Al8FM4dNFDxJ31+5R3M+O6oXOBsPt1u7HC3RBS8IA6wrhLGgr25xZRMN6m27lgfF6P7102dGSyLYuzAPm2UdFYUTLOGFyGoi5lr3w/FbuOImh/Xf41Oq7ik1JMldLNvtzOvYoT0aP8lunPsUsmuyJBeXa1MtLkVY+A+8mOE913KY9RKfUoIU1ZvpmhjFIHPmstNbOQPK400KkrI51grsj3JY48MubEj9IrPDBM0bxhdbn505I5hqC7UznrTVvqDpBkGak2O6UlgbrECWcPjfP8oul6IcWCVDYGRszOivTUH8LpbZTpf5TwehmEbTPJ8WVhAGPn/vWqgE25stT6I8bOCu1xX27voZJOH4ccdmF9Wx7PywaMpa+pqg4flYRye5HeaIyl4X96O3FbBNyF4fNIt9rQ2sX4ogtwdFaKDVAcP0qZedGsKTD1zUO23pOgQntmQntK+bLYGT1RNljIvocZe1KWbAqIvqCF56Z/RfvNyywoQvpEg9p5VuozdJZKvVeBhP/UOho/BH6JRv0sYo+N16cz/PsR8p6CSAdlZSQom6X2Ht2dnXHXtWBfMghx3X/MbRUQBEJb0MR83eVCFtWoemAY8oXwcaVK1Fr4lCz1rZlx0j41VdugJgfWMaQGNKsMQaTvuVTm5r/O4JzOfTAjbc0pUXrD8aUI2tdSLw6ArFMKvqURmB0J9t5KTvG4UdXJYdIm/XUoY5AXQ54HRjRggBLmJCp0A0ePagb5Mlsynoq+gnLJEI92DL8P8/8oR6lhUimF45gXf/XV7GypnVZ97y9DQmOinzuv1qOmabKk39U6mZDZvaCtOaqz8/JDmoESIM+YZZKqxhj7RD4eX/tHpOc7doJztIEnSClt3Iy6eUnBT1CaZqiaYVB8/TEEvhcZjhUw9XnLVCu2rEmMK0/26TkZpry25Rzra9xNAM96bzZA0w5bKxyLRupGud0DJKDWrHjr0ybxeLDTVVJNVO8fMFli2WYbGNSjEpHlSZtGfL9eF292xFnwgisFj6qHJIUWWEjK6IVWtA8Giw+wV5FHhq6sNyCPr/exfyVj3SVoVvX0xEjSuaUzTto2ARHQDNoZJZlP1w5aVoUFQG6AROZmFw9ixO09hXm84/zQ2T89uypEoVyLw/Q7r+LLlMpnA6lDOj8xrxhaQ3ATfeIIOcqzkbDZR6/CChEwhLM4AYK5ASEYi6diPvQSnvDHcE+lEqS2VWC9CLmQYb6k/Dugp+ffgAe7lbg3OfaPMzKilPUez1G9yHZIwcjJPmKQRgKJnqlt376IeYkGoaS61gmxaPzqSPY4bfpeX/PX8Tfq6sgUjC9+nqyz0lA6ZT/6AIq4zyCpibt3qWAbHBO3T0XTom4bOzuv5JWEfYTD8S2mR3E6aC8tvh3hiOf6J8tD1Xlq/OnYjrQ6Tm8j4qL9nApKpIjacJDQY5UW6pCQvO75fjzh1EABID2/GdA2+pgH5YkA7qTdp19p20TePFrSpZg7CNNrz5tozjvNaURxeAsb1YVVAIUNRizmZZbqVNUKkkq28+tYCqNpHDP2G0zb1wTeLasKs4Z1Gvk4pRnctUmWR3Pz8iwRxGPB4inW7KZYxCHO1673KbVmBq0As+PmXBiQmdCUg+vUUM2XV/POT7L4hdvHDcXgS4U5fW/RbBtzQJf193oD+mn4x5Z21x+CZWL8YexT6F/MVXMKVyPvojXc2W1/1Y9qj/Sc2IKz+ymMFysauEeHFuwHpcnozVaWPmGwbDJGDnqliWHkVDhXpxtJ6wiSexM3hULWvqWXas6MA247QDbCJGPnCe+xZppcpdcS+uHBkbXbUib/5EmCSNG9L/AshrhlFvw8+mbsiS/a1c8gylxHa+3+uH4vyqsnGDmjLBJHxQ7NYEy9lnwZiDs/tYSpvZc5HH+fUQVvXR0PXgKWfbQzvDa2SY2tQ+G2x+ORQEe4Nq1Z+Bqw5K+BqQR3aDPB59KJp1Z95fcxodBGyp1Le+e7uqUxaV/
*/