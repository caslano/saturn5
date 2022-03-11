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
   : private ::boost::details::compressed_pair_imp<T1, T2,
             ::boost::details::compressed_pair_switch<
                    T1,
                    T2,
                    ::boost::is_same<typename remove_cv<T1>::type, typename remove_cv<T2>::type>::value,
                    ::boost::details::compressed_pair_empty<T1>::value,
                    ::boost::details::compressed_pair_empty<T2>::value>::value>
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
   : private details::compressed_pair_imp<T, T,
             ::boost::details::compressed_pair_switch<
                    T,
                    T,
                    ::boost::is_same<typename remove_cv<T>::type, typename remove_cv<T>::type>::value,
                    ::boost::details::compressed_pair_empty<T>::value,
                    ::boost::details::compressed_pair_empty<T>::value>::value>
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