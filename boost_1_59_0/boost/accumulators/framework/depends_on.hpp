///////////////////////////////////////////////////////////////////////////////
// depends_on.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_DEPENDS_ON_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_DEPENDS_ON_HPP_EAN_28_10_2005

#include <boost/version.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/fusion/include/value_of.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/cons.hpp>

namespace boost { namespace accumulators
{
    ///////////////////////////////////////////////////////////////////////////
    // as_feature
    template<typename Feature>
    struct as_feature
    {
        typedef Feature type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // weighted_feature
    template<typename Feature>
    struct as_weighted_feature
    {
        typedef Feature type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // feature_of
    template<typename Feature>
    struct feature_of
    {
        typedef Feature type;
    };

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////////
        // feature_tag
        template<typename Accumulator>
        struct feature_tag
        {
            typedef typename Accumulator::feature_tag type;
        };

        template<typename Feature>
        struct undroppable
        {
            typedef Feature type;
        };

        template<typename Feature>
        struct undroppable<tag::droppable<Feature> >
        {
            typedef Feature type;
        };

        // For the purpose of determining whether one feature depends on another,
        // disregard whether the feature is droppable or not.
        template<typename A, typename B>
        struct is_dependent_on
          : is_base_and_derived<
                typename feature_of<typename undroppable<B>::type>::type
              , typename undroppable<A>::type
            >
        {};

        template<typename Feature>
        struct dependencies_of
        {
            typedef typename Feature::dependencies type;
        };

        // Should use mpl::insert_range, but doesn't seem to work with mpl sets
        template<typename Set, typename Range>
        struct set_insert_range
          : mpl::fold<
                Range
              , Set
              , mpl::insert<mpl::_1, mpl::_2>
            >
        {};

        template<typename Features>
        struct collect_abstract_features
          : mpl::fold<
                Features
              , mpl::set0<>
              , set_insert_range<
                    mpl::insert<mpl::_1, feature_of<mpl::_2> >
                  , collect_abstract_features<dependencies_of<mpl::_2> >
                >
            >
        {};

