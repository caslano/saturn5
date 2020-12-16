// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>
#include <io.h>

namespace boost { namespace process { namespace detail { namespace windows {

struct file_in : public ::boost::process::detail::handler_base,
                        ::boost::process::detail::uses_handles
{
    file_descriptor file;
    ::boost::winapi::HANDLE_ handle = file.handle();

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    template<typename T>
    file_in(T&& t) : file(std::forward<T>(t), file_descriptor::read) {}
    file_in(FILE * f) : handle(reinterpret_cast<::boost::winapi::HANDLE_>(_get_osfhandle(_fileno(f)))) {}

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);
        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
};

}}}}

#endif

/* file_in.hpp
vf9QVnDq/Yeygsr1H8oKTr3/gG7Y/oNDfwH9yvUXygoq118oK6h8f6GsoHL9haB+uPY9cbJj+67n6rYS+35GNezPxdjacBpxqx/xpoTT1QzXB9gt9ueL/S6HPsA+sW9jtqUPEO/XR2emGg9divFzXrpQG1eS1eanYkLb/DiHNv+Xyafb/NNt/qm1+f62vZVq29l3SP5y3OgoXsBN8hVWaNtl8qdhnNr4AG7Dt+/B+Wais9Wpfcf9qbfvvsJTb999hafevvsKK9e++wor1777Ck+9ffcVVq599xWeevvuK6xc++4rrFz77iusXPvuK6xc++4rrFz77is89fYd3XBttlMbj75jm+3UvqMbts12bOPRd26zndt49J3a7LBtPPq/32aHtPO4CddmO7fxOn/UM2Lfkz0dLhf7FWaxUUPPpdlahIw9xyOMTaasAeU72PWid8gV0vbrNrdjsbw76LlHD4gfUYY1p43tdgvyC4N5fQw/Y7DjG7vMdfKHcwLZxxLOOlfI+IDUFZ+I3Y2ut4xz0Eem49rIvl5K90fyJE7NmZGVFpg3U1XNqc+nDlfpv0rc7zMbMjdtBXNyXjbj9Hy5NhJeT/dTxtPkxFTzTDdzqVQePSTuuFbp/Rbd4Jy+A6QjS65bu0P7MDJPEftOYt9R7PlWK+vopkyeKvY/Yp8t9o3cIeMceu5WN7Gv7n6QHf1uMrcF5DoeS5jZtwCbu+X+HcS/p0W+3TZvT8bfdV6dJ+l5mjp7nZpjpPdR13NhI0XnbB2HFnLd1LWA+zHRfO5XcUgyNgfigH8rpcyMnW4vez+LXpS51BgVkq/RtjhIzajnuXnE3jRz2eYvs0LeF7Kz/0RSMMDobfpM/1yTknbod+X9mcITZxbGMf30V3t7B/Uao+f160WV7o1zR/9qTkotpTda+1e6Pc4bxbwcH/46z8mZjqwGsvnp1tjSAvW7UWrg+nVMbX6/l6R1pA+6EL0P4RUwQs0X+EDplEO3bb5DTezdqv/KtfRda/zOeNWTRaf7rv/Ovqtft1uYfmqWQz+1b5h+6sAw/dTsMP3UEb/RTx3lPDYldbPEXdfZFb9rbcGh/++L+EC/6g04xeffOFX6r+OKcsYUjXP4riXrffH7MdF7KD5Y99wm14/E1zCWxzv0bfHXuW8qc4Tx71mxvys+Qfm3Q67Z50DVUyMv819/ZaaZTysZcy6nI2On5k5GT69Df5gwnfu4spaUMPeK/Sod5stynezUX8Yv5z6wrNfCr3KxX6L92q/i79Cfxq+wfWTxbwP+fSk6l2v/PpPreMc+N/4596GVf6X4FzNFvitq/46Jm5p6njsLX7i+xt3MeNxs4vpa18tlksfVma3bxRzMKrgD5hlO/Xji4Nwvl7WphH+2hN8hPthuLJnJNTOWp5kROg6RolM/vonRKe5AXAfH/j/hOPfpVVjrCKuO+JOl05ok1xm6LLWUsNNcrcwbAzKdzhu8XShLDu8ShOv8bhAMo6GEke30XoHb8O8KwTXffxKdN53eNXAf9t1Bt+tbROclx3cP3Du/Szi/e6Af9l0CGesUyOMTojMl/k/edP1u+pbImji9n+Bn+PcN2dMAP9MkD4fGB/37RZVRh/cX/HN8H9F9jLmXImMt1GaXOgNJ1xdup/cb/HMck3R8v0E3/HdHFfeNM6Q+i3J631Hu9diZqce+WHdEPnSVfDgzPpiWlnK9jX3Bm+jn8ojI9rLu5oRxDmvcF5tZLof3JcIK/y4m69AJr4341Vznew25PkM/L8Nm+68X418y4YfWvfs9eaz0uSHyK9Ph/Yvwnd/tZA0OYfcMhKXD7ijXq5zezfAr7Lucfg5z5sg7jNO7Gu4rNx4=
*/