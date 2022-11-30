
// ----------------------------------------------------------------------------
// group.hpp :  encapsulates a group of manipulators along with an argument
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

                      
// group_head : cut the last element of a group out.
// (is overloaded below on each type of group)

// group_last : returns the last element of a group
// (is overloaded below on each type of group)
// ----------------------------------------------------------------------------


#ifndef BOOST_FORMAT_GROUP_HPP
#define BOOST_FORMAT_GROUP_HPP

#include <boost/config.hpp>


namespace boost {
namespace io {


namespace detail {


// empty group, but useful even though.
struct group0 
{
    group0()      {}
};

template <class Ch, class Tr>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << ( BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group0& )
{ 
   return os; 
}

template <class T1>
struct group1
{
    T1 a1_;
    group1(T1 a1)
      : a1_(a1)
      {}
private:
   group1& operator=(const group1&);
};

template <class Ch, class Tr, class T1>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group1<T1>& x)
{ 
   os << x.a1_;  
   return os; 
}




template <class T1,class T2>
struct group2
{
    T1 a1_;
    T2 a2_;
    group2(T1 a1,T2 a2)
      : a1_(a1),a2_(a2)
      {}
private:
   group2& operator=(const group2&);
};

template <class Ch, class Tr, class T1,class T2>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group2<T1,T2>& x)
{ 
   os << x.a1_<< x.a2_;  
   return os; 
}

template <class T1,class T2,class T3>
struct group3
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    group3(T1 a1,T2 a2,T3 a3)
      : a1_(a1),a2_(a2),a3_(a3)
      {}
private:
   group3& operator=(const group3&);
};

template <class Ch, class Tr, class T1,class T2,class T3>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group3<T1,T2,T3>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_;  
   return os; 
}

template <class T1,class T2,class T3,class T4>
struct group4
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    group4(T1 a1,T2 a2,T3 a3,T4 a4)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4)
      {}
