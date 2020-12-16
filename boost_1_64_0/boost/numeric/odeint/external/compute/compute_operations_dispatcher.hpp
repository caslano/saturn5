/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_operations_dispatcher.hpp

  [begin_description]
  operations_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_operations.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct operations_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_operations operations_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost




#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

/* compute_operations_dispatcher.hpp
4GcBn0+DP27gi+UtUdbg6wNfSYMfA1w7fgE+s67/A76Tzr+wgiXO0V1/4Btr+NuvaIlZdPoduPb5jcCv0lzfY8qWOFyTf2kC97dmfHJWRa9/7wKujV8w4N8Zzj/rSob+E7iOv72BHxjwswznv8uAv2w4/3cGfNaV9XgZ+H5Ta/Tb2nr+9sAP1NnHwE+EfOw+an+BdS3t8z++A97V7T+6nt6+usqA3wX8U0388MvrW+IQTf7BBobxE3Dt+An4HRr76eWNLLG37vkQG1si0OAfAteVT2xiiY5ufhi49vnZm1riGA3+OHDt/B1w7fhwMz2+PnDt+NCAXwVca98D19r3Br7YXM8vGfD1gT+uWd9X3sISz2v8i8FWhvExcG3/BlzrnzOc/2Xg2vURwLX6a2s9Xjbg2wPXji8M/LOAbzXZ6Pjp8rawHzT+g7u2s7Tra8T2ln5/VuC+zj4Hrt1fG7hu/779drDEaZrnb2y/E/LXzX8Cv1ezP/f2u1niYM3+Kd8Bv0G3vmN3S/v826v2sMQKuudLAsf4S8wzov8J9rTEXDr9DXxXjX0v9sL9qdufCbh2/mdvSyyn818CP1pgbDRi/5cPgW+O67f6CPyYfVF+Xf8K/Cfd85H3g/2K8884Ynz2oY3+H9e/PGJ8/J0L+0Jz/QLPEjdr8O3rGH9o8P32h/2qwcsNS7ypWZ+6vm+Jw3TPjzbgxxxgiWeFJv7yQPi3NOPvx5uW3N+lNGJ/pP3alrhFo//X71iioYkffxn485r4v1lDvX4sA9fqV+Ba/5vh/McYzn+VAX/cgH9oyF9Ehv7ZgK9vwPcDrq2/gX+VAX/cgH8IfF4NLmJLHKvx790FfE2N/IuufnxeBn6PRn/OerAlvtfsP3TWoZa4EPgcI/TPWYdbYiOdfxX4yhr9tv4R6J81+vcs4Dvq9PeRllhPg28P/PrJNP3vUcr/MusI/f0y8Dl09QP+lub+F8dY4ropRvtfzzoB/hudfXCiJU7OsPz1O8kSO6B+84zYf+rxky3h6tb/nWKJ9XX9L/B50L9sPqL/Lp8G+0y3vg74vbr9T063xEca++rDMyzxikb/fnemJff/X2qE/v7wbH351j8H/avOPwD8CN389bmWuH+y0esjjzkf9ulUQgQjyicus8QDuvgR4Fdr9h8TV1ri8sk1z1e/BvpB1/7XWuJr8JcbUb7gRkvcLTTz4zfBfhWa8t1siafT85f+Bj/mNoxfNfqhdLv++h0D/It0fDDH313/O+H/1Dz/Zda7oH/T/UHm+Rv++vdY4gSNffwd8JM01++qey0xjW59BfBNdff3fZZYV4PvB/x4zf0z6/0G+wK41r4w8APg2vGtgX+VIf/HDfiHwP/UjG9KD1piKl18NvA5h/AtZsjKu70BDwz4WQb8LgP+sgH/zoDP+pAeLxvw7Q14YMDPMuB3GfCXDfh3BnzWh/V42YBvb8ADA36WAb/LgL9swL8z4LM+osfLBnx74Mdrxi/rPwr9pNE/ZwFfSOe/An6Ybn/kx6A/NOXb73FLLK3TL8CnSPqHKSbNf7r++jNLzKizL5+0xKsCtu8U+P43/FmfsuTzk0vAZ/wb/OXnLG38p3ge80MafH3gM2mfj2OILwJ+7N/Ez02d4qUX4F/q2795/C7gM+iuH/AtsnPnz/8iro+Gvx/w+TX4WcCX0+AvA59Ng38HfMN8/AC+99YnYf5Slz/wOTT4XcA30s1/vWSJdwXkZ0T7ll9G+wz5j1wM2FYSs6LfQrpX4J8Uk+KvARfAQRN3AV9UN/8DXPf8lfKryj8344jyPQ58cwHuCLz0GtovZ59l3/cDfmRfP+T54nWMT1L7bdqB+pfT+n8OfGY=
*/