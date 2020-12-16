/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_14122005_2015)
#define FUSION_ADVANCE_IMPL_14122005_2015

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/mpl/negate.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<reverse_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename mpl::negate<Dist>::type negative_dist;
                typedef typename result_of::advance<first_type, negative_dist>::type advanced_type;
                typedef reverse_view_iterator<advanced_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
t53YFrRDLC7T7dX0ThlnlJH2l08p3gPiQesWIc13zJGV4jJRO9FC3xHiResZJm3mohqDhUF2Iz7rklYgXYxbWGJOI8xlNvVxxtJk0UY4HC7tb23DM/TOh3xG6K3Yv/9/H8TJgnmFBWNxHCKkZdj04pYwv80I68Kk1c04eKh474GzFLZFye8z9Otz0/Hvb8JspY0Qx8wxr9oUYW60o8wuL0wsQFbGCG800rQjb04WBuWNMI6ZZvKnRGHBCkZYCtKOXuhfS5ivohEKMru3NXIQxaF9YNbfN8xJOVQOzW94zD9bKQ6N51fhYvIHYY4qRqjH7JclzboL86JN5/UdOZ+P+tNuhErMvnyf8w7lgKZlub/pebWjMENVI2RmtrhBuydUZjUjnI6QNrrj0APUljpG+BGkZV17eTKV+ZMRJjA7uC9pEbUF7XtmGx0OqzCoa4RyWmlRnT3bhPnrG2E0s+TXD+MprqEROrIcTt8ZlEz1JRhhBEi77n/RQFhiIyM4mBVc3/0U1YdWk1nFOk3JbI1Dx2jJ6TVemoNokczk2QbP0GhtlHZ+wbPbC3/5ZGGJTY2QldmEXIklhPmaGWEDSPv9auN3VGZzZfwUW7e/+T1h0BLnJ7Oh03PECnO1NkJ+kEbPy9G8aEWYzf/3+kthQbTRzOofvHmU2tLGCFWY+Y6PLUZxaHOYLQwenUP1tTXCYGazqsVTOx2JqbfTheZidnHQ1BXCrO2MUIwZfS6DlohWnRl91oPmS2HyMyIssz2uW2bysyVsCxpvS5v4D4MoroNKW9Aua6WtrPasKvVZJyOUAWkP+5TzC7N3NsJQZmv/CX8vLIAWGSatb53tVJ+3mxHvA6Q13VBprTBDD9wjI6TV+/LmgTBIxv2Fz6VLdwLC3P2MsJLZjjlXW9OcGGCEUSy/Phd/Hi7MPxj7msUdtOUYJsw5FK8rzBrWse6nOTFcrrH/YGBpvsYSVcypYi4Vc6uYR8W8KuZTMT9aArPtm9vcoHEfgXOQmfz8CNsyQqUtaG2ZzT99e5Uwm8sITmby8yNsJ9pZZsUfLGlHNhLPS8z4O8phlBFyM+PvIbehpRbnVInzoI1lVu9Klz9pTozGHMKkPW/v1lHcOCP00EgbMHNiG6pvghFqMds0JrkhrYdJRrgA0gwLb/1Ca3qyEXall2aZ35LWinuecj1SrEb7BneonQtSz929QGWeoaXWL36VMg0LU4+zo6UW51KJ86JVYsbfzw6LUjcHWnaNtCXpk7ZQmYtxXjM7ds63nuI8eP4MY+18XLog9cvy1OsLosVHSHs98vhdiluH16Nwado/fvtMe8hmI5QEafwd8x4VC6AdYJav9q3lNEZbQtff0um5K1F+W40wleWX5o2zIcXtTL0+w+9G8GukNdmXO4ly2G2ERyDNWz2ansW69uDZTdmTv+Lzz+6nXZno+ct+Iz0fBA1AbdOFXsJcB/D8wmxokR0FhIEP1xizsFzD+glzox1k1qzbyh5kB40QnUbaksqvlLilYfaTRvp9e41madj6J+GJwoJoHmamSjG3hflOyXOdFo2ef6LZTsszShjayNi5L4S50LYxO7uqsVmY84wR8nEr9dtUYR60pmHStq+yrBTm9xuhNUgrd7xGQJjjghFaaqRdtbfrLsxwyQjzgZUZlvQrlYmmZ0af9aAFU5j8DAzLvBxq9JkUmg0titmHcn0PUjtTGH3/DM2Zwr5uXZtOmBstmZm7/c5wqu+KEbIxk89bsT60OcwujroXTjlcNcJdZvetVx5SmdeM8Buzmv+V3SIMroeOe4VaP86m+tC2MMtszr2RyrwRWmb1mTnyUpk38X6FWYK952UqE60Gs+SRTfYK86I=
*/