
#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

struct forward_iterator_tag       : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag : int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag : int_<2> { typedef random_access_iterator_tag type; };

}}

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

/* iterator_tags.hpp
A6B5RufVLP/nlPwKymNmPlZN1uw/oBSQXakwRr+pDFCop2O+AYBYqFIOsHo6P8oRTlMEfq5hLDffm/oN3jcmoJmh3ZktNMuUfUpEX/SbQlIiKhDFqBZv0a4ebDeIetVWp91Ne/TORA2/KYShXKKpoAuiSg/R0JrDEdU4PHqNP/OOeaQcSVblICEh3+kIEEwtyC/lOinavaPrlqZ0SFJ0iJuFHDe4H+s33yW+XTEI+PJwNrFM4uF8/io5ACV/PQxYTt2hsIk2b9nLlhDlQ9S8YhdgRNpDV8t5TdC61zyX5jR66yf7nMXGpsHw7Q+hLWr+vYrAMuEjJ+0jTr+C8mOa9cKbe8NTar+9V4uvH1+1izEJ02dxjVO94zZlH7eAtZlN+4e5dfzB63yUek5xY9hrgsxOXBhk4F9D88h2Yxu4PA4p0ROkAjE3VQdP+jUtvm7PqLGtJa/jLkIGWD6VHZ8JrGzoC+0BlZDprAq3cPLOEZczVf7wXJQTWYCGCOxip0UP4+yGNzBPEr1HDTCj0fGKNiBHspDdDyPaGWVFae+CauRykv25F8MvZ6NoEwNwJ1+rmK9EGGuqB5o6H2U9q74UsBTuN89yGnXnPsP446caIgmmKchXcd7aI72b5xt5m9P07F5/DMYCpgOs/MkCs7zHF0MWJVrkkWL1UudpIjL/ckzID9JNv3nYzQnJ28CSXd9eJznhuuIvukADc0Hy
*/