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
4PWeHGDgDOifYvRB93mTg3HEN91ewSu5uwGjjS0oH3lohTSo1HqsXgviHRnyRgEjqENeT1GAywCVYo/vfbCd4DCrlJay1hg1VM/bwJOPYgl/+25zPb63gcf3tvVkj29J8suWJNwScQb/Ul9yFK/MIrnxTzi1yA2q3wi5g1luPAUcYdHQ2ldwxejl94ANSRHf/yg72l25ARmA574xPORNJLkBQaG+X8uNJyVTd/xJcuMJf5FtRtE3J5AEUeE8Zro/cTKpN2V7b0Llg799N7luuJvApA6v1+KGK0keMk1RRoploHjw3+brY9tZvqXhd8PN9Pe54QoGmBuRKcpA+XU33H0BNxx91/qPYl/U8z4F1w03TTe74R5bI6ZuhnIelOOg7AllIyjLQJkDyttrxtTja0IdKOdCOQbKzlDWgbIolKnXjqnGWjFVgvISlAegXAvlTCiHQ5lv3ZiaHEptnZh6C8oT6wAvKOdAOXydtg+uffz1h7uezDuRb8a8DtXKdsa8ZEoNkPflsXJnMt046b0EHPTO2UjqjWkeK3Ymm3H0DVDaZLoO2gnqya/uVK1O1VQy1QD2xG0CcUvCMRG3CT5uFnOLjE3MzXK5vVwmZr1wBJi9XGReXtdgAdsz4kp3HQTUAeCEDkpyn/NJGjfsA/2S4iT/KZpIxE1yH3uiNS8JBrZTY6afHo0wwC6Glx0407np7FJVtDXpKm0qUX35/WRvnXdjgSEhnOnceKEcJ4mVOAD1fSvZ26DLqT/mTEBWeNf8rKjWBB8vhbzoEQR5KR+vTuRFzzPIq5N5+QUD7nVnzCcYwAGAf+tLN8r3qijfP/74NfpL+WWDLi/eGgBJW+TOBa9wj1CcQU3HMtRolFtDRL8gSbgy4LaIQyclcXYkXBlweyK8SOlWxdFJKR3e4nR4yLwqd3i5ZBUp46si4cqA2wJOPl2Jc1XClQG3J8IrlElTEbLhKxjb0eqeG8z2zrQpvkdzss7gps7BgxTq4f4KfuJ3KcFPOEpA9IDpcZtMUUaKLVMcA2xsxDE24hgaKXdSHlYR8rDmQhctJfxx/lFD70bQXBSnCAEB5KDJZ8rNiX33tScPrz2bbxdTtElZy/NpPhwn+DAl3BJxBiXOFYlzRcItEddgJYkKVwGRSKKLuupZ5grKiLb3nHYw2BoHPriJs/Ij/jjwpoyU3F/BT3gGWHT968lkmaKMFFumOAbY2IhjbMQxNNIS0V7zXBs19DzU6EWtpj0hMkGZCLZIcGTU1IBjasCRGyiXKDKsRvMBI776NT0fMCLhyoDbIg4vyxLngoQrA24HcW2y0bNSpBTapvXuIFVu6NVivK2o3NViJFwZcFvEoeOXOFclXBlwO4iTpxf1zO/9rLSG6FXRjPuSfThE7+KPg8k+g176QNOMO+gRTI1wnGAyXQiVJQffG/nzhtALVvlRW/VFJ/xnO/Iz0sPU9wz9xi48++H4uvBk7whHYiXxTd4BHQJDx6sr1OELhOlSUkMu80nT9+R6eXLg5TkMujvaUNz4WDyKMlIsA0WEtYDJFGWiyI0EJX+YjNYQODZaR7i+CM4a1tNDRx3BKVOUkWLLlIIB5kZkijJR5EaeSRV4PFPgnGqOyoOu2jclWPnleCydZ9yzeUx9tRn4c6A8DeUuKJdBOQnKflAm3xZ8NNuAjwbKIJSboZwD5XAo227T9tO0j/bxq+vN9kH+7hZBB1Ot1cHEawWQg6mmHUwOrRnj8JiPHEw8yKiRg6mqHUyO+4pI1VSSkkGJ2wTkxg6mILcJPm4Wc4uMTczNcrmhg6nGDqYAs5eLzGufmWmJ6rVOUc2NQQGABUSdpTQALOO0sLUCX0Mp4Z+qq8BPk3E=
*/