private:
   group4& operator=(const group4&);
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group4<T1,T2,T3,T4>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5>
struct group5
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    group5(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group5<T1,T2,T3,T4,T5>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5,class T6>
struct group6
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    T6 a6_;
    group6(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5,class T6>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group6<T1,T2,T3,T4,T5,T6>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_<< x.a6_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
struct group7
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    T6 a6_;
    T7 a7_;
    group7(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5,class T6,class T7>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group7<T1,T2,T3,T4,T5,T6,T7>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_<< x.a6_<< x.a7_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
struct group8
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    T6 a6_;
    T7 a7_;
    T8 a8_;
    group8(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group8<T1,T2,T3,T4,T5,T6,T7,T8>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_<< x.a6_<< x.a7_<< x.a8_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
struct group9
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    T6 a6_;
    T7 a7_;
    T8 a8_;
    T9 a9_;
    group9(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8),a9_(a9)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group9<T1,T2,T3,T4,T5,T6,T7,T8,T9>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_<< x.a6_<< x.a7_<< x.a8_<< x.a9_;  
   return os; 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
struct group10
{
    T1 a1_;
    T2 a2_;
    T3 a3_;
    T4 a4_;
    T5 a5_;
    T6 a6_;
    T7 a7_;
    T8 a8_;
    T9 a9_;
    T10 a10_;
    group10(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9,T10 a10)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8),a9_(a9),a10_(a10)
      {}
};

template <class Ch, class Tr, class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
inline
BOOST_IO_STD basic_ostream<Ch, Tr>&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>& x)
{ 
   os << x.a1_<< x.a2_<< x.a3_<< x.a4_<< x.a5_<< x.a6_<< x.a7_<< x.a8_<< x.a9_<< x.a10_;  
   return os; 
}




template <class T1,class T2>
inline
group1<T1> 
group_head( group2<T1,T2> const& x)
{
   return group1<T1> (x.a1_); 
}

template <class T1,class T2>
inline
group1<T2> 
group_last( group2<T1,T2> const& x)
{
   return group1<T2> (x.a2_); 
}



template <class T1,class T2,class T3>
inline
group2<T1,T2> 
group_head( group3<T1,T2,T3> const& x)
{
   return group2<T1,T2> (x.a1_,x.a2_); 
}

template <class T1,class T2,class T3>
inline
group1<T3> 
group_last( group3<T1,T2,T3> const& x)
{
   return group1<T3> (x.a3_); 
}



template <class T1,class T2,class T3,class T4>
inline
group3<T1,T2,T3> 
group_head( group4<T1,T2,T3,T4> const& x)
{
   return group3<T1,T2,T3> (x.a1_,x.a2_,x.a3_); 
}

template <class T1,class T2,class T3,class T4>
inline
group1<T4> 
group_last( group4<T1,T2,T3,T4> const& x)
{
   return group1<T4> (x.a4_); 
}



template <class T1,class T2,class T3,class T4,class T5>
inline
group4<T1,T2,T3,T4> 
group_head( group5<T1,T2,T3,T4,T5> const& x)
{
   return group4<T1,T2,T3,T4> (x.a1_,x.a2_,x.a3_,x.a4_); 
}

template <class T1,class T2,class T3,class T4,class T5>
inline
group1<T5> 
group_last( group5<T1,T2,T3,T4,T5> const& x)
{
   return group1<T5> (x.a5_); 
}



template <class T1,class T2,class T3,class T4,class T5,class T6>
inline
group5<T1,T2,T3,T4,T5> 
group_head( group6<T1,T2,T3,T4,T5,T6> const& x)
{
   return group5<T1,T2,T3,T4,T5> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_); 
}

template <class T1,class T2,class T3,class T4,class T5,class T6>
inline
group1<T6> 
group_last( group6<T1,T2,T3,T4,T5,T6> const& x)
{
   return group1<T6> (x.a6_); 
}



template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
inline
group6<T1,T2,T3,T4,T5,T6> 
group_head( group7<T1,T2,T3,T4,T5,T6,T7> const& x)
{
   return group6<T1,T2,T3,T4,T5,T6> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_); 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
inline
group1<T7> 
group_last( group7<T1,T2,T3,T4,T5,T6,T7> const& x)
{
   return group1<T7> (x.a7_); 
}



template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
inline
group7<T1,T2,T3,T4,T5,T6,T7> 
group_head( group8<T1,T2,T3,T4,T5,T6,T7,T8> const& x)
{
   return group7<T1,T2,T3,T4,T5,T6,T7> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_); 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
inline
group1<T8> 
group_last( group8<T1,T2,T3,T4,T5,T6,T7,T8> const& x)
{
   return group1<T8> (x.a8_); 
}



template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
inline
group8<T1,T2,T3,T4,T5,T6,T7,T8> 
group_head( group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> const& x)
{
   return group8<T1,T2,T3,T4,T5,T6,T7,T8> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_,x.a8_); 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
inline
group1<T9> 
group_last( group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> const& x)
{
   return group1<T9> (x.a9_); 
}



template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
inline
group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> 
group_head( group10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> const& x)
{
   return group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_,x.a8_,x.a9_); 
}

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
inline
group1<T10> 
group_last( group10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> const& x)
{
   return group1<T10> (x.a10_); 
}





} // namespace detail



// helper functions


inline detail::group1< detail::group0 >  
group() { return detail::group1< detail::group0 > ( detail::group0() ); }

template  <class T1, class Var> 
inline
detail::group1< detail::group2<T1, Var const&> >
  group(T1 a1, Var const& var)
{ 
   return detail::group1< detail::group2<T1, Var const&> >
                   ( detail::group2<T1, Var const&> 
                        (a1, var) 
                  );
}

template  <class T1,class T2, class Var> 
inline
detail::group1< detail::group3<T1,T2, Var const&> >
  group(T1 a1,T2 a2, Var const& var)
{ 
   return detail::group1< detail::group3<T1,T2, Var const&> >
                   ( detail::group3<T1,T2, Var const&> 
                        (a1,a2, var) 
                  );
}

