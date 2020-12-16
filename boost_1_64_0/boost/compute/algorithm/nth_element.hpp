//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/partition.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Rearranges the elements in the range [\p first, \p last) such that
/// the \p nth element would be in that position in a sorted sequence.
///
/// Space complexity: \Omega(3n)
template<class Iterator, class Compare>
inline void nth_element(Iterator first,
                        Iterator nth,
                        Iterator last,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    if(nth == last) return;

    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    while(1)
    {
        value_type value = nth.read(queue);

        using boost::compute::placeholders::_1;
        Iterator new_nth = partition(
            first, last, ::boost::compute::bind(compare, _1, value), queue
        );

        Iterator old_nth = find(new_nth, last, value, queue);

        value_type new_value = new_nth.read(queue);

        fill_n(new_nth, 1, value, queue);
        fill_n(old_nth, 1, new_value, queue);

        new_value = nth.read(queue);

        if(value == new_value) break;

        if(std::distance(first, nth) < std::distance(first, new_nth))
        {
            last = new_nth;
        }
        else
        {
            first = new_nth;
        }
    }
}

/// \overload
template<class Iterator>
inline void nth_element(Iterator first,
                        Iterator nth,
                        Iterator last,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    if(nth == last) return;

    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    less<value_type> less_than;

    return nth_element(first, nth, last, less_than, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP

/* nth_element.hpp
0rUvxWfSlP6Ifekv2o5h14/Yhq+Kf9cjaa+JDW2vrH+jvYZoe9WqQobt+k73TkxbwmaPrtdePIiw/o/8rKhxWpqz7fLFfh0zAKeUYsKfIWUMmHjTKUfn8PaTMBUmzEQ0fTTVdMy7YbMv9icSppDRHOeYf5/ABLjTf/hzhmT+dXk2LXA+m7rVtaNeu7VTHRLkKw3+DZNN/MwxUq9zFgeqM6R2D/msOkb3zmq9jhD7x5GfXcW/jdgnYR8q9g9N3RLerlsTfhDPDdHqxomr4pZJPXr1OvXre4qEeYkQPk3bqZMjFW6TMIutHrRHvFWnM+UpzNN6ruUsbZtn1O3ZBrRR4Ky3vWOcZ1fmuTyjFjieUcPbTOrA8X7R39GS32Mk3AreBVfgs2as80xKfRKXeanGOWdp2CxzJuVNYr/a058rDUQXzkxMhDMpNW5bo19ok9g3eXL5mj2ETVCzMOFnUur8pnEzI7bVN+Kfg86qK53fSlRnV0mA4+rm1AnMhb3aUU8deJYPPK9mMQ1mRjMf9kU9ULOYZom+GCynJ3RM6JTQNaaZL0qUFUU35019YmxCc/7u6OXPODaK2O/tMWF6hNKDZ2JJ3k72ZNHb5rPzrrMn1TwPpearrjQzB1dTcPsszmsk7njPAFI+kZYd5Glixsm7xDXnmZHWAQk71lNLHcgZjcZtMm6h9VJdGnp+/up8s1dZ1jjzNN142jRdwgTTaeJpxSzah918z+OTKuEdfoyxHfXqP1XfH/xJwiV7MqmDl/Qc+EpTB2HP9FrGH4nfHOaY47lieJkGsE8GOz6hz3pLJI5X3NLU7Qxxi2Xsmee/sHyfZT1KydIljvjrtYutOOLN4i9ZD9He0fj9Omxs727guO6ZX/8MR8ZYxDMck8LPcDRu9juEcN0jizpb8put55gUwRGBNco4M84ruVE6ninTdRztkjD5nl78W4Z5HaNjX+OrvjSJV83F9T5n/DfyPoieruuGhcfjxq7HFO59p1oj6unZKjTxuK/qe7AnxT7e00315IWPDV2ra7wkiTcd++Nin+TpSZzXMG79PRlOkjy1N/eH/mJPI29e7dP18m3uG1vEfQF13af+N1nt55aEuYfnklTTx6ML5D1GaB839TpNwjOexG5fu5vVgjdUfunHLYL7I8UvxvGOZLy4xYkb5ZHfCHHzWu3MexO9Dr2c/izfPK8n7XSJI/7mur2spqL1rAfzZEpHxkknzr6pk2mJ+lEs3x1i4jGJidHRMV5fKrNhHH3CtGvNsrmW3UYPS5oT1G7Xg63jam7psmWrTNs8K+GHqt2El7HnnGud4y2yLgrz7sLWRSF26bs6Bp36KorMmlP6m+Meur271rmHdJWjyXh1QXBs6Zq/mH8dz+32d37aXMP3MvohNoq9LafSe3V8Od+/TjRxOH9Xx8mVYs/wHG+NVTee/sYH3O5gNP3U9T5caNLJcr3XVhr/7iHPEswWTr2F9GF1l6jEDc7X4/V+pnP1Hklritxzq5mXyrrpPbdXQmd6T4uEfG65UYFbbhK33BnBW25iYpQcRh4r99z4hOYJHQOhY5okxnld77GXyXWaedqzxptAffxJ5n/8nHUSPpeYfK+VMG3N+86rJb2/sGqchltoWT6gNOdouKDbK4yYnfXmm6Bu0CxJux9zSYbp54PFLV3vryZtxmZ/9vCPZ19pdP35RfWIPi1hX2O+GKtuoWVc4zrH5Il/smPeGISb892qCSdzhHzD03bzd697vxNY9lTFRPmSea/vS3G81ze6hw7U9Uu1B/OWItcmivwelTDJlB83vXawDnqRWiF/adr8Ku13LjpuxG7SbumYH3aHzA95h3lXkBuio7DEvJfStWU=
*/