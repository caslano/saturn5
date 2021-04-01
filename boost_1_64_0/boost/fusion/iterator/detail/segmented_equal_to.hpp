/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil_, fusion::nil_>
          : mpl::true_
        {};
    }
}}

#endif

/* segmented_equal_to.hpp
4KKSJDeGPnTDIM27dw0rqP434j5iFam9J0Cfc/3LI6c+uQlmC6MWjlqf16eE4WH7YTE5OIx58qb7OABFQ/fQa7yXes0o/5h0ToHmNxY7jOLy+5oGn5u9+pPWPe0dogNBJ7hML74Izg1ElMo4CZpxHRDmisBTAg5+OC/Vmlkw0xMd1pFQUq5SotiL2+J4G+MQufF624k/N6x93Y8E5pvBFYzGDjdB+dFMjEHIp6s/9jijWaJEVp8OKWYJWItUsCDmv25x9KvI8PTqT3jpqhWKLxyrjNjfIkWPhdLEttqqlukHueeqy9kwE6Pc4Uns9p165omacPQY69aK77AIMAy4QshP+8uDk5jOItcFoUApeKv6ag1FvLmQyN4TqQmTyXuzPhytIH/Yb1OnB22BXT/GuggU3j8UgmBlYVF7lnZcSikxpmGfFPsTtc8WTBjb6g/TUTdpnzeF37Y4E7XNIO6xdpaaEbhcBQ1UTKcVu6/1hsMsrMcng9UUrPy5SawKPMF7bSRukTwp0pAAX7742cpC2tMzQ2pzt+AOO69xG6xrHvIv8NyihuBTKZ1fhQ==
*/