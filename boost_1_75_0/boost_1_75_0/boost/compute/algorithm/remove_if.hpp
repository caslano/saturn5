//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/logical.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element for which \p predicate returns \c true in the
/// range [\p first, \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove()
template<class Iterator, class Predicate>
inline Iterator remove_if(Iterator first,
                          Iterator last,
                          Predicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // temporary storage for the input data
    ::boost::compute::vector<value_type> tmp(first, last, queue);

    return ::boost::compute::copy_if(tmp.begin(),
                                     tmp.end(),
                                     first,
                                     not1(predicate),
                                     queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

/* remove_if.hpp
YAItifJtzou4qqVyWVNSW31ZaouzxOyyrcccOU7qq618GbomtxS5HNsCMITqpgWEd525Xtw7TpiPeI+cPAE5iMFex/cL+hMN/cB+QqfZHgyaFBpTDOCraWKhmsYA/C96pVT8YhZ6oGScF/epYlBNnZ8nrkALh1ELeovy0FEimTugubfoUGyPd0cBcteP2P0FW/BbYipOiisuCHCwo5vJbiU487wa7iWWnwx09kot4aSPcmkZ7lZWehgdblE90qdeDM2+RxGAQQWC+0YxowkNVbCbHst30MFUcd8FbwhGB8sMIzqOyQ+lt4wpifFfhr1nb7I9+y6K9CvPFcoM0yOvNL4YZw0Pl4w6mHpe1CfHTPDBesAHAvsiXhpT8pbJ31XEyGd1yqGccyo8Cdaa0KxsTIlqv3ofA2DTtotA7NvWV3D7+nkk+DF4qV//4nmDLTrMnwlO2GcXaWkVUb/jzOV0VyKfMEB6t6D/hTMPqSRaePhsEk1ORhLeAcVk2a+Mgn6xGYPDNxX7ns2veeySym9z+TUfL8HCYiFYWHJRO69z9kZyWEqHAZ/BfVkF5jDqotqv30vYrAd6kwAGBbzWjaza4rSoCYZ8lEx2EDEUIW+Q02IIkGd3sXA0fpwiZqkU5lpLaNlDLLwlJmdx76TAlfC6dx7LUe/Y5e8FfEY9s6eDdrFEru2pmrAld70pd9XSeEosNV0zfGd7RhvDpBTy
*/