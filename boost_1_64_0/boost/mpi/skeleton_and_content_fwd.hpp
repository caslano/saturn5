// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file skeleton_and_content_fwd.hpp
 *
 *  This header contains all of the forward declarations required to
 *  use transmit skeletons of data structures and the content of data
 *  structures separately. To actually transmit skeletons or content,
 *  include the header @c boost/mpi/skeleton_and_content.hpp.
 */

#ifndef BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

namespace boost { namespace mpi {

template <class T> struct skeleton_proxy;
template <class T> const skeleton_proxy<T> skeleton(T& x);
class content;
template <class T> const content get_content(const T& x);
class packed_skeleton_iarchive;
class packed_skeleton_oarchive;

} } // end namespace boost::mpi

#endif // BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

/* skeleton_and_content_fwd.hpp
D4dK1CntePnmyjidEagyZrhdGAW7lc51i+YC30lz4eMHlDWxgYDAc+IBbxwSOIKDvyjz4i1QUryUtCyYeAH0Gz57QDFOAS+1TDfwBEsa6Hu59kUj8lvc8hP70jQairCyc/Yz/0XKDs6HGTgf5nwzKb6mfKMbUiNleFl5vGJzlfHEFAw/Dmwt3xRCqsPobKqHZ7fh37pNrvyv/iPgcqXMAmBML7OG3WIO6JuKQUPn+BeVpLJ2gg4MCi9UAYdU7jbrvoGwv9bgoR1It5ps9qlC2jPFrwTsWdwOZBmh3B3i47TuuUkawvBCusO+XED6aCK9V/aKVdbroMD3YhTeLch9xco74hSSNIQhdJMNIqGplEVTg+mWZc/idiDr3b65b0hnLXQzLX1NN+3rEONQ0nAMuT+mBSVgdH+CZn/yLGOcLVaVbkdb23aBhcBkfDhJZW3JNlmkKZT7lmQi7e2yFWF4LUIK3TqCl6RpuvkFPQGj+a3A5Lc8C67ZQhtpR3C38EGGlNV8kCVdVXwgXaXxecW6HWpfEZgNRLIiF4h0VUmaqc1NFAVD0wzCyiTPgqd+UV0a0RuYKUuGnqMybVXWzhxNsxDRTJxLgrQkCQtYtsEFK5UkjKYnjvTSNm84z4JnjlBFN6IdPkJMKav5LEu6qfgsR9Osr0mzTE0zvdFho5nXgku+lE2Vayprp9dJruVbcM0VWDY+y9W46EVb81lA0FN8lqvpFtLhfxZcvQLLRjevBZd8Kavp5hf0FN28mm4FJt3yLbjmCiwb3XItuGRJWU03SVL/36m7avQ16ZZlwdUqB9LJ6fxUOR0U9BTdHOVavgO/5XfAbxlSNr1cy+lYrumN1QzANd06mp+6jvpt/GaTa6n8lpOG33Ic5FpOermWk1auiey1CzYd+qLXUUlLFW0BAeMk2wIO/BbogN8ypWx62ZabVrYJjpLWwToakLRU8SZdTa8XyLy36zmCu4N8y00v33I7lG96MztLswEtJbZVFJP0IhrUiyjBcJJteQ46W56TziYISBrQzC7bBEw62SZIS1L6NTRPr6E2wSa9dJJreVbPuF0fEAXMQrEsJ32NEdDd7ESuefVWSa90crpbipzWKoHI6c50guxUnUCHLgkOqfqN8LFHzRulr/UiufayKKe2dUfsg3TraDfpY6pc4yxZR0WuSaaDvtbNSV8THFL1zyzpquhr2j7om2wfNLX+DczJH9RsbNgZHQeGkYsNo/JNdGQGDaNgXX94xrhxVnwzpKIpGlpCX/zgPU/8oullqKDr1WyiAyZULz/+GCRi2RkNmyEHzDBvYAV98cdDK/gpvS0ueGvQDh92gLiJuG+JPMq3LOTHqtNWbYbSaNz67oAJSt/98cAd6gHoZb7u9gaB9e1teqHN0tfz6cB703TT6L14zX+R0Xvkc+Tzf/pBf08RTGSZqeb7/XPu+6CdHs/7wSN4AtIHTiC+NuVa+ukwt6W+UboQqoJMmxLCG91vCblqfaVbEvkAbWtZMQo3Eh1p61OrG9vbsZmGLVR3MMiyxqpQNWQ1Tg/BXSQ30alMlZvRKTyqFJ1HmEs53V8/+X9Xf9Bu3Fz3QTt0lGvEKuBxujZG/mQ4ec/XSNSbTQf52gCCimX64S084YVeesem0shbjRnwyukhvVGD7+253ArEK2FqK7xjkz+ID+4ZQ++jhE76q5/na5waqjQWX9jBs4W6//fCoEm/YU2AWweg9+7oVfBvZjQX/g1EJzQ9AkXxjSJ+f7Auq3RL0wPoF4T/uNlQFVLK+Mk3sM2QGqBbE1EC7aPnA7lwK7yRkVTo7MRMPFR6MzxueDShjriYnQgssI74MQCDG61orTIuToLTLaFePcw=
*/