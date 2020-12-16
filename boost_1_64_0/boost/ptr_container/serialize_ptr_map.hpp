// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_map<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multimap<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_map.hpp
c2kryNWalOxn+VijX6a+vbYVZm0d4oC8o87pb7+xRmdNO7NmfSYbi2AQTInU8xrasPOGX3riTlxMmbn7Q6wZVLG4ExdT1hsNpu2z1fRpdET1mVxbm+B/MOxgthD0Ji7DVZbTHw0SRo47obdMse6Lb2VoXWOtO63DMhxaj6FlKdpm5SXj0ZWBNiTefRf0qbR5yYPon6c7fBVlDerZ0UXVyuUKfsTHGgxiBB0bnJSrXndbeVnR5G3k2VN3cKZzJu1uqyMJR88GBpW3lpagS228KVTmBw9OVw8pMvWS6/yFu572cM5aDnWXI41yLZM3tWYjDXKsw9x1RD7qCMo+5BJ5J/u5tdnj06HlTiUn6XFoq6EtgraDoJ0H7TBoEwXtBmjXQ5ssaH82Y5wpaH8da92HXyHGfRDaO7TdW9R7DNr2u5C3E7SnoDVD207Qnje2eYbo7yVov3LVew3aHS7aG2Otc5YCRdtMmeY9q2lk+uO0ZycfKJn1+rhV1YbE6Oja4y4jjDRlTiy90bELHW3dRcWz/IGAPJP/Yqx11sCb+GbIzuXef2Xq9KSUi/uQqtxXZkm7PJMwdHfONzMX3anwJ0/OrSfudfyeHHOIrlO5QMED7j6E3OfyQ61yM6pjP4cZuhl1EzpbkrRxW+XK/J6yz+66bcXaXrrosXA01B0sKi0Udmcbu6+QYpFJJqYp9/akL982tb1ONqoDFVlu2svypBxkU76AZ9H9KvVJgeTXSLvMjGrTR9l03ZuTMxsD3begTJ+rbytotZUzPfa/8/h3Y4XDy+3Uv9PIwQRDNzviHqN4Zukg2syiYmcv8qEtWVDdWNPAs/XivuTOuVq+tHW36+6Sq8/aeNy3uFXi+F1N3bgWuINS7pRNF2VuOdvdlClrJ2VpBvSmMPdcqhzZK8m1sHKiW7/dA/zklJXm2niDK/H69Y3OGLNydd7O5Mgd+mzVX1cg1u3XZ61JOZhj5KCiumGBt3Hwfe+9UuXESINTvvfg9npoe677pJb3hMH06e5KdIm7EmV2m3C0MxRz9rMCunnKLzl/76DxU/OYyygv028k0I+t+w+MtCZ92opk2ZKy6qbkmRjg0t8eFDmIYJLfwH7X3cd2VcY+++WGiOccOsz89AmTXo+Tg5/gnEmZeYTjYNuoerWalI9wrn3fNeGxaTsqXkR6U2KdLqMbKr4s8ptTZWGfe0y5vGjZrV/E6uxnNMmTsNpq6/0FEg+5eOaWl0SuFaMzToN1335RaEDI5xTKNY6NB6ReSnpRYXGJJw29uLBkVjKm78vVfkSvRbG/t0dj9pCc64Caq6ljXI1fPidyKOUV7EUX1950JReWOTLXnJG7OpD6foyyMV5vparj1vfjLJuWLLLpv9H04kH0k5XuViXJyTFOV/Ms8+kTC/f4iynjlVz+1hAM6A7EVgo7dYaxx/YuyXZnijL3nZGzct1+nsai/Gx3uZpYuC+5N+cMKjc3TIQsni94vymscKHh/6bKLzW8l+VyjZcbPqfDOWs1r2WRI8PXGn5vatzrUmzO4OdSiijvRrnCrTqRrsGZLN9L+GZpU227dMNgm6YDB/I2Kssu7rubcz+T4bPpN+XadAYWZxM3O1iJDeW0UD2SRtjovqt6m1NPHQIY0MSKBI/WSdzFCQeKnqJbd7pwWUcsknKm+0erfH5jfbMd2HYghfLeitZd932Wu9XahA+16fc446Wcgf1psL2SzzMQ+5tyKyvQG7VN3qfm+VfaT5hhxQ/bbB4W78aVp8HiS0emiy+fyRX3UczDKFKGnxPl6mEWWfaCKHPz42+WzzA+x9m3l41sBUPxJE6Xsvma0qladT9SZGBF+Ru5rnvxrhztm5RrUlI=
*/