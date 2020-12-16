/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  for_each_n.hpp
/// \brief Apply a functor to the elements of a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_ALGORITHM_FOR_EACH_N_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn for_each_n(InputIterator first, Size n, Function f);
/// \return first + n
///
/// \param first    The start of the first range.
/// \param n        One past the end of the first range.
/// \param f        A functor to apply to the elements of the sequence
/// \note           If f returns a result, the result is ignored.
template<class InputIterator, class Size, class Function>
InputIterator for_each_n(InputIterator first, Size n, Function f)
{
    for ( ; n > 0; --n, ++first )
        f(*first);

    return first;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
EokOkwW7iiumRex15btpJDttFxXW3ycq3Pwcqc1tSPkEKVL5++z9G4n53p5IXI/EPDmpq1T+AVt/ckb3rshZzhXko8gunv3IQWxA7+28cxvHdrTCtuuX97f9a/+0eF51Xcgqbv4DWsyc6elOGX++xdz5DF3yPYiNdk2PCe7/4Fgz0VU75VWZtBukxv+KIbYA3qyYxwmoXIIqnmk1FV4glaeK0dkv4JRBWk0duaahVrZ/fhDDqAPu1gDP0QC/Y1K+0p71jXxQuW0EC+HXUQJ0/9ufooKk4BCnkGSl98d4kAgOX1DVK6gKweOJhjQY5eYJYpV5WqtVrVTSUGdO/Yxl+fIVaeQXIFQoVivUE4XoZIJi+o7JRzQ0WPBR+i6UZC/dO4YzWg6DX+SJU9Ms4KedXt+GdU9L7RRK/eFpkQqnvg+jjhxlxjph+xeT5W/FajVTeAv8z1JfiB/zgs/eIQUlXf1nbTWYbgUZZX2j8QH5oFNmMev1Z8WwLrAISho9BvC+ZHkWYHb0wh6YwucWB+wu6CQnH8A+7I+YlXWxbljFCYK7WOMqj94iKhpmEbsxF/KcWt5g7SM5rCc+g5K+fEQkdeMkmxKYrdsLnomCXbWCZzyrM6O2FsFBfQtCngu/jqGyVuW1Mp36k0Q5pn6LhlClcEvQXqvy3QUieTmScRII7WkHUjae55KH2rGhZ/MA9FldKiVIq7pY7jNpyQMns/XY3vtERc/drM1BxmIoyx71mjR1jfjmZg10qgaaw6BXprtpd+SQjyvdh4qMJ80igyJBPQipg5s3KSxxGhKl8lixNGC5oZkVj1cqvJen7kwrevGRq3h3TvHctE8fLxBfINVD8eVmz00ueRbNxZu0/I+1/PlmY2j+xd6VwDdZJfGkaWnaUlKBQgGBigWKRSlUoFiOhqaQQArlRgFBC8iCytUoyFUs1dbPKO6u1+quJyu7uqu7q1jRxZZKyyWXcnuhoq9UoMUVOYTsf+Z935ekCRAQd92jPyXJO+ZdM/PmzZuZl6IOopiThrJlY4oYcDM/o3JCOJZobfQFDERspDqPqWBGyuu7kSr0JWpyH8ld4iht8z0SfCdK63VnQn4KKmSoFYaoFRpSpjqpT6kVTvC+Y5RsqdsjZq6g3C0r7EcyOAbpiiPvrcdmMAtTJYg3fEEcXS5B2FUQTxjU+fZUiV+NBEplnLA8OPWsB6MdQFLI1qW+nIirrmC4+begBKS20amUNnwUM58cgLKLwSP5Rwb9AKv56+PMaqhYDYxz1NSnvakLnpSpYEBxIyUD+jt118knN+D/4hIswzqfh+KUfMmGiAldUG77X/mD/22nBbGIKKjqH3qZ8+OZkZURIzPNOYoCTyyCgy4F3aoIWr/Fueubuf7Y89d33HPO+g24fsJ56qeVkYlxXK9onMc80H6sjXNklM2pRa3PF3Kt/qh1Pv3aTcs0pR1pCR4wE763RVUrbcp14mvoOAsrwpA3CXk2pQLZCcgmDNuEPHAC+toftyMo01sv01At8xKVcY9hhomffy/ick31cuFquSWyXLJa7lFZ7psSrdwPC2S5MbJcJn2/YzGz2WFuM2f1nqgeTJhsL4v27Zz3/4Xe+/df5ga5//fJF8Hif9zrY/8cpP46n/yVQeqv8MlvHKR+kU/+tF8FeQ8qk89/aiklYsguVoewKYf2/BfdocyAb5XZIJ15RN5SZj78UGl2GjtI/ZGZVv6d/HzW69Pp4qWpK5V/hfF1hdmeAS8JV2soaflrsqsxIr9mQLHgimJ7DqW8plvaBvzbGceiDtxcflsC7XlYN/EX8U/52KVJCQtvDnD8G/XsO+lHPtMddH76LdXjH+30zo96HTGqoN4=
*/