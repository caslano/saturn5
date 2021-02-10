/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end_impl( seq, stack )
    //{
    //    assert(is_segmented(seq));
    //    auto it = end(segments(seq));
    //    return cons(iterator_range(it, it), stack);
    //}

    template <typename Sequence, typename Stack>
    struct segmented_end_impl
    {
        BOOST_MPL_ASSERT((traits::is_segmented<Sequence>));

        typedef
            typename result_of::end<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Sequence>::type
                    >::type
                >::type
            >::type
        end_type;

        typedef iterator_range<end_type, end_type>  pair_type;
        typedef cons<pair_type, Stack>              type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static pair_type make_pair(end_type end)
        {
            return pair_type(end, end);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq, Stack stack)
        {
            return type(
                make_pair(fusion::end(fusion::segments(seq))),
                stack);
        }
    };

}}}

#endif

/* segmented_end_impl.hpp
oCXADuBwQPAekwD2F6orgHU135NKVyliDiAfzp9sAREVCXGLjZVbCCHmp+EdtTaQ64zfhEmCE0WgSHFUGUHehkv6SlIgEkGTNZozFndq64ZJmIVepGXiLKwuINxhZ0gO6BMZSbaGol+sMi054hnoLxk4kK2WijblEN/4UMcr1BsphwDxwxRiEqoO1eqBRSd7GVuItSKbpWItkddapLftmhqcwNrzJ958zpcZpMoQsBacGNjvOMK2EIopKqQXwbGuBYmwfIGrhc0KxanhPUqYoAbGEvTFQw/WCJMSzv3cUriIEKKTMpyXKEpvJkWEjR40CRZ4beL2HiaCps3yc4nwPc0UJVrPuk3pCvhRZcjCloD4Lm1GCLhG4fGvBx/Z8THb6+w57MULHdHF54cf7XiJ7pWiO9rDyq3iwec9xyFsyraeIlV388nLl129Awr7pdXCwS81FfEQ5FDSkiVyh0iVZmEBaN+9Dx/2qISGHdM0VqR9MJp0XmkIItJGCFocdFnIXm9kCPbyZai2IhiqqHho7VRhpJBWBbLVGrCepLOmPAfsgcuYhYkHkfsbT4VSCH8oB0kv4EHKecPq5HT189IBhO2pi9756Wh80ZuqGWSjwAc1ytVrQYMmG7njk9Hw/PrzyH17NuyNr4k9Zt7W
*/