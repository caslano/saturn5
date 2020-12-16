// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP

#include <boost/mpi/config.hpp>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/mpi/datatype_fwd.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/array.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <boost/mpi/detail/antiques.hpp>

namespace boost { namespace mpi { namespace detail {

/////////////////////////////////////////////////////////////////////////
// class mpi_data_type_oprimitive - creation of custom MPI data types

class mpi_datatype_primitive
{
public:

    // trivial default constructor
    mpi_datatype_primitive()
     : is_committed(false),
       origin(0)
    {}

    mpi_datatype_primitive(void const* orig)
     : is_committed(false),
       origin()
    {
#if BOOST_MPI_VERSION >= 2
      BOOST_MPI_CHECK_RESULT(MPI_Get_address,(const_cast<void*>(orig), &origin));
#else
      BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(orig), &origin));
#endif
    }

    void save_binary(void const *address, std::size_t count)
    {
      save_impl(address,MPI_BYTE,count);
    }

    // fast saving of arrays of MPI types
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int /* version */)
    {
      if (x.count())
        save_impl(x.address(), boost::mpi::get_mpi_datatype(*x.address()), x.count());
    }

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

    // create and return the custom MPI data type
    MPI_Datatype get_mpi_datatype()
    {
      if (!is_committed)
      {
#if BOOST_MPI_VERSION >= 2
       BOOST_MPI_CHECK_RESULT(MPI_Type_create_struct,
                    (
                      addresses.size(),
                      c_data(lengths),
                      c_data(addresses),
                      c_data(types),
                      &datatype_
                    ));
#else
        BOOST_MPI_CHECK_RESULT(MPI_Type_struct,
                               (
                                addresses.size(),
                                c_data(lengths),
                                c_data(addresses),
                                c_data(types),
                                &datatype_
                                ));
#endif
        BOOST_MPI_CHECK_RESULT(MPI_Type_commit,(&datatype_));
        
        is_committed = true;
      }

      return datatype_;
    }

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_impl(&t, boost::mpi::get_mpi_datatype(t), 1);
    }

private:

    void save_impl(void const * p, MPI_Datatype t, int l)
    {
      BOOST_ASSERT ( !is_committed );

      // store address, type and length

      MPI_Aint a;
#if BOOST_MPI_VERSION >= 2
     BOOST_MPI_CHECK_RESULT(MPI_Get_address,(const_cast<void*>(p), &a));
#else
     BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(p), &a));
#endif
      addresses.push_back(a-origin);
      types.push_back(t);
      lengths.push_back(l);
    }

    template <class T>
    static T* get_data(std::vector<T>& v)
    {
      return v.empty() ? 0 : &(v[0]);
    }

    std::vector<MPI_Aint> addresses;
    std::vector<MPI_Datatype> types;
    std::vector<int> lengths;

    bool is_committed;
    MPI_Datatype datatype_;
    MPI_Aint origin;
};


} } } // end namespace boost::mpi::detail


#endif // BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP

/* mpi_datatype_primitive.hpp
ooWgw0Groy7Nki7i0ZUwx0iY44+f05ogWSqJn2MkyolfScu9Dkm+PZ683R4v3UiQ7o+bTvaKeJib4qUbCdL9kr5nSX7T2/tZkrcNLNmqmYbZYn/K9giFFjT3OqmuHquDNHyZ4j/67vuRWP/RgSXbia1pj1QXEb5sGsjO/q37nTVppyh+KiqIn2HEz0hQAQus7XJrRkuqJcV7e+zLc9ri3WnTFi/dSJDu3y29jUSblnTs5rf/LurBnVbbTBFHdaXwgGuZ2/FuHJlLu+ObSOxGS8UmkuByBICEmMxsPnrBRWBPNpQ8iQnhSfJZthwGniSHgcwj0w3u6nfij4Ezw0iU4Y2fETdVqCh+hpEowxs/w5naxgKI+7Up9uKr7XH9PsUNIX6GkSjDHzejKX4qKoifYcTPiF+B6dVA+WCD7TL5ad+GCBijzTwgSz5t4h0ijtK02HEcyVgdcyRjtQ6iPu+p/unG/fS7gH5n0u9E+v0h/RbS7xH0e+eAdON6+p1Mv2Po9zT6HUC/Pvr9MOc7f4jvfr77+aZ+ZP+1oTSzQs0YDCsPWXZi7Ct5iP9/uLWfIJdFwr7XWNZKE8020i62lgdd6qa3ImxIol1cDrc/kJUqADQTgGKAO95hAIO34UJ9gqcFAu5+RvCS4KRgirrrYBihWt6ECGs2XSqGeWX2bhCFsIlq3C5Gq57pLrYs0hZbTXW7q6pP8AeCLQBslSa2BeKXS8W2VlD9Tb052Sc7Ia6qg4MjnYWypVD44qALIXw+6AEbGM/scDepL80kJxUuNlqKTUaxloOkWB4KvdPXtAG38954Q4WvwSOb5L7voW7Zj+8D2MdtWNV5Cp73apf+P/dj3edTfRiPbyR6fIkuaHZQN38W6ZQu436+VL69mL4+Rb3bW/r5ZVklkLpARsc2mBbVkj4YIUomtxgqPsh1bZ/glc7SD5il75DTfQb9x8pLW0NF5mh1KojJqwfYE55KZ0kJc3uFuq6/OTA0l7WPVlf3QdeRsxHVEJhFWJyVjJBKwoNJqaDiEXaUoEYqbqQMj7ojDQhknD4z+MXPXgcyVjmBGzVKxDa6AaZRH2JlPfVBZL+OmsV/O8j7xRwYYUPhP4u9mpi9jJM/cvDfiRb/bdf81/dtm/9SWl4XViOAptGU+ZeeVNrmqJSWJ/QZlghzYIWXlQN6xm17wvTSYzeQLdriKi54Pbf4X0TczDrY0q8f5mfWCR1M2klDhX80SP5mdLuXmtsn8LA1asHgpTRq83vJqJ2DwG6Pvx8RTxAig+E8fhBavoYDR4tvE+jBB9roc7LtwhQ+MfAXC+8VwDtE8IL95hTY7PfmSd8E+9n3qX/eL1a+mtyoerXb3NcvsNVB3ZfR90zqKSz0FqVjoesVus4U43/WwcKD5PwGnfBU17X9Aq/E4Mg1cfxGcGwoShZOFEQNw/x0y9VOJzPSeL1pjxdwNB8o43VhI3EYuHJHHy090cHXSWdr4UJRw5iZmImChlQlvJjRzcGLgzBfZGHcTW7MD3wYxY27UmxuPOU9kAnooGfB1zGg1n770CzsP9ibKlckRzFFVqDT6rGU4ETqsQcN9Bj5g/WnxsdMFq9jZvDtrZtYHP8tJgEwxyG90RCNI+H8f0r/+PO/5BP703KyhwaJU/5YFUlQ3meWd2Cq+zhisn62zvchX55UQOeHUqmDTgnnU96sqb6Zrn5GVY6myxx8pzypk3UJuNiloOf23G/W+FUTtbLdc2qmq8qvSgkZ4a4vzmTDyjWUxkhPpqbqRvB9TKDHblocl3WwE2LDsEzd++rsTPR8l8cPrQj5BQ07UYZ80jXwkjT5wKN93xL67838olN6BI0/hr6EGkdY0Ex5Uq4=
*/