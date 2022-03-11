//  (C) Copyright John Maddock 2006.
//  (C) Copyright Paul A. Bristow 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_COMPLEMENT_HPP
#define BOOST_STATS_COMPLEMENT_HPP

//
// This code really defines our own tuple type.
// It would be nice to reuse boost::math::tuple
// while retaining our own type safety, but it's
// not clear if that's possible.  In any case this
// code is *very* lightweight.
//
namespace boost{ namespace math{

template <class Dist, class RealType>
struct complemented2_type
{
   complemented2_type(
      const Dist& d, 
      const RealType& p1)
      : dist(d), 
        param(p1) {}

   const Dist& dist;
   const RealType& param;

private:
   complemented2_type& operator=(const complemented2_type&);
};

template <class Dist, class RealType1, class RealType2>
struct complemented3_type
{
   complemented3_type(
      const Dist& d, 
      const RealType1& p1,
      const RealType2& p2)
      : dist(d), 
        param1(p1), 
        param2(p2) {}

   const Dist& dist;
   const RealType1& param1;
   const RealType2& param2;
private:
   complemented3_type& operator=(const complemented3_type&);
};

template <class Dist, class RealType1, class RealType2, class RealType3>
struct complemented4_type
{
   complemented4_type(
      const Dist& d, 
      const RealType1& p1,
      const RealType2& p2,
      const RealType3& p3)
      : dist(d), 
        param1(p1), 
        param2(p2), 
        param3(p3) {}

   const Dist& dist;
   const RealType1& param1;
   const RealType2& param2;
   const RealType3& param3;
private:
   complemented4_type& operator=(const complemented4_type&);
};

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4>
struct complemented5_type
{
   complemented5_type(
      const Dist& d, 
      const RealType1& p1,
      const RealType2& p2,
      const RealType3& p3,
      const RealType4& p4)
      : dist(d), 
        param1(p1), 
        param2(p2), 
        param3(p3), 
        param4(p4) {}

   const Dist& dist;
   const RealType1& param1;
   const RealType2& param2;
   const RealType3& param3;
   const RealType4& param4;
private:
   complemented5_type& operator=(const complemented5_type&);
};

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4, class RealType5>
struct complemented6_type
{
   complemented6_type(
      const Dist& d, 
      const RealType1& p1,
      const RealType2& p2,
      const RealType3& p3,
      const RealType4& p4,
      const RealType5& p5)
      : dist(d), 
        param1(p1), 
        param2(p2), 
        param3(p3), 
        param4(p4), 
        param5(p5) {}

   const Dist& dist;
   const RealType1& param1;
   const RealType2& param2;
   const RealType3& param3;
   const RealType4& param4;
   const RealType5& param5;
private:
   complemented6_type& operator=(const complemented6_type&);
};

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4, class RealType5, class RealType6>
struct complemented7_type
{
   complemented7_type(
      const Dist& d, 
      const RealType1& p1,
      const RealType2& p2,
      const RealType3& p3,
      const RealType4& p4,
      const RealType5& p5,
      const RealType6& p6)
      : dist(d), 
        param1(p1), 
        param2(p2), 
        param3(p3), 
        param4(p4), 
        param5(p5), 
        param6(p6) {}

   const Dist& dist;
   const RealType1& param1;
   const RealType2& param2;
   const RealType3& param3;
   const RealType4& param4;
   const RealType5& param5;
   const RealType6& param6;
private:
   complemented7_type& operator=(const complemented7_type&);
};

template <class Dist, class RealType>
inline complemented2_type<Dist, RealType> complement(const Dist& d, const RealType& r)
{
   return complemented2_type<Dist, RealType>(d, r);
}

template <class Dist, class RealType1, class RealType2>
inline complemented3_type<Dist, RealType1, RealType2> complement(const Dist& d, const RealType1& r1, const RealType2& r2)
{
   return complemented3_type<Dist, RealType1, RealType2>(d, r1, r2);
}

template <class Dist, class RealType1, class RealType2, class RealType3>
inline complemented4_type<Dist, RealType1, RealType2, RealType3> complement(const Dist& d, const RealType1& r1, const RealType2& r2, const RealType3& r3)
{
   return complemented4_type<Dist, RealType1, RealType2, RealType3>(d, r1, r2, r3);
}

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4>
inline complemented5_type<Dist, RealType1, RealType2, RealType3, RealType4> complement(const Dist& d, const RealType1& r1, const RealType2& r2, const RealType3& r3, const RealType4& r4)
{
   return complemented5_type<Dist, RealType1, RealType2, RealType3, RealType4>(d, r1, r2, r3, r4);
}

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4, class RealType5>
inline complemented6_type<Dist, RealType1, RealType2, RealType3, RealType4, RealType5> complement(const Dist& d, const RealType1& r1, const RealType2& r2, const RealType3& r3, const RealType4& r4, const RealType5& r5)
{
   return complemented6_type<Dist, RealType1, RealType2, RealType3, RealType4, RealType5>(d, r1, r2, r3, r4, r5);
}

template <class Dist, class RealType1, class RealType2, class RealType3, class RealType4, class RealType5, class RealType6>
inline complemented7_type<Dist, RealType1, RealType2, RealType3, RealType4, RealType5, RealType6> complement(const Dist& d, const RealType1& r1, const RealType2& r2, const RealType3& r3, const RealType4& r4, const RealType5& r5, const RealType6& r6)
{
   return complemented7_type<Dist, RealType1, RealType2, RealType3, RealType4, RealType5, RealType6>(d, r1, r2, r3, r4, r5, r6);
}

} // namespace math
} // namespace boost

#endif // BOOST_STATS_COMPLEMENT_HPP


/* complement.hpp
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
*/