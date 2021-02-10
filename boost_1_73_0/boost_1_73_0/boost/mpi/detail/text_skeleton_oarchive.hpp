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
SlIQ1yaxSwEAABACAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUwMFVUBQABtkgkYEVSwW7CMAy9R+IfPCHEZSwtYgeqqBc2waRtoFFpR5S1LkSkCWpcGH+/tGH0kuT5Pb/YcQSho1w6TJlQprR+O+L1YuvCpWyVZZtugeVrxqpGk2KC97zgIYUNYYv1GeuJUwUyUeNJXz1dSJLBhcdPMUyjCKTWsLe2eBiwF0mYQNbgI0Rz+LRnL4gjiGfJbJ546fIjG7Dgm0Bb5sR1gJfyiAO2sIbQ0CS7nrDlf4kfqNI98Y5mT4cE4mkXM5iTsiaBXFvn8wdshVpb+La1LnwroVjBb8X7nhZatT6hp7wDXhCKSNmB6OTl/1CUKKmp0d2ZPjAEslaDcnA5SPIAGoegjCOUBdgSxnlT6zETrSxlWv3Ez1HkLQJmIIys/IRa1a4bw+4iFfk4DwSI3FaVNEW4POF8tFpvs7dNMmpff7P+yvjN8i70x/+WeP8J/gBQSwMECgAAAAgALWdKUqjF7URbAQAAOgIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTAxVVQFAAG2SCRgTVLBjoIwEL1Pwj9MNB53q5vsZdOQNcpmTUxkBTUeKwyB
*/