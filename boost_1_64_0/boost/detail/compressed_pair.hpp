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
HPmHjFUKRXzMCuf3Hz4itd9fN1Lp92+wrtLvX32McoTMG7HC+f2RNVP7/ZPXVlrzSaOUzszI9ZQugHftf9rvN5iLeXqZFPNhLuZR5aqYD+c/YFZozv9opbyPLDPbYkXMB8n4cw0p5sPI+HItiQyrnL2wjlLOHqxQerpXrWUesBQxHyTjOImMQYyMA2QyrPxtKZEhGYWxFUpp8JuhixUxHyTju9WlmA8j470REhlWa/O4pIyS7bp5XeUsaK452cvJCHfQXcXw8Usj4oqRLbXkhnwqMoRLKj1ffRGP61eGtsdFHfjIo3tR+IBFsLBTj3u4ZgLONs9ZUAA+O3kxSyL3M5asAQU66vKdogjCxq6BBWBYioJVxLYt+uLZ/VrZK3tlr+yVvf6Nl/J7b934/ccg34WxuErswrjbsvmm+cDW5v3k7TnNR04pqxReMySsv97+xwt3EhIiB5YdljSvwR0XUXQzYaLUnDQByNEAuITLpwSQw0caAI/whzQAOcLZ1gDkCm9dA5An/HINQMIbBoDvUrTDIAagbYdiBqBtB68FIEy2tizBt0TOcINnQ3ypQAhAcQvW+JmYeQypF+74xtWOyeXNsLswGJ3PypSh/zXItJ+OoSB3x4ynGfhuDn+d2fsg3YUHm+vYp5vKgLjFCPFyuP3ZWc7YnYgECi4WBUEU8YlnvSVn4RPPojRXsCx8kt3r5niXPBFp7vmG7NGDYiDp4ORdvzE6ed3/0c9MS1o/C7Q+Nppr/TtBsau5mXRvOWx0qukMOaTdpdj/jn39+A2aUuj+QujkGVFXG/xMIzLhPfv0YsWWHdiuFHTXFgXlaEdQdIw8YwgCaOUCsgNZdJQcjgsCSCX5nLy0kahIRmaIVGudhgQmWQG5TkGJh9dpyHWWJur0ALIB4dNIzad/efCZl5rPYUo+ZetsrdMpgw0Sqcr+HMTrdGr6c5CMLF+kWuvMl8Ako63szxwRXdD0Z86A8Wmk5tO/PPjMS83nMCWf8mBqrdMlgxWLVGV/FouovaY/i2VkBSLVWmeBBCaNscr+zOV1Fmj6M3fA+DRS8+lfHnzmpeZzmJJP2fex1umWwbwiVdmfXl6nW9OfXhlZoUi11lkogUkukbI/80TYTdOfeQPGp5GaT//y4DMvNZ/DNHw6tHbIoeTTkbo/HXb6s0CkppTbHJGa2t4W2LG3/eLTSObTTn/2i8+8ZD7t2Fun1g45lX6CM7U/5LTjDxWK1JRymytSU9vbQjv2tl98Gsl82vGH+sVnXjKfduytS2uHXEo/wZXaH3LZ8YcMrZ9gKO2QkdreGnbsbb/4NJL5tOMP9YvPvGQ+7dhbt9aPdyv9BHdqf8htxx/KF6kp/T6PSE09X8m3M1/pF59GMp92/KF+8Zmn4lM/X+k58Pt43PsYmcWe3hXZVgQrCmC2Gu/ik1Xf9ApYLCojbwDBq4Azg3yi6/achWnwPMdBV4Ke6qkgM2ItKm9HEcnWooNIx4KPXGx1aY6Id8x3shFrlmclbWGy4pquvDN1eV+68q7U5f3pyrtJ+cqu07u8p/9C4ik9H0JQhZRphojKTutiRGXWfzSikr2yV/YaqIuGJsuErZA+yB7ys1AlvOM+7KfeOAs5wxkx565G8uCD2Gp8ASjvoOWj3c4+NE7BcFsNHFRAbma0Bhwtnsqu2Er4vDAUxlc6nfQzT4EnbcVTsZLLhgoig9GT4/H46V2IGM6dhNeT61mN7eFA9JnyPp6dY6cuCz9BXhXH17EqSbCgsH7V/rchtBGedPTx9sNPvYcCNM6PQVwkaQLsxwjQ5l2VUlpMn9Ym9RCAYXgq5vyT3OxL5tF6AtXpzOzT5Nb225PSN9/hpFiro20=
*/