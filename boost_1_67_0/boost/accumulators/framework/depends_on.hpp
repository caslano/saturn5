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