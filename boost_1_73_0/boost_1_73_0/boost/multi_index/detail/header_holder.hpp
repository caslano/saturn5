/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP
#define BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/noncopyable.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* A utility class used to hold a pointer to the header node.
 * The base from member idiom is used because index classes, which are
 * superclasses of multi_index_container, need this header in construction
 * time. The allocation is made by the allocator of the multi_index_container
 * class --hence, this allocator needs also be stored resorting
 * to the base from member trick.
 */

template<typename NodeTypePtr,typename Final>
struct header_holder:private noncopyable
{
  header_holder():member(final().allocate_node()){}
  ~header_holder(){final().deallocate_node(&*member);}

  NodeTypePtr member;

private:
  Final& final(){return *static_cast<Final*>(this);}
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* header_holder.hpp
1VwhVd3Oky2gIDbbzS4cTWMYdrqb8CTk22JnRQyb0ODXhA65tAAzMQgAWQ34KAvJlLvQ6yNnX8zLDtAHDtOdIocfyIKhIY9Eyul+PV0tJrdT6gI78kf+wBAbPgiypFvT3E3W64/L1TV1x2/+/MuRS/3YHK6mV7O72XSxoe678V9GfztHHQgAKdVtYZcNw+1kNr9ZLW8behY/1X1p4lbR3883M/9uurpZrm79nyaLD/5mdjs1Kf/rCGEZj0ajTkdpphEJJf7NfY1aZKEfsDjesuBLL9gzSWe5ll51bpb6I0Wstx4dMhHSmbEk73f+0yHqmZ0+2C7qD8PRfFnG5tOymk/JNYqAru5Xc381nVzf3C+u/Mn75Wpz0fm10xEpEgIolHaByukjcwCI0g80MmKsADozXQBbi/v5vN69pbPk6b7hVkBX7MsiTZFvHI7tCQqowG2gRcIPLKYk9xEtqdtnRpivLKrOZJBr375W0g2hpdjF2ZbFvkiF7ln3PsyX7ydz/3p6M0Ga+o6UM/XoaAxTuZkUsRZuN2ltt5U1Rvgsz3ka9upTr8FZ39o9PEOHM90zDE1VI2oBWsPWbqAAUPC8426VV2vovstMo1CnQHTqUDF1EKx7imv0XOugZ1OyvNv4WDwy+bxAJUc0eg1L
*/