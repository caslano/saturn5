// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Skeleton and content support for communicators

// This header should be included only after both communicator.hpp and
// skeleton_and_content.hpp have been included.
#ifndef BOOST_MPI_COMMUNICATOR_SC_HPP
#define BOOST_MPI_COMMUNICATOR_SC_HPP

namespace boost { namespace mpi {

template<typename T>
void
communicator::send(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_oarchive ar(*this);
  ar << proxy.object;
  send(dest, tag, ar);
}

template<typename T>
status
communicator::recv(int source, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
status communicator::recv(int source, int tag, skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
request
communicator::isend(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  shared_ptr<packed_skeleton_oarchive> 
    archive(new packed_skeleton_oarchive(*this));

  *archive << proxy.object;
  request result = isend(dest, tag, *archive);
  result.preserve(archive);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_COMMUNICATOR_SC_HPP


/* communicator_sc.hpp
QIocj/3mzfObCRxaFyuLIQtynRr6vWPzYerEhuwhilbdAveLiHFeozXFHlkgBkwg+jR2xs5gg/Uea27zhEA1VkVDgEQ51XMJ/8KHqefB8i/7pRxKiHb4A7w5vJg9Xfge+DM5m0uC3D9HrKeT0GrktgtEqt6RPSk6eDZJnuaYHFj8S/iz0y09sUyl7x1ZFpHaShhPfW96xZP4J7+cz66ns/nNmN3GMVaOr5XeopXw1lAldme0Q+34E+qtyyRctycaY5cbLSEujMUTJmoqbPV9OpG5smC/d1o3PENFqhq09DHGU2M4+dT7EIiDL51hd0Xe0vSGxV1AkP6pIcucqyjhGAZaldg7CR+5y2gpkljVCXxtTQ8KYlOWSifh0DaYyPM2d7VcR7RbbqLHFbQlpBD4qcqqwAvKGkDCn13dEOOJirYHiZ34V6zztIH2XaBShzW4DLtmQaYsvCFqGNvMuDEL9h2WKKraOBObImQ0U9CVgONsjNiDsU7Ct2pG7B8ZwW+3JIDasKsLcf66WG8ely+jQyMlTMRkxEYkdCgTiFNtMQz7f1BLAwQKAAAACAAtZ0pSABEn6zICAABBAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NTlVVAUAAbZIJGBtU11T
*/