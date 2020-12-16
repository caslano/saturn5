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
rEveePc5CsqebuJBUDNU77aGgVI/ehQmSpO8Rpi9mAgXV3CY3kOs9dfgl51DRbZeb17S7yK2PLPn4BGbkLp+KbN3WcsJdTX8OcJNWvf5wSYO9bIhxY47x4RDa0UX9l7STvTWOIDxH32l/p6FCD8ZJXy7H0BaS3/R8kg7zF9czqBufjDXaS0qLo+EJl0Y3/82x+x8i7bpteCitrQxDMH2UVFi4bdT1Cj/IIddsKGpzUB4/CzG/QBTDG40wK57r/H8yG2M9F8qL3cIwkm/U3yUtpMh/S7xjOpDjkvbh5Z5A7HOMFBYxQ9FWdEmOad1LRfNaSF+mgfTdGBHccDWiTdM/soa3woWheqKVVOX09F9kQh/okmP/THig1sGXg3TlyHTdjJDWAPx++jarZJ5+6J49ARgv+k0lbq2l609f6Pvtf3cUREFHzNzjnmZyS+fe8puo46yk8p3cdLkJnpu2cWqI+vpdM9JrpFN6ZDuKv1dHXjKqw06Rv3Bn7KmmOGyElNuWQmV+aWMX2Yu8r0DFd6V0qqzFX+n75f+YSaItMhhUb94xmc+4K5xIfyx+h/MhjzEhSjKzSOrkKh+lconsxC78hW9wtbTfVOJPL97Bf11X3PTtHb0XKEp7G9NQcpPDTb7aqbwqwdF2VmJqnVbReC8q9xts0n+s03B/PTzorbIjm4mCczf3IatN+/Ek6DXdCo+zJrycq5ZfUQeX+6M4a+aiJcB2Qx7uEm2djbnyFaOMuWgEnPPuGDiUQ8U9hkmu8wohG+ANywsJrDt7sncsi6DtR305eaqfnh2JEzcix5H24PjcWfjfKhVfxW+15awqdY2XptYDqN7DqJwohNn7PgonrQox1vPcmFf6cdW81qIJgsE9llt4/BfF/jhvJcYfX0Fsx5VyY5P7yBSWVvMOVyKHsd2SqMWU2g2fw0umpzEjoQCOTO5Bx7P92IvrzLMivYR599NZkp4Mctzp1NjWgW9rT/j3aiNstWwXfgRmSjcL4UxeauKWG8eiPd2fUXDipbIvr1H+Ifk8YyGBfTN13Bxaj/+WVqJpEct4HHvFV7IzvJEaSN67HFBa7f+uBz0SC76bcXCjVvxLHIQ7n/uIvYNuYhD9nFixNJUNrHeK5fEOGNTXqA02PCVm20n4b/a5zhwKg9vl93HZVsn6ZBjxB2XVovdLhHYFvoBru32Y2TDeIQtaYaHbtHo3v4Ph1/Jw8PseRh577086VzP8ePMmfl5I5JKFgmvmjqEa2ZhdN9LqBukJVPN03nAN0acS9iMYu9ceXajNXu97U6dJvZssqcWrb68QNPT0ULrxU+eGHJcfo/Iw8SgCzCvXYVwQ0vZoNcGmh4nFE5gOj0snGWKfTh7PXHm9v4t2P7aQalNL7bamyH1D+uitdcwhbe6wc+1J4XJbE1Y9b2ONcNqcLbwGQbHr+CR/bq4uzaDvRco8eAdM7qWT+IS06noXPCVx13VkG0cgWOad2GkZYqLC26jIfIjF1zX4uART/jZ5hcuu/URK81yofztHSI0fLg7Zi0mFmgjf6Gv8GdTWiplwUf9HgPaaiJm+kEUOSkY6MhImklrGWhzEB5LxnCFTTyXXisQM3b0hQkdaalyFc8aeogbyeH8MKi93DShAkX1y2Xo3jncOvgcrl8rY75GGIqfr4H+zKty598e6D42W4QcWoSjTzTltYTnVMscA5k/DLNtb+L7rR88uHGv+JyQwHLXl2JsyEbc2FciDDCQXfteF2NDq5F6NwMLSgsZeKROlKaa4GjlbnGhNo8TD8wTPRZ3RHin43Lnzaew7+SPnpHN0ffqeo5ZXU7H5GzuKXzD9Nj27DR+HYqOFrOJnhmXTY+Qw7cvpN0=
*/