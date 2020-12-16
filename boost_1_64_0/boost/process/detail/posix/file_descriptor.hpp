// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_FILE_DESCRIPTOR_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_FILE_DESCRIPTOR_HPP_

#include <fcntl.h>
#include <string>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct file_descriptor
{
    enum mode_t
    {
        read  = 1,
        write = 2,
        read_write = 3
    };


    file_descriptor() = default;
    explicit file_descriptor(const boost::filesystem::path& p, mode_t mode = read_write)
        : file_descriptor(p.native(), mode)
    {
    }

    explicit file_descriptor(const std::string & path , mode_t mode = read_write)
        : file_descriptor(path.c_str(), mode) {}


    explicit file_descriptor(const char*    path, mode_t mode = read_write)
        : _handle(create_file(path, mode))
    {

    }

    file_descriptor(const file_descriptor & ) = delete;
    file_descriptor(file_descriptor && ) = default;

    file_descriptor& operator=(const file_descriptor & ) = delete;
    file_descriptor& operator=(file_descriptor && ) = default;

    ~file_descriptor()
    {
        if (_handle != -1)
            ::close(_handle);
    }

    int handle() const { return _handle;}

private:
    static int create_file(const char* name, mode_t mode )
    {
        switch(mode)
        {
        case read:
            return ::open(name, O_RDONLY);
        case write:
            return ::open(name, O_WRONLY | O_CREAT, 0660);
        case read_write:
            return ::open(name, O_RDWR | O_CREAT, 0660);
        default:
            return -1;
        }
    }

    int _handle = -1;
};

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_FILE_DESCRIPTOR_HPP_ */

/* file_descriptor.hpp
/5lzsEPzr/fQZ72D+faburnWdb+6X92v7lf3q/vV/ep+db+6X92v7lf3+9/4/Uvn//NFVSb/W9Y/NP8/2fLLXJiawHdT/faKTL7dLwrJeEeSqrLFIiPyvKLSgsIa0S0no0tDupZlZCtENqM4f6Ytu1xkBdWlpWWESdyUzkqRVZfOKS2bJ+cjqPyaUFyVQdmFLXmnIDKdI4Xsp8g+6CjxlFWU5KMaXGvwM+TPxgbWFEzIyxuRNS4n15Y/p/KxZ2dnDZtky58PycePG3t2TqaVpvI/qTy4ZiFvzJDRmVYrdXsh3G145lg901/dX1T3Ibm5WXgz/l4K9zfq7JzcsHBfDnfPHD0kK5tgTZr2hrtnjbXssF9Rt6yRY84el5k3bFxWbtawIdnG/c8h95yc8ZnjWF+ROeysHEfYrwbd8ZgddHSE/VqkW96Q7GyH+76wslXvDvfX1T1z4lgUsnJV0cT9RihtY0ZlDcV5yBjb7c0It9FDxhq3t9RtIiez5uXkjssalmvifNvEmZs5ZnjmcBIfVpb71X18TiYVmJ07JMdO7zvh+Rk7LmtMrjM/7wbdtSxycvJyskY63d9T99xx43NyiVqbonF/X91zxmflZg7N696jX97ZY7LtPH9Qy91O94cRbv172OF+FEr3kHG5WUMCdTUka4wj3o/VfczZVGBu0DnH4X7AuGvWgs3Xaqvufwlvf0PG547Ky86ckJnt0PlEdWghZ59D0Z09kQaROS43x3F9fBq6RrOH5OTqGp+XUyxz9ubl0fwn8uAvGnN6Y94/nilzVAMdEZ2Ornlw/52ZFHHG5CINbIAqnIZ5vSnvhO0wpxeVz5LzvSL263Y/l/VMe+3Ha00DukHvTHdxP5v1zPB9kDsku6/bsFz3QXbu9WyvzyBeZHa8zvNLn41xL8ODdn4DnfSPxu8sw+x4/gvE60OuHEiY1ll2mNIhI6pnrzmwhupcsBjRe8nXjXmHZ2PKCGUv/BKT4qlv9cDkYNJ8XvZFrW8NxEzEzPBFudUB8drzgdti9ch9p9LqoXPIOop7H58fX6cwB+0FeBiT6Enmu/p2zxds/HaUE3Va+JLNHOIZ4me+lei6n7UdZ7LZO7uisLJapnS6raNAP7ze96aIqVXucc5yd55/PAbfDnv5GHtOWf0xtc+DmJFdew5YZnbt8xE62jIz9yzelvUKyT4+y8gkvAbIphlZf7EPMfa+Yj/J2Htjd7bfSjPvqy2msdZXKjK/2etbyzNi7/9ZuhZnEcaDWYhZGrg/jIloe3lMuy+rcLY/t7aDP9e2Y9aDvCvuc612bu0gwv+e5rKPfblzTUTXs3Fl9nQy9e4L20f+eOr+x8ssbE5/PfdrferZpmw4ezowfvrx/sbZh8TVDzoEvsu3VGYT7mI7XJngJ3P7k+Qs4iJZ2yHrAkJ6f/XY5a4y/tVTP8yMMNfeDeL2O4+f2UNmbYvILtM1ch6+PWPnourM3O4BngT8omfk/dm672SMmbNq5gs/K+F0sFrpPOgtYn+SEAZYpYwkN1ELj1pfOOailpt1MfdL2KWkP15lHr5xB9fKpFttJf+XyPx85h5WBNdMbmIuqH2OrBSTWQPUT8Ib5uniaaSyUPpPYyZxF489j3heUUHVLNMmN0qaX/bsQqMt7SoW2SuONYDOv3+r61YmHue6lcC1vlDylGifsWPL7DN7tG0G6q6x1jcyyS9lgEzKIKwdFTew5CdntmJmY04LtKOfmHZUVFpU5VxvMh24Xrf4iVxPMtc5d/sKcW/jcs3afuuZ9lpmrtdV4jbRtQ9Xf+bsifk0ilQrR8JYWIwgRp9jHGdA/1r8dKLFNDv+sw4wjSXvkfNjNY/I/Kbsy8I=
*/