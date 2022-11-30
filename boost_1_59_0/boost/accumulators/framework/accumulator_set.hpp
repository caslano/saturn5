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
IKhuF0QQaDMZ6rJ9TP38UGKdybaxwigu69rjL76Ft1lQegMGjuVku+WxK2Khpq1CTrYAKfp3LrpGTznEbTnqGKDSjzQLVNMLPODCLPyC1HEvN3DWpwLFzzu04jy4n5ss0qlvuipT21MQ6rE/JaNEYHe9BUsVe6pB6qksEMRpkxnFPFDw4Se/D2Y59xPGBEYySfSwxuswh+H2EJVol/NTWJ3dfSZOBq1m/LDrfG3WLLIl/YsgJ1sCKuZvpNeCafbc35LuAr8Xq1zX4SDcTGbteQZZNuDlxbVs/oJaznaILNTlxhj2jO4uIdmEXJapKcqEnbus4ohOvmQyVnMdhufH3+JQKuUjcLKAlciPkOuY93gb+xo0bmn1n448iG0o/me+Zdfd5wx4+8ehVsfTSxpS6K4ABlYPjgMkRJx+J8cwANVn7S0VzLCyrxQ7uFvCOOPE4M7sMT15FAMbwXImJXMPvX4Qg80keCwgMO8bqd+TsPyEgrGi0Qg8D5T4hNVADKwPbgXMsXASayrHs3rL5HR/Ql8btEtob4bbM8NTGeIdGsiQrVOhOZ2+iF0/woTBgWLXOMSxpVnTefq8dfmMu3HSERk/90q81k9vdUkgr4sk4mMM0K1LFnBN8PTOaiIjKOkZuFNh3NFy5OYcbRF2aZzmhGOkqHRjWyEQgf9aanPfD0rkNvM2uCo9V93s5Otk8LjtYJSm+3RFYs7QWznG3t2VW90+a6MmbD40ucpm38w3i6ecIoKlohanq5YWEtg/ydVR8ezCQbIArE0AOIO5ouljeZmv2lZVxnjWMautKlgyTXpTBKkCcfIBX9vSdMwrSuCQM0k7//fWqpboVkFDXqnTlrjOT5TnLXxyYf3O9d7f7Vej+PBkyLvT9+10rRjDmvsklxWEy3hXYY7qPRGv1C/hBsLgf0FToAuXIjrf6xdc//7wFrBEWrkhpnMaHwdJ6BjlPQAhediAPIEAPUnhCPJjjHwf8u2haMlbk4QIsyHJzgd7/Q3AoHEEHDJOiBKwOgC/YiG8QjSrzk5Ngf8irnOxw035RtVwVSTRrcYH+4Pa+6jG3Pvq4tu7YPg1O34D6CIo4Y6ntGZp2IdLnXFmCCCpl+MLT6m7WhbQt5FaF+XdouyzrfHN7lLOA9lKZypYitTeqmJokr3vajo5C8ghzmsJIwjl5Md8+I+dBdu8//H/uS0xYWUEQnshgzGPBLSeY0FdsB64I7lV86FxuBVrzGR02iwtTNiPKnAWZQHq6OwXM4qpnl5s2cXJzOfdzCkGtAAebggiUnnFAYBqBHLEyt8uISzd10xsrOauZlmt3Wu99Nvt0s03PhWlXKVhvwxQ+3r1i+MWEx4Fgm8ONDyB3LW0NP44iNITSX4MFzyYGv8YTmx5tlQM+qG9FpAq+iiC3aYIFJnhPPjQNk/+dMIFayYX6qqodjKeP1nMWjaSCCP5DfR+sm4MOTZc6TRR1bFa48u5ZYtkeAklkWdz99E8eOcUOeHLTGSAsUciuPBv1DpqD7XYoo6CDdhYUyrPtkWuQyJGKME1Vl1uLyQ3kG4+uV5f1Kc9aAOrtUQTqtE0urpNgk2rlq/WHNwOuDxtfPPwAtccYD8VC8sV6zcq8ev5TR7bmp2UHwkO9TU0TLd1Wn1FV0D7TwdWLCfYme25XAd+LnO2QLA1vXfvfHcU4xDk9ecnLBqdvICtFSNRsTCkhF7oAQPNJgv9adhzY9MpRSVD2YI/dB9DpZ6IzI9Nvv2HCxSFBIhkFwUXFOLwa20QNcV3DFRVg443Kkw4Ih1P15CmTc/mWOq2jqJX0eVHy0MaAuNInW3IWbTx950+flUzM/bBc+OaF3PVq7BYeNeQsmIRDZVa6XZ6MiMq+O3S0CSMa4pmG6YW6+V5K66C4oosKBAObCH58PUlKcdYcbzzRrDRLadKLraZxzJ6FpbcEZdbsqGDh9MtZMwy1YmmP6E71ehEsExLrnx+EjUm/bWKzXRkQleIf8DGaebmouRP5K6y3xljj/sjYi24j8MquGvt2TWgUqN+2F4+7XL0O2+63Jik37i/LnfxeHgnHCQ/ADYTQKfEgPfTyh+kLw4voZRtDYHKWK3XBYCFJDAF5T0P55KH77EZbqhazVbpqzP9e+Mg2d4LQvinCbqaPM+GUu64l/V2tdf/BJBQXNyKbC/BrT9QM6gEEc8dopxwNPRKhY7e/cP+SY2pRdcgcb7tK1WjadRIpMZSbWK0DfBBJnVjWgR+R3KtmEKIhfCWP5yaNAhBu9vgzR6fKW5woGonbNL4TQeB3YIPmZ7IVstFuI/PHipGsoYQdM59KJBuEIYMF4BezY/bByguHUU7413Zo6e9aMLaFeb3AIfvwX47uKMiC//eNkUWjjSFWxGV+Y3UcBcKBFXhucxZtZcQ/DtuyU69TuZ0difgAvFyUOf5m9/FhGYEKaADTdSTfd45qnx5D1KPNs9IdQNRYZWU7jgwgMfqNAO5fLjUm5K5csWFAuYsmrR7fkW+kljpi5UdiERw79jMOFwwqyTxrrZHRSQBzMyL2Bkj+nqlKIjMCsvN4OLmSTCZJik0+cNBXKqKqAHc/yMlSemvQ6b5UHnnpnAAUP3h0QH0+XFFFfYdyhxx2+++w8yC05qEkjwIqq65sx4ivhIZZOELzz/Ld59soFGg+ItovQGNrNHLeK0BoZTkDcLUILbUuaYtM0OsQNV7IymFv16DUeA2KWULNoLFFyYqfGEpvN1mV+WCDu3fkKCQQbvEwShYngOZA1c7YcmwGh72EsTag/vHb7OyDm+OYP9JDGnThM6dPg6xI9wRMD20L+zG5SjN+jMfpWdqJZG9QAI3wdZy+VZc7+I2fl+5zwU/6PbxpQVgUu8vc7pOrY4gJKlNoEi41/W2CcxUTHz7sz4JTw2k/NxcUkQ3BfUU1cH+Y0hW9FzPMmLFLsozVQuXpVIK6ORZozsMeCEM+2KZsxZ1F7DBghYVOXwB11OGVMhWc4J7GYdaj4SMSSnBh9ZDWhTCfL/QSR2fSoGkCZOOZFC9Jpu9YtlXatJP4mKRsrZ1nFKTR7YGirStSlsDRfIUOCpKUfcvra3jZqMFjOVBQRG1X3Ru2NHjFQ6Lf6dsqsNoyors7UNKA5cuMPLhm1/2M/X7HYCLks3BDz4TeKT5TbEY7NC2TtyXEWhRohXEOCFTWkUrWKzLQtsVI/Ex+gau+Be/CuLVQp8GVqgEPyrc0Zwqa91wgpZi3uND+ptGLSN4aPsw34f25+jHiV2HIcQKFt99t3smMOHEF3dxzmMxfkGEGmOs9h0n7E4qpZhhC+9wVP6cJcei9q7OlmQGTrDz3/+qxiyA61iWNH3EzMzMdMQMFjMzWMzMbDEzM4OFFku22JIli5mZmS3Gle+j+968idmI3Z2J7Y5zojOru7q6KvOrv2rWui7hiCt2Yx9aKRCt7ZHiw6fy06r97IdeioloUuYB584RhQpUOipjJQ1Yxcl+AkSWlG44F0eEy1h5ZeWI0Esoetj0kwwmVnzMXliGDfwFPCagURXP2GFToqRwCub+GQYzxCvHHRXRrS+KrJoFTkWw1i3nrCg/Jx+uGRxR/StydWQMkSi10Bp/ZpaDn9HHIm+Rhv5SIDgkVkvsUcUQO3a//8VrLtpSmb6Ji4Zc+cw1n6HazLCA8qge2dCTPeR9LaypP3KDUxtY/rMNlXALEO48z/4ihkyROOriWZx76DOjb1AQHjmeB0PsCnv56nBxwtY2QGKnrJCZZWnwWTcwsfx6nUN4rrf3rBhZAK3ZRBp3KfXr8hh+CYGXfQ/B8p4XLM7beGdXKpGTgcHnuCNkYFbYyuw8bo3FYpnOwEr3F7SbQPPAYLZFE+TPQ2Hl3eotPgN1yXmHqoVH6D8C08GemhUccBN9JoaTTZ/5ydBZCEUVWxRDyn8IzsiHVOwUCllTouPlPMbFz0fotFUiur1J7D/nBiwSJy1cfHdtkMeeM0itH/Nt/3b1Rh1qzZ5FVB9h44/1yJlVpt42OOmeF4m89wW3Zvg6fOgGyT2yEbu/qma9gmxhMuemZZkpbYApYib7vgPZWaN9+ks2VolB8QsN68rM7sij8rlFq0IvDg6xDzPmEpmMo+H2SlbZM+8PlZdGgy1+hJ4OPAZFPHC9qBInjP0HvrTMCn9+Di3e0lf+El97bRT14bY3X9vDzpGdS12niKp3vSqXnifRAfGTEdqfobed+lfSLgK6Bf4WeE2mKT3lj1xiU0itLTh+6w6UKh2r+dE22Z/jfp+iq9ed3FgIodui6+IR8aZOKZE/I4h0GH+16asvZZjlgJeg27WP7lKfvrrQhpT6lDmqVCrXJoilPK25FH5IZBuuoIFRfikmivF6osTDAJ08rhSGSqYNQqEw0WT/ys82Q6OVeh3jvriTIXPGp39eO0Ty4gJM0tbU3Uu+6T126iRKWlS70rSxu9K+ri7b2F/u7h4uC78wH0FZMabU2M1VMWvU3C6K8cahwihN4M0otn5bRPe0sZAlTaJsyWdzgUGwg50LrOZxVD9LvQfvLxzTu1fkn/AzxVeP/qlJlZIiiAyK/ObZLjbi5cgxiaZVq19ly+eq/Un2CetLLHGD9+oXVonbgUzfrxbUEeJlD1gknBTTplybVICZQ8h8rm0+dyDQNxg9KEVixCQkCq7aHhbff34xm2d7SpouFQoAal84PAJGdf/9vNfaEiTR6cdyTZFjWn+Zz1RtEYTH3RGdLzU0WQQdd+yA6d2DI3PIMEYU/lWsAwc3DHxdRi1iEPjuIuGWDKaYh5Go7bpEbnnkJ6ptjytOxD0qVKKVZ2nv2/gqzytRlgDlkW6FJkCNLcEUW8/2jLExVEWYDTeVI3b4aODMJI3iLVPMkQ6FBZvLFogetKrScCpBst7rflkbj10YkUNcLw3I6KW/8rqDFCSe0lR4OMlPgTm/mSE9ddxMfYs0hjmX9l0N6LW5lK6S+5/6WromSLzlpjeA12Rmb7O6gWdpnGBhSSypYWcF+Ltdr2zuT2pyUBBluavSIzhDLU8h7d9HQu6aMFE3yq2Hi3foXlVge5AmlecOfuQd7Pkpo+5wmE5KVB6SnvUsn1DNhUc+hMTY7x8tIaOqJBiPfwoZE5RVNkrm61lkJ5lTX4KePaGiu0q++IaRJXtchekBFo2qrR+2lJKxuTeh9PbzyO85qnSRtXHCnU+CILDUfH5nl+vXjF+ph1HDdra51DU9SDthtYKnSoIXuErddzSBHiGA83BRqbKB16eppWlOIkrNm8gdC0mAtKjZtYjVcwAyuWBRldDuV/HKL+jIRBHx9bqowbRabP6EZ2PopfbCF2SG3QOJ6EmQ0Gc3be7bOl7h7DMdEs+BEd2gvFbKM4L087XjKRTPPEJgN100z4NSOXyaCs8r20T9yApBeSAxNMp0XsmAyFEtgjhVhNlUA/qvyiarLfRs5OSkUzrCmmhesoQGtxptZ231oTtSnroGqZmpel9kJjVFY+iIKSpeULGZ+WL7a2iauZDSspcvRL6YTybPbB+t9dPykIHNpspKrWw3fEcJSLFlr9G4sxbz50PqHU4y+dnehJUXKMhCQ93XuhgqbkZbAD9Qox+qioDcL4hRmCb0C9OnU0uOuzo0U0j9ig+FlWUlHgwBijufEIn1cIpnplUSt8sIl4sLrWtXcSMYP5JYqFsG05OYKI3JV8muKydVDUKZOjOZ+zTrGy9LA46MgDY2SVTma9pBdI3wL/6uQkN489sPZlouJ/cTlWdWSK9q3t6DJ+j4MPRQONtbaSmZKIWJcMzf2TdWOMF1DB9aVDYMQ4X6SVGdS/aSniPKNlrerKd0iVMN3qrUKF/OjvFnIL+EWGSsA8r0XFvlsJqZsrBgsaxtaFtLdVcbTYL4hWoKNfG/lVFPi+Wj5+FOExslbUoF6ncEQEUUQJEWSph8nXOdogdw96dkfZIEUiVCapmRu1OQRXhqTuvRMuVblBXQRUJlFUjQdcV9OmFnY5Hyu+4W7V7a6YuyXdLrO3XRJZ3H753YKIOpsGTYdAg7kWqzW+Gv00rlFiPkwdKYNkGvX17G7S9wGs/G8iJgEaVVkmoSCHuYql1A4tc7O/+Q/yLXwP1MBptvcSpFzHOqFfdzW5TnBT55w9kX2m2AIiu0yaoOR94SE/NGvPhnWhSV5jWLBJT1DsA0jiKBB1oS5nQ554Yf7ifJChn98tboE7V/gmDQjE5vODnzFGij7A7yNwEfKSyJDNlXZjRzfqN7kRZGJ371ewXw9YoBiwIubwqU41OZ5ZzDUP8AbPVblSRjaNgvMde8AcxE8XJNa+vnTMOfuZz5KY5999IsUQLDilvCoaebVzdPPSyRzC1lJyqucp9IkRCoKD7GD6jmddaSfhOJvnB+adTFrjsuWC8b6sXmj+V7lWgu9/ZfzifjCzCozqChtofVzapR/RhbBrWDI/TTgpi94msy2IP01AvtvreyUNNonzskfukF/c7qKqu5bUCE0o2NrM52M3xhHKEq1WBYTV97T+/LTJ4FRk7Y95CMXRFPKn6mzjDtD8Yod0HXPLFonpttzvdngezW9pSE7DEON27Lwg1VsEKDoyyYGNhoo2ie6dhi1wI9Nda4a8hc2ZsdXZ6WfQ+UKee2MTTys9ZoVagVRMOOEI/J92YrDL0+0/2zv2yXeNzpvJ3ovib7Zw0dYe16LmYvUu1rzJFgnsOAZsJ5dJlb1DRN1OiOT0BKrqsFqyCEHjzJUHDIkLsmdhhw2gd+cWMMztaNFh9xNPvFQdm51aG/1uWCTJJsaGSKuNxSYtbqazJCsFx5enAyOZbuxLgUFyaGXdOFzXfmSIzLL51YPQonUOeLl3Gi3y42tjwWqvfgL86DjsLvnixmjnEQzdWOknGd4eiH2j5BG3KtTMYE2WB1gDOl3s2aRV8dcpH1QSLM15w/hTw1Z0OurGR2IpS70NhJZAXDn/1esep4gdsi9E5/qeZK8WVCCDerpRynIDj0YRu36/vHDwTehJ4sYXW6SIk7q/1YwaSVQXA2nSrQW1zfd8A1uhRYH4wxpw7Kb/NoMtO1cah0FTZxjbt1AEre/TSQYicCC9O77g4yzu0boaVPhKdUDwa78hZ6cntCuCfLEQe34VFWNbumM2l5bZQgazgpsrpjo0ws85ZDabA/bUp/pfGk70UvInWwrWM6KGsvDiclW91o/qzk/wHZ/pFtRW9vJJjGbDjDIlc2AL+4bvTiY9SwLK+V0HVBs15aqBD/ypDm9ERZpz/LtzcexbF0CY3VjBcAwnrokPfYLgyUnoCyyPx0qFOGmzdiZPlws69rOrhnjACHf8vsrFIx+TYY5mLVZHtLRn/Ctyw6t9Yyq+AXNhjz1vOhmUvT6jLKLHWS00v0dZFd/TuadjP4/ZBV5eolaj8rTM8+Xk3Mg/0BcXDfYn5DKJEAXltSUB/LeBwiSKPZ0xyEhSjFzwSCv1A+wQzH5zMu82PcVNvImofs+d1YpasUWJw9caxlwo6OndYsDF8TD4+7T2LMRl8RslWRMjgN0LHf8OB2sRYNckHWzIY8qNXm6AaPfX8DrEdEcxBj/0J3md9wQcjpSxmKh+MxUEBRQeg5R3TeQzawi7qRI6xTAAtdJWN+deKi0co9fzm+EeLG8IG/I+A7HVvhT6WzWs2x
*/