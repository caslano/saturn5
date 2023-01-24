/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09272006_0721)
#define BOOST_FUSION_END_IMPL_09272006_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace tuples
{
    struct null_type;
}}
    
namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef 
                    boost_tuple_iterator<
                        typename mpl::if_<
                            is_const<Sequence>
                          , tuples::null_type const
                          , tuples::null_type
                        >::type
                    > 
                type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
jMZIu1zqDZpukqgyEKR2zY1jLbUHG0miL2kMsVUFmhNzCOnMtP6y+yg0N9yUOks0qZROhPjlZWCJJGrsPPOTHAmeElfrSLjDtgS/RHRKH2qlOx2fQDs5pcyTDuWPDOmJzbjb1mwPH7QC1aL05i6UkEmn/x7ms+Xz8e1EynQQKdNBpEwHkTKdSaYikkz1wcQJqNV52rSiC1mmeSLTkZSpvwxStmcqG/GjSYnlsEBUuDsHkhP7m6x6D5uXDWx/XcuiHNrmpsaTmib72E4TM3TxvkEG1rkuUyKMz+Jw+jxOnblKwoyLzRy7JV7Sjd8NcRit2aY3mWZn9ejn8WbT75EYCWcJNyKq+tama2J1SbSx2V8S/XiwnSR6sTlAEt3fTJVejgO6SzgNaMT273k2iZyYOGMEOCqjeRLk5ZazKMmh2JBSyaVQAZBLCMH07cHggkks0Z7rQDa9hPWMitjXDzuaCdXDFiFUd9rJbKKARFKfm/rBlVgl54nClC1yWoxU8kwXi4XQh/KgGLg/XA+LTFgEIB4lWWXkqU8dOIHq2O9FEUH1nDBc43if4wLmBPxcxBceec6Uo6BbGk+7l9IDVotyqvl2lw7jGQGlELSd7YY8G65OaPV6pnl+SjK+wD1+onAl4eI2QCJ+sRbO9nlFMYs1AABzRziUU7CindidkhBe1B63lej56xegJ+Vo8x1wGSXgVpEm/OmzpQfSJGbX
*/