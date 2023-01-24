// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>

namespace boost { namespace mpi { namespace detail {

template<class Archive, class ImplementationArchive>
class forward_skeleton_oarchive 
  : public archive::detail::common_oarchive<Archive>
{
public:

    typedef ImplementationArchive implementation_archive_type;

    forward_skeleton_oarchive(implementation_archive_type& ar) 
      : archive::detail::common_oarchive<Archive>(archive::no_header),
        implementation_archive(ar)
    {
    }

#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class archive::detail::interface_oarchive<Archive>;
    friend class archive::save_access;
protected:
#endif

  template<class T>
  void save_override(T const& t)
  {
    archive::save(* this->This(), t);
  }

#define BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(T) \
    void save_override(T const & t)             \
    {                                           \
      implementation_archive << t;              \
    }

BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_optional_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::version_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_reference_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::object_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::object_reference_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::tracking_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_name_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(serialization::collection_size_type)

    void save_override(std::string const & t)    
    {                                          
      save_override(serialization::collection_size_type(t.size()));       
    }


#undef BOOST_ARCHIVE_FORWARD_IMPLEMENTATION
protected:
    /// the actual archive used to serialize the information we actually want to store
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP

/* forward_skeleton_oarchive.hpp
mVuZm5pb2rV2a8Ctw23ArceFxtTFNMTUx0CV65Qbqj0dfNx97FsqgO2G6472qk4wB05bTjtOp0pbaL1gg2C9IBRaB20QXco6wTgJOpE+6TmhP8k/AZ3AT96fJJ6USS8TrBIs5x6Fn054kYreQ3/M4cmH1YJ+gapAf0CNoAJQHagM1ArKA9UEediK5ouCRD2yzrNuVUBWECtHK3UrPSuwlXZReW11bXFtU21hbf305MEx5T7lMeUhJYLygPKE8ojyNHM/89g8rD4sH38AMEcVK1EmYS+W6S+Edp7crOnZCSvFW8YTBDiKrPg27jgfmQ6Y7m3+6AkKC8PDpwYIi0G8j8+uNyN6EsP0UhtYm1kblOaJ1gtPeTwLvXY8iTySPZK9tD0Wm8lb0pvTW/Sb9VsoDccrflR0VeRWbFbEV0xWVFecV0RUDHHMlZ/EImJP5jwGvI5aYlYPVptWZVctVndWtVcbEP2I34hdRApizlEeHRAFIN08Cfi903Gaohokyh6AY/f7BFb38FTWIMH78jrVNjCFDMiVj22J6gwzwhf6h4kG/JzEoIYAuf4R/Re8njj6kftfSdGj+z/+BcVREJMvI0/+/f8uMQJ2et89eUHvrde2nmIc/KRGxhuXmmOh509Jc1TKJ+TstxId7ILnAmLTECvIecBBuwQO6PdGmv990OrVU9bD9bP6SW7bjMmZD9PF7Et/cEX+nMSoZYBm
*/