#ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_IS_PLACEHOLDER_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
# pragma once
#endif


//  is_placeholder.hpp - TR1 is_placeholder metafunction
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


namespace boost
{

template< class T > struct is_placeholder
{
    enum _vt { value = 0 };
};

} // namespace boost

#endif // #ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
J3xlzPt4zrHF/dhcioRIQ0tAW06ZgBRaLesK5udbScJQ3xB4CmtnM8dUzSGmknb4mj8lGov7WjD7tTxlRNwR7XkaFhQ41VOhsZGZcDjXVYpJz2bjIr6pGXZMdcsrYSk7clJH1ZX/+Uudw2CDZOa04A2v3DhrZuPfrz7G+IhvdRGc8LSo6a9X8etm3bWVUFOyPVGh6dyCsiDuMH8pdwDQWqTQcHoc+eG0K36qtm1CWR+PgZsBAfksUSqVyMYqBviSMCFvODaHXG+jgka339LITThmaNyN5kbIQi+TPMDS/K7LhnwPiwPCkhlpG3QEDPVFUZ2jtD86i7H2noeQaQNylm6dQFszC8lWqlWwbiBk084Qz90PZ/cmTQvBWQDUbs0Ose9KflCG1auXKwqmVsS79iIYIwyf9K2U+PQtLgE3kSVsvhaJUaSyFwoousefAX7yBhrX9eCKL83nqiSUeca0EGwQ8CL8f2O7QFTp9T4ic9pZqF4Kni3b7yz+Fi0z9kIDeqqNsI5aEsgjVMVa4RzCjhgavVxd0Xr7REbCR6jGnrvc4RDnL4hgfUXhAA==
*/