//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
0StW4pAXGNxCylGXltizBhq7nufp1Jl3nX6LuAATn0z/G2j6iPZQK1If0bBdTJt/LvYqCX9Zi7A+YsJnmbr7ROzLpV592keMnGvAT+u50MTNNDJbswaJ7I9rn0mB08U/Vu12+Cbaf2lDI3sVI37zraCM4AL8F2o7LsLciKlqYDvmubRjAaQ+HO1YaM4CXOmQXZ0h/Ysxoe3yCKZJYOwOCmmX2vIqM4BVFvJ6qe9Kkjfto3EGRxqz6t/LtMdusV/vbA+Vb9khfh3sMSz2TNf6T4VviP+FzjGrbfO++K1yHaMZuQG/Ea5j9HnNnz1G55j9Me+J30C+cfpl3Bbh+4y43WLG5kX/5tjMg9Sv7NU0+wNlbEZsU7EX2fsjHHJVB2J1j7228UWYBNp4W66zjXUARmpfwjvH38tiXxJp/BHeOf5eEPvpruNvj/iVmfYmrmP8DR186PHXf7Bj/BE+8vh7T9KujDj+thzh+DNtdQTj7/t6zub/qgzPYyLD8/zsQY/d9PwlaW+f1nnfruM7f/C/K8NTd26Yrn10bVYRdm5Ylr4H7gK7w276Pbc7nAp76Pfpnvo9ohdcAbP1fWs//f7QH26AA+FGOAReB4fC++AA+AAcBB+Cw+Fv4Qj4OzgSqlyJ3ndZJ7jIlSTr++pWcChMg7Nga3gabAOXwAz9XtIWng/bwQtkbWq+0+r9RO57zu+0Ye9Xe8FZcBQ8GU6Gp8AqeCpcCkvgalgK18C5cC2cr/VUAa+Hc/Q7TRm8CS7Q+lgIH4GL7HrQ+Y98utRDvtbDeK2HCfAUOBEWw8marynwh3Cqlr8QXgSnwZIjeE/ceE7b0XsX7P/y6L0P/r69C+71Ae92MWWYtR80vpdt6O+70f8/H3nrqsDj/7d+9v+p3zK6Lt/wqV4+D9/5lfuTLOYPe215fP4UlFxOGn9y/tgZ4yfnF5eWLQjZB1Sj68tgnH7mbP7kXtiRknnN8obobKoVOftCWyeLxsvnvhJt9sx0lrjPsutko5wRsIvwbcXtFE80z++pRrYfufqAdp+yUj4b2utJv4SdLfYKc41ss758WPz7STpJoenUlM8NplMp8WydTIuxN5V4Cz1v6rn+HWRtWlZaS+1TLlnD28/91Wb/3GKJt4+5vb+VKm7BPDxKLspkJ4299662qrrGMrptMiVckcdLuXerfoqPkiQcoSyzf26ihOvtOT+g10PPRYjz1Z3T7fvRIvbz9mQLQ1QT2fdQJ4Nfy7rArOFP7a16+cRO7Ut6d1qdyN+lZi9K/T10UyRea9nL0IU1eRxul5P+FZgrQ/bOXaXPUBt0bc59/JD7HNaYfQ7spevl3Eu3w+wFqxH7LqNLqtZKx77HCu57cPQP8XvF7IdztLnZb06b4idt6jg3YHWUyp9immoaXwbGSu/IY2VuRfnchVbomRll9niReElmH9w1R6ArmbQCeXTk78EY1Uvg5Zs/zIBfkz9/n8j5q16me+PNM/+c6pBnRo2bafa0Zovd531b9MNomeivZr+fiTNM7ewIzladIubZr8y8q/uGsMBj+1WI3xIcU44L+L1lx2OuSdX9rzkSz+tN8sRbez2hOoHmFdM7jf6HXAl30LPZM9yMS8KYffsDxP8zz/2eHvZ19IyAKvyvEP8feMRuytI2JK0VRsdmbwn7ked0z9KQtKokrUX4fyD+GSFlXWT2kXfVet1JPoJ7pzcG3jtonyiR8JH3mpIvh46i9eZ9g7SnuG0w/Yb2cug81oOqdd9WUx1LXv7ZkR257zB03O4DGifDMedr37D9tM9fesR7P2vC9IPXSjnGaTkKVA/9Fnm+IH1MFAEPHLocRjOWS3k0bjczBtL6Sp+wKvnXbS4=
*/