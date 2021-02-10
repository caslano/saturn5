/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_06052005_0900)
#define FUSION_NEXT_IMPL_06052005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<filter_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::pred_type pred_type;
                typedef typename Iterator::category category;

                typedef typename
                    mpl::eval_if<
                        result_of::equal_to<first_type, last_type>
                      , mpl::identity<last_type>
                      , result_of::next<first_type>
                    >::type
                next_type;

                typedef filter_iterator<category, next_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
wt3JXlTQrmyhcZjLOaPemTAbl80FzCJF4fPUd/ImNRlHsbCr+ZTIomS90nwJLVUKiaPmpoVqJir9h+6dFPYi1xNOMYmuiZOu9V9TS7iLi+0djtc54Zapl6fmeQef8KpKNUjNEAbQOR4/NBkuLIBYsxRoDhABzsWWCjXYDpR6ksoJxCts4geE7e3seI2+OW6Xy1AyghKl8uUZiSOCh5RrJqg0GmSmwIRqnxCoMMOsutQuQDn+Bu6G0OjP1uprQv24H+tuUVATUMgL1OYZl1Dbp5xuGJCb2bxg44Bd9D2cGLMD5SxDA4olPmB31+xui6Iql/HE8qMHvT80HyFWJVaLznOt0xyq2sfEBJCDaQp8FSeMuw46Z5gyDfYo1+7tIN0nRrzv9A5eAZb/o919dYoJd6kKSU9dUCzduFbag5VvqP0iToPyJj0M44pXme2DKV+BrNGi1Et4TwKRt6syFhKapxLUdFWph4v5+MPek6cftZwyg0ELVBwPZB8aMDy+1iIdUDpuwO9s13Q0v4d2VjygtUHjPsj8pBm8PyLTuZ4rdUbzQChURmcTPjFKB+iXVgM6OQpOFDjB0VISsaCMksRscrixb797aA5fSSIbSoG7QZoSuSI7JLRysj3WA+/SN+yoDGNs8ufLlKwi/19z
*/