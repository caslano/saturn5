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
Jq8N/U3dKvLNuzB8uxC38e2y0LA30YbYMPobQx6jWd9x3rjwexONjKvbFlfYOhvDb0a5xqNbV8NC+XV1NYv4rcK1WlcTpu1r2uLK8G1BGlHoatZGoatZ23hdzZWNsLcOtsvi+Lp1dS3pzTHUlaoh6a9X11NHc6KoozlR1NGcv1FHVzeijoL9qap5XX3WDaS3aK1bn2XuT9eFryvSiFyftWht4/VZ5MGsz3Lfvwz297cQd6Uuq7k/3FTfcyWKMq78G2W8KS8yO3yzXXr0dvLR2pkn/+QjfMLJs+Y/+8yqWRcu3afPbRe2nBJeR2XWIYXTdUWv+zHrnMLZ/0dv3x6t3X60ezY11XwKsw4s/DwL8zyIprPD17bzT9fq2Ga4dFjdHbqu9SIXb5Dr6pCrFrmWDaSXvDb87+7l1O2tDf+7ezh1eyLXsoH0CkUuq4H8zTHImdJbJHLpDaS3sh65vRzrjxROS7Tm4fvy9wPTmtY2ff20RM8+PUr7dPSsUa1Hgk7Ws1HfBDbqVnlio+3UM4k7EO/HX45fiV+PtyoSra74g/AzKjx9qOc85znPec5znvOc5zznOc95znNbmtsc4//2QIW/8u+P/9vj72841vd7QsbfTxc94Wn4ydnoTJ+uXZ+ockJpycQDi2YGx0YOT6kZG8kS+9nWSvYka0/+H4YvwRvHfZ92j5v4/cZxNIfsjtYYde475O21tLojUMVCJJMY2Hszl7zCzzIattcNjqmQd8OYCvlwjKn03QxrG0W7JlF/NdYyO278j5NSVrfLH+RPyu3wy8YtZ02iLWWNoaayl7Z18f5gP5brqwqfiJ8kHTNN1vdpDdvCDnAvmAv3gTvCfWEOPFSOR8NsWCbHU2EmPE2OaS+93kx4fb5bh29YU6Z+fT16+sh09Ov5+wy4AO/Wx2fDPLzo4M36d5fu3aRznwNFz15Hxz4QH06nXqXXealffx7Az8XPx4uuXHTkWj+Obrx+nbjow7UuXOu/o9R9h9F1az13qUu3LXrtOrrslfh80V+vx2/wdNKe85znPOc5z3nOcxG7zfb9X9403/9vO77/48SmvEzKMkW+/+c8Vfv9X14yfXygCAWA6/s/XfajnatkJ/JNHcM3yA5mG9qnIv/2d8oGrNo14lvKut93qPPZ6vwAAvjS6m3J+Qy4RJ1vr9eO/5Lfe4cyfyU6BLeuIKERuoKW1p4pF6vf4ffyanUHy5tQd2C20wyvU7igt/pWH3rFoA03l+5e1XXds1/+fk7HcN+00esgAkoHccXUly847rpnFy67/MKJ/vWLtms6HYTZXnLL101cepQd/tYpk869PuPbuze0nvDeE3Mf7hK9zsJsJ9u0dppnBK8/uSe8JnaOsw1ziFNhGsyE6bA9zIC7wEzYA24Le8Is0WVsBw+A28MhsB08BLaFR8McOEXCJ8VGpstowC5R6zZe++qfWzP3pXNjrQ34cLaJcdVNY5/YvTrURjHpvNg6OpMcwsLbKjZsp+jWp4yttnUqnCdds60iMuc13laxITvFedWhtorz+a24fk1jp7ikOjJbxeT7ms5eccl5sVHbLDbWXnFkwNP7eM5znvOc5zzXGBeHL9vE3/+T7X2X+JJXGoC/uQagrQNY79ABsHyNFVwHLw12h7fZ80HXKB3AeObM9hsxpEfBiJHDBw/Zv2a/uSnJFucm+C3jfnMSl38tZV8uZCssx95gjz5hn00yfv874/rjVNzKyYRnETcdLlXnW8SssC5ir+t860VfpnF+rTMd2aOsZFaRcV86tyz5GH/UeKbTpkt+Wz7us+P7tra6s/9Kc58qByGXqXJkktaAFJ/0h+1sWVJoo8JqQjuosCpfLPqR/sQ=
*/