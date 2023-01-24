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
C6mp93TaevTFOWxGj50K86pssU6fLH7Vy2sxfvEKn04ocWvNJF9PMVg+o1jnhPJ4luJkZVj4yxe4LiaOSAwA7nAou7wt1I0dhiWc7Z0pG3nw0J+MkeEZriqiepSnAhkBHzGpIeRe/r6TLKVPe59Ei7nHMTemvbVEIRO0ugli5LduUap1yttxUdo/JMNf3p/yNTNaDA4bio9dW1TSWYcnm4tkzPxor1pBGeluNlQTzG2+bx4yik13cUYPPlPj3k+bRGqjYUkUiGwfeaw0ZY7Ku5ibW0CZirozsFc/raRiqZVnFRbV0NoRodWdTTo4qkj8CAQRrHhWPh79srIJHste6zbwFSjE2VRdSfzzumOu3XxUmEk+rvgXl03S8cOXnkhMJ8+8fQ1mZOnKUqTbskLGWAcarrm1ItsaLgqhnQ/7nYkpFr6GPOxfo1zXLbYJ/Mg+ZYkMqyiPjMS/q42fcy+1uBQYeL3NNO2Qt89elBTOsH1dnA2chbQSETsy09ifay0sWGRFXdI32kk5ysQNpSoPn+FScFQdoOw5xhsloq93YQ4oG7sdd33g0XKp9zJaygEGRgfkzmh+q3pFe50p4dXL9u/btB0A+li/Pz/+BpnNGob3SR/NiadE/k6akuvmgL52/mnitqr3WYvq9u1YHSsoyC6YuUH1FA14Uf2JSyvwoD6AmaYN9eevE1lX7hypsCwf4JISnU2OUfno576I
*/