        template<typename Features>
        struct depends_on_base
          : mpl::inherit_linearly<
                typename mpl::sort<
                    typename mpl::copy<
                        typename collect_abstract_features<Features>::type
                      , mpl::back_inserter<mpl::vector0<> >
                    >::type
                  , is_dependent_on<mpl::_1, mpl::_2>
                >::type
                // Don't inherit multiply from a feature
              , mpl::if_<
                    is_dependent_on<mpl::_1, mpl::_2>
                  , mpl::_1
                  , mpl::inherit<mpl::_1, mpl::_2>
                >
            >::type
        {
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    /// depends_on
    template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
    struct depends_on
      : detail::depends_on_base<
            typename mpl::transform<
                mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
              , as_feature<mpl::_1>
            >::type
        >
    {
        typedef mpl::false_ is_weight_accumulator;
        typedef
            typename mpl::transform<
                mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
              , as_feature<mpl::_1>
            >::type
        dependencies;
    };

    namespace detail
    {
        template<typename Feature>
        struct matches_feature
        {
            template<typename Accumulator>
            struct apply
              : is_same<
                    typename feature_of<typename as_feature<Feature>::type>::type
                  , typename feature_of<typename as_feature<typename feature_tag<Accumulator>::type>::type>::type
                >
            {};
        };

        template<typename Features, typename Accumulator>
        struct contains_feature_of
        {
            typedef
                mpl::transform_view<Features, feature_of<as_feature<mpl::_> > >
            features_list;

            typedef
                typename feature_of<typename feature_tag<Accumulator>::type>::type
            the_feature;

            typedef
                typename mpl::contains<features_list, the_feature>::type
            type;
        };

        // This is to work around a bug in early versions of Fusion which caused
        // a compile error if contains_feature_of<List, mpl::_> is used as a
        // predicate to fusion::find_if
        template<typename Features>
        struct contains_feature_of_
        {
            template<typename Accumulator>
            struct apply
              : contains_feature_of<Features, Accumulator>
            {};
        };

        template<
            typename First
          , typename Last
          , bool is_empty = fusion::result_of::equal_to<First, Last>::value
        >
        struct build_acc_list;

        template<typename First, typename Last>
        struct build_acc_list<First, Last, true>
        {
            typedef fusion::nil_ type;

            template<typename Args>
            static fusion::nil_
            call(Args const &, First const&, Last const&)
            {
                return fusion::nil_();
            }
        };

        template<typename First, typename Last>
        struct build_acc_list<First, Last, false>
        {
            typedef
                build_acc_list<typename fusion::result_of::next<First>::type, Last>
            next_build_acc_list;

            typedef fusion::cons<
                typename fusion::result_of::value_of<First>::type
              , typename next_build_acc_list::type>
            type;

            template<typename Args>
            static type
            call(Args const &args, First const& f, Last const& l)
            {
                return type(args, next_build_acc_list::call(args, fusion::next(f), l));
            }
        };

        namespace meta
        {
            template<typename Sequence>
            struct make_acc_list
              : build_acc_list<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            {};
        }

        template<typename Sequence, typename Args>
        typename meta::make_acc_list<Sequence>::type
        make_acc_list(Sequence &seq, Args const &args)
        {
            return meta::make_acc_list<Sequence>::call(args, fusion::begin(seq), fusion::end(seq));
        }

        template<typename Sequence, typename Args>
        typename meta::make_acc_list<Sequence>::type
        make_acc_list(Sequence const &seq, Args const &args)
        {
            return meta::make_acc_list<Sequence const>::call(args, fusion::begin(seq), fusion::end(seq));
        }

        ///////////////////////////////////////////////////////////////////////////
        // checked_as_weighted_feature
        template<typename Feature>
        struct checked_as_weighted_feature
        {
            typedef typename as_feature<Feature>::type feature_type;
            typedef typename as_weighted_feature<feature_type>::type type;
            // weighted and non-weighted flavors should provide the same feature.
            BOOST_MPL_ASSERT((
                is_same<
                    typename feature_of<feature_type>::type
                  , typename feature_of<type>::type
                >
            ));
        };

        ///////////////////////////////////////////////////////////////////////////
        // as_feature_list
        template<typename Features, typename Weight>
        struct as_feature_list
          : mpl::transform_view<Features, checked_as_weighted_feature<mpl::_1> >
        {
        };

        template<typename Features>
        struct as_feature_list<Features, void>
          : mpl::transform_view<Features, as_feature<mpl::_1> >
        {
        };

        ///////////////////////////////////////////////////////////////////////////
        // accumulator_wrapper
        template<typename Accumulator, typename Feature>
        struct accumulator_wrapper
          : Accumulator
        {
            typedef Feature feature_tag;

            accumulator_wrapper(accumulator_wrapper const &that)
              : Accumulator(*static_cast<Accumulator const *>(&that))
            {
            }

            template<typename Args>
            accumulator_wrapper(Args const &args)
              : Accumulator(args)
            {
            }
        };

        ///////////////////////////////////////////////////////////////////////////
        // to_accumulator
        template<typename Feature, typename Sample, typename Weight>
        struct to_accumulator
        {
            typedef
                accumulator_wrapper<
                    typename mpl::apply2<typename Feature::impl, Sample, Weight>::type
                  , Feature
                >
            type;
        };

        template<typename Feature, typename Sample, typename Weight, typename Tag, typename AccumulatorSet>
        struct to_accumulator<Feature, Sample, tag::external<Weight, Tag, AccumulatorSet> >
        {
            BOOST_MPL_ASSERT((is_same<Tag, void>));
            BOOST_MPL_ASSERT((is_same<AccumulatorSet, void>));

            typedef
                accumulator_wrapper<
                    typename mpl::apply2<typename Feature::impl, Sample, Weight>::type
                  , Feature
                >
            accumulator_type;

            typedef
                typename mpl::if_<
                    typename Feature::is_weight_accumulator
                  , accumulator_wrapper<impl::external_impl<accumulator_type, tag::weights>, Feature>
                  , accumulator_type
                >::type
            type;
        };

        // BUGBUG work around an MPL bug wrt map insertion
        template<typename FeatureMap, typename Feature>
        struct insert_feature
          : mpl::eval_if<
                mpl::has_key<FeatureMap, typename feature_of<Feature>::type>
              , mpl::identity<FeatureMap>
              , mpl::insert<FeatureMap, mpl::pair<typename feature_of<Feature>::type, Feature> >
            >
        {
        };

        template<typename FeatureMap, typename Feature, typename Weight>
        struct insert_dependencies
          : mpl::fold<
                as_feature_list<typename Feature::dependencies, Weight>
              , FeatureMap
              , insert_dependencies<
                    insert_feature<mpl::_1, mpl::_2>
                  , mpl::_2
                  , Weight
                >
            >
        {
        };

        template<typename FeatureMap, typename Features, typename Weight>
        struct insert_sequence
          : mpl::fold< // BUGBUG should use insert_range, but doesn't seem to work for maps
                as_feature_list<Features, Weight>
              , FeatureMap
              , insert_feature<mpl::_1, mpl::_2>
            >
        {
        };

        template<typename Features, typename Sample, typename Weight>
        struct make_accumulator_tuple
        {
            typedef
                typename mpl::fold<
                    as_feature_list<Features, Weight>
                  , mpl::map0<>
                  , mpl::if_<
                        mpl::is_sequence<mpl::_2>
                      , insert_sequence<mpl::_1, mpl::_2, Weight>
                      , insert_feature<mpl::_1, mpl::_2>
                    >
                >::type
            feature_map;

            // for each element in the map, add its dependencies also
            typedef
                typename mpl::fold<
                    feature_map
                  , feature_map
                  , insert_dependencies<mpl::_1, mpl::second<mpl::_2>, Weight>
                >::type
            feature_map_with_dependencies;

            // turn the map into a vector so we can sort it
            typedef
                typename mpl::insert_range<
                    mpl::vector<>
                  , mpl::end<mpl::vector<> >::type
                  , mpl::transform_view<feature_map_with_dependencies, mpl::second<mpl::_1> >
                >::type
            feature_vector_with_dependencies;

            // sort the features according to which is derived from which
            typedef
                typename mpl::sort<
                    feature_vector_with_dependencies
                  , is_dependent_on<mpl::_2, mpl::_1>
                >::type
            sorted_feature_vector;

            // From the vector of features, construct a vector of accumulators
            typedef
                typename mpl::transform<
                    sorted_feature_vector
                  , to_accumulator<mpl::_1, Sample, Weight>
                >::type
            type;
        };

    } // namespace detail

}} // namespace boost::accumulators

#endif

/* depends_on.hpp
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
*/