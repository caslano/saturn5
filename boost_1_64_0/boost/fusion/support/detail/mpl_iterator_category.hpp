/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_CATEGORY_07212005_0923)
#define FUSION_MPL_ITERATOR_CATEGORY_07212005_0923

namespace boost { namespace mpl 
{
    struct forward_iterator_tag;
    struct bidirectional_iterator_tag;
    struct random_access_iterator_tag;
}}

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    template <typename Category>
    struct mpl_iterator_category;
    
    template <>
    struct mpl_iterator_category<mpl::forward_iterator_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::bidirectional_iterator_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::random_access_iterator_tag>
    {
        typedef random_access_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<forward_traversal_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<bidirectional_traversal_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<random_access_traversal_tag>
    {
        typedef random_access_traversal_tag type;
    };
}}}

#endif

/* mpl_iterator_category.hpp
/J5Sn9B4YoQiNF/38G/cc6xQRfQx+PHrusji2397SDH1mNGoaW9IDjkBOMRLj8zkzQmemM/OFFryddPN+yg/dvLgtH+SeLuMF8b7k7YbxiH9K6DAUT/iKDwH4KVjPVDFZUqjp+4TWbjqHHqyzkWtp1TVw/Pf0r0R2Be9bNos/NMj73HXBA0EuLUiuqnXQw/jMuIKT/vNNn8DFfCQ/RguEl1P402ZHw1blcRu+wAoUhipawX9nCBABz4Pqmw+mZxSs3vvlzSloWD1f0XqH3J59cCCTBdHm/PFuAtBvzLZyp+0o3cUzBT4fcZLXjXtisVYDTEfAg+oU9VrJU/0msbqlZ9kHpR2efLmcrz2PpHLv5MmW52x9kCGA4OHGnjvvn11Ti3Aaep/G6g/OMTr8jqMP1d4wp6qPERUcKQz93iPKf8rHH03hopvWaIyMj/WIYk/gZXDyEAlyZmFwLpF0tBT8nrG1GUgKrHlkVSCgc4FfmU2ZNNEaj/Pr24nXoRRlatLN7Ej+ZU8F0OMtReYGGnvIeFvUwy8ALq87YBaP/pIbqG0XAgLY4dax7kPPg==
*/