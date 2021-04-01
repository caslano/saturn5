/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_27042006_2221)
#define BOOST_FUSION_IS_VIEW_IMPL_27042006_2221

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
8lf60hu4i+IKs6nlnvtesVwGv0whAANBpel+gBto1ocaisBOXfG946tIi/meYcsrMMKacS8EeTOnKdviCabhNVawwSue5xoC4ywgT9rSWbOZx6EJwVAhSmyjomeK7C1FO7spCjqYnP9e/GpxlYKvWGcveYnKM5x89zBxLY7e+esJHIXoDQeR+bqKscxu2RSsRWoM0uUfVPQgUEoGplgQY/0KftUH+gZt6ib7lVR/qHkN8MXQmwZBMdRU8I63L8lpBRoeO07ZcOxEFmAZi4rRiYTKk1/c92EaJRmRLCwXdjnmE6aYJD8VNt6Y8mHc0NGoCSEAsTV+8hdBoX0DeLBzTwxSqJenCCUt2zlStM+RlxzqI1R1Oa1U+v/LIGGc+d3b5gsBCfTKR63cKJ3NRViwII30loFEBcD82gysfYRsVeMrT5ldihnOxobICr+0omCObelbZvrZPlk7lkXBqA1T3UIoSzOQGPzp40/LG5wUuG6mdQNaoq5XQy5LNwuDXEjEnoSrrXTQ6NPwK8pctDyczFmfssadpHyR19q8sDEiMd++vareDYkpE11OiQ==
*/