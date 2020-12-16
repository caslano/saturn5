/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FILTER_VIEW_HPP)
#define FUSION_SEQUENCE_FILTER_VIEW_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/view/filter_view/filter_view_iterator.hpp>
#include <boost/fusion/view/filter_view/detail/begin_impl.hpp>
#include <boost/fusion/view/filter_view/detail/end_impl.hpp>
#include <boost/fusion/view/filter_view/detail/size_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Sequence, typename Pred>
    struct filter_view : sequence_base<filter_view<Sequence, Pred> >
    {
        typedef filter_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef typename
            mpl::eval_if<
                traits::is_associative<Sequence>
              , mpl::inherit2<forward_traversal_tag,associative_tag>
              , mpl::identity<forward_traversal_tag>
            >::type
        category;
        typedef mpl::true_ is_view;

        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef Pred pred_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(filter_view& operator= (filter_view const&))
    };
}}

#endif



/* filter_view.hpp
sckUIX4/diTne/Iqzus0dirRt6bAUXKjOGiM1xWpV6aZU0hjjo1NitOwSNxylzGwzhvOLlsx7BLPzZ3K794N8f3rN5d5emUZhF4V5cKeWq18XrDSq8rK973c7d5n8fr8xzKPRxUloQw9dGxhEdeduDPU+9iZFfPuJ46DvCxzXyyQi1yjKnpCp7HHxBcidMPaT2Jp4gQWpKHb7PYr9juEIi6LwBNjnfHy9o4ZbyjqMqm9NBWGRZNdOPAuM15fJE4SRaWXiK4j2k5c7JMmbyl8PynSKg7E0v33D+Cky7L9ez1LzxGeFzpp7oaSqd/tJgL9a4WPndRLK7eqJdtSt5eM+L7J05OMbhrEKrlOLyE+XS8XGF8gSqrRuK5SybgwvjlGtrIrVp8Oco/+yySvbpNxY2H2cTyvgef7dRU3Byb2kDXnFZOvFpmTZpTbhg3ekQ7xPiNYWoGonbhw8joTY9xW2n3mCOONRJk7eZrFqRjrytKKs8h4XeEHZRz4lWp/CrtQbYYrm4PhYRxowsbM5KuoaoqyLFJHsrUHXDmi1cHGzEqLJjIn8zKcneOhYltA2HYwvkS4ceLWjh8p+1RMnvbRa++/sDMz+UvhJXHkhWkkNrtJrug55qLJkwvXddMi9ELwHF7n7fcPlkdfZFWYOVHujbmv7MQ0nH08v8ev6tCP49g1FqJD2ij6wYhpOCrf3OO5DQWtLUWYsGrFObG2NRcmzz0Lr8xKaR1PWn13zau5fDdI4ygg+bK+h09+kGSAfJxPcp7ScSonS1whDRnJd8FYng2Tpxaun6Rh4fnN8esyRTtdAtvIzz78GtmGWkP0n9OPt+xE8yLOY3V5OcEFFO+3X2T8jgiDrMipfcW6dmKvvNfrSj6KOJ0m370833XyoAZTCzdsFC6ydCh7jpeGWSHX0EkO8ztrwMwqt+8qQ68s6lRNdSNm3nf3rHbmj6qMHDUnH6ehtURjzOJFegdX+f1LVQZJGJaS94l3o7nHKOmC5ok5T1j5NOFUimUfZ+ktYF1keYyFF5ZJSlUz/miA38WfZLyJ8MvIL6JYzf8rk5tfaP4zVtp5mqd+nNVqYd06+rj+IvebYa9d32T8oYiTzK/d2LxWsHkd2LvyugpcJy2jIhdwjGTYEet+9w+T52BVZU7mxwFYOvceM8f4vU8YeTTwqHwTHeRj8CJ2151MGXev3CyK3bSkGXqJj6W5Y9YbDjeKUt9PRKM12HrREH3G5Cvktasf137aLgFMh3Mwn5g8laj9MijyMCa9r8MFnhPHuF7jFlmSx6F1BcTHz+uPWe+vci/0y5zm7zZYhmTh4xXxS8+avKUoKjcPi9BhrDoGIu5bWXqVqEonjItCrTWTA3Twt0a/NWUccAMnDjynVNOEvmPtw9aNpZcKWue9KilzMensqrWPhB61xtZ9YqvdOui2edsWi5rv9hZfEIZpXTnU+WWf7HTGRezR1rj9e5QFcVYV5tNv3Anr+qhNnv2RT/03pKJSZaBfDRDbyMRKk6qEai8PxAD9o9sXl02eWiRhGldBEqBfjdM/T6zxfuVWuVP6cdPMY/aosI9kfLlIwyjyohRvoNvt2LhtyGgfaNV97FRp6XthZ8/acK7ovnKB8aUiiWsnr5KC7wM7bSf0PNJbN+eRMHUzN6oTsannEdjnr1s2dW6W1VlRSw3mEuUT0NHX+V4pzaPEzZ1R8TLYKKBsB1mamUiz0kkLZaw64XqQ378eWWc2i26l9uQyx3ImSrRdxaLuk8sm/p60jjt+VWcaz+eg4+t8DS+oMry8UhNX9zqSzwUfM3n3p2US06RMWzIaJ513Dd9k6eQiS8IyqCnByW6k0LegW5syDpZ+6cV1rbY=
*/