/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
/byV+699nLtV38rl7RHMipBd00oQYqpojvHheezDyq4W8HYsHLIvE0cSceLcmUK8D+HXkpUSgoPHwt8lK1m//y4l0FUFv0oqNBxD3BPGQ0WDbTV6+8awIA1GPnBEXzvDzBW97z94yq+O/wN2AGyGh9n65xeYGO/G7ZOp1UKuPfhNVSxhkxtgALIeKptCc/i2FB04cIiJ3uvC+djIlZUsRsK/XiCTbA7FymaPgn/5rTXAWldY6qLKwBV8sr+kCnVNL6DHufQYyCP70KuVHl3pEc4jj2/A1z/o8Ss9ft5Akd/T69f0qKNH7QZjfRDaPj38OSuK+18A5zqoEXrh8+2M0EW+ePu0+NcqktqLe+tSG4UtmxNZiamOmjCyIEa/z8+CyflRwDchDhGT5NsrONrEDXgShwC2lKKHZnWlVdSiEI1BVHjAv0MPsGx2+fsoTFKC36ZD4FZ1hFvCK6bPIwhKZYWFnujf1RfVtt1K/m8hKzmzDCYklPk39SJG/AXlFpiQw8nlXnzrAhRRBrYRZ9vwuAotNKGQzZmDcsJcdNNF4MysLu6ZWcpmvOYDK2E7+TPzjbeT68gNn8WZNMDZduWuZ6AfhOdUNqUBtBuOfYUg6AzxC7u05gTNdsMz/LbtWgh4nH2tD2iXt6JWFzUCTkb3iF2sI8awehdrtgHPoFAR5YUJ4cIlywkuyUhqIHYkThGA/UcugxETtuxbls59
*/