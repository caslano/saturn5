
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
TwJ7w7rwMNgMHgXHwWPgRDgU5sHhcJqeF+v5qYR7HMyBI2AuHAOnwhPhPDl39UeJXC5s6qM/aqvqy/kcNoHbobSXqKwqvEb9JWFGq791hO/wZdgavgKPhBtgAXwdFsE34Qz4NrwCvgsXw82avilGBpI+5KNX6g7c2XAFTID3whQ9r6/n3eBK2Bs+AH8DH9R0PALzbNqRxlcalVmCeZqviMpWSTlovrbDkJ6H9TxJz5P1PFXP
*/