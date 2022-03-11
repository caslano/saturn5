// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_DE9IM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_DE9IM_HPP

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/static_assert.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/core/topological_dimension.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/util/tuples.hpp>

namespace boost { namespace geometry
{
    
namespace de9im
{

/*!
\brief DE-9IM model intersection matrix.
\ingroup de9im
\details This matrix can be used to express spatial relations as defined in
         Dimensionally Extended 9-Intersection Model.

\qbk{[heading See also]}
\qbk{* [link geometry.reference.algorithms.relation relation]}
 */
class matrix
    : public detail::relate::matrix<3, 3>
{
#ifdef DOXYGEN_INVOKED
public:
    /*!
    \brief Initializes all of the matrix elements to F
     */
    matrix();
    /*!
    \brief Subscript operator
    \param index The index of the element
    \return The element
     */
    char operator[](std::size_t index) const;
    /*!
    \brief Returns the iterator to the first element
    \return const RandomAccessIterator
     */
    const_iterator begin() const;
    /*!
    \brief Returns the iterator past the last element
    \return const RandomAccessIterator
     */
    const_iterator end() const;
    /*!
    \brief Returns the number of elements
    \return 9
     */
    static std::size_t size();
    /*!
    \brief Returns raw pointer to elements
    \return const pointer to array of elements
     */
    inline const char * data() const;
    /*!
    \brief Returns std::string containing elements
    \return string containing elements
     */
    inline std::string str() const;
#endif
};

/*!
\brief DE-9IM model intersection mask.
\ingroup de9im
\details This mask can be used to check spatial relations as defined in
         Dimensionally Extended 9-Intersection Model.

\qbk{[heading See also]}
\qbk{* [link geometry.reference.algorithms.relate relate]}
 */
class mask
    : public detail::relate::mask<3, 3>
{
    typedef detail::relate::mask<3, 3> base_type;

public:
    /*!
    \brief The constructor.
    \param code The mask pattern.
    */
    inline explicit mask(const char* code)
        : base_type(code)
    {}
    
    /*!
    \brief The constructor.
    \param code The mask pattern.
    */
    inline explicit mask(std::string const& code)
        : base_type(code.c_str(), code.size())
    {}
};

// static_mask

/*!
\brief DE-9IM model intersection mask (static version).
\ingroup de9im
\details This mask can be used to check spatial relations as defined in
         Dimensionally Extended 9-Intersection Model.
\tparam II Interior/Interior intersection mask element
\tparam IB Interior/Boundary intersection mask element
\tparam IE Interior/Exterior intersection mask element
\tparam BI Boundary/Interior intersection mask element
\tparam BB Boundary/Boundary intersection mask element
\tparam BE Boundary/Exterior intersection mask element
\tparam EI Exterior/Interior intersection mask element
\tparam EB Exterior/Boundary intersection mask element
\tparam EE Exterior/Exterior intersection mask element

\qbk{[heading See also]}
\qbk{* [link geometry.reference.algorithms.relate relate]}
 */
template
<
    char II = '*', char IB = '*', char IE = '*',
    char BI = '*', char BB = '*', char BE = '*',
    char EI = '*', char EB = '*', char EE = '*'
>
class static_mask
    : public detail::relate::static_mask
        <
            boost::mpl::vector_c
                <
                    char, II, IB, IE, BI, BB, BE, EI, EB, EE
                >,
            3, 3
        >
{};

} // namespace de9im

namespace detail { namespace de9im
{

// a small helper util for ORing static masks

template
<
    typename Seq,
    typename T,
    bool IsSeq = boost::mpl::is_sequence<Seq>::value
>
struct push_back
{
    typedef typename boost::mpl::push_back
        <
            Seq,
            T
        >::type type;
};

template <typename Seq, typename T>
struct push_back<Seq, T, false>
{};

}} // namespace detail::de9im

namespace de9im
{

inline
boost::tuples::cons
    <
        mask,
        boost::tuples::cons<mask, boost::tuples::null_type>
    >
operator||(mask const& m1, mask const& m2)
{
    namespace bt = boost::tuples;

    return bt::cons<mask, bt::cons<mask, bt::null_type> >
        ( m1, bt::cons<mask, bt::null_type>(m2, bt::null_type()) );
}

template <typename Tail>
inline
typename geometry::tuples::push_back
    <
        boost::tuples::cons<mask, Tail>,
        mask
    >::type
operator||(boost::tuples::cons<mask, Tail> const& t, mask const& m)
{
    namespace bt = boost::tuples;

    return geometry::tuples::push_back
            <
                bt::cons<mask, Tail>,
                mask
            >::apply(t, m);
}

template
<
    char II1, char IB1, char IE1,
    char BI1, char BB1, char BE1,
    char EI1, char EB1, char EE1,
    char II2, char IB2, char IE2,
    char BI2, char BB2, char BE2,
    char EI2, char EB2, char EE2
>
inline
boost::mpl::vector<
    static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1>,
    static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2>
>
operator||(static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1> const& ,
           static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2> const& )
{
    return boost::mpl::vector
            <
                static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1>,
                static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2>
            >();
}

template
<
    typename Seq,
    char II, char IB, char IE,
    char BI, char BB, char BE,
    char EI, char EB, char EE
>
inline
typename detail::de9im::push_back
    <
        Seq,
        static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>
    >::type
operator||(Seq const& ,
           static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE> const& )
{
    return typename detail::de9im::push_back
            <
                Seq,
                static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>
            >::type();
}

} // namespace de9im


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace de9im
{

// PREDEFINED MASKS

// TODO:
// 1. specialize for simplified masks if available
// e.g. for TOUCHES use 1 mask for A/A
// 2. Think about dimensions > 2 e.g. should TOUCHES be true
// if the interior of the Areal overlaps the boundary of the Volumetric
// like it's true for Linear/Areal

// EQUALS
template <typename Geometry1, typename Geometry2>
struct static_mask_equals_type
{
    typedef geometry::de9im::static_mask<'T', '*', 'F', '*', '*', 'F', 'F', 'F', '*'> type; // wikipedia
    //typedef geometry::de9im::static_mask<'T', 'F', 'F', 'F', 'T', 'F', 'F', 'F', 'T'> type; // OGC
};

// DISJOINT
template <typename Geometry1, typename Geometry2>
struct static_mask_disjoint_type
{
    typedef geometry::de9im::static_mask<'F', 'F', '*', 'F', 'F', '*', '*', '*', '*'> type;
};

// TOUCHES - NOT P/P
template
<
    typename Geometry1,
    typename Geometry2,
    std::size_t Dim1 = geometry::topological_dimension<Geometry1>::value,
    std::size_t Dim2 = geometry::topological_dimension<Geometry2>::value
>
struct static_mask_touches_impl
{
    typedef boost::mpl::vector
        <
            geometry::de9im::static_mask<'F', 'T', '*', '*', '*', '*', '*', '*', '*'>,
            geometry::de9im::static_mask<'F', '*', '*', 'T', '*', '*', '*', '*', '*'>,
            geometry::de9im::static_mask<'F', '*', '*', '*', 'T', '*', '*', '*', '*'>
        > type;
};
// According to OGC, doesn't apply to P/P
// Using the above mask the result would be always false
template <typename Geometry1, typename Geometry2>
struct static_mask_touches_impl<Geometry1, Geometry2, 0, 0>
{
    typedef geometry::detail::relate::false_mask type;
};

template <typename Geometry1, typename Geometry2>
struct static_mask_touches_type
    : static_mask_touches_impl<Geometry1, Geometry2>
{};

// WITHIN
template <typename Geometry1, typename Geometry2>
struct static_mask_within_type
{
    typedef geometry::de9im::static_mask<'T', '*', 'F', '*', '*', 'F', '*', '*', '*'> type;
};

// COVERED_BY (non OGC)
template <typename Geometry1, typename Geometry2>
struct static_mask_covered_by_type
{
    typedef boost::mpl::vector
        <
            geometry::de9im::static_mask<'T', '*', 'F', '*', '*', 'F', '*', '*', '*'>,
            geometry::de9im::static_mask<'*', 'T', 'F', '*', '*', 'F', '*', '*', '*'>,
            geometry::de9im::static_mask<'*', '*', 'F', 'T', '*', 'F', '*', '*', '*'>,
            geometry::de9im::static_mask<'*', '*', 'F', '*', 'T', 'F', '*', '*', '*'>
        > type;
};

// CROSSES
// dim(G1) < dim(G2) - P/L P/A L/A
template
<
    typename Geometry1,
    typename Geometry2,
    std::size_t Dim1 = geometry::topological_dimension<Geometry1>::value,
    std::size_t Dim2 = geometry::topological_dimension<Geometry2>::value,
    bool D1LessD2 = (Dim1 < Dim2)
>
struct static_mask_crosses_impl
{
    typedef geometry::de9im::static_mask<'T', '*', 'T', '*', '*', '*', '*', '*', '*'> type;
};
// TODO: I'm not sure if this one below should be available!
// dim(G1) > dim(G2) - L/P A/P A/L
template
<
    typename Geometry1, typename Geometry2, std::size_t Dim1, std::size_t Dim2
>
struct static_mask_crosses_impl<Geometry1, Geometry2, Dim1, Dim2, false>
{
    typedef geometry::de9im::static_mask<'T', '*', '*', '*', '*', '*', 'T', '*', '*'> type;
};
// dim(G1) == dim(G2) - P/P A/A
template
<
    typename Geometry1, typename Geometry2, std::size_t Dim
>
struct static_mask_crosses_impl<Geometry1, Geometry2, Dim, Dim, false>
{
    typedef geometry::detail::relate::false_mask type;
};
// dim(G1) == 1 && dim(G2) == 1 - L/L
template <typename Geometry1, typename Geometry2>
struct static_mask_crosses_impl<Geometry1, Geometry2, 1, 1, false>
{
    typedef geometry::de9im::static_mask<'0', '*', '*', '*', '*', '*', '*', '*', '*'> type;
};

template <typename Geometry1, typename Geometry2>
struct static_mask_crosses_type
    : static_mask_crosses_impl<Geometry1, Geometry2>
{};

// OVERLAPS

// dim(G1) != dim(G2) - NOT P/P, L/L, A/A
template
<
    typename Geometry1,
    typename Geometry2,
    std::size_t Dim1 = geometry::topological_dimension<Geometry1>::value,
    std::size_t Dim2 = geometry::topological_dimension<Geometry2>::value
>
struct static_mask_overlaps_impl
{
    typedef geometry::detail::relate::false_mask type;
};
// dim(G1) == D && dim(G2) == D - P/P A/A
template <typename Geometry1, typename Geometry2, std::size_t Dim>
struct static_mask_overlaps_impl<Geometry1, Geometry2, Dim, Dim>
{
    typedef geometry::de9im::static_mask<'T', '*', 'T', '*', '*', '*', 'T', '*', '*'> type;
};
// dim(G1) == 1 && dim(G2) == 1 - L/L
template <typename Geometry1, typename Geometry2>
struct static_mask_overlaps_impl<Geometry1, Geometry2, 1, 1>
{
    typedef geometry::de9im::static_mask<'1', '*', 'T', '*', '*', '*', 'T', '*', '*'> type;
};

template <typename Geometry1, typename Geometry2>
struct static_mask_overlaps_type
    : static_mask_overlaps_impl<Geometry1, Geometry2>
{};

}} // namespace detail::de9im
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_DE9IM_HPP

/* de9im.hpp
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
*/