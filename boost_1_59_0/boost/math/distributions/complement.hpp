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
+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
*/