/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315
#define BOOST_ICL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315

#include <boost/icl/detail/notate.hpp>
#include <boost/icl/concept/interval_set_value.hpp>
#include <boost/icl/concept/element_set_value.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/associative_interval_container.hpp>
#include <boost/icl/associative_element_container.hpp>

namespace boost{namespace icl
{
    namespace segmental
    {
        template <typename ElementContainerT, typename IntervalContainerT>
        void atomize(ElementContainerT& result, const IntervalContainerT& src)
        {
            ICL_const_FORALL(typename IntervalContainerT, itv_, src)
            {
                const typename IntervalContainerT::key_type& itv   = icl::key_value<IntervalContainerT>(itv_);
                typename IntervalContainerT::codomain_type   coval = icl::co_value<IntervalContainerT>(itv_);

                for(typename IntervalContainerT::domain_type element = first(itv); element <= last(itv); ++element)
                    icl::insert(result, icl::make_value<ElementContainerT>(element, coval));
            }
        }

        template <typename IntervalContainerT, typename ElementContainerT>
        void cluster(IntervalContainerT& result, const ElementContainerT& src)
        {
            typedef typename IntervalContainerT::key_type key_type;
            ICL_const_FORALL(typename ElementContainerT, element_, src)
            {
                const typename ElementContainerT::key_type&  key  
                    = key_value<ElementContainerT>(element_);
                const typename codomain_type_of<ElementContainerT>::type& coval 
                    = co_value<ElementContainerT>(element_);

                result += icl::make_value<IntervalContainerT>(key_type(key), coval);
            }
        }

        template <typename AtomizedType, typename ClusteredType>
        struct atomizer
        {
            void operator()(AtomizedType& atomized, const ClusteredType& clustered)
            {
                segmental::atomize(atomized, clustered);
            }
        };

        template <typename ClusteredType, typename AtomizedType>
        struct clusterer
        {
            void operator()(ClusteredType& clustered, const AtomizedType& atomized)
            {
                segmental::cluster(clustered, atomized);
            }
        };

        template <typename JointType, typename SplitType>
        struct joiner
        {
            void operator()(JointType& joint, SplitType& split)
            {
                icl::join(split);
                ICL_FORALL(typename SplitType, split_, split)
                    joint.insert(*split_);
            }
        };

        template <typename AbsorberType, typename EnricherType>
        struct identity_absorber
        {
            void operator()(AbsorberType& absorber, EnricherType& enricher)
            {
                icl::absorb_identities(enricher);
                ICL_FORALL(typename EnricherType, enricher_, enricher)
                    absorber.insert(*enricher_);
            }
        };

    } // namespace Interval


    template<> 
    inline std::string binary_template_to_string<segmental::atomizer>::apply() { return "@"; }
    template<> 
    inline std::string binary_template_to_string<segmental::clusterer>::apply() { return "&"; }
    template<> 
    inline std::string binary_template_to_string<segmental::joiner>::apply() { return "j"; }
    template<> 
    inline std::string binary_template_to_string<segmental::identity_absorber>::apply() { return "a0"; }
}} // namespace boost icl

#endif // BOOST_ICL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315




/* interval_morphism.hpp
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
*/