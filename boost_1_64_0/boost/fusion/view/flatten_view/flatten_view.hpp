/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_FLATTEN_VIEW_HPP_INCLUDED
#define BOOST_FUSION_FLATTEN_VIEW_HPP_INCLUDED


#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/flatten_view/flatten_view_iterator.hpp>


namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct flatten_view_tag;

    template <typename Sequence>
    struct flatten_view
      : sequence_base<flatten_view<Sequence> >
    {
        typedef flatten_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;
        typedef forward_traversal_tag category;

        typedef Sequence sequence_type;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit flatten_view(Sequence& seq)
          : seq(seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }

        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;
    };
}}

namespace boost { namespace fusion { namespace extension
{
    template<>
    struct begin_impl<flatten_view_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::first_type first_type;

            typedef typename
                    result_of::begin<
                        mpl::single_view<
                            typename Sequence::sequence_type> >::type
            root_iterator;

            typedef
                detail::seek_descent<root_iterator, first_type>
            seek_descent;

            typedef typename seek_descent::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Sequence& seq)
            {
                return seek_descent::apply(root_iterator(), seq.first());
            }
        };
    };

    template<>
    struct end_impl<flatten_view_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::last_type last_type;

            typedef typename
                    result_of::end<
                        mpl::single_view<
                            typename Sequence::sequence_type> >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Sequence&)
            {
                return type();
            }
        };
    };

    template<>
    struct size_impl<flatten_view_tag>
    {
        template <typename Sequence>
        struct apply
          : result_of::distance
            <
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {};
    };

    template<>
    struct empty_impl<flatten_view_tag>
    {
        template <typename Sequence>
        struct apply
          : result_of::empty<typename Sequence::sequence_type>
        {};
    };
}}}


#endif

/* flatten_view.hpp
fyuxJJymJytAzfd9Zmp8td/C0tkKM+XwzvBLuW1ynKdF4go6PHn2qfXKDSxd0IAnWJafQsW5cnJSfs5O1fj2QL2k2ixrrsrCyopvfEnOsqc6PelAufvs3rq8BnOmvpG+QpPtkfnW6dPM/DulyALHD8L4qu8Qy1REPcaX1HYqVbKYPrnTV/u/xylM3gpWmr60XBy3Aq+bhspHW9fEovwohat4nim/FUtPyJ1uXNiy3BT2HAobPqOLYHX1S5ox1PgL2/jmoMJVWo9DnI+3omW1C63kXtyQUyNgJYf+endqi6whra+mmfd5ftzm4f3J+8IPb5tTbS1JD+n0ypPxdpyY2YO7siYfOF6t+Uj//rOT+cQbf0+bHLx1iTzSWUabo/ocKZOMzOSm+4n7D3QNdkIv4Xc/EjdyqLsIJa0EYdY6tjl8ScMmyned1A5iobInRwj9il7jbXqeluMUbl76WZ3W07dPqrS4DeoFlpYlvKhMk9gt67QGPTKfkqJNe8pLTM4WgZXGiR3ogqnXQJXJTaNsv2mkl7txWFq+Llslh/Tw5jYpUcPO0A9L1wp9UU8o1RyVWkAa6m1vcJuA2zDZUBSO54SJY3HZZ/cGyl5xRFMgJY+0QybviKywUjvMMxiBVmku0LcMdybk3PID1M/O0QRzptIrZoUk8Q8SfvDmwE0rJPTDP0t9G9sgKSK+YPQf1mGmb196eH1lTfr1pQt2xhrqTQbH7W+QTaJiAD9n4A5lpMYxxs5/oxpjMdrVe8/rw0GPEiTmeB0lvgkulEF2F7o62sM9XiO+Dfmi/fi+V+9Oeu3200nxdHbxVtqPgdeXzc9gnA9fwvc4wzxMitS/6rv8epynb7TaQ7+hWgdQCtV3GOEHVbjUAQLqsfn2ci3gR7YnvwDW8eXu8eKxy1HudQw8nUxQ34PX4bsi463CXoowykP1bYQf3qTWIWXBUHVbjH9fGeO6huvxg90vBsf0DktdEZy3cQ7GPvM7fXAGHHOgAn6HWYXzwcX0XwHcGAww3qvzOuC7WygtewP4kfslBzXVsl/4KMdrOwW8XQpstc/fHn6pgdGT7aPrqrbBPHBuDrhKU8Fd9ZQBPcFjzHPAg85ivvkzjqko6iqA/Oh64OjpIvL4TQMjsVbZ0+tznMoO2S+OMf2ysuSgbdwbADf7IuR/I/H2zAJle/INm7hMvjJDgn/iFkddAgY+f6MmXl34xduKakwJ+iOnUuB6DMTezVlzjFOv+1aU5e3lSlEN7ivb3IqEoVXpLWynYq33QzqhH6hHDIC/VOKT8lXjlyX+D8dW7FGC2xg3wTk0A05j/DXupb2E3cssy8CLo1ScWKBnqR9n6Z2i6lvVvzV9Y14s+Rqm2dEzu6NR452GALhqe2M/lmFsjfNRhimVBDY7LbHVI+tdjY+xNyhs/cgqsHHZ5l/M7kPZXhBGcSxoFrlBC8PT+juNuZMw+aUoPDvy/DwWube85Fil110qE8vh72ssmzILuZ2mThTlYjh4Rk9PexKdn6ex/MRxYKfyDiw96EWz4NO4+HJ3zBtNfiFcOwq8KClYfiK861C1z5WzUobnWLeS5FxHnKe9qMmJNIXtP/mNeGAbpHVwqs2RrYoz3Al4PecGx51uciKVDFv3tTmUjNHvZto4JYM0XilxpT88L2Yah2YncSLEcUHiSs/2juOR+8BhceAO7Fl2Z9rPStfOkqqvLUVBq6+Viq/hyX3NA97sawyjz8g8sB+3sE1go2mGsT76K4bxPvrIGcLQRyVu2BkoTPVRYLDHOMvnZ2WcpU541U/69oZbh0Vzj8Ct8lgm3hOgS/CRMMVxKgT68ldeaOTlIYkT+1GWxSItcrQNuN80uQs=
*/