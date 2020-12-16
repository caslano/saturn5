
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
IfGwTHwSEg3x89oIePdaUGe/N5+d426Q1jLWRQYIn71ud8nVnKciB/OwfxyndhSvVfAbG7twMgaw7ufIaTDjNOhzpLhLr+F+2goJO92qn8ogVe60FVEWNn3CRH8bglzsSgP+7GUEq8id5o875pBxPqchpyNETlU6A6Gj33OF3SFwuVFxN7YNsyMhLHgiGXQXe7LKuBUzTqQrDjdwV3wyQnbXBFtgd7UJ6BO7NJZrR/6EAjjiFPfLTdwvq0cE9Mtjpwz98r3JiJ/HIRB0OQCgXQGMRAxfZR3GXI6qCwqrPP6BEFwVD0AEXbybH4V/Iha2cZfOYkwiEZNZCpOmAFaw+zzEPp9lAJTuG+6mj0SilEwnCq59WATX7utsKJGMbV7KNT0wHGqarWp64aS/zVxjO4+ycuEBnw13XZZiegz+f1knxRRXN8W0HP7Phven4e/l8Nm44f+ey+A/vL8P/z+B56l1Umr8N5zD/+2VwgoIa3D0GSnJhpIfdV1ZEV5GlgL6RtK8/3qo0XXAx1l4tbofJ71hSLJrr1CSh5OeMSQ5tT9RUn9OuteQlKqtpKRrOWmuImMKssKnT4N/TI136y5YhZ0YdhOAXZqLKfnmgJsbBcnu0q6RNEN/GSK/ygmYse6POn4B1xO3ba+LNhnx7IrwPzsM8WmmXWb5nK7iYbmv3xN3Xo/nAjh3dN4IYtINK6GmZHcTpMVU7E5bzx5IFb3mKcoEPeQBYOMu0wMtX05rxgCX9jYoeS1bgErnFcTBy7Tjt8csNcMRiG1+Y+Euh7u8rid+sxPEuJmmZWBH2JtTnGnyHDoKm6NnWVm8p9e+W6M9pcd0+sV7ln12DFgC2s6u6tiVCrjYoQxzRDPZCEZwBcU78QLeArhnkixwOCbQtyONPyBJT1y8g+gisEc+hodq0GAYqkk4VBOxI/KgadqQk7QLLxXiQyyXDeVAMMhToBGUgWiP9ge9XAfEHFCpg8Z/khj/63H8FdC6J2j8u7lLJjOAjyAdWuGiT+EwaPLzywAHjGwSPgPWsOYJhYYByZ4uB7Rb3XgympB6Y/gDfpF/QeL7xl2UEq1H0MfKBNESuvtkJlZDd7i+kMGyA5V+yxldXKwr5B7Zl63oP168U84/t43+vzsLgj5ux0Q4ckxLoCPHnyaqk8hWjH4rk6I3iGhtynG9GuwB1s8KckdSX1Zsi+we4I5EMbyVQ5KPa0PDEnd0gmxAEv7SVHiyQrs510sDZXO+1yHPJsijivWFU70yApJNtOMXfAVo3SCYZRNwls0iifj3NGs/ggYJjyMJXsisceZJmHm+yryYMz9JNIlQ1E4W90ysQI/6r1Ql3va8/GS+Y1CNEdQ4BaobgNKSfyB4N5rZi5W41rDT4j9ATGQwrdylPzGYdwcCmIkKzHffAZgP4Uup+Flc/HEKrSmPUh7MM6DJN7yykwT4t7YR+Lbu0jMMfjaCn6HA343g5yL4+5E2uhfjru0lCDDNJZ5SBSk2SGhV9nOXJBAWysbIpG5k7qgDojOfU5XByus4rY72gzlQy6Mel/1rC6lr+QI8+RJ4+5TiRZf2Dohzd3KrkT5cGAHZuXU/PxfLnESjq5MJvf9nXJ2c7z7+wQ4sm07c3CFGcNMG8mlKqC1qD1xxBDXmihMXqhyR6UeqpdYekjU+vIPfKFOxy+UXUFjYD5IwOZurTT+mByjcdpTET1y2JOi310IaxMUn2pPXSRrk+DVoRhiiIlTOlZAzwD6li96YOAeOHvAu77cFHs8RwOeDJIDrAIBf0JGP/ByV1rGWNI6yvRcgVNo0Yimf/g5y+p/qEY/tgCpw1i4LjE0PVWA2FxiaZBYFDti5dhaDJcEH6S7BQrQ=
*/