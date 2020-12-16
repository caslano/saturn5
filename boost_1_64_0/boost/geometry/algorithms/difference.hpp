// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace difference
{

/*!
\brief_calc2{difference} \brief_strategy
\ingroup difference
\details \details_calc2{difference_insert, spatial set theoretic difference}
    \brief_strategy. \details_inserter{difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator output iterator
\tparam Strategy \tparam_strategy_overlay
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{difference}
\param strategy \param_strategy{difference}
\return \return_out

\qbk{distinguish,with strategy}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator difference_insert(Geometry1 const& geometry1,
                                        Geometry2 const& geometry2,
                                        OutputIterator out,
                                        Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();
    concepts::check<GeometryOut>();

    typedef typename geometry::rescale_overlay_policy_type
        <
            Geometry1,
            Geometry2,
            typename Strategy::cs_tag
        >::type rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                geometry1, geometry2, strategy);

    return geometry::dispatch::intersection_insert
        <
            Geometry1, Geometry2,
            GeometryOut,
            overlay_difference,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
        >::apply(geometry1, geometry2, robust_policy, out, strategy);
}

/*!
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference_insert, spatial set theoretic difference}.
    \details_insert{difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator output iterator
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{difference}
\return \return_out

\qbk{[include reference/algorithms/difference_insert.qbk]}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator difference_insert(Geometry1 const& geometry1,
                                        Geometry2 const& geometry2,
                                        OutputIterator out)
{
    typedef typename strategy::relate::services::default_strategy
        <
            Geometry1,
            Geometry2
        >::type strategy_type;

    return difference_insert<GeometryOut>(geometry1, geometry2, out,
                                          strategy_type());
}


}} // namespace detail::difference
#endif // DOXYGEN_NO_DETAIL


namespace resolve_strategy {

struct difference
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename Collection,
        typename Strategy
    >
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        typedef typename boost::range_value<Collection>::type geometry_out;

        detail::difference::difference_insert<geometry_out>(
            geometry1, geometry2,
            range::back_inserter(output_collection),
            strategy);
    }

    template
    <
        typename Geometry1,
        typename Geometry2,
        typename Collection
    >
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             default_strategy)
    {
        typedef typename boost::range_value<Collection>::type geometry_out;
        
        detail::difference::difference_insert<geometry_out>(
            geometry1, geometry2,
            range::back_inserter(output_collection));
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct difference
{
    template <typename Collection, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection& output_collection,
                             Strategy const& strategy)
    {
        resolve_strategy::difference::apply(geometry1, geometry2,
                                            output_collection,
                                            strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct difference<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Geometry2 const& m_geometry2;
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Geometry2 const& geometry2,
                Collection& output_collection,
                Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1>
        void operator()(Geometry1 const& geometry1) const
        {
            difference
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, m_geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(geometry2,
                                                           output_collection,
                                                           strategy),
                             geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct difference<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Geometry1 const& m_geometry1;
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Geometry1 const& geometry1,
                Collection& output_collection,
                Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry2>
        void operator()(Geometry2 const& geometry2) const
        {
            difference
                <
                    Geometry1,
                    Geometry2
                >::apply(m_geometry1, geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(Geometry1 const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(geometry1,
                                                           output_collection,
                                                           strategy),
                             geometry2);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct difference<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Collection& output_collection, Strategy const& strategy)
            : m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1, typename Geometry2>
        void operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            difference
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(output_collection,
                                                           strategy),
                             geometry1, geometry2);
    }
};
    
} // namespace resolve_variant


/*!
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference, spatial set theoretic difference}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection \tparam_output_collection
\tparam Strategy \tparam_strategy{Difference}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection
\param strategy \param_strategy{difference}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection,
    typename Strategy
>
inline void difference(Geometry1 const& geometry1,
                       Geometry2 const& geometry2,
                       Collection& output_collection,
                       Strategy const& strategy)
{
    resolve_variant::difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, strategy);
}


/*!
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference, spatial set theoretic difference}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection \tparam_output_collection
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection

\qbk{[include reference/algorithms/difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void difference(Geometry1 const& geometry1,
                       Geometry2 const& geometry2,
                       Collection& output_collection)
{
    resolve_variant::difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP

/* difference.hpp
GfqSoEzyTpakTPJOlmwol1pnuXui0sEGWRYtQ8s0WLbBcpVJjsjyDVZosGJlt3Pkv6IELNSybJHcO5GVKpNYk5WDDbYk9JUxkFUarEqZPEsgq1Em93hklledDcdgBdPt2QzmpUxiRmYH033xrbMvUYsDwYbQPayMjyxYmdRJFqoM6wxT1udib89ao2eVYEPVvW8kmrq/jQYbpp7TxqCpcnHK8L4xQRnu5Ulg96m9PBlN7eWpaGovT1eG7WUa2ss2tJdraC9fGcylhEKw4Za5/tIeWbEyaY+sRJm0R1aqDJ8vlYONVDmqNFiVs8F7kOdbasBG4ftGySy7nU3GR2ZVJnOezIaG85PMC031xW4wX4MFGvoZbLBQg4WhYTzJwpVJjsgiDeWiDXGJMfQlzlBngqHOJEPMkg3lUg3tpRvKZSqTZ5Vk2XXazOW5YKNpzcE6WpEPNob2XbRCZVInWTGa2udLlMnnYclKlflO3/QkW7mhXKUyOduQVSnDZ7g1YGNpn8dn6ZY9t22cxfk1IivY/eo5tM1gXsrkekRxt5PZblk47XXy+hGdFYOg3Hinc2tAYAjYA3RekvcSkw1TJu9FJRujTOYSWQSZO1jT/MIbbLOwnDoPxhosXpm8n4EsUZk8byVbZ7AUw/jSlEneyTKUSd7JspTdP+hoCFuOshezXpEx5JF5gG2vKj3DdkqVk9ffyc4qk32CrAwNz+V0xqwAm0BnTBk72RU0dTatJrOByecDyKzZzuXk2khmA9N1ehnK2Q3lfJXJ675kgcpkvpAFK4Nr+IpQsAg6Q0tcyMKU4b4UTmYDa7Sr8ydsswzlYpXhuTXeYImqvXll061sqcpCrgyJZ8tSdeJ5PkfZ6OufR7LlKds26FVftgJlct4lKzKUOwU2kfZWjPVZZbIvkZUpez1mbBu2CmXyOSmyK8rw3qla2ZKJHRax3VSG91Wue51NXhskc1cmr6uReSjbFfhyBZs3mQ1s0d7kcrZAKKfHHqwMX1MMBZtE1yrZQ8jClMnnesjClcm1gyySzAbWfsEbd7HFqnKe/hVT+ToWDzZZfb4jEU29DrvOYClo+rVdQ7kMZbbVfxSwZaGpz+DkGCwPTX3GqAAsUo29CE1938wpNPV+vrNoauxlaOr+rwJNvUfpCpoaX7XBbqLh2OmM4rrvtj1IZxTJA5m7MhkfmQeaum/0RlP3fz7K5PpA5qdMxkAWhKbuN0OUyfjo/m8Y2EN0/ydjIBtjsAhleJ8ahabuN2cpk/GRxSq73c/l8+LBptB5UOYgWSKZDSz4/egNtTZ7ZSqUi7IsX4rn+XSwqerZU6bBspXJe1zIcpXJa/pk+crkNW+yQoMVG/pSogzvSUqVydwlKzdYpcGqlOG1o0aZ5I/Mst/Z5L3gZFZlspeT2cB0nV7KZC6R2ZXh/ZEvmI5ZoMGClcn7yMhCDe2FgenchoPp3EYaLFoZzusYsGnqzBCnTO4tyBKUYXtJyuTMTpaMpq7hqWDTLcscZ3a2dGV4n5qpTPYesmyD5SqTPJDlK5P3C5MVGvpSbLASZfL+SLJSQ7lyZRJPskplTs/WwKLVtbhGGZaz5NRtVjR1bbShqfeReaGpM4rdUM7XUC4QTb0PMNjQz1CDhaGpM0o4mvqcRqQyPGdFo6nzS4xh7HHK8H1PCYZySYaYJaOp7xFMrbPcw5Z0sBmWZY65xJapTOJJlq1M1h9ZrsHylcnaJCtUNnlwx/fYig19KTFYqTJ5PZWsXJmsW7JKQ51VymTdktU4G6wx+hOBr922mRZ/R6zZrMrkXpTMpkzuDcm8lEluyexkNrCX/Y4ksAWpcpIHshBlW7/Oucw2TJnEhWyMwSKUYVw=
*/