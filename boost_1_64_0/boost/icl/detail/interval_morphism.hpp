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
MDgEgVkIJIufAN4lomLHpP5n+PSe8eK/Jv10vFmgedq0rmAX48ga0PZZBXkp8fwSKsnIBvfKLN9SEJ6cYwNw4Nvfmbdtg4qS8sTUGTpRxvTEwnENWWbURPW17UJ+MIb4jQrZ3hf/QXNUyrm3aztfSUsPdBn8Z019rlVWC1IBR+nSe7sGmrAO8LJVcnbNG6GoNSC3CIBjee0E4gfrUjpjkZM7nDDpguv4w8BPh0fLyF+bNmYUQYi/PdEiBqiUfysKiteLJZG7A5VmlyOVSNCpAb4/JFY5NCkUuA6XeEGeS5gmsAQH6PrV0rry7AYVA1nO4mcd4CoMlNC4/6VbNPqhD22wUJ2yYNiGam8P/bX7p47e8kZ6HtVl6lT3hLJRUEcmmRxlN7gwc00pHDFFWBxUdEBOh4AgdPZyKxQsYvc3L9TKVVCuEuzmhEaZsSqsTRnRhZ9Grc/PkkdNma3WOnZWlTul0IX6AVyMLUt7qWFMJMAvb9l8cCBm5uYmUqfckgRLmVux0l9xQUwfAIie6uCWNrgsvKXKJ3e8H7fXGxu8I1sZ//wEkLFeHB3sqA==
*/