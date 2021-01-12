/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005, 2014 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NIL_04232014_0843)
#define FUSION_NIL_04232014_0843

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct cons_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    struct nil_ : sequence_base<nil_>
    {
        typedef mpl::int_<0> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef void_ car_type;
        typedef void_ cdr_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        nil_() BOOST_NOEXCEPT {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        nil_(Iterator const& /*iter*/, mpl::true_ /*this_is_an_iterator*/) BOOST_NOEXCEPT
        {}

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign_from_iter(Iterator const& /*iter*/) BOOST_NOEXCEPT
        {
        }
    };
}}

#endif


/* nil.hpp
dLxVlnRJ5jdsUfz6S3zPHHz9mbZPmwps+5S1SVsmXM7JRZmEm3Ol68dqez491RF5E+2ELkEzqfuGY6Q9k5GXX000WhwpD0sc06alWuLt9+a58t7ctN/3Jf0GQe2XvJtpv3quP5E4zxJnW8qmabByrHOcyUvDG38fJKzEyaXq4r+Zy2T/XYRP03BXwsvE3vHUxQ7eMaSOf5G4Dzi7EdfXdkwZP5P9qWZsY7bksbv6uHE1zz25
*/