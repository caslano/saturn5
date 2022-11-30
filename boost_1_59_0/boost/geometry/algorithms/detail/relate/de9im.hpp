// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_DE9IM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_DE9IM_HPP

#include <tuple>

#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/core/topological_dimension.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/util/sequence.hpp>
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
            std::integer_sequence
                <
                    char, II, IB, IE, BI, BB, BE, EI, EB, EE
                >,
            3, 3
        >
{};


inline
std::tuple<mask, mask>
operator||(mask const& m1, mask const& m2)
{
    return std::tuple<mask, mask>(m1, m2);
}

template <typename ...Masks>
inline
std::tuple<Masks..., mask>
operator||(std::tuple<Masks...> const& t, mask const& m)
{
    return geometry::tuples::push_back
            <
                std::tuple<Masks...>,
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
util::type_sequence
    <
        static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1>,
        static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2>
    >
operator||(static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1> const& ,
           static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2> const& )
{
    return util::type_sequence
            <
                static_mask<II1, IB1, IE1, BI1, BB1, BE1, EI1, EB1, EE1>,
                static_mask<II2, IB2, IE2, BI2, BB2, BE2, EI2, EB2, EE2>
            >();
}

template
<
    typename ...StaticMasks,
    char II, char IB, char IE,
    char BI, char BB, char BE,
    char EI, char EB, char EE
>
inline
util::type_sequence
<
    StaticMasks...,
    static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>
>
operator||(util::type_sequence<StaticMasks...> const& ,
           static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE> const& )
{
    return util::type_sequence
            <
                StaticMasks...,
                static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>
            >();
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
    typedef util::type_sequence
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
    typedef util::type_sequence
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