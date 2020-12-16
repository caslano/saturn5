// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP

#include <boost/type_traits/is_enum.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/ignore_skeleton_oarchive.hpp>
#include <boost/mpi/detail/mpi_datatype_primitive.hpp>
#include <boost/mpi/datatype_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/integer.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi { namespace detail {


// an archive wrapper that stores only the data members but not the
// special types defined by the serialization library
// to define the data skeletons (classes, pointers, container sizes, ...)

class mpi_datatype_oarchive
  : public mpi_datatype_primitive,
    public ignore_skeleton_oarchive<mpi_datatype_oarchive>
{
public:
    template <class T>
    mpi_datatype_oarchive(const T& x)
         :  mpi_datatype_primitive(&x) // register address
        {
          BOOST_MPL_ASSERT((is_mpi_datatype<T>));
          *this << x;                   // serialize the object
        }

    template<class T>
    void save_override(T const& t)
    {
      save_enum(t,boost::is_enum<T>());
    }

    template<class T>
    void save_enum(T const& t, mpl::false_)
    {
      ignore_skeleton_oarchive<mpi_datatype_oarchive>::save_override(t);
    }

    template<class T>
    void save_enum(T const& t, mpl::true_)
    {
      // select the right sized integer for the enum
      typedef typename boost::uint_t<8*sizeof(T)>::least int_type;
      BOOST_STATIC_ASSERT((sizeof(T)==sizeof(int_type)));
      this->save(*reinterpret_cast<int_type const*>(&t));
    }

};

} } } // end namespace boost::mpi::detail

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::mpi_datatype_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::ignore_skeleton_oarchive<boost::mpi::detail::mpi_datatype_oarchive>)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::detail::mpi_datatype_oarchive)

#endif // BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP

/* mpi_datatype_oarchive.hpp
xikDUyZzUB04UZW6r0q9pUq9dcHsQFsvF+XFtzUfOuuqu/j2OHkhF+qhcFh60vsR+NLzHLrvIvDxMQc6NlpSBqpAjG9nz3Ng+XFNG1zVABppThjxypmPdfDKmSox8GIHzSJlVrxo5MeZYH2VuTgAme7SDD2PwS85VJcirGdg5+ZsQH25TMGhM2I7DVqfm+7ajPiTOp0INsx9VPMc6l4IdYPjp/k15fDGY59Nkvkomu1rPPZ5d+bjFXu+hVjqEVDengvvwn86Rhhv52SZ9xL0i8kzHy3W82LPhf26Bsgyx/dOnSl2UJVpMh9N0vM0fZw289GyPU/3XHgS1obuyxfkroOQ9x3soijkbjqV+mOfW3wqZ51Hp3LWnfCvNfA4AT/tOetcxHXAMLlBp8kUE8CKWl0MWv2ZvauBj6o44neXD47kME8IekLAWINGjRolKhjQhBIbkWBCidJqKyql5wGKelGwBMEQTQwRVLBYoUJFqy1WqmjRggJVQYstIlpU0IipbryosZ4aNJrO/Ofte++OOyFS1LaGX8J7u7Oz+3ZnZmdnZ2fn4GPkKAANnwQnxPDRQjfYn8ye5WrdC3ASZuMnKe2tNeuTScOW1QUiVtEgd3LfNgf70Kw8Wt0cD77lUBINF3znhxszX9xfmHB+OiRmfrrxRp6b6rzhbXvuRMY/ieIFOeMDzeP6hhY69YGgN+ji2UHd9jwmIn6HcnC9vEPZ2Ijn5PraKQiqErJjneCZWyzqQSP/LWxksIzGnRL2NglKwI2eutpfWCCz3jjU5Zo5LeXMmmeaimt2EaffzrPsAuTtzEDeiJpn24bVfOqtPl1qGdANyaU1G9uLKE4KI6PzDZU+1pIHrtN4u2m87cWUR3GHwkO/tLjxJcUNKt5yMH1FxiNoO0npAWxepOJ43ZVM7J6+Tj6MIq8gcadn1s5NLrtMOx2XGJi+uQ65VsWz3vgdYJD6/Kc1OyvTn61DntnaDN3atqKadm/1WXEa+Fg33qJ53qyIjNWs4Q/cvPvnPgrAjezdkOkNn7kXqIw9ojIIVcvnn3N8Gx5t77U9WbfxIdqeGv530A7o6tKjoRqApi6S58YF01ktRPZ9pZyEojoZVFbOKSC+6V6GyHQqriEpxHXpZNAc1y5axw+kUIAjSpl6pyrwoRRrJmrbUdKqElLBNsmzKJ4XFe6r4vkt/bH5/5T4/P8cxgzq3LbnEvC7cCgbKPEg9FFYK/w+gDiFBRbIiwNwJSbn78ehQc0MdFEeUbLPO/BZLQ+6aXnQPoxp2Ge0POzgwjeSZ70hXCkM+Glyzc4MzU0W53oGbHJyLp0EG6g516p41k5hSqQ+317TVKn5di9YZu+4r+WxLwBcoc45cjdeWFyyJ16YkuIga6F89ZPuVinlPtJByr8c9G0iZct/ZU2BeV9Hs2MzWXZTYUrfJAZ8SdGm9E3x0o0E6f646eRKEA/z5njpRoJ0f0x6lBNuuzZubBXjhqTo7Zyt8dKNBOn+uOnkDRIP87Z46UaCdH9MumN3E1pHDu1uPpti7zSoePsBKl66kSDdH5O+P/cwmrG32Ux6VGVzzTveevpb3UwR+MMsmkq8clcL/Ppi3Fba4qUbCdL9cdPJkhQPcyReupEg3R+TDl+ZTXJq3N5HaWMfJezYbZYjf7b7UoSztG/n6tHq7o8iMdFEVw+s3CoGc9MO72M7vA/1+SgVZvv4GUaiDH+cDEdA0dUDy7Z9XVdwtHjgn9lMkfiP4A0zNiF6G0caNDxeM1qbPhrZXLPWS05vDWUbYZ3cSG6yen+4ciM5GkWOSDc4fqSKipNPW3NIjI3eHy/dGzddEuNhbouHuS1eujduuiTuM9FM+fD/jGg=
*/