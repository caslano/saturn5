//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_DETAIL_HPP
#define BOOST_STRING_PREDICATE_DETAIL_HPP

#include <iterator>
#include <boost/algorithm/string/find.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  ends_with predicate implementation ----------------------------------//

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::bidirectional_iterator_tag)
            {
                ForwardIterator1T it=End;
                ForwardIterator2T pit=SubEnd;
                for(;it!=Begin && pit!=SubBegin;)
                {
                    if( !(Comp(*(--it),*(--pit))) )
                        return false;
                }

                return pit==SubBegin;
            }

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::forward_iterator_tag)
            {
                if ( SubBegin==SubEnd )
                {
                    // empty subsequence check
                    return true;
                }

                iterator_range<ForwardIterator1T> Result
                    =last_finder( 
                        ::boost::make_iterator_range(SubBegin, SubEnd),
                        Comp)(Begin, End);

                return !Result.empty() && Result.end()==End;
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_PREDICATE_DETAIL_HPP

/* predicate.hpp
7S/x66t9lw+LvNpX2UFz2znam1GNcxvMUNEQaDzy/vQ1nDw4cqq9yJ+FBDUDbeAvZP9Oe/nOyqNywvYo27HTuarfbXziM/JS5C3Qcgc/nBScEir+MqFErmPxzRePoeB1s7V73gW+UBU85LiDA2I92WrGxVSpUlLF/YoRNgZia/8y489lD+up/ILWm18d+bRmEkRDvtnnNva7M0KUKy94TSP5ebiLhekVGPD3XU0DvpIIaL+eeqme+vsyeucTKYS7CmlUkCWZvtQIvPGkCh3QmL1+5osE9E8BEnuLCCrWqrkEvQ4TTkZ6n++Evy+xUf4QbrSQX6lNefYtqm8r0xEGC5ks9z7EfqQwtijvo2DrlDRHX8OhfWr5KKI/ka0KaiR5DCfLVWLIqAypcnSiF4nYE6VwLIYnnYj30Gk9TbwoDwuPGvy5xHc0rxMGh4dwA1J70nmTTBRP7Sg+JXagrIx9uEjjhQcc+9pZ59nglIJa+nnTo8btlkcNeNI4F/4l2sObDjnSqJp0TTOONHxLy+uxRsGZRnBwsh/7noyq++A4IrZ4SSp+fPXauUSi9iPRBpEDk/GPe5OOGZjshScKX3bF9Gp/4RJ/4Yq87IoZqaRejbQ/iMuEfjUz1guvDnkA3aaHPGlJFiVSnapLQ/hZs9ud2sodzBF38qgDnDKd+7rfQOdpcyMZ8dLWq9Ce7tJvZft4zlXiEHLCz/TFsHyxr/g/cIAg/CngiOJPzHTA51VOisWerPUq0vlNKWXOcpjOb84o1M5vpIeoxVPZ20fIbYTYc1ieUUMm9fksF9ao+tjI6TRGHkokY3mHp06t2FcX4oPnemJaC2iyYo+dbmN3KKHAcA9wgF2pE5LYrtkTLIA3jS8S1C3JdKdhZRkPis88RvmcDkVXl83UbMir5cYryQ7pbkz/BHX3XjAVujBesyWWkRPrenrGk5ZHg5mSJ9HK00b93Mrzt1h2uQMFVAh2YdXBXHDD8hksSOTztdKbIrx3L7mCvHffoTpY2Scx81MZdcGcRg8McNqwEEPiyxJyTYJxPKtP59fl2tsIxnc3Jf45tAoDdzLQeQu/dZeOknsemLanyVsq6l0UEHE7+Rpx1O2uuY0fNAQIdmZ0bdxLrmGwVudgNd/pEKdb3QGDpz7mbtP+xPan3nZnMEfzhc7a7wzxhcpJ44xVTfnCEmgMD/A6o+fzj/MnVgX/WhmfsOuZDKR38fB5TWfT3Uwd/GuhJzRbYKbgzli5ZndqAla2rC6BjsE8tMnS7A0z2nhD5aFKT1ZW0dfYZYUqZ/XJ0td/buAmvoeWMS/0AvDAM+UE+AuqdGdXyTnozZS0lQ8uipgL860j4h6/qxdW/DtGkSis5c3hwlqu13yaWoFy5OfJNvNSji+amFFb1AmeDhGFq8pghipLEoajBNLwFxDwtR9xXH9C4GLPQsCiRt4QT8ywmzXEp+t3M4abw3Wregqb7dok9z95Y2DHCuouvUsIdAKKvc53FQP2l6EAphtB2J4+oX3EdO3MzsZKLd8w/8P+FL7vn+vy4aZIltlG+CB77wpikXG+i97oRTMfukMPsbnglL+qK9CJaF0WGgylKkjjtbq4/NtsNbMH7TcuF5GmG5sCBoJD7DgUu0V9hj2ns1yWpmtGVWIjRJLyRHb6+yyyeEugfuSBdzrhrVdfvlUX+STdHI32DJaMJ5tyksFoa6/gt8wJ4xSmXL38IfaYQqTIJ2voiAosogTDg82CQ7VtTId0JTb3InmANv5UFKM1cU9C4KScoNKrdaOa/KO5qqIO+tZWxHXzXyZyz4Beee5+l/FxDu5+YgHqjz7rLdqbonPQTKOGRriTHTZFLpzfrkZ/w61voH0=
*/