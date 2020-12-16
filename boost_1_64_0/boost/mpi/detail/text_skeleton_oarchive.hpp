// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_TEXT_SKELETON_OARCHIVE_HPP
#define BOOST_MPI_TEXT_SKELETON_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/mpi/detail/forward_skeleton_oarchive.hpp>
#include <boost/mpi/detail/ignore_oprimitive.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi {

// an archive that writes a text skeleton into a stream

class text_skeleton_oarchive 
  : public detail::ignore_oprimitive,
    public detail::forward_skeleton_oarchive<text_skeleton_oarchive,boost::archive::text_oarchive>
{
public:
    text_skeleton_oarchive(std::ostream & s, unsigned int flags = 0) 
     : detail::forward_skeleton_oarchive<text_skeleton_oarchive,boost::archive::text_oarchive>(skeleton_archive_)
     , skeleton_archive_(s,flags)
    {}

private:
    boost::archive::text_oarchive skeleton_archive_;
};

namespace detail {

typedef boost::mpi::detail::forward_skeleton_oarchive<boost::mpi::text_skeleton_oarchive,boost::archive::text_oarchive> type3;

}


} } // end namespace boost::mpi

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::text_skeleton_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::type3)


#endif // BOOST_MPI_TEXT_SKELETON_OARCHIVE_HPP

/* text_skeleton_oarchive.hpp
7nVXHSOBifQ/phiZJdtk3j7+D9yLuSRtwgVSxhNVpjNuqTH3c6k8HUDGgEiouUNPxEn/YS8Ti36Hktld7aA/5Wq+cIK9VD8osJbZvBs5K6aoP6/Xc+LJTO/0EUFM6ynQS6BtipvlyzriHrLPEN2gK7aqKH5e/By17/L7oufgnwfqcrJoi+xem+i9gUWcdJMkgYR9gRWc9It7Y1nDi72zDjl9SOmw60o0qxPejOxFNCv5iW//2ETtXXdvbHuf5JZ88Ftne7dx0mtI0u1t5aS//rYL7Z21cx/bO5Tbe+Bu7XUNoJYUR7U3k5OOi2pvLif17Up7n3/jq7cX57sa/xqJG09UOeP5Pn6TI56vKCwAaCaACAP89RZzBzZiVI2y7knXUXvboqL2EvigpVHTXB8yoC73cYwSMm2mqaVPyG5TE+vT5YQzhR0fIp1VR6sn5zkj0OZLqWKUmmiW+h3C6gYLJO8S5J1t5t3En2d/1itrHIoW704NdjajjxSiIz9yXiD8cMQKNstLA8RJaeVip0mxSSj25uNSbAAKNYsnNJT4EOa1HuBvHf4XQE/YQKrptv0bSFb/JDz/9gz8v+NGxMGk246tAj/5bvFmNWZAos9q+hAmy1CI5jLsJExUF93lHKwf68G6ijrp8TUyIC12tFL0ROccTvdGhwq+wFlytlnyAR0qWKYc1Uk/GChsXaWCYL0yZfEQXeLEUSQ4wpc2lrRBV8QCVY9thHQYcZLCzHFw8HJn2WSz7InaAUxHEQ6G1PkPRuyQpatXRaLDBx8WvAaIEPHmrD9GrGil9bd//UPO4z0I/L/B4v/YYzTNtjRoIma34sA8uMMpDf7K0gAAmzVfrbnJjJW0HUKEUqaIBmi7EZ7jBu3MmprsoSfm760cjuZ0INvsEB8bTfGxieN3NZZtZPGxa1GU+JBIMOpG4iIHc/pp9GLiDB/1oF5F9gvwoUAeDoltlKby/ix09SKlq7VLzaMJHTiaQHyu2PmLRYumBS7T/piUWcplVt1qqUjkU/WHGNDnBDQ8zYxsKEc2O9htQw4qcyJIt++tunfJzyumkTeYWAZiazwkl2M/ZW5xNZtBqtdYhQIoNFoKQbpcBzmdDA2p+lf2+Z93t5vpzV8jDXblx4qPvOPJWH9AWz4hXKpPlgkkonjI/iadgQMiIeqMkkdlyFKZYtb92hlR+UV7yADaxwR9dbeIympsHQgpOpryqzHlX1kl5e9IHE35gvqYaMrN9oADx22CI/xjK5ry3HURZzTlAnKuShxNmWTSxvsdMumDeXHCKEd0nRB9Dy63BVPbfJtC/vrK1y+k4scnHjNPO93Ez+8z58vzRy/X+XHj/66PXe/2jdbBfFoHM3QI3r0xL1j4+wG/eF70VZEbYuILQ6Q+IeSsYySnLY7ERlpdDAivhnhrHSAkBYYArx1NWT27aLcYJOMAKtn37VbYpwuTu0Tj7oUPB6hkT9qt8P6Jq5EofnTpIi3Si+LGj8618rPtj3K037uoa3GP48TDRoR180mtumPv8Dno8T1Nr/HXP6SFOoJpfLEg2oEsMNWtJUYa7QCnqfEr9bLyYIfSufCJSNfCiEfHD1c/r7H94RLHf/5lctfiP/88uWvxn09J3ov4z49H9ddTi2P6a5Gjv66h/ip4KF5/BR7ft/76cKHur1j7Sz/CjKjTuYgEhdoemKVPE3cn3n6ZRUqaWGOfk0hYuHMhItZQjkhKH3b8FueHZcyea0+IcnBFNFNVfpP4Lbjt6tZfjySyTIc82PGkjmKlNDCkRz+BmHy3faw4FwASQne4BhhpA8Dg49aH3oferM0T4Ux9SBVTzx2L9mgD7MqPdR7mObLySrxvFsotbpE=
*/