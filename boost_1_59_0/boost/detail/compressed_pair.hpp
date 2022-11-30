//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/utility for most recent version including documentation.

// compressed_pair: pair that "compresses" empty members
// (see libs/utility/doc/html/compressed_pair.html)
//
// JM changes 25 Jan 2004:
// For the case where T1 == T2 and both are empty, then first() and second()
// should return different objects.
// JM changes 25 Jan 2000:
// Removed default arguments from compressed_pair_switch to get
// C++ Builder 4 to accept them
// rewriten swap to get gcc and C++ builder to compile.
// added partial specialisations for case T1 == T2 to avoid duplicate constructor defs.

#ifndef BOOST_DETAIL_COMPRESSED_PAIR_HPP
#define BOOST_DETAIL_COMPRESSED_PAIR_HPP

#include <algorithm>

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_final.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/call_traits.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4512)
#endif 
namespace boost
{

template <class T1, class T2>
class compressed_pair;


// compressed_pair

namespace details
{
   template<class T, bool E = boost::is_final<T>::value>
   struct compressed_pair_empty
      : ::boost::false_type { };

   template<class T>
   struct compressed_pair_empty<T, false>
      : ::boost::is_empty<T> { };

   // JM altered 26 Jan 2000:
   template <class T1, class T2, bool IsSame, bool FirstEmpty, bool SecondEmpty>
   struct compressed_pair_switch;

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, false, false, false>
      {static const int value = 0;};

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, false, true, true>
      {static const int value = 3;};

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, false, true, false>
      {static const int value = 1;};

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, false, false, true>
      {static const int value = 2;};

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, true, true, true>
      {static const int value = 4;};

   template <class T1, class T2>
   struct compressed_pair_switch<T1, T2, true, false, false>
      {static const int value = 5;};

   template <class T1, class T2, int Version> class compressed_pair_imp;

#ifdef __GNUC__
   // workaround for GCC (JM):
   using std::swap;
#endif
   //
   // can't call unqualified swap from within classname::swap
   // as Koenig lookup rules will find only the classname::swap
   // member function not the global declaration, so use cp_swap
   // as a forwarding function (JM):
   template <typename T>
   inline void cp_swap(T& t1, T& t2)
   {
#ifndef __GNUC__
      using std::swap;
#endif
      swap(t1, t2);
   }

   // 0    derive from neither

   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 0>
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

      compressed_pair_imp() {} 

      compressed_pair_imp(first_param_type x, second_param_type y)
         : first_(x), second_(y) {}

      compressed_pair_imp(first_param_type x)
         : first_(x) {}

      compressed_pair_imp(second_param_type y)
         : second_(y) {}

      first_reference       first()       {return first_;}
      first_const_reference first() const {return first_;}

      second_reference       second()       {return second_;}
      second_const_reference second() const {return second_;}

      void swap(::boost::compressed_pair<T1, T2>& y)
      {
         cp_swap(first_, y.first());
         cp_swap(second_, y.second());
      }
   private:
      first_type first_;
      second_type second_;
   };

   // 1    derive from T1

   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 1>
      : protected ::boost::remove_cv<T1>::type
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

      compressed_pair_imp() {}

      compressed_pair_imp(first_param_type x, second_param_type y)
         : first_type(x), second_(y) {}

      compressed_pair_imp(first_param_type x)
         : first_type(x) {}

      compressed_pair_imp(second_param_type y)
         : second_(y) {}

      first_reference       first()       {return *this;}
      first_const_reference first() const {return *this;}

      second_reference       second()       {return second_;}
      second_const_reference second() const {return second_;}

