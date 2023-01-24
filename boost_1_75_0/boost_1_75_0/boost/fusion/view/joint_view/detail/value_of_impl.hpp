/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_IMPL_07162005_0132)
#define FUSION_VALUE_IMPL_07162005_0132

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<joint_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
tsQ9AQUQUQbtcIUhGPS4chDimTpqj77/INF7fDq+SVnZ6jdt51mfYCeXFSHVTv1bzPZfyJw9WDP353wXwDhRalxgM25DNrWQOyG1K1BfWwkiaybxrqRSuai01MNUlWtWUN7BV57QH9ecoqMJXDXX94QU/AzS92nzGb761dbwqWEgYYPD77EJUwdq6HnzO8eZ9TOdywZBQBIvvQ7XE2MXv+HmvTVXkpuw1r01XUeiuC1+m0yoML2hZuUI35RlcWWoHqdLPqXFbxKRP5RZacrV9mRFc0GT/LrCsJLyc91saO3iGOzb/XIZClBkUdEw9CBx9K0MRWilLPlrizHJzPcis5KOJzepsHylf57yRfERN7pHO6Ktfn1i5s18itawXanhxxIzaKGFVfJs0MZ+/mbENlndZCOfM8ZMZfG2A3CLpVb62KhziKZwMMw4kXvItsSlP9l4LjyJR5lASFCSx/32c7vE0bZz5b9tmeyx7Fzi0DMYjO5oz6LV87o5siYBebw4HtpPX6ceNfajFOVIyi629293cuu8ZzNVKRzmP8apn35lZRT94qaBGafpRYX0YeSneh5ZplsDxX/ebJ3N1yccg8qJM2wYbmTQYwHyMI07EUzn6SC/ICPn1vo4oSX/LVwcn2U8FIjLUbVcP6XCSDxiu2fp/WI7VGvhdT0bDlZnWY8tAkjNwnlnTVfpyKWrSl/Zr4lcpAb/qnbSDarm
*/