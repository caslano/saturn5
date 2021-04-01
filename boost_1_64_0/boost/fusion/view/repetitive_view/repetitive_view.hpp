/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/fusion/view/repetitive_view/detail/begin_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/end_impl.hpp>


namespace boost { namespace fusion
{
    struct repetitive_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequence> struct repetitive_view 
        : sequence_base< repetitive_view<Sequence> >
    {
        typedef repetitive_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef single_pass_traversal_tag category;

        typedef typename boost::remove_reference<Sequence>::type sequence_type;
        typedef typename 
            mpl::if_<traits::is_view<Sequence>, Sequence, sequence_type&>::type
        stored_seq_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view(Sequence& in_seq)
            : seq(in_seq) {}

        stored_seq_type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(repetitive_view& operator= (repetitive_view const&))
    };

}}

#endif

/* repetitive_view.hpp
4I0vrk3MhvyDW2p9bi8Up9uZMoOXeEU7AhzVd4a+BsoJ7wBJZIvrQcLeyYNQr2lJxFKTGgMjRVrvXpq3ZhmIzS+SsD8OcPHk8OBINMAKqaA3Oxz+B1mu9RzxXpdsiOpuSQIHEjt2EVTOZdr4AngOxd77VB6nl0l5RO/uZZeiLuJyGC9Ckd4w7aYCpu9yYce8pKOdxU7dF3a8gKbz3TE2nGHStZ+PG23RLqYdn+3QfaCmeQFwLzBz2/6tI9FfkhmbwJv8EDfhDzxJA3C2A5JT+KRVzBl7JAD4xaBQG54zPXJYO7vu5qavWPCSjAPEyP5rQeCQBYw4H5NG5P5m0NZj5GLQME5bgazIZJYwSA69htV/x7izUMqv0fId3wmdq6hwdEs/LAXZMPpIIwWV/C/dSK3N4gqYj4lI1iyCr6km8tprOWLOwHrsB0aNviGE0Dxlzc7nX4NINrhi9aHfgmgYCtmY8/AZwFi3qSfNoNLJa5DcHRoadAFYpoApR8k3MHUt3XF534WXJsfQveKCjFJAR7SCPC7rSsRdXgBAHGwVcO/65zNlyaRjAYKyBg==
*/