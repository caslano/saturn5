//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_SYSTEM_HPP
#define BOOST_CHRONO_DETAIL_SYSTEM_HPP

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING

#include <boost/system/error_code.hpp>

namespace boost {
namespace chrono {
    inline bool is_throws(system::error_code  & ec) { return (&ec==&boost::throws()); }
}
}

#endif
#endif

/* system.hpp
BYxeWONeE6NZsUggN0dka8C4q7a8KsyD7S/PwbL9TjtfdZNqCeQBNQZ9EN8Arazvfnc0Ozx7H06ICZPjqFreEnIZ3ItshLzbfFfqt5jE/rJoHg9mNfDt6Fq+M4xHh9ZXy7bk/qzK9wtBx1/VevUjn4l8DaG4Sc5zwJ62QPyAQ2Lt1dpIVmzg6wf/FVMdnda3BDx3LH5tPb1e6LNzRHAwOZUW9VSUCdTUdsyLPCbuADIPBBlXKgfObmpeSBaRclVh3fV3rZpL0rS7dwhD+bBuZEgnvfkDcH2se5A70VmaDq6pe6hmmHqnNYYdRJfKkKuODLmi78LIOxBPiN38K7xv79yHJjnMeqIFkVUuSjQR7FcNTB4B3GdRdofHkHFdXDaXTrhNPsO0BfkZZ1EIO2q4t0gnxnWojGkRxI8NavW6/Ol5wJl2dtJy0HY5avDCbVQNEo3AxKXA2N677Q7UDhN1xMgQ4w2TJHhwEiKOZ2NcVthvvZlccdH2PVG/Tl8mY55VzrqTKzlM++SHvZsFuG60TI3JCW89B+bwsQ5zc2W8K07fkgzzkbV/6LOvxg==
*/