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