/*
   Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.by>, 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned_until.hpp
/// \brief Tell if a sequence is partitioned
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename InputIterator, typename UnaryPredicate>
InputIterator is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return first;
    return last;
}

/// \fn is_partitioned_until ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param r        The input range
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename Range, typename UnaryPredicate>
typename boost::range_iterator<const Range>::type is_partitioned_until ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned_until (boost::begin(r), boost::end(r), p);
}

}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

/* is_partitioned_until.hpp
dQuFIEJTmi46lLwDq4KYi/xVDCEp7ghLg5nLCyCjcNp1uKsFS69RhiKtUySEg05QEP+1VSqRFuKVhzeBs9TjsgHhv4PI/CgXL8SvKxMh963I/cqmXXwnUHrkfqVTLW+ctlIpb64awuf/7UM0L0e88bam6cuuDJ8DNdn4AqDt8qJMG/ft5/uTfXsXZmIh8AaxoOCQCQJDHD+9Dkk8GhgFNl8AyxYeBebq9xtGelAhgY3PIDn3Xv+9JLg7R1pN3PkLppRE0QvJuCtnQMmBRoZUOTbutsRw8FxzUfWzn4np3wrN+ONGvesFz2tLGR7/RiFEhl9RMKMi7f4eBOAhjq7bGbY+8xW9wiEbcbxU/x1HTzAL2kCzBN2XMLcQ2fWrBdOaPi5wh4PvgqXp+FJ+LvC1649HwlfuqiS+rokwvhAg6BPjq8ei8lcvCm9lXS3gIMT6ewCOTqN8XtNtQb1V1YXtY/qJhC+Brt34bDfqpH10W4ZKc2ODQOBveWKsTHwIm2RAb0DKX8yU95CCPXDF34Yj2Lt0uISt58cZBXScR2/xt02J39i1C2mN8pSaG8naEdRrUTJAe6rIhrruRl0BYOynjx1vqJNj+usd//Gv6eP12BNivCqfP9J4XfFKcrzW/USM146mTzheJijGEnOUZJ+IbwN0/HKP4NkP/4CQXUkYWmQm3SOSSItdZSbdKpLORdIWM2mCSCpD0l4zqVIkXYikPl0iySeSKpB0upl0ikgKIOl8MylPJClI0sykru9zkoak68ykt0XSOCTNMJNaRdKlSNLNpKUiaSKSnjCTnhFJVyPpz2bSYyJpEpJWmEnzRNKNSHpTJKVFGJr8/WPYg/gkf4eL9yZGT15sWQAa5MmCFa3AKRVjvMeoDIDkE11VxeXjC6ty8FzfVTWI7+2/G7FdVyj6hY1K7NxGCud3hlF54/BveKpRSOEIbG7ZWEecTInNhK/vfQ5kqt6ocMDw6hyjciIckAN8iTVswYSOaLZ5xa0+PPEseLExxmdUXor9HL3Sh6vKZuTDXdbf1rVjeOXZ0xxsVcqmzA2951rhpxEfnrSWW4CqVGjYgYuELUYuAAcPJ2y06ihTbtiLw913fp49KCgcuu7aR0X7QUMFlLkGxZyjzcjtCsIkzHrdnG4oCWiPJxYsVXof3ydAQBVaQM1daAEFxTsNKHBKgquM4SJ9Mg22AnoX8K0lENeYIL7PIK5NA1Fc9IsV97HDaf3p4qrodPjF4skEvOkvDDjDCwbmN4bPKpgRMMENYGRT8J5uwQtSCe52IaTtRVTDgyRtBOSbjYbye1PysC8yDuKMIyjjtcgoL6wUapp9t5CiKpe+R7C94+qZ1b+ze8R7S82o7QvMQfFhHgmyvaMAB0XIyBadNXm4XDKzf0LPyiADAt/HK0iWTGxAOFQSGmKFUDOOwo9M/OipeEPPqTiE8HWY6fjqYaZjtqajAb7diWRnKWwz48meuMsF2wksUHcL+0qWUTm5Y7AWhYp+pwO3QWC2GpWaUenrwCmiMqQblVClGtIIRvTpeK32R+VfafLvz5b8A8wGSAhgn8Vgj0ssm52UgsPkhYPFyOfhoxxTvpp4anYyFvIZ5EwgDDYdO6G4+yERe5vsgKuGygIHV5N18ERoi5WDPPTmDuxtqCx2CEOhEr3bge+uRTuRuyQjk793NlSencEKU5UHduCPK20Pzw/soDBs9tR9NH+/7oXD8ff9H01UVR/N39cxQa09HEGZ5DKpAzGQQIVXf0r8OXpJ9/lGV0ss590zHNqYWzNdlTnebXI9HXAvrQnFVFvQWSvPqaVPfKIoU/ZTUIya8Ca3e0GjjLKra2V/y9ya6lV8GslfC4QeC2g=
*/