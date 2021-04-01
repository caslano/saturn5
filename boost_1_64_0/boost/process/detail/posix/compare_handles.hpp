// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_


#include <boost/process/detail/config.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {


inline bool compare_handles(int lhs, int rhs)
{

    if ((lhs == -1) || (rhs == -1))
        return false;

    if (lhs == rhs)
        return true;

    struct stat stat1, stat2;
    if(fstat(lhs, &stat1) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    if(fstat(rhs, &stat2) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);   
}





}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
iMvTZag5r0QNNIwA5uTaXnWamR25slnDmJOZm8BGJJLJcR8tSOXXgxhHHis7dAcltsBfB9U/BsJnJAeQGd4aNzOZgQ7iaQq2a2RIsI2hMhMPilDjcTZYjKpy1L6FuKbRo4ej1dJc+XavKBTf99HiIih/34vGVhvnSVWFDx9COuD+m0gy1Q45MTFkBz7NpVjMA5hfSs3ud2TEOLR9nfYy2i04BXQDPsB6fHJq81ILJgoSDIM2EgaqUDGcOJqLD+ycFB4pbX6b+KK/VI7SdA9IWg6H8ZV1GQtGnQ75HdZxAwlKR6+1VR03kunPNvK1qNYQGDZj7mXZ+cO9rlpyQtQjw9FjSsIXI+MlKv0ZT9mVoNqbipRviDcuX0tyhMvU4Lu+AvK4lHln/solXUr3U3spft4Kuj5YV2nwe3sWd3u89kwXZizpz1HyxgbCbkXugDb0EZT16DaSBhLyNAgtjkMTcRCD4ocMe4LXE6tjZdAcxEmNb384vqoIG+F5LP9PJW9oukVSgUydIESUHFeYaIfqhu/qeFcYvZ6JhZkDrfTb8blkJ+Bs328Q6JiOaQ==
*/