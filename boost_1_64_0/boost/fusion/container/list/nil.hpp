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
fgI3n3BTchY83qXEyigCy85jA/AObP5vjye9jgcjpasiLHZMdx43mUATyoFiB8r2LauNnZ+yGlOFqvK+IvgvPV7lQP53dNlsAPRyoqwh0cBi27Zfsse7Gn4XzkeSWqmPj/HEVfAn9pK9mn9jDRycQeFZnZo1WouVATP/pBa2/5U6t17FFGvb8LAGpyvvZbNerKamFdVrmeLoawRfXyv87RqhMmp3ffRd0EYDYYoJ+YBK7c09HgZNwvPf3cTw0lkVESmjOCVylQChUfhte1E357Ee8/XTJlwy5BbW0jgRDdtXzVZGnnprxSB7sz2tGMTdGeHWrnwTM1dM4NXxx+mSI9IwvJtt/s7KTjMwD64sQ7j3o1siYn/2UCiZmyVKddj+s9+Ycx3JnpzpbxmIntjrUe0+oN1lwszbxobnDXFfLimM473tWaBBK6kRfrTIr/oy+6q960Q1dkKL0UbNGrwYoBxL21g7OQO5b9kBK0xJ6+d3cDZLkzof1owqDC5shJZWpkhOs4pQLJ2HHQ/Lc0J4Jt1MaFH2WyWjbZea63saFJshM5h4hxKoz9IPsA==
*/