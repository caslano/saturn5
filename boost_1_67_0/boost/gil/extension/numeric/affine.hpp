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