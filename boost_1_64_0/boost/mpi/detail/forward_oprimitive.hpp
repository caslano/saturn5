// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/serialization/array.hpp>

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal output archive, which forwards saving to another archive
///
/// This class template is designed to use the saving facilities of another
/// output archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_oprimitive
{
public:

    /// the type of the archive to which the saving of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;
    
    /// the constructor takes a reference to the implementation archive used for saving primitve types
    forward_oprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    /// binary saving is forwarded to the implementation archive
    void save_binary(const void * address, std::size_t count)
    {
      implementation_archive.save_binary(address,count);
    }
    
    /// saving of arrays is forwarded to the implementation archive
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int file_version )
    {
      implementation_archive.save_array(x,file_version);
    }

    typedef typename ImplementationArchive::use_array_optimization use_array_optimization;

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::save_access;
protected:
#else
public:
#endif

    ///  saving of primitives is forwarded to the implementation archive
    template<class T>
    void save(const T & t)
    {
      implementation_archive << t;
    }

private:
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP

/* forward_oprimitive.hpp
sBh8cjrnaDFzMpxzqmMkcyPOOVqsHOdGZF52T0ilcLxqGuB7En2PQh5gEQw48XcYGcS2SF8S4EvKDmASdnwAbEsCfE15EfJggSEPvqLBRDXUI52et9sna7+Dnwfg5wb4uRp+Loaf0+FnWPvkuHV7/v9h+jyY5L8jFH02LPqcESyA21wm4OwHHnrLIXJTbVepkY1V7ZSuxUjPcEwH/HCCXOOUrsVIz2iUbhQb6AEblUqN4ipohPxAp637kJ+O6EyoheOTaLkXUuRMqHVK12KkZzimw8nvBDnslK7FSM9olF47tKAa1I+EUDFBwgC9Q/GuGLYIVRjThVBVgH7Q19GEqoLvMxIt2LdWM2ORQzJfIZxztJg5GU45NmpYQbENaoSW+ICWWDHGa5gyOedoMXMynHKqkr9DkmuE09b0cBPJhTktm5DspSMtzFQpLOF14fg+ABGD6VQ7AI8C5ql2AJ159nQ+1cJOZ0/YKd3rmM6JP+R5edTI8svw/xayPOWRkInI3sjpxilwKKUUHHJK12KkZzimA4foBLnSKV2LkZ4RnS5kDdlQg9hQReHeAwr3w7GIURglDYWdGgo7pWsx0jMk3WqI5ReQDEiIL9zp4GCkYrLx2ReEooDDeF4RugzFGOjVJlZDx4bidNUA66D4Dd9adABAoH3EiHhjZWixMjIcM2qcU6kB5wzNOSNWA7XAbhPBqqxqb1K2b3/QY0x2P3BvOPc/3KlmbnlIhmVEYXE6WKlWTDGSa2mRBd1oSXFvVZt4AR0bmldJp74B+xmcGQAe+oSoAwe/H4k6/C7aD0R9L83sfiDqvqxkErcejjXvVoYWK8PrnOGQKpjjnKHFyvA6Z1ip6jHdvJYxwWRSzX7U+fIiTHpFFJNeIUHBLr/x4S7J2k3wczX8XAo/Z8PPcPjpCT/J8FMKp+Bi+DkXfsbCT3/4aQc/4R7J2l97/J/v/v/n3++D95uBpP88QO43pXl90J1TtSV5AvE6iOiy4Z4zy01ibtpKBpENAyQckPEP9q4DypkpCmf/7NqRDXn66L130XuLHn313nvvrBZlidXrUQ6OXo5yHEe3+mIRBIs4gmBigyAIwrolb2Yy/32szsic83aT777cN+Xe+97cd+97q5NPpwLLMHzWQeNG6s6r/v0PdHdelXBlwG0RhxGbxLkm4cqA2wFcd5NgnsDE5lv9GflsaqaN9UK7A6n8xs4Nn6HdVe6v4CdgWtxfwU+AeesthLd7PZyr9yuf36zKg0OZoowUW6bUDDA3IlOUiSI3omctoqnZuJeinUPq0VSFdg7p7x3zDVviZ6bH+i23o+Z6hPGcU+b9bpC28vW4z8LWKF/omCzQuK2DXkcLIF+ruvL1EbStnZVVyVlZlXBlwG0Bp7GCxLkm4cqA2wHcGytUYayQ93r0GopbNj3TJpiyye8XeYiZrpB8ub+Cn0AXrn/F4lbzXBGzUV+mO9Z6f4e7xYvuh2WCMhFskVCTUWpAJiiZIDcQ1BcLpnRTP/lGR/VobwUxXH8kmq6c2ftT/xS4OU3i3vRPycfwlWWC+8rCU8GZ97qhsy/fCNL1dOqnCPwCpBN/Ap52T8dLqOPNMZT+mkXnbk075ubCiLAJ456XaB/jO7D/2YrmP+Zqnf+f+ozUEOWedj9Wjp6RzmEwV+9wpm941eO7ytvD9r+erMx1BrouHNLbEbAb8NQZ0Xo7IuHKgNsiDtIicS5JuDLgdgDnLvX+LrRnQyv05hIn34SfU0MLpnJw9V6HNAIWYrBVWAezqdk21kZjIDW4sTON83UzQSKaBlcEuHCKPPAtoucGOT6UTT+ENhX+9j2k/Te9D43NdZGzdAyjaalDt4ADd5DYy/s=
*/