      void swap(::boost::compressed_pair<T1,T2>& y)
      {
         // no need to swap empty base class:
         cp_swap(second_, y.second());
      }
   private:
      second_type second_;
   };

   // 2    derive from T2

   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 2>
      : protected ::boost::remove_cv<T2>::type
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

      compressed_pair_imp() {}

      compressed_pair_imp(first_param_type x, second_param_type y)
         : second_type(y), first_(x) {}

      compressed_pair_imp(first_param_type x)
         : first_(x) {}

      compressed_pair_imp(second_param_type y)
         : second_type(y) {}

      first_reference       first()       {return first_;}
      first_const_reference first() const {return first_;}

      second_reference       second()       {return *this;}
      second_const_reference second() const {return *this;}

      void swap(::boost::compressed_pair<T1,T2>& y)
      {
         // no need to swap empty base class:
         cp_swap(first_, y.first());
      }

   private:
      first_type first_;
   };

   // 3    derive from T1 and T2

   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 3>
      : protected ::boost::remove_cv<T1>::type,
        protected ::boost::remove_cv<T2>::type
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

      compressed_pair_imp() {}

      compressed_pair_imp(first_param_type x, second_param_type y)
         : first_type(x), second_type(y) {}

      compressed_pair_imp(first_param_type x)
         : first_type(x) {}

      compressed_pair_imp(second_param_type y)
         : second_type(y) {}

      first_reference       first()       {return *this;}
      first_const_reference first() const {return *this;}

      second_reference       second()       {return *this;}
      second_const_reference second() const {return *this;}
      //
      // no need to swap empty bases:
      void swap(::boost::compressed_pair<T1,T2>&) {}
   };

   // JM
   // 4    T1 == T2, T1 and T2 both empty
   //      Originally this did not store an instance of T2 at all
   //      but that led to problems beause it meant &x.first() == &x.second()
   //      which is not true for any other kind of pair, so now we store an instance
   //      of T2 just in case the user is relying on first() and second() returning
   //      different objects (albeit both empty).
   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 4>
      : protected ::boost::remove_cv<T1>::type
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

      compressed_pair_imp() {}

      compressed_pair_imp(first_param_type x, second_param_type y)
         : first_type(x), m_second(y) {}

      compressed_pair_imp(first_param_type x)
         : first_type(x), m_second(x) {}

      first_reference       first()       {return *this;}
      first_const_reference first() const {return *this;}

      second_reference       second()       {return m_second;}
      second_const_reference second() const {return m_second;}

      void swap(::boost::compressed_pair<T1,T2>&) {}
   private:
      T2 m_second;
   };

   // 5    T1 == T2 and are not empty:   //JM

   template <class T1, class T2>
   class compressed_pair_imp<T1, T2, 5>
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

      compressed_pair_imp() {}

      compressed_pair_imp(first_param_type x, second_param_type y)
         : first_(x), second_(y) {}

      compressed_pair_imp(first_param_type x)
         : first_(x), second_(x) {}

      first_reference       first()       {return first_;}
      first_const_reference first() const {return first_;}

      second_reference       second()       {return second_;}
      second_const_reference second() const {return second_;}

      void swap(::boost::compressed_pair<T1, T2>& y)
      {
         cp_swap(first_, y.first());
         cp_swap(second_, y.second());
      }
   private:
      first_type first_;
      second_type second_;
   };

}  // details

template <class T1, class T2>
class compressed_pair
#ifndef BOOST_UTILITY_DOCS
    : private ::boost::details::compressed_pair_imp<T1, T2,
             ::boost::details::compressed_pair_switch<
                    T1,
                    T2,
                    ::boost::is_same<typename remove_cv<T1>::type, typename remove_cv<T2>::type>::value,
                    ::boost::details::compressed_pair_empty<T1>::value,
                    ::boost::details::compressed_pair_empty<T2>::value>::value>
#endif // BOOST_UTILITY_DOCS
{
private:
   typedef details::compressed_pair_imp<T1, T2,
             ::boost::details::compressed_pair_switch<
                    T1,
                    T2,
                    ::boost::is_same<typename remove_cv<T1>::type, typename remove_cv<T2>::type>::value,
                    ::boost::details::compressed_pair_empty<T1>::value,
                    ::boost::details::compressed_pair_empty<T2>::value>::value> base;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : base() {}
            compressed_pair(first_param_type x, second_param_type y) : base(x, y) {}
   explicit compressed_pair(first_param_type x) : base(x) {}
   explicit compressed_pair(second_param_type y) : base(y) {}

   first_reference       first()       {return base::first();}
   first_const_reference first() const {return base::first();}

   second_reference       second()       {return base::second();}
   second_const_reference second() const {return base::second();}

   void swap(compressed_pair& y) { base::swap(y); }
};

// JM
// Partial specialisation for case where T1 == T2:
//
template <class T>
class compressed_pair<T, T>
#ifndef BOOST_UTILITY_DOCS
   : private details::compressed_pair_imp<T, T,
             ::boost::details::compressed_pair_switch<
                    T,
                    T,
                    ::boost::is_same<typename remove_cv<T>::type, typename remove_cv<T>::type>::value,
                    ::boost::details::compressed_pair_empty<T>::value,
                    ::boost::details::compressed_pair_empty<T>::value>::value>
#endif // BOOST_UTILITY_DOCS
{
private:
   typedef details::compressed_pair_imp<T, T,
             ::boost::details::compressed_pair_switch<
                    T,
                    T,
                    ::boost::is_same<typename remove_cv<T>::type, typename remove_cv<T>::type>::value,
                    ::boost::details::compressed_pair_empty<T>::value,
                    ::boost::details::compressed_pair_empty<T>::value>::value> base;
public:
   typedef T                                                  first_type;
   typedef T                                                  second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : base() {}
            compressed_pair(first_param_type x, second_param_type y) : base(x, y) {}
#if !(defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530))
   explicit 
#endif
      compressed_pair(first_param_type x) : base(x) {}

   first_reference       first()       {return base::first();}
   first_const_reference first() const {return base::first();}

   second_reference       second()       {return base::second();}
   second_const_reference second() const {return base::second();}

   void swap(::boost::compressed_pair<T,T>& y) { base::swap(y); }
};

template <class T1, class T2>
inline
void
swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}

} // boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif 

#endif // BOOST_DETAIL_COMPRESSED_PAIR_HPP


/* compressed_pair.hpp
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
*/