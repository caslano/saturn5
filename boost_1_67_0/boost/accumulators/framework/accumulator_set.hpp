///////////////////////////////////////////////////////////////////////////////
// accumulator_set.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_SET_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_SET_HPP_EAN_28_10_2005

#include <boost/version.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/parameter/is_argument_pack.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_concept.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/accumulators/droppable_accumulator.hpp>
#include <boost/fusion/include/any.hpp>
#include <boost/fusion/include/find_if.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/filter_view.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // accumulator_visitor
    //   wrap a boost::parameter argument pack in a Fusion extractor object
    template<typename Args>
    struct accumulator_visitor
    {
        explicit accumulator_visitor(Args const &a)
          : args(a)
        {
        }

        template<typename Accumulator>
        void operator ()(Accumulator &accumulator) const
        {
            accumulator(this->args);
        }

    private:
        accumulator_visitor &operator =(accumulator_visitor const &);
        Args const &args;
    };

    template<typename Args>
    inline accumulator_visitor<Args> const make_accumulator_visitor(Args const &args)
    {
        return accumulator_visitor<Args>(args);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // accumulator_set_base
    struct accumulator_set_base
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_accumulator_set
    template<typename T>
    struct is_accumulator_set
      : mpl::if_<
            boost::is_base_of<
                accumulator_set_base
              , typename boost::remove_const<
                    typename boost::remove_reference<T>::type
                >::type
            >
          , mpl::true_
          , mpl::false_
        >::type
    {
    };

    // function object that serialize an accumulator
    template<typename Archive>
    struct serialize_accumulator
    {
        serialize_accumulator(Archive & _ar, const unsigned int _file_version) :
            ar(_ar), file_version(_file_version)
        {}

        template<typename Accumulator>
        void operator ()(Accumulator &accumulator)
        {
            accumulator.serialize(ar, file_version);
        }

    private:
        Archive& ar;
        const unsigned int file_version;
    };

} // namespace detail

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4355) // warning C4355: 'this' : used in base member initializer list
#endif

