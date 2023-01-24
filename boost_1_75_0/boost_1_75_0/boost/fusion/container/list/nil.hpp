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
3MSY/1iZ7GsrRkT4GfO7yT9VeeIjZaLp6QxwaoRRPmaQi6P2GOWDenxuBJxJEWPI95PyDmZ16qHODu4heWc3n5NDvszrNycHf5k3S60v1Hp451ZpE+UdklxhkH/W2wbHxsn43BDTznA4+wHV4Fdt8zn5rE5V5Qvfv0UJOJuKfPcXzsSQ/fCHiG26BxJQl0ydVKZUOKqQfM53Xz1nrcQCz/TyTXzkygVURdYzkrlpV51GZdN9m0DYMk4y6/5uCYf8ldl0vyeSm0mSHBAHB8bio+vk3+JkY1gGYCEcjjrLwacPwXmBFVURpmlqVVYoCDcHlSAZ5d/QQwBCqE2X/7S/qsoHH7XleFAgPh4N9Q9IlSTZZ9jPLe2O1IzE503KBq1ePpYoV0jyT9D/tvgovfioPQBQRE8F6neo5e5dm62qNRyegh4VYwIN8kHcKV9EgVyWV5zdQeqhyQqQZI1Nd9YA94DqyDlnVV7w9RTf/NFqkA49yu3zlvhoTGk0+1YysBUf8hcpydO0+Ly5Y3A4SpaEFEGSW2fFI+YebAHMHfI04eMgxNy1LShzZxvJzV6SHAzkox6GqzCxQ4CbexHbEEM1ptmIoa3hBBbd4wZ/zLRY4JcEB6aMLsGcrLLm9lr6vA5BrA9q83nc5hkDqb4danOU0mYAatOIWJfv88LzgCujrEtGCVzJAp+hyr245+HQEsSa3xIRDOfFyX3ViEK9
*/