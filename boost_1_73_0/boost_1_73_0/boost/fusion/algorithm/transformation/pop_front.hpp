/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_09172005_1115)
#define FUSION_POP_FRONT_09172005_1115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct pop_front
        {
            typedef
                iterator_range<
                    typename next<
                        typename begin<Sequence>::type
                    >::type
                  , typename end<Sequence>::type
                >
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename result_of::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }
}}

#endif


/* pop_front.hpp
7KQhtH/QHu5coogTQqxjLd3cg3vknIvBfeJdkzxRyIvhW+FUlwO+Td7iR3FYnC3QFLGCFkQFAhEzoy2ZpRyNWWv8weQOns98OSGFiU7nxmvz9uC1C0SnlwGCkT4bBvessovpZ/InQPFER5LwDToOK9el0pcK97aIZTNN/vJrMWtwRaBg8cgVu7Do2sR2Xwh+NYOBo7d5UkLEWdXZ7Y/8Qb/baX0rNH9NTLCpl/Bbls/fM9XCBixKWFzxgYpzVRkbrpTXOcskihYpJx8lqEitJpMFQQcQa/18LmYi43I8+IpQpfQPnBvaP6QhFf+27CvlTGQ95fm3rQcfRiMSXAsP2Eoy+uB4PiQ6bLTV6l2HLppxu/CA6DuyL1rPu33ibOCZiKxU+efMw7TzT9mokD6jHYHAaz1hc7FahMJjR1PtNZx7PPT/3Gx9yjwltiOzukyXjYd3oSkd98smV7+obmU0PUP/4mrkaPLB79E10dXSBkjw1dAvNMM6EgtPJ7j1kfVF+QbaMlDZpo/wz27/i2Mc4zGKrgw6Q8e7qx7tVudDL/fqz1f+yCgM7ReWS3f6mK2luT3iZ8U94scKvvVYSzDo0fH4st+2p6zYyX/kGFcb0fLifyr9s+ZAqQD0hWRSyUK8n6NSpiTatC1WmVwU
*/