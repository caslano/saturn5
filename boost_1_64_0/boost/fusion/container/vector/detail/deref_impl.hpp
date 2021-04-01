/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
uS3/wSKKSkL9GB0l0ItXEEPnAsRORofHD/3WYL4qEJq6ISNZhoOaLDdWcXcMOMU5gJ5mxBSCc/Rn23yAIkX8SaYHE/Q/VolEOGusZU2wxOjxxaHFNHmThHG31gzjhRl6RGFMSO/vQMJmt3x4gwbBYk82LvDLEJ9mYJtL8StBNnDaME3dp5e5LC4ZiIsEHGJGeZgB41xwmV5q7ys0xA+OnvbXKyfVu4ChWr/2nOZaYe4grDmnJJsaakr5OLtWQvAChiaieq6BVFMrPqZvYnwSXHJqjPzlaU1J3TANDSf4oQx+2YQXdFvKmqillgrqgRYw9X2PfsPPNV1lVZK9JIdOi4UqVpYrn1KjdD0kBd0l2PCHvocNlrP3KgP6SDDQ+ED1ytQC9ec9fMZiZAnRR73kiOyQcS1lecoXNX7S7Zxmvl071NY+XxxEhZe1HbGqBRnz7qbWPx12sLzWfVPg6pcEE+oFz1MdkN1ExCRZMsBwknhuQrxFzIi3zqx8/CwAoRUfJfrmcRY0Kb1+NjVtfZs0fLIrZsMOEKoZlXzpH2MxmTH4Ze9OA5CT0BBJgQ==
*/