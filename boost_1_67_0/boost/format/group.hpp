
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