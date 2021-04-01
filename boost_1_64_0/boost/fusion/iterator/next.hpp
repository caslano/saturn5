/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_05042005_1101)
#define FUSION_NEXT_05042005_1101

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct next_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct next_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template next<Iterator> {};
        };

        template <>
        struct next_impl<boost_array_iterator_tag>;

        template <>
        struct next_impl<mpl_iterator_tag>;

        template <>
        struct next_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct next
            : extension::next_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::next<Iterator>::type const
    next(Iterator const& i)
    {
        return result_of::next<Iterator>::call(i);
    }
}}

#endif

/* next.hpp
WlKzTqcElBBOY7Xy5t7qdGPybIG9KFm6numwZhB64bGAmmCXJit0iiQkBgnX/AtOtdS/wRZ0qvFKs4DyY8TkdHndnzyjUghIJGBgJhN+fNVF6yKFSLF4doj91nXCI2/2/5isRFkY7G0ihcMTieqYp48uYjRocC4rznN9/OVmWZ9Ww1UNFlSjS9yikITF/rwo2bFYFYkUSqXmrxoX5CsVJ8mckDbIN+41iiC7m8y7wkD2DZ0gH2rzuCUJtaJOvT1brxVWXkJzmKtA0bFL9eJP8hGdAGx3nH/UOEebWzdEjqpnBZbx5L6V8KLs0Ecvoyj1+z9VSj6tgYt/xWVXsYAzX9GpkLpNzrZpQLt7kNmNgRKuSkzurCIunRUohMZC04GCZ9S/SOxIzP1s39tL1y7kw9+fNxRUDxZP3XDP9PFcpqdtUsmuDj58ACiI8ObKnwvA8tPauTSwQZrIYtkLpjRQSUacUGZ3l7ooRuf65Vi5x8NQVewph3tWSWbhb+zA8J5WuazcVB14gf787hV9MWpHgaAzZSdEds+ZKIu2JCvvKdM7z6UwbzOClUrFUg==
*/