///////////////////////////////////////////////////////////////////////////////
/// \brief A set of accumulators.
///
/// accumulator_set resolves the dependencies between features and ensures that
/// the accumulators in the set are updated in the proper order.
///
/// acccumulator_set provides a general mechanism to visit the accumulators
/// in the set in order, with or without a filter. You can also fetch a reference
/// to an accumulator that corresponds to a feature.
///
template<typename Sample, typename Features, typename Weight>
struct accumulator_set
  : detail::accumulator_set_base
{
    typedef Sample sample_type;     ///< The type of the samples that will be accumulated
    typedef Features features_type; ///< An MPL sequence of the features that should be accumulated.
    typedef Weight weight_type;     ///< The type of the weight parameter. Must be a scalar. Defaults to void.

    /// INTERNAL ONLY
    ///
    typedef
        typename detail::make_accumulator_tuple<
            Features
          , Sample
          , Weight
        >::type
    accumulators_mpl_vector;

    // generate a fusion::list of accumulators
    /// INTERNAL ONLY
    ///
    typedef
        typename detail::meta::make_acc_list<
            accumulators_mpl_vector
        >::type
    accumulators_type;

    /// INTERNAL ONLY
    ///
    //BOOST_MPL_ASSERT((mpl::is_sequence<accumulators_type>));

    ///////////////////////////////////////////////////////////////////////////////
    /// default-construct all contained accumulators
    accumulator_set()
      : accumulators(
            detail::make_acc_list(
                accumulators_mpl_vector()
              , (boost::accumulators::accumulator = *this)
            )
        )
    {
        // Add-ref the Features that the user has specified
        this->template visit_if<detail::contains_feature_of_<Features> >(
            detail::make_add_ref_visitor(boost::accumulators::accumulator = *this)
        );
    }

    /// \overload
    ///
    /// \param a1 Optional named parameter to be passed to all the accumulators
    template<typename A1>
    explicit accumulator_set(
        A1 const &a1
      , typename boost::enable_if<
            parameter::is_argument_pack<A1>
          , detail::_enabler
        >::type = detail::_enabler()
    ) : accumulators(
            detail::make_acc_list(
                accumulators_mpl_vector()
              , (boost::accumulators::accumulator = *this, a1)
            )
        )
    {
        // Add-ref the Features that the user has specified
        this->template visit_if<detail::contains_feature_of_<Features> >(
            detail::make_add_ref_visitor(boost::accumulators::accumulator = *this)
        );
    }

    /// \overload
    ///
    /// \param a1 Optional sample parameter to be passed to all the accumulators
    template<typename A1>
    explicit accumulator_set(
        A1 const &a1
      , typename boost::disable_if<
            parameter::is_argument_pack<A1>
          , detail::_enabler
        >::type = detail::_enabler()
    ) : accumulators(
            detail::make_acc_list(
                accumulators_mpl_vector()
              , (
                    boost::accumulators::accumulator = *this
                  , boost::accumulators::sample = a1
                )
            )
        )
    {
        // Add-ref the Features that the user has specified
        this->template visit_if<detail::contains_feature_of_<Features> >(
            detail::make_add_ref_visitor(boost::accumulators::accumulator = *this)
        );
    }

    // ... other overloads generated by Boost.Preprocessor:

    /// INTERNAL ONLY
    ///
#define BOOST_ACCUMULATORS_ACCUMULATOR_SET_CTOR(z, n, _)                                \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                  \
    accumulator_set(                                                                    \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)                                \
      , typename boost::enable_if<                                                      \
            parameter::is_argument_pack<A0>                                             \
          , detail::_enabler                                                            \
        >::type = detail::_enabler()                                                    \
    ) : accumulators(                                                                   \
            detail::make_acc_list(                                                      \
                accumulators_mpl_vector()                                               \
              , (                                                                       \
                    boost::accumulators::accumulator = *this                            \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, a)                            \
                )                                                                       \
            )                                                                           \
        )                                                                               \
    {                                                                                   \
        /* Add-ref the Features that the user has specified */                          \
        this->template visit_if<detail::contains_feature_of_<Features> >(               \
            detail::make_add_ref_visitor(boost::accumulators::accumulator = *this)      \
        );                                                                              \
    }                                                                                   \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                  \
    accumulator_set(                                                                    \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)                                \
      , typename boost::disable_if<                                                     \
            parameter::is_argument_pack<A0>                                             \
          , detail::_enabler                                                            \
        >::type = detail::_enabler()                                                    \
    ) : accumulators(                                                                   \
            detail::make_acc_list(                                                      \
                accumulators_mpl_vector()                                               \
              , (                                                                       \
                    boost::accumulators::accumulator = *this                            \
                  , boost::accumulators::sample = BOOST_PP_ENUM_PARAMS_Z(z, n, a)       \
                )                                                                       \
            )                                                                           \
        )                                                                               \
    {                                                                                   \
        /* Add-ref the Features that the user has specified */                          \
        this->template visit_if<detail::contains_feature_of_<Features> >(               \
            detail::make_add_ref_visitor(boost::accumulators::accumulator = *this)      \
        );                                                                              \
    }

    /// INTERNAL ONLY
    ///
    BOOST_PP_REPEAT_FROM_TO(
        2
      , BOOST_PP_INC(BOOST_ACCUMULATORS_MAX_ARGS)
      , BOOST_ACCUMULATORS_ACCUMULATOR_SET_CTOR
      , _
    )

    #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
    /// \overload
    ///
    template<typename A1, typename A2, ...>
    accumulator_set(A1 const &a1, A2 const &a2, ...);
    #endif

    // ... other overloads generated by Boost.Preprocessor below ...

    ///////////////////////////////////////////////////////////////////////////////
    /// Visitation
    /// \param func UnaryFunction which is invoked with each accumulator in turn.
    template<typename UnaryFunction>
    void visit(UnaryFunction const &func)
    {
        fusion::for_each(this->accumulators, func);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// Conditional visitation
    /// \param func UnaryFunction which is invoked with each accumulator in turn,
    ///     provided the accumulator satisfies the MPL predicate FilterPred.
    template<typename FilterPred, typename UnaryFunction>
    void visit_if(UnaryFunction const &func)
    {
        fusion::filter_view<accumulators_type, FilterPred> filtered_accs(this->accumulators);
        fusion::for_each(filtered_accs, func);
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// The return type of the operator() overloads is void.
    typedef void result_type;

    ///////////////////////////////////////////////////////////////////////////////
    /// Accumulation
    /// \param a1 Optional named parameter to be passed to all the accumulators
    void operator ()()
    {
        this->visit(
            detail::make_accumulator_visitor(
                boost::accumulators::accumulator = *this
            )
        );
    }

    // ... other overloads generated by Boost.Preprocessor:

    /// INTERNAL ONLY
    ///
#define BOOST_ACCUMULATORS_ACCUMULATOR_SET_FUN_OP(z, n, _)                              \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                  \
    void operator ()(                                                                   \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)                                \
      , typename boost::enable_if<                                                      \
            parameter::is_argument_pack<A0>                                             \
          , detail::_enabler                                                            \
        >::type = detail::_enabler()                                                    \
    )                                                                                   \
    {                                                                                   \
        this->visit(                                                                    \
            detail::make_accumulator_visitor(                                           \
                (                                                                       \
                    boost::accumulators::accumulator = *this                            \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, a)                            \
                )                                                                       \
            )                                                                           \
        );                                                                              \
    }                                                                                   \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                  \
    void operator ()(                                                                   \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)                                \
      , typename boost::disable_if<                                                     \
            parameter::is_argument_pack<A0>                                             \
          , detail::_enabler                                                            \
        >::type = detail::_enabler()                                                    \
    )                                                                                   \
    {                                                                                   \
        this->visit(                                                                    \
            detail::make_accumulator_visitor(                                           \
                (                                                                       \
                    boost::accumulators::accumulator = *this                            \
                  , boost::accumulators::sample = BOOST_PP_ENUM_PARAMS_Z(z, n, a)       \
                )                                                                       \
            )                                                                           \
        );                                                                              \
    }

    /// INTERNAL ONLY
    ///
    BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_PP_INC(BOOST_ACCUMULATORS_MAX_ARGS)
      , BOOST_ACCUMULATORS_ACCUMULATOR_SET_FUN_OP
      , _
    )

    #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
    /// \overload
    ///
    template<typename A1, typename A2, ...>
    void operator ()(A1 const &a1, A2 const &a2, ...);
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// Extraction
    template<typename Feature>
    struct apply
      : fusion::result_of::value_of<
            typename fusion::result_of::find_if<
                accumulators_type
              , detail::matches_feature<Feature>
            >::type
        >
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// Extraction
    template<typename Feature>
    typename apply<Feature>::type &extract()
    {
        return *fusion::find_if<detail::matches_feature<Feature> >(this->accumulators);
    }

    /// \overload
    template<typename Feature>
    typename apply<Feature>::type const &extract() const
    {
        return *fusion::find_if<detail::matches_feature<Feature> >(this->accumulators);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// Drop
    template<typename Feature>
    void drop()
    {
        // You can only drop the features that you have specified explicitly
        typedef typename apply<Feature>::type the_accumulator;
        BOOST_MPL_ASSERT((detail::contains_feature_of<Features, the_accumulator>));

        typedef
            typename feature_of<typename as_feature<Feature>::type>::type
        the_feature;

        (*fusion::find_if<detail::matches_feature<Feature> >(this->accumulators))
            .drop(boost::accumulators::accumulator = *this);

        // Also drop accumulators that this feature depends on
        typedef typename the_feature::dependencies dependencies;
        this->template visit_if<detail::contains_feature_of_<dependencies> >(
            detail::make_drop_visitor(boost::accumulators::accumulator = *this)
        );
    }

    // make the accumulator set serializeable
    template<class Archive>
    void serialize(Archive & ar, const unsigned int file_version)
    {
        detail::serialize_accumulator<Archive> serializer(ar, file_version);
        fusion::for_each(this->accumulators, serializer);
    }

private:

    accumulators_type accumulators;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

///////////////////////////////////////////////////////////////////////////////
// find_accumulator
//   find an accumulator in an accumulator_set corresponding to a feature
template<typename Feature, typename AccumulatorSet>
typename mpl::apply<AccumulatorSet, Feature>::type &
find_accumulator(AccumulatorSet &acc BOOST_ACCUMULATORS_PROTO_DISABLE_IF_IS_CONST(AccumulatorSet))
{
    return acc.template extract<Feature>();
}

/// \overload
template<typename Feature, typename AccumulatorSet>
typename mpl::apply<AccumulatorSet, Feature>::type const &
find_accumulator(AccumulatorSet const &acc)
{
    return acc.template extract<Feature>();
}

template<typename Feature, typename AccumulatorSet>
typename mpl::apply<AccumulatorSet, Feature>::type::result_type
extract_result(AccumulatorSet const &acc)
{
    return find_accumulator<Feature>(acc).result(
        boost::accumulators::accumulator = acc
    );
}

///////////////////////////////////////////////////////////////////////////////
// extract_result
//   extract a result from an accumulator set
/// INTERNAL ONLY
///
#define BOOST_ACCUMULATORS_EXTRACT_RESULT_FUN(z, n, _)                      \
    template<                                                               \
        typename Feature                                                    \
      , typename AccumulatorSet                                             \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename A)                   \
    >                                                                       \
    typename mpl::apply<AccumulatorSet, Feature>::type::result_type         \
    extract_result(                                                         \
        AccumulatorSet const &acc                                           \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, A, const &a)           \
      , typename boost::enable_if<                                          \
            parameter::is_argument_pack<A0>                                 \
          , detail::_enabler                                                \
        >::type                                                             \
    )                                                                       \
    {                                                                       \
        return find_accumulator<Feature>(acc).result(                       \
            (                                                               \
                boost::accumulators::accumulator = acc                      \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, a)                    \
            )                                                               \
        );                                                                  \
    }                                                                       \
    template<                                                               \
        typename Feature                                                    \
      , typename AccumulatorSet                                             \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename A)                   \
    >                                                                       \
    typename mpl::apply<AccumulatorSet, Feature>::type::result_type         \
    extract_result(                                                         \
        AccumulatorSet const &acc                                           \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, A, const &a)           \
      , typename boost::disable_if<                                         \
            parameter::is_argument_pack<A0>                                 \
          , detail::_enabler                                                \
        >::type                                                             \
    )                                                                       \
    {                                                                       \
        return find_accumulator<Feature>(acc).result((                      \
            boost::accumulators::accumulator = acc                          \
          , boost::accumulators::sample = BOOST_PP_ENUM_PARAMS_Z(z, n, a)   \
        ));                                                                 \
    }

BOOST_PP_REPEAT_FROM_TO(
    1
  , BOOST_PP_INC(BOOST_ACCUMULATORS_MAX_ARGS)
  , BOOST_ACCUMULATORS_EXTRACT_RESULT_FUN
  , _
)

}} // namespace boost::accumulators

#endif

/* accumulator_set.hpp
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
*/