template  <class T1,class T2,class T3, class Var> 
inline
detail::group1< detail::group4<T1,T2,T3, Var const&> >
  group(T1 a1,T2 a2,T3 a3, Var const& var)
{ 
   return detail::group1< detail::group4<T1,T2,T3, Var const&> >
                   ( detail::group4<T1,T2,T3, Var const&> 
                        (a1,a2,a3, var) 
                  );
}

template  <class T1,class T2,class T3,class T4, class Var> 
inline
detail::group1< detail::group5<T1,T2,T3,T4, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4, Var const& var)
{ 
   return detail::group1< detail::group5<T1,T2,T3,T4, Var const&> >
                   ( detail::group5<T1,T2,T3,T4, Var const&> 
                        (a1,a2,a3,a4, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5, class Var> 
inline
detail::group1< detail::group6<T1,T2,T3,T4,T5, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5, Var const& var)
{ 
   return detail::group1< detail::group6<T1,T2,T3,T4,T5, Var const&> >
                   ( detail::group6<T1,T2,T3,T4,T5, Var const&> 
                        (a1,a2,a3,a4,a5, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6, class Var> 
inline
detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6, Var const& var)
{ 
   return detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var const&> >
                   ( detail::group7<T1,T2,T3,T4,T5,T6, Var const&> 
                        (a1,a2,a3,a4,a5,a6, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7, class Var> 
inline
detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7, Var const& var)
{ 
   return detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> >
                   ( detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8, class Var> 
inline
detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8, Var const& var)
{ 
   return detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> >
                   ( detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9, class Var> 
inline
detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9, Var const& var)
{ 
   return detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> >
                   ( detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8,a9, var) 
                  );
}


#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST

template  <class T1, class Var> 
inline
detail::group1< detail::group2<T1, Var&> >
  group(T1 a1, Var& var)
{ 
   return detail::group1< detail::group2<T1, Var&> >
                   ( detail::group2<T1, Var&> 
                        (a1, var) 
                  );
}

template  <class T1,class T2, class Var> 
inline
detail::group1< detail::group3<T1,T2, Var&> >
  group(T1 a1,T2 a2, Var& var)
{ 
   return detail::group1< detail::group3<T1,T2, Var&> >
                   ( detail::group3<T1,T2, Var&> 
                        (a1,a2, var) 
                  );
}

template  <class T1,class T2,class T3, class Var> 
inline
detail::group1< detail::group4<T1,T2,T3, Var&> >
  group(T1 a1,T2 a2,T3 a3, Var& var)
{ 
   return detail::group1< detail::group4<T1,T2,T3, Var&> >
                   ( detail::group4<T1,T2,T3, Var&> 
                        (a1,a2,a3, var) 
                  );
}

template  <class T1,class T2,class T3,class T4, class Var> 
inline
detail::group1< detail::group5<T1,T2,T3,T4, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4, Var& var)
{ 
   return detail::group1< detail::group5<T1,T2,T3,T4, Var&> >
                   ( detail::group5<T1,T2,T3,T4, Var&> 
                        (a1,a2,a3,a4, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5, class Var> 
inline
detail::group1< detail::group6<T1,T2,T3,T4,T5, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5, Var& var)
{ 
   return detail::group1< detail::group6<T1,T2,T3,T4,T5, Var&> >
                   ( detail::group6<T1,T2,T3,T4,T5, Var&> 
                        (a1,a2,a3,a4,a5, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6, class Var> 
inline
detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6, Var& var)
{ 
   return detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var&> >
                   ( detail::group7<T1,T2,T3,T4,T5,T6, Var&> 
                        (a1,a2,a3,a4,a5,a6, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7, class Var> 
inline
detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7, Var& var)
{ 
   return detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> >
                   ( detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8, class Var> 
inline
detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8, Var& var)
{ 
   return detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> >
                   ( detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8, var) 
                  );
}

template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9, class Var> 
inline
detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9, Var& var)
{ 
   return detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> >
                   ( detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8,a9, var) 
                  );
}


#endif  // - BOOST_NO_OVERLOAD_FOR_NON_CONST


} // namespace io

} // namespace boost


#endif   // BOOST_FORMAT_GROUP_HPP

/* group.hpp
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
*/