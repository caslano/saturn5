//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_AFFINE_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_AFFINE_HPP

#include <boost/gil/point.hpp>

namespace boost { namespace gil {

////////////////////////////////////////////////////////////////////////////////////////
///
/// Simple matrix to do 2D affine transformations. It is actually 3x3 but the last column is [0 0 1]
///
////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class matrix3x2 {
public:
    matrix3x2() : a(1), b(0), c(0), d(1), e(0), f(0) {}
    matrix3x2(T A, T B, T C, T D, T E, T F) : a(A),b(B),c(C),d(D),e(E),f(F) {}
    matrix3x2(const matrix3x2& mat) : a(mat.a), b(mat.b), c(mat.c), d(mat.d), e(mat.e), f(mat.f) {}
    matrix3x2& operator=(const matrix3x2& m)           { a=m.a; b=m.b; c=m.c; d=m.d; e=m.e; f=m.f; return *this; }

    matrix3x2& operator*=(const matrix3x2& m)          { (*this) = (*this)*m; return *this; }

    static matrix3x2 get_rotate(T rads)                { T c=std::cos(rads); T s=std::sin(rads); return matrix3x2(c,s,-s,c,0,0); }
    static matrix3x2 get_translate(point<T> const& t)
    {
        return matrix3x2(1, 0, 0, 1, t.x, t.y);
    }
    static matrix3x2 get_translate(T x, T y)           { return matrix3x2(1  ,0,0,1  ,x,  y  ); }
    static matrix3x2 get_scale(point<T> const& s)
    {
        return matrix3x2(s.x, 0, 0, s.y, 0, 0);
    }
    static matrix3x2 get_scale(T x, T y)           { return matrix3x2(x,  0,0,y,  0  ,0  ); }
    static matrix3x2 get_scale(T s)                { return matrix3x2(s  ,0,0,s  ,0  ,0  ); }

    T a,b,c,d,e,f;
};

template <typename T> BOOST_FORCEINLINE
matrix3x2<T> operator*(const matrix3x2<T>& m1, const matrix3x2<T>& m2) {
    return matrix3x2<T>(
                m1.a * m2.a + m1.b * m2.c,
                m1.a * m2.b + m1.b * m2.d,
                m1.c * m2.a + m1.d * m2.c,
                m1.c * m2.b + m1.d * m2.d,
                m1.e * m2.a + m1.f * m2.c + m2.e,
                m1.e * m2.b + m1.f * m2.d + m2.f );
}

template <typename T, typename F>
BOOST_FORCEINLINE
point<F> operator*(point<T> const& p, matrix3x2<F> const& m)
{
    return { m.a*p.x + m.c*p.y + m.e, m.b*p.x + m.d*p.y + m.f };
}

////////////////////////////////////////////////////////////////////////////////////////
/// Define affine mapping that transforms the source coordinates by the affine transformation
////////////////////////////////////////////////////////////////////////////////////////
/*
template <typename MapFn>
concept MappingFunctionConcept {
    typename mapping_traits<MapFn>::result_type;   where PointNDConcept<result_type>;

    template <typename Domain> { where PointNDConcept<Domain> }
    result_type transform(MapFn&, const Domain& src);
};
*/

template <typename T> struct mapping_traits;

template <typename F>
struct mapping_traits<matrix3x2<F>>
{
    using result_type =  point<F>;
};

template <typename F, typename F2>
BOOST_FORCEINLINE
point<F> transform(matrix3x2<F> const& mat, point<F2> const& src)
{
    return src * mat;
}

}} // namespace boost::gil

#endif

/* affine.hpp
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
*/