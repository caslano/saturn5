/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_05042005_1019)
#define FUSION_DEREF_05042005_1019

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
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
        struct deref_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct deref_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template deref<Iterator> {};
       };

        template <>
        struct deref_impl<boost_array_iterator_tag>;

        template <>
        struct deref_impl<mpl_iterator_tag>;

        template <>
        struct deref_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct deref
            : extension::deref_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        return deref_meta::call(i);
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }
}}

#endif

/* deref.hpp
a6MKlqRD6cSaHtXpu7pUPF8IeHaHdenFGuvq9F3WFdcXrNsFa4Px9mz164qxjI7XInqf6a15Yb2no9ip13TTuuWFfGtr1uifDgejGTTgdPhev/wc9T4OcFhO/DKYTIfjETQuU/TORiY6LWHz2h8k8gJzscxtXpTLrVsLG27dqrWhrdqUW7b9fD6c6Y0bD19k5KbFIpk2LTLrJHMDobpcmykboiIoqNkrYv8YB9RE0ttLxGT9Bo3KGJOqDP+1Kk5Tt2VHZd5k5W8wLeNKtXHg+QFO9E6nA3o0XUMsIEsi4QV5GTDdxgOl4GhwPBwN6kBs5mpQnlvtfjbdTXy6T2D0chOj30VpWIftewrDJtC+B7L/32D6fxFLTSA/AKb/GZoaiPwvYuTvEAarsGdhIrHdeB0nOhWc0DuqCaKA2zNa8hI36DLO9f3drHzmXw6BV184lSxxTb8wwrSvmLdcgl2486LosVH5g+KyDKgtq2UYmQNUQXI9Cp4SBxsjoQCB3xAOxrS3lYtzeRe8tX9hxBy685dhTKd/A1BLAwQKAAAACAAtZ0pSoTOh8x8CAACqBAAAFgAJAGN1cmwtbWFzdGVyL2xpYi9kaWN0LmhVVAUAAbZIJGCtVNFO2zAUfc9XHK0vgLKG8TQ2NK1r2aiG
*/