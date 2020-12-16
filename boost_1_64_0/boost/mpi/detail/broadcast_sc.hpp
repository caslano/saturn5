// Copyright (C) 2005, 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Allows broadcast of skeletons via proxy.

// This header may only be included after both the broadcast.hpp and
// and skeleton_and_content.hpp headers have been included.
#ifndef BOOST_MPI_BROADCAST_SC_HPP
#define BOOST_MPI_BROADCAST_SC_HPP

namespace boost { namespace mpi {

template<typename T>
void
broadcast(const communicator& comm, const skeleton_proxy<T>& proxy, int root)
{
  if (comm.rank() == root) {
    packed_skeleton_oarchive oa(comm);
    oa << proxy.object;
    broadcast(comm, oa, root);
  } else {
    packed_skeleton_iarchive ia(comm);
    broadcast(comm, ia, root);
    ia >> proxy.object;
  }
}

template<typename T>
inline void
broadcast(const communicator& comm, skeleton_proxy<T>& proxy, int root)
{
  const skeleton_proxy<T>& const_proxy(proxy);
  broadcast(comm, const_proxy, root);
}


} } // end namespace boost::mpi

#endif // BOOST_MPI_BROADCAST_SC_HPP

/* broadcast_sc.hpp
ZahxedA3Xh9Bg66BeiOY944SX5VBU0QdX77h+6SOzvg31o3331L7evlrGzrqOLklld+isyr8DXpWt+IUURL0fD6NOG3NtTTnvmBZNaSXrsffJNPRcWrBJxV8zzcqCYUA3n6Ch78TiiA23j74A8uB15n1mBhcjylANkq2YyulZfg1H9xoEVRpehE0vbsEWyJbgO8AwNCXKRBmcP0hSK36m4RQ9vQydeZKarB/9PvNQ8aDt8CCPrgTk8rwd7CslnqGv0EQtrsE4UyFZeL4iutruAO13Cv8pgSQiNGrePEn7S4Jqz7BzYn+pobD1Ar+zqGaS3pC1cT1mHA5KEtBFs1cLX4Pes4I7YwTTlrxF7ggBIi7BgpKk4u/6ptW8i7F56wgKNFFzpzsDpYZ1KSBoA/3D/Ifz+Pv09OuK6NlNrDw1rWe3W20hj5l1bvaaAwGKRH9wfAJaWeWn4N1IgYy4Qx3aGL5Esf0E8tPc0zvVD7bKb34eRpJWkm/Bljcw9/JWIK0SkNfTitJg7QyYDsB/TCzmpcJc/N1nAKFQcbP8wkPy91klYc5wbK9kLP6+b0KE5cA82i8emVdw9C3Skv2Ug9uScLKCuFE463k5cASY+zldQ0gB/br8wFTEBM8h3DTHKDZxN8JgTOhaULsPQqx8V90f+lC3MF/S8uwJJyJ3kOERqmlVBZIVwDwqhSgEdIPhNxQJ7+mr4K21L7CJmugUNmDuF2YZPzqeiYZN47+QxttA/wsgp+18DMDfrbCT0ISiMzhf/kkyceVFPlxR31PjPru2fv/jwM9vW1XhD0Eu1iOCNZoLCL+uQl+wygDFluihURcAMbcBRla8SsueHSZDDhSQSdyprpbFYnfBgqizueX8/nRVP963dps/46sidG/e++M7N/eY+0f80dFa0z/I3z8+oDBNaP/2V9GerJn1Qrcka3hujLEMJaJAPcRKlSLwQxvMgtdQYVekkLkaJE0EWvgaCflGODpsktFUqLfKjU5HPcCylBvs7dHQV0gUENDzFAXc5k95EBsHNyZ78C3lxFn2azTymP4WPK/YmCaz5lT12AFGlfhSOgin+n/CQ9jnH8lDOPXV8nkoL4qsJdefpq89JeW58jJXGEJVSjkClWnQnFk8OmC+wZ8sV6Rirr6p3GVpVRlvKqSAqVYWFjPzyCPAkZJsONPLUFWGUljMsHaLhrsRXawoaUMFp074HqaTzMP83VDoJG6G4RQ7h8JrbN/jh3a3QwtNBd6ZyEIA3xuobz1uCEs6RVYjUW6dX57SyyGT+ex/XmR6KYyjMQyy5c5qWD18l9tAdrCgHjqp/87aKia8saDq5R/1l92lrdwJTCinYEigN0u/Ao4VE4brH7HYfe8FxMxkksfGiIN62AxDVG4+s7+4wUPl8P09yjk6Z8tOhj05Li82CaEwiUbyHXmU53DAa5zEr7HHFZxNOFFnmy4RxeiIjclh0N/ASwFgEEvTnwn/wjuFSpRDpv7A8noIu6Xq2bg/bJ8snW/XMUXyrR1fL+cdS59TVjXkvsl3bqP109ol6Ap0fMnLJT3L9HDH5LceYpxjk4DjK3f+u2KWPFZ24GFuiX8H46IqpJ/L8L/sC1CE0XqHNARkERk/2G482yJE49N+cIC6I8+otKuryHvO9DNSZBhxuL46HRLQzT2+y/AUwhrfAktADSRg+OM/9T0lzneI09ASeR3TCJh1JPw/sJZQgO6k4cpmGGSmv0MEPHixUyJVmF6eSUyjCIyHrDQhsEo1/5jVN2+XDf0ExyVvuqPbTTgHwfSjnl0thnxGHqBgvWlXfX3oup/dCXXb62E6+Llbj4LM0i+egiO0+/jDdnZ/xtIuf0zuUseQ78=
*/