/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
ZAsHN34hdo/uw2yfibBIxt8AkTDJeuU9WtjvqwTtZqmz1DGovVLMkhl8WlUGd5ZpSJedJaWlxexHYEBbG5HSE50muQ+4+vL0FPoVi/04MbotX4TLt3qP8jxNZkxNhoA4JQ5Swtm1B9V0V5ukammvKxKJcqNuwbTu+tqahp+FYdI5vKWg9NOBJ7UyGQS2RtfO9+y69VUziGzP+tZtzjXPWc8qcIciFKVu/l0F0ktWo4ODTAXrTO4/UWeiP2UddFPAUzB2sbG7dux3uCOH9o87Fr7+BN4zEz08TzWkPkbE68/ImHB3c7vbm8FsXIg+cWGX0GJ8QdEaKdDCN4oJbkfE78hFHsJbk7p+WtziBK5NIY/UeEHEnrq53EOYef9DfoXrJ1kl48PwqNYWU00E+68Awk4zdylt/4yjPQ312a13ehT4XSCXzB/puiBULkdkcU8DXPIgvJjbXZWKlq0C8cqb1NpzaxkbOiUSjZT1dOONMjWFw22HD3F25/5EYfD8bcM6CHk81Z23YRhizy17myG+kPnfVXYbmCQotUwXzo6aIcffBMzayXw09zTmvw==
*/